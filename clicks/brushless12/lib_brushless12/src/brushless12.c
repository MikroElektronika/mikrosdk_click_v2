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
 * @file brushless12.c
 * @brief Brushless 12 Click Driver.
 */

#include "brushless12.h"

void brushless12_cfg_setup ( brushless12_cfg_t *cfg ) 
{
    cfg->brk  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
}

err_t brushless12_init ( brushless12_t *ctx, brushless12_cfg_t *cfg ) 
{
    err_t return_flag = 0;

    return_flag |=  digital_out_init( &ctx->brk, cfg->brk );
    return_flag |=  digital_out_init( &ctx->en, cfg->en );
    return_flag |=  digital_out_init( &ctx->dir, cfg->dir );

    return return_flag;
}

err_t brushless12_default_cfg ( brushless12_t *ctx ) 
{
    brushless12_set_direction ( ctx, BRUSHLESS12_DIR_FORWARD );
    brushless12_set_brake ( ctx, BRUSHLESS12_BRAKE );
    brushless12_set_enable ( ctx, BRUSHLESS12_ENABLE );
    
    return BRUSHLESS12_OK;
}

void brushless12_set_brake ( brushless12_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->brk, state );
}

void brushless12_set_direction ( brushless12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->dir, state );
}

void brushless12_set_enable ( brushless12_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

// ------------------------------------------------------------------------- END
