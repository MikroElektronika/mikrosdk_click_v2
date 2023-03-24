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

#include "leddriver3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void leddriver3_cfg_setup ( leddriver3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = 0x38;
}

LEDDRIVER3_RETVAL leddriver3_init ( leddriver3_t *ctx, leddriver3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LEDDRIVER3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return LEDDRIVER3_OK;
}

void leddriver3_generic_write ( leddriver3_t *ctx, uint8_t reg )
{
    i2c_master_write( &ctx->i2c, &reg, 1 );
}

void leddriver3_generic_read ( leddriver3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void leddriver3_set_intensity ( leddriver3_t *ctx, uint8_t intensity )
{
    leddriver3_generic_write( ctx, intensity );
}

void leddriver3_set_rgb_color ( leddriver3_t *ctx, leddriver3_rgb_t *rgb )
{
    uint8_t write_reg[ 3 ];

    if ( rgb->red < 0x40 || rgb->red > 0x5F )
    {
        write_reg[ 0 ] = 0x40;
    }
    else
    {
        write_reg[ 0 ] = rgb->red;
    }

    if ( rgb->green < 0x60 || rgb->green > 0x7F )
    {
        write_reg[ 1 ] = 0x60;
    }
    else
    {
        write_reg[ 1 ] = rgb->green;
    }

    if ( rgb-> blue < 0x80 || rgb->blue > 0x9F )
    {
        write_reg[ 2 ] = 0x80;
    }
    else
    {
        write_reg[ 2 ] = rgb->blue;
    }

    i2c_master_write( &ctx->i2c, &write_reg[0], 1 );
    i2c_master_write( &ctx->i2c, &write_reg[1], 1 );
    i2c_master_write( &ctx->i2c, &write_reg[2], 1 );
}

void leddriver3_set_color ( leddriver3_t *ctx, uint32_t color )
{
    uint8_t write_reg[ 3 ];

    write_reg[ 0 ] = color;
    write_reg[ 1 ] = color >> 8;
    write_reg[ 2 ] = color >> 16;

    i2c_master_write( &ctx->i2c, &write_reg[0], 1 );
    i2c_master_write( &ctx->i2c, &write_reg[1], 1 );
    i2c_master_write( &ctx->i2c, &write_reg[2], 1 );
}

void leddriver3_shut_down ( leddriver3_t *ctx )
{
    uint8_t write_reg[ 1 ];

    write_reg[ 0 ] = 0x00;

    leddriver3_generic_write( ctx, write_reg[0] );
}

void leddriver3_set_timer ( leddriver3_t *ctx, uint8_t time )
{
    leddriver3_generic_write( ctx, time );
}

// ------------------------------------------------------------------------- END

