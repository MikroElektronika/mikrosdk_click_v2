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
 * @file dcmotor5.c
 * @brief DC Motor 5 Click Driver.
 */

#include "dcmotor5.h"

void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->snso   = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->fault   = HAL_PIN_NC;
    cfg->in2 = HAL_PIN_NC;

    cfg->dev_pwm_freq = DCMOTOR5_DEF_FREQ;
}

err_t dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( DCMOTOR5_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return DCMOTOR5_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->sleep, cfg->sleep );
    digital_out_init( &ctx->in2, cfg->in2 );

    // Input pins
    digital_in_init( &ctx->snso, cfg->snso );
    digital_in_init( &ctx->fault, cfg->fault );
    
    digital_out_low( &ctx->in2 );
    
    return DCMOTOR5_OK;
}

void dcmotor5_set_duty_cycle ( dcmotor5_t *ctx, float duty_cycle ) 
{
    pwm_set_duty( &ctx->pwm, duty_cycle );
}

void dcmotor5_pwm_stop ( dcmotor5_t *ctx ) 
{
    pwm_stop( &ctx->pwm );
}

void dcmotor5_pwm_start ( dcmotor5_t *ctx ) 
{
    pwm_start( &ctx->pwm );
}

void dcmotor5_enable ( dcmotor5_t *ctx )
{
   digital_out_high( &ctx->sleep );
}

void dcmotor5_standby ( dcmotor5_t *ctx )
{
   digital_out_low( &ctx->sleep );
}

void dcmotor5_counter_clockwise ( dcmotor5_t *ctx )
{
    digital_out_low( &ctx->in2 );
    dcmotor5_set_duty_cycle( ctx, 1.0 );
}

void dcmotor5_clockwise ( dcmotor5_t *ctx )
{
    dcmotor5_set_duty_cycle( ctx, 0.0 );
    digital_out_high( &ctx->in2 );
}

void dcmotor5_short_brake ( dcmotor5_t *ctx )
{
    dcmotor5_set_duty_cycle( ctx, 1.0 );
    digital_out_high( &ctx->in2 );
}

void dcmotor5_stop ( dcmotor5_t *ctx )
{
    dcmotor5_set_duty_cycle( ctx, 0.0 );
    digital_out_low( &ctx->in2 );
}

uint8_t dcmotor5_get_fault_conditions ( dcmotor5_t *ctx )
{
    return !( digital_in_read( &ctx->fault ) );
}

uint8_t dcmotor5_get_sense_comparator ( dcmotor5_t *ctx )
{
    return !( digital_in_read( &ctx->snso ) );
}

// ------------------------------------------------------------------------- END
