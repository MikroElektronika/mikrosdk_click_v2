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
 * @file solidswitch8.c
 * @brief SolidSwitch 8 Click Driver.
 */

#include "solidswitch8.h"

void solidswitch8_cfg_setup ( solidswitch8_cfg_t *cfg ) 
{
    cfg->err = HAL_PIN_NC;
    cfg->in  = HAL_PIN_NC;
    cfg->sts = HAL_PIN_NC;
}

err_t solidswitch8_init ( solidswitch8_t *ctx, solidswitch8_cfg_t *cfg ) 
{
    err_t error_flag = SOLIDSWITCH8_OK;

    error_flag |= digital_out_init( &ctx->err, cfg->err );
    error_flag |= digital_out_init( &ctx->in, cfg->in );

    error_flag |= digital_in_init( &ctx->sts, cfg->sts );

    return error_flag;
}

void solidswitch8_default_cfg ( solidswitch8_t *ctx ) 
{
    solidswitch8_set_in_pin( ctx, SOLIDSWITCH8_PIN_STATE_LOW );
    solidswitch8_set_err_pin( ctx, SOLIDSWITCH8_PIN_STATE_LOW );
}

void solidswitch8_set_err_pin ( solidswitch8_t *ctx, uint8_t pin_state )
{
    if ( SOLIDSWITCH8_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->err );
    }
    else
    {
        digital_out_low( &ctx->err );
    }
}

void solidswitch8_set_in_pin ( solidswitch8_t *ctx, uint8_t pin_state )
{
    if ( SOLIDSWITCH8_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->in );
    }
    else
    {
        digital_out_low( &ctx->in );
    }
}

uint8_t solidswitch8_get_sts_pin ( solidswitch8_t *ctx )
{
    return digital_in_read( &ctx->sts );
}

// ------------------------------------------------------------------------- END
