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
 * @file c6dofimu28.c
 * @brief 6DOF IMU 28 Click Driver.
 */

#include "c6dofimu28.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief 6DOF IMU 28 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu28_i2c_write ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 28 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu28_i2c_read ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 28 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu28_spi_write ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 28 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu28_spi_read ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void c6dofimu28_cfg_setup ( c6dofimu28_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;
    cfg->int2 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU28_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = C6DOFIMU28_DRV_SEL_I2C;
}

void c6dofimu28_drv_interface_sel ( c6dofimu28_cfg_t *cfg, c6dofimu28_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu28_init ( c6dofimu28_t *ctx, c6dofimu28_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( C6DOFIMU28_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = c6dofimu28_i2c_read;
        ctx->write_f = c6dofimu28_i2c_write;
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

        ctx->read_f  = c6dofimu28_spi_read;
        ctx->write_f = c6dofimu28_spi_write;
    }

    digital_in_init( &ctx->int1, cfg->int1 );
    digital_in_init( &ctx->int2, cfg->int2 );

    return C6DOFIMU28_OK;
}

err_t c6dofimu28_default_cfg ( c6dofimu28_t *ctx ) 
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( C6DOFIMU28_ERROR == c6dofimu28_check_communication ( ctx ) )
    {
        return C6DOFIMU28_ERROR;
    }
    // Select user memory bank
    error_flag |= c6dofimu28_set_mem_bank ( ctx, C6DOFIMU28_MEM_BANK_USER );

    // Restore default configuration
    error_flag |= c6dofimu28_sw_reset ( ctx );

    // Enable block data update
    error_flag |= c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL3, &reg_data );
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data |= C6DOFIMU28_CTRL3_BDU;
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL3, reg_data );
    }

    // Set output data rate
    error_flag |= c6dofimu28_set_accel_odr ( ctx, C6DOFIMU28_ACCEL_ODR_7_5_HZ );
    error_flag |= c6dofimu28_set_gyro_odr ( ctx, C6DOFIMU28_GYRO_ODR_7_5_HZ );

    // Set full scale
    error_flag |= c6dofimu28_set_accel_fsr ( ctx, C6DOFIMU28_ACCEL_FS_2G );
    error_flag |= c6dofimu28_set_gyro_fsr ( ctx, C6DOFIMU28_GYRO_FS_2000DPS );

    // Enable data ready interrupt
    error_flag |= c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_INT1_CTRL, C6DOFIMU28_INT1_CTRL_DRDY_G | 
                                                                        C6DOFIMU28_INT1_CTRL_DRDY_XL );

    return error_flag;
}

err_t c6dofimu28_write_reg ( c6dofimu28_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t c6dofimu28_write_regs ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu28_read_reg ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t c6dofimu28_read_regs ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return ctx->read_f( ctx, reg, data_out, len );
}

uint8_t c6dofimu28_get_int1_pin ( c6dofimu28_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t c6dofimu28_get_int2_pin ( c6dofimu28_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t c6dofimu28_check_communication ( c6dofimu28_t *ctx )
{
    uint8_t who_am_i = 0;
    err_t error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_WHO_AM_I, &who_am_i );
    if ( ( C6DOFIMU28_OK == error_flag ) && ( C6DOFIMU28_WHO_AM_I != who_am_i ) )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    return error_flag;
}

err_t c6dofimu28_set_mem_bank ( c6dofimu28_t *ctx, uint8_t mem_bank )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( mem_bank > C6DOFIMU28_MEM_BANK_EMBEDDED_FUNC )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_FUNC_CFG_ACCESS, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data &= ( ~( C6DOFIMU28_FUNC_CFG_ACCESS_EMBF_MASK | C6DOFIMU28_FUNC_CFG_ACCESS_SHUB_MASK ) );
        reg_data |= ( ( mem_bank << 6 ) & ( C6DOFIMU28_FUNC_CFG_ACCESS_EMBF_MASK | C6DOFIMU28_FUNC_CFG_ACCESS_SHUB_MASK ) );
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_FUNC_CFG_ACCESS, reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_sw_reset ( c6dofimu28_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL3, &reg_data );
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data |= C6DOFIMU28_CTRL3_SW_RESET;
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL3, reg_data );
    }
    while ( ( C6DOFIMU28_OK == error_flag ) && ( reg_data & C6DOFIMU28_CTRL3_SW_RESET ) )
    {
        Delay_1ms ( );
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL3, &reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_set_accel_odr ( c6dofimu28_t *ctx, uint8_t odr )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( odr > C6DOFIMU28_ACCEL_ODR_7680_HZ )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL1, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data &= ( ~C6DOFIMU28_CTRL1_ODR_XL_MASK );
        reg_data |= ( odr & C6DOFIMU28_CTRL1_ODR_XL_MASK );
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL1, reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_set_gyro_odr ( c6dofimu28_t *ctx, uint8_t odr )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( odr > C6DOFIMU28_GYRO_ODR_7680_HZ )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL2, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data &= ( ~C6DOFIMU28_CTRL2_ODR_G_MASK );
        reg_data |= ( odr & C6DOFIMU28_CTRL2_ODR_G_MASK );
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL2, reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_set_accel_fsr ( c6dofimu28_t *ctx, uint8_t fsr )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( fsr > C6DOFIMU28_ACCEL_FS_16G )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL8, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data &= ( ~C6DOFIMU28_CTRL8_FS_XL_MASK );
        reg_data |= ( fsr & C6DOFIMU28_CTRL8_FS_XL_MASK );
        ctx->accel_sens = C6DOFIMU28_ACCEL_SENS_G_PER_LSB * ( 1 << fsr );
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL8, reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_set_gyro_fsr ( c6dofimu28_t *ctx, uint8_t fsr )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( ( fsr < C6DOFIMU28_GYRO_FS_250DPS ) || ( fsr > C6DOFIMU28_GYRO_FS_4000DPS ) )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_CTRL6, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        reg_data &= ( ~C6DOFIMU28_CTRL6_FS_G_MASK );
        if ( C6DOFIMU28_GYRO_FS_4000DPS == fsr )
        {
            reg_data |= C6DOFIMU28_CTRL6_FS_G_4000DPS;
        }
        else
        {
            reg_data |= ( fsr & C6DOFIMU28_CTRL6_FS_G_MASK );
        }
        ctx->gyro_sens = C6DOFIMU28_GYRO_SENS_DPS_PER_LSB * ( 1 << ( fsr - 1 ) );
        error_flag = c6dofimu28_write_reg ( ctx, C6DOFIMU28_REG_CTRL6, reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_get_accel_drdy ( c6dofimu28_t *ctx, uint8_t *drdy )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_STATUS, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        *drdy = ( C6DOFIMU28_STATUS_XLDA & reg_data );
    }
    return error_flag;
}

