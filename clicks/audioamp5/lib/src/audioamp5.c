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

#include "audioamp5.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void update_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp5_cfg_setup ( audioamp5_cfg_t *cfg )
{
    // Additional gpio pins
    
    cfg->mds = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->gs = HAL_PIN_NC;
}

AUDIOAMP5_RETVAL audioamp5_init ( audioamp5_t *ctx, audioamp5_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->mds, cfg->mds );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->gs, cfg->gs );

    return AUDIOAMP5_OK;
}

void audioamp5_default_cfg ( audioamp5_t *ctx )
{
    audioamp5_set_device_state( ctx, AUDIOAMP5_PWRUP_UNMUTE_OUTPUTS );
    audioamp5_gain_select( ctx, AUDIOAMP5_GAIN_20DB );
    audioamp5_mode_select( ctx, AUDIOAMP5_BD_MODE );
}

void audioamp5_set_device_state ( audioamp5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

void audioamp5_mode_select ( audioamp5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->mds, state );
}

void audioamp5_gain_select ( audioamp5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->gs, state );
}

void audioamp5_config_update ( audioamp5_t *ctx )
{
    audioamp5_set_device_state( ctx, AUDIOAMP5_SHDWN_MUTE_OUTPUTS );
    update_delay( );
    audioamp5_set_device_state( ctx, AUDIOAMP5_PWRUP_UNMUTE_OUTPUTS );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void update_delay ( void )
{
    Delay_1ms();
}

// ------------------------------------------------------------------------- END

