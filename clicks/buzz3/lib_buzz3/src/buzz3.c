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
 * @file buzz3.c
 * @brief Buzz 3 Click Driver.
 */

#include "buzz3.h"

void buzz3_cfg_setup ( buzz3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->pwm = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en1 = HAL_PIN_NC;
    cfg->en2 = HAL_PIN_NC;

	cfg->dev_pwm_freq = BUZZ3_DEF_FREQ;
}

err_t buzz3_init ( buzz3_t *ctx, buzz3_cfg_t *cfg ) 
{
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

    // Output pins
    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );

    return PWM_SUCCESS;
}

err_t buzz3_default_cfg ( buzz3_t *ctx ) {
    
    digital_out_low( &ctx->en1 );
    digital_out_low( &ctx->en2 );
    return BUZZ3_OK;
}

err_t buzz3_set_duty_cycle ( buzz3_t *ctx, float duty_cycle ) {
    
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t buzz3_pwm_stop ( buzz3_t *ctx ) {
   
    return pwm_stop( &ctx->pwm );
}

err_t buzz3_pwm_start ( buzz3_t *ctx ) {
   
    return pwm_start( &ctx->pwm );
}

err_t buzz3_set_gain_operating_mode ( buzz3_t *ctx, uint8_t op_mode ) {
    
    uint8_t status;
    
    status = BUZZ3_OK;
    
    switch ( op_mode ) {
        
        case BUZZ3_OP_MODE_GAIN_x0: {
            
            digital_out_low( &ctx->en1 );
            digital_out_low( &ctx->en2 );
            break;
        }
        case BUZZ3_OP_MODE_GAIN_x1: {            
            
            digital_out_low( &ctx->en1 );
            digital_out_high( &ctx->en2 );
            break;
        }
        case BUZZ3_OP_MODE_GAIN_x2: {
            
            digital_out_high( &ctx->en1 );
            digital_out_low( &ctx->en2 );
            break;
        }
        case BUZZ3_OP_MODE_GAIN_x3: {
            
            digital_out_high( &ctx->en1 );
            digital_out_high( &ctx->en2 );
            break;
        }
        default: {
            
            digital_out_low( &ctx->en1 );
            digital_out_high( &ctx->en2 );
            status = BUZZ3_ERROR;
            break;
        }
    }
    
    return status;
}

void buzz3_play_sound ( buzz3_t *ctx, uint16_t freq, uint16_t duration ) {
    
    pwm_set_freq( &ctx->pwm, freq );
    ctx->pwm_freq = freq;
    buzz3_set_duty_cycle( ctx, 0.09 );
    buzz3_pwm_start( ctx );
    
    while ( duration ) {
        
        Delay_1ms( );
        duration--;
    }
    
    buzz3_pwm_stop( ctx );
}

// ------------------------------------------------------------------------- END
