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
 * @file brushless31.c
 * @brief Brushless 31 Click Driver.
 */

#include "brushless31.h"

void brushless31_cfg_setup ( brushless31_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->start = HAL_PIN_NC;
    cfg->brake = HAL_PIN_NC;
    cfg->hp = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS31_DEF_FREQ;
}

err_t brushless31_init ( brushless31_t *ctx, brushless31_cfg_t *cfg ) 
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
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->start, cfg->start );
    digital_out_init( &ctx->brake, cfg->brake );

    // Input pins
    digital_in_init( &ctx->hp, cfg->hp );

    return PWM_SUCCESS;
}

err_t brushless31_default_cfg ( brushless31_t *ctx ) 
{
    err_t error_flag = BRUSHLESS31_OK;
    
    error_flag |= brushless31_set_duty_cycle ( ctx, 0.0 );
    error_flag |= brushless31_pwm_start( ctx );
    brushless31_set_direction ( ctx, BRUSHLESS31_DIR_CW );
    brushless31_release_brake ( ctx );
    brushless31_start ( ctx );
    
    return error_flag;
}

err_t brushless31_set_duty_cycle ( brushless31_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless31_pwm_stop ( brushless31_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless31_pwm_start ( brushless31_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void brushless31_set_direction ( brushless31_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless31_switch_direction ( brushless31_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

void brushless31_pull_brake ( brushless31_t *ctx )
{
    digital_out_low ( &ctx->brake );
}

void brushless31_release_brake ( brushless31_t *ctx )
{
    digital_out_high ( &ctx->brake );
}

void brushless31_start ( brushless31_t *ctx )
{
    digital_out_high ( &ctx->start );
}

void brushless31_stop ( brushless31_t *ctx )
{
    digital_out_low ( &ctx->start );
}

uint8_t brushless31_get_hp_pin ( brushless31_t *ctx )
{
    return digital_in_read ( &ctx->hp );
}

// ------------------------------------------------------------------------- END
