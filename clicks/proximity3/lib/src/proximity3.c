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

PROXIMITY3_RETVAL proximity3_init ( proximity3_t *ctx, proximity3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return PROXIMITY3_OK;
}

void proximity3_write_16 ( proximity3_t *ctx, uint8_t reg_address, uint16_t data_in )
{
    uint8_t tx_buf[ 3 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg_address;
    tx_buf[ 1 ] = ( uint8_t )( data_in & 0x00FF );
    tx_buf[ 2 ] = ( uint8_t )( ( data_in & 0xFF00 ) >> 8 );

    i2c_master_write( &ctx->i2c, tx_buf, 3 );      
}

uint16_t proximity3_read_16 ( proximity3_t *ctx, uint8_t reg_address )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];
    
    uint16_t reg_data;

    tx_buf [ 0 ] = reg_address;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );

    reg_data = rx_buf[ 1 ];
    reg_data <<= 8;
    reg_data |= rx_buf[ 0 ];

    return reg_data;
}

uint16_t proximity3_read_ambient_light_sensor( proximity3_t *ctx )
{
    uint16_t value_als;

    value_als = proximity3_read_16( ctx, PROXIMITY3_AMBIENT_REG );

    return value_als;
}

uint8_t proximity3_read_proximity( proximity3_t *ctx )
{
    uint16_t value_ps;
    uint8_t result_ps;

    value_ps = proximity3_read_16( ctx, PROXIMITY3_PROXIMITY_REG );

    result_ps = ( uint8_t ) ( value_ps & 0x00FF );

    return result_ps;

}

uint8_t proximity3_get_distance( proximity3_t *ctx )
{
    uint8_t value_ps;
    uint8_t number;
    uint8_t counter = 0;
    uint8_t distance[ 17 ]  = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85 };
    uint8_t data_[ 16 ]  = { 170, 130, 110, 83, 62, 50, 39, 30, 23, 17, 13, 12, 10, 8, 7, 6 };

    value_ps = proximity3_read_proximity( ctx );

    for ( counter = 0; counter < 16; counter ++ )
    {
        if ( value_ps > data_[ counter ])
        {
            number = counter;
            counter = 16;
        }
    }

   value_ps = distance[ number ];

   return value_ps;
}


uint16_t proximity3_get_illuminance( proximity3_t *ctx )
{
    uint16_t result;
    uint32_t value_als;

    value_als = ( uint32_t ) proximity3_read_ambient_light_sensor( ctx );

    value_als *= 10;
    value_als  = value_als >> 8;
    result = ( uint16_t ) value_als;

    return result;
}

// ------------------------------------------------------------------------- END

