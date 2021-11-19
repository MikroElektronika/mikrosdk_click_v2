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
 * @file hbridgedriver.c
 * @brief H-Bridge Driver Click Driver.
 */

#include "hbridgedriver.h"

void hbridgedriver_cfg_setup ( hbridgedriver_cfg_t *cfg ) 
{
    cfg->il2 = HAL_PIN_NC;
    cfg->ih2 = HAL_PIN_NC;
    cfg->gen = HAL_PIN_NC;
    cfg->il1 = HAL_PIN_NC;
    cfg->ih1 = HAL_PIN_NC;
}

err_t hbridgedriver_init ( hbridgedriver_t *ctx, hbridgedriver_cfg_t *cfg ) 
{
   err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->il2, cfg->il2 );
    return_flag |= digital_out_init( &ctx->ih2, cfg->ih2 );
    return_flag |= digital_out_init( &ctx->gen, cfg->gen );
    return_flag |= digital_out_init( &ctx->il1, cfg->il1 );
    return_flag |= digital_out_init( &ctx->ih1, cfg->ih1 );

    return return_flag;
}

void hbridgedriver_glo_enable ( hbridgedriver_t *ctx, uint8_t state )
{
    if ( HBRIDGEDRIVER_PROP_EN == state )
    {
        digital_out_high( &ctx->gen );
    }
    else if ( HBRIDGEDRIVER_PROP_DIS == state )
    {
        digital_out_low( &ctx->gen );
    }
}

void hbridgedriver_in_ls_2 ( hbridgedriver_t *ctx, uint8_t state )
{
    if ( HBRIDGEDRIVER_PROP_EN == state )
    {
        digital_out_high( &ctx->il2 );
    }
    else if ( HBRIDGEDRIVER_PROP_DIS == state )
    {
        digital_out_low( &ctx->il2 );
    }
}

void hbridgedriver_in_hs_2 ( hbridgedriver_t *ctx, uint8_t state )
{
    if ( HBRIDGEDRIVER_PROP_EN == state )
    {
        digital_out_high( &ctx->ih2 );
    }
    else if ( HBRIDGEDRIVER_PROP_DIS == state )
    {
        digital_out_low( &ctx->ih2 );
    }
}

void hbridgedriver_in_ls_1 ( hbridgedriver_t *ctx, uint8_t state )
{
    if ( HBRIDGEDRIVER_PROP_EN == state )
    {
        digital_out_high( &ctx->il1 );
    }
    else if ( HBRIDGEDRIVER_PROP_DIS == state )
    {
        digital_out_low( &ctx->il1 );
    }
}

void hbridgedriver_in_hs_1 ( hbridgedriver_t *ctx, uint8_t state )
{
    if ( HBRIDGEDRIVER_PROP_EN == state )
    {
        digital_out_high( &ctx->ih1 );
    }
    else if ( HBRIDGEDRIVER_PROP_DIS == state )
    {
        digital_out_low( &ctx->ih1 );
    }
}

void hbridgedriver_dc_fwd_1 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_dc_bwd_1 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_EN );
}

void hbridgedriver_dc_coast_1 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_dc_brake_1 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_EN );
}

void hbridgedriver_dc_fwd_2 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_dc_bwd_2 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_EN );
}

void hbridgedriver_dc_coast_2 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_dc_brake_2 ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_EN );
}

void hbridgedriver_reverse ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_forward ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_braking ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_EN );
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_DIS );
}

void hbridgedriver_coasting ( hbridgedriver_t *ctx )
{
    hbridgedriver_in_ls_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_ls_2( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_hs_1( ctx, HBRIDGEDRIVER_PROP_DIS );
    hbridgedriver_in_hs_2( ctx, HBRIDGEDRIVER_PROP_DIS );
}

// ------------------------------------------------------------------------- END
