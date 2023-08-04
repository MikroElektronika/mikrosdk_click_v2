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

#include "analogmux.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void analogmux_cfg_setup ( analogmux_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->s0 = HAL_PIN_NC;
    cfg->s3 = HAL_PIN_NC;
    cfg->s1 = HAL_PIN_NC;
    cfg->s2 = HAL_PIN_NC;

    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref         = 3.3;
}

ANALOGMUX_RETVAL analogmux_init ( analogmux_t *ctx, analogmux_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ANALOGMUX_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Output pins 

    digital_out_init( &ctx->s0, cfg->s0 );
    digital_out_init( &ctx->s3, cfg->s3 );
    digital_out_init( &ctx->s1, cfg->s1 );
    digital_out_init( &ctx->s2, cfg->s2 );

    return ANALOGMUX_OK;
}

uint16_t analogmux_generic_read ( analogmux_t *ctx )
{
    uint16_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

float analogmux_generic_read_voltage ( analogmux_t *ctx )
{
    float voltage;
    
    analog_in_read_voltage( &ctx->adc, &voltage );

    return voltage;
} 

void analogmux_set_channel ( analogmux_t *ctx, uint8_t cfg )
{
    digital_out_write( &ctx->s0, cfg & 0x01 );
    digital_out_write( &ctx->s1, ( cfg >> 1 ) & 0x01 );
    digital_out_write( &ctx->s2, ( cfg >> 2 ) & 0x01 );
    digital_out_write( &ctx->s3, ( cfg >> 3 ) & 0x01 );
}

// ------------------------------------------------------------------------- END

