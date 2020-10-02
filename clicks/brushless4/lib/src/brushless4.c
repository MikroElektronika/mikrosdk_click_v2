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

#include "brushless4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void brushless4_cfg_setup ( brushless4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->fg = HAL_PIN_NC;

    cfg->dev_pwm_freq 	  = 5000;
}

BRUSHLESS4_RETVAL brushless4_init ( brushless4_t *ctx, brushless4_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Input pins

    digital_in_init( &ctx->fg, cfg->fg );
    digital_in_init( &ctx->pwm_pin, cfg->pwm );

    return BRUSHLESS4_OK;
}

void brushless4_default_cfg ( brushless4_t *ctx )
{
    ctx->num_of_poles = 0;
    ctx->num_of_slots = 0;
}

void brushless4_set_duty_cycle ( brushless4_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void brushless4_pwm_stop ( brushless4_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void brushless4_pwm_start ( brushless4_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void brushless4_motor_parameters ( brushless4_t *ctx , uint8_t poles, uint8_t slots )
{
    ctx->num_of_poles = poles;
    ctx->num_of_slots = slots;
    ctx->slots_poles = ctx->num_of_poles * ctx->num_of_slots;
}

uint16_t brushless4_get_speed ( brushless4_t *ctx, uint16_t pulse_sample )
{
    uint16_t rotor_speed;

    rotor_speed = pulse_sample * 720;
    rotor_speed = rotor_speed / ctx->slots_poles;

    return rotor_speed;
}

void brushless4_pwm_pin ( brushless4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->pwm_pin, state );
}

uint8_t brushless4_fg_get ( brushless4_t *ctx )
{
    return  digital_in_read( &ctx->fg );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

