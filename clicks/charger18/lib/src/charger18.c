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
 * @file charger18.c
 * @brief Charger 18 Click Driver.
 */

#include "charger18.h"

void charger18_cfg_setup ( charger18_cfg_t *cfg ) 
{
    cfg->bon = HAL_PIN_NC;
    cfg->on  = HAL_PIN_NC;
    cfg->ien = HAL_PIN_NC;
    cfg->ldo = HAL_PIN_NC;
    cfg->sta = HAL_PIN_NC;
}

err_t charger18_init ( charger18_t *ctx, charger18_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->bon, cfg->bon );
    return_flag |= digital_out_init( &ctx->on, cfg->on );
    return_flag |= digital_out_init( &ctx->ien, cfg->ien );
    return_flag |= digital_out_init( &ctx->ldo, cfg->ldo );

    return_flag |= digital_in_init( &ctx->sta, cfg->sta );
    
    digital_out_low ( &ctx->bon );
    digital_out_low ( &ctx->on );
    digital_out_low ( &ctx->ien );
    digital_out_low ( &ctx->ldo );

    return return_flag;
}

void charger18_buck_control ( charger18_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->bon, state );
}

void charger18_ldo_control ( charger18_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->ldo, state );
}

void charger18_suspend_control ( charger18_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->ien, state );
}

void charger18_power_control ( charger18_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->on, state );
}

uint8_t charger18_get_sta_pin ( charger18_t *ctx ) 
{
   return digital_in_read( &ctx->sta );
}

// ------------------------------------------------------------------------- END
