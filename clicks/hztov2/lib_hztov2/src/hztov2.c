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

#include "hztov2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hztov2_cfg_setup ( hztov2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->an_pin = HAL_PIN_NC;
    cfg->fin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en  = HAL_PIN_NC;

    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref         = 3.3;
    cfg->dev_pwm_freq   = HZTOV2_DEF_FREQ;
}

HZTOV2_RETVAL hztov2_init ( hztov2_t *ctx, hztov2_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;
    pwm_config_t pwm_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return HZTOV2_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->fin;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->fin, &pwm_cfg );
    pwm_set_freq( &ctx->fin, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    return HZTOV2_OK;
}

hztov2_data_t hztov2_generic_read ( hztov2_t *ctx )
{
    hztov2_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

float hztov2_read_voltage ( hztov2_t *ctx )
{
    float rx_data;

    analog_in_read_voltage( &ctx->adc, &rx_data );
    
    return rx_data;
}

void hztov2_en_pin ( hztov2_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->en, pin_state );
}

HZTOV2_RETVAL hztov2_fin_set ( hztov2_t *ctx, uint32_t fin )
{
    if ( fin < 200 || fin > 120000 )
        return 1;
        
    ctx->pwm_freq = fin;
    pwm_set_freq( &ctx->fin, ctx->pwm_freq );
    
    pwm_start( &ctx->fin ); 
    pwm_set_duty( &ctx->fin, 0.5 ); 
    
    return 0;
}

// ------------------------------------------------------------------------- END

