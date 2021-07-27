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

#include "dcmotor14.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor14_cfg_setup ( dcmotor14_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

DCMOTOR14_RETVAL dcmotor14_init ( dcmotor14_t *ctx, dcmotor14_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );

    return DCMOTOR14_OK;
}

void dcmotor14_set_an_state ( dcmotor14_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in1, state );
}

void dcmotor14_set_rst_state ( dcmotor14_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in2, state );
}

void dcmotor14_stop ( dcmotor14_t *ctx )
{
    digital_out_write( &ctx->in1, DCMOTOR14_LOW );
   
    digital_out_write( &ctx->in2, DCMOTOR14_LOW );
}

void dcmotor14_forward ( dcmotor14_t *ctx )
{
    digital_out_write( &ctx->in1, DCMOTOR14_HIGH );
    
    digital_out_write( &ctx->in2, DCMOTOR14_LOW );
}

void dcmotor14_reverse ( dcmotor14_t *ctx )
{
    digital_out_write( &ctx->in1, DCMOTOR14_LOW );

    digital_out_write( &ctx->in2, DCMOTOR14_HIGH );
}

void dcmotor14_brake ( dcmotor14_t *ctx )
{
    digital_out_write( &ctx->in1, DCMOTOR14_HIGH );

    digital_out_write( &ctx->in2, DCMOTOR14_HIGH );
}

// ------------------------------------------------------------------------- END

