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

#include "dcmotor3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dcmotor3_cfg_setup ( dcmotor3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->in1 = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;

    cfg->dev_pwm_freq 	  = 5000;
}

DCMOTOR3_RETVAL dcmotor3_init ( dcmotor3_t *ctx, dcmotor3_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->in1, cfg->in1 );
    digital_out_init( &ctx->in2, cfg->in2 );
    digital_out_init( &ctx->slp, cfg->slp );

    return DCMOTOR3_OK;
}

void dcmotor3_set_duty_cycle ( dcmotor3_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void dcmotor3_pwm_stop ( dcmotor3_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void dcmotor3_pwm_start ( dcmotor3_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

// Enable the motor function 
void dcmotor3_enable ( dcmotor3_t *ctx )
{
   digital_out_high( &ctx->slp );
}

// Disable the motor function 
void dcmotor3_standby ( dcmotor3_t *ctx )
{
    digital_out_low( &ctx->slp );
}

// Set the direction of rotation in the counter clockwise direction function 
void dcmotor3_counter_clockwise ( dcmotor3_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_high( &ctx->in2 ); 
}

// Set the direction of rotation in the clockwise direction function
void dcmotor3_clockwise ( dcmotor3_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

// Brake the engine function
void dcmotor3_short_brake ( dcmotor3_t *ctx )
{
    digital_out_high( &ctx->in1 );
    digital_out_high( &ctx->in2);
}

// Stop the engine function
void dcmotor3_stop ( dcmotor3_t *ctx )
{
    digital_out_low( &ctx->in1 );
    digital_out_low( &ctx->in2 );
}

// ------------------------------------------------------------------------- END

