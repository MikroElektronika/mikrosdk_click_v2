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


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c7segrgb_cfg_setup ( c7segrgb_cfg_t *cfg )
{
    // Additional gpio pins

    cfg->cs  = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
}

C7SEGRGB_RETVAL c7segrgb_init ( c7segrgb_t *ctx, c7segrgb_cfg_t *cfg )
{
    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->pwm, cfg->pwm );

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

float c7segrgb_get_delay_value ( uint8_t cyc_num )
{
    unsigned long clk;
    float delay_value;

    clk = Get_Fosc_kHz() / 1000; //get devices clock

    delay_value = ( cyc_num * clk ) / 72;
    return delay_value;
}

// ------------------------------------------------------------------------- END

