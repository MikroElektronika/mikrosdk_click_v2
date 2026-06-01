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
 * @file opto8.c
 * @brief Opto 8 Click Driver.
 */

#include "opto8.h"

void opto8_cfg_setup ( opto8_cfg_t *cfg ) 
{
    cfg->in1 = HAL_PIN_NC;
    cfg->out1 = HAL_PIN_NC;
    cfg->out2 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

err_t opto8_init ( opto8_t *ctx, opto8_cfg_t *cfg ) 
{
    err_t error_flag = OPTO8_OK;

    error_flag |= digital_out_init( &ctx->out1, cfg->out1 );
    error_flag |= digital_out_init( &ctx->out2, cfg->out2 );

    error_flag |= digital_in_init( &ctx->in1, cfg->in1 );
    error_flag |= digital_in_init( &ctx->in2, cfg->in2 );

    return error_flag;
}

void opto8_set_out1 ( opto8_t *ctx )
{
    digital_out_high( &ctx->out1 );
}

void opto8_clear_out1 ( opto8_t *ctx )
{
    digital_out_low( &ctx->out1 );
}

void opto8_toggle_out1 ( opto8_t *ctx )
{
    digital_out_toggle( &ctx->out1 );
}

void opto8_set_out2 ( opto8_t *ctx )
{
    digital_out_high( &ctx->out2 );
}

void opto8_clear_out2 ( opto8_t *ctx )
{
    digital_out_low( &ctx->out2 );
}

void opto8_toggle_out2 ( opto8_t *ctx )
{
    digital_out_toggle( &ctx->out2 );
}

uint8_t opto8_get_in1 ( opto8_t *ctx )
{
    return !!digital_in_read( &ctx->in1 );
}

uint8_t opto8_get_in2 ( opto8_t *ctx )
{
    return !!digital_in_read( &ctx->in2 );
}

// ------------------------------------------------------------------------- END
