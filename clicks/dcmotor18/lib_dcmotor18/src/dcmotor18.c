/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file dcmotor18.c
 * @brief DC Motor 18 Click Driver.
 */

#include "dcmotor18.h"

/**
 * @brief DC Motor 18 current calculation parameters.
 * @details Specified macros for calculating current for 
 * AN pin of DC Motor 18 Click driver.
 */
#define DIVIDER 1.5
#define R_SENS  220

void dcmotor18_cfg_setup ( dcmotor18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->pw2 = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = DCMOTOR18_DEF_FREQ;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t dcmotor18_init ( dcmotor18_t *ctx, dcmotor18_cfg_t *cfg ) 
{
    //PWM
    pwm_config_t pwm_cfg;
    pwm_configure_default( &pwm_cfg );
    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;
    ctx->pwm_freq = cfg->dev_pwm_freq;
    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->pw2, cfg->pw2 );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    //ADC
    analog_in_config_t adc_cfg;
    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin = cfg->an;
    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }
    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }
    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    return PWM_SUCCESS;
}

err_t dcmotor18_default_cfg ( dcmotor18_t *ctx ) 
{
    digital_out_high( &ctx->en );
    digital_out_low( &ctx->pw2 );
    ctx->direction = 0;
    dcmotor18_set_duty_cycle ( ctx, 0.0 );
    dcmotor18_pwm_start( ctx );
    return DCMOTOR18_OK;
}

err_t dcmotor18_set_duty_cycle ( dcmotor18_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t dcmotor18_pwm_stop ( dcmotor18_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t dcmotor18_pwm_start ( dcmotor18_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t dcmotor18_read_an_pin_value ( dcmotor18_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t dcmotor18_read_an_pin_voltage ( dcmotor18_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t dcmotor18_read_an_pin_current ( dcmotor18_t *ctx, float *data_out )
{
    float temp_data = 0;
    err_t ret_val = dcmotor18_read_an_pin_voltage ( ctx, &temp_data );
    temp_data *= 1000;//convert to mV
    temp_data /= R_SENS * DIVIDER;//calculate current
    *data_out = temp_data;
    return ret_val;
}

void dcmotor18_set_direction ( dcmotor18_t *ctx, uint8_t state )
{
    if ( state && ( ctx->direction != state ) )
    {
        digital_out_high( &ctx->pw2 );
        ctx->direction = 1;
    }
    else if ( ctx->direction != state )
    {
        digital_out_low( &ctx->pw2 );
        ctx->direction = 0;
    }
}

void dcmotor18_set_enable ( dcmotor18_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t dcmotor18_get_interrupt ( dcmotor18_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t dcmotor18_set_speed_percentage ( dcmotor18_t *ctx, float speed_percentage )
{
    float duty_cycle;
    if ( ctx->direction )
    {
        duty_cycle = 1.0 - speed_percentage;
    }
    else
    {
        duty_cycle = speed_percentage;
    }
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

// ------------------------------------------------------------------------- END
