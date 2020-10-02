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

#include "battman.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void battman_cfg_setup ( battman_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->chg = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;
}

BATTMAN_RETVAL battman_init ( battman_t *ctx, battman_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->chg, cfg->chg );
    digital_in_init( &ctx->flt, cfg->flt );

    digital_out_high( &ctx->en );

    return BATTMAN_OK;
}

void battman_set_enable ( battman_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

uint8_t battman_get_charging_indicator ( battman_t *ctx )
{
    return digital_in_read(  &ctx->chg );
}

uint8_t battman_get_fault_indicator ( battman_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END

