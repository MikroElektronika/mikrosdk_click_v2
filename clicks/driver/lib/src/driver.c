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

#include "driver.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void driver_cfg_setup ( driver_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->in3   = HAL_PIN_NC;
    cfg->in4 = HAL_PIN_NC;
    cfg->in5 = HAL_PIN_NC;
}

DRIVER_RETVAL driver_init ( driver_t *ctx, driver_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->in3, cfg->in3 );
    digital_out_init( &ctx->in4, cfg->in4 );
    digital_out_init( &ctx->in5, cfg->in5 );
    digital_out_init( &ctx->in6, cfg->in6 );
    digital_out_init( &ctx->in7, cfg->in7 );

    return DRIVER_OK;
}

void driver_set_in1 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in1, state );
}

void driver_set_in2 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in2, state );
}

void driver_set_in3 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in3, state );
}

void driver_set_in4 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in4, state );
}

void driver_set_in5 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in5, state );
}

void driver_set_in6 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in6, state );
}

void driver_set_in7 ( driver_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->in7, state );
}

// ------------------------------------------------------------------------- END

