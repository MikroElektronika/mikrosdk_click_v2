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
 * @file rfswitch2.c
 * @brief RF Switch 2 Click Driver.
 */

#include "rfswitch2.h"

void rfswitch2_cfg_setup ( rfswitch2_cfg_t *cfg ) 
{
    cfg->v1_pin = HAL_PIN_NC;
    cfg->v2_pin = HAL_PIN_NC;
    cfg->v3_pin = HAL_PIN_NC;
}

err_t rfswitch2_init ( rfswitch2_t *ctx, rfswitch2_cfg_t *cfg ) 
{
    err_t error_flag = RFSWITCH2_OK;

    error_flag |= digital_out_init( &ctx->v1_pin, cfg->v1_pin );
    error_flag |= digital_out_init( &ctx->v2_pin, cfg->v2_pin );
    error_flag |= digital_out_init( &ctx->v3_pin, cfg->v3_pin );
    Delay_1ms ( );
    digital_out_high( &ctx->v1_pin );
    digital_out_high( &ctx->v2_pin );
    digital_out_high( &ctx->v3_pin );
    Delay_1ms ( );

    return error_flag;
}

void rfswitch2_set_mode ( rfswitch2_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case RFSWITCH2_MODE_RF1_ON:
        {
            digital_out_high( &ctx->v1_pin );
            digital_out_low( &ctx->v2_pin );
            digital_out_low( &ctx->v3_pin );
            break;
        }
        case RFSWITCH2_MODE_RF2_ON:
        {
            digital_out_low( &ctx->v1_pin );
            digital_out_high( &ctx->v2_pin );
            digital_out_low( &ctx->v3_pin );
            break;
        }
        case RFSWITCH2_MODE_RF3_ON:
        {
            digital_out_high( &ctx->v1_pin );
            digital_out_high( &ctx->v2_pin );
            digital_out_low( &ctx->v3_pin );
            break;
        }
        case RFSWITCH2_MODE_RF4_ON:
        {
            digital_out_low( &ctx->v1_pin );
            digital_out_low( &ctx->v2_pin );
            digital_out_low( &ctx->v3_pin );
            break;
        }
        default:
        {
            digital_out_high( &ctx->v1_pin );
            digital_out_high( &ctx->v2_pin );
            digital_out_high( &ctx->v3_pin );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
