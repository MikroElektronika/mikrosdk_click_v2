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

#include "flame.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void flame_cfg_setup ( flame_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

FLAME_RETVAL flame_init ( flame_t *ctx, flame_cfg_t *cfg )
{

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return FLAME_OK;
}

uint8_t flame_check_status ( flame_t *ctx )
{
    return digital_in_read ( &ctx->an );  
}

uint8_t flame_get_interrupt ( flame_t *ctx )
{
     return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

