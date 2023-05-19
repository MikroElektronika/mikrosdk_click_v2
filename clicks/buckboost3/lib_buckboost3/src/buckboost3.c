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

#include "buckboost3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buckboost3_cfg_setup ( buckboost3_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->uv = HAL_PIN_NC;
}

BUCKBOOST3_RETVAL buckboost3_init ( buckboost3_t *ctx, buckboost3_cfg_t *cfg )
{
    // Output pins 
 
    digital_out_init ( &ctx->en, cfg->en );
  
    // Input pins

    digital_in_init ( &ctx->uv, cfg->uv );

    digital_out_low ( &ctx->en );
    Delay_100ms( );
    return BUCKBOOST3_OK;
}

void buckboost3_enable ( buckboost3_t *ctx, uint8_t state )
{
    if ( state == 0 || state == 1 )
    {
        digital_out_write( &ctx->en, state );
    }
}

uint8_t buckboost3_get_interrupt_state ( buckboost3_t *ctx )
{
    return digital_in_read( &ctx->uv );
}

// ------------------------------------------------------------------------- END

