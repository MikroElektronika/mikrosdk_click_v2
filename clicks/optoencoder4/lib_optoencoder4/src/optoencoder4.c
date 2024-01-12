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
 * @file optoencoder4.c
 * @brief Opto Encoder 4 Click Driver.
 */

#include "optoencoder4.h"

void optoencoder4_cfg_setup ( optoencoder4_cfg_t *cfg )
{
    cfg->out = HAL_PIN_NC;
    cfg->our = HAL_PIN_NC;
}

err_t optoencoder4_init ( optoencoder4_t *ctx, optoencoder4_cfg_t *cfg )
{
    err_t error_flag = OPTOENCODER4_OK;

    error_flag |= digital_in_init( &ctx->out, cfg->out );
    error_flag |= digital_in_init( &ctx->our, cfg->our );

    return error_flag;
}

uint8_t optoencoder4_get_out_pin ( optoencoder4_t *ctx )
{
    return digital_in_read( &ctx->out );
}

uint8_t optoencoder4_get_our_pin ( optoencoder4_t *ctx )
{
    return digital_in_read( &ctx->our );
}

// ------------------------------------------------------------------------- END
