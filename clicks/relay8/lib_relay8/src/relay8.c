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
 * @file relay8.c
 * @brief Relay 8 Click Driver.
 */

#include "relay8.h"

void relay8_cfg_setup ( relay8_cfg_t *cfg ) 
{
    cfg->rst = HAL_PIN_NC;
    cfg->set = HAL_PIN_NC;
    cfg->tgl = HAL_PIN_NC;
}

err_t relay8_init ( relay8_t *ctx, relay8_cfg_t *cfg ) 
{
    err_t error_flag = RELAY8_OK;

    error_flag |= digital_out_init( &ctx->rst, cfg->rst );
    error_flag |= digital_out_init( &ctx->set, cfg->set );
    error_flag |= digital_out_init( &ctx->tgl, cfg->tgl );

    /* Set all 3 pins to inactive states */
    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->set );
    digital_out_low( &ctx->tgl );

    return error_flag;
}

void relay8_set_relay ( relay8_t *ctx ) 
{
    digital_out_high( &ctx->set );
    Delay_1ms( );
    digital_out_low( &ctx->set );
}

void relay8_reset_relay ( relay8_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_1ms( );
    digital_out_high( &ctx->rst );
}

void relay8_toggle_relay ( relay8_t *ctx ) 
{
    digital_out_high( &ctx->tgl );
    Delay_1ms( );
    digital_out_low( &ctx->tgl );
}

// ------------------------------------------------------------------------- END
