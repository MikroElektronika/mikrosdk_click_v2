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
 * @file ireclipse2.c
 * @brief IR Eclipse 2 Click Driver.
 */

#include "ireclipse2.h"

void ireclipse2_cfg_setup ( ireclipse2_cfg_t *cfg ) 
{
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t ireclipse2_init ( ireclipse2_t *ctx, ireclipse2_cfg_t *cfg ) 
{
    err_t err_flag = digital_out_init( &ctx->en, cfg->en );
    err_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );
    return err_flag;
}

void ireclipse2_enable ( ireclipse2_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void ireclipse2_disable ( ireclipse2_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

uint8_t ireclipse2_get_state ( ireclipse2_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
