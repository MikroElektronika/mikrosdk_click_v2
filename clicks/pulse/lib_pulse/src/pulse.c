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
 * @file pulse.c
 * @brief PULSE Click Driver.
 */

#include "pulse.h"

void pulse_cfg_setup ( pulse_cfg_t *cfg ) 
{
    cfg->out     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t pulse_init ( pulse_t *ctx, pulse_cfg_t *cfg ) 
{
    err_t error_flag = PULSE_OK;

    error_flag |= digital_in_init( &ctx->out, cfg->out );
    error_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return error_flag;
}

err_t pulse_read_pin ( pulse_t *ctx, uint8_t pin, uint8_t *state ) 
{
    if ( PULSE_PIN_OUT == pin )
    {
        *state = digital_in_read( &ctx->out );
    }
    else if ( PULSE_PIN_INT == pin )
    {
        *state = digital_in_read( &ctx->int_pin );
    }
    else
    {
        /* Unknown pin selection */
        return PULSE_ERROR;
    }

    return PULSE_OK;
}

// ------------------------------------------------------------------------- END
