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
 * \file
 *
 */

#include "vreg2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vreg2_cfg_setup ( vreg2_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->pwm = HAL_PIN_NC;
    
    cfg->dev_pwm_freq = VREG2_DEF_FREQ;
}

err_t vreg2_init ( vreg2_t *ctx, vreg2_cfg_t *cfg )
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

    return VREG2_OK;
}

err_t vreg2_default_cfg ( vreg2_t *ctx ) 
{
    err_t error_flag = VREG2_OK;
    
    error_flag |= vreg2_set_duty_cycle ( ctx, 0.0 );
    error_flag |= vreg2_pwm_start( ctx );

    return error_flag;
}

err_t vreg2_set_duty_cycle ( vreg2_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t vreg2_pwm_stop ( vreg2_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t vreg2_pwm_start ( vreg2_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

// ------------------------------------------------------------------------- END
