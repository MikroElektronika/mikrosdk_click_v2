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

#include "buck.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck_cfg_setup ( buck_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->a0 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;
}

BUCK_RETVAL buck_init ( buck_t *ctx, buck_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->a1, cfg->a1 );

    // Input pins

    digital_in_init( &ctx->pg, cfg->pg );
    
    return BUCK_OK;
}

void buck_default_cfg ( buck_t *ctx )
{
    // Click default configuration 

    buck_switch_frequency ( ctx, BUCK_FREQ_400KHz );
    buck_set_mode ( ctx, BUCK_DEVICE_ENABLE );
}

void buck_device_reset ( buck_t *ctx )
{
    digital_out_write( &ctx->en, BUCK_DEVICE_DISABLE );
    Delay_100ms();
    digital_out_write( &ctx->en, BUCK_DEVICE_ENABLE );
    Delay_100ms();
}

void buck_set_mode ( buck_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->en, mode );
}

uint8_t buck_get_power_good ( buck_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

void buck_set_multiplexer_state ( buck_t *ctx, uint8_t mux, uint8_t state )
{
    if ( mux == BUCK_SET_MULTIPLEXER_A0 )
    {
        digital_out_write( &ctx->a0, state );
    }
    else
    {
        digital_out_write( &ctx->a1, state );
    }
}

void buck_switch_frequency ( buck_t *ctx, uint8_t frequency )
{
    if ( frequency == BUCK_FREQ_400KHz )
    {
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A0, 0 );
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A1, 0 );
    }
     
    if ( frequency == BUCK_FREQ_1200KHz )
    {
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A0, 0 );
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A1, 1 );
    }
     
    if ( frequency == BUCK_FREQ_800KHz )
    {
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A0, 1 );
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A1, 0 );
    }
     
    if ( frequency == BUCK_FREQ_1600KHz )
    {
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A0, 1 );
        buck_set_multiplexer_state( ctx, BUCK_SET_MULTIPLEXER_A1, 1 );
    }
}

// ------------------------------------------------------------------------- END

