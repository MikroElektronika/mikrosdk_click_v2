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

#include "proximity3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity3_cfg_setup ( proximity3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = PROXIMITY3_I2CADDR;
}

err_t proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return PROXIMITY3_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY3_OK;
}

err_t proximity3_default_cfg ( proximity3_t *ctx ) 
{
    err_t error_flag = PROXIMITY3_OK;
    Delay_100ms( );

    // Check device ID
    if ( PROXIMITY3_DEVICE_ID_VALUE != proximity3_read_16( ctx, PROXIMITY3_DEVICE_ID_REG ) )
    {
        return PROXIMITY3_ERROR;
    }
    // Default startup options for Ambient Light Sensor
    error_flag |= proximity3_write_16( ctx, PROXIMITY3_ALS_CONF_REG, PROXIMITY3_ALS_CONF_CONFIG );
    Delay_100ms( );

    // Default startup options for Proximity
    error_flag |= proximity3_write_16( ctx, PROXIMITY3_PS_CONF1_CONF2_REG, PROXIMITY3_PS_CONF1_CONF2_CONFIG );
    Delay_100ms( );
    error_flag |= proximity3_write_16( ctx, PROXIMITY3_PS_CONF3_MS_REG, PROXIMITY3_PS_CONF3_MS_CONFIG );
    Delay_100ms( );

    // Set the proximity interrupt levels
    error_flag |= proximity3_write_16( ctx, PROXIMITY3_PS_THDL_REG, PROXIMITY3_PS_THDL_CONFIG );
    Delay_100ms( );
    error_flag |= proximity3_write_16( ctx, PROXIMITY3_PS_THDH_REG, PROXIMITY3_PS_THDH_CONFIG );
    Delay_100ms( );

    return error_flag;
}

err_t proximity3_write_16 ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    
    tx_buf[ 0 ] = reg_address;
    tx_buf[ 1 ] = ( uint8_t )( data_in & 0x00FF );
    tx_buf[ 2 ] = ( uint8_t )( ( data_in & 0xFF00 ) >> 8 );

    return i2c_master_write( &ctx->i2c, tx_buf, 3 );      
}

uint16_t proximity3_read_16 ( proximity3_t *ctx, uint8_t reg_address )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint16_t reg_data = 0;

    i2c_master_write_then_read( &ctx->i2c, &reg_address, 1, rx_buf, 2 );

    reg_data = rx_buf[ 1 ];
    reg_data <<= 8;
    reg_data |= rx_buf[ 0 ];

    return reg_data;
}

uint16_t proximity3_read_als ( proximity3_t *ctx )
{
    return proximity3_read_16( ctx, PROXIMITY3_AMBIENT_REG );
}

uint16_t proximity3_read_proximity ( proximity3_t *ctx )
{
    return proximity3_read_16( ctx, PROXIMITY3_PROXIMITY_REG );
}

// ------------------------------------------------------------------------- END

