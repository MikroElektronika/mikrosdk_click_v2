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
    
    // Set all registers, based on the motor configuration information
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_KIX_KI, BRUSHLESS23_KIX_KI );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_KPX_KP, BRUSHLESS23_KPX_KP );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_14, 
                                               ( ( ( BRUSHLESS23_MOTOR_POLE_PAIRS - 1 ) << 3 ) | 
                                                 BRUSHLESS23_MOTOR_MAX_SPEED ) );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_15, BRUSHLESS23_TSPSEL_PWM_DUTY );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_16, 
                                               ( BRUSHLESS23_MOTOR_DUTY_CHG_LIM | BRUSHLESS23_MOTOR_START_CURR ) );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_17, 
                                               ( BRUSHLESS23_MOTOR_SS_ADD_SEL | 
                                                 BRUSHLESS23_MOTOR_SS_UP_SEL | 
                                                 BRUSHLESS23_MOTOR_SS_DUTY_CHG_LIM | 
                                                 BRUSHLESS23_MOTOR_DUTY_UP_TIME ) );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_18, BRUSHLESS23_CLEAR_REG );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_19, BRUSHLESS23_ALERT_INV_LOW );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_TRE_PRETIP_TIP, BRUSHLESS23_2ND_DC_EXC_0_4 );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_LA_FMAX_FST, BRUSHLESS23_CLEAR_REG );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_FPWM_DEADTIME, BRUSHLESS23_DEAD_TIME_500 );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_ISD_OCP_SRC_SINK, BRUSHLESS23_SOURCE_CURR_51 | 
                                                                                      BRUSHLESS23_SINK_CURR_74 );
    error_flag |= brushless23_write_register ( ctx, BRUSHLESS23_REG_COMP_HYS, BRUSHLESS23_CLEAR_REG );

    error_flag |= brushless23_set_motor_operation ( ctx, BRUSHLESS23_MOTOR_OPERATION );
    error_flag |= brushless23_set_start_duty ( ctx, BRUSHLESS23_MOTOR_START_DUTY );
    error_flag |= brushless23_set_stop_duty ( ctx, BRUSHLESS23_MOTOR_STOP_DUTY );
    error_flag |= brushless23_set_change_duty ( ctx, BRUSHLESS23_MOTOR_CHANGE_DUTY );
    error_flag |= brushless23_set_max_duty ( ctx, BRUSHLESS23_MOTOR_MAX_DUTY );
    if ( BRUSHLESS23_OPEN_LOOP_CONTROL == ctx->motor.loop_control ) 
    {
        error_flag |= brushless23_set_min_out_duty ( ctx, BRUSHLESS23_MOTOR_MIN_OUT_DUTY );
        error_flag |= brushless23_set_max_out_duty ( ctx, BRUSHLESS23_MOTOR_MAX_OUT_DUTY );
        error_flag |= brushless23_set_change_out_duty ( ctx, BRUSHLESS23_MOTOR_CHANGE_OUT_DUTY );
    } 
    else 
    {
        error_flag |= brushless23_set_pole_pairs ( ctx, BRUSHLESS23_MOTOR_POLE_PAIRS );        
        error_flag |= brushless23_set_start_rpm ( ctx, BRUSHLESS23_MOTOR_START_RPM );
        error_flag |= brushless23_set_max_rpm ( ctx, BRUSHLESS23_MOTOR_MAX_RPM );
        error_flag |= brushless23_set_change_rpm ( ctx, BRUSHLESS23_MOTOR_CHANGE_RPM );
    }
    error_flag |= brushless23_set_speed_slope ( ctx, &ctx->motor );
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
    *motor_speed_hz = ( 0xFFFF == hz_cnt ) ? 0.0f : ( BRUSHLESS23_SPEED_FREQUENCY / hz_cnt );
    return error_flag;
}

err_t brushless23_set_start_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_START_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_START_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.start_duty = duty_cycle;
    return brushless23_write_register( ctx, BRUSHLESS23_REG_START_DUTY, ( uint8_t ) ( 512 * duty_cycle ) );
}

