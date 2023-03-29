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

#include "motion.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void motion_cfg_setup ( motion_cfg_t *cfg )
{
    // Additional gpio pins
    
    cfg->en = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

MOTION_RETVAL motion_init ( motion_t *ctx, motion_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->out, cfg->out );

    return MOTION_OK;
}

void motion_default_cfg ( motion_t *ctx )
{
    // Click default configuration
    
    motion_set_en_pin( ctx, MOTION_PIN_STATE_HIGH ); 
}

void motion_set_en_pin (  motion_t *ctx, motion_pin_state_t en_state )
{    
    digital_out_write( &ctx->en, en_state );
}

motion_detect_state_t motion_get_detected ( motion_t *ctx )
{
    uint8_t out_state;
    
    out_state = ( motion_pin_state_t ) digital_in_read( &ctx->out );
    
    if ( out_state == MOTION_PIN_STATE_LOW )
    {
        return MOTION_NO_DETECT;    
    }
    else if ( out_state == MOTION_PIN_STATE_HIGH )
    {
        return MOTION_DETECTED;
    }
}

// ------------------------------------------------------------------------- END

