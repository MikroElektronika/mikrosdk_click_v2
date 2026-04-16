/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file smartdof6.c
 * @brief Smart DOF 6 Click Driver.
 */

#include "smartdof6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Smart DOF 6 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof6_i2c_write ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 6 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof6_i2c_read ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 6 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof6_spi_write ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 6 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof6_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof6_spi_read ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void smartdof6_cfg_setup ( smartdof6_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTDOF6_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTDOF6_DRV_SEL_I2C;
}

void smartdof6_drv_interface_sel ( smartdof6_cfg_t *cfg, smartdof6_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartdof6_init ( smartdof6_t *ctx, smartdof6_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( SMARTDOF6_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = smartdof6_i2c_read;
        ctx->write_f = smartdof6_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = smartdof6_spi_read;
        ctx->write_f = smartdof6_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SMARTDOF6_OK;
}

err_t smartdof6_default_cfg ( smartdof6_t *ctx ) 
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( SMARTDOF6_ERROR == smartdof6_check_communication ( ctx ) )
    {
        return SMARTDOF6_ERROR;
    }
    // Select user memory bank
    error_flag |= smartdof6_set_mem_bank ( ctx, SMARTDOF6_MEM_BANK_USER );

    // Restore default configuration
    error_flag |= smartdof6_sw_reset ( ctx );

    // Enable block data update
    error_flag |= smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL3, &reg_data );
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data |= SMARTDOF6_CTRL3_BDU;
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL3, reg_data );
    }

    // Set output data rate
    error_flag |= smartdof6_set_accel_odr ( ctx, SMARTDOF6_ACCEL_ODR_7_5_HZ );
    error_flag |= smartdof6_set_gyro_odr ( ctx, SMARTDOF6_GYRO_ODR_7_5_HZ );

    // Set full scale
    error_flag |= smartdof6_set_accel_fsr ( ctx, SMARTDOF6_ACCEL_FS_2G );
    error_flag |= smartdof6_set_gyro_fsr ( ctx, SMARTDOF6_GYRO_FS_2000DPS );

    // Enable data ready interrupt
    error_flag |= smartdof6_write_reg ( ctx, SMARTDOF6_REG_INT1_CTRL, SMARTDOF6_INT1_CTRL_DRDY_G | 
                                                                        SMARTDOF6_INT1_CTRL_DRDY_XL );

    return error_flag;
}

err_t smartdof6_write_reg ( smartdof6_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t smartdof6_write_regs ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smartdof6_read_reg ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t smartdof6_read_regs ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t smartdof6_get_int_pin ( smartdof6_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t smartdof6_check_communication ( smartdof6_t *ctx )
{
    uint8_t who_am_i = 0;
    err_t error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_WHO_AM_I, &who_am_i );
    if ( ( SMARTDOF6_OK == error_flag ) && ( SMARTDOF6_WHO_AM_I != who_am_i ) )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    return error_flag;
}

err_t smartdof6_set_mem_bank ( smartdof6_t *ctx, uint8_t mem_bank )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( mem_bank > SMARTDOF6_MEM_BANK_EMBEDDED_FUNC )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_FUNC_CFG_ACCESS, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data &= ( ~( SMARTDOF6_FUNC_CFG_ACCESS_EMBF_MASK | SMARTDOF6_FUNC_CFG_ACCESS_SHUB_MASK ) );
        reg_data |= ( ( mem_bank << 6 ) & ( SMARTDOF6_FUNC_CFG_ACCESS_EMBF_MASK | SMARTDOF6_FUNC_CFG_ACCESS_SHUB_MASK ) );
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_FUNC_CFG_ACCESS, reg_data );
    }
    return error_flag;
}

err_t smartdof6_sw_reset ( smartdof6_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL3, &reg_data );
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data |= SMARTDOF6_CTRL3_SW_RESET;
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL3, reg_data );
    }
    while ( ( SMARTDOF6_OK == error_flag ) && ( reg_data & SMARTDOF6_CTRL3_SW_RESET ) )
    {
        Delay_1ms ( );
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL3, &reg_data );
    }
    return error_flag;
}

err_t smartdof6_set_accel_odr ( smartdof6_t *ctx, uint8_t odr )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( odr > SMARTDOF6_ACCEL_ODR_7680_HZ )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL1, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF6_CTRL1_ODR_XL_MASK );
        reg_data |= ( odr & SMARTDOF6_CTRL1_ODR_XL_MASK );
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL1, reg_data );
    }
    return error_flag;
}

