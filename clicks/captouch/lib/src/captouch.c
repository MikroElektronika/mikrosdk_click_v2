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

#include "captouch.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void captouch_cfg_setup ( captouch_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->mod = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

CAPTOUCH_RETVAL captouch_init ( captouch_t *ctx, captouch_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->mod, cfg->mod );

    // Input pins

    digital_in_init( &ctx->out, cfg->out );

    return CAPTOUCH_OK;
}

void captouch_default_cfg ( captouch_t *ctx )
{
    // Click default configuration

    captouch_set_mode( ctx, CAPTOUCH_FAST_MODE );
}

void captouch_set_mode( captouch_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->mod, mode );
}

uint8_t captouch_get_touch( captouch_t *ctx )
{
    return digital_in_read( &ctx->out );
}

// ------------------------------------------------------------------------- END

