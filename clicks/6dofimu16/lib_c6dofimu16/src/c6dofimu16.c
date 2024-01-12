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
 * @file c6dofimu16.c
 * @brief 6DOF IMU 16 Click Driver.
 */

#include "c6dofimu16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief 6DOF IMU 16 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu16_i2c_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 16 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu16_i2c_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief 6DOF IMU 16 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu16_spi_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief 6DOF IMU 16 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #c6dofimu16_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c6dofimu16_spi_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void c6dofimu16_cfg_setup ( c6dofimu16_cfg_t *cfg ) 
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
    cfg->i2c_address = C6DOFIMU16_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = C6DOFIMU16_DRV_SEL_SPI;
}

void c6dofimu16_drv_interface_sel ( c6dofimu16_cfg_t *cfg, c6dofimu16_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t c6dofimu16_init ( c6dofimu16_t *ctx, c6dofimu16_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( C6DOFIMU16_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = c6dofimu16_i2c_read;
        ctx->write_f = c6dofimu16_i2c_write;
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

        ctx->read_f  = c6dofimu16_spi_read;
        ctx->write_f = c6dofimu16_spi_write;
    }

    digital_in_init( &ctx->int1, cfg->int1 );
    digital_in_init( &ctx->int2, cfg->int2 );

    return C6DOFIMU16_OK;
}

err_t c6dofimu16_default_cfg ( c6dofimu16_t *ctx ) 
{
    err_t error_flag = C6DOFIMU16_OK;
    
    error_flag |= c6dofimu16_sw_reset( ctx );
    
    error_flag |= c6dofimu16_reg_write( ctx, C6DOFIMU16_REG_PWR_MGMNT0, C6DOFIMU16_GYRO_MODE_LOW_NOISE | C6DOFIMU16_ACCEL_MODE_LOW_NOISE );
    error_flag |= c6dofimu16_reg_write( ctx, C6DOFIMU16_REG_ACCEL_CONFIG0, C6DOFIMU16_ACCEL_UI_FS_SEL_16g | C6DOFIMU16_ACCEL_ODR_6_4_KHZ );
    error_flag |= c6dofimu16_reg_write( ctx, C6DOFIMU16_REG_GYRO_CONFIG0, C6DOFIMU16_GYRO_UI_FS_SEL_2000DPS | C6DOFIMU16_GYRO_ODR_6_4_KHZ );

    return error_flag;
}

err_t c6dofimu16_generic_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t c6dofimu16_generic_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t c6dofimu16_reg_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t data_in )
{
    return c6dofimu16_generic_write( ctx, reg, &data_in, 1 );
}

err_t c6dofimu16_reg_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return c6dofimu16_generic_read( ctx, reg, data_out, 1 );
}

uint8_t c6dofimu16_get_int1_pin ( c6dofimu16_t *ctx )
{
    return digital_in_read ( &ctx->int1 );
}

uint8_t c6dofimu16_get_int2_pin ( c6dofimu16_t *ctx )
{
    return digital_in_read ( &ctx->int2 );
}

err_t c6dofimu16_sw_reset ( c6dofimu16_t *ctx )
{
    err_t error_flag = C6DOFIMU16_OK;

    error_flag |= c6dofimu16_reg_write( ctx, C6DOFIMU16_REG_REG_MISC2, C6DOFIMU16_SOFTWARE_RESET );
    Delay_100ms();

    return error_flag;
}

err_t c6dofimu16_get_gyro_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *gyro_data )
{
    err_t error_flag = C6DOFIMU16_OK;
    float mul_factor = 0;
    uint8_t tmp_data[ 6 ] = { 0 };
    int16_t raw_data = 0;
    uint8_t reg_data = 0;

    error_flag |= c6dofimu16_reg_read( ctx, C6DOFIMU16_REG_GYRO_CONFIG0, &reg_data );

    switch ( reg_data & C6DOFIMU16_GYRO_UI_FS_SEL_MASK )
    {
        case C6DOFIMU16_GYRO_UI_FS_SEL_2000DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_2000DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_1000DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_1000DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_500DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_500DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_250DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_250DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_125DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_125DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_62_5DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_62_5DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_31_25DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_31_25DPS_CONV_MUL;
            break;
        }
        case C6DOFIMU16_GYRO_UI_FS_SEL_15_625DPS:
        {
            mul_factor = C6DOFIMU16_GYRO_15_625DPS_CONV_MUL;
            break;
        }
        default:
        {
            return C6DOFIMU16_ERROR;
        }
    }

    error_flag |= c6dofimu16_generic_read( ctx, C6DOFIMU16_REG_GYRO_DATA_X1_UI, tmp_data, 6 );

    raw_data = ( ( int16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];
    gyro_data->x_data = ( float ) raw_data * mul_factor;

    raw_data = ( ( int16_t ) tmp_data[ 3 ] << 8 ) | tmp_data[ 2 ];
    gyro_data->y_data = ( float ) raw_data * mul_factor;

    raw_data = ( ( int16_t ) tmp_data[ 5 ] << 8 ) | tmp_data[ 4 ];
    gyro_data->z_data = ( float ) raw_data * mul_factor;

    return error_flag;
}

err_t c6dofimu16_get_accel_data ( c6dofimu16_t *ctx, c6dofimu16_axis_t *accel_data )
{
    err_t error_flag = C6DOFIMU16_OK;
    float mul_factor = 0;
    uint8_t tmp_data[ 6 ] = { 0 };
    int16_t raw_data = 0;
    uint8_t reg_data = 0;

    error_flag |= c6dofimu16_reg_read( ctx, C6DOFIMU16_REG_ACCEL_CONFIG0, &reg_data );

    switch ( reg_data & C6DOFIMU16_ACCEL_UI_FS_SEL_MASK )
    {
        case C6DOFIMU16_ACCEL_UI_FS_SEL_16g:
        {
            mul_factor = C6DOFIMU16_ACCEL_16G_CONV_MUL;
            break;
        }
        case C6DOFIMU16_ACCEL_UI_FS_SEL_8g:
        {
            mul_factor = C6DOFIMU16_ACCEL_8G_CONV_MUL;
            break;
        }
        case C6DOFIMU16_ACCEL_UI_FS_SEL_4g:
        {
            mul_factor = C6DOFIMU16_ACCEL_4G_CONV_MUL;
            break;
        }
        case C6DOFIMU16_ACCEL_UI_FS_SEL_2g:
        {
            mul_factor = C6DOFIMU16_ACCEL_2G_CONV_MUL;
            break;
        }
        default:
        {
            return C6DOFIMU16_ERROR;
        }
    }

    error_flag |= c6dofimu16_generic_read( ctx, C6DOFIMU16_REG_ACCEL_DATA_X1_UI, tmp_data, 6 );

    raw_data = ( ( int16_t ) tmp_data[ 1 ] << 8 ) | tmp_data[ 0 ];
    accel_data->x_data = ( float ) raw_data * mul_factor;

    raw_data = ( ( int16_t ) tmp_data[ 3 ] << 8 ) | tmp_data[ 2 ];
    accel_data->y_data = ( float ) raw_data * mul_factor;

    raw_data = ( ( int16_t ) tmp_data[ 5 ] << 8 ) | tmp_data[ 4 ];
    accel_data->z_data = ( float ) raw_data * mul_factor;

    return error_flag;
}

static err_t c6dofimu16_i2c_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t c6dofimu16_i2c_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t c6dofimu16_spi_write ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t c6dofimu16_spi_read ( c6dofimu16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