err_t smartdof6_set_gyro_odr ( smartdof6_t *ctx, uint8_t odr )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( odr > SMARTDOF6_GYRO_ODR_7680_HZ )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL2, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF6_CTRL2_ODR_G_MASK );
        reg_data |= ( odr & SMARTDOF6_CTRL2_ODR_G_MASK );
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL2, reg_data );
    }
    return error_flag;
}

err_t smartdof6_set_accel_fsr ( smartdof6_t *ctx, uint8_t fsr )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( fsr > SMARTDOF6_ACCEL_FS_16G )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL8, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF6_CTRL8_FS_XL_MASK );
        reg_data |= ( fsr & SMARTDOF6_CTRL8_FS_XL_MASK );
        ctx->accel_sens = SMARTDOF6_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL8, reg_data );
    }
    return error_flag;
}

err_t smartdof6_set_gyro_fsr ( smartdof6_t *ctx, uint8_t fsr )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( ( fsr < SMARTDOF6_GYRO_FS_250DPS ) || ( fsr > SMARTDOF6_GYRO_FS_4000DPS ) )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_CTRL6, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF6_CTRL6_FS_G_MASK );
        if ( SMARTDOF6_GYRO_FS_4000DPS == fsr )
        {
            reg_data |= SMARTDOF6_CTRL6_FS_G_4000DPS;
        }
        else
        {
            reg_data |= ( fsr & SMARTDOF6_CTRL6_FS_G_MASK );
        }
        ctx->gyro_sens = SMARTDOF6_GYRO_SENS_DPS_PER_LSB * ( 1 << ( fsr - 1 ) );
        error_flag = smartdof6_write_reg ( ctx, SMARTDOF6_REG_CTRL6, reg_data );
    }
    return error_flag;
}

err_t smartdof6_get_accel_drdy ( smartdof6_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        *drdy = ( SMARTDOF6_STATUS_XLDA & reg_data );
    }
    return error_flag;
}

err_t smartdof6_get_gyro_drdy ( smartdof6_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        *drdy = ( ( SMARTDOF6_STATUS_GDA & reg_data ) >> 1 );
    }
    return error_flag;
}

err_t smartdof6_get_temp_drdy ( smartdof6_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_read_reg ( ctx, SMARTDOF6_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        *drdy = ( ( SMARTDOF6_STATUS_TDA & reg_data ) >> 2 );
    }
    return error_flag;
}

err_t smartdof6_get_accel ( smartdof6_t *ctx, smartdof6_axes_t *accel )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_accel_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof6_read_regs ( ctx, SMARTDOF6_REG_OUTX_L_A, data_buf, 6 );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        accel->x = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 3 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        accel->y = ( float ) raw_data * ctx->accel_sens;
        raw_data = data_buf[ 5 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        accel->z = ( float ) raw_data * ctx->accel_sens;
    }
    return error_flag;
}

err_t smartdof6_get_gyro ( smartdof6_t *ctx, smartdof6_axes_t *gyro )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == gyro )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_gyro_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof6_read_regs ( ctx, SMARTDOF6_REG_OUTX_L_G, data_buf, 6 );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        gyro->x = ( float ) raw_data * ctx->gyro_sens;
        raw_data = data_buf[ 3 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 2 ];
        gyro->y = ( float ) raw_data * ctx->gyro_sens;
        raw_data = data_buf[ 5 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 4 ];
        gyro->z = ( float ) raw_data * ctx->gyro_sens;
    }
    return error_flag;
}

err_t smartdof6_get_temp ( smartdof6_t *ctx, float *temp )
{
    err_t error_flag = SMARTDOF6_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_temp_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof6_read_regs ( ctx, SMARTDOF6_REG_OUT_TEMP_L, data_buf, 2 );
    }
    if ( ( SMARTDOF6_OK == error_flag ) && ( drdy ) )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        *temp = ( float ) raw_data / SMARTDOF6_TEMP_SENS_LSB_PER_C + SMARTDOF6_TEMP_OFFSET;
    }
    return error_flag;
}

err_t smartdof6_get_data ( smartdof6_t *ctx, smartdof6_data_t *data_out )
{
    err_t error_flag = SMARTDOF6_OK;
    if ( NULL == data_out )
    {
        error_flag = SMARTDOF6_ERROR;
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_temp ( ctx, &data_out->temperature );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_accel ( ctx, &data_out->accel );
    }
    if ( SMARTDOF6_OK == error_flag )
    {
        error_flag = smartdof6_get_gyro ( ctx, &data_out->gyro );
    }
    return error_flag;
}

static err_t smartdof6_i2c_write ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t smartdof6_i2c_read ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smartdof6_spi_write ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t smartdof6_spi_read ( smartdof6_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
