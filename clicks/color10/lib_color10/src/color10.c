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

#include "color10.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define COLOR10_MIN_ORANGE_VAL                              0.089
#define COLOR10_MAX_ORANGE_VAL                              0.154

#define COLOR10_MIN_RED_VAL                                 0.05
#define COLOR10_MAX_RED_VAL                                 0.09

#define COLOR10_MIN_PINK_VAL                                0.920
#define COLOR10_MAX_PINK_VAL                                0.98

#define COLOR10_MIN_PURPLE_VAL                              0.6201
#define COLOR10_MAX_PURPLE_VAL                              0.919

#define COLOR10_MIN_BLUE_VAL                                0.521
#define COLOR10_MAX_BLUE_VAL                                0.6200

#define COLOR10_MIN_CYAN_VAL                                0.430
#define COLOR10_MAX_CYAN_VAL                                0.520

#define COLOR10_MIN_GREEN_VAL                               0.300
#define COLOR10_MAX_GREEN_VAL                               0.429

#define COLOR10_MIN_YELLOW_VAL                              0.155
#define COLOR10_MAX_YELLOW_VAL                              0.299

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static float drv_max_color ( float color_a, float color_b );
static float drv_min_color ( float color_a, float color_b );
static float drv_rgb_to_hsl ( float red, float green, float blue ) ;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void color10_cfg_setup ( color10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR10_SLAVE_ADDR;
}

COLOR10_RETVAL color10_init ( color10_t *ctx, color10_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR10_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return COLOR10_OK;
}

void color10_generic_write ( color10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

uint16_t color10_generic_read ( color10_t *ctx, uint8_t cmd_addr )
{
    uint8_t rx_buf[ 2 ];
    uint16_t temp_data;

    i2c_master_write_then_read( &ctx->i2c, &cmd_addr, 1, rx_buf, 2 );

    temp_data = rx_buf[ 1 ];
    temp_data = ( temp_data << 8 );
    temp_data = temp_data | rx_buf[ 0 ];
   
    return temp_data;
}

void color10_config ( color10_t *ctx, uint16_t cfg_data )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = COLOR10_CMD_REG_CFG;
    tx_buf[ 1 ] = cfg_data;
    tx_buf[ 2 ] = ( cfg_data >> 8 );

    i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

uint8_t color10_get_id ( color10_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint8_t tx_tmp;

    tx_tmp = COLOR10_CMD_REG_ID;

    i2c_master_write_then_read( &ctx->i2c, &tx_tmp, 1, rx_buf, 2 );

    return rx_buf[ 0 ];
}

float color10_read_color_ratio ( color10_t *ctx, uint8_t color_cmd_reg )
{
    uint16_t color_data;
    uint16_t clear_data;
    float color_ratio;

    color_data = color10_generic_read( ctx, color_cmd_reg );
    clear_data = color10_generic_read( ctx, COLOR10_CMD_REG_C );

    color_ratio = ( ( float ) color_data / ( float ) clear_data );

    return color_ratio;
}

float color10_get_color_value ( color10_t *ctx )
{
    float red_ratio;
    float green_ratio;
    float blue_ratio;

    float color_data;
    float sum_color;
    uint8_t cnt;

   for ( cnt = 0; cnt < 16; cnt++ )
    {
        red_ratio = color10_read_color_ratio( ctx, COLOR10_CMD_REG_R );
        green_ratio = color10_read_color_ratio( ctx, COLOR10_CMD_REG_G );
        blue_ratio = color10_read_color_ratio( ctx, COLOR10_CMD_REG_B );
    
        color_data = drv_rgb_to_hsl( red_ratio, green_ratio, blue_ratio );
        sum_color = sum_color + color_data;
    }

    sum_color = sum_color / 16.0;

    return sum_color;
}

uint8_t color10_get_color ( float color_value )
{
    if ( ( color_value >= COLOR10_MIN_ORANGE_VAL ) && ( color_value <= COLOR10_MAX_ORANGE_VAL ) )
     {
         return COLOR10_COLOR_ORANGE;
     }
     else if ( ( color_value >= COLOR10_MIN_RED_VAL ) && ( color_value <= COLOR10_MAX_RED_VAL ) )
     {
         return COLOR10_COLOR_RED;
     }
     else if ( ( color_value >= COLOR10_MIN_PINK_VAL ) && ( color_value <= COLOR10_MAX_PINK_VAL ) )
     {
         return COLOR10_COLOR_PINK;
     }
     else if ( ( color_value >= COLOR10_MIN_PURPLE_VAL ) && ( color_value <= COLOR10_MAX_PURPLE_VAL ) )
     {
         return COLOR10_COLOR_PURPLE;
     }
     else if ( ( color_value >= COLOR10_MIN_BLUE_VAL ) && ( color_value <= COLOR10_MAX_BLUE_VAL ) )
     {
         return COLOR10_COLOR_BLUE;
     }
     else if ( ( color_value >= COLOR10_MIN_CYAN_VAL ) && ( color_value < COLOR10_MAX_CYAN_VAL ) )
     {
         return COLOR10_COLOR_CYAN;
     }
     else if ( ( color_value >= COLOR10_MIN_GREEN_VAL ) && ( color_value <= COLOR10_MAX_GREEN_VAL ) )
     {
         return COLOR10_COLOR_GREEN;
     }
     else if ( ( color_value >= COLOR10_MIN_YELLOW_VAL ) && ( color_value <= COLOR10_MAX_YELLOW_VAL ) )
     {
         return COLOR10_COLOR_YELLOW;
     }

     return COLOR10_COLOR_OTHER;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float drv_max_color ( float color_a, float color_b )
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

static float drv_min_color ( float color_a, float color_b )
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

static float drv_rgb_to_hsl ( float red, float green, float blue )
{
    float fmax;
    float fmin;
    float hue_value;
    float saturation_value;
    float luminance_value;

    fmax = drv_max_color( drv_max_color( red, green ), blue );
    fmin = drv_min_color( drv_min_color( red, green ), blue );

    luminance_value = fmax;
    
    if (fmax > 0)
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

