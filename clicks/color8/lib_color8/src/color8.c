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

#include "color8.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float max_color ( float color_a, float color_b );

static float min_color ( float color_a, float color_b );

static float rgb_to_hsl ( float red, float green, float blue );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color8_cfg_setup ( color8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR8_DEF_SLAVE_ADDRESS_0;
}

COLOR8_RETVAL color8_init ( color8_t *ctx, color8_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR8_OK;

}


void color8_generic_write ( color8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void color8_generic_read ( color8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void color8_write_byte ( color8_t *ctx, uint8_t reg, uint8_t w_data )
{   
    color8_generic_write( ctx, reg, &w_data, 1 );
}

uint8_t color8_read_byte ( color8_t *ctx, uint8_t reg )
{
    uint8_t read_reg;
    
    color8_generic_read( ctx, reg, &read_reg, 1 );

    return read_reg;
}

uint8_t color8_get_interrupt ( color8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint16_t color8_read_data ( color8_t *ctx, uint8_t reg_data )
{
    uint16_t read_data;
    
    read_data = color8_read_byte( ctx, reg_data + 1 );
    read_data <<= 8;
    read_data |= color8_read_byte( ctx, reg_data );

    return read_data;
}

float color8_get_color_value ( color8_t *ctx )
{
    float red_ratio;
    float green_ratio;
    float blue_ratio;

    float color_data;
    float sum_color;
    uint8_t counter;

    for ( counter = 0; counter < 16; counter++ )
    {
        red_ratio = color8_read_data( ctx, COLOR8_REG_RED_DATA );
        green_ratio = color8_read_data( ctx, COLOR8_REG_GREEN_DATA );
        blue_ratio = color8_read_data( ctx, COLOR8_REG_BLUE_DATA );

        color_data = rgb_to_hsl( red_ratio, green_ratio, blue_ratio );
        sum_color = sum_color + color_data;
    }
    sum_color = sum_color / 16.0;

    return sum_color;
}

uint8_t color8_get_color ( color8_t *ctx, float color_value )
{
     if ( ( color_value >= 0.920 ) && ( color_value <= 0.9749 ) )
     {
         return PINK_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.6201 ) && ( color_value <= 0.919 ) )
     {
         return PURPLE_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.521 ) && ( color_value <= 0.6200 ) )
     {
         return BLUE_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.430 ) && ( color_value < 0.520 ) )
     {
         return CYAN_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.300 ) && ( color_value <= 0.429 ) )
     {
         return GREEN_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.205 ) && ( color_value <= 0.299 ) )
     {
         return YELLOW_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.019 ) && ( color_value <= 0.200 ) )
     {
         return ORANGE_COLOR_FLAG;
     }
     else if ( ( color_value >= 0.0005 ) && ( color_value <= 0.018 ) )
     {
         return RED_COLOR_FLAG;
     }
     return NON_COLOR_FLAG;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float max_color ( float color_a, float color_b )
{
    if( color_a > color_b )
    {
        return color_a;
    }
    else
    {
        return color_b;
    }
}

static float min_color ( float color_a, float color_b )
{
    if( color_a < color_b )
    {
        return color_a;
    }
    else
    {
        return color_b;
    }
}

static float rgb_to_hsl ( float red, float green, float blue )
{
    float fmax;
    float fmin;
    float hue_value;
    float saturation_value;
    float luminance_value;

    fmax = max_color( max_color( red, green ), blue );
    fmin = min_color( min_color( red, green ), blue );

    luminance_value = fmax;

    if ( fmax > 0 )
    {
        saturation_value = ( fmax - fmin ) / fmax;
    }
    else
    {
        saturation_value = 0;
    }

    if ( saturation_value == 0 )
    {
        hue_value = 0;
    }
    else
    {
        if ( fmax == red )
        {
            hue_value = ( green - blue ) / ( fmax - fmin );
        }
        else if ( fmax == green )
        {
            hue_value = 2 + ( blue - red ) / ( fmax - fmin );
        }
        else
        {
             hue_value = 4 + ( red - green ) / ( fmax - fmin );
        }
        hue_value = hue_value / 6;

        if ( hue_value < 0 )
        {
            hue_value = hue_value + 1;
        }
    }
    return hue_value;
}

// ------------------------------------------------------------------------- END

