/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "comparator.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void comparator_cfg_setup ( comparator_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->o1   = HAL_PIN_NC;
    cfg->o2   = HAL_PIN_NC;
}

COMPARATOR_RETVAL comparator_init ( comparator_t *ctx, comparator_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->o1, cfg->o1 );
    digital_in_init( &ctx->o2, cfg->o2 );

    return COMPARATOR_OK;
}

uint8_t comparator_check_output_one ( comparator_t *ctx )
{
    if ( digital_in_read( &ctx->o1 ) )
    {
        return COMPARATOR_STATE_HIGH;
    }
    else
    {
        return COMPARATOR_STATE_LOW;
    }
}

uint8_t comparator_check_output_two ( comparator_t *ctx )
{
    if ( digital_in_read( &ctx->o2 ) )
    {
        return COMPARATOR_STATE_HIGH;
    }
    else
    {
        return COMPARATOR_STATE_LOW;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

