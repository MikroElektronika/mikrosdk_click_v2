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
 * @file brushless15.c
 * @brief Brushless 15 Click Driver.
 */

#include "brushless15.h"

void brushless15_cfg_setup ( brushless15_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->en  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS15_DEF_FREQ;
}

err_t brushless15_init ( brushless15_t *ctx, brushless15_cfg_t *cfg ) 
{
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
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PWM_SUCCESS;
}

err_t brushless15_default_cfg ( brushless15_t *ctx ) 
{
    err_t error_flag = BRUSHLESS15_OK;
    
    brushless15_disable_device ( ctx );
    Delay_1sec( );
    brushless15_enable_device ( ctx );
    brushless15_set_direction ( ctx, BRUSHLESS15_DIR_CW );
    error_flag |= brushless15_set_duty_cycle ( ctx, 0.5 );
    error_flag |= brushless15_pwm_start( ctx );

    return error_flag;
}

err_t brushless15_set_duty_cycle ( brushless15_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless15_pwm_stop ( brushless15_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless15_pwm_start ( brushless15_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless15_enable_device ( brushless15_t *ctx ) 
{
    digital_out_low ( &ctx->en );
}

void brushless15_disable_device ( brushless15_t *ctx ) 
{
    digital_out_high ( &ctx->en );
}

uint8_t brushless15_get_int_pin ( brushless15_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

void brushless15_set_direction ( brushless15_t *ctx, uint8_t direction ) 
{
    digital_out_write ( &ctx->dir, direction );
}

void brushless15_switch_direction ( brushless15_t *ctx ) 
{
    digital_out_toggle ( &ctx->dir );
}

// ------------------------------------------------------------------------- END
