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

BRUSHLESS3_RETVAL brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    pwm_config_t pwm_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return BRUSHLESS3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->pwm;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );

    // Output pins 

    digital_out_init( &ctx->dir, cfg->dir );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return BRUSHLESS3_OK;
}

void brushless3_default_cfg ( brushless3_t *ctx )
{
    digital_out_low( &ctx->dir ); 
}

void brushless3_write_data ( brushless3_t *ctx, uint8_t reg_addr, uint8_t write_data )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg_addr;
    tx_buf[ 1 ] = write_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
}

uint8_t brushless3_read_data ( brushless3_t *ctx, uint8_t reg_addr )
{
    uint8_t rx_buf[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, rx_buf, 1 );

    return rx_buf[ 0 ];
}

void brushless3_set_default_param ( brushless3_t *ctx )
{
    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, BRUSHLESS3_PARAM_START_EE_CTRL );
    
    brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_1, BRUSHLESS3_PARAM_MOTOR_PARAM_1 );
    
    brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_2, BRUSHLESS3_PARAM_MOTOR_PARAM_2 );
    
    brushless3_write_data( ctx, BRUSHLESS3_MOTOR_PARAM_3, BRUSHLESS3_PARAM_MOTOR_PARAM_3 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_1, BRUSHLESS3_PARAM_SYS_OPT_1 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_2, BRUSHLESS3_PARAM_SYS_OPT_2 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_3, BRUSHLESS3_PARAM_SYS_OPT_3 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_4, BRUSHLESS3_PARAM_SYS_OPT_4 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_5, BRUSHLESS3_PARAM_SYS_OPT_5 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_6, BRUSHLESS3_PARAM_SYS_OPT_6 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_7, BRUSHLESS3_PARAM_SYS_OPT_7 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_8, BRUSHLESS3_PARAM_SYS_OPT_8 );
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, BRUSHLESS3_PARAM_SYS_OPT_9 );
    
    brushless3_write_data( ctx, BRUSHLESS3_DEV_CTRL, BRUSHLESS3_PARAM_DEV_CTRL );
    
    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, BRUSHLESS3_PARAM_STOP_EE_CTRL );
    
    brushless3_set_speed( ctx, 100 );
}

void brushless3_set_pwm_mode ( brushless3_t *ctx )
{
    uint8_t tmp;
    
    tmp = brushless3_read_data( ctx, BRUSHLESS3_SYS_OPT_9 );
    
    tmp |= 0x02;
    
    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, tmp );
}

void brushless3_set_an_mode ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_SYS_OPT_9 );

    tmp &= 0xFD;

    brushless3_write_data( ctx, BRUSHLESS3_SYS_OPT_9, tmp );
}

void brushless3_disable_sleep_mode ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp |= 0x80;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

void brushless3_enable_config ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp |= 0x40;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

void brushless3_disable_config ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp &= 0xBF;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

void brushless3_copy_eeprom ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp |= 0x20;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

void brushless3_enable_write_eeprom ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp |= 0x10;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

void brushless3_disable_write_eeprom ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_EE_CTRL );

    tmp |= 0x10;

    brushless3_write_data( ctx, BRUSHLESS3_EE_CTRL, tmp );
}

uint8_t brushless3_check_over_temp ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_STATUS );

    tmp >>= 7;
    tmp &= 0x01;

    return tmp;
}

uint8_t brushless3_check_sleep_mode ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_STATUS );

    tmp >>= 6;
    tmp &= 0x01;

    return tmp;
}

uint8_t brushless3_check_motor_lock ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_STATUS );

    tmp >>= 4;
    tmp &= 0x01;

    return tmp;
}

float brushless3_get_supply_voltage_value ( brushless3_t *ctx )
{
    uint8_t tmp;
    float result;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_SUPPLY_VOLTAGE );

    result = ( float ) tmp;
    result *= 30.0;
    result /= 256.0;

    return result;
}

