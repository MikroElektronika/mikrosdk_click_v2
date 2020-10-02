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

#include "c6dofimu7.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c6dofimu7_cfg_setup ( c6dofimu7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int2 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = C6DOFIMU7_SLAVE_ADDRESS;
}

C6DOFIMU7_RETVAL c6dofimu7_init ( c6dofimu7_t *ctx, c6dofimu7_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return C6DOFIMU7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    return C6DOFIMU7_OK;
}

void c6dofimu7_default_cfg ( c6dofimu7_t *ctx )
{
    uint8_t power_management_l;
    uint8_t power_management_h;

    power_management_l = C6DOFIMU7_PWM_MGMT_L;
    power_management_h = C6DOFIMU7_PWM_MGMT_H;

    c6dofimu7_generic_write( ctx, C6DOFIMU7_PWR_MGMT, &power_management_l, 1 );
    Delay_10ms( );
    c6dofimu7_generic_write( ctx, C6DOFIMU7_PWR_MGMT, &power_management_h, 1 );
    Delay_10ms( );
}

void c6dofimu7_get_accel_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *accel, float sensitivity )
{
    accel->x_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_ACCEL_XOUT_H ) / sensitivity;
    accel->y_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_ACCEL_YOUT_H ) / sensitivity;
    accel->z_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_ACCEL_ZOUT_H ) / sensitivity;
}

void c6dofimu7_get_gyro_data ( c6dofimu7_t *ctx, c6dofimu7_axis_t *gyro, float sensitivity )
{   
    gyro->x_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_GYRO_XOUT_H ) / sensitivity;
    gyro->y_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_GYRO_YOUT_H ) / sensitivity;
    gyro->z_axis = c6dofimu7_read_word( ctx, C6DOFIMU7_GYRO_ZOUT_H ) / sensitivity;
}

float c6dofimu7_get_temp_data ( c6dofimu7_t *ctx, float temp_sensitivity, float temp_offset )
{
    float temperature_output;

    temperature_output = ( float ) c6dofimu7_read_word( ctx, C6DOFIMU7_TEMP_OUT_H );
    temperature_output -= temp_offset * temp_sensitivity;
    temperature_output = ( temperature_output / temp_sensitivity ) + 21;

    return temperature_output;
}

int16_t c6dofimu7_read_word ( c6dofimu7_t *ctx, uint8_t address ) 
{
    int16_t temp_var;
    uint8_t temp_buf[ 2 ];

    c6dofimu7_generic_read( ctx, address, temp_buf, 2 );

    temp_var = temp_buf[ 0 ];
    temp_var <<= 8;
    temp_var |= temp_buf[ 1 ];

    return temp_var;
}

void c6dofimu7_generic_write ( c6dofimu7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void c6dofimu7_generic_read ( c6dofimu7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t c6dofimu7_get_pwm_input ( c6dofimu7_t *ctx )
{
    return digital_in_read( &ctx->int2 );
}

uint8_t c6dofimu7_get_int_input ( c6dofimu7_t *ctx )
{
    return digital_in_read( &ctx->int1 );
}

// ------------------------------------------------------------------------- END

