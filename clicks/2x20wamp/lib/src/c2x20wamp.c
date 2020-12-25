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

#include "c2x20wamp.h"

void c2x20wamp_cfg_setup ( c2x20wamp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins

    cfg->shdn = HAL_PIN_NC;
    cfg->mute = HAL_PIN_NC;
    cfg->addr1 = HAL_PIN_NC;
    cfg->addr2 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C2X20WAMP_I2C_ADDRESS | C2X20WAMP_ADDRESS_1 | C2X20WAMP_ADDRESS_2;
}

C2X20WAMP_RETVAL c2x20wamp_init ( c2x20wamp_t *ctx, c2x20wamp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C2X20WAMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->shdn, cfg->shdn );
    digital_out_init( &ctx->mute, cfg->mute );

    digital_out_init( &ctx->addr1, cfg->addr1 );
    digital_out_init( &ctx->addr2, cfg->addr2 );

    digital_out_high( &ctx->addr1 );
    digital_out_high( &ctx->addr2 );

    return C2X20WAMP_OK;
}

void c2x20wamp_generic_write ( c2x20wamp_t *ctx, uint8_t data_buf )
{
    uint8_t send_data = data_buf;

    i2c_master_write( &ctx->i2c, &send_data, 1 ); 
}

void c2x20wamp_mode_play ( c2x20wamp_t *ctx )
{
    digital_out_low( &ctx->mute );
}

void c2x20wamp_mode_mute ( c2x20wamp_t *ctx )
{
    digital_out_high( &ctx->mute );
}

void c2x20wamp_disable ( c2x20wamp_t *ctx )
{
    digital_out_low( &ctx->shdn );
}

void c2x20wamp_enable ( c2x20wamp_t *ctx )
{
    digital_out_high( &ctx->shdn );
}

void c2x20wamp_set_volume ( c2x20wamp_t *ctx, uint8_t volume )
{
    c2x20wamp_generic_write( ctx, volume & C2X20WAMP_6_BIT_VALUE );
}

void c2x20wamp_volume_up ( c2x20wamp_t *ctx )
{
    c2x20wamp_generic_write( ctx, C2X20WAMP_CMD_VOLUME_UP );
}

void c2x20wamp_volume_down ( c2x20wamp_t *ctx )
{
    c2x20wamp_generic_write( ctx, C2X20WAMP_CMD_VOLUME_DOWN );
}

void c2x20wamp_filterless_modulation ( c2x20wamp_t *ctx )
{
    c2x20wamp_generic_write( ctx, C2X20WAMP_CMD_FILTERLESS_MODULATION );
}


void c2x20wamp_classic_pwm_modulation ( c2x20wamp_t *ctx )
{
    c2x20wamp_generic_write( ctx, C2X20WAMP_CMD_CLASSIC_PWM_MODULATION );
}

// ------------------------------------------------------------------------ END
