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

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t calculate_crc ( uint8_t *ptr, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dht222_cfg_setup ( dht222_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->ow = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DHT222_I2C_ADDRESS;
}

DHT222_RETVAL dht222_init ( dht222_t *ctx, dht222_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) != I2C_MASTER_SUCCESS )
    {
        return DHT222_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->ow, cfg->ow );

    return DHT222_OK;
}


void dht222_generic_write ( dht222_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void dht222_generic_read ( dht222_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t dht222_read_byte ( dht222_t *ctx, uint8_t address )
{
    uint8_t wake_data = DHT222_WAKE_DATA_CMD;
    uint8_t read_data[ 3 ];
    uint8_t response[ 5 ];
    uint16_t result;

    read_data[ 0 ]= DHT222_READ_REG;
    read_data[ 1 ] = address;
    read_data[ 2 ] = DHT222_READ_REQUEST_1_BYTE_CMD;
      
    while ( 1 )
    {
        dht222_generic_write ( ctx, DHT222_WAKE_DATA_CMD, &wake_data, 2 );
        
        Delay_10us( );
    
        i2c_master_write( &ctx->i2c, read_data, 3 );    
        i2c_master_read( &ctx->i2c, response, 5 );

        result = response[ 4 ];
        result <<= 8;
        result |= response[ 3 ];

        if ( calculate_crc( response, 3 ) == result )
            break;
    }
    return response[ 2 ];
}

uint16_t dht222_read_data ( dht222_t *ctx, uint8_t address )
{
    uint8_t wake_data = DHT222_WAKE_DATA_CMD;
    uint8_t read_data[ 3 ];
    uint8_t response[ 6 ];
    uint16_t check_is_correct;
    uint16_t result;
    uint16_t crc;
      
    read_data[ 0 ] = DHT222_READ_REG;
    read_data[ 1 ] = address;
    read_data[ 2 ] = DHT222_READ_REQUEST_2_BYTE_CMD;
    
    while ( 1 )
    {
        dht222_generic_write ( ctx, DHT222_WAKE_DATA_CMD, &wake_data, 2 );
        
        Delay_10us( );
    
        i2c_master_write( &ctx->i2c, read_data, 3 );    
        i2c_master_read( &ctx->i2c, response, 6 );
  
        check_is_correct = response[ 5 ];
        check_is_correct <<= 8;
        check_is_correct |= response[ 4 ];
    
        crc = calculate_crc( response, 4 );
        if ( crc == check_is_correct )
        {
            break;
        }
    } 
    
    result = response[ 2 ];
    result <<= 8;
    result |= response[ 3 ];
      
    return result;
}

uint32_t dht222_read_all_data ( dht222_t *ctx, uint8_t address )
{
    uint8_t wake_data = DHT222_WAKE_DATA_CMD;
    uint8_t read_data[ 3 ];
    uint8_t response[ 8 ];
    uint16_t check_is_correct;
    uint16_t result;
    
    read_data[ 0 ] = DHT222_READ_REG;
    read_data[ 1 ] = address;
    read_data[ 2 ] = DHT222_READ_REQUEST_4_BYTE_CMD;
    
    while ( 1 )
    {
       dht222_generic_write ( ctx, DHT222_WAKE_DATA_CMD, &wake_data, 2 );
        
        Delay_10us( );
    
        i2c_master_write( &ctx->i2c, read_data, 3 );    
        i2c_master_read( &ctx->i2c, response, 8 );
  
        check_is_correct = response[ 7 ];
        check_is_correct <<= 8;
        check_is_correct |= response[ 6 ];
    
        if ( calculate_crc( response, 6 ) == check_is_correct )
            break;
    }
    
    result = response[ 2 ];
    result <<= 8;
    result |= response[ 3 ];
    result <<= 8;
    result |= response[ 4 ];
    result <<= 8;
    result |= response[ 5 ];
    
    return result;
}

uint16_t dht222_get_temperature ( dht222_t *ctx )
{
    uint16_t temperature;
    
    temperature = dht222_read_data( ctx, DHT222_TEMPERATURE_DATA_REG );
    
    return temperature;
}

uint16_t dht222_get_humidity ( dht222_t *ctx )
{
    uint16_t humidity;

    humidity = dht222_read_data( ctx, DHT222_HUMIDITY_DATA_REG );

    return humidity;
}

uint16_t dht222_get_model ( dht222_t *ctx )
{
    return dht222_read_data( ctx, DHT222_MODEL_DATA_REG );
}

uint16_t dht222_get_users_reg1 ( dht222_t *ctx )
{
    return dht222_read_data( ctx, DHT222_USERS_REG_1 );
}

uint16_t dht222_get_users_reg2 ( dht222_t *ctx )
{
    return dht222_read_data( ctx, DHT222_USERS_REG_2 );
}

uint8_t dht222_get_version ( dht222_t *ctx )
{
    return dht222_read_byte( ctx, DHT222_VERSION_DATA_REG );
}

uint32_t dht222_get_id ( dht222_t *ctx )
{
    return dht222_read_all_data( ctx, DHT222_ID_DATA_REG );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t calculate_crc ( uint8_t *ptr, uint8_t len )
{
    uint16_t crc = 65535;
    uint8_t i;
    
    while ( len-- )
    {
        crc ^= *ptr;

        ptr++;

        for ( i = 0; i < 8; i++ )
        {
            if ( crc & 0x01 )
            {
                crc >>= 1;
                crc ^= 40961;
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

