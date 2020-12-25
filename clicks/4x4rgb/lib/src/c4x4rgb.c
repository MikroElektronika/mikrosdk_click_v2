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



// ------------------------------------------------ PRIVATE VARIABLES

static uint32_t diode_array[ 16 ];
uint32_t * array;

// ------------------------------------------------ PUBLIC FUNCTION DECLARATIONS

static void dev_delay ( uint16_t delay_time, char delay_unit );

static void dev_init_diode ( c4x4rgb_t *ctx, uint32_t a_rgb_color, uint32_t diode_num );

static void dev_set_color ( c4x4rgb_t *ctx, uint32_t diode_num );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c4x4rgb_cfg_setup ( c4x4rgb_cfg_t *cfg, drv_logic_t logic_zero, drv_logic_t logic_one, uint8_t select_ctrl_pin )
{
    // Additional gpio pins
    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->out = HAL_PIN_NC;
    
    cfg->logic_zero = logic_zero;
    cfg->logic_one = logic_one;
    
    cfg->ctrl_pin = select_ctrl_pin;
}

C4X4RGB_RETVAL c4x4rgb_init ( c4x4rgb_t *ctx, c4x4rgb_cfg_t *cfg ) 
{
    // Output pins 
    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->out, cfg->out );
    
    ctx->logic_zero = cfg->logic_zero;
    ctx->logic_one = cfg->logic_one;
    
    if ( cfg->ctrl_pin == C4X4RGB_CTRL_PIN_IN2 )
    {
        ctx->ctrl_pin = ctx->in2;
    }
    else
    {
        ctx->ctrl_pin = ctx->in1;
    }
    
    array = &diode_array[ 0 ];

    return C4X4RGB_OK;
}

err_t c4x4rgb_set_diode ( c4x4rgb_t *ctx, uint32_t diode_num, uint32_t diode_color )
{
    uint32_t cnt_i;
    
    if (diode_num > 16)
        return -1;
    
    for ( cnt_i = 0; cnt_i < 16; cnt_i++ )
    {
        if ( cnt_i == diode_num - 1 )
        {
            dev_init_diode( ctx, diode_color, cnt_i );
            dev_set_color( ctx, cnt_i );
        }
        else
        {
           dev_set_color( ctx, cnt_i );
        }
    }

    dev_delay( 60, 'u' ); // reset delay
    return 0;
}



void c4x4rgb_fill_screen ( c4x4rgb_t *ctx, uint32_t fill_color, uint16_t fill_delay )
{
    int8_t cnt_i;

    for ( cnt_i = 0 ; cnt_i < 16; cnt_i++ )
    {
        c4x4rgb_set_diode( ctx, cnt_i+1, fill_color );
        dev_delay( fill_delay, 'm' );
    }
}


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

static void dev_delay ( uint16_t delay_time, char delay_unit )
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

static void dev_init_diode ( c4x4rgb_t *ctx, uint32_t a_rgb_color, uint32_t diode_num )
{
    *( array + diode_num ) = ( a_rgb_color & 0x000000FF ) | ( ( ( a_rgb_color & 0x00FF0000 ) >> 16 ) << 8 ) | ( ( ( a_rgb_color & 0x0000FF00 ) >> 8 ) << 16 );
}

static void dev_set_color ( c4x4rgb_t *ctx, uint32_t diode_num )
{    
    uint32_t cnt_i;
    uint32_t tmp;

    tmp = 1;

    for ( cnt_i = 0; cnt_i < 24; cnt_i++ )
    {
        if ( ( ( *( array + diode_num ) ) & ( tmp << ( 23 - cnt_i ) ) ) == 0 )
        {
            ctx->logic_zero(  );
        }
        else
        {
            ctx->logic_one(  );
        }
    }
}


// ------------------------------------------------------------------------- END

