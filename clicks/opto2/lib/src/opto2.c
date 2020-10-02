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

#include "opto2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void opto2_cfg_setup ( opto2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in4   = HAL_PIN_NC;
    cfg->in3 = HAL_PIN_NC;
    cfg->in2   = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
}

OPTO2_RETVAL opto2_init ( opto2_t *ctx, opto2_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->in4, cfg->in4 );
    digital_in_init( &ctx->in3, cfg->in3 );
    digital_in_init( &ctx->in2, cfg->in2 );
    digital_in_init( &ctx->in1, cfg->in1 );

    return OPTO2_OK;
}

uint8_t opto2_check_out1 ( opto2_t *ctx )
{   
    uint8_t state;

    state = digital_in_read ( &ctx->in1 );
    return state;
}

uint8_t opto2_check_out2 ( opto2_t *ctx )
{
    uint8_t state;

    state = digital_in_read ( &ctx->in2 );
    return state;
}

uint8_t opto2_check_out3 ( opto2_t *ctx )
{
    uint8_t state;
    
    state = digital_in_read ( &ctx->in3 );
    return state;
}

uint8_t opto2_check_out4 ( opto2_t *ctx )
{
    uint8_t state;
    
    state = digital_in_read ( &ctx->in4 );
    return state;
}

// ------------------------------------------------------------------------- END

