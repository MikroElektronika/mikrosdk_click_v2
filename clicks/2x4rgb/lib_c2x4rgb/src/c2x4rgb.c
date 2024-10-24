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
 * @file c2x4rgb.c
 * @brief 2x4 RGB Click Driver.
 */

#include "c2x4rgb.h"

void c2x4rgb_cfg_setup ( c2x4rgb_cfg_t *cfg ) 
{
    cfg->din = HAL_PIN_NC;
}

err_t c2x4rgb_init ( c2x4rgb_t *ctx, c2x4rgb_logic_t logic_zero, c2x4rgb_logic_t logic_one, c2x4rgb_cfg_t *cfg ) 
{
    err_t error_flag = C2X4RGB_OK;

    error_flag |= digital_out_init( &ctx->din, cfg->din );
    
    ctx->logic_zero = logic_zero;
    ctx->logic_one = logic_one;

    return error_flag;
}

err_t c2x4rgb_default_cfg ( c2x4rgb_t *ctx ) 
{
    err_t error_flag = C2X4RGB_OK;
    c2x4rgb_set_leds_intensity ( ctx, C2X4RGB_LED_BRIGHTNESS_DEFAULT, C2X4RGB_LED_CURRENT_GAIN_DEFAULT );
    c2x4rgb_set_leds_color ( ctx, C2X4RGB_COLOR_BLACK );
    error_flag |= c2x4rgb_write_led_matrix ( ctx );
    return error_flag;
}

err_t c2x4rgb_write_leds ( c2x4rgb_t *ctx, c2x4rgb_led_t *leds, uint8_t num_leds )
{
    if ( num_leds > C2X4RGB_NUM_LEDS )
    {
        return C2X4RGB_ERROR;
    }
    uint8_t data_buf[ C2X4RGB_NUM_LEDS * 6 ] = { 0 };
    uint16_t color_12bit = 0;
    uint8_t bit_cnt = 0;
    uint8_t byte_cnt = 0;
    uint8_t led_cnt = 0;
    for ( led_cnt = C2X4RGB_LED_0; led_cnt < num_leds; led_cnt++ )
    {
        color_12bit = ( uint16_t ) leds[ led_cnt ].red * ( ( leds[ led_cnt ].brightness % 16 ) + 1 );
        data_buf[ 0 + led_cnt * 6 ] = ( leds[ led_cnt ].current_gain << 4 ) | ( ( color_12bit >> 8 ) & 0x0F );
        data_buf[ 1 + led_cnt * 6 ] = ( uint8_t ) ( color_12bit & 0xFF );
        color_12bit = ( uint16_t ) leds[ led_cnt ].green * ( ( leds[ led_cnt ].brightness % 16 ) + 1 );
        data_buf[ 2 + led_cnt * 6 ] = ( leds[ led_cnt ].current_gain << 4 ) | ( ( color_12bit >> 8 ) & 0x0F );
        data_buf[ 3 + led_cnt * 6 ] = ( uint8_t ) ( color_12bit & 0xFF );
        color_12bit = ( uint16_t ) leds[ led_cnt ].blue * ( ( leds[ led_cnt ].brightness % 16 ) + 1 );
        data_buf[ 4 + led_cnt * 6 ] = ( leds[ led_cnt ].current_gain << 4 ) | ( ( color_12bit >> 8 ) & 0x0F );
        data_buf[ 5 + led_cnt * 6 ] = ( uint8_t ) ( color_12bit & 0xFF );
    }
    for ( byte_cnt = 0; byte_cnt < ( C2X4RGB_NUM_LEDS * 6 ); byte_cnt++ )
    {
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( data_buf[ byte_cnt ] & ( 0x80 >> bit_cnt ) )
            {
                ctx->logic_one( );
            }
            else
            {
                ctx->logic_zero( );
            }
        }
    }
    Delay_60us ( );
    return C2X4RGB_OK;
}

err_t c2x4rgb_write_led_matrix ( c2x4rgb_t *ctx )
{
    return c2x4rgb_write_leds ( ctx, ctx->led_matrix, C2X4RGB_NUM_LEDS );
}

void c2x4rgb_set_led_intensity ( c2x4rgb_t *ctx, uint8_t led_num, uint8_t brightness, uint8_t gain )
{
    ctx->led_matrix[ led_num % C2X4RGB_NUM_LEDS ].brightness = brightness % ( C2X4RGB_LED_BRIGHTNESS_MAX + 1 );
    ctx->led_matrix[ led_num % C2X4RGB_NUM_LEDS ].current_gain = gain % ( C2X4RGB_LED_CURRENT_GAIN_MAX + 1 );
}

void c2x4rgb_set_leds_intensity ( c2x4rgb_t *ctx, uint8_t brightness, uint8_t gain )
{
    for ( uint8_t led_cnt = C2X4RGB_LED_0; led_cnt <= C2X4RGB_LED_7; led_cnt++ )
    {
        c2x4rgb_set_led_intensity ( ctx, led_cnt, brightness, gain );
    }
}

void c2x4rgb_set_led_color ( c2x4rgb_t *ctx, uint8_t led_num, uint32_t rgb )
{
    ctx->led_matrix[ led_num % C2X4RGB_NUM_LEDS ].red = ( uint8_t ) ( ( rgb >> 16 ) & 0xFF );
    ctx->led_matrix[ led_num % C2X4RGB_NUM_LEDS ].green = ( uint8_t ) ( ( rgb >> 8 ) & 0xFF );
    ctx->led_matrix[ led_num % C2X4RGB_NUM_LEDS ].blue = ( uint8_t ) ( rgb & 0xFF );
}

void c2x4rgb_set_leds_color ( c2x4rgb_t *ctx, uint32_t rgb )
{
    for ( uint8_t led_cnt = C2X4RGB_LED_0; led_cnt <= C2X4RGB_LED_7; led_cnt++ )
    {
        c2x4rgb_set_led_color ( ctx, led_cnt, rgb );
    }
}

// ------------------------------------------------------------------------- END
