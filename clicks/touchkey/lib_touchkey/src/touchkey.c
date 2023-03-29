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

#include "touchkey.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void touchkey_cfg_setup ( touchkey_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->b = HAL_PIN_NC;
    cfg->a = HAL_PIN_NC;
    cfg->c = HAL_PIN_NC;
    cfg->d = HAL_PIN_NC;
}

TOUCHKEY_RETVAL touchkey_init ( touchkey_t *ctx, touchkey_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->b, cfg->b );
    digital_in_init( &ctx->a, cfg->a );
    digital_in_init( &ctx->c, cfg->c );
    digital_in_init( &ctx->d, cfg->d );
    
    return TOUCHKEY_OK;
}

uint8_t touchkey_a ( touchkey_t *ctx )
{
    return digital_in_read( &ctx->a );
}

uint8_t touchkey_b ( touchkey_t *ctx )
{
    return digital_in_read( &ctx->b );
}

uint8_t touchkey_c ( touchkey_t *ctx )
{
    return digital_in_read( &ctx->c );
}

uint8_t touchkey_d ( touchkey_t *ctx )
{
    return digital_in_read( &ctx->d );
}

// ------------------------------------------------------------------------- END

