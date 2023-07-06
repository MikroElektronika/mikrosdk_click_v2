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
 * @file usbmux.c
 * @brief USB MUX Click Driver.
 */

#include "usbmux.h"

void usbmux_cfg_setup ( usbmux_cfg_t *cfg ) 
{
    cfg->oe = HAL_PIN_NC;
    cfg->sel = HAL_PIN_NC;
}

err_t usbmux_init ( usbmux_t *ctx, usbmux_cfg_t *cfg ) 
{
    err_t error_flag = USBMUX_OK;

    error_flag |= digital_out_init( &ctx->oe, cfg->oe );
    error_flag |= digital_out_init( &ctx->sel, cfg->sel );

    return error_flag;
}

void usbmux_default_cfg ( usbmux_t *ctx ) 
{
    usbmux_disable_output( ctx );
    usbmux_set_output( ctx, USBMUX_USB1_SELECT );
}

void usbmux_set_oe_pin ( usbmux_t *ctx, uint8_t pin_state )
{
    if ( USBMUX_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->oe );
    }
    else
    {
        digital_out_low( &ctx->oe );
    }
}

void usbmux_set_sel_pin ( usbmux_t *ctx, uint8_t pin_state )
{
    if ( USBMUX_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->sel );
    }
    else
    {
        digital_out_low( &ctx->sel );
    }
}

void usbmux_enable_output ( usbmux_t *ctx )
{
    usbmux_set_oe_pin( ctx, USBMUX_PIN_STATE_LOW );
}

void usbmux_disable_output ( usbmux_t *ctx )
{
    usbmux_set_oe_pin( ctx, USBMUX_PIN_STATE_HIGH );
}

void usbmux_set_output ( usbmux_t *ctx, uint8_t out_sel )
{
    if ( USBMUX_USB1_SELECT == out_sel )
    {
        usbmux_set_sel_pin( ctx, USBMUX_PIN_STATE_LOW );
    }
    else
    {
        usbmux_set_sel_pin( ctx, USBMUX_PIN_STATE_HIGH );
    }
}

// ------------------------------------------------------------------------- END
