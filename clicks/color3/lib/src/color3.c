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

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

void color3_cfg_setup ( color3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = COLOR_3_I2C_SLAVE_ADDR;

}

COLOR3_RETVAL color3_init ( color3_t *ctx, color3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->clear_data = cfg->dev_const.clear_data;
    ctx->red_data = cfg->dev_const.red_data;
    ctx->green_data = cfg->dev_const.green_data;
    ctx->blue_data = cfg->dev_const.blue_data;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return COLOR3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return COLOR3_OK;

}

void color3_generic_write ( color3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void color3_generic_read ( color3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void color3_normal_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = wr_data;

    color3_generic_write( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_AUTOINC | wr_addr, w_buffer, 1 );
}

void color3_special_wr_byte ( color3_t *ctx, uint8_t wr_addr, uint8_t wr_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = wr_data;

  color3_generic_write( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_SPECIAL | wr_addr, w_buffer, 1 );
}

uint8_t color3_read_byte ( color3_t *ctx, uint8_t rd_addr )
{
    uint8_t r_buffer[ 1 ];

   color3_generic_read( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_AUTOINC | rd_addr, r_buffer, 1 );

    return r_buffer[ 0 ];
}

void color3_normal_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 0 ] = ( uint8_t ) wr_data;
    w_buffer[ 1 ] = ( uint8_t ) ( wr_data >> 8 );

   color3_generic_write( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_AUTOINC | wr_addr, w_buffer, 2  );
}

void color3_special_wr_data ( color3_t *ctx, uint8_t wr_addr, uint16_t wr_data )
{
    uint8_t w_buffer[ 2 ];

    w_buffer[ 1 ] = ( uint8_t ) wr_data;
    w_buffer[ 2 ] = ( uint8_t ) ( wr_data >> 8 );

    color3_generic_write( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_SPECIAL | wr_addr, w_buffer, 2 );
}

uint16_t color3_read_data ( color3_t *ctx, uint8_t rd_addr )
{
    uint16_t result;
    uint8_t r_buffer[ 2 ];

    color3_generic_read( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_AUTOINC | rd_addr,r_buffer, 2 );

    result = r_buffer[ 1 ];
    result <<= 8;
    result |=  r_buffer[ 0 ];

    return result;
}

void color3_write_enable_register ( color3_t *ctx, uint8_t wr_data )
{
 color3_normal_wr_byte( ctx, COLOR_3_ENABLE, wr_data );
}

uint8_t color3_read_enable_register ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_ENABLE );

    return result;
}

void color3_write_rgbc_timing_register ( color3_t *ctx , uint8_t wr_data )
{
 color3_normal_wr_byte( ctx, COLOR_3_ATIME, wr_data );
}

uint8_t color3_read_rgbc_timing_register ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_ATIME );

    return result;
}

void color3_write_proxy_timing_register ( color3_t *ctx )
{
 color3_normal_wr_byte( ctx, COLOR_3_PTIME, 0xFF );
}

uint8_t color3_read_proxy_timing_register ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_PTIME );

    return result;
}

void color3_write_wait_time_register ( color3_t *ctx, uint8_t wr_data )
{
 color3_normal_wr_byte( ctx, COLOR_3_WTIME, wr_data );
}

uint8_t color3_read_wait_time_register ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_WTIME );

    return result;
}

void color3_set_inter_trsh_lo_val( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR_3_AILTL, wr_data );
}

void color3_set_inter_trsh_hi_val ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data ( ctx, COLOR_3_AIHTL, wr_data );
}

void color3_set_proxy_inter_trsh_lo_val ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR_3_PILTL, wr_data );
}

void color3_set_proxy_inter_trsh_hi_val ( color3_t *ctx, uint16_t wr_data )
{
    color3_normal_wr_data( ctx, COLOR_3_PIHTL, wr_data );
}

void color3_set_interrupt_persistence ( color3_t *ctx, uint8_t int_pers )
{
    color3_normal_wr_byte( ctx, COLOR_3_PERS, int_pers );
}

