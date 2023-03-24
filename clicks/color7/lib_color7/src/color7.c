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

#include "color7.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// Color FLAG

#define ORANGE_COLOR_FLAG 1
#define RED_COLOR_FLAG    2
#define PINK_COLOR_FLAG   3
#define PURPLE_COLOR_FLAG 4
#define BLUE_COLOR_FLAG   5
#define CYAN_COLOR_FLAG   6
#define GREEN_COLOR_FLAG  7
#define YELLOW_COLOR_FLAG 8
#define NON_COLOR_FLAG    0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float max_color ( float color_a, float color_b );
static float min_color ( float color_a, float color_b );
static float rgb_to_hsl ( float red, float green, float blue );

static void color7_write_data_u8 ( color7_t *ctx, uint8_t reg, uint8_t _data );
static uint16_t color7_read_data_u16 ( color7_t *ctx, uint8_t reg );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color7_cfg_setup ( color7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x29;
}

COLOR7_RETVAL color7_init ( color7_t *ctx, color7_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR7_OK;
}

void color7_default_cfg ( color7_t *ctx )
{
    // Click default configuration

    color7_write_data_u8( ctx, COLOR7_REG_ENABLE, COLOR7_ENABLE_RGBC_INTERRUPT | 
                                                  COLOR7_ENABLE_WAIT |
                                                  COLOR7_ENABLE_RGBC | COLOR7_POWER_ON );

    color7_write_data_u8( ctx, COLOR7_REG_CONTROL, COLOR7_CTRL_GAIN_x16 );
    color7_write_data_u8( ctx, COLOR7_REG_RGBC_TIME, COLOR7_RGBC_TIME_700ms );
}

void color7_generic_write ( color7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void color7_generic_read ( color7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float color7_read_color_ratio ( color7_t *ctx, uint8_t color )
{
    uint16_t color_data;
    uint16_t clear_data;
    float color_ratio;

    color_data = color7_read_data_u16( ctx, color );
    clear_data = color7_read_data_u16( ctx, COLOR7_COLOR_DATA_CLEAR );

    color_ratio = ( ( float ) color_data / ( float ) clear_data );

    return color_ratio;
}

float color7_get_color_value ( color7_t *ctx )
{
    float red_ratio;
    float green_ratio;
    float blue_ratio;

    float color_data;
    float sum_color;
    uint8_t counter;

    for ( counter = 0; counter < 16; counter++ )
    {
        red_ratio = color7_read_color_ratio( ctx, COLOR7_COLOR_DATA_RED );
        green_ratio = color7_read_color_ratio( ctx, COLOR7_COLOR_DATA_GREEN );
        blue_ratio = color7_read_color_ratio( ctx, COLOR7_COLOR_DATA_BLUE );

        color_data = rgb_to_hsl( red_ratio, green_ratio, blue_ratio );
        sum_color = sum_color + color_data;
    }
    sum_color = sum_color / 16.0;

    return sum_color;
}

uint8_t color7_get_color( color7_t *ctx )
{
    float color;

    color = color7_get_color_value( ctx );

     if ( ( color >= 0.920 ) && ( color <= 0.9749 ) )
     {
         return PINK_COLOR_FLAG;
     }
     else if ( ( color >= 0.6201 ) && ( color <= 0.919 ) )
     {
         return PURPLE_COLOR_FLAG;
     }
     else if ( ( color >= 0.521 ) && ( color <= 0.6200 ) )
     {
         return BLUE_COLOR_FLAG;
     }
     else if ( ( color >= 0.430 ) && ( color < 0.520 ) )
     {
         return CYAN_COLOR_FLAG;
     }
     else if ( ( color >= 0.300) && ( color <= 0.429 ) )
     {
         return GREEN_COLOR_FLAG;
     }
     else if ( ( color >= 0.205 ) && ( color <= 0.299 ) )
     {
         return YELLOW_COLOR_FLAG;
     }
     else if ( ( color >= 0.019 ) && ( color <= 0.200 ) )
     {
         return ORANGE_COLOR_FLAG;
     }
     else if ( ( color >= 0.0005 ) && ( color <= 0.018 ) )
     {
         return RED_COLOR_FLAG;
     }
    return NON_COLOR_FLAG;
}

uint8_t color7_get_interrupt_state ( color7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void color7_write_data_u8 ( color7_t *ctx, uint8_t reg, uint8_t _data )
{
    color7_generic_write( ctx,  reg | COLOR7_CMD_SELECT, &_data, 1 );
}

static uint16_t color7_read_data_u16 ( color7_t *ctx, uint8_t reg )
{
    uint8_t rx_data[ 2 ];
    volatile uint16_t out_data;

    color7_generic_read( ctx, reg | COLOR7_CMD_SELECT, rx_data, 2 );

    out_data = rx_data[ 1 ];
    out_data = out_data << 8;
    out_data = out_data | rx_data[ 0 ];

    return out_data;
}

static float max_color ( float color_a, float color_b )
{
    if ( color_a > color_b )
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
    if ( color_a < color_b )
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
    float f_max;
    float f_min;
    float hue_val;
    float saturation_val;
    float luminance_val;

    f_max = max_color( max_color ( red, green ), blue );
    f_min = min_color ( min_color ( red, green ), blue );

    luminance_val = f_max;

    if ( f_max > 0 )
    {
        saturation_val = ( f_max - f_min ) / f_max;
    }
    else
    {
        saturation_val = 0;
    }

    if ( saturation_val == 0 )
    {
        hue_val = 0;
    }
    else
    {
        if ( f_max == red )
        {
             hue_val = ( green - blue ) / ( f_max - f_min );
        }
        else if ( f_max == green )
        {
             hue_val = 2 + ( blue - red ) / ( f_max - f_min );
        }
        else
        {
             hue_val = 4 + ( red - green ) / ( f_max - f_min );
        }
        hue_val = hue_val / 6;

        if ( hue_val < 0 )
        {
             hue_val = hue_val + 1;
        }
    }
    return hue_val;
}

// ------------------------------------------------------------------------- END

