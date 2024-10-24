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
 * @file recnplay2.c
 * @brief Rec N Play 2 Click Driver.
 */

#include "recnplay2.h"

void recnplay2_cfg_setup ( recnplay2_cfg_t *cfg ) 
{
    cfg->rec = HAL_PIN_NC;
    cfg->pe  = HAL_PIN_NC;
    cfg->pl  = HAL_PIN_NC;
}

err_t recnplay2_init ( recnplay2_t *ctx, recnplay2_cfg_t *cfg ) 
{
    err_t error_flag = RECNPLAY2_OK;

    error_flag |= digital_out_init( &ctx->rec, cfg->rec );
    error_flag |= digital_out_init( &ctx->pe, cfg->pe );
    error_flag |= digital_out_init( &ctx->pl, cfg->pl );

    return error_flag;
}

void recnplay2_default_cfg ( recnplay2_t *ctx ) 
{
    digital_out_high( &ctx->rec );
    digital_out_high( &ctx->pe );
    digital_out_high( &ctx->pl );
}

void recnplay2_set_rec_pin ( recnplay2_t *ctx, uint8_t pin_state )
{
    if ( 1 == pin_state )
    {
        digital_out_high( &ctx->rec );
    }
    else
    {
        digital_out_low( &ctx->rec );
    }
} 

void recnplay2_set_pe_pin ( recnplay2_t *ctx, uint8_t pin_state )
{
    if ( 1 == pin_state )
    {
        digital_out_high( &ctx->pe );
    }
    else
    {
        digital_out_low( &ctx->pe );
    }
}

void recnplay2_set_pl_pin ( recnplay2_t *ctx, uint8_t pin_state )
{
    if ( 1 == pin_state )
    {
        digital_out_high( &ctx->pl );
    }
    else
    {
        digital_out_low( &ctx->pl );
    }
}

err_t recnplay2_record_sound ( recnplay2_t *ctx, uint16_t rec_len )
{
    if ( RECNPLAY2_DURATION_24S >= rec_len )
    {
        recnplay2_set_rec_pin( ctx, 0 );
        for ( uint16_t n_cnt = 0; n_cnt < rec_len; n_cnt ++ )
        {
            Delay_1ms( );
        }
        recnplay2_set_rec_pin( ctx, 1 );
        return RECNPLAY2_OK;
    }
    else
    {
        return RECNPLAY2_ERROR;
    }
}

err_t recnplay2_play_sound ( recnplay2_t *ctx, uint16_t play_len )
{
    if ( RECNPLAY2_DURATION_24S >= play_len )
    {
        recnplay2_set_pl_pin( ctx, 0 );
        for ( uint16_t n_cnt = 0; n_cnt < play_len; n_cnt ++ )
        {
            Delay_1ms( );
        }
        recnplay2_set_pl_pin( ctx, 1 );
        return RECNPLAY2_OK;
    }
    else
    {
        return RECNPLAY2_ERROR;
    }
}

// ------------------------------------------------------------------------- END
