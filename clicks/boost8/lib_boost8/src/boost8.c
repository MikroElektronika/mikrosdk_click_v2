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
 * @file boost8.c
 * @brief Boost 8 Click Driver.
 */

#include "boost8.h"

void boost8_cfg_setup ( boost8_cfg_t *cfg ) 
{
    cfg->en_p = HAL_PIN_NC;
    cfg->en_n = HAL_PIN_NC;
}

err_t boost8_init ( boost8_t *ctx, boost8_cfg_t *cfg ) 
{
    err_t error_flag = BOOST8_OK;

    error_flag |= digital_out_init( &ctx->en_p, cfg->en_p );
    error_flag |= digital_out_init( &ctx->en_n, cfg->en_n );

    return error_flag;
}

void boost8_default_cfg ( boost8_t *ctx ) 
{    
    digital_out_low( &ctx->en_p );
    digital_out_low( &ctx->en_n );
}

void boost8_enable_positive_voltage ( boost8_t *ctx )
{
    digital_out_high( &ctx->en_p );
}

void boost8_disable_positive_voltage ( boost8_t *ctx )
{
    digital_out_low( &ctx->en_p );
}

void boost8_enable_negative_voltage ( boost8_t *ctx )
{
    digital_out_high( &ctx->en_n );
}

void boost8_disable_negative_voltage ( boost8_t *ctx )
{
    digital_out_low( &ctx->en_n );
}

void boost8_enable_both_outputs ( boost8_t *ctx )
{
    digital_out_high( &ctx->en_p );
    digital_out_high( &ctx->en_n );
}

void boost8_disable_both_outputs ( boost8_t *ctx )
{
    digital_out_low( &ctx->en_p );
    digital_out_low( &ctx->en_n );
}

// ------------------------------------------------------------------------- END
