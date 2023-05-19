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

#include "dht222.h"

// Return current level of SCL line, 0 or 1
static uint8_t dht222_read_scl ( dht222_t *ctx );

// Set SCL pin as input (high-impedance)
static void dht222_set_scl ( dht222_t *ctx );

// Drive SCL signal low
static void dht222_clear_scl ( dht222_t *ctx );

// Return current level of SDA line, 0 or 1
static uint8_t dht222_read_sda ( dht222_t *ctx );

// Set SDA pin as input (high-impedance)
static void dht222_set_sda ( dht222_t *ctx );

// Drive SDA signal low
static void dht222_clear_sda ( dht222_t *ctx );

// Send I2C stop condition
static err_t dht222_i2c_stop ( dht222_t *ctx );

// Send I2C start condition
static err_t dht222_i2c_start ( dht222_t *ctx );

// Write a LSB bit of data_in to I2C bus
static err_t dht222_i2c_write_bit ( dht222_t *ctx, uint8_t data_in );

// Read a bit from I2C bus and store it into LSB of data_out
static err_t dht222_i2c_read_bit ( dht222_t *ctx, uint8_t *data_out );

// Write a data_in byte to I2C bus. Return 0 if ack by the target
// Also sends start/stop condition if send_start/send_stop is true
static err_t dht222_i2c_write_byte ( dht222_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop );

// Read a byte from I2C bus and store it into data_out
// Sends NACK if nack is true, otherwise responds with ACK.
// Also sends stop condition if send_stop is true
static err_t dht222_i2c_read_byte ( dht222_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop );

// Calculate CRC 16-bit from data_in array
static uint16_t dht222_calculate_crc ( uint8_t *data_in, uint8_t len );

void dht222_cfg_setup ( dht222_cfg_t *cfg )
{
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
}

err_t dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg )
{
    ctx->scl = cfg->scl;
    ctx->sda = cfg->sda;
    ctx->i2c_started = false;
    return DHT222_OK;
}

err_t dht222_read_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = DHT222_OK;
    uint8_t data_buf[ 24 ] = { 0 };
    uint16_t crc = 0;
    if ( ( len + address ) > 20 )
    {
        return DHT222_ERROR;
    }
    // Send wake up command, sensor responds with NACK so we don't check it for errors here
    dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_WRITE, true, false );
    Delay_1ms( );
    Delay_1ms( );
    error_flag |= dht222_i2c_stop ( ctx );
    Delay_5ms( );

    // Send instruction
    error_flag |= dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_WRITE, true, false );
    Delay_10us( );
    error_flag |= dht222_i2c_write_byte ( ctx, DHT222_CMD_READ, false, false );
    error_flag |= dht222_i2c_write_byte ( ctx, address, false, false );
    error_flag |= dht222_i2c_write_byte ( ctx, len, false, true );
    Delay_5ms( );
    
    // Read response
    error_flag |= dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_READ, true, false );
    Delay_50us( );
    for ( uint8_t cnt = 0; cnt < ( len + 3 ); cnt++ )
    {
        error_flag |= dht222_i2c_read_byte ( ctx, &data_buf[ cnt ], false, false );
    }
    error_flag |= dht222_i2c_read_byte ( ctx, &data_buf[ len + 3 ], true, true );
    // Check CRC
    crc = dht222_calculate_crc ( data_buf, len + 2 );
    if ( ( ( ( uint16_t ) data_buf[ len + 3 ] << 8 ) | data_buf[ len + 2 ] ) != crc )
    {
        error_flag = DHT222_ERROR;
    }
    if ( DHT222_OK == error_flag )
    {
        memcpy ( data_out, &data_buf[ 2 ], len );
    }
    return error_flag;
}

