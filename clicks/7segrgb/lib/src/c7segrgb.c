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

#include "c7segrgb.h"

//

static c7segrgb_segment_t segmentar[ 8 ];

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS

static void dev_set_color ( c7segrgb_t *ctx, uint8_t green, uint8_t red, uint8_t blue );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->cs  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    
    cfg->logic_one = 0;
    cfg->logic_zero = 0;
}

C7SEGRGB_RETVAL c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg )
{
    
    ctx->logic_one = cfg->logic_one;
    ctx->logic_zero = cfg->logic_zero;
    
    if ( ( ctx->logic_one == 0 ) || ( ctx->logic_zero == 0 ) )
        return C7SEGRGB_INIT_ERROR;
    
    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

    digital_out_low( &ctx->cs );
    digital_out_low( &ctx->pwm );
    
    ctx->segments = segmentar;
    
    return C7SEGRGB_OK;
}


void c7segrgb_cs_low ( c7segrgb_t *ctx )
{
    digital_out_low( &ctx->cs );
}

void c7segrgb_cs_high ( c7segrgb_t *ctx )
{
    digital_out_high( &ctx->cs );
}

void c7segrgb_pwm_low ( c7segrgb_t *ctx )
{
    digital_out_low( &ctx->pwm);
}

void c7segrgb_pwm_high ( c7segrgb_t *ctx )
{
    digital_out_high( &ctx->pwm );
}




void c7segrgb_set_num ( c7segrgb_t *ctx, uint8_t  character, uint8_t green_brightness, uint8_t red_brightness, uint8_t blue_brightness )
{
    uint8_t tmp;
    uint8_t cnt;

    for ( cnt = 0; cnt < 8; cnt++ )
    {
        tmp = character >> cnt & 1;

        if ( tmp )
        {
            dev_set_color( ctx, green_brightness, red_brightness, blue_brightness );
        }
        else
        {
            dev_set_color( ctx, 0, 0, 0 );
        }
    }
}

void c7segrgb_set_seven_seg ( c7segrgb_t *ctx )
{
    uint8_t tmp;
    uint8_t cnt;

    for ( uint8_t cnt = 0; cnt < 8; cnt++ )
    {
        if ( ctx->segments[cnt].logic_lvl )
        {
            dev_set_color( ctx, ctx->segments[cnt].green,  ctx->segments[cnt].red,  ctx->segments[cnt].blue );
        }
        else
        {
            dev_set_color( ctx, 0, 0, 0 );
        }
    }
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS

static void dev_set_color ( c7segrgb_t *ctx, uint8_t green, uint8_t red, uint8_t blue )
{
    uint8_t tmp;
    int8_t cnt;

    for ( cnt = 7; cnt > -1; cnt-- )
    {
        tmp  = green >> cnt & 1;
        
        if ( tmp )
        {
            ctx->logic_one( );
        }
        else
        {
            ctx->logic_zero( );
        }
    }

    for ( cnt = 7; cnt > -1; cnt--  )
    {
        tmp = red >> cnt & 1;
        
        if ( tmp )
        {
            ctx->logic_one( );
        }
        else
        {
            ctx->logic_zero( );
        }
    }

    for ( cnt = 7; cnt > -1; cnt--  )
    {
        tmp = blue >> cnt & 1;
        
        if ( tmp )
        {
            ctx->logic_one( );
        }
        else
        {
            ctx->logic_zero( );
        }
    }
}

// ------------------------------------------------------------------------- END

