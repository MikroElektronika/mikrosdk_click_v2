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

#include "charger9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger9_cfg_setup ( charger9_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->flt = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;
    cfg->chg = HAL_PIN_NC;
    cfg->ful = HAL_PIN_NC;
}

CHARGER9_RETVAL charger9_init ( charger9_t *ctx, charger9_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->shd, cfg->shd );

    // Input pins

    digital_in_init( &ctx->flt, cfg->flt );
    digital_in_init( &ctx->chg, cfg->chg );
    digital_in_init( &ctx->ful, cfg->ful );

    return CHARGER9_OK;
}

CHARGER9_RETVAL charger9_enable ( charger9_t *ctx, CHARGER9_STATE pwr_state )
{
    if ( pwr_state > 1 )
    {
        return CHARGER9_INVALID_STATE;
    }
    
    digital_out_write( &ctx->shd, pwr_state );
    
    return CHARGER9_OK;
}

CHARGER9_RETVAL charger9_fast_charge_ind ( charger9_t *ctx )
{
    if ( digital_in_read( &ctx->chg ) )
    {
        return CHARGER9_IND_INACTIVE;
    }
    else
    {
        return CHARGER9_IND_ACTIVE;
    }
}

CHARGER9_RETVAL charger9_full_charge_ind ( charger9_t *ctx )
{
    if ( digital_in_read( &ctx->ful ) )
    {
        return CHARGER9_IND_INACTIVE;
    }
    else
    {
        return CHARGER9_IND_ACTIVE;
    }
}

CHARGER9_RETVAL charger9_fault_ind ( charger9_t *ctx )
{
    if ( digital_in_read( &ctx->flt ) )
    {
        return CHARGER9_IND_INACTIVE;
    }
    else
    {
        return CHARGER9_IND_ACTIVE;
    }
}

// ------------------------------------------------------------------------- END