err_t dht222_write_reg ( dht222_t *ctx, uint8_t address, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = DHT222_OK;
    uint8_t data_buf[ 25 ] = { 0 };
    uint16_t crc = 0;
    if ( ( len + address ) > 20 )
    {
        return DHT222_ERROR;
    }
    data_buf[ 0 ] = DHT222_CMD_WRITE;
    data_buf[ 1 ] = address;
    data_buf[ 2 ] = len;
    memcpy ( &data_buf[ 3 ], data_in, len );
    crc = dht222_calculate_crc ( data_buf, len + 3 );
    data_buf[ len + 3 ] = ( uint8_t ) ( crc & 0xFF );
    data_buf[ len + 4 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    
    // Send wake up command, sensor responds with NACK so we don't check it for errors here
    dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_WRITE, true, false );
    Delay_1ms( );
    Delay_1ms( );
    error_flag |= dht222_i2c_stop ( ctx );
    Delay_5ms( );

    // Send instruction
    error_flag |= dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_WRITE, true, false );
    Delay_10us( );
    for ( uint8_t cnt = 0; cnt < ( len + 5 ); cnt++ )
    {
        error_flag |= dht222_i2c_write_byte ( ctx, data_buf[ cnt ], false, false );
    }
    error_flag |= dht222_i2c_stop ( ctx );
    Delay_5ms( );
    
    // Read response
    error_flag |= dht222_i2c_write_byte ( ctx, DHT222_I2C_ADDRESS_READ, true, false );
    Delay_50us( );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        error_flag |= dht222_i2c_read_byte ( ctx, &data_buf[ cnt ], false, false );
    }
    error_flag |= dht222_i2c_read_byte ( ctx, &data_buf[ 4 ], true, true );
    
    // Check CRC
    crc = dht222_calculate_crc ( data_buf, 3 );
    if ( ( ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ] ) != crc )
    {
        error_flag = DHT222_ERROR;
    }
    return error_flag;
}

err_t dht222_get_temperature ( dht222_t *ctx, uint16_t *temperature )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = dht222_read_reg ( ctx, DHT222_REG_TEMPERATURE_MSB, data_buf, 2 );
    if ( DHT222_OK == error_flag )
    {
        *temperature = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t dht222_get_humidity ( dht222_t *ctx, uint16_t *humidity )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = dht222_read_reg ( ctx, DHT222_REG_HUMIDITY_MSB, data_buf, 2 );
    if ( DHT222_OK == error_flag )
    {
        *humidity = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t dht222_get_temp_hum ( dht222_t *ctx, uint16_t *temperature, uint16_t *humidity )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t error_flag = dht222_read_reg ( ctx, DHT222_REG_HUMIDITY_MSB, data_buf, 4 );
    if ( DHT222_OK == error_flag )
    {
        *humidity = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        *temperature = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    }
    return error_flag;
}

static uint8_t dht222_read_scl ( dht222_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
    return digital_in_read ( &scl );
}

static void dht222_set_scl ( dht222_t *ctx )
{
    digital_in_t scl;
    digital_in_init ( &scl, ctx->scl );
}

static void dht222_clear_scl ( dht222_t *ctx )
{
    digital_out_t scl;
    digital_out_init ( &scl, ctx->scl );
    digital_out_low ( &scl );
}

static uint8_t dht222_read_sda ( dht222_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
    return digital_in_read ( &sda );
}

static void dht222_set_sda ( dht222_t *ctx )
{
    digital_in_t sda;
    digital_in_init ( &sda, ctx->sda );
}

static void dht222_clear_sda ( dht222_t *ctx )
{
    digital_out_t sda;
    digital_out_init ( &sda, ctx->sda );
    digital_out_low ( &sda );
}

static err_t dht222_i2c_start ( dht222_t *ctx )
{
    uint32_t timeout_cnt = 0;
    if ( ctx->i2c_started ) 
    { 
        // If started, do a restart condition, set SDA
        dht222_set_sda ( ctx );
        Delay_10us ( );
        dht222_set_scl ( ctx );
        while ( 0 == dht222_read_scl ( ctx ) ) 
        {   
            // Clock stretching
            if ( ++timeout_cnt > DHT222_TIMEOUT )
            {
                return DHT222_ERROR;
            }
        }
        // Repeated start setup time, minimum 4.7us
        Delay_10us ( );
    }

    if ( 0 == dht222_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return DHT222_ERROR;
    }

    // SCL is high, clear SDA
    dht222_clear_sda ( ctx );
    Delay_10us ( );
    dht222_clear_scl ( ctx );
    ctx->i2c_started = true;
    return DHT222_OK;
}

static err_t dht222_i2c_stop ( dht222_t *ctx )
{
    uint32_t timeout_cnt = 0;
    // Clear SDA
    dht222_clear_sda ( ctx );
    Delay_10us ( );

    dht222_set_scl ( ctx );
    while ( 0 == dht222_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > DHT222_TIMEOUT )
        {
            return DHT222_ERROR;
        }
    }

    // Stop bit setup time, minimum 4us
    Delay_10us ( );

    // SCL is high, set SDA
    dht222_set_sda ( ctx );
    Delay_10us ( );

    if ( 0 == dht222_read_sda ( ctx ) ) 
    {
        // Lost arbitration
        return DHT222_ERROR;
    }
    ctx->i2c_started = false;
    return DHT222_OK;
}

