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

#include "color2.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float max_color( float color_a, float color_b );

static float min_color( float color_a, float color_b );

static float rgb_to_hsl( float red, float green, float blue );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color2_cfg_setup ( color2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR2_I2C_ADDR;
}

COLOR2_RETVAL color2_init ( color2_t *ctx, color2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR2_OK;

}

void color2_default_cfg ( color2_t *ctx )
{
    color2_write_data ( ctx, COLOR2_CONFIG_1, ( COLOR2_CFG1_MODE_RGB | COLOR2_CFG1_10KLUX ) );
    color2_write_data ( ctx, COLOR2_CONFIG_2, COLOR2_CFG2_IR_ADJUST_HIGH );
    color2_write_data ( ctx, COLOR2_CONFIG_3, COLOR2_CFG_DEFAULT ); 
}

void color2_write_data ( color2_t *ctx, uint8_t address, uint8_t write_command )
{
    uint8_t buffer[ 2 ];
    uint8_t cnt;
    
    buffer[ 0 ] = address;
    buffer[ 1 ] = write_command;
    
    i2c_master_write( &ctx->i2c, buffer, 2 );   
}

uint8_t color2_read_data ( color2_t *ctx, uint8_t address )
{
    uint8_t rx_buf[ 1 ];

    //i2c_master_write_then_read( &ctx->i2c, &address, 1, rx_buf, 1 );
    i2c_master_write( &ctx->i2c, &address, 1 );
    i2c_master_read( &ctx->i2c, rx_buf, 1 );

    return rx_buf[ 0 ];
}

uint8_t color2_reset ( color2_t *ctx )
{
    uint8_t ret;
    color2_write_data( ctx, COLOR2_DEVICE_ID, 0x46 );

    ret = color2_read_data( ctx, COLOR2_CONFIG_1 );
    ret |= color2_read_data( ctx, COLOR2_CONFIG_2 );
    ret |= color2_read_data( ctx, COLOR2_CONFIG_3 );
    ret |= color2_read_data( ctx, COLOR2_STATUS );
  
    if ( ret != 0x00 )
    {
        return 0;
    }
  
    return 1;
}

uint8_t color2_init_advanced ( color2_t *ctx, uint8_t config1, uint8_t config2, uint8_t config3)
{
    uint8_t ret;
    
    if ( color2_read_data( ctx, COLOR2_DEVICE_ID ) != 0x7D )
    {
        return 0;
    }

    color2_write_data( ctx, COLOR2_CONFIG_1, config1 );
    
    color2_write_data( ctx, COLOR2_CONFIG_2, config2 );
    
    color2_write_data( ctx, COLOR2_CONFIG_3, config3 );
    
    ret = color2_read_data( ctx, COLOR2_CONFIG_1 );
    
    if ( ret != config1 )
    {
        return 0;
    }
  
    ret = color2_read_data( ctx, COLOR2_CONFIG_2 );
    if ( ret != config2 )
    {
        return 0;
    }
  
    ret = color2_read_data( ctx, COLOR2_CONFIG_3 );
    if ( ret != config3 )
    {
        return 0;
    }
    
    return 1;
}

void color2_set_upper_threshold( color2_t *ctx, uint16_t upper_threshold )
{
    uint8_t buffer[2];

    buffer[ 0 ] = upper_threshold & 0xFF;
    buffer[ 1 ] = upper_threshold >> 8;
    
    color2_write_data( ctx, COLOR2_THRESHOLD_HL, buffer[ 0 ] );
    color2_write_data( ctx, COLOR2_THRESHOLD_HH, buffer[ 1 ] );
}

void color2_set_lower_hreshold( color2_t *ctx, uint16_t lower_threshold )
{
    uint8_t buffer[2];

    buffer[ 0 ] = lower_threshold & 0xFF;
    buffer[ 1 ] = lower_threshold >> 8;

    color2_write_data( ctx, COLOR2_THRESHOLD_LL, buffer[ 0 ] );
    color2_write_data( ctx, COLOR2_THRESHOLD_LH, buffer[ 1 ] );
}

uint16_t color2_read_upper_threshold( color2_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    result = 0x0000;

    buffer[ 0 ] = color2_read_data( ctx, COLOR2_THRESHOLD_HH );
    buffer[ 1 ] = color2_read_data( ctx, COLOR2_THRESHOLD_HL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

uint16_t color2_read_lower_threshold( color2_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    result = 0x0000;

    buffer[ 0 ] = color2_read_data( ctx, COLOR2_THRESHOLD_LH );
    buffer[ 1 ] = color2_read_data( ctx, COLOR2_THRESHOLD_LL );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

float color2_read_red( color2_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    result = 0x0000;

    buffer[ 0 ] = color2_read_data( ctx, COLOR2_RED_H );
    buffer[ 1 ] = color2_read_data( ctx, COLOR2_RED_L );


    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

float color2_read_green ( color2_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    result = 0x0000;

    buffer[ 0 ] = color2_read_data( ctx, COLOR2_GREEN_H );
    buffer[ 1 ] = color2_read_data( ctx, COLOR2_GREEN_L );


    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

float color2_read_blue ( color2_t *ctx )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    result = 0x0000;

    buffer[ 0 ] = color2_read_data( ctx, COLOR2_BLUE_H );
    buffer[ 1 ] = color2_read_data( ctx, COLOR2_BLUE_L );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

uint8_t color2_read_status ( color2_t *ctx )
{
    uint8_t result;

    result = color2_read_data( ctx, COLOR2_STATUS );

    return result;
}

float color2_get_color_value ( color2_t *ctx )
{
    float color_data;
    float sum_color;
    uint8_t counter;

    for ( counter = 0; counter < 16; counter++ )
    {
        color_data = rgb_to_hsl( color2_read_red( ctx ), color2_read_green( ctx ), color2_read_blue( ctx ) );
        sum_color = sum_color + color_data;
    }
    sum_color = sum_color / 16.0;

    return sum_color;
}

uint8_t color2_get_color ( float color_value )
{
     if( ( color_value >= 0.992 ) && ( color_value <= 0.999 ) )
     {
         return 1; 
     }
     else if ( ( color_value >= 0.9750 ) && ( color_value <= 0.9919 ) )
     {
         return 2; 
     }
     else if ( ( color_value >= 0.920 ) && ( color_value <= 0.9749 ) )
     {
         return 3; 
     }
     else if ( ( color_value >= 0.6201 ) && ( color_value <= 0.919 ) )
     {
         return 4; 
     }
     else if ( ( color_value >= 0.521 ) && ( color_value <= 0.6200 ) )
     {
         return 5; 
     }
     else if ( ( color_value >= 0.470 ) && ( color_value < 0.520 ) )
     {
         return 6; 
     }
     else if ( ( color_value >= 0.210 ) && ( color_value <= 0.469 ) )
     {
         return 7; 
     }
     else if ( ( color_value >= 0.0650 ) && ( color_value <= 0.180 ) )
     {
         return 8; 
     }

     return 0; 
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

