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

#include "mcp73871.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mcp73871_cfg_setup ( mcp73871_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->pg2   = HAL_PIN_NC;
    cfg->ce   = HAL_PIN_NC;
    cfg->te = HAL_PIN_NC;
}

MCP73871_RETVAL mcp73871_init ( mcp73871_t *ctx, mcp73871_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->pg2, cfg->pg2 );
    digital_out_init( &ctx->ce, cfg->ce );
    digital_out_init( &ctx->te, cfg->te );

    mcp73871_enable_pin_control( ctx, 1 );

    return MCP73871_OK;
}

void mcp73871_enable_pin_control ( mcp73871_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->ce, pin_state );
}

void mcp73871_prog_pin_control ( mcp73871_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->pg2, pin_state );
}

void mcp73871_timer_pin_control ( mcp73871_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->te, pin_state );
}

// ------------------------------------------------------------------------- END

