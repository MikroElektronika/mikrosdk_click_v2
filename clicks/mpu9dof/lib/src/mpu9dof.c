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

#include "mpu9dof.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mpu9dof_cfg_setup ( mpu9dof_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->fsy = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MPU9DOF_XLG_I2C_ADDR_0;
    cfg->i2c_mag_address = MPU9DOF_M_I2C_ADDR_0;
}

MPU9DOF_RETVAL mpu9dof_init ( mpu9dof_t *ctx, mpu9dof_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->magnetometer_address = cfg->i2c_mag_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MPU9DOF_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->fsy, cfg->fsy );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return MPU9DOF_OK;
}

void mpu9dof_default_cfg ( mpu9dof_t *ctx )
{
    uint8_t command;

    // Chip reset 
    command = MPU9DOF_BIT_H_RESET;
    mpu9dof_generic_write( ctx, MPU9DOF_PWR_MGMT_1, &command, 1 );
    Delay_10ms( );

    // Initialize accel & gyro 
    command = MPU9DOF_DEFAULT;
    mpu9dof_generic_write( ctx, MPU9DOF_SMPLRT_DIV, &command, 1 );
    Delay_10ms( );

    command = MPU9DOF_BITS_DLPF_CFG_42HZ;
    mpu9dof_generic_write( ctx, MPU9DOF_CONFIG, &command, 1 );
    Delay_10ms( );

    command = MPU9DOF_BITS_FS_1000DPS;
    mpu9dof_generic_write( ctx, MPU9DOF_GYRO_CONFIG, &command, 1 );
    Delay_10ms( );

    command = MPU9DOF_BITS_AFSL_SEL_8G;
    mpu9dof_generic_write( ctx, MPU9DOF_ACCEL_CONFIG, &command, 1 );
    Delay_10ms( );

    // Disable FIFOs
    command = MPU9DOF_BIT_FIFO_DIS;
    mpu9dof_generic_write( ctx, MPU9DOF_FIFO_EN , &command, 1 );
    Delay_10ms( );

    // Bypass mode enabled
    command = MPU9DOF_BIT_INT_PIN_CFG;
    mpu9dof_generic_write( ctx, MPU9DOF_INT_PIN_CFG , &command, 1 );
    Delay_10ms( );

    // Disable all interrupts
    command = MPU9DOF_DEFAULT;
    mpu9dof_generic_write( ctx, MPU9DOF_INT_ENABLE , &command, 1 );
    Delay_10ms( );

    // No FIFO and no I2C slaves
    command = MPU9DOF_DEFAULT;
    mpu9dof_generic_write( ctx, MPU9DOF_USER_CTRL , &command, 1 );
    Delay_10ms( );

    // No power management, internal clock source
    command = MPU9DOF_DEFAULT;
    mpu9dof_generic_write( ctx, MPU9DOF_PWR_MGMT_1, &command, 1 );
    Delay_10ms( );
    command = MPU9DOF_DEFAULT;
    mpu9dof_generic_write( ctx, MPU9DOF_PWR_MGMT_2, &command, 1 );
    Delay_10ms( );

    // Initialize magnetometer 
    mpu9dof_write_data_mag( ctx, MPU9DOF_MAG_CNTL, MPU9DOF_BIT_RAW_RDY_EN );
    Delay_10ms( );
}

void mpu9dof_generic_write ( mpu9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

void mpu9dof_generic_read ( mpu9dof_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = reg;

    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_buf, len );
}

// Generic write data function MPU-9150 MAG 
void mpu9dof_write_data_mag ( mpu9dof_t *ctx, uint8_t address, uint8_t write_command )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = address;
    tx_buf[ 1 ] = write_command;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->magnetometer_address );
    i2c_master_write( &ctx->i2c, tx_buf, 2 ); 
}

// Generic read data function MPU-9150 MAG 
uint8_t mpu9dof_read_data_mag ( mpu9dof_t *ctx, uint8_t address )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 1 ];

    write_reg[ 0 ] = address;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->magnetometer_address );
    i2c_master_write_then_read( &ctx->i2c, write_reg, 1, read_reg, 1 );

    return read_reg[ 0 ];
}

// Function get data from MPU-9150 XL G register 
int16_t mpu9dof_get_axis ( mpu9dof_t *ctx, uint8_t adr_reg_high )
{
    uint16_t result;
    uint8_t buffer[ 2 ];

    mpu9dof_generic_read( ctx, adr_reg_high, buffer, 2 );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

// Function get data from MPU-9150 MAG register
int16_t mpu9dof_get_axis_mag ( mpu9dof_t *ctx, uint8_t adr_reg_low )
{
    uint16_t result;
    uint8_t buffer[ 2 ];
    
    mpu9dof_write_data_mag( ctx, MPU9DOF_MAG_CNTL, 0x01);
    Delay_10ms( );

    buffer[ 0 ] = mpu9dof_read_data_mag( ctx, adr_reg_low + 1 );
    buffer[ 1 ] = mpu9dof_read_data_mag( ctx, adr_reg_low );

    result = buffer[ 0 ];
    result <<= 8;
    result |= buffer[ 1 ];

    return result;
}

// Function read Gyro X-axis, Y-axis and Z-axis axis
void mpu9dof_read_gyro ( mpu9dof_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = mpu9dof_get_axis( ctx, MPU9DOF_GYRO_XOUT_H );
    *gyro_y = mpu9dof_get_axis( ctx, MPU9DOF_GYRO_YOUT_H );
    *gyro_z = mpu9dof_get_axis( ctx, MPU9DOF_GYRO_ZOUT_H );
}

// Function read Accel X-axis, Y-axis and Z-axis 
void mpu9dof_read_accel ( mpu9dof_t *ctx, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z )
{
    *accel_x = mpu9dof_get_axis( ctx, MPU9DOF_ACCEL_XOUT_H );
    *accel_y = mpu9dof_get_axis( ctx, MPU9DOF_ACCEL_YOUT_H );
    *accel_z = mpu9dof_get_axis( ctx, MPU9DOF_ACCEL_ZOUT_H );
}

// Function read Magnetometar X-axis, Y-axis and Z-axis 
void mpu9dof_read_mag ( mpu9dof_t *ctx, int16_t *mag_x, int16_t *mag_y, int16_t *mag_z )
{
    *mag_x = mpu9dof_get_axis_mag( ctx, MPU9DOF_MAG_XOUT_L );
    *mag_y = mpu9dof_get_axis_mag( ctx, MPU9DOF_MAG_YOUT_L );
    *mag_z = mpu9dof_get_axis_mag( ctx, MPU9DOF_MAG_ZOUT_L );
}

// Function read Temperature data from MPU-9150 XL G register
float mpu9dof_read_temperature ( mpu9dof_t *ctx )
{
    int16_t result;
    float temperature;
    temperature = 0.00;

    result = mpu9dof_get_axis( ctx, MPU9DOF_TEMP_OUT_H );
    Delay_10ms( );

    temperature =  ( float ) result;
    temperature -= 21;
    temperature /= 333.87;
    temperature += 21;

    return temperature;
}

uint8_t get_int_pin_state ( mpu9dof_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void adapter_turn_fsy_on ( mpu9dof_t *ctx )
{
    digital_out_high( &ctx->fsy );
}

void adapter_turn_fsy_off ( mpu9dof_t *ctx )
{
    digital_out_low( &ctx->fsy );
}
// ------------------------------------------------------------------------- END

