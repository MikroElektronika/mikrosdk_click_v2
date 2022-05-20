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
 * @file brushless17.c
 * @brief Brushless 17 Click Driver.
 */

#include "brushless17.h"

void brushless17_cfg_setup ( brushless17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->brk  = HAL_PIN_NC;
    cfg->dir  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->diag = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS17_DEF_FREQ;
}

err_t brushless17_init ( brushless17_t *ctx, brushless17_cfg_t *cfg ) 
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
    digital_out_init( &ctx->brk, cfg->brk );
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins
    digital_in_init( &ctx->diag, cfg->diag );

    return PWM_SUCCESS;
}

err_t brushless17_default_cfg ( brushless17_t *ctx ) 
{
    err_t error_flag = BRUSHLESS17_OK;
    
    error_flag |= brushless17_set_duty_cycle ( ctx, 0.0 );
    error_flag |= brushless17_pwm_start( ctx );

    brushless17_enable_chip ( ctx );
    brushless17_set_direction ( ctx, BRUSHLESS17_DIR_CW );
    brushless17_release_brake ( ctx );
    
    return error_flag;
}

err_t brushless17_set_duty_cycle ( brushless17_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless17_pwm_stop ( brushless17_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless17_pwm_start ( brushless17_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless17_enable_chip ( brushless17_t *ctx ) 
{
    digital_out_high ( &ctx->en );
}

void brushless17_disable_chip ( brushless17_t *ctx ) 
{
    digital_out_low ( &ctx->en );
}

void brushless17_set_direction ( brushless17_t *ctx, uint8_t dir ) 
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless17_switch_direction ( brushless17_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void brushless17_pull_brake ( brushless17_t *ctx ) 
{
    digital_out_low ( &ctx->brk );
}

void brushless17_release_brake ( brushless17_t *ctx ) 
{
    digital_out_high ( &ctx->brk );
}

uint8_t brushless17_get_diagnostic_pin ( brushless17_t *ctx )
{
    return digital_in_read ( &ctx->diag );
}

// ------------------------------------------------------------------------- END
