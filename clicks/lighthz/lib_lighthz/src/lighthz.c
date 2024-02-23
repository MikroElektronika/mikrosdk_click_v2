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
 * @file lighthz.c
 * @brief LightHz Click Driver.
 */

#include "lighthz.h"

void lighthz_cfg_setup ( lighthz_cfg_t *cfg ) 
{
    cfg->s1 = HAL_PIN_NC;
    cfg->s3 = HAL_PIN_NC;
    cfg->s2 = HAL_PIN_NC;
    cfg->s0 = HAL_PIN_NC;
    cfg->freq = HAL_PIN_NC;
}

err_t lighthz_init ( lighthz_t *ctx, lighthz_cfg_t *cfg ) 
{
    err_t error_flag = LIGHTHZ_OK;

    error_flag |= digital_out_init( &ctx->s1, cfg->s1 );
    error_flag |= digital_out_init( &ctx->s3, cfg->s3 );
    error_flag |= digital_out_init( &ctx->s2, cfg->s2 );
    error_flag |= digital_out_init( &ctx->s0, cfg->s0 );

    error_flag |= digital_in_init( &ctx->freq, cfg->freq );

    return error_flag;
}

void lighthz_set_s0_pin ( lighthz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->s0, state );
}

void lighthz_set_s1_pin ( lighthz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->s1, state );
}

void lighthz_set_s2_pin ( lighthz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->s2, state );
}

void lighthz_set_s3_pin ( lighthz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->s3, state );
}

void lighthz_set_sensitivity ( lighthz_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case LIGHTHZ_SENS_POWER_DOWN:
        {
            digital_out_low ( &ctx->s0 );
            digital_out_low ( &ctx->s1 );
            break;
        }
        case LIGHTHZ_SENS_1X:
        {
            digital_out_low ( &ctx->s0 );
            digital_out_high ( &ctx->s1 );
            break;
        }
        case LIGHTHZ_SENS_10X:
        {
            digital_out_high ( &ctx->s0 );
            digital_out_low ( &ctx->s1 );
            break;
        }
        case LIGHTHZ_SENS_100X:
        {
            digital_out_high ( &ctx->s0 );
            digital_out_high ( &ctx->s1 );
            break;
        }
        default:
        {
            break;
        }
    }
}

void lighthz_set_frequency_scaling ( lighthz_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case LIGHTHZ_FSCALE_1:
        {
            digital_out_low ( &ctx->s2 );
            digital_out_low ( &ctx->s3 );
            break;
        }
        case LIGHTHZ_FSCALE_2:
        {
            digital_out_low ( &ctx->s2 );
            digital_out_high ( &ctx->s3 );
            break;
        }
        case LIGHTHZ_FSCALE_10:
        {
            digital_out_high ( &ctx->s2 );
            digital_out_low ( &ctx->s3 );
            break;
        }
        case LIGHTHZ_FSCALE_100:
        {
            digital_out_high ( &ctx->s2 );
            digital_out_high ( &ctx->s3 );
            break;
        }
        default:
        {
            break;
        }
    }
}

uint8_t lighthz_get_freq_pin ( lighthz_t *ctx )
{
    return digital_in_read ( &ctx->freq );
}

// ------------------------------------------------------------------------- END
