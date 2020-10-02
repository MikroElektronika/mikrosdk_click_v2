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

#include "audioamp6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp6_cfg_setup ( audioamp6_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->mds = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->gs  = HAL_PIN_NC;
}

AUDIOAMP6_RETVAL audioamp6_init ( audioamp6_t *ctx, audioamp6_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->mds, cfg->mds );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->gs, cfg->gs );

    return AUDIOAMP6_OK;
}

void audioamp6_set_mode( audioamp6_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->mds, mode );
}

void audioamp6_set_output( audioamp6_t *ctx, uint8_t out )
{
    digital_out_write( &ctx->en, out );
}

void audioamp6_set_gain( audioamp6_t *ctx, uint8_t gain )
{
    digital_out_write( &ctx->gs, gain );

    // Reset 
    audioamp6_set_output( ctx, AUDIOAMP6_OUTPUT_DISABLE );
    Delay_1ms();
    audioamp6_set_output( ctx, AUDIOAMP6_OUTPUT_ENABLE );
}

// ------------------------------------------------------------------------- END

