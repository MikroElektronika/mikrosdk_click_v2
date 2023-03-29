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
 * @file brushless16.c
 * @brief Brushless 16 Click Driver.
 */

#include "brushless16.h"

void brushless16_cfg_setup ( brushless16_cfg_t *cfg ) 
{
    cfg->en   = HAL_PIN_NC;
    cfg->fg = HAL_PIN_NC;
    cfg->rd = HAL_PIN_NC;
}

err_t brushless16_init ( brushless16_t *ctx, brushless16_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |= digital_out_init( &ctx->en, cfg->en );
    
    return_flag |= digital_in_init( &ctx->fg, cfg->fg );
    return_flag |= digital_in_init( &ctx->rd, cfg->rd );

    return return_flag;
}

void brushless16_set_en ( brushless16_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t brushless16_get_rd ( brushless16_t *ctx )
{
    return digital_in_read( &ctx->fg );
}

uint8_t brushless16_get_fg ( brushless16_t *ctx )
{
    return digital_in_read( &ctx->rd );
}

// ------------------------------------------------------------------------- END
