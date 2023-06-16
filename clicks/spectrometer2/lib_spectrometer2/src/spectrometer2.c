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
 * @file spectrometer2.c
 * @brief Spectrometer 2 Click Driver.
 */

#include "spectrometer2.h"

/**
 * @brief Spectrometer 2 max float function.
 * @details This function returns the maximal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Maximal float number.
 * @note None.
 */
static float spectrometer2_max_float ( float x, float y, float z );

/**
 * @brief Spectrometer 2 min float function.
 * @details This function returns the minimal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Minimal float number.
 * @note None.
 */
static float spectrometer2_min_float ( float x, float y, float z );

void spectrometer2_cfg_setup ( spectrometer2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SPECTROMETER2_DEVICE_ADDRESS;
}

err_t spectrometer2_init ( spectrometer2_t *ctx, spectrometer2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t spectrometer2_default_cfg ( spectrometer2_t *ctx ) 
{
    err_t error_flag = SPECTROMETER2_OK;
    if ( SPECTROMETER2_ERROR == spectrometer2_check_communication ( ctx ) )
    {
        return SPECTROMETER2_ERROR;
    }
    error_flag |= spectrometer2_set_exposure_time ( ctx, SPECTROMETER2_EXPOSURE_TIME_MS_DEFAULT );
    error_flag |= spectrometer2_set_inter_measurement_period ( ctx, SPECTROMETER2_IM_PERIOD_MS_DEFAULT );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH1, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH2, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH3, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH4, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH5, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_GAIN_CH6, SPECTROMETER2_AGAIN_66p6X );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_CHANNEL_ENABLE, SPECTROMETER2_ALL_CHANNELS_ENABLE );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_CHANNEL6_ENABLE, SPECTROMETER2_CHANNEL6_ENABLE );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_CTRL, SPECTROMETER2_ALS_MODE_CONTINUOUS | 
                                                                                  SPECTROMETER2_ALS_START );
    error_flag |= spectrometer2_clear_interrupt ( ctx );
    return error_flag;
}

err_t spectrometer2_generic_write ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t spectrometer2_generic_read ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t spectrometer2_write_register ( spectrometer2_t *ctx, uint8_t reg, uint8_t data_in )
{
    return spectrometer2_generic_write( ctx, reg, &data_in, 1 );
}

err_t spectrometer2_read_register ( spectrometer2_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return spectrometer2_generic_read( ctx, reg, data_out, 1 );
}

err_t spectrometer2_check_communication ( spectrometer2_t *ctx )
{
    uint8_t device_id;
    if ( SPECTROMETER2_OK == spectrometer2_read_register ( ctx, SPECTROMETER2_REG_DEVICE_ID, &device_id ) )
    {
        if ( SPECTROMETER2_DEVICE_ID == device_id )
        {
            return SPECTROMETER2_OK;
        }
    }
    return SPECTROMETER2_ERROR;
}

uint8_t spectrometer2_get_int_pin ( spectrometer2_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

uint8_t spectrometer2_get_an_pin ( spectrometer2_t *ctx )
{
    return digital_in_read ( &ctx->an );
}

err_t spectrometer2_get_data ( spectrometer2_t *ctx, spectrometer2_als_channels_t *als_channels )
{
    uint8_t data_buf[ 3 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH1_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->red = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH2_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->visible = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH3_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->blue = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH4_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->green = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH5_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->ir = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    if ( SPECTROMETER2_ERROR == spectrometer2_generic_read ( ctx, SPECTROMETER2_REG_ALS_CH6_DATA_H, data_buf, 3 ) )
    {
        return SPECTROMETER2_ERROR;
    }
    als_channels->clear = ( ( uint32_t ) data_buf[ 0 ] << 16 ) | ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    return SPECTROMETER2_OK;
}

err_t spectrometer2_clear_interrupt ( spectrometer2_t *ctx )
{
    err_t error_flag = spectrometer2_write_register ( ctx, SPECTROMETER2_REG_INTERRUPT_CTRL, SPECTROMETER2_CLR_INTR_SET );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_INTERRUPT_CTRL, SPECTROMETER2_CLR_INTR_CLEAR );
    return error_flag;
}

err_t spectrometer2_set_exposure_time ( spectrometer2_t *ctx, float exp_time )
{
    if ( ( exp_time < SPECTROMETER2_EXPOSURE_TIME_MS_MIN ) || ( exp_time > SPECTROMETER2_EXPOSURE_TIME_MS_MAX ) )
    {
        return SPECTROMETER2_ERROR;
    }
    uint16_t raw_exp_time = ( uint16_t ) ( exp_time / SPECTROMETER2_EXPOSURE_TIME_MS_LSB - 1 ) & SPECTROMETER2_EXPOSURE_TIME_RES;
    err_t error_flag = spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_EXPOSURE_L, ( uint8_t ) ( raw_exp_time & 0xFF ) );
    error_flag |= spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_EXPOSURE_M, ( uint8_t ) ( ( raw_exp_time >> 8 ) & 0xFF ) );
    return error_flag;
}

