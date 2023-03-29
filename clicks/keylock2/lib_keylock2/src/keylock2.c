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

#include "keylock2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void keylock2_cfg_setup ( keylock2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in3 = HAL_PIN_NC;
}

KEYLOCK2_RETVAL keylock2_init ( keylock2_t *ctx, keylock2_cfg_t *cfg )
{

    // Input pins

    digital_in_init( &ctx->in1, cfg->in1 );
    digital_in_init( &ctx->in2, cfg->in2 );
    digital_in_init( &ctx->in3, cfg->in3 );

    return KEYLOCK2_OK;
}

uint8_t keylock2_get_pin_state ( keylock2_t *ctx, uint8_t pin )
{
    if ( pin == 1 )
    {
        return digital_in_read( &ctx->in1 );
    }
    else if ( pin == 2 )
    {
        return digital_in_read( &ctx->in2 );
    }

    return digital_in_read( &ctx->in3 );
}

uint8_t keylock2_get_position ( keylock2_t *ctx )
{
    uint8_t pos_1;
    uint8_t pos_2;
    uint8_t pos_3;
    
    pos_1 = keylock2_get_pin_state( ctx, KEYLOCK2_STATE_RST_PIN );
    pos_2 = keylock2_get_pin_state( ctx, KEYLOCK2_STATE_PWM_PIN );
    pos_3 = keylock2_get_pin_state( ctx, KEYLOCK2_STATE_INT_PIN );
    
    if ( ( pos_1 == 1 ) && ( pos_2 == 0 ) && ( pos_3 == 0 ) )
    {
        return KEYLOCK2_POSITION_1;
    }
    else if ( ( pos_1 == 0 ) && ( pos_2 == 1 ) && ( pos_3 == 0 ) )
    {
        return KEYLOCK2_POSITION_2;
    }
    else if ( ( pos_1 == 0 ) && ( pos_2 == 0 ) && ( pos_3 == 1 ) )
    {
        return KEYLOCK2_POSITION_3;
    }
}

// ------------------------------------------------------------------------- END

