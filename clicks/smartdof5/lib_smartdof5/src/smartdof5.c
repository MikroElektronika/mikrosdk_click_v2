/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file smartdof5.c
 * @brief Smart DOF 5 Click Driver.
 */

#include "smartdof5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Smart DOF 5 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof5_i2c_write ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 5 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof5_i2c_read ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Smart DOF 5 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof5_spi_write ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Smart DOF 5 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #smartdof5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t smartdof5_spi_read ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void smartdof5_cfg_setup ( smartdof5_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTDOF5_DEVICE_ADDRESS_1;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = SMARTDOF5_DRV_SEL_I2C;
}

void smartdof5_drv_interface_sel ( smartdof5_cfg_t *cfg, smartdof5_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t smartdof5_init ( smartdof5_t *ctx, smartdof5_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( SMARTDOF5_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = smartdof5_i2c_read;
        ctx->write_f = smartdof5_i2c_write;
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

        ctx->read_f  = smartdof5_spi_read;
        ctx->write_f = smartdof5_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SMARTDOF5_OK;
}

err_t smartdof5_default_cfg ( smartdof5_t *ctx ) 
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( SMARTDOF5_ERROR == smartdof5_check_communication ( ctx ) )
    {
        return SMARTDOF5_ERROR;
    }
    // Select user memory bank
    error_flag |= smartdof5_set_mem_bank ( ctx, SMARTDOF5_MEM_BANK_USER );

    // Restore default configuration
    error_flag |= smartdof5_sw_reset ( ctx );

    // Disable I3C interface
    error_flag |= smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL9_XL, &reg_data );
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data |= SMARTDOF5_CTRL9_XL_I3C_DISABLE;
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL9_XL, reg_data );
    }
    
    // Enable block data update
    error_flag |= smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL3_C, &reg_data );
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data |= SMARTDOF5_CTRL3_C_BDU;
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL3_C, reg_data );
    }

    // Set output data rate
    error_flag |= smartdof5_set_accel_odr ( ctx, SMARTDOF5_ACCEL_ODR_12_5_HZ );
    error_flag |= smartdof5_set_gyro_odr ( ctx, SMARTDOF5_GYRO_ODR_12_5_HZ );

    // Set full scale
    error_flag |= smartdof5_set_accel_fsr ( ctx, SMARTDOF5_ACCEL_FS_2G );
    error_flag |= smartdof5_set_gyro_fsr ( ctx, SMARTDOF5_GYRO_FS_2000DPS );

    // Enable data ready interrupt
    error_flag |= smartdof5_write_reg ( ctx, SMARTDOF5_REG_INT1_CTRL, SMARTDOF5_INT1_CTRL_DRDY_G | 
                                                                      SMARTDOF5_INT1_CTRL_DRDY_XL );

    return error_flag;
}

err_t smartdof5_write_reg ( smartdof5_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t smartdof5_write_regs ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t smartdof5_read_reg ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t smartdof5_read_regs ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t smartdof5_get_int_pin ( smartdof5_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t smartdof5_check_communication ( smartdof5_t *ctx )
{
    uint8_t who_am_i = 0;
    err_t error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_WHO_AM_I, &who_am_i );
    if ( ( SMARTDOF5_OK == error_flag ) && ( SMARTDOF5_WHO_AM_I != who_am_i ) )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    return error_flag;
}

err_t smartdof5_set_mem_bank ( smartdof5_t *ctx, uint8_t mem_bank )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( mem_bank > SMARTDOF5_MEM_BANK_EMBEDDED_FUNC )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_FUNC_CFG_ACCESS, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF5_FUNC_CFG_ACCESS_MASK );
        reg_data |= ( ( mem_bank << 6 ) & SMARTDOF5_FUNC_CFG_ACCESS_MASK );
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_FUNC_CFG_ACCESS, reg_data );
    }
    return error_flag;
}

err_t smartdof5_sw_reset ( smartdof5_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL3_C, &reg_data );
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data |= SMARTDOF5_CTRL3_C_SW_RESET;
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL3_C, reg_data );
    }
    while ( ( SMARTDOF5_OK == error_flag ) && ( reg_data & SMARTDOF5_CTRL3_C_SW_RESET ) )
    {
        Delay_1ms ( );
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL3_C, &reg_data );
    }
    return error_flag;
}

err_t smartdof5_set_accel_odr ( smartdof5_t *ctx, uint8_t odr )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( odr > SMARTDOF5_ACCEL_ODR_1_6_HZ )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL1_XL, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF5_CTRL1_XL_ODR_MASK );
        reg_data |= ( ( odr << 4 ) & SMARTDOF5_CTRL1_XL_ODR_MASK );
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL1_XL, reg_data );
    }
    return error_flag;
}

