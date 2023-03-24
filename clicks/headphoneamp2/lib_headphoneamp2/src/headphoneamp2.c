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
 * @file headphoneamp2.c
 * @brief Headphone Amp 2 Click Driver.
 */

#include "headphoneamp2.h"

void headphoneamp2_cfg_setup ( headphoneamp2_cfg_t *cfg ) 
{
    cfg->stb = HAL_PIN_NC;
    cfg->gs = HAL_PIN_NC;
}

err_t headphoneamp2_init ( headphoneamp2_t *ctx, headphoneamp2_cfg_t *cfg ) 
{
    err_t err_flag = digital_out_init( &ctx->stb, cfg->stb );
    err_flag |= digital_out_init( &ctx->gs, cfg->gs );
    return err_flag;
}

void headphoneamp2_default_cfg ( headphoneamp2_t *ctx ) 
{
    headphoneamp2_set_device_on( ctx );
    headphoneamp2_gain_select( ctx, HEADPHONEAMP2_GAIN_6_DB );
}

void headphoneamp2_standby_mode ( headphoneamp2_t *ctx ) 
{
    digital_out_low( &ctx->stb );
}

void headphoneamp2_set_device_on ( headphoneamp2_t *ctx ) 
{
    digital_out_high( &ctx->stb );
}

void headphoneamp2_gain_select ( headphoneamp2_t *ctx, headphoneamp2_gain_select_value_t sel_gain ) 
{
    if ( HEADPHONEAMP2_GAIN_6_DB == sel_gain )
    {
        digital_out_high( &ctx->gs );
    }
    else
    {
        digital_out_low( &ctx->gs );
    }
}

void headphoneamp2_change_gain  ( headphoneamp2_t *ctx ) 
{
    digital_out_toggle( &ctx->gs );
}


// ------------------------------------------------------------------------- END
