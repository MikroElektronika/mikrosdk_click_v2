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

#include "temphum9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum9_cfg_setup ( temphum9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM9_DEVICE_ADDRESS;
}

TEMPHUM9_RETVAL temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    return TEMPHUM9_OK;
}


void temphum9_read_register ( temphum9_t *ctx, uint16_t register_address, uint8_t n_data, uint16_t *register_buffer )
{
    uint8_t write_buffer[ 2 ];
    uint8_t read_buffer[ 6 ];
    
    write_buffer[ 0 ] = register_address  >> 8;
    write_buffer[ 1 ] = register_address ;


    i2c_master_write_then_read ( &ctx->i2c, write_buffer, 2, read_buffer, n_data );  

    if (n_data  ==  TEMPHUM9_SINGLE_DATA)
    {
        register_buffer[ 0 ] = ( uint16_t ) read_buffer[ 0 ];
        register_buffer[ 0 ] <<= 8;
        register_buffer[ 0 ] |= ( uint16_t ) read_buffer[ 1 ];
    }
    else if (n_data == TEMPHUM9_DUAL_DATA)
    {
        register_buffer[ 0 ] = ( uint16_t ) read_buffer[ 0 ];
        register_buffer[ 0 ] <<= 8;
        register_buffer[ 0 ] |= ( uint16_t ) read_buffer[ 1 ];
        
        register_buffer[ 1 ] = ( uint16_t ) read_buffer[ 3 ];
        register_buffer[ 1 ] <<= 8;
        register_buffer[ 1 ] |= ( uint16_t ) read_buffer[ 4] ;
    }
}

void temphum9_send_command ( temphum9_t *ctx, uint16_t command )
{
    uint8_t write_buffer[2];

    write_buffer[0] = command >> 8;
    write_buffer[1] = command;

    i2c_master_write( &ctx->i2c, write_buffer, 2 );  
}

float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode )
{
    float temperature;
    uint16_t register_buffer[ 1 ];

    if ( data_mode  == TEMPHUM9_NORMAL_MODE )
    {
        temphum9_read_register ( ctx, 0x7CA2,  TEMPHUM9_SINGLE_DATA, register_buffer );
    }
    else if ( data_mode == TEMPHUM9_LOW_POWER_MODE )
    {
        temphum9_read_register ( ctx, 0x6458, TEMPHUM9_SINGLE_DATA, register_buffer );
    }

    temperature  = ( float ) register_buffer[ 0 ];
    temperature  *= 175;
    temperature  /= 65536;
    temperature  -= 45;
    
    return temperature ;
}

float temphum9_get_relative_humidity ( temphum9_t *ctx, uint8_t data_mode )
{
    float relative_humidity ;
    uint16_t register_buffer[ 1 ];

    if ( data_mode ==  TEMPHUM9_NORMAL_MODE )
    {
        temphum9_read_register ( ctx, 0x5C24, TEMPHUM9_SINGLE_DATA, register_buffer );
    }
    else if (data_mode  ==  TEMPHUM9_LOW_POWER_MODE )
    {
        temphum9_read_register ( ctx, 0x44DE,  TEMPHUM9_SINGLE_DATA, register_buffer );
    }

    relative_humidity  = ( float ) register_buffer[ 0 ]  ;
    relative_humidity  *= 100;
    relative_humidity  /= 65536;

    return relative_humidity ;
}

void temhum9_get_temperature_and_humidity ( temphum9_t *ctx,  uint8_t data_mode , float *measurement_data )
{
    uint16_t register_buffer[ 2 ];
    
    if ( data_mode  ==  TEMPHUM9_NORMAL_MODE )
    {
        temphum9_read_register ( ctx, 0x7CA2,  TEMPHUM9_DUAL_DATA, register_buffer );
    }
    else if ( data_mode  ==  TEMPHUM9_LOW_POWER_MODE )
    {
        temphum9_read_register ( ctx, 0x6458, TEMPHUM9_DUAL_DATA, register_buffer );
    }
    
    measurement_data[ 0 ] = ( float ) register_buffer [ 0 ];
    measurement_data[ 0 ] *= 175;
    measurement_data[ 0 ] /= 65536;
    measurement_data[ 0 ] -= 45;

    measurement_data[ 1 ] = ( float ) register_buffer [ 1 ];
    measurement_data[ 1 ] *= 100;
    measurement_data[ 1 ] /= 65536;
}

// ------------------------------------------------------------------------- END

