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

#include "optoencoder2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void optoencoder2_cfg_setup ( optoencoder2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg-> b = HAL_PIN_NC;
    cfg->a = HAL_PIN_NC;
}

OPTOENCODER2_RETVAL optoencoder2_init ( optoencoder2_t *ctx, optoencoder2_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->b, cfg->b );
    digital_in_init( &ctx->a, cfg->a );

    return OPTOENCODER2_OK;
}

uint8_t optoencoder2_pwm_get ( optoencoder2_t *ctx )
{
    return digital_in_read( &ctx->b );
}

uint8_t optoencoder2_int_get ( optoencoder2_t *ctx )
{
    return digital_in_read( &ctx->a );
}

int32_t optoencoder2_get_position ( optoencoder2_t *ctx )
{
    return ctx->position_counter;
}

void optoencoder2_zero_counter ( optoencoder2_t *ctx )
{
    ctx->position_counter = 0;
}

uint8_t optoencoder2_isr ( optoencoder2_t *ctx, uint8_t n_cycles )
{
    ctx->timeout_counter = 0;
    while ( ( optoencoder2_int_get( ctx ) != 0 ) && ( ctx->timeout_counter < n_cycles ) ) 
    {
        ctx->timeout_counter++;
    }
    if ( ctx->timeout_counter < n_cycles )
    {
        ctx->timeout_counter = 0;
        while ( ( optoencoder2_int_get( ctx ) != 1 ) && ( ctx->timeout_counter < n_cycles ) ) 
        {
            ctx->timeout_counter++;
        }
        if ( ctx->timeout_counter < n_cycles )
        {
            if ( optoencoder2_pwm_get( ctx ) == 0 ) 
            { 
                ctx->position_counter += 1; 
                return 0; 
            }
            else 
            { 
                ctx->position_counter -= 1; 
                return 0; 
            }
        } 
        else
        {
            return 1;
        }
    } 
    else 
    {
        return 1;
    }
}

// ------------------------------------------------------------------------- END

