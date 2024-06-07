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
 * @file rotaryrgb.c
 * @brief Rotary RGB Click Driver.
 */

#include "rotaryrgb.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void rotaryrgb_cfg_setup ( rotaryrgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one ) 
{
    cfg->enb    = HAL_PIN_NC;
    cfg->do_pin = HAL_PIN_NC;
    cfg->di_pin = HAL_PIN_NC;
    cfg->ena    = HAL_PIN_NC;
    cfg->sw     = HAL_PIN_NC;

    cfg->logic_zero = logic_zero;
    cfg->logic_one = logic_one;
}

err_t rotaryrgb_init ( rotaryrgb_t *ctx, rotaryrgb_cfg_t *cfg ) 
{
    err_t err_flag = digital_out_init( &ctx->di_pin, cfg->di_pin );

    err_flag |= digital_in_init( &ctx->enb, cfg->enb );
    err_flag |= digital_in_init( &ctx->do_pin, cfg->do_pin );
    err_flag |= digital_in_init( &ctx->ena, cfg->ena );
    err_flag |= digital_in_init( &ctx->sw, cfg->sw );

    // Function pointers 
    ctx->logic_zero = cfg->logic_zero;
    ctx->logic_one = cfg->logic_one;

    return err_flag;
}

void rotaryrgb_set_led_data ( rotaryrgb_t *ctx, uint32_t data_in ) 
{
    uint32_t tmp = 1ul;
    for ( int8_t n_cnt = 23; n_cnt >= 0; n_cnt-- )
    {
        if ( 0 == ( data_in & ( tmp << n_cnt ) ) )
        {
            ctx->logic_zero( );
        }
        else
        {
            ctx->logic_one( );
        }
    }
}

void rotaryrgb_set_all_leds_data ( rotaryrgb_t *ctx, uint32_t *data_in ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        rotaryrgb_set_led_data( ctx, data_in[ n_cnt ] );
    }
}

void rotaryrgb_set_all_led_color ( rotaryrgb_t *ctx, uint32_t led_color ) 
{
    for ( uint8_t n_cnt = 0; n_cnt < 16; n_cnt++ )
    {
        rotaryrgb_set_led_data( ctx, led_color );
    }
}

err_t rotaryrgb_set_led_pos_color ( rotaryrgb_t *ctx, uint8_t led_pos, uint32_t led_color ) 
{
    err_t err_flag = ROTARYRGB_ERROR;
    if ( ( 16 >= led_pos ) && ( 1 <= led_pos ) )
    {
        err_flag = ROTARYRGB_OK;
        rotaryrgb_set_all_led_color( ctx, ROTARYRGB_COLOR_OFF );
        Delay_1ms( );
        for ( uint8_t n_cnt = 1; n_cnt <= led_pos; n_cnt++ )
        {
            rotaryrgb_set_led_data( ctx, led_color );  
        }
    }
    
    return err_flag;
}

uint32_t rotaryrgb_make_color ( uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness ) 
{
    uint32_t color = DUMMY;
    if ( brightness )
    {
         color = ( uint16_t ) ( green * brightness ) >> 8;
         color <<= 8;
         color |= ( uint16_t ) ( red * brightness ) >> 8;
         color <<= 8;
         color |= ( uint16_t ) ( blue * brightness ) >> 8;
    }
    else
    {
        color = green;
        color <<= 8;
        color |= red;
        color <<= 8;
        color |= blue;
    }
    return color;
}

void rotaryrgb_set_state_di_pin ( rotaryrgb_t *ctx ) 
{
   digital_out_high( &ctx->di_pin );
}

void rotaryrgb_di_pin_clear ( rotaryrgb_t *ctx ) 
{
   digital_out_low( &ctx->di_pin );
}

uint8_t rotaryrgb_get_state_do_pin ( rotaryrgb_t *ctx ) 
{
    return digital_in_read( &ctx->do_pin );
}

uint8_t rotaryrgb_get_state_switch ( rotaryrgb_t *ctx ) 
{
    return digital_in_read( &ctx->sw );
}

uint8_t rotaryrgb_get_state_ena ( rotaryrgb_t *ctx ) 
{
    return digital_in_read( &ctx->ena );
}

uint8_t rotaryrgb_get_state_enb ( rotaryrgb_t *ctx ) 
{
    return digital_in_read( &ctx->enb );
}

// ------------------------------------------------------------------------- END
