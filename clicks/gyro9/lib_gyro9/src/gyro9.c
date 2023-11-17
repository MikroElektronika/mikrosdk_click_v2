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
 * @file gyro9.c
 * @brief Gyro 9 Click Driver.
 */

#include "gyro9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Gyro 9 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro9_i2c_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 9 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro9_i2c_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Gyro 9 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro9_spi_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Gyro 9 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #gyro9_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gyro9_spi_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void gyro9_cfg_setup ( gyro9_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dr   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = GYRO9_DEVICE_ADDRESS_GND;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = GYRO9_DRV_SEL_SPI;
}

void gyro9_drv_interface_selection ( gyro9_cfg_t *cfg, gyro9_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t gyro9_init ( gyro9_t *ctx, gyro9_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( GYRO9_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = gyro9_i2c_read;
        ctx->write_f = gyro9_i2c_write;
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

        ctx->read_f  = gyro9_spi_read;
        ctx->write_f = gyro9_spi_write;
    }

    digital_in_init( &ctx->dr, cfg->dr );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GYRO9_OK;
}

err_t gyro9_default_cfg ( gyro9_t *ctx ) 
{
    uint8_t who_am_i = DUMMY;
    err_t err_flag = gyro9_get_device_id( ctx, &who_am_i );
    if ( GYRO9_WHO_AM_I == who_am_i )
    {
        err_flag |= gyro9_set_mode_normal( ctx );
        Delay_1ms( );
        
        err_flag |= gyro9_set_output_data_rate( ctx, GYRO9_ODR_200_HZ );
        Delay_1ms( );
        
        err_flag |= gyro9_set_bandwidth_sel( ctx, GYRO9_BW_0 );
        Delay_1ms( );
        
        err_flag |= gyro9_set_fifo_mode( ctx, GYRO9_FIFO_CTRL_BYPASS_MODE );
        Delay_1ms( );
        
        err_flag |= gyro9_enable_data_ready( ctx );
        Delay_1ms( );
    }
    else
    {
        err_flag = GYRO9_ERROR;
    }
    return err_flag;
}

err_t gyro9_generic_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t gyro9_generic_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t gyro9_get_device_id ( gyro9_t *ctx, uint8_t *who_am_i )
{
    return gyro9_generic_read( ctx, GYRO9_REG_WHO_AM_I, who_am_i, 1 );
}

err_t gyro9_set_output_data_rate ( gyro9_t *ctx, uint8_t odr )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    data_buf &= ~GYRO9_ODR_BIT_MASK;
    data_buf |= ( odr << 6 ) & GYRO9_ODR_BIT_MASK;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_set_bandwidth_sel ( gyro9_t *ctx, uint8_t bandwidth )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    data_buf &= ~GYRO9_BW_BIT_MASK;
    data_buf |= ( bandwidth << 4 ) & GYRO9_BW_BIT_MASK;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_set_mode_pd ( gyro9_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    data_buf &= ~GYRO9_PD_BIT_MASK;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_set_mode_sleep ( gyro9_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    data_buf &= ~GYRO9_PD_NORMAL;
    data_buf |= GYRO9_PD_SLEEP;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_set_mode_normal ( gyro9_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    data_buf &= ~GYRO9_PD_NORMAL;
    data_buf |= GYRO9_PD_NORMAL;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG1, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_set_fifo_mode ( gyro9_t *ctx, uint8_t fifo_mode )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = GYRO9_ERROR;
    if ( GYRO9_FIFO_CTRL_STREAM_MODE >= fifo_mode )
    {
        err_flag = gyro9_generic_read( ctx, GYRO9_REG_FIFO_CTRL_REG, &data_buf, 1 );
        data_buf &= ~GYRO9_FIFO_CTRL_BIT_MASK;
        data_buf |= ( fifo_mode << 4 ) & GYRO9_FIFO_CTRL_BIT_MASK;
        err_flag |= gyro9_generic_write( ctx, GYRO9_REG_FIFO_CTRL_REG, &data_buf, 1 );
    }
    return err_flag;
}

err_t gyro9_enable_data_ready ( gyro9_t *ctx )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_CTRL_REG3, &data_buf, 1 );
    data_buf |= GYRO9_CTRL_I2_DRDY_EN;
    err_flag |= gyro9_generic_write( ctx, GYRO9_REG_CTRL_REG3, &data_buf, 1 );
    return err_flag;
}

err_t gyro9_get_status ( gyro9_t *ctx, uint8_t *status )
{
    return gyro9_generic_read( ctx, GYRO9_REG_STATUS_REG, status, 1 );
}

err_t gyro9_get_axis_data ( gyro9_t *ctx, gyro9_axis_data_t *gyro_axis )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_OUT_X_H, &data_buf, 1 );
    gyro_axis->x = data_buf;
    gyro_axis->x <<= 8;
    err_flag = gyro9_generic_read( ctx, GYRO9_REG_OUT_X_L, &data_buf, 1 );
    gyro_axis->x |= data_buf;
    err_flag |= gyro9_generic_read( ctx, GYRO9_REG_OUT_Y_H, &data_buf, 1 );
    gyro_axis->y = data_buf;
    gyro_axis->y <<= 8;
    err_flag = gyro9_generic_read( ctx, GYRO9_REG_OUT_Y_L, &data_buf, 1 );
    gyro_axis->y |= data_buf;
    err_flag |= gyro9_generic_read( ctx, GYRO9_REG_OUT_Z_H, &data_buf, 1 );
    gyro_axis->z = data_buf;
    gyro_axis->z <<= 8;
    err_flag = gyro9_generic_read( ctx, GYRO9_REG_OUT_Z_L, &data_buf, 1 );
    gyro_axis->z |= data_buf;
    return err_flag;
}

err_t gyro9_get_gyro_axis ( gyro9_t *ctx, gyro9_axis_t *gyro_axis )
{
    gyro9_axis_data_t gyro_axis_raw;
    err_t err_flag = gyro9_get_axis_data ( ctx, &gyro_axis_raw );
    gyro_axis->x = ( ( float ) gyro_axis_raw.x ) * GYRO9_SENSITIVITY_DPS;
    gyro_axis->y = ( ( float ) gyro_axis_raw.y ) * GYRO9_SENSITIVITY_DPS;
    gyro_axis->z = ( ( float ) gyro_axis_raw.z ) * GYRO9_SENSITIVITY_DPS;
    return err_flag;
}

err_t gyro9_get_temperature_raw ( gyro9_t *ctx, int8_t *temp_raw )
{
    uint8_t data_buf = DUMMY;
    err_t err_flag = gyro9_generic_read( ctx, GYRO9_REG_OUT_TEMP, &data_buf, 1 );
    *temp_raw = ( int8_t ) data_buf;
    return err_flag;
}

uint8_t gyro9_get_data_ready ( gyro9_t *ctx )
{
    return digital_in_read( &ctx->dr );
}

uint8_t gyro9_get_interrupt ( gyro9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

static err_t gyro9_i2c_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t gyro9_i2c_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t gyro9_spi_write ( gyro9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t gyro9_spi_read ( gyro9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