uint8_t color3_read_interrupt_persistence ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_PERS );

    return result;
}

void color3_setproxy_interrupt_persistence ( color3_t *ctx, uint8_t int_pers )
{
    int_pers <<= 4;
    color3_normal_wr_byte( ctx, COLOR_3_PERS, int_pers );
}

uint8_t color3_read_proxy_interrupt_persistence ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_PERS );
    result >>=4;

    return result;
}

void color3_set_long_wait ( color3_t *ctx, uint8_t lon_wait )
{
    color3_normal_wr_byte( ctx, COLOR_3_CONFIG, lon_wait );
}

uint8_t color3_read_long_wait ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_CONFIG );

    return result;
}

void color3_write_pulse_cnt ( color3_t *ctx, uint8_t pulse_cnt )
{
    color3_normal_wr_byte( ctx, COLOR_3_PPCOUNT, pulse_cnt );
}

uint8_t color3_read_pulse_cnt ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_PPCOUNT );

    return result;
}

void color3_write_rgbc_gain ( color3_t *ctx, uint8_t gain_val )
{
    color3_normal_wr_byte( ctx, COLOR_3_CONTROL, gain_val );
}

uint8_t color3_read_rgbc_gain ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_CONTROL );

    return result;
}

void color3_set_diode_select ( color3_t *ctx, uint8_t dio_sel )
{
    color3_normal_wr_byte( ctx, COLOR_3_CONTROL, dio_sel );
}

uint8_t color3_get_diode_select ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_CONTROL );

    return result;
}

void color3_set_led_str ( color3_t *ctx, uint8_t led_str )
{
    color3_normal_wr_byte( ctx, COLOR_3_CONTROL, led_str );
}

uint8_t color3_read_led_str ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_CONTROL );

    return result;
}


uint8_t color3_read_dev_id ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_ID );

    return result;
}

uint8_t color3_read_dev_stat ( color3_t *ctx )
{
    uint8_t result;
    result =  color3_read_byte( ctx, COLOR_3_STATUS );

    return result;
}

uint16_t color3_read_clear_data ( color3_t *ctx )
{
    uint16_t result;
    result = color3_read_data( ctx, COLOR_3_CDATA );

    return result;
}

uint16_t color3_read_red_data ( color3_t *ctx )
{
    uint16_t result;
    result = color3_read_data( ctx, COLOR_3_RDATA );

    return result;
}

uint16_t color3_read_green_data ( color3_t *ctx )
{
    uint16_t result;
    result = color3_read_data( ctx, COLOR_3_GDATA );

    return result;
}


uint16_t color3_read_blue_data ( color3_t *ctx )
{
    uint16_t result;
    result = color3_read_data( ctx, COLOR_3_BDATA );

    return result;
}

uint16_t color3_read_proxy_data( color3_t *ctx )
{
    uint16_t result;
    result = color3_read_data( ctx, COLOR_3_PDATA );

    return result;
}

