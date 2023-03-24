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

#include "c2x2key.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c2x2key_cfg_setup ( c2x2key_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->t1o  = HAL_PIN_NC;
    cfg->t2o  = HAL_PIN_NC;
    cfg->t3o  = HAL_PIN_NC;
    cfg->t4o  = HAL_PIN_NC;
    cfg->tint = HAL_PIN_NC;
}

C2X2KEY_RETVAL c2x2key_init ( c2x2key_t *ctx, c2x2key_cfg_t *cfg )
{

    // Input pins

    digital_in_init( &ctx->t1o, cfg->t1o );
    digital_in_init( &ctx->t2o, cfg->t2o );
    digital_in_init( &ctx->t3o, cfg->t3o );
    digital_in_init( &ctx->t4o, cfg->t4o );
    digital_in_init( &ctx->tint, cfg->tint );

    return C2X2KEY_OK;
}

uint8_t c2x2key_t1_state ( c2x2key_t *ctx )
{
    return digital_in_read( &ctx->t1o );
}

uint8_t c2x2key_t2_state ( c2x2key_t *ctx )
{
    return digital_in_read( &ctx->t2o );
}

uint8_t c2x2key_t3_state ( c2x2key_t *ctx )
{
    return digital_in_read( &ctx->t3o );
}

uint8_t c2x2key_t4_state ( c2x2key_t *ctx )
{
    return digital_in_read( &ctx->t4o );
}

uint8_t c2x2key_taster_pressed ( c2x2key_t *ctx )
{
    return digital_in_read( &ctx->tint );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

