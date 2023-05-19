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

#include "color3.h"

/**
 * @brief Color 3 max float function.
 * @details This function returns the maximal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Maximal float number.
 * @note None.
 */
static float color3_max_float ( float x, float y, float z );

/**
 * @brief Color 3 min float function.
 * @details This function returns the minimal number of 3 float inputs.
 * @param[in] x : First float parameter.
 * @param[in] y : Second float parameter.
 * @param[in] z : Third float parameter.
 * @return Minimal float number.
 * @note None.
 */
static float color3_min_float ( float x, float y, float z );

void color3_cfg_setup ( color3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR3_I2C_SLAVE_ADDR;
}

err_t color3_init ( color3_t *ctx, color3_cfg_t *cfg )
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

    return COLOR3_OK;
}

err_t color3_generic_write ( color3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t color3_generic_read ( color3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void color3_normal_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    color3_generic_write( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_AUTOINC | wr_addr, &wr_data, 1 );
}

void color3_special_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    color3_generic_write( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_SPECIAL | wr_addr, &wr_data, 1 );
}

uint8_t color3_read_byte ( color3_t *ctx, uint8_t rd_addr )
{
    uint8_t rd_data = 0;
    color3_generic_read( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_AUTOINC | rd_addr, &rd_data, 1 );
    return rd_data;
}

void color3_normal_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data )
{
    uint8_t w_buffer[ 2 ] = { 0 };
    w_buffer[ 0 ] = ( uint8_t ) wr_data;
    w_buffer[ 1 ] = ( uint8_t ) ( wr_data >> 8 );
    color3_generic_write( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_AUTOINC | wr_addr, w_buffer, 2  );
}

void color3_special_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data )
{
    uint8_t w_buffer[ 2 ] = { 0 };
    w_buffer[ 1 ] = ( uint8_t ) wr_data;
    w_buffer[ 2 ] = ( uint8_t ) ( wr_data >> 8 );
    color3_generic_write( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_SPECIAL | wr_addr, w_buffer, 2 );
}

uint16_t color3_read_data ( color3_t *ctx, uint8_t rd_addr )
{
    uint16_t result = 0;
    uint8_t r_buffer[ 2 ] = { 0 };
    color3_generic_read( ctx, COLOR3_COMMAND_SELECT | COLOR3_COMMAND_TYPE_AUTOINC | rd_addr, r_buffer, 2 );
    result = r_buffer[ 1 ];
    result <<= 8;
    result |= r_buffer[ 0 ];
    return result;
}

void color3_write_enable_reg ( color3_t *ctx, uint8_t wr_data )
{
    color3_normal_wr_byte( ctx, COLOR3_ENABLE, wr_data );
}

uint8_t color3_read_enable_reg ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_ENABLE );
}

void color3_write_rgbc_timing_reg ( color3_t *ctx , uint8_t wr_data )
{
    color3_normal_wr_byte( ctx, COLOR3_ATIME, wr_data );
}

uint8_t color3_read_rgbc_timing_reg ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_ATIME );
}

void color3_write_prox_timing_reg ( color3_t *ctx )
{
    color3_normal_wr_byte( ctx, COLOR3_PTIME, 0xFF );
}

uint8_t color3_read_prox_timing_reg ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_PTIME );
}

void color3_write_wait_time_reg ( color3_t *ctx, uint8_t wr_data )
{
    color3_normal_wr_byte( ctx, COLOR3_WTIME, wr_data );
}

uint8_t color3_read_wait_time_reg ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_WTIME );
}

void color3_set_inter_trsh_lo ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR3_AILTL, wr_data );
}

void color3_set_inter_trsh_hi ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data ( ctx, COLOR3_AIHTL, wr_data );
}

void color3_set_prox_inter_trsh_lo ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR3_PILTL, wr_data );
}

void color3_set_prox_inter_trsh_hi ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR3_PIHTL, wr_data );
}

void color3_set_int_pers ( color3_t *ctx, uint8_t int_pers )
{
    color3_normal_wr_byte( ctx, COLOR3_PERS, int_pers );
}

