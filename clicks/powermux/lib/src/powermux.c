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
 * @file powermux.c
 * @brief Power MUX Click Driver.
 */

#include "powermux.h"

void powermux_cfg_setup ( powermux_cfg_t *cfg ) 
{
    cfg->d0 = HAL_PIN_NC;
    cfg->d1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg ) 
{
   err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->d0, cfg->d0 );
    return_flag |= digital_out_init( &ctx->d1, cfg->d1 );

    return_flag |= digital_in_init( &ctx->int_pin, cfg->int_pin );

    return return_flag;
}

void powermux_default_cfg ( powermux_t *ctx ) 
{
    digital_out_high( &ctx->d0 );
    digital_out_low( &ctx->d1 );
}

uint8_t powermux_int_pin_read ( powermux_t *ctx ) 
{
   return digital_in_read( &ctx->int_pin );
}

void powermux_set_mode ( powermux_t *ctx, uint8_t mode )
{
    switch ( mode ) {
        case ( POWERMUX_INPUT_CHANNEL_1_ON ) : {
            digital_out_low( &ctx->d0 );
            digital_out_high( &ctx->d1 );
            break;
        }
        case ( POWERMUX_INPUT_CHANNEL_2_ON ) : {
            digital_out_low( &ctx->d0 );
            digital_out_low( &ctx->d1 );
            break;
        }
        case ( POWERMUX_INPUT_CHANNEL_OFF ) : {
            digital_out_high( &ctx->d0 );
            digital_out_high( &ctx->d1 );
            break;
        }
        case ( POWERMUX_INPUT_CHANNEL_AUTO ) : {
            digital_out_high( &ctx->d0 );
            digital_out_low( &ctx->d1 );
            break;
        }
        default : {
            digital_out_high( &ctx->d0 );
            digital_out_low( &ctx->d1 );
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
