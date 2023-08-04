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
 * @file zerocross.c
 * @brief Zero-Cross Click Driver.
 */

#include "zerocross.h"

void zerocross_cfg_setup ( zerocross_cfg_t *cfg ) 
{
    cfg->zc = HAL_PIN_NC;
}

err_t zerocross_init ( zerocross_t *ctx, zerocross_cfg_t *cfg ) 
{
    err_t error_flag = ZEROCROSS_OK;

    error_flag |= digital_in_init( &ctx->zc, cfg->zc );

    return error_flag;
}

uint8_t zerocross_pin_read ( zerocross_t *ctx ) 
{
    return digital_in_read( &ctx->zc );
}

void zerocross_get_freq ( zerocross_t *ctx, float *freq )
{
    uint16_t zc_cnt = 0;
    
    for ( uint16_t time_data = 0; time_data < 1000; time_data++ )
    {
        if ( ZEROCROSS_PIN_STATE_LOW == zerocross_pin_read( ctx ) )
        {
            zc_cnt++;
            while( ZEROCROSS_PIN_STATE_LOW == zerocross_pin_read( ctx ) );
        }
        else
        {
           Delay_1ms( ); 
        }
        
    }
    
    *freq = ( float ) ( zc_cnt / 2 );
}

// ------------------------------------------------------------------------- END
