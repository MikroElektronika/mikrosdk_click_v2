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

#include "pll.h"
// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pll_cfg_setup ( pll_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->s1   = HAL_PIN_NC;
    cfg->s0 = HAL_PIN_NC;
    cfg->oe   = HAL_PIN_NC;
    cfg->ick = HAL_PIN_NC;
}

PLL_RETVAL pll_init ( pll_t *ctx, pll_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->s1, cfg->s1 );
    digital_out_init( &ctx->s0, cfg->s0 );
    digital_out_init( &ctx->oe, cfg->oe );

    // Input pins

    digital_in_init( &ctx->ick, cfg->ick );

    return PLL_OK;
}

void pll_set_clock_output ( pll_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->oe, mode );
}

void pll_set_pll_4x ( pll_t *ctx )
{
    digital_out_low( &ctx->s1 );
    digital_out_low( &ctx->s0 );
}

void pll_set_pll_5x ( pll_t *ctx )
{
    digital_out_low( &ctx->s1 );
    digital_out_high( &ctx->s0 );
}

void pll_set_pll_6x ( pll_t *ctx )
{
    digital_out_high( &ctx->s1 );
    digital_out_low( &ctx->s0 );
}

void pll_set_pll_8x ( pll_t *ctx )
{
    digital_out_high( &ctx->s1 );
    digital_out_high( &ctx->s0 );
}

void pll_set_pll_3x ( pll_t *ctx )
{
    digital_out_high( &ctx->s1 );
}

void pll_set_pll_3_125x ( pll_t *ctx )
{
    digital_out_high( &ctx->s0 );
}

void pll_set_pll_6_25x ( pll_t *ctx )
{
    digital_out_low( &ctx->s0 );
}

void pll_set_pll_5_3125x ( pll_t *ctx )
{
    digital_out_low( &ctx->s1 );
}

// ------------------------------------------------------------------------- END

