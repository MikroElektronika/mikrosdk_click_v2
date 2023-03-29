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
 * @file haptic2.c
 * @brief HAPTIC 2 Click Driver.
 */

#include "haptic2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define HAPTIC2_DUTY_CYCLE_ZERO    0.0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void haptic2_cfg_setup ( haptic2_cfg_t *cfg ) {

    cfg->pwm = HAL_PIN_NC;

	cfg->dev_pwm_freq = HAPTIC2_DEF_FREQ;
}

err_t haptic2_init ( haptic2_t *ctx, haptic2_cfg_t *cfg ) {
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return PWM_SUCCESS;
}

err_t haptic2_default_cfg ( haptic2_t *ctx ) {
    err_t status;
    
    status = PWM_SUCCESS;
    
    status |= haptic2_set_duty_cycle ( ctx, HAPTIC2_DUTY_CYCLE_ZERO );
    status |= haptic2_pwm_start( ctx );
    
    return status;
}

err_t haptic2_set_duty_cycle ( haptic2_t *ctx, float duty_cycle ) {
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t haptic2_pwm_stop ( haptic2_t *ctx ) {
    return pwm_stop( &ctx->pwm );
}

err_t haptic2_pwm_start ( haptic2_t *ctx ) {
    return pwm_start( &ctx->pwm );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
