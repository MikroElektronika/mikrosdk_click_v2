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

#include "opto3.h"

void opto3_cfg_setup ( opto3_cfg_t *cfg )
{
    // Additional gpio pins
    cfg->out1 = HAL_PIN_NC;
    cfg->out2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

err_t opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg )
{
    // Output pins 
    digital_out_init( &ctx->out1, cfg->out1 );
    digital_out_init( &ctx->out2, cfg->out2 );

    // Input pins
    digital_in_init( &ctx->in1, cfg->in1 );
    digital_in_init( &ctx->in2, cfg->in2 );
    
    digital_out_low( &ctx->out1 );
    digital_out_low( &ctx->out2 );
    
    return OPTO3_OK;
}

uint8_t opto3_get_in1 ( opto3_t *ctx )
{
    return digital_in_read ( &ctx->in1 );
}

uint8_t opto3_get_in2 ( opto3_t *ctx )
{
    return digital_in_read ( &ctx->in2 );
}

void opto3_set_out1 ( opto3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->out1, state );
}

void opto3_set_out2 ( opto3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->out2, state );
}

// ------------------------------------------------------------------------- END

