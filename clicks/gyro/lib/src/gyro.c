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

#include "gyro.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gyro_cfg_setup ( gyro_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = GYRO_L3GD20_I2C_ADDRESS;
}

GYRO_RETVAL gyro_init ( gyro_t *ctx, gyro_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return GYRO_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GYRO_OK;

}

void gyro_default_cfg ( gyro_t *ctx )
{
    gyro_write_data( ctx, GYRO_L3GD20_REGISTER_CTRL_REG1, GYRO_L3GD20_REG1_NORMAL_MODE );
    gyro_write_data( ctx, GYRO_L3GD20_REGISTER_CTRL_REG4, GYRO_L3GD20_REG4_250DPS );
    gyro_write_data( ctx, GYRO_L3GD20_REGISTER_CTRL_REG5, GYRO_L3GD20_REG5_FIFO_ENABLE_INT1 );
    gyro_write_data( ctx, GYRO_L3GD20_REGISTER_FIFO_CTRL_REG, GYRO_L3GD20_FIFO_CTRL_REG_CONFIG );
}

void gyro_write_data ( gyro_t *ctx, uint8_t address, uint8_t write_command )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = address;
    tx_buf[ 1 ] = write_command;


    i2c_master_write( &ctx->i2c, tx_buf, 2 );      
}

uint8_t gyro_read_data ( gyro_t *ctx, uint8_t address )
{
    uint8_t tx_buf;
    
    i2c_master_write_then_read( &ctx->i2c, &address, 1, &tx_buf, 1 );

    return tx_buf;
}

int16_t gyro_get_axis ( gyro_t *ctx, uint8_t adr_reg_low )
{
    uint16_t result;
    uint8_t buffer[ 2 ];

    buffer[ 0 ] = gyro_read_data( ctx, adr_reg_low );
    buffer[ 1 ] = gyro_read_data( ctx, adr_reg_low + 1 );

    result = buffer[ 1 ];
    result <<= 8;
    result |= buffer[ 0 ];

    return ( int16_t )result;
}

void gyro_read_gyro ( gyro_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z )
{
    *gyro_x = gyro_get_axis( ctx, GYRO_L3GD20_REGISTER_OUT_X_L );
    *gyro_y = gyro_get_axis( ctx, GYRO_L3GD20_REGISTER_OUT_Y_L );
    *gyro_z = gyro_get_axis( ctx, GYRO_L3GD20_REGISTER_OUT_Z_L );
}

// ------------------------------------------------------------------------- END