err_t brushless23_set_stop_duty ( brushless23_t *ctx, float duty_cycle )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    if ( ( BRUSHLESS23_STOP_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_STOP_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.stop_duty = duty_cycle;
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_STOP_DUTY, &reg_data );
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
    ctx->motor.max_duty = duty_cycle;
    return brushless23_write_register( ctx, BRUSHLESS23_REG_MAX_DUTY, ( uint8_t ) ( 512 * duty_cycle - 257 ) );
}

err_t brushless23_set_change_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_CHANGE_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_CHANGE_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.change_duty = duty_cycle;
    return brushless23_write_register( ctx, BRUSHLESS23_REG_CHANGE_DUTY, ( uint8_t ) ( 256 * duty_cycle ) );
}

err_t brushless23_set_start_rpm ( brushless23_t *ctx, uint16_t start_rpm )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    if ( ( BRUSHLESS23_START_RPM_MIN > start_rpm ) || ( BRUSHLESS23_START_RPM_MAX < start_rpm ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.start_rpm = start_rpm;
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_START_RPM_MSB, ( uint8_t ) ( start_rpm >> 4 ) );
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_START_RPM_LSB, &reg_data );
    reg_data = ( reg_data & 0x0F ) | ( uint8_t ) ( ( start_rpm & 0x0F ) << 4 );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_START_RPM_LSB, reg_data );
    return error_flag ;
}

err_t brushless23_set_max_rpm ( brushless23_t *ctx, uint16_t max_rpm )
{
    if ( ( BRUSHLESS23_MAX_RPM_MIN > max_rpm ) || ( BRUSHLESS23_MAX_RPM_MAX < max_rpm ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.max_rpm = max_rpm;
    return BRUSHLESS23_OK;
}

err_t brushless23_set_change_rpm ( brushless23_t *ctx, uint16_t change_rpm )
{
    if ( ( ctx->motor.start_rpm > change_rpm ) || ( ctx->motor.max_rpm < change_rpm ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.change_rpm = change_rpm;
    return BRUSHLESS23_OK;
}

err_t brushless23_set_min_out_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_MIN_OUT_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_MIN_OUT_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.min_out = duty_cycle;
    return brushless23_write_register( ctx, BRUSHLESS23_REG_START_RPM_MSB, ( uint8_t ) ( 512 * duty_cycle ) );
}

err_t brushless23_set_max_out_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( BRUSHLESS23_MAX_OUT_DUTY_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_MAX_OUT_DUTY_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.max_out = duty_cycle;
    return BRUSHLESS23_OK;
}

err_t brushless23_set_change_out_duty ( brushless23_t *ctx, float duty_cycle )
{
    if ( ( ctx->motor.min_out > duty_cycle ) || ( ctx->motor.max_out < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    ctx->motor.change_out = duty_cycle;
    return BRUSHLESS23_OK;
}

err_t brushless23_set_duty_cycle ( brushless23_t *ctx, float duty_cycle )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    if ( ( BRUSHLESS23_DUTY_CYCLE_MIN_PCT > duty_cycle ) || ( BRUSHLESS23_DUTY_CYCLE_MAX_PCT < duty_cycle ) )
    {
        return BRUSHLESS23_ERROR;
    }
    uint16_t speed = ( uint16_t ) ( 512 * duty_cycle );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPD_MSB, ( uint8_t ) ( speed >> 2 ) );
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_SPD_LSB, &reg_data );
    reg_data = ( reg_data & 0x03 ) | ( uint8_t ) ( ( speed & 0x03 ) << 6 );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPD_LSB, reg_data );
    return error_flag;
}

err_t brushless23_set_pole_pairs ( brushless23_t *ctx, uint8_t pole_pairs )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    if ( ( BRUSHLESS23_POLE_PAIRS_1 >= pole_pairs ) || ( BRUSHLESS23_POLE_PAIRS_8 <= pole_pairs ) )
    {
        return BRUSHLESS23_ERROR;
    }
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_14, &reg_data );
    reg_data = ( reg_data & BRUSHLESS23_POLE_PAIRS_MSK ) | ( uint8_t ) ( ( pole_pairs - 1 ) << 3 );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_14, reg_data );
    ctx->motor.pole_pairs = pole_pairs;
    return error_flag;
}

