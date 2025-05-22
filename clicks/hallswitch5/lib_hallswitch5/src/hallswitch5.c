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
 * @file hallswitch5.c
 * @brief Hall Switch 5 Click Driver.
 */

#include "hallswitch5.h"

void hallswitch5_cfg_setup ( hallswitch5_cfg_t *cfg ) 
{
    cfg->speed = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
}

err_t hallswitch5_init ( hallswitch5_t *ctx, hallswitch5_cfg_t *cfg ) 
{
    err_t error_flag = HALLSWITCH5_OK;

    error_flag |= digital_in_init( &ctx->speed, cfg->speed );
    error_flag |= digital_in_init( &ctx->dir, cfg->dir );

    return error_flag;
}

uint8_t hallswitch5_get_speed_pin ( hallswitch5_t *ctx )
{
    return digital_in_read( &ctx->speed ) & HALLSWITCH5_PIN_MASK;
}

uint8_t hallswitch5_get_dir_pin ( hallswitch5_t *ctx )
{
    return digital_in_read( &ctx->dir ) & HALLSWITCH5_PIN_MASK;
}

// ------------------------------------------------------------------------- END
