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
 * @file audioamp12.c
 * @brief AudioAMP 12 Click Driver.
 */

#include "audioamp12.h"

void audioamp12_cfg_setup ( audioamp12_cfg_t *cfg ) 
{
    cfg->stb = HAL_PIN_NC;
    cfg->gs  = HAL_PIN_NC;
}

err_t audioamp12_init ( audioamp12_t *ctx, audioamp12_cfg_t *cfg ) 
{
    err_t err_flag = digital_out_init( &ctx->stb, cfg->stb );
    err_flag |= digital_out_init( &ctx->gs, cfg->gs );
    return err_flag;
}

void audioamp12_default_cfg ( audioamp12_t *ctx ) 
{
    audioamp12_set_mode_operation( ctx );
    audioamp12_gain_select( ctx, AUDIOAMP12_GAIN_6_DB );
}

void audioamp12_set_mode_standby ( audioamp12_t *ctx ) 
{
    digital_out_low( &ctx->stb );
}

void audioamp12_set_mode_operation ( audioamp12_t *ctx ) 
{
    digital_out_high( &ctx->stb );
}

void audioamp12_gain_select ( audioamp12_t *ctx, audioamp12_gain_select_t sel_gain ) 
{
    if ( AUDIOAMP12_GAIN_6_DB == sel_gain )
    {
        digital_out_high( &ctx->gs );
    }
    else
    {
        digital_out_low( &ctx->gs );
    }
}

void audioamp12_change_gain ( audioamp12_t *ctx ) 
{
    digital_out_toggle( &ctx->gs );
}

// ------------------------------------------------------------------------- END
