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
 * @file mux5.c
 * @brief MUX 5 Click Driver.
 */

#include "mux5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void mux5_cfg_setup ( mux5_cfg_t *cfg ) 
{
    cfg->scl   = HAL_PIN_NC;
    cfg->sda   = HAL_PIN_NC;
    cfg->sck   = HAL_PIN_NC;
    cfg->miso  = HAL_PIN_NC;
    cfg->mosi  = HAL_PIN_NC;
    cfg->cs    = HAL_PIN_NC;
    cfg->com_b = HAL_PIN_NC;
    cfg->sd    = HAL_PIN_NC;
    cfg->com_a = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = MUX5_DEVICE_ADDRESS_0;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t mux5_init ( mux5_t *ctx, mux5_cfg_t *cfg ) 
{
#if ( MUX5_DRIVER_SEL == MUX5_SPI_DRIVER )
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
#else
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
#endif
        
    digital_out_init( &ctx->sd, cfg->sd );

    digital_in_init( &ctx->com_b, cfg->com_b );
    digital_in_init( &ctx->com_a, cfg->com_a );

    return MUX5_OK;
}

err_t mux5_default_cfg ( mux5_t *ctx ) 
{
    err_t error_flag = MUX5_OK;
    mux5_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= mux5_set_channels_state ( ctx, MUX5_CHANNEL_ALL, MUX5_CHANNEL_STATE_HIGH_Z );
    return error_flag;
}

#if ( MUX5_DRIVER_SEL == MUX5_I2C_DRIVER )
err_t mux5_i2c_write_register ( mux5_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t mux5_i2c_read_register ( mux5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}
#endif

err_t mux5_set_channels_state ( mux5_t *ctx, uint16_t ch_mask, uint8_t ch_state )
{
    if ( ch_state > MUX5_CHANNEL_STATE_COM_AB )
    {
        return MUX5_ERROR;
    }
    switch ( ch_state )
    {
        case MUX5_CHANNEL_STATE_HIGH_Z:
        {
            ctx->ch_a &= ~ch_mask;
            ctx->ch_b &= ~ch_mask;
            break;
        }
        case MUX5_CHANNEL_STATE_COM_A:
        {
            ctx->ch_a |= ch_mask;
            ctx->ch_b &= ~ch_mask;
            break;
        }
        case MUX5_CHANNEL_STATE_COM_B:
        {
            ctx->ch_a &= ~ch_mask;
            ctx->ch_b |= ch_mask;
            break;
        }
        case MUX5_CHANNEL_STATE_COM_AB:
        {
            ctx->ch_a |= ch_mask;
            ctx->ch_b |= ch_mask;
            break;
        }
    }
#if ( MUX5_DRIVER_SEL == MUX5_I2C_DRIVER )
    err_t error_flag = MUX5_OK;
    error_flag |= mux5_i2c_write_register ( ctx, MUX5_REG_DIR0, ( uint8_t ) ( ctx->ch_a & 0xFF ) );
    error_flag |= mux5_i2c_write_register ( ctx, MUX5_REG_DIR1, ( uint8_t ) ( ( ctx->ch_a >> 8 ) & 0xFF ) );
    error_flag |= mux5_i2c_write_register ( ctx, MUX5_REG_DIR2, ( uint8_t ) ( ctx->ch_b & 0xFF ) );
    error_flag |= mux5_i2c_write_register ( ctx, MUX5_REG_DIR3, ( uint8_t ) ( ( ctx->ch_b >> 8 ) & 0xFF ) );
    return error_flag;
#else
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( ctx->ch_b >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ctx->ch_b & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( ctx->ch_a >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ctx->ch_a & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
#endif
}

void mux5_enable_device ( mux5_t *ctx )
{
    digital_out_high ( &ctx->sd );
}

void mux5_disable_device ( mux5_t *ctx )
{
    digital_out_low ( &ctx->sd );
}

uint8_t mux5_get_com_a_pin ( mux5_t *ctx )
{
    return digital_in_read ( &ctx->com_a );
}

uint8_t mux5_get_com_b_pin ( mux5_t *ctx )
{
    return digital_in_read ( &ctx->com_b );
}

// ------------------------------------------------------------------------ END
