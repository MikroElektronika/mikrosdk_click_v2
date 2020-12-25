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

#include "dcmotor4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor4_cfg_setup ( dcmotor4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dir   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->dev_pwm_freq 	  = 5000;
}

DCMOTOR4_RETVAL dcmotor4_init ( dcmotor4_t *ctx, dcmotor4_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_low( &ctx->en );
    digital_out_low( &ctx->dir );

    // Input pins

    digital_in_init( &ctx->flt, cfg->flt );

    return DCMOTOR4_OK;

}

void dcmotor4_set_duty_cycle ( dcmotor4_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void dcmotor4_pwm_stop ( dcmotor4_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void dcmotor4_pwm_start ( dcmotor4_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void dcmotor4_run_clockwise ( dcmotor4_t *ctx )
{
    digital_out_high( &ctx->dir );
}

void dcmotor4_run_counter_clockwise ( dcmotor4_t *ctx )
{
    digital_out_low( &ctx->dir );
}

void dcmotor4_enable_motor ( dcmotor4_t *ctx )
{
    digital_out_low( &ctx->en );
}

void dcmotor4_disable_motor ( dcmotor4_t *ctx )
{
    digital_out_high( &ctx->en );
}

uint8_t dcmotor4_get_diagnostic ( dcmotor4_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END

