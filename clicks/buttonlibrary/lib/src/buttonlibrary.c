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

#include "buttonlibrary.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buttonlibrary_cfg_setup ( buttonlibrary_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin      = HAL_PIN_NC;
	cfg->dev_pwm_freq = 5000;
}

BUTTONLIBRARY_RETVAL buttonlibrary_init ( buttonlibrary_t *ctx, buttonlibrary_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BUTTONLIBRARY_OK;
}

void buttonlibrary_set_duty_cycle ( buttonlibrary_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void buttonlibrary_pwm_stop ( buttonlibrary_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void buttonlibrary_pwm_start ( buttonlibrary_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

uint8_t buttonlibrary_get_button_state ( buttonlibrary_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

