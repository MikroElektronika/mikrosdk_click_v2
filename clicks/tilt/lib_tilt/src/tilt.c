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

#include "tilt.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

//  Check the state of vo1 ( PWM ) pin function
static uint8_t dev_state_vo1 ( tilt_t *ctx );

//  Check the state of vo2 ( INT ) pin function
static uint8_t dev_state_vo2 ( tilt_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void tilt_cfg_setup ( tilt_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->vo1 = HAL_PIN_NC;
    cfg->vo2 = HAL_PIN_NC;
}

TILT_RETVAL tilt_init ( tilt_t *ctx, tilt_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->vo1, cfg->vo1 );
    digital_in_init( &ctx->vo2, cfg->vo2 );

    return TILT_OK;
}

uint8_t tilt_left ( tilt_t *ctx )
{
    uint8_t tmp;
    
    tmp = TILT_NO_DETECTION;
    
    if ( dev_state_vo1( ctx ) == TILT_DETECTION )
    {
        if ( dev_state_vo2( ctx ) == TILT_NO_DETECTION )
        {
            tmp = TILT_DETECTION;
        }
    }
    
    return tmp;
}

uint8_t tilt_right ( tilt_t *ctx )
{
    uint8_t tmp;

    tmp = TILT_NO_DETECTION;

    if ( dev_state_vo1( ctx ) == TILT_NO_DETECTION )
    {
        if ( dev_state_vo2( ctx ) == TILT_DETECTION )
        {
            tmp = TILT_DETECTION;
        }
    }

    return tmp;
}

uint8_t tilt_up ( tilt_t *ctx )
{
    uint8_t tmp;

    tmp = TILT_NO_DETECTION;

    if ( dev_state_vo1( ctx ) == TILT_NO_DETECTION )
    {
        if ( dev_state_vo2( ctx ) == TILT_NO_DETECTION )
        {
            tmp = TILT_DETECTION;
        }
    }

    return tmp;
}

uint8_t tilt_down ( tilt_t *ctx )
{
    uint8_t tmp;

    tmp = TILT_NO_DETECTION;

    if ( dev_state_vo1( ctx ) == TILT_DETECTION )
    {
        if ( dev_state_vo2( ctx ) == TILT_DETECTION )
        {
            tmp = TILT_DETECTION;
        }
    }

    return tmp;
}

uint8_t tilt_direction ( tilt_t *ctx )
{
    uint8_t tmp;

    tmp = TILT_NO_DETECTION;

    if ( tilt_left( ctx ) )
    {
        tmp = TILT_LEFT_DETECTION;
    }
    
    if ( tilt_right( ctx ) )
    {
        tmp = TILT_RIGHT_DETECTION;
    }
    
    if ( tilt_up( ctx ) )
    {
        tmp = TILT_UP_DETECTION;
    }
    
    if ( tilt_down( ctx ) )
    {
        tmp = TILT_DOWN_DETECTION;
    }

    return tmp;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_state_vo1 ( tilt_t *ctx )
{
    return digital_in_read( &ctx->vo1 );
}

static uint8_t dev_state_vo2 ( tilt_t *ctx )
{
    return digital_in_read( &ctx->vo2 );
}

// ------------------------------------------------------------------------- END

