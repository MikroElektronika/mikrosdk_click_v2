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
 * @file efuse7.c
 * @brief eFuse 7 Click Driver.
 */

#include "efuse7.h"

void efuse7_cfg_setup ( efuse7_cfg_t *cfg ) 
{
    cfg->rst  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
}

err_t efuse7_init ( efuse7_t *ctx, efuse7_cfg_t *cfg ) 
{
    err_t error_flag = EFUSE7_OK;

    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->cs, cfg->cs );
    error_flag |= digital_out_init( &ctx->sck, cfg->sck );
    error_flag |= digital_out_init( &ctx->mosi, cfg->mosi );
   
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->sck );
    digital_out_high( &ctx->mosi );

    return error_flag;
}

err_t efuse7_default_cfg ( efuse7_t *ctx ) 
{
    err_t error_flag = EFUSE7_OK;
    
    efuse7_wiper_dec( ctx, EFUSE7_POT_STEPS );
    
    error_flag = efuse7_set_limit ( ctx, EFUSE7_CURRENT_LIMIT_1A );
    
    efuse7_enable_output( ctx );
    
    return error_flag;
}

void efuse7_enable_output ( efuse7_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void efuse7_disable_output ( efuse7_t *ctx )
{
    digital_out_low( &ctx->rst );
}

void efuse7_wiper_inc ( efuse7_t *ctx, uint8_t inc_num )
{
    digital_out_low( &ctx->cs );
    digital_out_high( &ctx->mosi );
    for ( uint8_t n_cnt = 0; n_cnt < inc_num; n_cnt++ )
    {
        digital_out_low( &ctx->sck );
        digital_out_high( &ctx->sck );
    }
    
    digital_out_high( &ctx->cs );
}

void efuse7_wiper_dec ( efuse7_t *ctx, uint8_t dec_num )
{
    digital_out_low( &ctx->cs );
    digital_out_low( &ctx->mosi );
    for ( uint8_t n_cnt = 0; n_cnt < dec_num; n_cnt++ )
    {
        digital_out_low( &ctx->sck );
        digital_out_high( &ctx->sck );
    }
    
    digital_out_high( &ctx->cs );
}

err_t efuse7_set_resistance ( efuse7_t *ctx, uint16_t resistance )
{
    uint8_t wiper_pos_val;
    
    if ( ( EFUSE7_MAX_RESISTANCE < resistance ) || ( EFUSE7_R5_RESISTANCE > resistance ) )
    {
        return EFUSE7_ERROR;
    }
    
    wiper_pos_val = ( resistance - EFUSE7_R5_RESISTANCE ) / EFUSE7_CONVERSION_MUL;
    efuse7_wiper_dec( ctx, EFUSE7_POT_STEPS );
    efuse7_wiper_inc( ctx, wiper_pos_val );
    
    return EFUSE7_OK;
}

err_t efuse7_set_limit ( efuse7_t *ctx, uint8_t set_current )
{
    err_t error_flag = EFUSE7_OK;
    
    switch ( set_current )
    {
        case EFUSE7_CURRENT_LIMIT_1A:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_1A_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_2A:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_2A_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_2A5:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_2A5_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_3A:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_3A_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_3A5:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_3A5_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_4A:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_4A_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_4A5:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_4A5_RESISTANCE );
            break;
        }
        case EFUSE7_CURRENT_LIMIT_5A:
        {
            error_flag |= efuse7_set_resistance( ctx, EFUSE7_LIMIT_5A_RESISTANCE );
            break;
        }
        default:
        {
            error_flag = EFUSE7_ERROR;
        }
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
