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

err_t temphum9_init ( temphum9_t *ctx, temphum9_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    return TEMPHUM9_OK;
}

void temphum9_read_register ( temphum9_t *ctx, uint16_t address, uint8_t num_data, uint16_t *data_out )
{
    uint8_t write_buffer[ 2 ] = { 0 };
    uint8_t read_buffer[ 6 ] = { 0 };
    
    write_buffer[ 0 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    write_buffer[ 1 ] = ( uint8_t ) ( address & 0xFF );

    i2c_master_write ( &ctx->i2c, write_buffer, 2 );
    Delay_10ms ( );
    i2c_master_read ( &ctx->i2c, read_buffer, num_data );

    if ( TEMPHUM9_SINGLE_DATA == num_data )
    {
        data_out[ 0 ] = ( uint16_t ) read_buffer[ 0 ];
        data_out[ 0 ] <<= 8;
        data_out[ 0 ] |= ( uint16_t ) read_buffer[ 1 ];
    }
    else if ( TEMPHUM9_DUAL_DATA == num_data )
    {
        data_out[ 0 ] = ( uint16_t ) read_buffer[ 0 ];
        data_out[ 0 ] <<= 8;
        data_out[ 0 ] |= ( uint16_t ) read_buffer[ 1 ];
        
        data_out[ 1 ] = ( uint16_t ) read_buffer[ 3 ];
        data_out[ 1 ] <<= 8;
        data_out[ 1 ] |= ( uint16_t ) read_buffer[ 4] ;
    }
}

void temphum9_send_command ( temphum9_t *ctx, uint16_t command )
{
    uint8_t write_buffer[ 2 ] = { 0 };

    write_buffer[ 0 ] = ( uint8_t ) ( ( command >> 8 ) & 0xFF );
    write_buffer[ 1 ] = ( uint8_t ) ( command & 0xFF );

    i2c_master_write( &ctx->i2c, write_buffer, 2 );
    Delay_10ms ( );
}

float temphum9_get_temperature ( temphum9_t *ctx, uint8_t data_mode )
{
    float temperature = 0;
    uint16_t reg_data = 0;

    if ( TEMPHUM9_NORMAL_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x7CA2, TEMPHUM9_SINGLE_DATA, &reg_data );
    }
    else if ( TEMPHUM9_LOW_POWER_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x6458, TEMPHUM9_SINGLE_DATA, &reg_data );
    }

    temperature = ( float ) reg_data;
    temperature *= 175;
    temperature /= 65536;
    temperature -= 45;
    
    return temperature;
}

float temphum9_get_humidity ( temphum9_t *ctx, uint8_t data_mode )
{
    float relative_humidity = 0;
    uint16_t reg_data = 0;

    if ( TEMPHUM9_NORMAL_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x5C24, TEMPHUM9_SINGLE_DATA, &reg_data );
    }
    else if ( TEMPHUM9_LOW_POWER_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x44DE, TEMPHUM9_SINGLE_DATA, &reg_data );
    }

    relative_humidity = ( float ) reg_data;
    relative_humidity *= 100;
    relative_humidity /= 65536;

    return relative_humidity;
}

void temhum9_get_data ( temphum9_t *ctx, uint8_t data_mode, float *temp, float *hum )
{
    uint16_t reg_data[ 2 ] = { 0 };
    
    if ( TEMPHUM9_NORMAL_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x7CA2, TEMPHUM9_DUAL_DATA, reg_data );
    }
    else if ( TEMPHUM9_LOW_POWER_MODE == data_mode )
    {
        temphum9_read_register ( ctx, 0x6458, TEMPHUM9_DUAL_DATA, reg_data );
    }
    
    *temp = ( float ) reg_data[ 0 ];
    *temp *= 175;
    *temp /= 65536;
    *temp -= 45;

    *hum = ( float ) reg_data[ 1 ];
    *hum *= 100;
    *hum /= 65536;
}

// ------------------------------------------------------------------------- END

