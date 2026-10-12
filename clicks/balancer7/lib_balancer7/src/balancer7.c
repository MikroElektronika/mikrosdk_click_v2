/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file balancer7.c
 * @brief Balancer 7 Click Driver.
 */

#include "balancer7.h"

void balancer7_cfg_setup ( balancer7_cfg_t *cfg ) 
{
    cfg->mb_en = HAL_PIN_NC;
    cfg->mb_md = HAL_PIN_NC;
}

err_t balancer7_init ( balancer7_t *ctx, balancer7_cfg_t *cfg ) 
{
    err_t error_flag = BALANCER7_OK;

    error_flag |= digital_out_init( &ctx->mb_en, cfg->mb_en );
    error_flag |= digital_out_init( &ctx->mb_md, cfg->mb_md );

    /* Default state: disabled, buck mode */
    digital_out_low( &ctx->mb_en );
    digital_out_low( &ctx->mb_md );

    return error_flag;
}

void balancer7_enable_device ( balancer7_t *ctx ) 
{
    digital_out_high( &ctx->mb_en );
}

void balancer7_disable_device ( balancer7_t *ctx ) 
{
    digital_out_low( &ctx->mb_en );
}

void balancer7_set_mode ( balancer7_t *ctx, uint8_t mode ) 
{
    if ( BALANCER7_MODE_BOOST == mode )
    {
        digital_out_high( &ctx->mb_md );
    }
    else
    {
        digital_out_low( &ctx->mb_md );
    }
}

// ------------------------------------------------------------------------- END