err_t brushless23_set_speed_slope ( brushless23_t *ctx, brushless23_motor_t *motor )
{
    uint16_t speed_slope;
    uint16_t speed_slope2;
    err_t error_flag = BRUSHLESS23_OK;
    if ( BRUSHLESS23_OPEN_LOOP_CONTROL == motor->loop_control )
    {
        if ( 0.0 == motor->change_duty )
        {
            speed_slope = 1024 * ( motor->max_out - motor->min_out ) / ( motor->max_duty - motor->start_duty );
            speed_slope2 = 0;
        } 
        else 
        {
            speed_slope = 1024 * ( motor->change_out - motor->min_out ) / ( motor->change_duty - motor->start_duty );
            speed_slope2 = 1024 * ( motor->max_out - motor->change_out ) / ( motor->max_duty - motor->change_duty );
        }
    } 
    else 
    {
        if ( 0.0 == motor->change_duty )
        {
            speed_slope = ( motor->max_rpm - motor->start_rpm ) / ( ( motor->max_duty - motor->start_duty ) * 8 );
            speed_slope2 = 0;
        } 
        else 
        {
            speed_slope = ( motor->change_rpm - motor->start_rpm ) / ( ( motor->change_duty - motor->start_duty ) * 8 );
            speed_slope2 = ( motor->max_rpm - motor->change_rpm ) / ( ( motor->max_duty - motor->change_duty ) * 8 );
        }
    }
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE_MSB, ( uint8_t )( speed_slope >> 6 ) );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE_LSB, ( uint8_t )( speed_slope & 0x3F ) << 2 );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE2_MSB, ( uint8_t )( speed_slope2 >> 6 ) );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE2_LSB, ( uint8_t )( speed_slope2 & 0x3F ) << 2 );
    motor->speed_slope = speed_slope;
    motor->speed_slope2 = speed_slope2;
    return error_flag;
}

err_t brushless23_set_motor_operation ( brushless23_t *ctx, uint8_t m_operation )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    switch ( m_operation )
    {
        case BRUSHLESS23_CLOSED_LOOP_CONTROL:
        {
            ctx->motor.loop_control = BRUSHLESS23_CLOSED_LOOP_CONTROL;
            break;
        }
        case BRUSHLESS23_OPEN_LOOP_CONTROL:
        {
            ctx->motor.loop_control = BRUSHLESS23_OPEN_LOOP_CONTROL;
            break;
        }
        default:
        {
            return BRUSHLESS23_ERROR;
        }
    }
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE2_LSB, &reg_data );
    reg_data = ( reg_data & 0xFE ) | ( uint8_t ) ( ctx->motor.loop_control );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_SPEED_SLOPE2_LSB, reg_data );
    return error_flag;
}

err_t brushless23_set_user_id ( brushless23_t *ctx, uint8_t user_id )
{
    return brushless23_write_register( ctx, BRUSHLESS23_REG_USER_ID, user_id ) ;
}

err_t brushless23_get_user_id ( brushless23_t *ctx, uint8_t *user_id )
{
    return brushless23_read_register( ctx, BRUSHLESS23_REG_USER_ID, user_id ) ;
}

err_t brushless23_get_status_reg ( brushless23_t *ctx, uint8_t *status )
{
    return brushless23_read_register( ctx, BRUSHLESS23_REG_STATUS, status ) ;
}

err_t brushless23_set_i2c_addr_reg ( brushless23_t *ctx, uint8_t i2c_addr )
{
    if ( ( i2c_addr > BRUSHLESS23_DEVICE_ADDRESS_MAX ) || ( i2c_addr < BRUSHLESS23_DEVICE_ADDRESS_MIN ) )
    {
        return BRUSHLESS23_ERROR ;
    }
    return brushless23_write_register( ctx, BRUSHLESS23_REG_SLAVE_ADRS, ( i2c_addr << 1 ) ) ;
}

err_t brushless23_get_i2c_addr_reg ( brushless23_t *ctx, uint8_t *i2c_addr )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    error_flag = brushless23_read_register( ctx, BRUSHLESS23_REG_SLAVE_ADRS, &reg_data );
    *i2c_addr = ( reg_data >> 1 );
    return error_flag ;
}

err_t brushless23_read_config_regs ( brushless23_t *ctx, uint8_t *data_out )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    for ( uint8_t cnt = BRUSHLESS23_REG_STATUS; cnt <= BRUSHLESS23_REG_SPD_LSB; cnt++ )
    {
        error_flag |= brushless23_read_register( ctx, cnt, &reg_data );
        data_out[ cnt ] = reg_data;
    }
    return error_flag ;
}

