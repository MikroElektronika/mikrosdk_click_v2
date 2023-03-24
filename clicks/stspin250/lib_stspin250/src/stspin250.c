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

#include "stspin250.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void stspin250_cfg_setup ( stspin250_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ph   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

	cfg->dev_pwm_freq 	  = 5000;
}

STSPIN250_RETVAL stspin250_init ( stspin250_t *ctx, stspin250_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );


    // Output pins 

    digital_out_init( &ctx->ph, cfg->ph );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->flt, cfg->flt );

    digital_out_high( &ctx->rst );

    return STSPIN250_OK;

}

void stspin250_set_duty_cycle ( stspin250_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void stspin250_pwm_stop ( stspin250_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void stspin250_pwm_start ( stspin250_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void stspin250_enable ( stspin250_t *ctx, uint8_t state)
{
    digital_out_write( &ctx->en, state );
}

void stspin250_set_ph ( stspin250_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->ph, state );
}

void stspin250_reset ( stspin250_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_10ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
}

uint8_t stspin250_get_fault ( stspin250_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END

