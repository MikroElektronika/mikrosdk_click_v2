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

#include "charger13.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void charger13_cfg_setup ( charger13_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
}

CHARGER13_RETVAL charger13_init ( charger13_t *ctx, charger13_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return CHARGER13_OK;
}

void charger13_enable ( charger13_t *ctx )
{
    digital_out_low( &ctx->en );
}

void charger13_disable ( charger13_t *ctx )
{
    digital_out_high( &ctx->en );
}

uint8_t charger13_check ( charger13_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

