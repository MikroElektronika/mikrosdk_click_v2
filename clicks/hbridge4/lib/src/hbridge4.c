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

#include "hbridge4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hbridge4_cfg_setup ( hbridge4_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->in4 = HAL_PIN_NC;
    cfg->in3 = HAL_PIN_NC;
}

HBRIDGE4_RETVAL hbridge4_init ( hbridge4_t *ctx, hbridge4_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->in4, cfg->in4 );
    digital_out_init( &ctx->in3, cfg->in3 );

    return HBRIDGE4_OK;
}


void hbridge4_enable ( hbridge4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

void hbridge4_set_in1 ( hbridge4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in1, state );
}

void hbridge4_set_in2 ( hbridge4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in2, state );
}

void hbridge4_set_in3 ( hbridge4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in3, state );
}

void hbridge4_set_in4 ( hbridge4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in4, state );
}

void hbridge4_motor_a_standby ( hbridge4_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

void hbridge4_motor_acw ( hbridge4_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

void hbridge4_motor_accw ( hbridge4_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_high( &ctx->in2 );
}

void hbridge4_motor_a_brake ( hbridge4_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_high( &ctx->in2 );
}

void hbridge4_motor_b_standby ( hbridge4_t *ctx )
{
    digital_out_low( &ctx->in3 );
    digital_out_low( &ctx->in4 );
}
 
void hbridge4_motor_bcw ( hbridge4_t *ctx )
{
    digital_out_high( &ctx->in3 );
    digital_out_low( &ctx->in4 );
}

void hbridge4_motor_bccw ( hbridge4_t *ctx )
{
    digital_out_low( &ctx->in3 );
    digital_out_high( &ctx->in4 );
}

void hbridge4_motor_b_brake ( hbridge4_t *ctx )
{
    digital_out_high( &ctx->in3 );
    digital_out_high( &ctx->in4 );
}

// ------------------------------------------------------------------------- END

