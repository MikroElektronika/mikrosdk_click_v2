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
 * @file leddriver11.c
 * @brief LED Driver 11 Click Driver.
 */

#include "leddriver11.h"

void leddriver11_cfg_setup ( leddriver11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;

    cfg->i2c_speed    = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address  = LEDDRIVER11_SET_DEV_ADDR;
    
    cfg->resolution   = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                          Different MCU's have different resolutions. 
                                                          Change only if necessary.*/
    cfg->vref         = 3.3;
    cfg->dev_pwm_freq = LEDDRIVER11_DEF_FREQ;
}

err_t leddriver11_init ( leddriver11_t *ctx, leddriver11_cfg_t *cfg ) 
{
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) 
    {
        return ADC_ERROR;
    }
    
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR ) 
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    return I2C_MASTER_SUCCESS;
}

err_t leddriver11_default_cfg ( leddriver11_t *ctx ) 
{
    err_t error_flag = leddriver11_pwm_start( ctx );    
    error_flag |= leddriver11_set_current( ctx, LEDDRIVER11_MIN_CURRENT );
    
    return error_flag;
}

err_t leddriver11_set_current ( leddriver11_t *ctx, uint16_t curr ) 
{
    #define DAC_VOLATILE_ALL_MEM 0x60
    uint8_t tx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = DAC_VOLATILE_ALL_MEM;
    tx_buf[ 1 ] = ( uint8_t ) ( ( curr >> 4 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( curr << 4 ) & 0xFF );

    return i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

err_t leddriver11_read_dac_memory( leddriver11_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 6 );
}

err_t leddriver11_read_an_pin_value ( leddriver11_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t leddriver11_read_an_pin_voltage ( leddriver11_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t leddriver11_set_duty_cycle ( leddriver11_t *ctx, float duty_cycle ) 
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t leddriver11_pwm_stop ( leddriver11_t *ctx ) 
{
    return pwm_stop( &ctx->pwm );
}

err_t leddriver11_pwm_start ( leddriver11_t *ctx ) 
{
    return pwm_start( &ctx->pwm );
}

// ------------------------------------------------------------------------- END
