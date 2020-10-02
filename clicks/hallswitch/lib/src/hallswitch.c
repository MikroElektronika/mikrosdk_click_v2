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

#include "hallswitch.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallswitch_cfg_setup ( hallswitch_cfg_t *cfg )
{
    // Additional gpio pins  

    cfg->np   = HAL_PIN_NC;
    cfg->sp = HAL_PIN_NC;
}

HALLSWITCH_RETVAL hallswitch_init ( hallswitch_t *ctx, hallswitch_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->np, cfg->np );
    digital_out_init( &ctx->sp, cfg->sp );

    return HALLSWITCH_OK;
}

void hallswitch_set_npole ( hallswitch_t *ctx, uint8_t state )
{
     digital_out_write( &ctx->np, state );
}

void hallswitch_set_spole ( hallswitch_t *ctx, uint8_t state )
{
     digital_out_write( &ctx->sp, state );
}

// ------------------------------------------------------------------------- END

