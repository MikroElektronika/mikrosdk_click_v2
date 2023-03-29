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
 * @file brushless8.c
 * @brief Brushless 8  Click Driver.
 */

#include "brushless8.h"

void brushless8_cfg_setup ( brushless8_cfg_t *cfg )
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->an  = HAL_PIN_NC;
    cfg->res = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->fg  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BRUSHLESS8_SLAVE_ADDRESS_1;

    cfg->dev_pwm_freq = 18000;

    cfg->resolution = ANALOG_IN_RESOLUTION_12_BIT;
    cfg->vref       = 2.5;

    /* Sets PWM mode by default. */
    cfg->ctrl_mod = BRUSHLESS8_PWM;
}

BRUSHLESS8_RETVAL brushless8_init ( brushless8_t *ctx, brushless8_cfg_t *cfg )
{
    // I2C
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

    // PWM
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    if ( pwm_open( &ctx->pwm, &pwm_cfg ) == PWM_ERROR )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // ADC
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );
    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    // GPIO
    digital_out_init( &ctx->res, cfg->res );
    digital_out_init( &ctx->dir, cfg->dir );

    digital_in_init( &ctx->fg, cfg->fg );

    // Set mode
    ctx->ctrl_mod = cfg->ctrl_mod;

    return BRUSHLESS8_OK;
}

BRUSHLESS8_RETVAL brushless8_default_cfg ( brushless8_t *ctx )
{
    brushless8_set_direction( ctx, BRUSHLESS8_DIRECTION_CW );
    brushless8_set_reset( ctx, BRUSHLESS8_RESET_EN );

    if ( BRUSHLESS8_PWM == ctx->ctrl_mod ) {
        brushless8_dac_write_data( ctx, BRUSHLESS8_DAC_REG_DEVICE_CONFIG, 0 );

        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_B_FGC, BRUSHLESS8_FGC_STEP_3 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_C_LA, BRUSHLESS8_LA_STEP_0_DEG_0 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_D_LAS, BRUSHLESS8_LAS_EXT_IN_60_DEG_RST );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_E_LAL, BRUSHLESS8_LAL_STEP_0_DEG_0 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_F_LAAJ, BRUSHLESS8_LAAJ_STEP_0_PHASE_DEG_0 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 0 );
    } else if ( BRUSHLESS8_DAC == ctx->ctrl_mod ) {
        brushless8_dac_write_data( ctx, BRUSHLESS8_DAC_REG_DEVICE_CONFIG, 0 );

        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_B_FGC, BRUSHLESS8_FGC_STEP_9 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_C_LA, BRUSHLESS8_LA_STEP_0_DEG_0 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_D_LAS, BRUSHLESS8_LAS_AUTOMATIC_360_DEG_RST );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_E_LAL, BRUSHLESS8_LAL_STEP_0_DEG_0 );
        Delay_100ms( );
        brushless8_set_dac_vout( ctx, BRUSHLESS8_DAC_REG_CHN_F_LAAJ, BRUSHLESS8_LAAJ_STEP_0_PHASE_DEG_0 );
        Delay_100ms( );
    } else {
        return BRUSHLESS8_ERROR;
    }

    brushless8_set_reset( ctx, BRUSHLESS8_RESET_EN );
    Delay_100ms( );

    return BRUSHLESS8_OK;
}

void brushless8_dac_write_data ( brushless8_t *ctx, uint8_t reg, uint16_t write_data )
{
    uint8_t tx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = reg; 
    tx_buf[ 1 ] = 0x00FF & ( write_data >> 8 );
    tx_buf[ 2 ] = write_data;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );   
}

uint16_t brushless8_dac_read_data ( brushless8_t *ctx, uint8_t reg )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t temp_data;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 2 );

    temp_data = rx_buf[ 0 ];
    temp_data <<= 8;
    temp_data |= rx_buf[ 1 ];

    return temp_data;
}

uint8_t brushless8_get_fg ( brushless8_t *ctx )
{
    return digital_in_read( &ctx->fg );
}

void brushless8_set_direction ( brushless8_t *ctx, uint8_t status )
{
    if ( status > 0 )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

void brushless8_set_reset ( brushless8_t *ctx, uint8_t status )
{
    if ( status > 0 )
    {
        digital_out_high( &ctx->res );
    }
    else
    {
        digital_out_low( &ctx->res );
    }
}

int8_t brushless8_set_dac_vout ( brushless8_t *ctx, uint8_t dac_chn, uint16_t vout )
{
    volatile float temp_f;
    volatile uint16_t vout_data;
    char txt[ 50 ];

    if ( ( dac_chn > BRUSHLESS8_DAC_REG_CHN_F_LAAJ ) || ( dac_chn < BRUSHLESS8_DAC_REG_CHN_A_DVSP ) )
    {
        return BRUSHLESS8_PARAM_ERROR;
    }

    if ( vout > BRUSHLESS8_VREF )
    {
        return BRUSHLESS8_PARAM_ERROR;
    }

    temp_f = ( float )vout * BRUSHLESS8_RESOLUTION;
    temp_f /= BRUSHLESS8_VREF;

    vout_data = ( uint16_t )temp_f;
    vout_data <<= 2;

    brushless8_dac_write_data( ctx, dac_chn, vout_data );

    return BRUSHLESS8_OK;
}

void brushless8_set_duty_cycle ( brushless8_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void brushless8_pwm_stop ( brushless8_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void brushless8_pwm_start ( brushless8_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

BRUSHLESS8_RETVAL brushless8_read_adc ( brushless8_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

BRUSHLESS8_RETVAL brushless8_read_an_voltage ( brushless8_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

// ------------------------------------------------------------------------ END
