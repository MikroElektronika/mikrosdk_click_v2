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

#include "hztov.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hztov_cfg_setup ( hztov_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    cfg->vo   = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en   = HAL_PIN_NC;

    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref         = 3.3;
    cfg->dev_pwm_freq = HZTOV_DEF_FREQ;
}

HZTOV_RETVAL hztov_init ( hztov_t *ctx, hztov_cfg_t *cfg )
{
    analog_in_config_t adc_cfg;
    pwm_config_t pwm_cfg;
    
    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->vo;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return HZTOV_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );

    return HZTOV_OK;
}

hztov_data_t hztov_generic_read ( hztov_t *ctx )
{
    hztov_data_t rx_data = 0;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

float hztov_read_voltage ( hztov_t *ctx )
{
    float rx_data = 0;

    analog_in_read_voltage( &ctx->adc, &rx_data );
    
    return rx_data;
}

void hztov_set_enable ( hztov_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

void hztov_set_duty_cycle ( hztov_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void hztov_pwm_stop ( hztov_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void hztov_pwm_start ( hztov_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void hztov_set_input_frequency ( hztov_t *ctx, uint16_t freq )
{
    if ( freq > 10000 )
    {
        freq = 10000;
    }
    else if ( freq < 1000 )
    {
        freq = 1000;
    }
    
    ctx->pwm_freq = ( uint32_t ) freq;
    pwm_set_freq( &ctx->pwm, ctx->pwm_freq );
    
    hztov_pwm_start ( ctx );
    hztov_set_duty_cycle ( ctx, 0.5 );
}

// ------------------------------------------------------------------------- END

