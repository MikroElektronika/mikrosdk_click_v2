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

#include "linefollower.h"

// ------------------------------------------------------------- PRIVATE MACROS 


// -------------------------------------------------------------- PRIVATE TYPES


// ------------------------------------------------------------------ CONSTANTS


// ------------------------------------------------------------------ VARIABLES


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t dev_linefollower_get_sensor_data ( linefollower_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void linefollower_cfg_setup ( linefollower_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->u1 = HAL_PIN_NC;
    cfg->u2 = HAL_PIN_NC;
    cfg->u3 = HAL_PIN_NC;
    cfg->u4 = HAL_PIN_NC;
    cfg->u5 = HAL_PIN_NC;
}

LINEFOLLOWER_RETVAL linefollower_init ( linefollower_t *ctx, linefollower_cfg_t *cfg )
{
    // Input pins

    digital_in_init( &ctx->u1, cfg->u1 );
    digital_in_init( &ctx->u2, cfg->u2 );
    digital_in_init( &ctx->u3, cfg->u3 );
    digital_in_init( &ctx->u4, cfg->u4 );
    digital_in_init( &ctx->u5, cfg->u5 );

    return LINEFOLLOWER_OK;
}

uint8_t linefollower_get_u1 ( linefollower_t *ctx )
{
    return digital_in_read( &ctx->u1 );
}

uint8_t linefollower_get_u2 ( linefollower_t *ctx )
{
    return digital_in_read( &ctx->u2 );
}

uint8_t linefollower_get_u3 ( linefollower_t *ctx )
{
    return digital_in_read( &ctx->u3 );
}

uint8_t linefollower_get_u4 ( linefollower_t *ctx )
{
    return digital_in_read( &ctx->u4 );
}

uint8_t linefollower_get_u5 ( linefollower_t *ctx )
{
    return digital_in_read( &ctx->u5 );
}

void linefollower_data_track ( linefollower_t *ctx, linefollower_direction_t *data_track )
{
    data_track->u1 = digital_in_read( &ctx->u1 );
    data_track->u2 = digital_in_read( &ctx->u2 );
    data_track->u3 = digital_in_read( &ctx->u3 );
    data_track->u4 = digital_in_read( &ctx->u4 );
    data_track->u5 = digital_in_read( &ctx->u5 );
}

uint8_t linefollower_get_direction ( linefollower_t *ctx )
{
    uint8_t dir_data;
    uint8_t result;

    dir_data = dev_linefollower_get_sensor_data ( ctx );
    
    switch ( dir_data )
    {
        case LINEFOLLOWER_DATA_DIR_1 :
        {
            result = LINEFOLLOWER_DIR_SHARP_RIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_2 :
        {
            result = LINEFOLLOWER_DIR_RIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_3 :
        {
            result = LINEFOLLOWER_DIR_SHARP_RIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_4 :
        {
            result = LINEFOLLOWER_DIR_STRAIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_6 :
        {
            result = LINEFOLLOWER_DIR_RIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_7 :
        {
            result = LINEFOLLOWER_DIR_SHARP_RIGHT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_8 :
        {
            result = LINEFOLLOWER_DIR_LEFT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_12 :
        {
            result = LINEFOLLOWER_DIR_LEFT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_16 :
        {
            result = LINEFOLLOWER_DIR_SHARP_LEFT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_24 :
        {
            result = LINEFOLLOWER_DIR_SHARP_LEFT;
            break;
        }
        
        case LINEFOLLOWER_DATA_DIR_28 :
        {
            result = LINEFOLLOWER_DIR_SHARP_LEFT;
            break;
        }
        case LINEFOLLOWER_DATA_DIR_31 :
        {
            result = LINEFOLLOWER_DIR_STRAIGHT;
            break;
        }
        default:
        {
            result = LINEFOLLOWER_DIR_TRACKING_LOST;
            break;
        }
    }
        
     return result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t dev_linefollower_get_sensor_data ( linefollower_t *ctx )
{
    uint8_t dir_data;

    dir_data = LINEFOLLOWER_DATA_DIR_START;

    dir_data |= ( linefollower_get_u5 ( ctx ) << 4 ) & LINEFOLLOWER_BIT_4;
    dir_data |= ( linefollower_get_u4 ( ctx ) << 3 ) & LINEFOLLOWER_BIT_3;
    dir_data |= ( linefollower_get_u3 ( ctx ) << 2 ) & LINEFOLLOWER_BIT_2;
    dir_data |= ( linefollower_get_u2 ( ctx ) << 1 ) & LINEFOLLOWER_BIT_1;
    dir_data |= linefollower_get_u1 ( ctx ) & LINEFOLLOWER_BIT_0;

    return dir_data;
}

// ------------------------------------------------------------------------- END

