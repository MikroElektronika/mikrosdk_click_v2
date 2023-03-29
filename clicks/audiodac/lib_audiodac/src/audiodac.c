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
 * @file audiodac.c
 * @brief Audio DAC Click Driver.
 */

#include "audiodac.h"

void audiodac_cfg_setup ( audiodac_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->mute = HAL_PIN_NC;
    cfg->gpio4 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AUDIODAC_DEVICE_ADDRESS;
}

err_t audiodac_init ( audiodac_t *ctx, audiodac_cfg_t *cfg ) 
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

    digital_out_init( &ctx->mute, cfg->mute );

    digital_in_init( &ctx->gpio4, cfg->gpio4 );

    return I2C_MASTER_SUCCESS;
}

err_t audiodac_default_cfg ( audiodac_t *ctx ) 
{
    err_t error_flag = AUDIODAC_OK;
    audiodac_mute_output ( ctx );
    error_flag |= audiodac_select_page ( ctx, AUDIODAC_PAGE_0 );
    error_flag |= audiodac_write_register ( ctx, AUDIODAC_REG_P0_GPIO_EN, AUDIODAC_GPIO4_OUT_EN );
    error_flag |= audiodac_write_register ( ctx, AUDIODAC_REG_P0_GPIO4_OUT_SEL, AUDIODAC_GPIO_OUT_SEL_AUTO_MUTE_LR );
    error_flag |= audiodac_volume_control ( ctx, AUDIODAC_CHANNEL_BOTH, AUDIODAC_VOLUME_DEFAULT );
    audiodac_unmute_output ( ctx );
    return error_flag;
}

err_t audiodac_generic_write ( audiodac_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t audiodac_generic_read ( audiodac_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t audiodac_write_register ( audiodac_t *ctx, uint8_t reg, uint8_t data_in )
{
    return audiodac_generic_write( ctx, reg & ( ~AUDIODAC_AUTO_INCREMENT_ENABLE ), &data_in, 1 );
}

err_t audiodac_read_register ( audiodac_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return audiodac_generic_read( ctx, reg & ( ~AUDIODAC_AUTO_INCREMENT_ENABLE ), data_out, 1 );
}

void audiodac_mute_output ( audiodac_t *ctx )
{
    digital_out_low ( &ctx->mute );
}

void audiodac_unmute_output ( audiodac_t *ctx )
{
    digital_out_high ( &ctx->mute );
}

uint8_t audiodac_get_gpio4_pin ( audiodac_t *ctx )
{
    return digital_in_read ( &ctx->gpio4 );
}

err_t audiodac_select_page ( audiodac_t *ctx, uint8_t page_num )
{
    return audiodac_write_register ( ctx, AUDIODAC_REG_P0_PAGE_SEL, page_num );
}

err_t audiodac_volume_control ( audiodac_t *ctx, uint8_t channel, uint8_t volume )
{
    err_t error_flag = AUDIODAC_OK;
    uint8_t raw_vol;
    if ( ( channel > AUDIODAC_CHANNEL_RIGHT ) || ( volume > AUDIODAC_VOLUME_MAX ) )
    {
        return AUDIODAC_ERROR;
    }
    if ( AUDIODAC_VOLUME_MUTE == volume )
    {
        raw_vol = AUDIODAC_DIG_VOLUME_MUTE;
    }
    else
    {
        raw_vol = AUDIODAC_VOLUME_MAX - volume;
    }
    if ( ( AUDIODAC_CHANNEL_BOTH == channel ) || ( AUDIODAC_CHANNEL_LEFT == channel ) )
    {
        error_flag |= audiodac_write_register ( ctx, AUDIODAC_REG_P0_DIG_VOLUME_LEFT, raw_vol );
    }
    if ( ( AUDIODAC_CHANNEL_BOTH == channel ) || ( AUDIODAC_CHANNEL_RIGHT == channel ) )
    {
        error_flag |= audiodac_write_register ( ctx, AUDIODAC_REG_P0_DIG_VOLUME_RIGHT, raw_vol );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
