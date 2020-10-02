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

#include "powermux.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void powermux_cfg_setup ( powermux_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->d0 = HAL_PIN_NC;
    cfg->d1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

POWERMUX_RETVAL powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->d0, cfg->d0 );
    digital_out_init( &ctx->d1, cfg->d1 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return POWERMUX_OK;
}

// Set D0 state function
void powermux_set_d0 ( powermux_t *ctx, uint8_t state )
{
    if ( state == POWERMUX_PIN_STATE_1 )
    {
        digital_out_write( &ctx->d0, POWERMUX_PIN_STATE_1 );
    }
    else
    {
        digital_out_write( &ctx->d0, POWERMUX_PIN_STATE_0 );
    }
}

// Set D1 state function
void powermux_set_d1 ( powermux_t *ctx, uint8_t state )
{
    if ( state == POWERMUX_PIN_STATE_1 )
    {
        digital_out_write( &ctx->d1, POWERMUX_PIN_STATE_1 );
    }
    else
    {
        digital_out_write( &ctx->d1, POWERMUX_PIN_STATE_0 );
    }
}

// Check INT pin state function
uint8_t powermux_int_pin_state ( powermux_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// Output From Input Channel 2 function
void powermux_output_input_ch_2 ( powermux_t *ctx )
{
    powermux_set_d0( ctx, POWERMUX_PIN_STATE_0 );
    powermux_set_d1( ctx, POWERMUX_PIN_STATE_0 );
}

// Output From Input Channel 1 function
void powermux_output_input_ch_1 ( powermux_t *ctx )
{
    powermux_set_d0( ctx, POWERMUX_PIN_STATE_0 );
    powermux_set_d1( ctx, POWERMUX_PIN_STATE_1 );
}

// Automatic Output Channel Selection function
void powermux_auto_sel_input_ch ( powermux_t *ctx )
{
    powermux_set_d0( ctx, POWERMUX_PIN_STATE_1 );
    powermux_set_d1( ctx, POWERMUX_PIN_STATE_0 );
}

// No Output function
void powermux_no_output ( powermux_t *ctx )
{
    powermux_set_d0( ctx, POWERMUX_PIN_STATE_1 );
    powermux_set_d1( ctx, POWERMUX_PIN_STATE_1 );
}


// ------------------------------------------------------------------------- END

