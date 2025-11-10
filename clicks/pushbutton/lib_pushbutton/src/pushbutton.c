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
 * @file pushbutton.c
 * @brief Push Button Click Driver.
 */

#include "pushbutton.h"

void pushbutton_cfg_setup ( pushbutton_cfg_t *cfg ) 
{
    cfg->out = HAL_PIN_NC;
    cfg->clr = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t pushbutton_init ( pushbutton_t *ctx, pushbutton_cfg_t *cfg ) 
{
    err_t error_flag = PUSHBUTTON_OK;

    error_flag |= digital_out_init( &ctx->clr, cfg->clr );

    error_flag |= digital_in_init( &ctx->out, cfg->out );
    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    pushbutton_clear_output ( ctx );

    return error_flag;
}

void pushbutton_clear_output ( pushbutton_t *ctx )
{
    digital_out_low( &ctx->clr );
    Delay_100ms ( );
    digital_out_high( &ctx->clr );
}

uint8_t pushbutton_get_out_pin ( pushbutton_t *ctx )
{
    return digital_in_read( &ctx->out );
}

uint8_t pushbutton_get_int_pin ( pushbutton_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
