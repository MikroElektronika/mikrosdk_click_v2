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
 * @file rgbring.c
 * @brief RGB Ring Click Driver.
 */

#include "rgbring.h"

void rgbring_cfg_setup ( rgbring_cfg_t *cfg ) 
{
    cfg->din = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t rgbring_init ( rgbring_t *ctx, rgbring_logic_t logic_zero, rgbring_logic_t logic_one, rgbring_cfg_t *cfg ) 
{
    err_t error_flag = RGBRING_OK;

    error_flag |= digital_out_init( &ctx->din, cfg->din );

    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    ctx->logic_zero = logic_zero;
    ctx->logic_one = logic_one;

    return error_flag;
}

err_t rgbring_default_cfg ( rgbring_t *ctx ) 
{
    err_t error_flag = RGBRING_OK;
    rgbring_set_leds_color ( ctx, RGBRING_COLOR_BLACK );
    Delay_100ms ( );
    error_flag |= rgbring_write_led_matrix ( ctx );
    return error_flag;
}

err_t rgbring_write_leds ( rgbring_t *ctx, rgbring_led_t *leds, uint8_t num_leds )
{
    if ( num_leds > RGBRING_NUM_LEDS )
    {
        return RGBRING_ERROR;
    }
    uint8_t data_buf[ RGBRING_NUM_LEDS * 3 ] = { 0 };
    uint8_t bit_cnt = 0;
    uint8_t byte_cnt = 0;
    uint8_t led_cnt = 0;
    for ( led_cnt = RGBRING_LED_0; led_cnt < num_leds; led_cnt++ )
    {
        data_buf[ 0 + led_cnt * 3 ] = leds[ led_cnt ].green;
        data_buf[ 1 + led_cnt * 3 ] = leds[ led_cnt ].red;
        data_buf[ 2 + led_cnt * 3 ] = leds[ led_cnt ].blue;
    }
    for ( byte_cnt = 0; byte_cnt < ( RGBRING_NUM_LEDS * 3 ); byte_cnt++ )
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
    Delay_80us ( );
    Delay_80us ( );
    Delay_60us ( );
    return RGBRING_OK;
}

err_t rgbring_write_led_matrix ( rgbring_t *ctx )
{
    return rgbring_write_leds ( ctx, ctx->led_matrix, RGBRING_NUM_LEDS );
}

void rgbring_set_led_color ( rgbring_t *ctx, uint8_t led_num, uint32_t rgb )
{
    ctx->led_matrix[ led_num % RGBRING_NUM_LEDS ].red = ( uint8_t ) ( ( rgb >> 16 ) & 0xFF );
    ctx->led_matrix[ led_num % RGBRING_NUM_LEDS ].green = ( uint8_t ) ( ( rgb >> 8 ) & 0xFF );
    ctx->led_matrix[ led_num % RGBRING_NUM_LEDS ].blue = ( uint8_t ) ( rgb & 0xFF );
}

void rgbring_set_leds_color ( rgbring_t *ctx, uint32_t rgb )
{
    for ( uint8_t led_cnt = RGBRING_LED_0; led_cnt <= RGBRING_LED_7; led_cnt++ )
    {
        rgbring_set_led_color ( ctx, led_cnt, rgb );
    }
}

uint8_t rgbring_get_int_pin ( rgbring_t *ctx ) 
{
    return ( RGBRING_BUTTON_PRESSED != digital_in_read( &ctx->int_pin ) );
}

// ------------------------------------------------------------------------- END