err_t c6dofimu28_get_gyro_drdy ( c6dofimu28_t *ctx, uint8_t *drdy )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_STATUS, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        *drdy = ( ( C6DOFIMU28_STATUS_GDA & reg_data ) >> 1 );
    }
    return error_flag;
}

err_t c6dofimu28_get_temp_drdy ( c6dofimu28_t *ctx, uint8_t *drdy )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t reg_data = 0;
    if ( NULL == drdy )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_read_reg ( ctx, C6DOFIMU28_REG_STATUS, &reg_data );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        *drdy = ( ( C6DOFIMU28_STATUS_TDA & reg_data ) >> 2 );
    }
    return error_flag;
}

err_t c6dofimu28_get_accel ( c6dofimu28_t *ctx, c6dofimu28_axes_t *accel )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_accel_drdy ( ctx, &drdy );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
    {
        error_flag = c6dofimu28_read_regs ( ctx, C6DOFIMU28_REG_OUTX_L_A, data_buf, 6 );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
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

err_t c6dofimu28_get_gyro ( c6dofimu28_t *ctx, c6dofimu28_axes_t *gyro )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == gyro )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_gyro_drdy ( ctx, &drdy );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
    {
        error_flag = c6dofimu28_read_regs ( ctx, C6DOFIMU28_REG_OUTX_L_G, data_buf, 6 );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
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

err_t c6dofimu28_get_temp ( c6dofimu28_t *ctx, float *temp )
{
    err_t error_flag = C6DOFIMU28_OK;
    uint8_t drdy = 0;
    uint8_t data_buf[ 2 ] = { 0 };
    int16_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_temp_drdy ( ctx, &drdy );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
    {
        error_flag = c6dofimu28_read_regs ( ctx, C6DOFIMU28_REG_OUT_TEMP_L, data_buf, 2 );
    }
    if ( ( C6DOFIMU28_OK == error_flag ) && ( drdy ) )
    {
        raw_data = data_buf[ 1 ];
        raw_data <<= 8;
        raw_data |= data_buf[ 0 ];
        *temp = ( float ) raw_data / C6DOFIMU28_TEMP_SENS_LSB_PER_C + C6DOFIMU28_TEMP_OFFSET;
    }
    return error_flag;
}

err_t c6dofimu28_get_data ( c6dofimu28_t *ctx, c6dofimu28_data_t *data_out )
{
    err_t error_flag = C6DOFIMU28_OK;
    if ( NULL == data_out )
    {
        error_flag = C6DOFIMU28_ERROR;
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_temp ( ctx, &data_out->temperature );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_accel ( ctx, &data_out->accel );
    }
    if ( C6DOFIMU28_OK == error_flag )
    {
        error_flag = c6dofimu28_get_gyro ( ctx, &data_out->gyro );
    }
    return error_flag;
}

static err_t c6dofimu28_i2c_write ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t c6dofimu28_i2c_read ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t c6dofimu28_spi_write ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t c6dofimu28_spi_read ( c6dofimu28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
