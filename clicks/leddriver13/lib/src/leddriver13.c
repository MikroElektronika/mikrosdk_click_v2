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
 * @file leddriver13.c
 * @brief LED Driver 13 Click Driver.
 */

#include "leddriver13.h"

/**
 * @brief LED Driver 13 configuration delay function.
 * @details This function executes a measurement delay of the 100 milliseconds
 * the A80604 High Power LED Driver with Pre-Emptive Boost
 * for Ultra-High Dimming Ratio and Low Output Ripple
 * on the LED Driver 13 board™.
 * @return Nothing.
 *
 * @note None.
 */
static void dev_cfg_delay ( void );

void leddriver13_cfg_setup ( leddriver13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->dev_pwm_freq = LEDDRIVER13_DEF_FREQ;
}

err_t leddriver13_init ( leddriver13_t *ctx, leddriver13_cfg_t *cfg ) 
{
    // Output pins
    digital_out_init( &ctx->en, cfg->en );
    
    // Input pins
    digital_in_init( &ctx->flt, cfg->flt );
    
    digital_out_low( &ctx->en );
    dev_cfg_delay( );
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return PWM_SUCCESS;
}

err_t leddriver13_default_cfg ( leddriver13_t *ctx ) 
{
    err_t error_flag = LEDDRIVER13_OK;
    
    digital_out_low( &ctx->en );
    dev_cfg_delay( );
    
    error_flag |= leddriver13_set_duty_cycle ( ctx, 0.0 );
    error_flag |= leddriver13_pwm_start( ctx );
    dev_cfg_delay( );
    
    digital_out_high( &ctx->en );
    dev_cfg_delay( );
    
    return error_flag;
}

err_t leddriver13_set_duty_cycle ( leddriver13_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t leddriver13_pwm_stop ( leddriver13_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t leddriver13_pwm_start ( leddriver13_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t leddriver13_set_enable ( leddriver13_t *ctx ) 
{
    digital_out_high( &ctx->en );

    return LEDDRIVER13_OK;
}

err_t leddriver13_set_disable ( leddriver13_t *ctx ) 
{
    digital_out_low( &ctx->en );
    
    return LEDDRIVER13_OK;
}

uint8_t leddriver13_get_fault ( leddriver13_t *ctx ) 
{   
    return digital_in_read( &ctx->flt );
}

static void dev_cfg_delay ( void ) 
{   
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
