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

#include "rgbdriver.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rgbdriver_cfg_setup ( rgbdriver_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x38;
}

RGBDRIVER_RETVAL rgbdriver_init ( rgbdriver_t *ctx, rgbdriver_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RGBDRIVER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return RGBDRIVER_OK;
}

RGBDRIVER_RETVAL rgbdriver_default_cfg ( rgbdriver_t *ctx )
{
    uint8_t write_reg[ 3 ];
    
    write_reg[ 0 ] = 0x3F;
    
    rgbdriver_shut_down( ctx );
    rgbdriver_generic_write( ctx, write_reg, 1 );
    
    return RGBDRIVER_OK;
}

void rgbdriver_generic_write ( rgbdriver_t *ctx, uint8_t *data_buf, uint8_t len )
{
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        i2c_master_write( &ctx->i2c, &data_buf[ cnt ], 1 );
        Delay_50us( );
    }
}

void rgbdriver_set_rgb_color ( rgbdriver_t *ctx, uint8_t red, uint8_t green, uint8_t blue )
{
    uint8_t write_reg[ 3 ];

    if ( blue < 0x40 || blue > 0x5F )
    {
        write_reg[ 0 ] = 0x40;
    }
    else
    {
        write_reg[ 0 ] = blue;
    }

    if ( red < 0x60 || red > 0x7F )
    {
        write_reg[ 1 ] = 0x60;
    }
    else
    {
        write_reg[ 1 ] = red;
    }

    if ( green < 0x80 || green > 0x9F )
    {
        write_reg[ 2 ] = 0x80;
    }
    else
    {
        write_reg[ 2 ] = green;
    }

    rgbdriver_generic_write( ctx, write_reg, 3 );
}

void rgbdriver_set_color ( rgbdriver_t *ctx, uint32_t color )
{
    uint8_t write_reg[ 3 ];
    write_reg[ 0 ] = ( uint8_t ) ( color & 0xFF );
    write_reg[ 1 ] = ( uint8_t ) ( ( color >> 8 ) & 0xFF );
    write_reg[ 2 ] = ( uint8_t ) ( ( color >> 16 ) & 0xFF );

    rgbdriver_generic_write( ctx, write_reg, 3 );
}

void rgbdriver_shut_down ( rgbdriver_t *ctx )
{
    uint8_t write_reg[ 1 ];
    write_reg[ 0 ] = RGBDRIVER_COLOR_OFF;

    i2c_master_write( &ctx->i2c, write_reg, 1 );
}

// ------------------------------------------------------------------------- END

