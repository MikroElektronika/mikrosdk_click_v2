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

#include "brushless.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0 

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void brushless_cfg_setup ( brushless_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    cfg->an_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dir = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq 	  = BRUSHLESS_DEF_FREQ;

    cfg->resolution   = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref         = 3.3;
}

BRUSHLESS_RETVAL brushless_init ( brushless_t *ctx, brushless_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    analog_in_config_t adc_cfg;
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin  = cfg->an_pin;
 
    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return BRUSHLESS_INIT_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // Output pins 

    digital_out_init( &ctx->dir, cfg->dir );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BRUSHLESS_OK;
}

void brushless_set_duty_cycle ( brushless_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void brushless_pwm_stop ( brushless_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void brushless_pwm_start ( brushless_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

brushless_data_t brushless_generic_read ( brushless_t *ctx )
{
    brushless_data_t rx_data;

    analog_in_read( &ctx->adc, &rx_data );
    
    return rx_data;
}

void brushless_spin_clockwise ( brushless_t *ctx )
{
    digital_out_high( &ctx->dir );
}

void brushless_spin_counter_clockwise ( brushless_t *ctx )
{
    digital_out_low( &ctx->dir );
}

uint8_t brushless_read_rotation_speed_sensor_output ( brushless_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