float brushless3_get_speed_cmd ( brushless3_t *ctx )
{
    uint8_t tmp;
    float result;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_SPEED_CMD );

    result = ( float ) tmp;
    result /= 255.0;
    result *= 100.0;

    return result;
}

uint8_t brushless3_check_fault_code ( brushless3_t *ctx )
{
    uint8_t tmp;

    tmp = brushless3_read_data( ctx, BRUSHLESS3_FAULT_CODE );

    return tmp;
}

float brushless3_get_speed ( brushless3_t *ctx )
{
    uint8_t r_buffer[ 2 ];
    uint16_t speed;
    float result;
    speed = 0;

    r_buffer[ 0 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_SPEED_1 );
    r_buffer[ 1 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_SPEED_2 );
    
    speed = r_buffer[ 0 ];
    speed <<= 8;
    speed |= r_buffer[ 1 ];
    
    result = ( float ) speed;
    result /= 10.0;

    return result;
}

void brushless3_set_speed ( brushless3_t *ctx, uint16_t motor_speed_hz )
{
    uint8_t tmp1;
    uint8_t tmp2;
    uint16_t speed;
    
    speed = motor_speed_hz / 2;
    speed &= 0x01FF;
    
    tmp1 = ( uint8_t ) speed;
    tmp2 = ( uint8_t ) ( speed >> 8 );
    tmp2 &= 0x01;
    tmp2 |= 0x80;

    brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_2, tmp2 );
    Delay_10us( );
    brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_1, tmp1 );
}

void brushless3_set_speedPWM ( brushless3_t *ctx, uint16_t motor_speed_hz )
{
    uint8_t tmp1;
    uint8_t tmp2;
    uint16_t speed;
    
    speed = motor_speed_hz / 2;
    speed &= 0x01FF;
    
    tmp1 = ( uint8_t ) speed;
    tmp2 = ( uint8_t ) ( speed >> 8 );
    tmp2 &= 0x01;

    brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_2, tmp2 );
    Delay_10us( );
    brushless3_write_data( ctx, BRUSHLESS3_SPEED_CTRL_1, tmp1 );
}

float brushless3_get_period ( brushless3_t *ctx )
{
    uint8_t r_buffer[ 2 ];
    uint16_t period;
    float result;
    period = 0;

    r_buffer[ 0 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_PERIOD_1 );
    r_buffer[ 1 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_PERIOD_2 );

    period = r_buffer[ 0 ];
    period <<= 8;
    period |= r_buffer[ 1 ];

    result = ( float ) period;
    result /= 10.0;

    return result;
}

void brushless3_enable_programming_eeprom ( brushless3_t *ctx )
{
    brushless3_write_data( ctx, BRUSHLESS3_DEV_CTRL, BRUSHLESS3_PARAM_DEV_CTRL );
}

float brushless3_get_velocity_constant ( brushless3_t *ctx )
{
    uint8_t r_buffer[ 2 ];
    uint16_t vel_const;
    float result;
    vel_const = 0;

    r_buffer[ 0 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_KT_1 );
    r_buffer[ 1 ] = brushless3_read_data( ctx, BRUSHLESS3_MOTOR_KT_2 );
    vel_const = r_buffer[ 0 ];
    vel_const <<= 8;
    vel_const |= r_buffer[ 1 ];

    result = ( float ) vel_const;
    result /= 2.0;
    result /= 1090.0;

    return result;
}

void brushless3_forward_direction ( brushless3_t *ctx )
{
    digital_out_low( &ctx->dir ); 
}

void brushless3_reverse_direction ( brushless3_t *ctx )
{
    digital_out_high( &ctx->dir ); 
}

uint8_t brushless3_get_interrupt_status ( brushless3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void brushless3_set_duty_cycle ( brushless3_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

void brushless3_pwm_stop ( brushless3_t *ctx )
{
    pwm_stop( &ctx->pwm ); 
}

void brushless3_pwm_start ( brushless3_t *ctx )
{
    pwm_start( &ctx->pwm ); 
}

// ------------------------------------------------------------------------- END

