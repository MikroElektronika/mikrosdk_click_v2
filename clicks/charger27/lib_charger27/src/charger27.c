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
 * @file charger27.c
 * @brief Charger 27 Click Driver.
 */

#include "charger27.h"

void charger27_cfg_setup ( charger27_cfg_t *cfg ) 
{
    cfg->aok = HAL_PIN_NC;
    cfg->md  = HAL_PIN_NC;
    cfg->chg = HAL_PIN_NC;
}

err_t charger27_init ( charger27_t *ctx, charger27_cfg_t *cfg ) 
{
    err_t err_flag = CHARGER27_OK;

    err_flag |= digital_out_init( &ctx->md, cfg->md );

    err_flag |= digital_in_init( &ctx->aok, cfg->aok );
    err_flag |= digital_in_init( &ctx->chg, cfg->chg );

    return err_flag;
}

uint8_t charger27_check_input_supply ( charger27_t *ctx ) 
{
    return digital_in_read( &ctx->aok );
}

err_t charger27_set_mode ( charger27_t *ctx, uint8_t mode ) 
{
    err_t err_flag = CHARGER27_OK;
    if ( CHARGER27_MODE_DISCHARGE < mode )
    {
        err_flag = CHARGER27_ERROR;
    }
    else
    {
        digital_out_write( &ctx->md, mode );
    }
    return err_flag;
}

uint8_t charger27_check_chg_completion ( charger27_t *ctx ) 
{
    return digital_in_read( &ctx->chg );
}

// ------------------------------------------------------------------------- END
