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

#include "c4x4rgb.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
}

C4X4RGB_RETVAL c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg ) 
{
    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->out, cfg->out );

    return C4X4RGB_OK;
}

void c4x4rgb_logic_zero ( c4x4rgb_t *ctx )
{
    c4x4rgb_get_device_clock( ctx );
    digital_out_high( &ctx->in2 );
    Delay_Cyc( ctx->end_first );
    digital_out_low( &ctx->in2 );
    Delay_Cyc( ctx->end_second );
}

void c4x4rgb_logic_one ( c4x4rgb_t *ctx )
{
    c4x4rgb_get_device_clock( ctx );
    digital_out_high( &ctx->in2 );
    Delay_Cyc( ctx->end_second );
    digital_out_low( &ctx->in2 );
    Delay_Cyc( ctx->end_first );
}

void c4x4rgb_delay ( uint16_t delay_time, char delay_unit )
{
    uint16_t cnt;
    
    if ( delay_unit == 'm' ) // delay for milliseconds
    {
        for ( cnt = 0; cnt < delay_time; cnt++ )
        {
            Delay_1ms( );
        }
    }
    
    if ( delay_unit == 'u' ) // delay for microseconds
    {
        for ( cnt = 0; cnt < delay_time; cnt++ )
        {
            Delay_1us( );
        }
    }
}

void c4x4rgb_get_device_clock ( c4x4rgb_t *ctx )
{
    unsigned long clk;
    float one_cyc;

    ctx->first_delay = 0.024;
    ctx->second_delay = 0.048;
    clk = Get_Fosc_kHz() / 1000;
    
    one_cyc = ( float ) 1 / clk;
    ctx->first_delay = ctx->first_delay / one_cyc;
    ctx->second_delay = ctx->first_delay / one_cyc;

    if ( ( uint8_t ) ( ctx->first_delay ) == ( uint8_t ) ( ctx->first_delay ) )
    {
        ctx->end_first = ( uint8_t ) ( ctx->first_delay );
    }
    else
    {
        ctx->end_first =  ( uint8_t ) ( ctx->first_delay + 1 );
    }    
    if ( ( float ) ( ctx->second_delay ) == ( uint8_t ) ( ctx->second_delay ) )
    {
        ctx->end_second = ( uint8_t ) ( ctx->second_delay );
    }
    else
    {
        ctx->end_second = ( ( uint8_t ) ( ctx->second_delay ) + 1 );
    }
}

// ------------------------------------------------------------------------- END