err_t brushless23_read_nvm_to_regs ( brushless23_t *ctx, uint8_t *data_out )
{
#define READ_TIMEOUT 10
    uint8_t reg_data = BRUSHLESS23_NVM_ST_START;
    uint16_t timeout;
    err_t error_flag = BRUSHLESS23_OK;
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_NVM_W_R, BRUSHLESS23_NVM_WR_READ );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_NVM_ST, BRUSHLESS23_NVM_ST_START );
    for ( timeout = READ_TIMEOUT; reg_data && timeout; timeout-- )
    {
        error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_NVM_ST, &reg_data );
        Delay_1ms( );
    }
    if ( 0 == timeout )
    {
        return BRUSHLESS23_ERROR;
    } 
    for ( uint8_t cnt = BRUSHLESS23_REG_STATUS; cnt <= BRUSHLESS23_REG_SPD_LSB; cnt++ )
    {
        error_flag |= brushless23_read_register( ctx, cnt, &reg_data );
        data_out[ cnt ] = reg_data;
    }
    return error_flag;
}

err_t brushless23_write_regs_to_nvm ( brushless23_t *ctx )
{
#define WRITE_TIMEOUT 1000
    uint8_t reg_data = BRUSHLESS23_NVM_ST_START;
    uint16_t timeout;
    err_t error_flag = BRUSHLESS23_OK;
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_NVM_W_R, BRUSHLESS23_NVM_WR_WRITE );
    error_flag |= brushless23_write_register( ctx, BRUSHLESS23_REG_NVM_ST, BRUSHLESS23_NVM_ST_START );
    for ( timeout = WRITE_TIMEOUT; reg_data && timeout; timeout-- )
    {
        error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_NVM_ST, &reg_data );
        Delay_1ms( );
    }
    if ( 0 == timeout )
    {
        return BRUSHLESS23_ERROR;
    }
    return error_flag ;
}

uint8_t brushless23_device_is_ready ( brushless23_t *ctx )
{
    uint8_t reg_data;
    err_t error_flag = BRUSHLESS23_OK;
    brushless23_set_sby_pin ( ctx, BRUSHLESS23_SBY_NORMAL_OPERATION );
    Delay_100ms ( );
    error_flag |= brushless23_read_register( ctx, BRUSHLESS23_REG_SLAVE_ADRS, &reg_data ) ;
    if ( ( reg_data > BRUSHLESS23_DEVICE_ADDRESS_MAX ) || ( reg_data < BRUSHLESS23_DEVICE_ADDRESS_MIN ) )
    {
        error_flag |= BRUSHLESS23_ERROR;
    }
    brushless23_set_sby_pin ( ctx, BRUSHLESS23_SBY_STANDBY );
    Delay_100ms ( );
    return ( error_flag == BRUSHLESS23_OK );
}

err_t brushless23_set_motor_config ( brushless23_t *ctx, brushless23_motor_t *motor )
{
    err_t error_flag = BRUSHLESS23_OK;
    error_flag |= brushless23_set_motor_operation ( ctx, motor->loop_control );
    error_flag |= brushless23_set_start_duty ( ctx, motor->start_duty );
    error_flag |= brushless23_set_stop_duty ( ctx, motor->stop_duty );
    error_flag |= brushless23_set_change_duty( ctx, motor->change_duty );
    error_flag |= brushless23_set_max_duty ( ctx, motor->max_duty );
    if ( BRUSHLESS23_OPEN_LOOP_CONTROL == motor->loop_control ) 
    {
        error_flag |= brushless23_set_min_out_duty ( ctx, motor->min_out );
        error_flag |= brushless23_set_max_out_duty ( ctx, motor->max_out );
        error_flag |= brushless23_set_change_out_duty ( ctx, motor->change_out );
    } 
    else 
    {
        error_flag |= brushless23_set_start_rpm ( ctx, motor->start_rpm );
        error_flag |= brushless23_set_max_rpm ( ctx, motor->max_rpm );
        error_flag |= brushless23_set_change_rpm ( ctx, motor->change_rpm );
    }
    error_flag |= brushless23_set_speed_slope( ctx, motor );
    return error_flag;
}

// ------------------------------------------------------------------------- END
