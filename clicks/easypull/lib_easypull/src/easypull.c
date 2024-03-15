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
 * @file easypull.c
 * @brief EasyPull Click Driver.
 */

#include "easypull.h"

void easypull_cfg_setup ( easypull_cfg_t *cfg ) 
{
    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t easypull_init ( easypull_t *ctx, easypull_cfg_t *cfg ) 
{
    err_t error_flag = EASYPULL_OK;

    error_flag |= digital_in_init( &ctx->an, cfg->an );
    error_flag |= digital_in_init( &ctx->rst, cfg->rst );
    error_flag |= digital_in_init( &ctx->cs, cfg->cs );
    error_flag |= digital_in_init( &ctx->pwm, cfg->pwm );
    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

uint8_t easypull_get_an_pin ( easypull_t *ctx )
{
    return digital_in_read( &ctx->an );
}

uint8_t easypull_get_rst_pin ( easypull_t *ctx )
{
    return digital_in_read( &ctx->rst );
}

uint8_t easypull_get_cs_pin ( easypull_t *ctx )
{
    return digital_in_read( &ctx->cs );
}

uint8_t easypull_get_pwm_pin ( easypull_t *ctx )
{
    return digital_in_read( &ctx->pwm );
}

uint8_t easypull_get_int_pin ( easypull_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
