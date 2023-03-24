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
 * @file pressure21.c
 * @brief Pressure 21 Click Driver.
 */

#include "pressure21.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00
#define SPI_READ_MASK     0x80

/**
 * @brief Pressure 21 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure21_i2c_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 21 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure21_i2c_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Pressure 21 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure21_spi_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Pressure 21 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #pressure21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t pressure21_spi_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

void pressure21_cfg_setup ( pressure21_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PRESSURE21_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = PRESSURE21_DRV_SEL_I2C;
}

void pressure21_drv_interface_selection ( pressure21_cfg_t *cfg, pressure21_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t pressure21_init ( pressure21_t *ctx, pressure21_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( PRESSURE21_DRV_SEL_I2C == ctx->drv_sel ) 
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

        ctx->read_f  = pressure21_i2c_read;
        ctx->write_f = pressure21_i2c_write;
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

        ctx->read_f  = pressure21_spi_read;
        ctx->write_f = pressure21_spi_write;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PRESSURE21_OK;
}

err_t pressure21_default_cfg ( pressure21_t *ctx ) 
{
    err_t error_flag = PRESSURE21_OK;
    if ( PRESSURE21_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        pressure21_check_communication ( ctx ); // Dummy read in order to switch to the SPI communication
        Delay_100ms ( );
    }
    if ( PRESSURE21_ERROR == pressure21_check_communication ( ctx ) )
    {
        return PRESSURE21_ERROR;
    }
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_ODR_CONFIG, PRESSURE21_PWR_MODE_STANDBY );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_OSR_CONFIG, PRESSURE21_PRESS_EN );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_DSP_CONFIG, PRESSURE21_SHDW_SEL_IIR_P | 
                                                                              PRESSURE21_SHDW_SEL_IIR_T | 
                                                                              PRESSURE21_DSP_CFG_RESERVED_BITS );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_DSP_IIR, PRESSURE21_SET_IIR_P_FLT_COEF_1 | 
                                                                           PRESSURE21_SET_IIR_T_FLT_COEF_1 );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_INT_SOURCE, PRESSURE21_DISABLE_INT );
    uint8_t int_status;
    error_flag |= pressure21_read_register ( ctx, PRESSURE21_REG_INT_STATUS, &int_status );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_INT_CONFIG, PRESSURE21_PAD_INT_DRV_DEFAULT | 
                                                                              PRESSURE21_INT_ENABLE | 
                                                                              PRESSURE21_INT_PUSH_PULL | 
                                                                              PRESSURE21_INT_ACTIVE_HIGH | 
                                                                              PRESSURE21_INT_PULSED );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_INT_SOURCE, PRESSURE21_DRDY_DATA_REG_EN );
    error_flag |= pressure21_write_register ( ctx, PRESSURE21_REG_ODR_CONFIG, PRESSURE21_ODR_1_HZ | 
                                                                              PRESSURE21_PWR_MODE_NORMAL );
    return error_flag;
}

err_t pressure21_generic_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t pressure21_generic_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t pressure21_write_register ( pressure21_t *ctx, uint8_t reg, uint8_t data_in )
{
    return ctx->write_f( ctx, reg, &data_in, 1 );
}

err_t pressure21_read_register ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return ctx->read_f( ctx, reg, data_out, 1 );
}

err_t pressure21_check_communication ( pressure21_t *ctx )
{
    uint8_t chip_id;
    if ( PRESSURE21_OK == pressure21_read_register ( ctx, PRESSURE21_REG_CHIP_ID, &chip_id ) )
    {
        if ( PRESSURE21_CHIP_ID == chip_id )
        {
            return PRESSURE21_OK;
        }
    }
    return PRESSURE21_ERROR;
}

uint8_t pressure21_get_int_pin ( pressure21_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t pressure21_get_sensor_data ( pressure21_t *ctx, float *pressure, float *temperature )
{
    uint8_t data_buf[ 6 ] = { 0 };
    if ( PRESSURE21_OK == pressure21_generic_read ( ctx, PRESSURE21_REG_TEMP_DATA_XLSB, data_buf, 6 ) )
    {
        int32_t raw_data = ( int32_t ) ( ( ( int32_t ) data_buf[ 5 ] << 24 ) | 
                                         ( ( int32_t ) data_buf[ 4 ] << 16 ) |
                                         ( ( int32_t ) data_buf[ 3 ] << 8 ) ) >> 8;
        *pressure = raw_data / PRESSURE21_PRESS_RESOLUTION;
        
        raw_data = ( int32_t ) ( ( ( int32_t ) data_buf[ 2 ] << 24 ) | 
                                 ( ( int32_t ) data_buf[ 1 ] << 16 ) |
                                 ( ( int32_t ) data_buf[ 0 ] << 8 ) ) >> 8;
        *temperature = raw_data / PRESSURE21_TEMP_RESOLUTION;
        return PRESSURE21_OK;
    }
    return PRESSURE21_ERROR;
}

static err_t pressure21_i2c_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

static err_t pressure21_i2c_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

static err_t pressure21_spi_write ( pressure21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    err_t error_flag = PRESSURE21_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ ) 
    {
        data_buf[ 0 ] = ( reg + cnt ) & ( ~SPI_READ_MASK );
        data_buf[ 1 ] = data_in[ cnt ];
        error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

static err_t pressure21_spi_read ( pressure21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_adr = reg | SPI_READ_MASK;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg_adr, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------ END
