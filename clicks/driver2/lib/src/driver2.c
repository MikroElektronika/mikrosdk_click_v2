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
 * @file driver2.c
 * @brief Driver 2 Click Driver.
 */

#include "driver2.h"

void driver2_cfg_setup ( driver2_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sd   = HAL_PIN_NC;
    cfg->fb = HAL_PIN_NC;

    cfg->dev_pwm_freq = DRIVER2_DEF_FREQ;
}

err_t driver2_init ( driver2_t *ctx, driver2_cfg_t *cfg ) {
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->sd, cfg->sd );

    // Input pins
    digital_in_init( &ctx->fb, cfg->fb );

    return PWM_SUCCESS;
}

err_t driver2_default_cfg ( driver2_t *ctx ) {
    digital_out_high( &ctx->sd );
    pwm_stop( &ctx->pwm );
    return DRIVER2_OK;
}

err_t driver2_set_duty_cycle ( driver2_t *ctx, float duty_cycle ) {
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t driver2_pwm_stop ( driver2_t *ctx ) {
    return pwm_stop( &ctx->pwm );
}

err_t driver2_pwm_start ( driver2_t *ctx ) {
    return pwm_start( &ctx->pwm );
}

void driver2_set_sd_pin ( driver2_t *ctx, uint8_t state ) {
    if ( state == DRIVER2_PIN_ENABLE ) {
        digital_out_high( &ctx->sd );
    } else {
        digital_out_low( &ctx->sd );
    }
}

void driver2_set_pwm_pin ( driver2_t *ctx, uint8_t state ) {
    if ( state == DRIVER2_PIN_ENABLE ) {
        pwm_start( &ctx->pwm );
    } else {
        pwm_stop( &ctx->pwm );
    }
}

uint8_t driver2_get_fb_pin ( driver2_t *ctx ) {
    return digital_in_read( &ctx->fb );
}

// ------------------------------------------------------------------------- END
