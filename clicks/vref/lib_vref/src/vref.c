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
 * @file vref.c
 * @brief VREF Click Driver.
 */

#include "vref.h"

void vref_cfg_setup ( vref_cfg_t *cfg ) 
{
    cfg->en = HAL_PIN_NC;
}

err_t vref_init ( vref_t *ctx, vref_cfg_t *cfg ) 
{
    err_t error_flag = VREF_OK;

    error_flag |= digital_out_init( &ctx->en, cfg->en );

    return error_flag;
}

void vref_enable_output ( vref_t *ctx )
{
    digital_out_high( &ctx->en );
}

void vref_disable_output ( vref_t *ctx )
{
    digital_out_low( &ctx->en );
}

// ------------------------------------------------------------------------- END
