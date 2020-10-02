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

#include "dcmotor.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PWM_PERIOD_ERROR   0


void dcmotor_cfg_setup ( dcmotor_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg-> slp   = HAL_PIN_NC;
    cfg-> sl1 = HAL_PIN_NC;
    cfg-> sl2   = HAL_PIN_NC;
    cfg-> flt = HAL_PIN_NC;

    cfg->dev_pwm_freq 	  = 5000;
}

DCMOTOR_RETVAL dcmotor_init ( dcmotor_t *ctx, dcmotor_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

	pwm_cfg.pin      = cfg->pwm;
	pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx-> slp, cfg-> slp );
    digital_out_init( &ctx-> sl1, cfg-> sl1 );
    digital_out_init( &ctx-> sl2, cfg-> sl2 );

    // Input pins

    digital_in_init( &ctx-> flt, cfg-> flt );

    return DCMOTOR_OK;

}

void dcmotor_set_duty_cycle ( dcmotor_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void dcmotor_pwm_stop ( dcmotor_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void dcmotor_pwm_start ( dcmotor_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

void dcmotor_enable ( dcmotor_t *ctx )
{
    digital_out_high( &ctx-> slp );
}

/* Set sleep mode function */
void dcmotor_sleep_mode ( dcmotor_t *ctx )
{
    digital_out_low( &ctx-> slp );
}

/* Select left direction, fast decay function */
void dcmotor_left_direction_fast ( dcmotor_t *ctx )
{
    digital_out_low( &ctx-> sl1 );
    digital_out_low( &ctx-> sl2 );
}

/* Select right direction, fast decay function */
void dcmotor_right_direction_fast ( dcmotor_t *ctx )
{
    digital_out_low( &ctx-> sl1 );
    digital_out_high( &ctx-> sl2 );
}

/* Select left direction, slow deca function */
void dcmotor_left_direction_slow ( dcmotor_t *ctx )
{
    digital_out_high( &ctx-> sl1 );
    digital_out_high( &ctx-> sl2 );
}

/* Select right direction, slow decay function */
void dcmotor_right_direction_slow ( dcmotor_t *ctx )
{
    digital_out_high( &ctx-> sl1 );
    digital_out_low( &ctx-> sl2 );    
}

/* Get diagnostic function */
uint8_t dcmotor_get_diagnostic ( dcmotor_t *ctx )
{
    return digital_in_read( &ctx-> flt );
}
// ------------------------------------------------------------------------- END

