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
 * @file hallswitch6.c
 * @brief Hall Switch 6 Click Driver.
 */

#include "hallswitch6.h"

void hallswitch6_cfg_setup ( hallswitch6_cfg_t *cfg ) 
{
    cfg->ot1 = HAL_PIN_NC;
    cfg->ot2 = HAL_PIN_NC;
}

err_t hallswitch6_init ( hallswitch6_t *ctx, hallswitch6_cfg_t *cfg ) 
{
    err_t error_flag = HALLSWITCH6_OK;

    error_flag |= digital_in_init( &ctx->ot1, cfg->ot1 );
    error_flag |= digital_in_init( &ctx->ot2, cfg->ot2 );

    return error_flag;
}

uint8_t hallswitch6_get_out1_pin ( hallswitch6_t *ctx )
{
    return digital_in_read( &ctx->ot1 );
}

uint8_t hallswitch6_get_out2_pin ( hallswitch6_t *ctx )
{
    return digital_in_read( &ctx->ot2 );
}

uint8_t hallswitch6_get_pole ( hallswitch6_t *ctx )
{
    if ( HALLSWITCH6_PIN_STATE_LOW == digital_in_read( &ctx->ot1 ) )
    {
        return HALLSWITCH6_SOUTH_POLE;
    }
    else if ( HALLSWITCH6_PIN_STATE_LOW == digital_in_read( &ctx->ot2 ) )
    {
        return HALLSWITCH6_NORTH_POLE;
    }
    return HALLSWITCH6_NO_MAGNET;
}

// ------------------------------------------------------------------------- END
