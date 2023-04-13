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
 * @file audioamp9.c
 * @brief AudioAmp 9 Click Driver.
 */

#include "audioamp9.h"

void audioamp9_cfg_setup ( audioamp9_cfg_t *cfg ) 
{
    cfg->mut = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;
    cfg->g0  = HAL_PIN_NC;
    cfg->g1  = HAL_PIN_NC;
}

err_t audioamp9_init ( audioamp9_t *ctx, audioamp9_cfg_t *cfg ) 
{
    err_t error_flag = AUDIOAMP9_OK;

    error_flag |= digital_out_init( &ctx->mut, cfg->mut );
    error_flag |= digital_out_init( &ctx->shd, cfg->shd );
    error_flag |= digital_out_init( &ctx->g0, cfg->g0 );
    error_flag |= digital_out_init( &ctx->g1, cfg->g1 );

    return error_flag;
}

void audioamp9_default_cfg ( audioamp9_t *ctx ) 
{
    audioamp9_shutdown_off( ctx );
    audioamp9_mute_off( ctx );
    audioamp9_set_gain1( ctx );
}

void audioamp9_shutdown_on ( audioamp9_t *ctx )
{
    digital_out_high( &ctx->shd );
}

void audioamp9_shutdown_off ( audioamp9_t *ctx )
{
    digital_out_low( &ctx->shd );
}

void audioamp9_mute_on ( audioamp9_t *ctx )
{
    digital_out_low( &ctx->mut );
}

void audioamp9_mute_off ( audioamp9_t *ctx )
{
    digital_out_high( &ctx->mut );
}

void audioamp9_set_gain1 ( audioamp9_t *ctx )
{
   digital_out_high( &ctx->g0 );
   digital_out_high( &ctx->g1 );
}

void audioamp9_set_gain2 ( audioamp9_t *ctx )
{
   digital_out_low( &ctx->g0 );
   digital_out_high( &ctx->g1 );
}

void audioamp9_set_gain3 ( audioamp9_t *ctx )
{
   digital_out_high( &ctx->g0 );
   digital_out_low( &ctx->g1 );
}

void audioamp9_set_gain4 ( audioamp9_t *ctx )
{
   digital_out_low( &ctx->g0 );
   digital_out_low( &ctx->g1 );
}

err_t audioamp9_set_gain_level ( audioamp9_t *ctx, uint8_t gain_level )
{
    err_t error_flag = AUDIOAMP9_OK;
    
    switch ( gain_level )
    {
        case AUDIOAMP9_GAIN_LEVEL1:
        {
            audioamp9_set_gain1( ctx );
            error_flag = AUDIOAMP9_OK;
            break;
        }
        case AUDIOAMP9_GAIN_LEVEL2:
        {
            audioamp9_set_gain2( ctx );
            error_flag = AUDIOAMP9_OK;
            break;
        }
        case AUDIOAMP9_GAIN_LEVEL3:
        {
            audioamp9_set_gain4( ctx );
            error_flag = AUDIOAMP9_OK;
            break;
        }
        case AUDIOAMP9_GAIN_LEVEL4:
        {
            audioamp9_set_gain4( ctx );
            error_flag = AUDIOAMP9_OK;
            break;
        }
        default :
        {
            audioamp9_mute_on( ctx );
            error_flag = AUDIOAMP9_ERROR;
            break;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
