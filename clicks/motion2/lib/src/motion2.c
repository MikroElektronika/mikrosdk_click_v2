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
 * @file motion2.c
 * @brief Motion 2 Click Driver.
 */

#include "motion2.h"

void motion2_cfg_setup ( motion2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

err_t motion2_init ( motion2_t *ctx, motion2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return MOTION2_OK;
}

void motion2_enable ( motion2_t *ctx, uint8_t state ) {
    if ( MOTION2_NO_DETECT_OBJECT == state )
    {
        digital_out_write( &ctx->en, 0 );
    }
    else
    {
        digital_out_write( &ctx->en, 1 );
    }
}

uint8_t motion2_detect_state ( motion2_t *ctx ) {
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

