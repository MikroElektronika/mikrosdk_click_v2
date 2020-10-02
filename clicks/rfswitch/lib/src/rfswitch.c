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

#include "rfswitch.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->on  = HAL_PIN_NC;
    cfg->sel = HAL_PIN_NC;
}

RFSWITCH_RETVAL rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->on, cfg->on );
    digital_out_init( &ctx->sel, cfg->sel );


    return RFSWITCH_OK;
}

void rfswitch_set_mode ( rfswitch_t *ctx, uint8_t enable )
{
    if ( enable == RFSWITCH_PWR_MODE_ENABLE )
    {
        digital_out_high( &ctx->on );
    }
    else
    {
        digital_out_low( &ctx->on );
    }
}

void rfswitch_sel_state (  rfswitch_t *ctx, uint8_t sel_state )
{
    if ( sel_state == RFSWITCH_SEL_PIN_STATE_HIGH )
    {
        digital_out_high( &ctx->sel );
    }
    else
    {
        digital_out_low( &ctx->sel );
    }
}

void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel )
{
    switch ( select_channel )
    {
        case RFSWITCH_SELECT_CHANNEL_1:
        {
            rfswitch_sel_state( ctx, RFSWITCH_SEL_PIN_STATE_LOW );
            break;
        }
        case RFSWITCH_SELECT_CHANNEL_2:
        {
            rfswitch_sel_state( ctx, RFSWITCH_SEL_PIN_STATE_HIGH );
            break;
        }
        default:
        {
            rfswitch_sel_state( ctx, RFSWITCH_SEL_PIN_STATE_LOW );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END

