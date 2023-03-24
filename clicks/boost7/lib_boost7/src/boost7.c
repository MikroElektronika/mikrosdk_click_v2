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
 * @file boost7.c
 * @brief Boost 7 Click Driver.
 */

#include "boost7.h"

void boost7_cfg_setup ( boost7_cfg_t *cfg ) 
{
    cfg->stb1 = HAL_PIN_NC;
    cfg->stb2 = HAL_PIN_NC;
}

err_t boost7_init ( boost7_t *ctx, boost7_cfg_t *cfg ) 
{
    err_t error_flag = BOOST7_OK;
    error_flag |= digital_out_init( &ctx->stb1, cfg->stb1 );
    error_flag |= digital_out_init( &ctx->stb2, cfg->stb2 );
    digital_out_low( &ctx->stb1 );
    digital_out_low( &ctx->stb2 );
    return error_flag;
}

void boost7_enable_out1 ( boost7_t *ctx ) 
{
    digital_out_high( &ctx->stb1 );
}

void boost7_disable_out1 ( boost7_t *ctx ) 
{
    digital_out_low( &ctx->stb1 );
}

void boost7_enable_out2 ( boost7_t *ctx ) 
{
    digital_out_high( &ctx->stb2 );
}

void boost7_disable_out2 ( boost7_t *ctx ) 
{
    digital_out_low( &ctx->stb2 );
}

// ------------------------------------------------------------------------- END
