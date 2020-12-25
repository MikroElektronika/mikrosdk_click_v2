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

#include "irbeacon.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void irbeacon_cfg_setup ( irbeacon_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->mod = HAL_PIN_NC;

    cfg->dev_pwm_freq = IRBEACON_DEF_FREQ;
}

IRBEACON_RETVAL irbeacon_init ( irbeacon_t *ctx, irbeacon_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->mod, cfg->mod );

    return IRBEACON_OK;
}

void irbeacon_set_duty_cycle ( irbeacon_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void irbeacon_pwm_stop ( irbeacon_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void irbeacon_pwm_start ( irbeacon_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void irbeacon_enable_mod ( irbeacon_t *ctx )
{
    digital_out_high( &ctx->mod );
}

void irbeacon_disable_mod ( irbeacon_t *ctx )
{
    digital_out_low( &ctx->mod );
}

void irbeacon_reset_mod ( irbeacon_t *ctx )
{
    digital_out_low( &ctx->mod );
    Delay_100ms( );
    digital_out_high( &ctx->mod );
}

// ------------------------------------------------------------------------- END

