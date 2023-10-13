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
 * @file brushless11.c
 * @brief Brushless 11 Click Driver.
 */

#include "brushless11.h"

void brushless11_cfg_setup ( brushless11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fg1 = HAL_PIN_NC;
    cfg->brk = HAL_PIN_NC;
    cfg->fg2 = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS11_DEF_FREQ;
}

err_t brushless11_init ( brushless11_t *ctx, brushless11_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->brk, cfg->brk );

    // Input pins
    digital_in_init( &ctx->fg1, cfg->fg1 );
    digital_in_init( &ctx->fg2, cfg->fg2 );

    return PWM_SUCCESS;
}

err_t brushless11_default_cfg ( brushless11_t *ctx ) 
{
    err_t error_flag = BRUSHLESS11_OK;
    
    brushless11_set_brake( ctx, BRUSHLESS11_BRAKE_OFF );
    
    error_flag |= brushless11_set_speed ( ctx, 0 );
    error_flag |= brushless11_pwm_start( ctx );

    return error_flag;
}

err_t brushless11_set_duty_cycle ( brushless11_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless11_pwm_stop ( brushless11_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless11_pwm_start ( brushless11_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless11_set_brk_pin ( brushless11_t *ctx, uint8_t pin_state )
{
    if ( BRUSHLESS11_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->brk );
    }
    else
    {
        digital_out_low( &ctx->brk );
    }
}

uint8_t brushless11_get_fg1_pin ( brushless11_t *ctx )
{
    return digital_in_read( &ctx->fg1);
}

uint8_t brushless11_get_fg2_pin ( brushless11_t *ctx )
{
    return digital_in_read( &ctx->fg2);
}

void brushless11_set_brake ( brushless11_t *ctx, uint8_t brake_state )
{
    if ( BRUSHLESS11_BRAKE_ON == brake_state )
    {
        brushless11_set_brk_pin( ctx, BRUSHLESS11_PIN_STATE_LOW );
    }
    else
    {
        brushless11_set_brk_pin( ctx, BRUSHLESS11_PIN_STATE_HIGH );
    }
}

err_t brushless11_set_speed ( brushless11_t *ctx, uint8_t speed )
{
    err_t error_flag = BRUSHLESS11_OK;
    float speed_val;
    
    if ( ( 100 < speed ) )
    {
        return BRUSHLESS11_ERROR;
    }
    speed_val = ( ( float ) ( 100 - speed ) / 100 );
    
    error_flag |= pwm_set_duty( &ctx->pwm, speed_val );
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
