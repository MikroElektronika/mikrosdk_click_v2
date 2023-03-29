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

#include "hallcurrent5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallcurrent5_cfg_setup ( hallcurrent5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
    
    cfg->init_volt = 316;
}

HALLCURRENT5_RETVAL hallcurrent5_init ( hallcurrent5_t *ctx, hallcurrent5_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if (  analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return HALLCURRENT5_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return HALLCURRENT5_OK;
}

hallcurrent5_data_t hallcurrent5_generic_read ( hallcurrent5_t *ctx )
{
    hallcurrent5_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

float hallcurrent5_generic_read_voltage ( hallcurrent5_t *ctx )
{
    float voltage;

    analog_in_read_voltage( &ctx->adc, &voltage );
    
    return voltage;
}

float hallcurrent5_get_current ( hallcurrent5_t *ctx )
{
    float voltage;
    float current;
    
    voltage = hallcurrent5_generic_read_voltage( ctx );
    voltage *= 1000;
    current = ( ( voltage - ctx->dev_init_volt - 12 ) / 66.0 ) * 1000.0;
    
    return current;
}

uint8_t hallcurrent5_get_fault ( hallcurrent5_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void hallcurrent5_set_init_voltage ( hallcurrent5_t *ctx, uint16_t voltage )
{
    ctx->dev_init_volt = voltage;
}

// ------------------------------------------------------------------------- END

