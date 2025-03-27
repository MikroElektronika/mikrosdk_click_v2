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
 * @file tilt6.c
 * @brief Tilt 6 Click Driver.
 */

#include "tilt6.h"

void tilt6_cfg_setup ( tilt6_cfg_t *cfg ) 
{
    cfg->out1 = HAL_PIN_NC;
    cfg->out2 = HAL_PIN_NC;
}

err_t tilt6_init ( tilt6_t *ctx, tilt6_cfg_t *cfg ) 
{
    err_t error_flag = TILT6_OK;

    error_flag |= digital_in_init( &ctx->out1, cfg->out1 );
    error_flag |= digital_in_init( &ctx->out2, cfg->out2 );

    return error_flag;
}

uint8_t tilt6_get_out1_pin ( tilt6_t *ctx )
{
    return ( TILT6_STATE_IDLE != digital_in_read( &ctx->out1 ) );
}

uint8_t tilt6_get_out2_pin ( tilt6_t *ctx )
{
    return ( TILT6_STATE_IDLE != digital_in_read( &ctx->out2 ) );
}

uint8_t tilt6_get_tilt_state ( tilt6_t *ctx )
{
    uint8_t state = TILT6_STATE_IDLE;
    state = tilt6_get_out1_pin ( ctx ) | ( tilt6_get_out2_pin ( ctx ) << 1 );
    return state;
}

// ------------------------------------------------------------------------- END