err_t spectrometer2_set_inter_measurement_period ( spectrometer2_t *ctx, float im_period )
{
    if ( ( im_period < SPECTROMETER2_IM_PERIOD_MS_MIN ) || ( im_period > SPECTROMETER2_IM_PERIOD_MS_MAX ) )
    {
        return SPECTROMETER2_ERROR;
    }
    return spectrometer2_write_register ( ctx, SPECTROMETER2_REG_ALS_PERIOD, 
                                          ( uint8_t ) ( im_period / SPECTROMETER2_IM_PERIOD_MS_LSB ) & SPECTROMETER2_IM_PERIOD_RES );
}

uint8_t spectrometer2_get_color ( spectrometer2_hsl_t *hsl )
{
    if ( hsl->lightness >= SPECTROMETER2_WHITE_COLOR_LIGHTNESS )
    {
        return SPECTROMETER2_WHITE_COLOR;
    }
    else if ( hsl->lightness <= SPECTROMETER2_BLACK_COLOR_LIGHTNESS )
    {
        return SPECTROMETER2_BLACK_COLOR;
    }
    else if ( ( hsl->hue >= SPECTROMETER2_RED_COLOR_HUE_ANGLE ) || ( hsl->hue < SPECTROMETER2_YELLOW_COLOR_HUE_ANGLE ) )
    {
        return SPECTROMETER2_RED_COLOR;
    }
    else if ( hsl->hue >= SPECTROMETER2_MAGENTA_COLOR_HUE_ANGLE )
    {
        return SPECTROMETER2_MAGENTA_COLOR;
    }
    else if ( hsl->hue >= SPECTROMETER2_BLUE_COLOR_HUE_ANGLE )
    {
        return SPECTROMETER2_BLUE_COLOR;
    }
    else if ( hsl->hue >= SPECTROMETER2_CYAN_COLOR_HUE_ANGLE )
    {
        return SPECTROMETER2_CYAN_COLOR;
    }
    else if ( hsl->hue >= SPECTROMETER2_GREEN_COLOR_HUE_ANGLE )
    {
        return SPECTROMETER2_GREEN_COLOR;
    }
    else if ( hsl->hue >= SPECTROMETER2_YELLOW_COLOR_HUE_ANGLE )
    {
        return SPECTROMETER2_YELLOW_COLOR;
    }
    else 
    {
        return SPECTROMETER2_UNKNOWN_COLOR;
    }
}

void spectrometer2_rgbc_to_hsl ( spectrometer2_als_channels_t *rgbc, spectrometer2_hsl_t *hsl )
{
    if ( ( !rgbc->clear ) || ( ( !rgbc->red ) && ( !rgbc->red ) && ( !rgbc->red ) ) )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
        hsl->lightness = 0;
        return;
    }
    float red_ratio = ( float ) rgbc->red / rgbc->clear;
    float green_ratio = ( float ) rgbc->green / rgbc->clear;
    float blue_ratio = ( float ) rgbc->blue / rgbc->clear;
    float color_max = spectrometer2_max_float ( red_ratio, green_ratio, blue_ratio );
    float color_min = spectrometer2_min_float ( red_ratio, green_ratio, blue_ratio );
    
    hsl->lightness = ( color_max + color_min ) / 2;
    if ( color_max == color_min )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
    }
    else
    {
        if ( hsl->lightness > 0.5 )
        {
            hsl->saturation = ( color_max - color_min ) / ( 2 - color_max - color_min );
        }
        else
        {
            hsl->saturation = ( color_max - color_min ) / ( color_max + color_min );
        }
        if ( red_ratio == color_max ) 
        {
            hsl->hue = ( green_ratio - blue_ratio ) / ( color_max - color_min );
            
        }
        else if ( green_ratio == color_max ) 
        {
            hsl->hue = ( blue_ratio - red_ratio ) / ( color_max - color_min ) + 2;
        }
        else 
        {
            hsl->hue = ( red_ratio - green_ratio ) / ( color_max - color_min ) + 4;
        }
        hsl->hue /= 6;
        if ( hsl->hue < 0 )
        {
            hsl->hue += 1;
        }
    }
    hsl->hue *= SPECTROMETER2_HSL_HUE_RESOLUTION;
    hsl->saturation *= SPECTROMETER2_HSL_SATURATION_RESOLUTION;
    hsl->lightness *= SPECTROMETER2_HSL_LIGHTNESS_RESOLUTION;
}

static float spectrometer2_max_float ( float x, float y, float z )
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

static float spectrometer2_min_float ( float x, float y, float z )
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
