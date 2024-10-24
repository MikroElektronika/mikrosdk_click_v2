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
 * @file buzzer.c
 * @brief Buzzer Click Driver.
 */

#include "buzzer.h"

void buzzer_cfg_setup ( buzzer_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    cfg->dev_pwm_freq = BUZZER_DEF_FREQ;
}

err_t buzzer_init ( buzzer_t *ctx, buzzer_cfg_t *cfg ) 
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

    return PWM_SUCCESS;
}

err_t buzzer_set_duty_cycle ( buzzer_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t buzzer_pwm_stop ( buzzer_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t buzzer_pwm_start ( buzzer_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t buzzer_play_sound ( buzzer_t *ctx, uint16_t freq, uint8_t level, uint16_t duration ) 
{
    if ( ( freq > BUZZER_DEF_FREQ ) || ( level > BUZZER_VOLUME_MAX ) || ( level < BUZZER_VOLUME_MIN ) )
    {
        return BUZZER_ERROR;
    }
    err_t error_flag = pwm_set_freq( &ctx->pwm, freq );
    ctx->pwm_freq = freq;
    error_flag |= buzzer_pwm_start( ctx );
    error_flag |= buzzer_set_duty_cycle( ctx, ( float ) ( BUZZER_VOLUME_MAX - level + 1 ) / BUZZER_VOLUME_MAX );
    while ( duration )
    {
        Delay_1ms( );
        duration--;
    }
    error_flag |= buzzer_pwm_stop( ctx );
    return error_flag;
}

// ------------------------------------------------------------------------- END
