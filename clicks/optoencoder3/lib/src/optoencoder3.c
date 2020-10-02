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

#include "optoencoder3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define STARTING_SWIPE  1
#define STOPED_SWIPE    0

#define STAGE_0         0
#define STAGE_1         1
#define STAGE_2         2
#define STAGE_3         3

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void swiper ( optoencoder3_t *ctx );
static void swiping_dir_checker ( optoencoder3_t *ctx );
static void stage_checker ( optoencoder3_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void optoencoder3_cfg_setup ( optoencoder3_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->o1 = HAL_PIN_NC;
    cfg->o2 = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->o4 = HAL_PIN_NC;
    cfg->o3 = HAL_PIN_NC;
}

OPTOENCODER3_RETVAL optoencoder3_init ( optoencoder3_t *ctx, optoencoder3_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->o1, cfg->o1 );
    digital_in_init( &ctx->o2, cfg->o2 );
    digital_in_init( &ctx->o4, cfg->o4 );
    digital_in_init( &ctx->o3, cfg->o3 );
    
    ctx->dev_cnt          = 0;
    ctx->dev_swipe_cnt    = 0;
    ctx->dev_swiping_dir  = 0;
    ctx->dev_stage        = 0;

    return OPTOENCODER3_OK;
}

void optoencoder3_enabler ( optoencoder3_t *ctx, uint8_t active )
{
    digital_out_write ( &ctx->en, active );
}

uint8_t optoencoder3_read_pin_o1 ( optoencoder3_t *ctx )
{
    return digital_in_read( &ctx->o1 );
}

uint8_t optoencoder3_read_pin_o2 ( optoencoder3_t *ctx )
{
    return digital_in_read( &ctx->o2 );
}

uint8_t optoencoder3_read_pin_o3 ( optoencoder3_t *ctx )
{
    return digital_in_read( &ctx->o3 );
}

uint8_t optoencoder3_read_pin_o4 ( optoencoder3_t *ctx )
{
    return digital_in_read( &ctx->o4 );
}

uint8_t optoencoder3_cnt ( optoencoder3_t *ctx )
{
    swiper( ctx );
    return ctx->dev_cnt;
}

int8_t optoencoder3_dir_cnt ( optoencoder3_t *ctx )
{
    swiper( ctx );
    return ctx->dev_swipe_cnt;
}

void optoencoder3_reset_counters ( optoencoder3_t *ctx )
{
    ctx->dev_cnt = 0;
    ctx->dev_swipe_cnt = 0;
}

void optoencoder3_read_all_pins ( optoencoder3_t *ctx, optoencoder3_pins_t *pins )
{
    pins->pin_o1 = optoencoder3_read_pin_o1( ctx );
    pins->pin_o2 = optoencoder3_read_pin_o2( ctx );
    pins->pin_o3 = optoencoder3_read_pin_o3( ctx );
    pins->pin_o4 = optoencoder3_read_pin_o4( ctx );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void swiping_dir_checker ( optoencoder3_t *ctx )
{
    if ( optoencoder3_read_pin_o1( ctx ) == 0 || 
         optoencoder3_read_pin_o2( ctx ) == 0 ||
         optoencoder3_read_pin_o3( ctx ) == 0 ||
         optoencoder3_read_pin_o4( ctx ) == 0 )
    {
        ctx->dev_swiping_dir = STARTING_SWIPE;
    }
    else
    {
        ctx->dev_swiping_dir = STOPED_SWIPE;
    }
}

static void stage_checker ( optoencoder3_t *ctx )
{
    swiping_dir_checker( ctx );
    if ( ctx->dev_swiping_dir == STARTING_SWIPE )
    {
        if ( ( optoencoder3_read_pin_o1( ctx ) == 0 || optoencoder3_read_pin_o2( ctx ) == 0 ) &&
             ( optoencoder3_read_pin_o3( ctx ) == 1 || optoencoder3_read_pin_o4( ctx ) == 1 ) )
        {
            ctx->dev_stage = STAGE_1;
        }

        if ( ( optoencoder3_read_pin_o1( ctx ) == 0 || optoencoder3_read_pin_o2( ctx ) == 0 ) &&
             ( optoencoder3_read_pin_o3( ctx ) == 0 || optoencoder3_read_pin_o4( ctx ) == 0 ) )
        {
            ctx->dev_stage = STAGE_2;
        }

        if ( ( optoencoder3_read_pin_o1( ctx ) == 1 || optoencoder3_read_pin_o2( ctx ) == 1 ) &&
             ( optoencoder3_read_pin_o3( ctx ) == 0 || optoencoder3_read_pin_o4( ctx ) == 0 ) )
        {
            ctx->dev_stage = STAGE_3;
        }
    }
    else
    {
        ctx->dev_stage = STAGE_0;
    }
}

static void swiper ( optoencoder3_t *ctx )
{
    stage_checker( ctx );
    if ( ctx->dev_stage == STAGE_1 )
    {
        while ( ctx->dev_stage != STAGE_2 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_0 )
            {
                return;
            }
        }

        while ( ctx->dev_stage != STAGE_3 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_0 )
            {
                return;
            }
        }

        while ( ctx->dev_stage != STAGE_0 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_0 )
            {
                ctx->dev_swipe_cnt++;
                ctx->dev_cnt++;
                return;
            }
        }
    }

    if ( ctx->dev_stage == STAGE_3 )
    {
        while ( ctx->dev_stage != STAGE_2 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_1 )
            {
                return;
            }
        }

        while ( ctx->dev_stage != STAGE_1 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_0 )
            {
                return;
            }
        }

        while ( ctx->dev_stage != STAGE_0 )
        {
            stage_checker( ctx );
            if ( ctx->dev_stage == STAGE_0 )
            {
                ctx->dev_swipe_cnt--;
                ctx->dev_cnt++;
                return;
            }
        }
    }
}

// ------------------------------------------------------------------------- END

