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
 * @file ipd2.c
 * @brief IPD 2 Click Driver.
 */

#include "ipd2.h"

void ipd2_cfg_setup ( ipd2_cfg_t *cfg ) 
{
    cfg->st2 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->st1 = HAL_PIN_NC;
}

err_t ipd2_init ( ipd2_t *ctx, ipd2_cfg_t *cfg ) 
{
    err_t error_flag = IPD2_OK;
    error_flag |= digital_out_init( &ctx->in2, cfg->in2 );
    error_flag |= digital_out_init( &ctx->in1, cfg->in1 );
    error_flag |= digital_in_init( &ctx->st2, cfg->st2 );
    error_flag |= digital_in_init( &ctx->st1, cfg->st1 );
    digital_out_low( &ctx->in2 );
    digital_out_low( &ctx->in1 );
    Delay_100ms ( );
    return error_flag;
}

void ipd2_enable_out1 ( ipd2_t *ctx )
{
    digital_out_high( &ctx->in1 );
}

void ipd2_disable_out1 ( ipd2_t *ctx )
{
    digital_out_low( &ctx->in1 );
}

void ipd2_enable_out2 ( ipd2_t *ctx )
{
    digital_out_high( &ctx->in2 );
}

void ipd2_disable_out2 ( ipd2_t *ctx )
{
    digital_out_low( &ctx->in2 );
}

uint8_t ipd2_get_st1_pin ( ipd2_t *ctx )
{
    return digital_in_read( &ctx->st1 );
}

uint8_t ipd2_get_st2_pin ( ipd2_t *ctx )
{
    return digital_in_read( &ctx->st2 );
}

// ------------------------------------------------------------------------- END
