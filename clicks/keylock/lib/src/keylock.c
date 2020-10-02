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

#include "keylock.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void keylock_cfg_setup ( keylock_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->out1 = HAL_PIN_NC;
    cfg->out2 = HAL_PIN_NC;
    cfg->out3 = HAL_PIN_NC;
}

KEYLOCK_RETVAL keylock_init ( keylock_t *ctx, keylock_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->out1, cfg->out1 );
    digital_in_init( &ctx->out2, cfg->out2 );
    digital_in_init( &ctx->out3, cfg->out3 );

    return KEYLOCK_OK;
}

uint8_t keylock_check_pin ( keylock_t *ctx, uint8_t pin )
{
    if ( pin == 1 )
    {
        return digital_in_read( &ctx->out1 );
    }
    else if ( pin == 2 )
    {
        return digital_in_read( &ctx->out2 );
    }
     else if ( pin == 3 )
    {
        return digital_in_read( &ctx->out3 );
    }
    else
    {
        return KEYLOCK_ERROR_FLAG;
    }
}

uint8_t keylock_get_position ( keylock_t *ctx )
{
    uint8_t pos1;
    uint8_t pos2;
    uint8_t pos3;

    pos1 = keylock_check_pin( ctx, 1 );
    pos2 = keylock_check_pin( ctx, 2 );
    pos3 = keylock_check_pin( ctx, 3 );

    if ( pos1 == 1 )
    {
        return KEYLOCK_KEY_POS_1;
    }
    else if ( pos2 == 1 )
    {
        return KEYLOCK_KEY_POS_2;
    }
    else if ( pos3 == 1 )
    {
        return KEYLOCK_KEY_POS_3;
    }
}

uint8_t keylock_check_an_state ( keylock_t *ctx )
{
    return digital_in_read( &ctx->out1 );
}

uint8_t keylock_check_pwm_state ( keylock_t *ctx )
{
    return digital_in_read( &ctx->out2 );
}

uint8_t keylock_check_int_state ( keylock_t *ctx )
{
    return digital_in_read( &ctx->out3 );
}

// ------------------------------------------------------------------------- END

