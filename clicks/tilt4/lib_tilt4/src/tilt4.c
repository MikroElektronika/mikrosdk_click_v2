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
 * @file tilt4.c
 * @brief Tilt 4 Click Driver.
 */

#include "tilt4.h"

void tilt4_cfg_setup ( tilt4_cfg_t *cfg ) 
{
    cfg->led = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t tilt4_init ( tilt4_t *ctx, tilt4_cfg_t *cfg ) 
{
    err_t error_flag = TILT4_OK;

    error_flag |= digital_out_init( &ctx->led, cfg->led );

    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

uint8_t tilt4_read_int_state ( tilt4_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void tilt4_set_led_state ( tilt4_t *ctx, uint8_t pin_state )
{
    if ( TILT4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->led );
    }
    else
    {
        digital_out_low( &ctx->led );
    }
}

// ------------------------------------------------------------------------- END
