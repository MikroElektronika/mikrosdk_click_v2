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

#include "leddriver6.h"

#define LEDDRIVER6_SLAVE_ADDR  0x4D

#define LEDDRIVER6_ADC_RES   4096
#define LEDDRIVER6_ADC_VREF  3.3

void leddriver6_cfg_setup ( leddriver6_cfg_t *cfg )
{
    cfg->pwm     = HAL_PIN_NC;
    cfg->scl     = HAL_PIN_NC;
    cfg->sda     = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = LEDDRIVER6_DEF_FREQ;
    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address  = LEDDRIVER6_SLAVE_ADDR;
}

err_t leddriver6_init ( leddriver6_t *ctx, leddriver6_cfg_t *cfg )
{
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin = cfg->pwm;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    if ( pwm_set_freq( &ctx->pwm, cfg->dev_pwm_freq ) == PWM_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, cfg->i2c_address ) == I2C_MASTER_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    if ( digital_in_init( &ctx->int_pin, cfg->int_pin ) == DIGITAL_IN_UNSUPPORTED_PIN )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    return LEDDRIVER6_OK;
}

err_t leddriver6_set_duty_cycle ( leddriver6_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t leddriver6_pwm_stop ( leddriver6_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t leddriver6_pwm_start ( leddriver6_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

err_t leddriver6_read_adc ( leddriver6_t *ctx, uint16_t *data_out )
{
    uint8_t read_data[ 2 ];

    if ( i2c_master_read( &ctx->i2c, read_data, 2 ) == I2C_MASTER_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    *data_out = read_data[ 0 ];
    *data_out <<= 8;
    *data_out |= read_data[ 1 ];

    return LEDDRIVER6_OK;
}

err_t leddriver6_get_pg_voltage ( leddriver6_t *ctx, float *data_out )
{
    uint16_t adc_data;

    if ( leddriver6_read_adc( ctx, &adc_data ) == LEDDRIVER6_INIT_ERROR )
    {
        return LEDDRIVER6_INIT_ERROR;
    }

    *data_out = (float)adc_data / LEDDRIVER6_ADC_RES * LEDDRIVER6_ADC_VREF;

    return LEDDRIVER6_OK;
}

uint8_t leddriver6_get_interrupt_state ( leddriver6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------ END