uint8_t color3_read_int_pers ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_PERS );
}

void color3_set_prox_int_pers ( color3_t *ctx, uint8_t int_pers )
{
    color3_normal_wr_byte( ctx, COLOR3_PERS, int_pers << 4 );
}

uint8_t color3_read_prox_int_pers ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_PERS ) >> 4;
}

void color3_set_long_wait ( color3_t *ctx, uint8_t lon_wait )
{
    color3_normal_wr_byte( ctx, COLOR3_CONFIG, lon_wait );
}

uint8_t color3_read_long_wait ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_CONFIG );
}

void color3_write_pulse_cnt ( color3_t *ctx, uint8_t pulse_cnt )
{
    color3_normal_wr_byte( ctx, COLOR3_PPCOUNT, pulse_cnt );
}

uint8_t color3_read_pulse_cnt ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_PPCOUNT );
}

void color3_write_rgbc_gain ( color3_t *ctx, uint8_t gain )
{
    color3_normal_wr_byte( ctx, COLOR3_CONTROL, gain );
}

uint8_t color3_read_rgbc_gain ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_CONTROL );
}

void color3_set_diode_select ( color3_t *ctx, uint8_t dio_sel )
{
    color3_normal_wr_byte( ctx, COLOR3_CONTROL, dio_sel );
}

uint8_t color3_get_diode_select ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_CONTROL );
}

void color3_set_led_str ( color3_t *ctx, uint8_t led_str )
{
    color3_normal_wr_byte( ctx, COLOR3_CONTROL, led_str );
}

uint8_t color3_read_led_str ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_CONTROL );
}

uint8_t color3_read_dev_id ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_ID );
}

uint8_t color3_read_dev_stat ( color3_t *ctx )
{
    return color3_read_byte( ctx, COLOR3_STATUS );
}

uint16_t color3_read_clear_data ( color3_t *ctx )
{
    return color3_read_data( ctx, COLOR3_CDATA );
}

uint16_t color3_read_red_data ( color3_t *ctx )
{
    return color3_read_data( ctx, COLOR3_RDATA );
}

uint16_t color3_read_green_data ( color3_t *ctx )
{
    return color3_read_data( ctx, COLOR3_GDATA );
}

uint16_t color3_read_blue_data ( color3_t *ctx )
{
    return color3_read_data( ctx, COLOR3_BDATA );
}

uint16_t color3_read_prox_data( color3_t *ctx )
{
    return color3_read_data( ctx, COLOR3_PDATA );
}

uint8_t color3_get_inter_state ( color3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void color3_set_default_settings ( color3_t *ctx )
{
    color3_set_diode_select( ctx, COLOR3_IR_DIODE );
    color3_write_pulse_cnt( ctx, COLOR3_PROXY_PULSE_256 );
    color3_write_wait_time_reg( ctx, COLOR3_WAIT_TIME_REG_64_CYC );
    color3_set_prox_inter_trsh_lo( ctx, COLOR3_LOW_THRESHOLD_VALUE );
    color3_set_prox_inter_trsh_hi( ctx, COLOR3_HIGH_THRESHOLD_VALUE );
    color3_set_inter_trsh_lo( ctx, COLOR3_LOW_THRESHOLD_VALUE );
    color3_set_inter_trsh_hi( ctx, COLOR3_HIGH_THRESHOLD_VALUE );
    color3_set_int_pers( ctx, COLOR3_2_OR_INTER );
    color3_set_prox_int_pers( ctx, COLOR3_2_OR_INTER );
    color3_write_enable_reg(  ctx, COLOR3_ENABLE_REG_PON | COLOR3_ENABLE_REG_AEN |
                                   COLOR3_ENABLE_REG_PEN | COLOR3_ENABLE_REG_WEN | 
                                   COLOR3_ENABLE_REG_AIEN | COLOR3_ENABLE_REG_PIEN );
    color3_write_rgbc_timing_reg( ctx, COLOR3_RGBC_TIMING_4_CYC );
    color3_write_prox_timing_reg( ctx );
    color3_write_rgbc_gain( ctx, COLOR3_A_GAIN_16 );
}

void color3_get_rgb_data ( color3_t *ctx, uint16_t *red_data, uint16_t *green_data, uint16_t *blue_data )
{
    *red_data = color3_read_red_data( ctx );
    *green_data = color3_read_green_data( ctx );
    *blue_data = color3_read_blue_data( ctx );
}

float color3_get_color_ratio ( color3_t *ctx, uint16_t color_data )
{
    return ( ( float ) color_data / ( float ) color3_read_clear_data( ctx ) );
}

err_t color3_get_rgbc_data ( color3_t *ctx, color3_channels_t *channels )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( COLOR3_ERROR == color3_generic_read( ctx, COLOR3_COMMAND_SELECT | 
                                                   COLOR3_COMMAND_TYPE_AUTOINC | 
                                                   COLOR3_CDATA, data_buf, 8 ) )
    {
        return COLOR3_ERROR;
    }
    channels->clear = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    channels->red = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    channels->green = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 4 ];
    channels->blue = ( ( uint16_t ) data_buf[ 7 ] << 8 ) | data_buf[ 6 ];
    return COLOR3_OK;
}

