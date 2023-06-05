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

#include "peltier.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void peltier_cfg_setup ( peltier_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->en2 = HAL_PIN_NC;
    cfg->en1   = HAL_PIN_NC;
    cfg->chg = HAL_PIN_NC;
    cfg->con = HAL_PIN_NC;
}

PELTIER_RETVAL peltier_init ( peltier_t *ctx, peltier_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en2, cfg->en2 );
    digital_out_init( &ctx->en1, cfg->en1 );

    // Input pins

    digital_in_init( &ctx->chg, cfg->chg );
    digital_in_init( &ctx->con, cfg->con );

    return PELTIER_OK;
}

void peltier_enable_ldo2 ( peltier_t *ctx )
{
    digital_out_high( &ctx->en2 );
}

void peltier_disable_ldo2 ( peltier_t *ctx )
{
    digital_out_low( &ctx->en2 );
}

void peltier_enable_ldo1 ( peltier_t *ctx )
{
    digital_out_high( &ctx->en1 );
}

void peltier_disable_ldo1 ( peltier_t *ctx )
{
    digital_out_low( &ctx->en1 );
}

uint8_t peltier_battery_charge ( peltier_t *ctx )
{
    return digital_in_read( &ctx->chg );
}

uint8_t peltier_vin_good_flag ( peltier_t *ctx )
{
    return digital_in_read( &ctx->con );
}

// ------------------------------------------------------------------------- END

