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
 * @file brushless23.c
 * @brief Brushless 23 Click Driver.
 */

#include "brushless23.h"

void brushless23_cfg_setup ( brushless23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->spd = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sby = HAL_PIN_NC;
    cfg->cmo = HAL_PIN_NC;
    cfg->dir = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BRUSHLESS23_DEVICE_ADDRESS_ID2ID1_00;
    
    cfg->dev_pwm_freq = BRUSHLESS23_DEF_FREQ;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = 3.3;
}

err_t brushless23_init ( brushless23_t *ctx, brushless23_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    pwm_config_t pwm_cfg;

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->spd;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->cmo;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->sby, cfg->sby );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t brushless23_default_cfg ( brushless23_t *ctx ) 
{
    err_t error_flag = BRUSHLESS23_OK;
    
    brushless23_set_sby_pin ( ctx, BRUSHLESS23_SBY_NORMAL_OPERATION );
    Delay_100ms ( );
    brushless23_set_direction ( ctx, BRUSHLESS23_DIR_CW );
    
    error_flag |= brushless23_pwm_stop ( ctx );
    error_flag |= brushless23_pwm_set_duty_cycle ( ctx, BRUSHLESS23_DUTY_CYCLE_MIN_PCT );
    
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_8, BRUSHLESS23_SPEED_SLOP_1_MSB );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_9, BRUSHLESS23_SPEED_SLOP_1_LSB );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_10, BRUSHLESS23_SPEED_SLOP_2_MSB );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_11, BRUSHLESS23_SPEED_SLOP_2_LSB | 
                                                                        BRUSHLESS23_OPEN_LOOP );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_15, BRUSHLESS23_TSPSEL_PWM_DUTY );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_19, BRUSHLESS23_ALERTINV_LOW );
    
    error_flag |= brushless23_set_start_duty ( ctx, BRUSHLESS23_START_DUTY_20_PCT );
    error_flag |= brushless23_set_stop_duty ( ctx, BRUSHLESS23_STOP_DUTY_18_PCT );
    error_flag |= brushless23_set_max_duty ( ctx, BRUSHLESS23_MAX_DUTY_90_PCT );
    error_flag |= brushless23_set_start_rpm ( ctx, BRUSHLESS23_START_RPM_10_PCT );
    error_flag |= brushless23_set_change_duty ( ctx, BRUSHLESS23_CHANGE_DUTY_90_PCT );
    
    error_flag |= brushless23_pwm_start ( ctx );
    
    return error_flag;
}

err_t brushless23_write_register ( brushless23_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t brushless23_read_register ( brushless23_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t brushless23_pwm_set_duty_cycle ( brushless23_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle );
}

err_t brushless23_pwm_stop ( brushless23_t *ctx )
{
    return pwm_stop( &ctx->pwm );
}

err_t brushless23_pwm_start ( brushless23_t *ctx )
{
    return pwm_start( &ctx->pwm );
}

err_t brushless23_read_an_pin_value ( brushless23_t *ctx, uint16_t *data_out )
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t brushless23_read_an_pin_voltage ( brushless23_t *ctx, float *data_out )
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

void brushless23_set_sby_pin ( brushless23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->sby, state );
}

void brushless23_set_direction ( brushless23_t *ctx, uint8_t dir )
{
    digital_out_write ( &ctx->dir, dir );
}

void brushless23_switch_direction ( brushless23_t *ctx )
{
    digital_out_toggle ( &ctx->dir );
}

uint8_t brushless23_get_int_pin ( brushless23_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t brushless23_get_motor_speed ( brushless23_t *ctx, float *motor_speed_hz )
{
    uint8_t reg_data;
    uint16_t hz_cnt;
    err_t error_flag = brushless23_read_register( ctx, BRUSHLESS23_REG_HZ_CNT_MSB, &reg_data );
    hz_cnt = reg_data;
    hz_cnt <<= 8;
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_HZ_CNT_LSB, &reg_data );
    hz_cnt |= reg_data;
    *motor_speed_hz = BRUSHLESS23_SPEED_FREQUENCY / hz_cnt;
    return error_flag;
}

err_t brushless23_set_start_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_START_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_START_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    return brushless23_write_register( ctx, BRUSHLESS23_REG_START_DUTY, ( uint8_t ) ( 512 * duty_cycle ) );
}

err_t brushless23_set_stop_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_STOP_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_STOP_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    uint8_t reg_data;
    err_t error_flag = brushless23_read_register( ctx, BRUSHLESS23_REG_STOP_DUTY, &reg_data );
    reg_data = ( reg_data & BRUSHLESS23_NO_STOP_BIT_MASK ) | ( uint8_t ) ( 256 * duty_cycle );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_STOP_DUTY, reg_data );
    return error_flag;
}

err_t brushless23_set_max_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_MAX_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_MAX_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    return brushless23_write_register( ctx, BRUSHLESS23_REG_MAX_DUTY, ( uint8_t ) ( 512 * duty_cycle - 257 ) );
}

err_t brushless23_set_change_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_CHANGE_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_CHANGE_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    return brushless23_write_register( ctx, BRUSHLESS23_REG_CHANGE_DUTY, ( uint8_t ) ( 256 * duty_cycle ) );
}

err_t brushless23_set_start_rpm ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_START_RPM_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_START_RPM_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    return brushless23_write_register( ctx, BRUSHLESS23_REG_START_RPM_MSB, ( uint8_t ) ( 512 * duty_cycle ) );
}

err_t brushless23_set_duty_cycle ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_DUTY_CYCLE_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_DUTY_CYCLE_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    uint16_t speed = ( uint16_t ) ( 1024 * duty_cycle );
    err_t error_flag = brushless23_write_register( ctx, BRUSHLESS23_REG_SPD_MSB, ( uint8_t )( speed >> 2 ) );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPD_LSB, ( uint8_t )( speed & 0x03 ) << 6 );
    return error_flag;
}

// ------------------------------------------------------------------------- END
