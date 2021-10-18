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
 * @file stepper17.c
 * @brief Stepper 17 Click Driver.
 */

#include "stepper17.h"


void stepper17_cfg_setup ( stepper17_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;
    cfg->dir   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->clk = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = STEPPER17_SET_DEV_ADDR;

    cfg->dev_pwm_freq   = STEPPER17_DEF_FREQ;
}

err_t stepper17_init ( stepper17_t *ctx, stepper17_cfg_t *cfg ) 
{
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
    
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    pwm_config_t pwm_cfg;
    
    pwm_configure_default( &pwm_cfg );

    pwm_cfg.pin      = cfg->clk;
    pwm_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm, &pwm_cfg );
    pwm_set_freq( &ctx->pwm, pwm_cfg.freq_hz );
    
    digital_out_init( &ctx->dir, cfg->dir );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t stepper17_default_cfg ( stepper17_t *ctx ) 
{
    err_t error_flag;
    
    uint8_t write_data = 0x00;
    error_flag = stepper17_generic_write( ctx, STEPPER17_REG_CONFIGUARTION_PORT0, &write_data, 1 );
    write_data = 0xFF;
    error_flag |= stepper17_generic_write( ctx, STEPPER17_REG_CONFIGUARTION_PORT1, &write_data, 1 );
    
    stepper17_reset_electrical_angle( ctx );
    stepper17_set_en_state( ctx, 0 );
    
    stepper17_mode( ctx, STEPPER17_MODE_NORMAL );
    stepper17_torque_setting( ctx, STEPPER17_TORQUE_100PCT );
    stepper17_decay_function( ctx, STEPPER17_DECAY_ADMD );
    
    error_flag |= stepper17_set_duty_cycle( ctx, 0.5 );
    error_flag |= stepper17_pwm_start( ctx );
    
    return error_flag;
}

err_t stepper17_generic_write ( stepper17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ];
    uint8_t cnt;

    data_buf[ 0 ] = reg;

    for ( cnt = 1; cnt <= tx_len; cnt++ ) 
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t stepper17_generic_read ( stepper17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t stepper17_set_duty_cycle ( stepper17_t *ctx, float duty_cycle )
{
    return pwm_set_duty( &ctx->pwm, duty_cycle ); 
}

err_t stepper17_pwm_stop ( stepper17_t *ctx )
{
    return pwm_stop( &ctx->pwm ); 
}

err_t stepper17_pwm_start ( stepper17_t *ctx )
{
    return pwm_start( &ctx->pwm ); 
}

void stepper17_set_dir_state ( stepper17_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->dir );
    }
    else
    {
        digital_out_low( &ctx->dir );
    }
}

void stepper17_set_rst_state ( stepper17_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void stepper17_set_en_state ( stepper17_t *ctx, uint8_t state )
{
    if ( state > 0 )
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint8_t stepper17_get_int_state ( stepper17_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t stepper17_step_resolution ( stepper17_t *ctx, uint8_t resolution )
{
    if ( ( resolution >= STEPPER17_STEP_FULL ) && ( resolution <= ( STEPPER17_STEP_1DIV32 + 1 ) ) )
    {
        uint8_t current_settings = 0;
        stepper17_generic_read( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        current_settings &= 0xF8;
        current_settings |= resolution;
        stepper17_generic_write( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        return STEPPER17_OK;
    }
    else
    {
        return STEPPER17_ERROR;
    }
}

err_t stepper17_torque_setting ( stepper17_t *ctx, uint8_t torque )
{
    if ( ( torque == STEPPER17_TORQUE_100PCT ) || ( ( torque >= STEPPER17_TORQUE_75PCT ) && ( torque <= STEPPER17_TORQUE_25PCT ) ) )
    {
        uint8_t current_settings = 0;
        stepper17_generic_read( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        current_settings &= 0x9F;
        current_settings |= torque;
        stepper17_generic_write( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        return STEPPER17_OK;
    }
    else
    {
        return STEPPER17_ERROR;
    }
}

err_t stepper17_decay_function ( stepper17_t *ctx, uint8_t decay )
{
    if ( ( decay == STEPPER17_DECAY_MIXED ) || ( ( decay >= STEPPER17_DECAY_SLOW ) && ( decay <= STEPPER17_DECAY_ADMD ) ) )
    {
        uint8_t current_settings = 0;
        stepper17_generic_read( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        current_settings &= 0xE7;
        current_settings |= decay;
        stepper17_generic_write( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        return STEPPER17_OK;
    }
    else
    {
        return STEPPER17_ERROR;
    }
}

err_t stepper17_mode ( stepper17_t *ctx, uint8_t mode )
{
    if ( ( mode == STEPPER17_MODE_NORMAL ) || ( mode == STEPPER17_MODE_SLEEP ) )
    {
        uint8_t current_settings = 0;
        stepper17_generic_read( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        current_settings &= 0xE7;
        current_settings |= mode;
        stepper17_generic_write( ctx, STEPPER17_REG_OUTPUT_PORT0, &current_settings, 1 );
        return STEPPER17_OK;
    }
    else
    {
        return STEPPER17_ERROR;
    }
}

uint8_t stepper17_get_error ( stepper17_t *ctx )
{
    uint8_t error_status = 0;
    stepper17_generic_read( ctx, STEPPER17_REG_INPUT_PORT1, &error_status, 1 );
    error_status &= 0x03;
    
    return error_status;
}

uint8_t stepper17_get_electrical_angle( stepper17_t *ctx )
{
    uint8_t mo_status = 0;
    stepper17_generic_read( ctx, STEPPER17_REG_INPUT_PORT1, &mo_status, 1 );
    mo_status &= 0x04;
    
    return mo_status;
}

void stepper17_reset_electrical_angle ( stepper17_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_1ms( );
    digital_out_low( &ctx->rst );
}

// ------------------------------------------------------------------------- END
