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
 * @file captouch6.c
 * @brief Cap Touch 6 Click Driver.
 */

#include "captouch6.h"

void captouch6_cfg_setup ( captouch6_cfg_t *cfg ) 
{
    cfg->tout = HAL_PIN_NC;
    cfg->pout = HAL_PIN_NC;
}

err_t captouch6_init ( captouch6_t *ctx, captouch6_cfg_t *cfg ) 
{
    err_t error_flag = CAPTOUCH6_OK;
    error_flag |= digital_in_init( &ctx->tout, cfg->tout );
    error_flag |= digital_in_init( &ctx->pout, cfg->pout );
    return error_flag;
}

uint8_t captouch6_get_tout_pin ( captouch6_t *ctx ) 
{
    return digital_in_read( &ctx->tout );
}

uint8_t captouch6_get_pout_pin ( captouch6_t *ctx ) 
{
    return digital_in_read( &ctx->pout );
}

// ------------------------------------------------------------------------- END
