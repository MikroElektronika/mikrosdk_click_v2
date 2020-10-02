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

#include "stepdown2.h" 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stepdown2_cfg_setup ( stepdown2_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->err = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
}

STEPDOWN2_RETVAL stepdown2_init ( stepdown2_t *ctx, stepdown2_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->err, cfg->err );

    return STEPDOWN2_OK;
}

uint8_t stepdown2_digital_read_rst ( stepdown2_t *ctx )
{
    return digital_in_read( &ctx->err );
} 

void stepdown2_digital_write_cs ( stepdown2_t *ctx, uint8_t signal )
{
    digital_out_write( &ctx->en, signal );
}

// ------------------------------------------------------------------------- END

