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

#include "capextend3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void capextend3_cfg_setup ( capextend3_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->to0   = HAL_PIN_NC;
    cfg->to1 = HAL_PIN_NC;
    cfg->to2   = HAL_PIN_NC;
    cfg->to3 = HAL_PIN_NC;
    cfg->to4 = HAL_PIN_NC;
}

CAPEXTEND3_RETVAL capextend3_init ( capextend3_t *ctx, capextend3_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->to0, cfg->to0 );
    digital_in_init( &ctx->to1, cfg->to1 );
    digital_in_init( &ctx->to2, cfg->to2 );
    digital_in_init( &ctx->to3, cfg->to3 );
    digital_in_init( &ctx->to4, cfg->to4 );

    return CAPEXTEND3_OK;
}

uint8_t capextend3_touch_0 ( capextend3_t *ctx )
{
    return digital_in_read( &ctx->to0 );
}

uint8_t capextend3_touch_1 ( capextend3_t *ctx )
{
    return digital_in_read( &ctx->to1 );
}

uint8_t capextend3_touch_2 ( capextend3_t *ctx )
{
    return digital_in_read( &ctx->to2 );
}

uint8_t capextend3_touch_3 ( capextend3_t *ctx )
{
    return digital_in_read( &ctx->to4 );
}

uint8_t capextend3_touch_4 ( capextend3_t *ctx )
{
    return digital_in_read( &ctx->to3 );
}

// ------------------------------------------------------------------------- END

