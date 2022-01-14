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
 * @file terminal2.c
 * @brief Terminal 2 Click Driver.
 */

#include "terminal2.h"

void terminal2_cfg_setup ( terminal2_cfg_t *cfg ) 
{
    cfg->scl    = HAL_PIN_NC;
    cfg->sda    = HAL_PIN_NC;
    cfg->sck    = HAL_PIN_NC;
    cfg->miso   = HAL_PIN_NC;
    cfg->mosi   = HAL_PIN_NC;
    cfg->cs     = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->an      = HAL_PIN_NC;
    cfg->rst     = HAL_PIN_NC;
    cfg->pwm     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t terminal2_init ( terminal2_t *ctx, terminal2_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->scl, cfg->scl );
    return_flag |= digital_out_init( &ctx->sda, cfg->sda );
    return_flag |= digital_out_init( &ctx->sck, cfg->sck );
    return_flag |= digital_out_init( &ctx->miso, cfg->miso );
    return_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
    return_flag |= digital_out_init( &ctx->cs, cfg->cs );
    return_flag |= digital_out_init( &ctx->tx_pin, cfg->tx_pin );
    return_flag |= digital_out_init( &ctx->rx_pin, cfg->rx_pin );
    return_flag |= digital_out_init( &ctx->an, cfg->an );
    return_flag |= digital_out_init( &ctx->rst, cfg->rst );
    return_flag |= digital_out_init( &ctx->pwm, cfg->pwm );
    return_flag |= digital_out_init( &ctx->int_pin, cfg->int_pin );

    return return_flag;
}

void terminal2_set_pin_high ( digital_out_t *pin ) 
{
    digital_out_high( pin );
}

void terminal2_set_pin_low ( digital_out_t *pin )
{
    digital_out_low( pin );
}

void terminal2_toggle_pin ( digital_out_t *pin )
{
    digital_out_toggle( pin );
}

void terminal2_set_all_pins_high ( terminal2_t *ctx )
{
    digital_out_high( &ctx->scl );
    digital_out_high( &ctx->sda );
    digital_out_high( &ctx->sck );
    digital_out_high( &ctx->miso );
    digital_out_high( &ctx->mosi );
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->tx_pin );
    digital_out_high( &ctx->rx_pin );
    digital_out_high( &ctx->an );
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->pwm );
    digital_out_high( &ctx->int_pin );
}

void terminal2_set_all_pins_low ( terminal2_t *ctx )
{
    digital_out_low( &ctx->scl );
    digital_out_low( &ctx->sda );
    digital_out_low( &ctx->sck );
    digital_out_low( &ctx->miso );
    digital_out_low( &ctx->mosi );
    digital_out_low( &ctx->cs );
    digital_out_low( &ctx->tx_pin );
    digital_out_low( &ctx->rx_pin );
    digital_out_low( &ctx->an );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->pwm );
    digital_out_low( &ctx->int_pin );
}

void terminal2_toggle_all_pins ( terminal2_t *ctx )
{
    digital_out_toggle( &ctx->scl );
    digital_out_toggle( &ctx->sda );
    digital_out_toggle( &ctx->sck );
    digital_out_toggle( &ctx->miso );
    digital_out_toggle( &ctx->mosi );
    digital_out_toggle( &ctx->cs );
    digital_out_toggle( &ctx->tx_pin );
    digital_out_toggle( &ctx->rx_pin );
    digital_out_toggle( &ctx->an );
    digital_out_toggle( &ctx->rst );
    digital_out_toggle( &ctx->pwm );
    digital_out_toggle( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