err_t smartdof5_set_gyro_odr ( smartdof5_t *ctx, uint8_t odr )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( odr > SMARTDOF5_GYRO_ODR_6667_HZ )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL2_G, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF5_CTRL2_G_ODR_MASK );
        reg_data |= ( ( odr << 4 ) & SMARTDOF5_CTRL2_G_ODR_MASK );
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL2_G, reg_data );
    }
    return error_flag;
}

err_t smartdof5_set_accel_fsr ( smartdof5_t *ctx, uint8_t fsr )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( fsr > SMARTDOF5_ACCEL_FS_8G )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL1_XL, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data &= ( ~SMARTDOF5_CTRL1_XL_FS_MASK );
        reg_data |= ( ( fsr << 2 ) & SMARTDOF5_CTRL1_XL_FS_MASK );
        ctx->accel_sens = SMARTDOF5_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL1_XL, reg_data );
    }
    return error_flag;
}

err_t smartdof5_set_gyro_fsr ( smartdof5_t *ctx, uint8_t fsr )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( fsr > SMARTDOF5_GYRO_FS_125DPS )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_CTRL2_G, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        reg_data &= ( ~ ( SMARTDOF5_CTRL2_G_FS_MASK | SMARTDOF5_CTRL2_G_FS_125_MASK | SMARTDOF5_CTRL2_G_FS_4000_MASK ) );
        if ( SMARTDOF5_GYRO_FS_125DPS == fsr )
        {
            reg_data |= SMARTDOF5_CTRL2_G_FS_125_MASK;
            ctx->gyro_sens = SMARTDOF5_GYRO_SENS_DPS_PER_LSB;
        }
        else if ( SMARTDOF5_GYRO_FS_4000DPS == fsr )
        {
            reg_data |= SMARTDOF5_CTRL2_G_FS_4000_MASK;
            ctx->gyro_sens = SMARTDOF5_GYRO_SENS_DPS_PER_LSB * 32;
        }
        else
        {
            reg_data |= ( ( fsr << 2 ) & SMARTDOF5_CTRL1_XL_FS_MASK );
            ctx->gyro_sens = SMARTDOF5_GYRO_SENS_DPS_PER_LSB * ( 2 << fsr );
        }
        error_flag = smartdof5_write_reg ( ctx, SMARTDOF5_REG_CTRL2_G, reg_data );
    }
    return error_flag;
}

err_t smartdof5_get_accel_drdy ( smartdof5_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        *drdy = ( SMARTDOF5_STATUS_XLDA & reg_data );
    }
    return error_flag;
}

err_t smartdof5_get_gyro_drdy ( smartdof5_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        *drdy = ( ( SMARTDOF5_STATUS_GDA & reg_data ) >> 1 );
    }
    return error_flag;
}

err_t smartdof5_get_temp_drdy ( smartdof5_t *ctx, uint8_t *drdy )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_read_reg ( ctx, SMARTDOF5_REG_STATUS, &reg_data );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        *drdy = ( ( SMARTDOF5_STATUS_TDA & reg_data ) >> 2 );
    }
    return error_flag;
}

err_t smartdof5_get_accel ( smartdof5_t *ctx, smartdof5_axes_t *accel )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_accel_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof5_read_regs ( ctx, SMARTDOF5_REG_OUTX_L_A, data_buf, 6 );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
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

err_t smartdof5_get_gyro ( smartdof5_t *ctx, smartdof5_axes_t *gyro )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == gyro )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_gyro_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof5_read_regs ( ctx, SMARTDOF5_REG_OUTX_L_G, data_buf, 6 );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
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

err_t smartdof5_get_temp ( smartdof5_t *ctx, float *temp )
{
    err_t error_flag = SMARTDOF5_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_temp_drdy ( ctx, &drdy );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
    {
        error_flag = smartdof5_read_regs ( ctx, SMARTDOF5_REG_OUT_TEMP_L, data_buf, 2 );
    }
    if ( ( SMARTDOF5_OK == error_flag ) && ( drdy ) )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        *temp = ( float ) raw_data / SMARTDOF5_TEMP_SENS_LSB_PER_C + SMARTDOF5_TEMP_OFFSET;
    }
    return error_flag;
}

err_t smartdof5_get_data ( smartdof5_t *ctx, smartdof5_data_t *data_out )
{
    err_t error_flag = SMARTDOF5_OK;
    if ( NULL == data_out )
    {
        error_flag = SMARTDOF5_ERROR;
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_temp ( ctx, &data_out->temperature );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_accel ( ctx, &data_out->accel );
    }
    if ( SMARTDOF5_OK == error_flag )
    {
        error_flag = smartdof5_get_gyro ( ctx, &data_out->gyro );
    }
    return error_flag;
}

static err_t smartdof5_i2c_write ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t smartdof5_i2c_read ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t smartdof5_spi_write ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t smartdof5_spi_read ( smartdof5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
