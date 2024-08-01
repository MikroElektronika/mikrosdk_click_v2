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
 * @file button2.c
 * @brief Button 2 Click Driver.
 */

#include "button2.h"

void button2_cfg_setup ( button2_cfg_t *cfg ) 
{
    cfg->led = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t button2_init ( button2_t *ctx, button2_cfg_t *cfg ) 
{
    err_t error_flag = BUTTON2_OK;

    error_flag |= digital_out_init( &ctx->led, cfg->led );

    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_low ( &ctx->led );

    return error_flag;
}

void button2_enable_led ( button2_t *ctx ) 
{
    digital_out_high( &ctx->led );
}

void button2_disable_led ( button2_t *ctx ) 
{
    digital_out_low( &ctx->led );
}

void button2_toggle_led ( button2_t *ctx ) 
{
    digital_out_toggle( &ctx->led );
}

uint8_t button2_get_int_pin ( button2_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
