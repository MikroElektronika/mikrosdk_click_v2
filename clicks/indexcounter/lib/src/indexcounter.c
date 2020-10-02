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

#include "indexcounter.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void indexcounter_cfg_setup ( indexcounter_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->dir   = HAL_PIN_NC;
    cfg->spd = HAL_PIN_NC;
}

INDEXCOUNTER_RETVAL indexcounter_init ( indexcounter_t *ctx, indexcounter_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->dir, cfg->dir );
    digital_in_init( &ctx->spd, cfg->spd );

    return INDEXCOUNTER_OK;
}

// Get direction pin states function

uint8_t indexcounter_get_dir ( indexcounter_t *ctx )
{
    
    uint8_t state;

    state = digital_in_read( &ctx->dir ); 

    if ( state == 1 )
    {
        return INDEXCOUNTER_ACTIVE;
    }
    else
    {
        return INDEXCOUNTER_INACTIVE;
    }
}

// Get state of the speed pin function

uint8_t indexcounter_get_speed ( indexcounter_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->spd ); 

    if ( state == 1 )
    {
        return INDEXCOUNTER_ACTIVE;
    }
    else
    {
        return INDEXCOUNTER_INACTIVE;
    }
}

// ------------------------------------------------------------------------- END

