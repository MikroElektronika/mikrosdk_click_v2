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

#include "temphum11.h"


// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void com_delay ( );
static void conv_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum11_cfg_setup ( temphum11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;


    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM11_DEVICE_SLAVE_ADDR;
}

TEMPHUM11_RETVAL temphum11_init ( temphum11_t *ctx, temphum11_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM11_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return TEMPHUM11_OK;
}

void temphum11_default_cfg ( temphum11_t *ctx )
{
    temphum11_write_config( ctx, TEMPHUM11_NORMAL_OPERATION | TEMPHUM11_HEATER_DISABLED |
                                 TEMPHUM11_TEMP_HUM_ACQUIRED | TEMPHUM11_TEMP_RESOLUTION_14bit |
                                 TEMPHUM11_HUM_RESOLUTION_14bit ); 
}

void temphum11_write_config ( temphum11_t *ctx, uint16_t config )
{
    uint8_t write_reg[ 3 ];
    
    write_reg[ 0 ] = TEMPHUM11_REG_CONFIGURATION;
    write_reg[ 1 ] = ( uint8_t )( config >> 8 );
    write_reg[ 2 ] = ( uint8_t )( config );  

    i2c_master_write( &ctx->i2c, write_reg, 3 );  
}

uint16_t temphum11_read_data ( temphum11_t *ctx, uint8_t reg )
{
    uint8_t write_reg[ 1 ];
    uint8_t read_reg[ 2 ] = { 0 };
    uint16_t read_data = 0;

    write_reg[ 0 ] = reg;

	i2c_master_write( &ctx->i2c, write_reg, 1 );
	com_delay();
	i2c_master_read( &ctx->i2c, read_reg, 2 );

    read_data = read_reg[ 0 ];
    read_data = read_data << 8 ;
    read_data = read_data | read_reg[ 1 ];
    
    return read_data;
}

float temphum11_get_temperature ( temphum11_t *ctx, uint8_t temp_in )
{
    uint16_t temp_out = 0;
    float temperature;
    
    temp_out = temphum11_read_data( ctx, TEMPHUM11_REG_TEMPERATURE );
    temperature = ( float )( temp_out / 65536.0 ) * 165.0 - 40;

    conv_delay( );
    
    if ( temp_in == TEMPHUM11_TEMP_IN_KELVIN )
    {
        temperature = temperature + 273.15;
    }
    else if ( temp_in == TEMPHUM11_TEMP_IN_FAHRENHEIT )
    {
        temperature = ( temperature * 9.0/5.0 ) + 32;
    }
    
    return temperature;
}

float temphum11_get_humidity ( temphum11_t *ctx )
{
    uint16_t hum_out = 0;
    float humidity;

    hum_out = temphum11_read_data( ctx, TEMPHUM11_REG_HUMIDITY );
    humidity = ( float )( hum_out / 65536.0 ) * 100.0;
    
    conv_delay( );
    
    return humidity;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void com_delay ( )
{
    Delay_10ms( );
}

static void conv_delay ( )
{
    Delay_5ms( );
    Delay_1ms( );
    Delay_1ms( );
}


// ------------------------------------------------------------------------- END

