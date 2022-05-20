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
 * @file color15.c
 * @brief Color 15 Click Driver.
 */

#include "color15.h"

/**
 * @brief Color 15 max float function.
 * @details This function returns the maximal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Maximal float number.
 * @note None.
 */
static float color15_max_float ( float x, float y, float z );

/**
 * @brief Color 15 min float function.
 * @details This function returns the minimal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Minimal float number.
 * @note None.
 */
static float color15_min_float ( float x, float y, float z );

void color15_cfg_setup ( color15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = COLOR15_DEVICE_ADDRESS;
}

err_t color15_init ( color15_t *ctx, color15_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t color15_default_cfg ( color15_t *ctx ) 
{
    err_t error_flag = COLOR15_OK;
    if ( COLOR15_ERROR == color15_check_communication ( ctx ) )
    {
        return COLOR15_ERROR;
    }
    error_flag |= color15_write_register ( ctx, COLOR15_REG_SYSM_CTRL, COLOR15_SYSM_CTRL_EN_IR | 
                                                                       COLOR15_SYSM_CTRL_EN_CLS );
    error_flag |= color15_write_register ( ctx, COLOR15_REG_INT_CTRL, COLOR15_INT_CTRL_CLS_SYNC | 
                                                                      COLOR15_INT_CTRL_EN_CINT );
    error_flag |= color15_write_register ( ctx, COLOR15_REG_INT_SOURCE, COLOR15_INT_SRC_WCH_DATA );
    error_flag |= color15_write_register ( ctx, COLOR15_REG_PERSISTENCE, COLOR15_PRS_CLS_INDEPENDENT );
    error_flag |= color15_write_register ( ctx, COLOR15_REG_CLS_GAIN, COLOR15_CLS_GAIN_DIOD_SELT_X2 | 
                                                                      COLOR15_CLS_GAIN_PGA_CLS_X96 );
    error_flag |= color15_set_cls_time ( ctx, COLOR15_CLSCONV_4, COLOR15_INT_TIME_64 );
    error_flag |= color15_clear_interrupt ( ctx );
    return error_flag;
}

err_t color15_generic_write ( color15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color15_generic_read ( color15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t color15_write_register ( color15_t *ctx, uint8_t reg, uint8_t data_in )
{
    return color15_generic_write ( ctx, reg, &data_in, 1 );
}

err_t color15_read_register ( color15_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return color15_generic_read ( ctx, reg, data_out, 1 );
}

err_t color15_check_communication ( color15_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( COLOR15_OK == color15_generic_read ( ctx, COLOR15_REG_PROD_ID_L, data_buf, 2 ) )
    {
        if ( ( COLOR15_PRODUCT_ID_LSB == data_buf[ 0 ] ) && ( COLOR15_PRODUCT_ID_MSB == data_buf[ 1 ] ) )
        {
            return COLOR15_OK;
        }
    }
    return COLOR15_ERROR;
}

uint8_t color15_get_int_pin ( color15_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t color15_clear_interrupt ( color15_t *ctx )
{
    return color15_write_register ( ctx, COLOR15_REG_INT_FLAG, COLOR15_INT_FLAG_CLEAR_ALL );
}

err_t color15_set_wait_time ( color15_t *ctx, uint16_t wait_time )
{
    if ( ( wait_time < COLOR15_WAIT_TIME_MS_MIN ) || ( wait_time > COLOR15_WAIT_TIME_MS_MAX ) )
    {
        return COLOR15_ERROR;
    }
    return color15_write_register ( ctx, COLOR15_REG_WAIT_TIME, ( uint8_t ) ( wait_time / COLOR15_WAIT_TIME_MS_LSB - 1 ) );
}

err_t color15_set_cls_time ( color15_t *ctx, uint8_t clsconv, uint8_t int_time )
{
    if ( ( clsconv > COLOR15_CLSCONV_15 ) || ( int_time > COLOR15_INT_TIME_64 ) )
    {
        return COLOR15_ERROR;
    }
    uint32_t max_count = COLOR15_MAX_COUNT_LSB * ( 1 << ( int_time * 2 ) ) * ( clsconv + 1 ) - 1;
    if ( max_count > COLOR15_MAX_COUNT_RES )
    {
        max_count = COLOR15_MAX_COUNT_RES;
    }
    ctx->resolution = ( uint16_t ) max_count;
    return color15_write_register ( ctx, COLOR15_REG_CLS_TIME, ( clsconv << 4 ) | int_time );
}

err_t color15_get_data ( color15_t *ctx, color15_channels_t *channels )
{
    uint8_t data_buf[ 10 ];
    if ( COLOR15_ERROR == color15_generic_read ( ctx, COLOR15_REG_RCH_DATA_L, data_buf, 10 ) )
    {
        return COLOR15_ERROR;
    }
    channels->red = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    channels->green = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    channels->blue = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
    channels->white = ( ( uint16_t ) data_buf[ 7 ] << 8 ) | data_buf[ 6 ];
    channels->ir = ( ( uint16_t ) data_buf[ 9 ] << 8 ) | data_buf[ 8 ];
    return COLOR15_OK;
}

uint8_t color15_get_color ( color15_hsl_t *hsl )
{
    if ( hsl->lightness >= COLOR15_WHITE_COLOR_LIGHTNESS )
    {
        return COLOR15_WHITE_COLOR;
    }
    else if ( hsl->lightness <= COLOR15_BLACK_COLOR_LIGHTNESS )
    {
        return COLOR15_BLACK_COLOR;
    }
    else if ( ( hsl->hue >= COLOR15_RED_COLOR_HUE_ANGLE ) || ( hsl->hue < COLOR15_YELLOW_COLOR_HUE_ANGLE ) )
    {
        return COLOR15_RED_COLOR;
    }
    else if ( hsl->hue >= COLOR15_MAGENTA_COLOR_HUE_ANGLE )
    {
        return COLOR15_MAGENTA_COLOR;
    }
    else if ( hsl->hue >= COLOR15_BLUE_COLOR_HUE_ANGLE )
    {
        return COLOR15_BLUE_COLOR;
    }
    else if ( hsl->hue >= COLOR15_CYAN_COLOR_HUE_ANGLE )
    {
        return COLOR15_CYAN_COLOR;
    }
    else if ( hsl->hue >= COLOR15_GREEN_COLOR_HUE_ANGLE )
    {
        return COLOR15_GREEN_COLOR;
    }
    else if ( hsl->hue >= COLOR15_YELLOW_COLOR_HUE_ANGLE )
    {
        return COLOR15_YELLOW_COLOR;
    }
    else 
    {
        return COLOR15_UNKNOWN_COLOR;
    }
}

void color15_rgbw_to_hsl ( color15_t *ctx, color15_channels_t *rgbw, color15_hsl_t *hsl )
{
    if ( ( !rgbw->white ) || ( ( !rgbw->red ) && ( !rgbw->red ) && ( !rgbw->red ) ) )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
        hsl->lightness = 0;
        return;
    }
    float red_ratio = ( float ) rgbw->red / ctx->resolution;
    float green_ratio = ( float ) rgbw->green / ctx->resolution;
    float blue_ratio = ( float ) rgbw->blue / ctx->resolution;
    float color_max = color15_max_float ( red_ratio, green_ratio, blue_ratio );
    float color_min = color15_min_float ( red_ratio, green_ratio, blue_ratio );
    float chroma = color_max - color_min;
    
    hsl->lightness = ( float ) rgbw->white / ctx->resolution;
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
    hsl->hue *= COLOR15_HSL_HUE_RESOLUTION;
    hsl->saturation *= COLOR15_HSL_SATURATION_RESOLUTION;
    hsl->lightness *= COLOR15_HSL_LIGHTNESS_RESOLUTION;
}

static float color15_max_float ( float x, float y, float z )
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

static float color15_min_float ( float x, float y, float z )
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
