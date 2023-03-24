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

#include "opto4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void opto4_cfg_setup ( opto4_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->cs   = HAL_PIN_NC;
}

OPTO4_RETVAL opto4_init ( opto4_t *ctx, opto4_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );

    return OPTO4_OK;
}

void opto4_output_enable ( opto4_t *ctx, uint8_t enable )
{
    digital_out_write( &ctx->cs, enable );
}

// ------------------------------------------------------------------------- END

