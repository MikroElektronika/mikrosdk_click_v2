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
 * @file charger26.c
 * @brief Charger 26 Click Driver.
 */

#include "charger26.h"

void charger26_cfg_setup ( charger26_cfg_t *cfg ) 
{
    cfg->vsel = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->isel = HAL_PIN_NC;
    cfg->chg  = HAL_PIN_NC;
}

err_t charger26_init ( charger26_t *ctx, charger26_cfg_t *cfg ) 
{
    err_t error_flag = CHARGER26_OK;

    error_flag |= digital_out_init( &ctx->vsel, cfg->vsel );
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_out_init( &ctx->isel, cfg->isel );

    error_flag |= digital_in_init( &ctx->chg, cfg->chg );

    return error_flag;
}

void charger26_default_cfg ( charger26_t *ctx ) 
{
    charger26_enable_output ( ctx, CHARGER26_DISABLE_OUTPUT );
    charger26_set_vsel( ctx, CHARGER26_SELV_4V1_REG_POINT );
    charger26_set_isel( ctx, CHARGER26_SELI_100_MA_MAX_REG );
}

void charger26_set_vsel ( charger26_t *ctx, uint8_t vout_sel )
{
    if ( CHARGER26_SELV_4V2_REG_POINT == vout_sel )
    {
        digital_out_high( &ctx->vsel );
    }
    else
    {
        digital_out_low( &ctx->vsel );
    }
}

void charger26_set_isel ( charger26_t *ctx, uint8_t iout_sel )
{
    if ( CHARGER26_SELI_500_MA_MAX_REG == iout_sel )
    {
        digital_out_high( &ctx->isel );
    }
    else
    {
        digital_out_low( &ctx->isel );
    }
}

void charger26_enable_output ( charger26_t *ctx, uint8_t output_state )
{
    if ( CHARGER26_ENABLE_OUTPUT == output_state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t charger26_get_chg_state ( charger26_t *ctx ) 
{
    return digital_in_read( &ctx->chg );
}

// ------------------------------------------------------------------------- END
