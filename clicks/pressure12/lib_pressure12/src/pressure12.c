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

#include "pressure12.h"

// ------------------------------------------------------------- PRIVATE MACROS

#define PRESSURE12_VSUPPLY  3.3
#define PRESSURE12_PMAX_MIN  0.6

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void pressure12_cfg_setup ( pressure12_cfg_t *cfg )
{
    cfg->an_pin = HAL_PIN_NC;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = 3.3;
}

err_t pressure12_init ( pressure12_t *ctx, pressure12_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    return ADC_SUCCESS;
}

err_t pressure12_read_pin_adc ( pressure12_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t pressure12_read_pin_voltage ( pressure12_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t pressure12_get_pressure ( pressure12_t *ctx, uint16_t *data_out )
{
    float voltage = 0;
    float pressure = 0;

    if ( pressure12_read_pin_voltage( ctx, &voltage ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    pressure = voltage - ( 0.1 * PRESSURE12_VSUPPLY );
    pressure = pressure / ( ( 0.8 * PRESSURE12_VSUPPLY ) / PRESSURE12_PMAX_MIN );
    pressure *= 1000;
    
    *data_out = ( uint16_t ) pressure;
    
    return ADC_SUCCESS;
}

// ------------------------------------------------------------------------- END
