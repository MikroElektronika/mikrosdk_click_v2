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

#include "buck8.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck8_cfg_setup ( buck8_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->syn  = HAL_PIN_NC;
}

BUCK8_RETVAL buck8_init ( buck8_t *ctx, buck8_cfg_t *cfg )
{
    // Output pins 

    digital_in_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->syn, cfg->syn );

    digital_out_high( &ctx->syn );

    return BUCK8_OK;
}

void buck8_default_cfg ( buck8_t *ctx )
{
    // Click default configuration 

    buck8_set_power_mode ( ctx, BUCK8_MODE_ACTIVE );
}

void buck8_set_power_mode ( buck8_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->en, mode );
}

uint8_t buck8_get_state ( buck8_t *ctx )
{
    return digital_in_read( &ctx->rst );
}

// ------------------------------------------------------------------------- END

