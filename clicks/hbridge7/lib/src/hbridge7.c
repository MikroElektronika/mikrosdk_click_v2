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

#include "hbridge7.h"

// ------------------------------------------------------------------ VARIABLES

static uint8_t drv_motor_state = 0;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hbridge7_cfg_setup ( hbridge7_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->nsl   = HAL_PIN_NC;
    cfg->ph = HAL_PIN_NC;
    cfg->nft = HAL_PIN_NC;
}

HBRIDGE7_RETVAL hbridge7_init ( hbridge7_t *ctx, hbridge7_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->nsl, cfg->nsl );
    digital_out_init( &ctx->ph, cfg->ph );

    // Input pins

    digital_in_init( &ctx->nft, cfg->nft );

    return HBRIDGE7_OK;
}

void hbridge7_motor_state ( hbridge7_t *ctx, uint8_t state )
{   
    digital_out_write( &ctx->nsl, state);

    drv_motor_state = state;
}

void hbridge7_motor_control ( hbridge7_t *ctx, uint8_t ctrl )
{
    if ( drv_motor_state == HBRIDGE7_MOTOR_SLEEP )
    {
        digital_out_high( &ctx->nsl );
    }
    
    switch ( ctrl )
    {
        case 1:
        {
            digital_out_high( &ctx->en );
            digital_out_high( &ctx->ph );
            break;
        }
        case 2:
        {
            digital_out_high( &ctx->en );
            digital_out_low( &ctx->ph );
            break;
        }
        case 3:
        {
            digital_out_low( &ctx->en );
            digital_out_low( &ctx->ph );
            break;
        }
    }
}

uint8_t hbridge7_get_fault_state ( hbridge7_t *ctx )
{
    return digital_in_read( &ctx->nft );
}

// ------------------------------------------------------------------------- END

