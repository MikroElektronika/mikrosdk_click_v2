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
 * @file brushless18.c
 * @brief Brushless 18 Click Driver.
 */

#include "brushless18.h"

void brushless18_cfg_setup ( brushless18_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS18_DEF_FREQ;
}

err_t brushless18_init ( brushless18_t *ctx, brushless18_cfg_t *cfg ) 
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

err_t brushless18_set_duty_cycle ( brushless18_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless18_pwm_stop ( brushless18_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless18_pwm_start ( brushless18_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t brushless18_throttle_calib ( brushless18_t *ctx )
{
    err_t error_flag = BRUSHLESS18_OK;
    error_flag |= brushless18_set_duty_cycle ( ctx, BRUSHLESS18_DC_ZERO );
    error_flag |= brushless18_pwm_start( ctx );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
    error_flag |= brushless18_set_duty_cycle ( ctx, BRUSHLESS18_DC_MIN_THROTTLE );
    Delay_1sec ( );
    Delay_1sec ( );
    error_flag |= brushless18_set_duty_cycle ( ctx, BRUSHLESS18_DC_MAX_THROTTLE );
    Delay_1sec ( );
    Delay_1sec ( );
    error_flag |= brushless18_set_duty_cycle ( ctx, BRUSHLESS18_DC_IDLE );
    Delay_1sec ( );
    Delay_1sec ( );
    return error_flag;
}

err_t brushless18_drive_motor ( brushless18_t *ctx, uint8_t direction, uint8_t speed )
{
    if ( ( direction > BRUSHLESS18_DIRECTION_CCW ) || ( speed > BRUSHLESS18_SPEED_MAX ) )
    {
        return BRUSHLESS18_ERROR;
    }
    float duty_cycle = BRUSHLESS18_DC_IDLE;
    if ( BRUSHLESS18_DIRECTION_CW == direction )
    {
        duty_cycle -= ( BRUSHLESS18_DC_1_PCT * speed );
    }
    else
    {
        duty_cycle += ( BRUSHLESS18_DC_1_PCT * speed );
    }
    return brushless18_set_duty_cycle( ctx, duty_cycle );
}

// ------------------------------------------------------------------------- END
