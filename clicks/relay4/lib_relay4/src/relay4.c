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
 * @file relay4.c
 * @brief Relay 4 Click Driver.
 */

#include "relay4.h"

void relay4_cfg_setup ( relay4_cfg_t *cfg ) 
{
    cfg->rl1 = HAL_PIN_NC;
    cfg->rl2 = HAL_PIN_NC;
}

err_t relay4_init ( relay4_t *ctx, relay4_cfg_t *cfg ) 
{
    err_t error_flag = RELAY4_OK;
    error_flag |= digital_out_init( &ctx->rl1, cfg->rl1 );
    error_flag |= digital_out_init( &ctx->rl2, cfg->rl2 );
    return error_flag;
}

void relay4_set_relay1_open ( relay4_t *ctx ) 
{
    digital_out_low( &ctx->rl1 );
}

void relay4_set_relay1_close ( relay4_t *ctx ) 
{
    digital_out_high( &ctx->rl1 );
}

void relay4_switch_relay1 ( relay4_t *ctx ) 
{
    digital_out_toggle( &ctx->rl1 );
}

void relay4_set_relay2_open ( relay4_t *ctx ) 
{
    digital_out_low( &ctx->rl2 );
}

void relay4_set_relay2_close ( relay4_t *ctx ) 
{
    digital_out_high( &ctx->rl2 );
}

void relay4_switch_relay2 ( relay4_t *ctx ) 
{
    digital_out_toggle( &ctx->rl2 );
}

// ------------------------------------------------------------------------- END
