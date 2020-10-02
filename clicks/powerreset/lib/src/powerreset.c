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

#include "powerreset.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void powerreset_cfg_setup ( powerreset_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->sta = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
}

POWERRESET_RETVAL powerreset_init ( powerreset_t *ctx, powerreset_cfg_t *cfg )
{

    // Input pins

    digital_in_init( &ctx->sta, cfg->sta );
    digital_in_init( &ctx->rst, cfg->rst );

    return POWERRESET_OK;
}

powerreset_state_t powerreset_get_pwr( powerreset_t *ctx )
{
    if ( digital_in_read( &ctx->sta ) )
    {
        return POWERRESET_ACTIVE;
    }
    else
    {
        return POWERRESET_INACTIVE;
    }
}

powerreset_state_t powerreset_get_rst( powerreset_t *ctx )
{
    if ( digital_in_read( &ctx->rst ) )
    {
        return POWERRESET_ACTIVE;
    }
    else
    {
        return POWERRESET_INACTIVE;
    }
}

// ------------------------------------------------------------------------- END