uint8_t color3_get_inter_state ( color3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void color3_set_default_settings ( color3_t *ctx )
{
    color3_set_diode_select( ctx, COLOR_3_IR_DIODE );
    color3_write_pulse_cnt( ctx, COLOR_3_PROXY_PULSE_256 );
    color3_write_wait_time_register( ctx, COLOR_3_WAIT_TIME_REG_40_CYC );
    color3_set_proxy_inter_trsh_lo_val( ctx, COLOR_3_LOW_THRESHOLD_VALUE );
    color3_set_proxy_inter_trsh_hi_val( ctx, COLOR_3_HIGH_THRESHOLD_VALUE );
    color3_set_inter_trsh_lo_val( ctx, COLOR_3_LOW_THRESHOLD_VALUE );
    color3_set_inter_trsh_hi_val( ctx, COLOR_3_HIGH_THRESHOLD_VALUE );
    color3_set_interrupt_persistence( ctx, COLOR_3_2_OR_INTER );
    color3_setproxy_interrupt_persistence( ctx, COLOR_3_2_OR_INTER );
    color3_write_enable_register(  ctx,  COLOR_3_ENABLE_REG_PON | COLOR_3_ENABLE_REG_AEN |COLOR_3_ENABLE_REG_PEN | COLOR_3_ENABLE_REG_WEN | COLOR_3_ENABLE_REG_AIEN | COLOR_3_ENABLE_REG_PIEN );
    color3_write_rgbc_timing_register( ctx, COLOR_3_RGBC_TIMING_4_CYC );
    color3_write_proxy_timing_register( ctx );
}

void color_3_get_rgb_data ( color3_t *ctx, uint16_t *red_data, uint16_t *green_data, uint16_t *blue_data )
{
    *red_data = color3_read_red_data( ctx );
    *green_data = color3_read_green_data( ctx );
    *blue_data = color3_read_blue_data( ctx );
}

float color3_get_color_ratio ( color3_t *ctx, uint16_t color_data )
{
    uint16_t clear_data;
    float color_ratio;

    clear_data = color3_read_clear_data( ctx );

    color_ratio = ( ( float )color_data / ( float )clear_data );

    return color_ratio;
}

float color3_get_color_value ( color3_t *ctx )
{
    uint16_t red_data;
    uint16_t green_data;
    uint16_t blue_data;
    float red_ratio;
    float green_ratio;
    float blue_ratio;
    float color_data;
    float color_value;
    uint8_t cnt;

    color_value = 0.0;
    color_data = 0.0;
    red_data = color3_read_red_data( ctx );
    green_data = color3_read_green_data( ctx );
    blue_data = color3_read_blue_data( ctx );

    for ( cnt = 0; cnt < 16; cnt++ )
    {
        red_ratio = color3_get_color_ratio( ctx, red_data );
        green_ratio = color3_get_color_ratio( ctx, green_data );
        blue_ratio = color3_get_color_ratio( ctx, blue_data );

        color_data = color3_rgb_to_hsl( ctx, red_ratio, green_ratio, blue_ratio );
        color_value = color_value + color_data;
    }
    color_value = color_value / 16.0;

    return color_value;
}

void color_3_get_crgb_data ( color3_t *ctx, color3_const_t *data_const )
{
    uint8_t r_buffer[ 8 ];
    uint16_t temp_data;
    
    color3_generic_read( ctx, COLOR_3_COMMAND_SELECT | COLOR_3_COMMAND_TYPE_AUTOINC | 0x14, r_buffer, 8 );

    //Clear Data
    temp_data = r_buffer[ 1 ];
    temp_data <<= 8;
    temp_data |= r_buffer[ 0 ];
    
    *data_const->clear_data = temp_data;

  //Red Data
    temp_data = 0;
    
    temp_data = r_buffer[ 3 ];
    temp_data <<= 8;
    temp_data |= r_buffer[ 2 ];
    
    *data_const->red_data = temp_data;

    //Green Data
    temp_data = 0;
    
    temp_data = r_buffer[ 5 ];
    temp_data <<= 8;
    temp_data |= r_buffer[ 4 ];
    
   * data_const->green_data = temp_data;

    //Blue Data
    temp_data = 0;
    
    temp_data = r_buffer[ 7 ];
    temp_data <<= 8;
    temp_data |= r_buffer[ 6 ];

   * data_const->blue_data = temp_data;
}
// ----------------------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static float color3_max_color ( color3_t *ctx, float color_a, float color_b )
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

static float color3_min_color ( color3_t *ctx, float color_a, float color_b )
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

static float color3_rgb_to_hsl ( color3_t *ctx, float red, float green, float blue )
{
    float fmax;
    float fmin;
    float hue_value;
    float saturation_value;

    fmax = color3_max_color( ctx, color3_max_color( ctx, red, green ),  blue );
    fmin = color3_min_color( ctx, color3_min_color(ctx,  red, green ), blue );

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

