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

/**
 * @brief Color 2 max float function.
 * @details This function returns the maximal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Maximal float number.
 * @note None.
 */
static float color2_max_float ( float x, float y, float z );

/**
 * @brief Color 2 min float function.
 * @details This function returns the minimal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Minimal float number.
 * @note None.
 */
static float color2_min_float ( float x, float y, float z );

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

err_t color2_init ( color2_t *ctx, color2_cfg_t *cfg )
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

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR2_OK;
}

err_t color2_default_cfg ( color2_t *ctx )
{
    err_t error_flag = COLOR2_OK;
    error_flag |= color2_init_advanced ( ctx, COLOR2_CFG1_MODE_RGB | COLOR2_CFG1_10KLUX, 
                                              COLOR2_CFG2_IR_ADJUST_HIGH, 
                                              COLOR2_CFG3_RGB_CONV_TO_INT_ENABLE );
    return error_flag;
}

err_t color2_generic_write ( color2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color2_generic_read ( color2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color2_write_reg ( color2_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t buffer[ 2 ] = { 0 };
    buffer[ 0 ] = reg;
    buffer[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, buffer, 2 );   
}

err_t color2_read_reg ( color2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t color2_get_int_pin ( color2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t color2_reset ( color2_t *ctx )
{
    err_t error_flag = color2_write_reg( ctx, COLOR2_DEVICE_ID, 0x46 );
    Delay_1sec ( );
    return error_flag;
}

err_t color2_init_advanced ( color2_t *ctx, uint8_t config1, uint8_t config2, uint8_t config3 )
{
    uint8_t reg_data = 0;
    err_t error_flag = COLOR2_OK;
    
    if ( ( COLOR2_OK != color2_read_reg( ctx, COLOR2_DEVICE_ID, &reg_data ) ) && 
         ( 0x7D != reg_data ) )
    {
        return COLOR2_ERROR;
    }

    error_flag |= color2_write_reg( ctx, COLOR2_CONFIG_1, config1 );
    
    error_flag |= color2_write_reg( ctx, COLOR2_CONFIG_2, config2 );
    
    error_flag |= color2_write_reg( ctx, COLOR2_CONFIG_3, config3 );
    
    error_flag |= color2_read_reg( ctx, COLOR2_CONFIG_1, &reg_data );
    
    if ( reg_data != config1 )
    {
        return COLOR2_ERROR;
    }
  
    error_flag |= color2_read_reg( ctx, COLOR2_CONFIG_2, &reg_data );
    
    if ( reg_data != config2 )
    {
        return COLOR2_ERROR;
    }
    
    error_flag |= color2_read_reg( ctx, COLOR2_CONFIG_3, &reg_data );
    
    if ( reg_data != config3 )
    {
        return COLOR2_ERROR;
    }
    
    return error_flag;
}

err_t color2_set_upper_threshold( color2_t *ctx, uint16_t upper_threshold )
{
    err_t error_flag = COLOR2_OK;
    uint8_t buffer[ 2 ] = { 0 };
    buffer[ 0 ] = upper_threshold & 0xFF;
    buffer[ 1 ] = upper_threshold >> 8;
    error_flag |= color2_generic_write ( ctx, COLOR2_THRESHOLD_HL, buffer, 2 );
    return error_flag;
}

err_t color2_set_lower_hreshold( color2_t *ctx, uint16_t lower_threshold )
{
    err_t error_flag = COLOR2_OK;
    uint8_t buffer[ 2 ] = { 0 };
    buffer[ 0 ] = lower_threshold & 0xFF;
    buffer[ 1 ] = lower_threshold >> 8;
    error_flag |= color2_generic_write ( ctx, COLOR2_THRESHOLD_LL, buffer, 2 );
    return error_flag;
}

err_t color2_read_upper_threshold ( color2_t *ctx, uint16_t *upper_threshold )
{
    err_t error_flag = COLOR2_OK;
    uint8_t buffer[ 2 ] = { 0 };
    error_flag |= color2_generic_read( ctx, COLOR2_THRESHOLD_HL, buffer, 2 );
    *upper_threshold = ( ( uint16_t ) buffer[ 1 ] << 8 ) | buffer[ 0 ];
    return error_flag;
}

err_t color2_read_lower_threshold ( color2_t *ctx, uint16_t *lower_threshold )
{
    err_t error_flag = COLOR2_OK;
    uint8_t buffer[ 2 ] = { 0 };
    error_flag |= color2_generic_read( ctx, COLOR2_THRESHOLD_LL, buffer, 2 );
    *lower_threshold = ( ( uint16_t ) buffer[ 1 ] << 8 ) | buffer[ 0 ];
    return error_flag;
}

err_t color2_read_rgb ( color2_t *ctx, color2_rgb_t *rgb )
{
    err_t error_flag = COLOR2_OK;
    uint8_t buffer[ 6 ] = { 0 };
    error_flag |= color2_generic_read( ctx, COLOR2_GREEN_L, buffer, 6 );
    rgb->green = ( ( uint16_t ) buffer[ 1 ] << 8 ) | buffer[ 0 ];
    rgb->red = ( ( uint16_t ) buffer[ 3 ] << 8 ) | buffer[ 2 ];
    rgb->blue = ( ( uint16_t ) buffer[ 5 ] << 8 ) | buffer[ 4 ];
    return error_flag;
}

err_t color2_read_status ( color2_t *ctx, uint8_t *status )
{
    return color2_read_reg( ctx, COLOR2_STATUS, status );
}

void color2_rgb_to_hsl ( color2_t *ctx, color2_rgb_t *rgb, color2_hsl_t *hsl )
{
    if ( ( !rgb->red ) && ( !rgb->red ) && ( !rgb->red ) )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
        hsl->lightness = 0;
        return;
    }
    float red_ratio = ( float ) rgb->red / 0xFFFF;
    float green_ratio = ( float ) rgb->green / 0xFFFF;
    float blue_ratio = ( float ) rgb->blue / 0xFFFF;
    float color_max = color2_max_float ( red_ratio, green_ratio, blue_ratio );
    float color_min = color2_min_float ( red_ratio, green_ratio, blue_ratio );
    float chroma = color_max - color_min;
    
    hsl->lightness = color_max;
    if ( color_max == color_min )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
    }
    else
    {
        if ( hsl->lightness > 0.5 )
        {
            hsl->saturation = chroma / ( 2 - color_max - color_min );
        }
        else
        {
            hsl->saturation = chroma / ( color_max + color_min );
        }
        if ( red_ratio == color_max ) 
        {
            hsl->hue = ( green_ratio - blue_ratio ) / chroma;
            
        }
        else if ( green_ratio == color_max ) 
        {
            hsl->hue = ( blue_ratio - red_ratio ) / chroma + 2;
        }
        else 
        {
            hsl->hue = ( red_ratio - green_ratio ) / chroma + 4;
        }
        hsl->hue /= 6;
        if ( hsl->hue < 0 )
        {
            hsl->hue += 1;
        }
    }
    hsl->hue *= COLOR2_HSL_HUE_RESOLUTION;
    hsl->saturation *= COLOR2_HSL_SATURATION_RESOLUTION;
    hsl->lightness *= COLOR2_HSL_LIGHTNESS_RESOLUTION;
}

uint8_t color2_get_color ( color2_hsl_t *hsl )
{
    if ( hsl->lightness >= COLOR2_WHITE_COLOR_LIGHTNESS )
    {
        return COLOR2_WHITE_COLOR;
    }
    else if ( hsl->lightness <= COLOR2_BLACK_COLOR_LIGHTNESS )
    {
        return COLOR2_BLACK_COLOR;
    }
    else if ( ( hsl->hue >= COLOR2_RED_COLOR_HUE_ANGLE ) || ( hsl->hue < COLOR2_YELLOW_COLOR_HUE_ANGLE ) )
    {
        return COLOR2_RED_COLOR;
    }
    else if ( hsl->hue >= COLOR2_MAGENTA_COLOR_HUE_ANGLE )
    {
        return COLOR2_MAGENTA_COLOR;
    }
    else if ( hsl->hue >= COLOR2_BLUE_COLOR_HUE_ANGLE )
    {
        return COLOR2_BLUE_COLOR;
    }
    else if ( hsl->hue >= COLOR2_CYAN_COLOR_HUE_ANGLE )
    {
        return COLOR2_CYAN_COLOR;
    }
    else if ( hsl->hue >= COLOR2_GREEN_COLOR_HUE_ANGLE )
    {
        return COLOR2_GREEN_COLOR;
    }
    else if ( hsl->hue >= COLOR2_YELLOW_COLOR_HUE_ANGLE )
    {
        return COLOR2_YELLOW_COLOR;
    }
    else 
    {
        return COLOR2_UNKNOWN_COLOR;
    }
}

static float color2_max_float ( float x, float y, float z )
{
    if ( ( x >= y ) && ( x >= z ) )
    {
        return x;
    }
    else if ( y >= z )
    {
        return y;
    }
    else
    {
        return z;
    }
}

static float color2_min_float ( float x, float y, float z )
{
    if ( ( x <= y ) && ( x <= z ) )
    {
        return x;
    }
    else if ( y <= z )
    {
        return y;
    }
    else
    {
        return z;
    }
}

// ------------------------------------------------------------------------- END
