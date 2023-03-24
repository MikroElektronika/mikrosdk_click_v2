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
 * @file audioamp11.c
 * @brief AudioAMP 11 Click Driver.
 */

#include "audioamp11.h"

void audioamp11_cfg_setup ( audioamp11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = AUDIOAMP11_DEVICE_ADDRESS;
}

err_t audioamp11_init ( audioamp11_t *ctx, audioamp11_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t audioamp11_default_cfg ( audioamp11_t *ctx ) 
{
    audioamp11_enable_device( ctx );
    return audioamp11_set_output_volume_level( ctx, AUDIOAMP11_VOLUME_LEVEL_0 );
}

err_t audioamp11_generic_write ( audioamp11_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t audioamp11_generic_read ( audioamp11_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void audioamp11_enable_device ( audioamp11_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void audioamp11_disable_device ( audioamp11_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t audioamp11_check_gain ( audioamp11_t *ctx, uint8_t *gain ) 
{
    return audioamp11_generic_read( ctx, AUDIOAMP11_REG_REGGAIN, gain );
}

err_t audioamp11_get_output_volume_level ( audioamp11_t *ctx, uint8_t *vol_ctrl ) 
{
    return audioamp11_generic_read( ctx, AUDIOAMP11_REG_VOLCTRL, vol_ctrl );
}

err_t audioamp11_set_output_volume_level ( audioamp11_t *ctx, uint8_t vol_ctrl ) 
{
    err_t err_flag;
    if ( vol_ctrl > AUDIOAMP11_VOLUME_MUTE )
    {
        err_flag = AUDIOAMP11_ERROR;
    }
    else
    {
        err_flag = audioamp11_generic_write( ctx, AUDIOAMP11_REG_VOLCTRL, vol_ctrl );
    }
    return err_flag;
}


// ------------------------------------------------------------------------- END