static err_t dht222_i2c_write_bit ( dht222_t *ctx, uint8_t data_in )
{
    uint32_t timeout_cnt = 0;
    if ( data_in ) 
    {
        dht222_set_sda ( ctx );
    } 
    else 
    {
        dht222_clear_sda ( ctx );
    }

    // SDA change propagation delay
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    dht222_set_scl ( ctx );

    // Wait for SDA value to be read by target, minimum of 4us for standard mode
    Delay_10us ( );

    while ( 0 == dht222_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > DHT222_TIMEOUT )
        {
            return DHT222_ERROR;
        }
    }

    // SCL is high, now data is valid
    // If SDA is high, check that nobody else is driving SDA
    if ( data_in && ( 0 == dht222_read_sda ( ctx ) ) ) 
    {
        return DHT222_ERROR;
    }

    // Clear the SCL to low in preparation for next change
    dht222_clear_scl ( ctx );
    return DHT222_OK;
}

static err_t dht222_i2c_read_bit ( dht222_t *ctx, uint8_t *data_out ) 
{
    uint32_t timeout_cnt = 0;
    // Let the target drive data
    dht222_set_sda ( ctx );

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // Set SCL to indicate a new valid SDA value is available
    dht222_set_scl ( ctx );

    while ( 0 == dht222_read_scl ( ctx ) ) 
    {   
        // Clock stretching
        if ( ++timeout_cnt > DHT222_TIMEOUT )
        {
            return DHT222_ERROR;
        }
    }

    // Wait for SDA value to be written by target, minimum of 4us for standard mode
    Delay_10us ( );

    // SCL is high, read out bit
    *data_out = dht222_read_sda ( ctx );

    // Set SCL low in preparation for next operation
    dht222_clear_scl ( ctx );

    return DHT222_OK;
}

static err_t dht222_i2c_write_byte ( dht222_t *ctx, uint8_t data_in, uint8_t send_start, uint8_t send_stop )
{
    err_t error_flag = DHT222_OK;
    uint8_t nack = 0;

    if ( send_start ) 
    {
        error_flag |= dht222_i2c_start ( ctx );
    }

    for ( int8_t bit_cnt = 7; bit_cnt >= 0; bit_cnt-- )
    {
        error_flag |= dht222_i2c_write_bit ( ctx, ( ( data_in >> bit_cnt ) & 0x01 ) );
    }

    error_flag |= dht222_i2c_read_bit ( ctx, &nack );

    if ( send_stop ) 
    {
        error_flag |= dht222_i2c_stop ( ctx );
    }
    
    if ( nack )
    {
        error_flag = DHT222_ERROR;
    }
    
    return error_flag;
}

static err_t dht222_i2c_read_byte ( dht222_t *ctx, uint8_t *data_out, uint8_t nack, uint8_t send_stop )
{
    err_t error_flag = DHT222_OK;
    uint8_t rd_byte = 0;
    uint8_t rd_bit = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
    {
        error_flag |= dht222_i2c_read_bit ( ctx, &rd_bit );
        rd_byte = ( rd_byte << 1 ) | rd_bit;
    }

    error_flag |= dht222_i2c_write_bit ( ctx, nack );

    if ( send_stop ) 
    {
        error_flag |= dht222_i2c_stop ( ctx );
    }
    
    if ( DHT222_OK == error_flag )
    {
        *data_out = rd_byte;
    }

    return error_flag;
}

static uint16_t dht222_calculate_crc ( uint8_t *data_in, uint8_t len )
{
    uint16_t crc = 0xFFFF;
    for ( uint8_t byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        crc ^= *data_in++;
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc & 0x01 )
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END