uint8_t color3_get_color ( color3_hsl_t *hsl )
{
    if ( hsl->lightness >= COLOR3_WHITE_COLOR_LIGHTNESS )
    {
        return COLOR3_WHITE_COLOR;
    }
    else if ( hsl->lightness <= COLOR3_BLACK_COLOR_LIGHTNESS )
    {
        return COLOR3_BLACK_COLOR;
    }
    else if ( ( hsl->hue >= COLOR3_RED_COLOR_HUE_ANGLE ) || ( hsl->hue < COLOR3_YELLOW_COLOR_HUE_ANGLE ) )
    {
        return COLOR3_RED_COLOR;
    }
    else if ( hsl->hue >= COLOR3_MAGENTA_COLOR_HUE_ANGLE )
    {
        return COLOR3_MAGENTA_COLOR;
    }
    else if ( hsl->hue >= COLOR3_BLUE_COLOR_HUE_ANGLE )
    {
        return COLOR3_BLUE_COLOR;
    }
    else if ( hsl->hue >= COLOR3_CYAN_COLOR_HUE_ANGLE )
    {
        return COLOR3_CYAN_COLOR;
    }
    else if ( hsl->hue >= COLOR3_GREEN_COLOR_HUE_ANGLE )
    {
        return COLOR3_GREEN_COLOR;
    }
    else if ( hsl->hue >= COLOR3_YELLOW_COLOR_HUE_ANGLE )
    {
        return COLOR3_YELLOW_COLOR;
    }
    else 
    {
        return COLOR3_UNKNOWN_COLOR;
    }
}

void color3_rgbc_to_hsl ( color3_t *ctx, color3_channels_t *rgbc, color3_hsl_t *hsl )
{
    if ( ( !rgbc->clear ) || ( ( !rgbc->red ) && ( !rgbc->red ) && ( !rgbc->red ) ) )
    {
        hsl->hue = 0;
        hsl->saturation = 0;
        hsl->lightness = 0;
        return;
    }
    float red_ratio = ( float ) rgbc->red / 4096;
    float green_ratio = ( float ) rgbc->green / 4096;
    float blue_ratio = ( float ) rgbc->blue / 4096;
    float color_max = color3_max_float ( red_ratio, green_ratio, blue_ratio );
    float color_min = color3_min_float ( red_ratio, green_ratio, blue_ratio );
    float chroma = color_max - color_min;
    
    hsl->lightness = ( float ) rgbc->clear / 4096;
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
    hsl->hue *= COLOR3_HSL_HUE_RESOLUTION;
    hsl->saturation *= COLOR3_HSL_SATURATION_RESOLUTION;
    hsl->lightness *= COLOR3_HSL_LIGHTNESS_RESOLUTION;
}

static float color3_max_float ( float x, float y, float z )
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

static float color3_min_float ( float x, float y, float z )
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
