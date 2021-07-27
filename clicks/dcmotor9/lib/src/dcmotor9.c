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
 * \file dcmotor9.c
 *
 */

#include "dcmotor9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg )
{
    cfg->an  = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;
    cfg->pw1 = HAL_PIN_NC;
    cfg->pw2 = HAL_PIN_NC;

    cfg->pwm_freq   = DCMOTOR9_DEF_FREQ;
    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref       = DCMOTOR9_DEF_VREF;
}

err_t dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ACQUIRE_FAIL )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin = cfg->pw1;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR )
    {
        return PWM_ERROR;
    }

    pwm_set_freq( &ctx->pwm, cfg->pwm_freq );

    if ( digital_out_init( &ctx->shd, cfg->shd ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    if ( digital_out_init( &ctx->pw2, cfg->pw2 ) == DIGITAL_OUT_UNSUPPORTED_PIN )
    {
        return DIGITAL_OUT_UNSUPPORTED_PIN;
    }

    digital_out_high( &ctx->shd );

    return PWM_SUCCESS;
}

void dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void dcmotor9_pwm_stop ( dcmotor9_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void dcmotor9_pwm_start ( dcmotor9_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

// Enable the motor function

void dcmotor9_enable ( dcmotor9_t *ctx )
{
   digital_out_high( &ctx->shd );
}

// Disable the motor function

void dcmotor9_standby ( dcmotor9_t *ctx )
{
   digital_out_low( &ctx->shd );
}

// Set the direction of rotation in the counter clockwise direction function

void dcmotor9_counter_clockwise ( dcmotor9_t *ctx )
{
    digital_out_low( &ctx->pw2 );
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_100 );
}

// Set the direction of rotation in the clockwise direction function

void dcmotor9_clockwise ( dcmotor9_t *ctx )
{
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    digital_out_high( &ctx->pw2 );
}

// Brake the engine function

void dcmotor9_short_brake ( dcmotor9_t *ctx )
{
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_100 );
    digital_out_high( &ctx->pw2 );
}

// Stop the engine function

void dcmotor9_stop ( dcmotor9_t *ctx )
{
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    digital_out_low( &ctx->pw2 );
}

err_t dcmotor9_read_an_value ( dcmotor9_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor9_read_an_voltage ( dcmotor9_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------- END
