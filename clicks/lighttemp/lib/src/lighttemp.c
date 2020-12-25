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

#include "lighttemp.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lighttemp_cfg_setup ( lighttemp_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->pwm1 = HAL_PIN_NC;
    cfg->pwm2  = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;

    cfg->dev_pwm_freq = LIGHTTEMP_DEF_FREQ;
}

LIGHTTEMP_RETVAL lighttemp_init ( lighttemp_t *ctx, lighttemp_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    pwm_config_t pwm1_cfg;
    pwm_config_t pwm2_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return LIGHTTEMP_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    pwm_configure_default( &pwm1_cfg );

    pwm1_cfg.pin      = cfg->pwm1;
    pwm1_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm1, &pwm1_cfg );
    pwm_set_freq( &ctx->pwm1, pwm1_cfg.freq_hz );
    
    pwm_configure_default( &pwm2_cfg );
    pwm2_cfg.pin      = cfg->pwm2;
    pwm2_cfg.freq_hz  = cfg->dev_pwm_freq;

    ctx->pwm_freq = cfg->dev_pwm_freq;
    pwm_open( &ctx->pwm2, &pwm2_cfg );
    pwm_set_freq( &ctx->pwm2, pwm2_cfg.freq_hz );
    
    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return LIGHTTEMP_OK;
}

void lighttemp_generic_write ( lighttemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );    
}

void lighttemp_generic_read ( lighttemp_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t lighttemp_get_pg_voltage ( lighttemp_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t read_data;
    double res;

    i2c_master_read( &ctx->i2c, read_reg, 2 );

    read_data = read_reg[ 0 ];
    read_data = read_data << 8;
    read_data = read_data | read_reg[ 1 ];
    
    read_data = read_data & 0x0FFF;
    
    res = (double) read_data / 4096.0;
    res *= 3300.0;
    
    return (uint16_t) res;
}

uint8_t lighttemp_get_interrupt_state ( lighttemp_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void lighttemp_led1_set_duty_cycle ( lighttemp_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm1, duty_cycle ); 
}

void lighttemp_led1_pwm_stop ( lighttemp_t *ctx )
{
    pwm_stop( &ctx->pwm1 ); 
}

void lighttemp_led1_pwm_start ( lighttemp_t *ctx )
{
    pwm_start( &ctx->pwm1 ); 
}

void lighttemp_led2_set_duty_cycle ( lighttemp_t *ctx, float duty_cycle )
{
    pwm_set_duty( &ctx->pwm2, duty_cycle ); 
}

void lighttemp_led2_pwm_stop ( lighttemp_t *ctx )
{
    pwm_stop( &ctx->pwm2 ); 
}

void lighttemp_led2_pwm_start ( lighttemp_t *ctx )
{
    pwm_start( &ctx->pwm2 ); 
}


// ------------------------------------------------------------------------- END

