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

#include "dcmotor6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor6_cfg_setup ( dcmotor6_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

DCMOTOR6_RETVAL dcmotor6_init ( dcmotor6_t *ctx, dcmotor6_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );

    // Example: Sets pin [high, low] 

    digital_out_low( &ctx->in1 );
    digital_out_low( &ctx->in2 );

    return DCMOTOR6_OK;
}

void dcmotor6_set_in1_pin ( dcmotor6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in1, state );
}

void dcmotor6_set_in2_pin ( dcmotor6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in2, state );
}

void dcmotor6_set_direction( dcmotor6_t *ctx, uint8_t dir )
{
    switch ( dir )
    {
        case DCMOTOR6_MOTOR_FORWARD:
        {
            digital_out_high( &ctx->in1 );
            digital_out_low( &ctx->in2 );
            break;
        }
        case DCMOTOR6_MOTOR_REVERSE:
        {
            digital_out_low( &ctx->in1 );
            digital_out_high( &ctx->in2 );
            break;
        }
        case DCMOTOR6_MOTOR_BRAKE:
        {
            digital_out_high( &ctx->in1 );
            digital_out_high( &ctx->in2 );
            break;
        }
        default:
        {
            digital_out_low( &ctx->in1 );
            digital_out_low( &ctx->in2 );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

