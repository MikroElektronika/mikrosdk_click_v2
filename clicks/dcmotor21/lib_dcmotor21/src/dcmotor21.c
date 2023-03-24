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
 * @file dcmotor21.c
 * @brief DC Motor 21 Click Driver.
 */

#include "dcmotor21.h"

void dcmotor21_cfg_setup ( dcmotor21_cfg_t *cfg ) 
{
    cfg->hn1 = HAL_PIN_NC;
    cfg->ln1 = HAL_PIN_NC;
    cfg->hn2 = HAL_PIN_NC;
    cfg->ln2 = HAL_PIN_NC;
}

err_t dcmotor21_init ( dcmotor21_t *ctx, dcmotor21_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->hn1, cfg->hn1 );
    return_flag |= digital_out_init( &ctx->ln1, cfg->ln1 );
    return_flag |= digital_out_init( &ctx->hn2, cfg->hn2 );
    return_flag |= digital_out_init( &ctx->ln2, cfg->ln2 );

    return return_flag;
}

void dcmotor21_default_cfg ( dcmotor21_t *ctx ) 
{
    dcmotor21_set_out_1 ( ctx, DCMOTOR21_OUT_HIGH_Z );
    dcmotor21_set_out_2 ( ctx, DCMOTOR21_OUT_HIGH_Z );
}

void dcmotor21_set_out_1 ( dcmotor21_t *ctx, uint8_t state ) 
{
    switch ( state )
    {
        case DCMOTOR21_OUT_HIGH_Z:
        {
            digital_out_low ( &ctx->hn1 );
            digital_out_low ( &ctx->ln1 );
            break;
        }
        case DCMOTOR21_OUT_LOW:
        {
            digital_out_low ( &ctx->hn1 );
            digital_out_high ( &ctx->ln1 );
            break;
        }
        case DCMOTOR21_OUT_HIGH:
        {
            digital_out_high ( &ctx->hn1 );
            digital_out_low ( &ctx->ln1 );
            break;
        }
        default:
        {
            break;
        }
    }
}

void dcmotor21_set_out_2 ( dcmotor21_t *ctx, uint8_t state ) 
{
    switch ( state )
    {
        case DCMOTOR21_OUT_HIGH_Z:
        {
            digital_out_low ( &ctx->hn2 );
            digital_out_low ( &ctx->ln2 );
            break;
        }
        case DCMOTOR21_OUT_LOW:
        {
            digital_out_low ( &ctx->hn2 );
            digital_out_high ( &ctx->ln2 );
            break;
        }
        case DCMOTOR21_OUT_HIGH:
        {
            digital_out_high ( &ctx->hn2 );
            digital_out_low ( &ctx->ln2 );
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
