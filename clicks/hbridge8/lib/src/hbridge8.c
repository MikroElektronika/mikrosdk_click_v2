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
 * @file hbridge8.c
 * @brief H-Bridge 8 Click Driver.
 */

#include "hbridge8.h"

void hbridge8_cfg_setup ( hbridge8_cfg_t *cfg ) 
{
    cfg->pwm = HAL_PIN_NC;

    cfg->en = HAL_PIN_NC;
    cfg->mod   = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

	cfg->dev_pwm_freq = HBRIDGE8_DEF_FREQ;
}

err_t hbridge8_init ( hbridge8_t *ctx, hbridge8_cfg_t *cfg ) 
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->mod, cfg->mod );

    digital_in_init( &ctx->flt, cfg->flt );

    return PWM_SUCCESS;
}

err_t hbridge8_default_cfg ( hbridge8_t *ctx ) 
{
    hbridge8_enable( ctx );
    
    return HBRIDGE8_OK;
}

err_t hbridge8_set_duty_cycle ( hbridge8_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t hbridge8_pwm_stop ( hbridge8_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t hbridge8_pwm_start ( hbridge8_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

err_t hbridge8_set_mode ( hbridge8_t *ctx, uint8_t mode ) 
{
    if ( mode == HBRIDGE8_MODE_REVERSE ) {
        digital_out_low( &ctx->mod );    
    } else if ( mode == HBRIDGE8_MODE_FORWARD ) {
        digital_out_high( &ctx->mod );      
    } else {
        return HBRIDGE8_ERROR;    
    }
    
    return HBRIDGE8_OK;
}

err_t hbridge8_enable ( hbridge8_t *ctx ) 
{
    digital_out_high( &ctx->en ); 
    
    return HBRIDGE8_OK;
}

err_t hbridge8_disable ( hbridge8_t *ctx ) 
{
    digital_out_low( &ctx->en ); 
    
    return HBRIDGE8_OK;
}

uint8_t hbridge8_get_fault_indication ( hbridge8_t *ctx ) 
{   
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
