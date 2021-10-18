/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file rfswitch.c
 * @brief RF Switch Click Driver.
 */

#include "rfswitch.h"

void rfswitch_cfg_setup ( rfswitch_cfg_t *cfg ) 
{
    cfg->on   = HAL_PIN_NC;
    cfg->sel = HAL_PIN_NC;
}

err_t rfswitch_init ( rfswitch_t *ctx, rfswitch_cfg_t *cfg ) 
{
   err_t return_flag = 0;
   
    return_flag |= digital_out_init( &ctx->on, cfg->on );
    return_flag |= digital_out_init( &ctx->sel, cfg->sel );
    
    digital_out_low( &ctx->on );
    digital_out_low( &ctx->sel );

    return return_flag;
}

void rfswitch_power_on ( rfswitch_t *ctx )
{
    digital_out_high( &ctx->on );
}

void rfswitch_on_pin_set ( rfswitch_t *ctx, uint8_t enable ) 
{
    if ( enable == RFSWITCH_ON_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->on );
    } else {
        digital_out_low( &ctx->on );
    }
}

void rfswitch_sel_pin_set ( rfswitch_t *ctx, uint8_t enable ) 
{
    if ( enable == RFSWITCH_SEL_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->sel );
    } else {
        digital_out_low( &ctx->sel );
    }
}

void rfswitch_switch_channel ( rfswitch_t *ctx )
{
    digital_out_toggle( &ctx->sel );
}

void rfswitch_select_channel ( rfswitch_t *ctx, uint8_t select_channel )
{
    switch ( select_channel ) 
    {
        case RFSWITCH_SELECT_CHANNEL_1 : 
        {
            rfswitch_sel_pin_set( ctx, RFSWITCH_SEL_PIN_STATE_LOW );
            break;
        }
        case RFSWITCH_SELECT_CHANNEL_2 : 
        {
            rfswitch_sel_pin_set( ctx, RFSWITCH_SEL_PIN_STATE_HIGH );
            break;
        }
        default : 
        {
            rfswitch_sel_pin_set( ctx, RFSWITCH_SEL_PIN_STATE_LOW );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
