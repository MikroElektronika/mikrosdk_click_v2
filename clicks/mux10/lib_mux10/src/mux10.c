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
 * @file mux10.c
 * @brief MUX 10 Click Driver.
 */

#include "mux10.h"

void mux10_cfg_setup ( mux10_cfg_t *cfg ) 
{
    cfg->a1 = HAL_PIN_NC;
    cfg->a0 = HAL_PIN_NC;
}

err_t mux10_init ( mux10_t *ctx, mux10_cfg_t *cfg ) 
{         
    err_t error_flag = MUX10_OK;

    error_flag |= digital_out_init( &ctx->a1, cfg->a1 );
    error_flag |= digital_out_init( &ctx->a0, cfg->a0 );

    return error_flag;
}

void mux10_set_a0 ( mux10_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->a0, state );
}

void mux10_set_a1 ( mux10_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->a1, state );
}

err_t mux10_active_channel_sel ( mux10_t *ctx, uint8_t sel_ch ) 
{   
    err_t error_flag = MUX10_OK;

    if ( ( MUX10_SELECT_CH_1 > sel_ch ) || ( MUX10_SELECT_CH_4 < sel_ch ) ) 
    {
        return MUX10_ERROR;
    }
    
    /*  sel_ch   |  ch_addr  |  A1A0b
     *    1            0         00 
     *    2            1         01 
     *    3            2         10 
     *    4            3         11  */
    uint8_t ch_addr = sel_ch - 1;
    mux10_set_a1( ctx, ( ch_addr >> 1 ) & 0x01 );
    mux10_set_a0( ctx, ch_addr & 0x01 );

    return error_flag;
}

// ------------------------------------------------------------------------- END
