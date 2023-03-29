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

#include "thermo4.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// Device I2C addresses
#define THERMO4_I2C_SLAVE_ADDR         0x48

//Register addresses
#define THERMO4_TEMP_REG_ADDR          0x00
#define THERMO4_CONFIG_REG_ADDR        0x01
#define THERMO4_THYST_REG_ADDR         0x02
#define THERMO4_TOS_REG_ADDR           0x03

//Configuration values
#define THERMO4_SHUTDOWN               0x01
#define THERMO4_POWERUP                0xFE
#define THERMO4_INTERRUPT_MODE         0x02
#define THERMO4_COMPARATOR_MODE        0xFD
#define THERMO4_OS_ACTIVE_HIGH         0x04
#define THERMO4_OS_ACTIVE_LOW          0xFB
#define THERMO4_FAULT_QUEUE_1          0xE7
#define THERMO4_FAULT_QUEUE_2          0x08
#define THERMO4_FAULT_QUEUE_4          0x10
#define THERMO4_FAULT_QUEUE_6          0x18

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo4_cfg_setup ( thermo4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

THERMO4_RETVAL thermo4_init ( thermo4_t *ctx, thermo4_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO4_OK;
}

void thermo4_write_byte ( thermo4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = data_in;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );      
}

void thermo4_read_byte ( thermo4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t tx_buf[ 1 ];

    tx_buf [ 0 ] = reg;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, 1 );
}

void thermo4_write_data ( thermo4_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_buf[ 3 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( uint8_t ) data_in;
    tx_buf[ 2 ] = ( uint8_t ) ( data_in >> 8 ); 

    i2c_master_write( &ctx->i2c, tx_buf, 3 );
}

void thermo4_read_data ( thermo4_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t rx_buf[ 2 ];
    uint16_t res = 0;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 2 );
    
    res = rx_buf[ 0 ];
    res = res << 8;
    res = res | rx_buf[ 1 ];
    *data_out = res;
}

void thermo4_write_cfg ( thermo4_t *ctx, uint8_t wr_cfg )
{
    thermo4_write_byte( ctx, THERMO4_CONFIG_REG_ADDR, wr_cfg );
}

uint8_t thermo4_read_cfg ( thermo4_t *ctx )
{
    uint8_t result;

    thermo4_read_byte( ctx, THERMO4_CONFIG_REG_ADDR, &result );

    return result;
}

void thermo4_shut_down ( thermo4_t *ctx )
{
    thermo4_write_byte( ctx , THERMO4_CONFIG_REG_ADDR, THERMO4_SHUTDOWN );
}

void thermo4_power_up ( thermo4_t *ctx )
{
    thermo4_write_byte( ctx, THERMO4_CONFIG_REG_ADDR, THERMO4_POWERUP );
}

void thermo4_reset ( thermo4_t *ctx )
{
    thermo4_write_byte( ctx, THERMO4_CONFIG_REG_ADDR, THERMO4_SHUTDOWN );
    thermo4_write_byte( ctx, THERMO4_CONFIG_REG_ADDR, THERMO4_POWERUP );
}

float thermo4_read_temperature_c ( thermo4_t *ctx )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result;
    
    result = 0.0;
    
    thermo4_read_data( ctx, THERMO4_TEMP_REG_ADDR, &temp );
    
    buff[ 0 ] = ( uint8_t )( temp >> 5 );
    buff[ 0 ] &= 0x07;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );
    
    if ( buff[ 1 ] > 0x80 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
    }
    return result;
}

float thermo4_read_temperature_f ( thermo4_t *ctx )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result;

    result = 0.0;
    
    thermo4_read_data( ctx, THERMO4_TEMP_REG_ADDR, &temp );
    
    buff[ 0 ] = ( uint8_t )( temp >> 5 );
    buff[ 0 ] &= 0x07;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );

    if (  buff[ 1 ] > 0x80 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
        result = result * 1.8 + 32;
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
        result = result * 1.8 + 32;
    }
    return result;
}

float thermo4_read_temperature_k ( thermo4_t *ctx )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result;

    result = 0.0;
    
    thermo4_read_data( ctx, THERMO4_TEMP_REG_ADDR, &temp );
    
    buff[ 0 ] = ( uint8_t )( temp >> 5 );
    buff[ 0 ] &= 0x07;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );

    if(  buff[ 1 ] > 0x80 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.125 );
    }
    result += 273.15;
    
    return result;
}

float thermo4_read_over_temp_shut_down ( thermo4_t *ctx )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result;

    result = 0.0;
    
    thermo4_read_data( ctx, THERMO4_TOS_REG_ADDR, &temp );
    
    buff[ 0 ] = ( uint8_t )( temp >> 7 );
    buff[ 0 ] &= 0x01;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );

    if ( buff[ 1 ] > 0x79 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.5 );
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.5 );
    }
    return result;
}

float thermo4_read_temp_hyst ( thermo4_t *ctx )
{
    uint16_t temp;
    uint8_t buff[ 2 ];
    float result;

    result = 0.0;
    
    thermo4_read_data( ctx, THERMO4_THYST_REG_ADDR, &temp );
    
    buff[ 0 ] = ( uint8_t )( temp >> 7 );
    buff[ 0 ] &= 0x01;
    buff[ 1 ] = ( uint8_t )( temp >> 8 );

    if (  buff[ 1 ] > 0x80 )
    {
        buff[ 1 ] = ( ~ buff[ 1 ] ) + 1;
        result = ( float )  buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.5 );
        result *= -1.0;
    }
    else
    {
        result = ( float ) buff[ 1 ] + ( ( float ) buff[ 0 ] * 0.5 );
    }
    return result;
}

void thermo4_write_over_temp_shut_down ( thermo4_t *ctx,  float input_val )
{
    uint16_t dec_val;
    uint16_t wr_data;
    
    dec_val = input_val*2;

    if ( dec_val < 0 )
    {
        wr_data = ( ~ dec_val ) + 1;
	    wr_data <<= 7;
	    thermo4_write_data( ctx, THERMO4_TOS_REG_ADDR, wr_data );
    }
    else
    {
        dec_val <<= 7;
	    thermo4_write_data( ctx, THERMO4_TOS_REG_ADDR, dec_val );
    }
}

void thermo4_write_temp_hyst ( thermo4_t *ctx, float input_val )
{
    uint16_t dec_val;
    uint16_t wr_data;
    
    dec_val = input_val * 2;

    if ( dec_val < 0 )
    {
        wr_data = ( ~ dec_val ) + 1;
	    wr_data <<= 7;
	    thermo4_write_data( ctx, THERMO4_THYST_REG_ADDR, wr_data );
    }
    else
    {
        dec_val <<= 7;
	    thermo4_write_data( ctx, THERMO4_THYST_REG_ADDR, dec_val );
    }
}
// ------------------------------------------------------------------------- END

