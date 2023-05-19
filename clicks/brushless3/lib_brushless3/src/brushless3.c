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

#include "brushless3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void brushless3_cfg_setup ( brushless3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->dev_pwm_freq = BRUSHLESS3_DEF_FREQ;
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = BRUSHLESS3_I2C_ADDRESS;
}

err_t brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg )
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

    pwm_cfg.pin     = cfg->pwm;
    pwm_cfg.freq_hz = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;

    if ( PWM_ERROR == pwm_open( &ctx->pwm, &pwm_cfg ) )
    {
        return PWM_ERROR;
    }
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 
    digital_out_init( &ctx->dir, cfg->dir );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BRUSHLESS3_OK;
}

err_t brushless3_default_cfg ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    brushless3_forward_direction( ctx );
    error_flag |= brushless3_set_default_param ( ctx );
    error_flag |= brushless3_set_duty_cycle ( ctx, 0.5 );
    error_flag |= brushless3_pwm_start( ctx );
    Delay_1sec ( );
    return error_flag;
}

err_t brushless3_write_data ( brushless3_t *ctx, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    tx_buf[ 0 ] = reg_addr;
    tx_buf[ 1 ] = write_data;
    return i2c_master_write ( &ctx->i2c, tx_buf, 2 ); 
}

err_t brushless3_read_data ( brushless3_t *ctx, uint8_t reg_addr, uint8_t *read_data )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, read_data, 1 );
}

err_t brushless3_set_default_param ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, BRUSHLESS3_PARAM_START_EE_CTRL );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_1, BRUSHLESS3_PARAM_MOTOR_PARAM_1 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_2, BRUSHLESS3_PARAM_MOTOR_PARAM_2 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_3, BRUSHLESS3_PARAM_MOTOR_PARAM_3 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_1, BRUSHLESS3_PARAM_SYS_OPT_1 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_2, BRUSHLESS3_PARAM_SYS_OPT_2 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_3, BRUSHLESS3_PARAM_SYS_OPT_3 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_4, BRUSHLESS3_PARAM_SYS_OPT_4 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_5, BRUSHLESS3_PARAM_SYS_OPT_5 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_6, BRUSHLESS3_PARAM_SYS_OPT_6 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_7, BRUSHLESS3_PARAM_SYS_OPT_7 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_8, BRUSHLESS3_PARAM_SYS_OPT_8 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, BRUSHLESS3_PARAM_SYS_OPT_9 );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_DEV_CTRL, BRUSHLESS3_PARAM_DEV_CTRL );
    
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, BRUSHLESS3_PARAM_STOP_EE_CTRL );
    
    error_flag |= brushless3_set_speed( ctx, 100 );
    
    return error_flag;
}

err_t brushless3_set_pwm_mode ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_SYS_OPT_9, &tmp );
    tmp |= 0x02;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, tmp );
    return error_flag;
}

err_t brushless3_set_an_mode ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_SYS_OPT_9, &tmp );
    tmp &= 0xFD;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, tmp );
    return error_flag;
}

err_t brushless3_dis_sleep_mode ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp |= 0x80;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_en_config ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp |= 0x40;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_dis_config ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp &= 0xBF;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_copy_eeprom ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp |= 0x20;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_en_write_eeprom ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp |= 0x10;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_dis_write_eeprom ( brushless3_t *ctx )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL, &tmp );
    tmp |= 0x10;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
    return error_flag;
}

err_t brushless3_check_over_temp ( brushless3_t *ctx, uint8_t *over_temp )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_STATUS, &tmp );
    tmp >>= 7;
    tmp &= 0x01;
    *over_temp = tmp;
    return error_flag;
}

err_t brushless3_check_sleep_mode ( brushless3_t *ctx, uint8_t *sleep_mode )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_STATUS, &tmp );
    tmp >>= 6;
    tmp &= 0x01;
    *sleep_mode = tmp;
    return error_flag;
}

err_t brushless3_check_motor_lock ( brushless3_t *ctx, uint8_t *motor_lock )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_STATUS, &tmp );
    tmp >>= 4;
    tmp &= 0x01;
    *motor_lock = tmp;
    return error_flag;
}

