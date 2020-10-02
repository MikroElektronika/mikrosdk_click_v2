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

#include "opto.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void opto_cfg_setup ( opto_cfg_t *cfg )
{

    cfg->in4   = HAL_PIN_NC;
    cfg->in3   = HAL_PIN_NC;
    cfg->in2   = HAL_PIN_NC;
    cfg->in1   = HAL_PIN_NC;
}

OPTO_RETVAL opto_init ( opto_t *ctx, opto_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->in4, cfg->in4 );
    digital_in_init( &ctx->in3, cfg->in3 );
    digital_in_init( &ctx->in2, cfg->in2 );
    digital_in_init( &ctx->in1, cfg->in1 );
    
    return OPTO_OK;
}

uint8_t opto_check_out1( opto_t *ctx )
{
    return digital_in_read( &ctx->in1 );
}

uint8_t opto_check_out2( opto_t *ctx )
{
    return digital_in_read( &ctx->in2 );
}

uint8_t opto_check_out3( opto_t *ctx )
{
    return digital_in_read( &ctx->in3 );
}

uint8_t opto_check_out4( opto_t *ctx )
{
    return digital_in_read( &ctx->in4 );
}


// ------------------------------------------------------------------------- END

