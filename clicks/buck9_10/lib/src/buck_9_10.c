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

#include "buck_9_10.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck_9_10_cfg_setup ( buck_9_10_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
}

BUCK_9_10_RETVAL buck_9_10_init ( buck_9_10_t *ctx, buck_9_10_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    return BUCK_9_10_OK;
}

void buck_9_10_default_cfg ( buck_9_10_t *ctx )
{
    // Click default configuration 

    buck9_set_device_mode ( ctx, BUCK_9_10_DEVICE_ENABLE );
}

void buck9_set_device_mode ( buck_9_10_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->en, mode );
}

// ------------------------------------------------------------------------- END

