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
 * @file mic3.c
 * @brief MIC 3 Click Driver.
 */

#include "mic3.h"

void mic3_cfg_setup ( mic3_cfg_t *cfg ) 
{
    cfg->shd   = HAL_PIN_NC;
}

err_t mic3_init ( mic3_t *ctx, mic3_cfg_t *cfg ) 
{
   err_t return_flag = 0;
   
    return_flag = digital_out_init( &ctx->shd, cfg->shd );

    return return_flag;
}

err_t mic3_default_cfg ( mic3_t *ctx ) 
{
    digital_out_low( &ctx->shd );
    return MIC3_OK;
}

void mic3_shd_pin_set ( mic3_t *ctx, uint8_t state ) 
{
    if ( state == MIC3_PIN_STATE_HIGH ) {
        digital_out_high( &ctx->shd );
    } else {
        digital_out_low( &ctx->shd );
    }
    
}


// ------------------------------------------------------------------------- END
