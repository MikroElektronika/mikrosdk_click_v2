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

    cfg->ou1   = HAL_PIN_NC;
    cfg->ou2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

OPTO3_RETVAL opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->ou1, cfg->ou1 );
    digital_out_init( &ctx->ou2, cfg->ou2 );

    // Input pins

    digital_in_init( &ctx->in1, cfg->in1 );
    digital_in_init( &ctx->in2, cfg->in2 );
    
    return OPTO3_OK;
}

OPTO3_STATE opto3_get_in1 ( opto3_t *ctx )
{
    uint8_t tmp;

    tmp = digital_in_read ( &ctx->in1 );
    
    if ( tmp == 1 )
    {
        return OPTO3_HIGH;
    }
    else
    {
        return OPTO3_LOW;
    }
}

OPTO3_STATE opto3_get_in2 ( opto3_t *ctx )
{
    uint8_t tmp;

    tmp = digital_in_read ( &ctx->in2 );

    if ( tmp == 1 )
    {
        return OPTO3_HIGH;
    }
    else
    {
        return OPTO3_LOW;
    }
}

void opto3_set_out1 ( opto3_t *ctx, OPTO3_SWITCH state )
{
    digital_out_write( &ctx->ou1, state );
}

void opto3_set_out2 ( opto3_t *ctx, OPTO3_SWITCH state )
{
    digital_out_write( &ctx->ou2, state );
}

// ------------------------------------------------------------------------- END

