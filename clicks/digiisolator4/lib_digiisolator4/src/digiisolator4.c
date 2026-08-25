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
 * @file digiisolator4.c
 * @brief DIGI Isolator 4 Click Driver.
 */

#include "digiisolator4.h"

void digiisolator4_cfg_setup ( digiisolator4_cfg_t *cfg ) 
{
    cfg->en  = HAL_PIN_NC;
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
}

err_t digiisolator4_init ( digiisolator4_t *ctx, digiisolator4_cfg_t *cfg ) 
{
    err_t error_flag = DIGIISOLATOR4_OK;

    error_flag |= digital_out_init( &ctx->en, cfg->en );

    error_flag |= digital_in_init( &ctx->in1, cfg->in1 );
    error_flag |= digital_in_init( &ctx->in2, cfg->in2 );

    return error_flag;
}

void digiisolator4_enable_output ( digiisolator4_t *ctx )
{
    digital_out_high( &ctx->en );
}

void digiisolator4_disable_output ( digiisolator4_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t digiisolator4_get_in1_pin ( digiisolator4_t *ctx )
{
    return digital_in_read( &ctx->in1 );
}

uint8_t digiisolator4_get_in2_pin ( digiisolator4_t *ctx )
{
    return digital_in_read( &ctx->in2 );
}

err_t digiisolator4_read_inputs ( digiisolator4_t *ctx, digiisolator4_inputs_t *data_out )
{
    if ( NULL == data_out )
    {
        return DIGIISOLATOR4_ERROR;
    }

    data_out->in1_state = digital_in_read( &ctx->in1 );
    data_out->in2_state = digital_in_read( &ctx->in2 );

    return DIGIISOLATOR4_OK;
}

// ------------------------------------------------------------------------- END
