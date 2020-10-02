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

#include "c2x30wamp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c2x30wamp_cfg_setup ( c2x30wamp_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->mt   = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;
}

C2X30WAMP_RETVAL c2x30wamp_init ( c2x30wamp_t *ctx, c2x30wamp_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->mt, cfg->mt );

    // Input pins

    digital_in_init( &ctx->flt, cfg->flt );

    return C2X30WAMP_OK;
}

void c2x30wamp_enable ( c2x30wamp_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->rst );

    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void c2x30wamp_mute ( c2x30wamp_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->mt );
    }
    else
    {
        digital_out_low( &ctx->mt );
    }
}

uint8_t c2x30wamp_check_diagnostic ( c2x30wamp_t *ctx )
{
    if ( digital_in_read( &ctx->flt ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END

