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
 * @file opto5.c
 * @brief Opto 5 Click Driver.
 */

#include "opto5.h"

void opto5_cfg_setup ( opto5_cfg_t *cfg ) {
    cfg->pwm = HAL_PIN_NC;
}

err_t opto5_init ( opto5_t *ctx, opto5_cfg_t *cfg ) {
    err_t return_flag = 0;

    return_flag |=  digital_out_init( &ctx->pwm, cfg->pwm );

    return return_flag;
}

void opto5_default_cfg ( opto5_t *ctx ) {
    // Click default configuration.
    opto5_pin_set( ctx );
}

void opto5_pin_set ( opto5_t *ctx ) {
    digital_out_high( &ctx->pwm );
}

void opto5_pin_clear ( opto5_t *ctx ) {
    digital_out_low( &ctx->pwm );
}

void opto5_pin_toggle ( opto5_t *ctx ) {
    digital_out_toggle( &ctx->pwm );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
