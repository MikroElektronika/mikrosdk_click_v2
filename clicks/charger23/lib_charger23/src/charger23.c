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
 * @file charger23.c
 * @brief Charger 23 Click Driver.
 */

#include "charger23.h"

void charger23_cfg_setup ( charger23_cfg_t *cfg )
{
    cfg->status = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->fault = HAL_PIN_NC;
}

err_t charger23_init ( charger23_t *ctx, charger23_cfg_t *cfg )
{
    err_t error_flag = CHARGER23_OK;
    error_flag |= digital_out_init( &ctx->en, cfg->en );
    error_flag |= digital_in_init( &ctx->status, cfg->status );
    error_flag |= digital_in_init( &ctx->fault, cfg->fault );
    digital_out_low ( &ctx->en );
    return error_flag;
}

void charger23_enable_device ( charger23_t *ctx )
{
    digital_out_high( &ctx->en );
    Delay_100ms ( );
}

void charger23_disable_device ( charger23_t *ctx )
{
    digital_out_low( &ctx->en );
    Delay_100ms ( );
}

uint8_t charger23_get_status_pin ( charger23_t *ctx )
{
    return digital_in_read( &ctx->status );
}

uint8_t charger23_get_fault_pin ( charger23_t *ctx )
{
    return digital_in_read( &ctx->fault );
}

uint8_t charger23_get_charger_state ( charger23_t *ctx )
{
    return ( uint8_t ) ( ( ( charger23_get_fault_pin ( ctx ) << 1 ) | 
                           charger23_get_status_pin ( ctx ) ) & CHARGER23_STATE_MASK );
}

// ------------------------------------------------------------------------- END
