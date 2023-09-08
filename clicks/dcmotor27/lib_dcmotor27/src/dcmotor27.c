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
 * @file dcmotor27.c
 * @brief DC Motor 27 Click Driver.
 */

#include "dcmotor27.h"

void dcmotor27_cfg_setup ( dcmotor27_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ip  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->dev_pwm_freq = DCMOTOR27_DEF_FREQ;
}

err_t dcmotor27_init ( dcmotor27_t *ctx, dcmotor27_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins
    digital_in_init( &ctx->ip, cfg->ip );
    digital_in_init( &ctx->flt, cfg->flt );

    return PWM_SUCCESS;
}

err_t dcmotor27_default_cfg ( dcmotor27_t *ctx ) 
{
    err_t error_flag = DCMOTOR27_OK;

    dcmotor27_set_rst_pin( ctx, DCMOTOR27_SET_PIN_LOW );
    Delay_10us();
    dcmotor27_set_rst_pin( ctx, DCMOTOR27_SET_PIN_HIGH );
    while( DCMOTOR27_SET_PIN_LOW == dcmotor27_get_flt_pin( ctx ) ) 
    {
        Delay_1us();
    }
    Delay_100ms();
    
    dcmotor27_set_rst_pin( ctx, DCMOTOR27_SET_PIN_LOW );
    Delay_10us();
    dcmotor27_set_rst_pin( ctx, DCMOTOR27_SET_PIN_HIGH );
    while( DCMOTOR27_SET_PIN_LOW == dcmotor27_get_flt_pin( ctx ) ) 
    {
        Delay_1us();
    }

    error_flag |= dcmotor27_set_duty_cycle ( ctx, 0.0 );
    error_flag |= dcmotor27_pwm_start( ctx );
    
    dcmotor27_set_rst_pin( ctx, DCMOTOR27_SET_PIN_HIGH );
    dcmotor27_set_cs_pin( ctx, DCMOTOR27_SET_PIN_LOW );

    return error_flag;
}

err_t dcmotor27_set_duty_cycle ( dcmotor27_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t dcmotor27_pwm_stop ( dcmotor27_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t dcmotor27_pwm_start ( dcmotor27_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

uint8_t dcmotor27_get_flt_pin ( dcmotor27_t *ctx )
{
    return digital_in_read( &ctx->flt );
}

uint8_t dcmotor27_get_ip_pin ( dcmotor27_t *ctx )
{
    return digital_in_read( &ctx->ip );
}

void dcmotor27_set_rst_pin ( dcmotor27_t *ctx, uint8_t pin_state )
{
    if ( DCMOTOR27_SET_PIN_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void dcmotor27_set_cs_pin ( dcmotor27_t *ctx, uint8_t pin_state )
{
    if ( DCMOTOR27_SET_PIN_HIGH == pin_state )
    {
        digital_out_high( &ctx->cs );
    }
    else
    {
        digital_out_low( &ctx->cs );
    }
}

void dcmotor27_set_coast ( dcmotor27_t *ctx, uint8_t coast_state )
{
    if ( DCMOTOR27_SET_COAST_ON == coast_state )
    {
        dcmotor27_set_cs_pin( ctx, DCMOTOR27_SET_PIN_HIGH );
    }
    else
    {
        dcmotor27_set_cs_pin( ctx, DCMOTOR27_SET_PIN_LOW );
    }
}


// ------------------------------------------------------------------------- END
