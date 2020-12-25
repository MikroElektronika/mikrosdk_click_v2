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

#include "thermo13.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_conversion_delay( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo13_cfg_setup ( thermo13_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO13_DEVICE_SLAVE_ADDR_000;
}

THERMO13_RETVAL thermo13_init ( thermo13_t *ctx, thermo13_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO13_INIT_ERROR;
    }
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->int_pin, cfg->int_pin );

    return THERMO13_OK;
}

void thermo13_generic_write ( thermo13_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo13_generic_read ( thermo13_t *ctx, uint8_t reg, uint8_t *data_buf, 
uint8_t len )
{
    
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t thermo13_read_data (  thermo13_t *ctx, uint8_t reg_addr)
{

    uint8_t read_data[ 2 ];
    uint16_t raw_data;

    thermo13_generic_read( ctx, reg_addr, read_data, 2 );

    raw_data = read_data[ 0 ];
    raw_data <<= 8;
    raw_data |= read_data[ 1 ];

    return raw_data;
}

void thermo13_configuration ( thermo13_t *ctx, uint16_t cfg_data )
{
    uint8_t write_data[ 2 ];
    
    write_data[ 0 ] = ( cfg_data >> 8 ) & 0x00FF;
    write_data[ 1 ] =  cfg_data & 0x00FF;
    
    thermo13_generic_write( ctx, THERMO13_REG_CONFIGURATION, write_data, 2 );
}

float thermo13_get_ambient_temperature_data ( thermo13_t *ctx, uint8_t temp_in )
{
    uint16_t raw_temp;
    float temperature;

    raw_temp =  thermo13_read_data( ctx, THERMO13_REG_TEMPERATURE );
    raw_temp >>= 4;
    
    
    if ( raw_temp > 0x1000 )
    {
        temperature =  ( ( float )raw_temp - 4096) / 16.0;
    }
    else
    {
        temperature = ( float )raw_temp / 16.0;
    }

    dev_conversion_delay( );

    if ( temp_in ==  THERMO13_TEMP_IN_KELVIN )
    {
        temperature = temperature + 273.15;
    }
    else if ( temp_in  ==  THERMO13_TEMP_IN_FAHRENHEIT )
    {
        temperature = ( temperature * 9.0/5.0 ) + 32;
    }

    return temperature;
}

void thermo13_set_temp_limit ( thermo13_t *ctx, uint8_t temp_reg, float temp )
{
    uint16_t temp_data;
    uint8_t write_data[ 2 ];

    temp_data = ( uint16_t ) ( temp * 16 );
    temp_data <<= 4;

    write_data[ 0 ] = ( temp_data >> 8 );
    write_data[ 1 ] = ( temp_data & 0x00FF );
    
    thermo13_generic_write( ctx, temp_reg, write_data, 2 );
}

float thermo13_get_temp_limit ( thermo13_t *ctx, uint8_t temp_reg )
{
    float temperature;
    uint16_t temp_data;

    temp_data = thermo13_read_data( ctx, temp_reg );
    temp_data >>= 4;

    temperature = ( float )temp_data / 16.0;

    return temperature;
}

uint8_t thermo13_get_interrupt_state( thermo13_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void thermo13_software_reset ( thermo13_t *ctx )
{
    uint8_t write_data;

    write_data = 0x01;
    thermo13_generic_write( ctx, THERMO13_REG_SOFTWARE_RESET, &write_data, 1 );
    
    Delay_100ms();

    write_data = 0x00;
    thermo13_generic_write( ctx, THERMO13_REG_SOFTWARE_RESET, &write_data, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_conversion_delay ( void )
{
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
    Delay_10ms();
}

// ------------------------------------------------------------------------- END


