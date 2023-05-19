/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "evc.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void evc_cfg_setup ( evc_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EVC_DEVICE_SLAVE_ADDRESS_11;
    cfg->mute_cfg_flag = 0;
    cfg->play_cfg_flag = 0;
    cfg->cfg_volume = 0;
    cfg->cfg_channel = 1;
    cfg->test_cfg_flag = 0;
}

EVC_RETVAL evc_init ( evc_t *ctx, evc_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->mute_flag = cfg->mute_cfg_flag;
    ctx->play_flag = cfg->play_cfg_flag;
    ctx->volume = cfg->cfg_volume;
    ctx->channel = cfg->cfg_channel;
    ctx->test_flag = cfg->test_cfg_flag;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EVC_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return EVC_OK;
}

void evc_default_cfg ( evc_t *ctx )
{
    evc_clear( ctx );
    
    evc_set_volume_part( ctx, EVC_CHANNEL_1, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_CHANNEL_2, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_CHANNEL_3, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_CHANNEL_4, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_CHANNEL_5, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_CHANNEL_6, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    evc_set_volume_part( ctx, EVC_ALL_CHANNEL, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );
    
    evc_mute( ctx, EVC_ALL_CHANNEL_UNMUTE );

    evc_set_volume_part( ctx, EVC_CHANNEL_1, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );   
    evc_set_volume_part( ctx, EVC_CHANNEL_2, EVC_SET_VOLUME_0dB, EVC_SET_VOLUME_0dB );  
}

void evc_generic_write ( evc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );   
}

void evc_generic_read ( evc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void evc_set_volume_part ( evc_t *ctx, uint8_t channel, uint8_t volume1, uint8_t volume2 )
{
    uint8_t vol_1;
    uint8_t vol_2;

    vol_1 = channel | volume1;
    vol_2 = channel | volume2;
    
    evc_generic_write( ctx, vol_1, &vol_2, 1 );
}

void evc_set_volume_full ( evc_t *ctx, uint8_t channel, int8_t volume )
{
    uint8_t volume1;
    uint8_t volume2;

    volume2 = ( -volume ) % 10;
    volume1 = ( -volume ) / 10;

    volume2 = channel | ( 0x10 | volume2 );
    volume1 = channel | volume1;

    evc_generic_write( ctx, volume2, &volume1, 1 );
}

void evc_clear ( evc_t *ctx )
{
    uint8_t clear;

    evc_generic_write( ctx, EVC_CLEAR_ALL, &clear, 0 );
}

void evc_mute ( evc_t *ctx, uint8_t mute )
{
    uint8_t mute_reg;

    mute_reg = mute;

    evc_generic_write( ctx, mute_reg, &mute_reg, 0 );
}

// ------------------------------------------------------------------------- END

