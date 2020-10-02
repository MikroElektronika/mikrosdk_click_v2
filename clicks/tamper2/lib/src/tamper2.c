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

#include "tamper2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tamper2_cfg_setup ( tamper2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->ncl   = HAL_PIN_NC;
    cfg->nop = HAL_PIN_NC;
}

TAMPER2_RETVAL tamper2_init ( tamper2_t *ctx, tamper2_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->ncl, cfg->ncl );
    digital_in_init( &ctx->nop, cfg->nop );

    return TAMPER2_OK;
}

uint8_t tamper2_get_off_state ( tamper2_t *ctx )
{
    return  digital_in_read( &ctx->ncl );
}

uint8_t tamper2_get_on_state ( tamper2_t *ctx )
{
    return  digital_in_read( &ctx->nop );
}

// ------------------------------------------------------------------------- END

