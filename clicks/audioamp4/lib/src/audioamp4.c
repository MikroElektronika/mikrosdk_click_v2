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

#include "audioamp4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void audioamp4_cfg_setup ( audioamp4_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->s0   = HAL_PIN_NC;
    cfg->s1   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->s2   = HAL_PIN_NC;
}

AUDIOAMP4_RETVAL audioamp4_init ( audioamp4_t *ctx, audioamp4_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->s0, cfg->s0 );
    digital_out_init( &ctx->s1, cfg->s1 );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->pwm, cfg->pwm );
    digital_out_init( &ctx->s2, cfg->s2 );

    return AUDIOAMP4_OK;
}

void audioamp4_default_cfg ( audioamp4_t *ctx )
{
    audioamp4_shutdown( ctx, AUDIOAMP4_SHUTDOWN_OFF );
    audioamp4_set_channel( ctx, AUDIOAMP4_VOLUME_CHANN_0 );
}

AUDIOAMP4_RETVAL audioamp4_set_channel ( audioamp4_t *ctx, uint8_t channel )
{
    uint8_t sel0;
    uint8_t sel1;
    uint8_t sel2;
    
    if ( channel > AUDIOAMP4_VOLUME_CHANN_7 )
    {
        return AUDIOAMP4_VOL_CHANN_ERR;
    }
    
    sel0 = channel & 0x01;
    sel1 = (channel & 0x02) >> 1;
    sel2 = (channel & 0x04) >> 2;
    
    digital_out_write( &ctx->s0, sel0 );
    digital_out_write( &ctx->s1, sel1 );
    digital_out_write( &ctx->s2, sel2 );
    
    return AUDIOAMP4_OK;
}

AUDIOAMP4_RETVAL audioamp4_shutdown ( audioamp4_t *ctx, uint8_t state )
{
    if ( state > 0x01 )
    {
        return AUDIOAMP4_SHTDWN_STATE_ERR;
    }
    
    digital_out_write( &ctx->en, state );
    
    return AUDIOAMP4_OK;
}
// ------------------------------------------------------------------------- END
