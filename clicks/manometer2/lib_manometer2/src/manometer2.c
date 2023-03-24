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

#include "manometer2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MANOMETER2_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void manometer2_initialization ( manometer2_t *ctx, manometer2_coef_t *coef );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void manometer2_cfg_setup ( manometer2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MANOMETER2_I2C_ADDRESS_0;
}

MANOMETER2_RETVAL manometer2_init ( manometer2_t *ctx, manometer2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl      = cfg->scl;
    i2c_cfg.sda      = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MANOMETER2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_high( &ctx->cs );

    return MANOMETER2_OK;
}

void manometer2_write_data ( manometer2_t *ctx, uint8_t reg_address, uint8_t write_command )
{
    uint8_t buffer[ 2 ];
    buffer[ 0 ]= reg_address;
    buffer[ 1 ] = write_command;

    i2c_master_write( &ctx->i2c, buffer, 2 );
}

uint16_t manometer2_read_data ( manometer2_t *ctx, uint8_t reg_address )
{
    uint8_t read_reg[ 2 ];
    uint16_t result = 0x0000;

    i2c_master_write( &ctx->i2c, &reg_address, 1 );

    i2c_master_read( &ctx->i2c, read_reg, 2 );

    result = read_reg[ 0 ];
    result <<= 8;
    result |= read_reg[ 1 ];

    return result;
}

uint32_t manometer2_read_command ( manometer2_t *ctx, uint8_t reg_address )
{
    uint8_t command;
    uint8_t read_reg[ 3 ];
    uint32_t result = 0x00000000;

    command = MANOMETER2_ADC_READ;
    
    i2c_master_write( &ctx->i2c, &reg_address, 1 );
    Delay_10ms( );

    i2c_master_write( &ctx->i2c, &command, 1 );
    Delay_10ms( );

    i2c_master_read( &ctx->i2c, read_reg, 3 );

    result = read_reg[ 0 ];
    result <<= 8;
    result |= read_reg[ 1 ];
    result <<= 8;
    result |= read_reg[ 2 ];

    return result;
}

void manometer2_reset ( manometer2_t *ctx )
{
    uint8_t cmd;
    cmd = MANOMETER2_RESET;

    i2c_master_write( &ctx->i2c, &cmd, 1 );
}

void manometer2_read_coef ( manometer2_t *ctx )
{
    uint8_t cmd;
    cmd = MANOMETER2_RESET;

    i2c_master_write( &ctx->i2c, &cmd, 1 );   
    Delay_10ms( );

    manometer2_initialization( ctx, &ctx->coef );
}

float manometer2_get_temperature ( manometer2_t *ctx, uint8_t oversampling_ratio )
{
    uint8_t temperature_command;
    uint32_t d2temp;
    int32_t dtbuff;
    int32_t temperature;
    float result;

    switch ( oversampling_ratio )
    {
        case MANOMETER2_CONVERT_256:
        {
            temperature_command = MANOMETER2_D2_CONVERT_256;
            break;
        }
        case MANOMETER2_CONVERT_512:
        {
            temperature_command = MANOMETER2_D2_CONVERT_512;
            break;
        }
        case MANOMETER2_CONVERT_1024:
        {
            temperature_command = MANOMETER2_D2_CONVERT_1024;
            break;
        }
        case MANOMETER2_CONVERT_2048:
        {
            temperature_command = MANOMETER2_D2_CONVERT_2048;
            break;
        }
        case MANOMETER2_CONVERT_4096:
        {
            temperature_command = MANOMETER2_D2_CONVERT_4096;
            break;
        }
    }
    
    d2temp = manometer2_read_command( ctx, temperature_command );

    dtbuff = ( int32_t ) d2temp - ( ( ( int32_t ) ctx->coef.coef5 ) << 7 );
    
    dtbuff = dtbuff >> 9;
    temperature = 2000 + ( ( ( int32_t ) dtbuff * ctx->coef.coef6 ) >> ( MANOMETER2_Q6 - 9 ) );

    result = ( float ) temperature / 100;

    return result;
}

float manometer2_get_pressure ( manometer2_t *ctx, uint8_t oversampling_ratio )
{
    uint8_t pressure_command;
    uint8_t temperature_command;
    uint32_t d1press;
    uint32_t d2temp;
    int32_t dtbuff;
    int32_t pressure;

    int32_t off;
    int32_t sens;

    float result;

    switch ( oversampling_ratio )
    {
        case MANOMETER2_CONVERT_256:
        {
            pressure_command = MANOMETER2_D1_CONVERT_256;
            temperature_command = MANOMETER2_D2_CONVERT_256;
            break;
        }
        case MANOMETER2_CONVERT_512:
        {
            pressure_command = MANOMETER2_D1_CONVERT_512;
            temperature_command = MANOMETER2_D2_CONVERT_512;
            break;
        }
        case MANOMETER2_CONVERT_1024:
        {
            pressure_command = MANOMETER2_D1_CONVERT_1024;
            temperature_command = MANOMETER2_D2_CONVERT_1024;
            break;
        }
        case MANOMETER2_CONVERT_2048:
        {
            pressure_command = MANOMETER2_D1_CONVERT_2048;
            temperature_command = MANOMETER2_D2_CONVERT_2048;
            break;
        }
        case MANOMETER2_CONVERT_4096:
        {
            pressure_command = MANOMETER2_D1_CONVERT_4096;
            temperature_command = MANOMETER2_D2_CONVERT_4096;
            break;
        }
    }

    d1press = manometer2_read_command( ctx, pressure_command );
    
    d2temp = manometer2_read_command( ctx, temperature_command );
    
    dtbuff = ( int32_t ) d2temp - ( ( ( int32_t ) ctx->coef.coef5 ) << MANOMETER2_Q5 );
    
    dtbuff = dtbuff >> 10;
    
    off = ( ( int32_t ) ctx->coef.coef2 << ( MANOMETER2_Q2 - 10 ) ) + 
          ( ( dtbuff * ( int32_t ) ctx->coef.coef4 ) >> MANOMETER2_Q4 );
          
    sens = ( ( int32_t ) ctx->coef.coef1 << ( MANOMETER2_Q1 - 10 ) ) + 
           ( ( dtbuff * ( int32_t ) ctx->coef.coef3 ) >> MANOMETER2_Q3 );

    d1press = d1press >> 9;
    sens = sens >> 10;
    pressure = d1press * sens;
    pressure = pressure >> 2;
    pressure = pressure - off;
    pressure = pressure >> 5;

    result = ( float ) pressure / 10000;
    return  result;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void manometer2_initialization ( manometer2_t *ctx, manometer2_coef_t *coef )
{
    coef->coef1 = manometer2_read_data( ctx, MANOMETER2_C1_READ );
    Delay_10ms( );

    coef->coef2 = manometer2_read_data( ctx, MANOMETER2_C2_READ );
    Delay_10ms( );

    coef->coef3 = manometer2_read_data( ctx, MANOMETER2_C3_READ );
    Delay_10ms( );

    coef->coef4 = manometer2_read_data( ctx, MANOMETER2_C4_READ );
    Delay_10ms( );

    coef->coef5 = manometer2_read_data( ctx, MANOMETER2_C5_READ );
    Delay_10ms( );

    coef->coef6 = manometer2_read_data( ctx, MANOMETER2_C6_READ );
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

