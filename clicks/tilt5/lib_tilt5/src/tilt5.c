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
 * @file tilt5.c
 * @brief Tilt 5 Click Driver.
 */

#include "tilt5.h"

void tilt5_cfg_setup ( tilt5_cfg_t *cfg ) 
{
    cfg->out = HAL_PIN_NC;
}

err_t tilt5_init ( tilt5_t *ctx, tilt5_cfg_t *cfg ) 
{
    err_t error_flag = TILT5_OK;

    error_flag |= digital_in_init( &ctx->out, cfg->out );

    return error_flag;
}

uint8_t tilt5_get_out_pin ( tilt5_t *ctx )
{
    return ( TILT5_STATE_IDLE != digital_in_read( &ctx->out ) );
}

// ------------------------------------------------------------------------- END
