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

#include "uv3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uv3_cfg_setup ( uv3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ack = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = UV3_I2C_ADDR_DEFAULT;
}

UV3_RETVAL uv3_init ( uv3_t *ctx, uv3_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return UV3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->ack, cfg->ack );

    return UV3_OK;
}

void uv3_default_cfg ( uv3_t *ctx )
{
    uv3_enable_sensor( ctx );
}

void uv3_write_command ( uv3_t *ctx, uint8_t slave_addr, uint8_t command )
{
    uint8_t tx_data = 0;
    
    tx_data = command;

    i2c_master_set_slave_address( &ctx->i2c, slave_addr );
    i2c_master_write( &ctx->i2c, &tx_data, 1 );  
    Delay_100ms( );
}

uint8_t uv3_read_byte ( uv3_t *ctx, uint8_t slave_addr )
{
    uint8_t rx_data = 0;

    i2c_master_set_slave_address( &ctx->i2c, slave_addr );

    i2c_master_read( &ctx->i2c, &rx_data, 1 );  

    return rx_data;
}

void uv3_clear_ack ( uv3_t *ctx )
{
    uint8_t read_data;
    
    read_data = uv3_read_byte( ctx,  UV3_ADDR_ARA );
}

void uv3_enable_sensor ( uv3_t *ctx )
{
    uint8_t cmd_buffer;
    cmd_buffer &= ~UV3_CMD_SD;

    uv3_write_command( ctx, UV3_ADDR_CMD, cmd_buffer );
}

void uv3_disable_mode ( uv3_t *ctx )
{
    uint8_t cmd_buffer;
    cmd_buffer |= UV3_CMD_SD;

    uv3_write_command( ctx, UV3_ADDR_CMD, cmd_buffer );
}

void uv3_set_integration_time ( uv3_t *ctx, uint8_t int_data )
{
    uint8_t cmd_buffer;

    cmd_buffer &= ~UV3_CMD_SD;
    cmd_buffer |= int_data;

    uv3_write_command( ctx, UV3_ADDR_CMD, cmd_buffer );
}

uint16_t uv3_read_measurements ( uv3_t *ctx )
{
    uint16_t result;
    uint8_t read_data;
      
    read_data = uv3_read_byte( ctx,  UV3_ADDR_DATA_MSB );
    
    result = read_data;
    result <<= 8;

    read_data = uv3_read_byte( ctx, UV3_ADDR_DATA_LSB );
         
    result |= read_data;
    
    return result;
}

uint8_t uv3_risk_level ( uint16_t uv_data )
{
    uint8_t cnt;
    uint8_t risk_lvl;
    uint16_t risk_level_table[ 4 ] = { 2241, 4482, 5976, 8217 };
    
    risk_lvl = 5;
        
    for ( cnt = 0; cnt < 4; cnt++ )
    {
        if ( uv_data <= risk_level_table[ 3 - cnt ] )
            risk_lvl = 4 - cnt;
    }

    return risk_lvl;
}

uint8_t uv3_get_interrupt ( uv3_t *ctx )
{
    return digital_in_read( &ctx->ack );
}

// ------------------------------------------------------------------------- END

