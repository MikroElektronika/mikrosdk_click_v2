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

#include "temphum6.h"

/**
 * \defgroup crc_const CRC Const
 * \{
 */     
#define CRC7WIDTH      7
#define CRC7POLY    0x89
#define CRC7IVEC    0x7F
/** \} */

/**
 * \defgroup payload_data Paylaod Data
 * \{
 */   
#define DATA7WIDTH   17
#define DATA7MASK    ( ( 1UL << DATA7WIDTH ) -1 )
#define DATA7MSB     ( 1UL << ( DATA7WIDTH -1 ) )
/** \} */

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint32_t f_crc7 ( uint32_t val );

static void booting_time ( );

static void single_time ( );

static void count_time ( );

static void extract ( uint32_t val, uint16_t *bit_data, uint8_t *status );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum6_cfg_setup ( temphum6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM6_DEVICE_SLAVE_ADDRESS;
}

TEMPHUM6_RETVAL temphum6_init ( temphum6_t *ctx, temphum6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM6_INIT_ERROR;
    }

    return TEMPHUM6_OK;
}

void temphum6_generic_write ( temphum6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );       
}

void temphum6_generic_read ( temphum6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void temphum6_reset ( temphum6_t *ctx )
{
    uint8_t write_reg;

    write_reg = 0x80;
    
    temphum6_generic_write( ctx, TEMPHUM6_REG_SYSTEM_CONTROL, &write_reg, 1 );
    booting_time( );
}

uint16_t temphum6_get_part_id ( temphum6_t *ctx )
{
    volatile uint16_t id;  
    uint8_t read_reg[ 2 ];
    uint8_t tmp;
    
    tmp = 0x00;
   
    temphum6_generic_write( ctx, 0x10, &tmp, 1 );
    booting_time( );
    
    temphum6_generic_read( ctx, 0x00, read_reg, 2 );
    id = read_reg[ 1 ];
    id <<=  8;
    id |= read_reg[ 0 ];

    return id;
}

void temphum6_run ( temphum6_t *ctx )
{
    uint8_t temp_write[ 1 ];
    
    temp_write[ 0 ] = TEMPHUM6_HUM_RUN_SINGLE_SHOT_MODE | TEMPHUM6_TEMP_RUN_SINGLE_SHOT_MODE;
    temphum6_generic_write( ctx, TEMPHUM6_REG_SENS_RUN, temp_write , 1 );
    
    temp_write[ 0 ] = TEMPHUM6_HUM_START_MEASUREMENT | TEMPHUM6_TEMP_START_MEASUREMENT;
    temphum6_generic_write( ctx, TEMPHUM6_REG_SENS_START, temp_write, 1);
}

void temphum6_stop ( temphum6_t *ctx )
{
    uint8_t temp_write[ 1 ];
    
    temp_write[ 0 ] = TEMPHUM6_HUM_STOP_CONTINUOUS_MEASUREMENT | TEMPHUM6_TEMP_STOP_CONTINUOUS_MEASUREMENT;
    temphum6_generic_write( ctx, TEMPHUM6_REG_SENS_STOP,  temp_write, 1 );
}

float temphum6_read_temperature ( temphum6_t *ctx, uint8_t temp_in )
{
    uint8_t read_reg[ 3 ];
    volatile uint32_t temperature;
    uint8_t status;
    uint16_t temp;
    
    temphum6_run( ctx );
    single_time( );

    temphum6_generic_read( ctx, TEMPHUM6_REG_TEMPERATURE, read_reg, 3 );
    
    temperature = ( read_reg[ 2 ] << 16 ) + ( read_reg[ 1 ] << 8 ) + read_reg[ 0 ];

    extract ( temperature, &temp, &status );

    if ( temp_in == TEMPHUM6_TEMP_IN_FAHRENHEIT )
    {
        return ( ( ( ( float )temp / 64 ) - 273.15 ) * 1.8 + 32.0 );
    }
    else if ( temp_in == TEMPHUM6_TEMP_IN_KELVIN )
    {
        return ( ( ( float )temp / 64 ) );
    }
    else
    {
        return ( ( ( float )temp / 64 ) - 273.15 );
    }
}

float temphum6_read_relative_huminidy ( temphum6_t *ctx )
{
    uint8_t read_reg[ 3 ];
    volatile uint32_t humidity;
    uint8_t status;
    uint16_t hum;

    temphum6_run( ctx );
    single_time( );

    temphum6_generic_read( ctx, TEMPHUM6_REG_RELATIVE_HUMIDITY, read_reg, 3 );

    humidity = ( read_reg[ 2 ] << 16 ) + ( read_reg[ 1 ] << 8 ) + read_reg[ 0 ];

    extract( humidity, &hum, &status );

    return ( ( float )hum / 512.0 );
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint32_t f_crc7 ( uint32_t val ) 
{
    uint32_t test_bit;

    // Setup polynomial

    uint32_t pol = CRC7POLY;

    // Align polynomial with data

    pol = pol << ( DATA7WIDTH - CRC7WIDTH - 1 );

    // Loop variable (indicates which bit to test, start with highest)

    test_bit = DATA7MSB;
    
    // Make room for CRC value

    val = val << CRC7WIDTH;
    test_bit = test_bit << CRC7WIDTH;
    pol = pol << CRC7WIDTH;

    // Insert initial vector

    val |= CRC7IVEC;

    // Apply division until all bits done

    while ( test_bit & ( DATA7MASK << CRC7WIDTH ) ) 
    {
        if ( test_bit & val ) 
        { 
            val ^= pol;
        }
        test_bit >>= 1;
        pol >>= 1;
    }

    return val;
}

static void booting_time ( )
{
    Delay_1ms( );
    Delay_1ms( );
    Delay_1ms( );
}

static void single_time ( )
{
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void count_time ( )
{
    Delay_100ms( );   
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
    Delay_10ms( );
}

static void extract ( uint32_t val, uint16_t *bit_data, uint8_t *status )
{
    uint8_t  valid;
    uint32_t crc;
    uint32_t payload;
    uint8_t  crc_ok;

    *bit_data = ( val >> 0 )  & 0xffff;
    valid     = ( val >> 16 ) & 0x1;
    crc       = ( val >> 17 ) & 0x7f;
    payload   = ( val >> 0 )  & 0x1ffff;

    if ( f_crc7( payload ) == crc )
    {
        crc_ok = 1;
    }
    else
    {
        crc_ok = 0;
    }

    if( crc_ok != 1 )
    {
        *status = TEMPHUM6_STATUS_CRC_ERROR;
    }
    else if( valid != 1 )
    {
        *status= TEMPHUM6_STATUS_INVALID;
    }
    else
    {
        *status= TEMPHUM6_STATUS_OK;
    }
}

// ------------------------------------------------------------------------- END

