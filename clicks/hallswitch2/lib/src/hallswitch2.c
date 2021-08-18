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
 * @file hallswitch2.c
 * @brief Hall Switch 2 Click Driver.
 */

#include "hallswitch2.h"

void hallswitch2_cfg_setup ( hallswitch2_cfg_t *cfg ) 
{
    cfg->n = HAL_PIN_NC;
    cfg->s = HAL_PIN_NC;
}

err_t hallswitch2_init ( hallswitch2_t *ctx, hallswitch2_cfg_t *cfg ) 
{
    err_t return_flag = digital_in_init( &ctx->n, cfg->n );
    return_flag |= digital_in_init( &ctx->s, cfg->s );

    return return_flag;
}

uint8_t hallswitch2_check_state ( hallswitch2_t *ctx ) 
{
    if ( !digital_in_read( &ctx->n ) )
    {
        return HALLSWITCH2_N_POLE_DETECTED;
    }

    if ( !digital_in_read( &ctx->s ) )
    {
        return HALLSWITCH2_S_POLE_DETECTED;
    }

    return HALLSWITCH2_NO_MAGNET_DETECTED;
}

// ------------------------------------------------------------------------- END
