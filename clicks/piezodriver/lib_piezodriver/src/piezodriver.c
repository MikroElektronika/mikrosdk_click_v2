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
 * @file piezodriver.c
 * @brief Piezo Driver Click Driver.
 */

#include "piezodriver.h"

void piezodriver_cfg_setup ( piezodriver_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    cfg->dev_pwm_freq = PIEZODRIVER_DEF_FREQ;
}

err_t piezodriver_init ( piezodriver_t *ctx, piezodriver_cfg_t *cfg ) 
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

err_t piezodriver_default_cfg ( piezodriver_t *ctx ) 
{
    err_t error_flag = PIEZODRIVER_OK;
    
    error_flag |= piezodriver_set_duty_cycle ( ctx, 0.0 );
    error_flag |= piezodriver_pwm_start( ctx );

    return error_flag;
}

err_t piezodriver_set_duty_cycle ( piezodriver_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t piezodriver_pwm_stop ( piezodriver_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t piezodriver_pwm_start ( piezodriver_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

void piezodriver_play_sound ( piezodriver_t *ctx, uint16_t freq, uint8_t level, uint16_t duration ) 
{
    if ( 10 > level )
    {
        level = 10;
    }
    pwm_set_freq( &ctx->pwm, freq );
    ctx->pwm_freq = freq;
    piezodriver_pwm_start( ctx );
    piezodriver_set_duty_cycle( ctx, ( float ) ( level - 10 ) / 100.0 );
    
    while ( duration ) 
    {
        Delay_1ms( );
        duration--;
    }
    
    piezodriver_pwm_stop( ctx );
}

// ------------------------------------------------------------------------- END
