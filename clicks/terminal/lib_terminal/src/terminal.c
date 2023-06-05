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

#include "terminal.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void terminal_cfg_setup ( terminal_cfg_t *cfg )
{
    // Output pins

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

TERMINAL_RETVAL terminal_init ( terminal_t *ctx, terminal_cfg_t *cfg )
{
    // Communication pins 

    digital_out_init( &ctx->scl, cfg->scl );
    digital_out_init( &ctx->sda, cfg->sda );
    digital_out_init( &ctx->sck, cfg->sck );
    digital_out_init( &ctx->miso, cfg->miso );
    digital_out_init( &ctx->mosi, cfg->mosi );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->tx_pin, cfg->tx_pin );
    digital_out_init( &ctx->rx_pin, cfg->rx_pin );

    // Gpio pins

    digital_out_init( &ctx->an, cfg->an );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->pwm, cfg->pwm );
    digital_out_init( &ctx->int_pin, cfg->int_pin );

    return TERMINAL_OK;
}

void terminal_set_pin_high ( digital_out_t *pin ) 
{
    digital_out_high( pin );
}

void terminal_set_pin_low ( digital_out_t *pin )
{
    digital_out_low( pin );
}

// ------------------------------------------------------------------------- END

