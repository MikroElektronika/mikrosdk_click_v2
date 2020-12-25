/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "boost6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void boost6_cfg_setup ( boost6_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
}

BOOST6_RETVAL boost6_init ( boost6_t *ctx, boost6_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return BOOST6_OK;
}

void boost6_hw_reset ( boost6_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void boost6_power_off ( boost6_t *ctx )
{
    digital_out_low( &ctx->cs );
}

void boost6_power_on ( boost6_t *ctx )
{
    digital_out_high( &ctx->cs );
}

// ------------------------------------------------------------------------- END

