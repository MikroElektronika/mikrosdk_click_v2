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
 * @file powermux3.c
 * @brief Power MUX 3 Click Driver.
 */

#include "powermux3.h"

void powermux3_cfg_setup ( powermux3_cfg_t *cfg ) 
{
    cfg->shd = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
}

err_t powermux3_init ( powermux3_t *ctx, powermux3_cfg_t *cfg ) 
{
    err_t error_flag = POWERMUX3_OK;

    error_flag |= digital_out_init( &ctx->shd, cfg->shd );
    error_flag |= digital_out_init( &ctx->en, cfg->en );

    return error_flag;
}

void powermux3_enable_device ( powermux3_t *ctx ) 
{
    digital_out_high( &ctx->shd );
}

void powermux3_disable_device ( powermux3_t *ctx ) 
{
    digital_out_low( &ctx->shd );
}

void powermux3_enable_output ( powermux3_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void powermux3_disable_output ( powermux3_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END
