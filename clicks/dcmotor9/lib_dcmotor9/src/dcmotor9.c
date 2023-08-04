/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file dcmotor9.c
 * @brief DC Motor 9 Click Driver.
 */

#include "dcmotor9.h"

void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;
    cfg->pw1 = HAL_PIN_NC;
    cfg->pw2   = HAL_PIN_NC;
   
    cfg->dev_pwm_freq = DCMOTOR9_DEF_FREQ;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT;
    cfg->vref       = DCMOTOR9_DEF_VREF;
}

err_t dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;
    analog_in_config_t adc_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) {
        return ADC_ERROR;
    }
    
    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin = cfg->pw1;

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) {
        return ADC_ERROR;
    }
    
    pwm_set_freq( &ctx->pwm, cfg->dev_pwm_freq );

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) {
        return ADC_ERROR;
    }

    // Output pins
    digital_out_init( &ctx->shd, cfg->shd );
    digital_out_init( &ctx->pw2, cfg->pw2 );
    digital_out_high( &ctx->shd );

    return PWM_SUCCESS;
}

err_t dcmotor9_default_cfg ( dcmotor9_t *ctx ) 
{
    err_t error_flag = DCMOTOR9_OK;
    error_flag |= dcmotor9_set_duty_cycle ( ctx, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    error_flag |= dcmotor9_pwm_start( ctx );

    return error_flag;
}

err_t dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t dcmotor9_pwm_stop ( dcmotor9_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t dcmotor9_pwm_start ( dcmotor9_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void dcmotor9_enable ( dcmotor9_t *ctx )
{
   digital_out_high( &ctx->shd );
}

void dcmotor9_standby ( dcmotor9_t *ctx )
{
   digital_out_low( &ctx->shd );
}

void dcmotor9_counter_clockwise ( dcmotor9_t *ctx )
{
    digital_out_low( &ctx->pw2 );
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_100 );
}

void dcmotor9_clockwise ( dcmotor9_t *ctx )
{
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_0 );
    digital_out_high( &ctx->pw2 );
}

void dcmotor9_short_brake ( dcmotor9_t *ctx )
{
    dcmotor9_set_duty_cycle( ctx, DCMOTOR9_PWM_DUTY_PERCENT_100 );
    digital_out_high( &ctx->pw2 );
}

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