err_t brushless3_get_supply_voltage ( brushless3_t *ctx, float *voltage )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_SUPPLY_VOLTAGE, &tmp );
    *voltage = ( float ) tmp * 30.0 / 256.0;
    return error_flag;
}

err_t brushless3_get_speed_cmd ( brushless3_t *ctx, float *speed_cmd )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_SPEED_CMD, &tmp );
    *speed_cmd = ( float ) tmp * 100.0 / 255.0;
    return error_flag;
}

err_t brushless3_check_fault_code ( brushless3_t *ctx, uint8_t *fault_code )
{
    return brushless3_read_data( ctx, BRUSHLESS3_FAULT_CODE, fault_code );
}

err_t brushless3_get_speed ( brushless3_t *ctx, float *speed )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t r_buffer[ 2 ] = { 0 };
    uint16_t tmp_speed = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_SPEED_1, &r_buffer[ 0 ] );
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_SPEED_2, &r_buffer[ 1 ] );
    tmp_speed = r_buffer[ 0 ];
    tmp_speed <<= 8;
    tmp_speed |= r_buffer[ 1 ];
    *speed = ( float ) tmp_speed / 10.0;
    return error_flag;
}

err_t brushless3_set_speed ( brushless3_t *ctx, uint16_t motor_speed_hz )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp1 = 0;
    uint8_t tmp2 = 0;
    uint16_t speed = ( motor_speed_hz / 2 ) & 0x01FF;
    tmp1 = ( uint8_t ) speed;
    tmp2 = ( uint8_t ) ( speed >> 8 );
    tmp2 &= 0x01;
    tmp2 |= 0x80;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_2, tmp2 );
    Delay_10us( );
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_1, tmp1 );
    return error_flag;
}

err_t brushless3_set_speed_pwm ( brushless3_t *ctx, uint16_t motor_speed_hz )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t tmp1 = 0;
    uint8_t tmp2 = 0;
    uint16_t speed = ( motor_speed_hz / 2 ) & 0x01FF;
    tmp1 = ( uint8_t ) speed;
    tmp2 = ( uint8_t ) ( speed >> 8 );
    tmp2 &= 0x01;
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_2, tmp2 );
    Delay_10us( );
    error_flag |= brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_1, tmp1 );
    return error_flag;
}

err_t brushless3_get_period ( brushless3_t *ctx, float *period )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t r_buffer[ 2 ] = { 0 };
    uint16_t tmp_period = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_PERIOD_1, &r_buffer[ 0 ] );
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_PERIOD_2, &r_buffer[ 1 ] );
    tmp_period = r_buffer[ 0 ];
    tmp_period <<= 8;
    tmp_period |= r_buffer[ 1 ];
    *period = ( float ) tmp_period / 10.0;
    return error_flag;;
}

err_t brushless3_en_prog_eeprom ( brushless3_t *ctx )
{
    return brushless3_write_data( ctx, BRUSHLESS3_DEV_CTRL, BRUSHLESS3_PARAM_DEV_CTRL );
}

err_t brushless3_get_vel_const ( brushless3_t *ctx, float *velocity )
{
    err_t error_flag = BRUSHLESS3_OK;
    uint8_t r_buffer[ 2 ] = { 0 };
    uint16_t vel_const = 0;
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_KT_1, &r_buffer[ 0 ] );
    error_flag |= brushless3_read_data( ctx, BRUSHLESS3_MOTOR_KT_2, &r_buffer[ 1 ] );
    vel_const = r_buffer[ 0 ];
    vel_const <<= 8;
    vel_const |= r_buffer[ 1 ];
    *velocity = ( float ) vel_const / 2.0 / 1090.0;
    return error_flag;;
}

void brushless3_forward_direction ( brushless3_t *ctx )
{
    digital_out_low( &ctx->dir ); 
}

void brushless3_reverse_direction ( brushless3_t *ctx )
{
    digital_out_high( &ctx->dir ); 
}

uint8_t brushless3_get_int_pin ( brushless3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t brushless3_set_duty_cycle ( brushless3_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

err_t brushless3_pwm_stop ( brushless3_t *ctx )
{
    return pwm_stop( &ctx->pwm ); 
}

err_t brushless3_pwm_start ( brushless3_t *ctx )
{
    return pwm_start( &ctx->pwm ); 
}

// ------------------------------------------------------------------------- END

