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

#include "vacuum.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void vacuum_read ( vacuum_t *ctx, uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void vacuum_cfg_setup ( vacuum_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
  
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;
}

VACCUM_RETVAL vacuum_init ( vacuum_t *ctx, vacuum_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return VACCUM_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Output pins 

    digital_out_init( &ctx->an, cfg->an );

    return VACCUM_OK;
}

uint16_t vacuum_read_data ( vacuum_t *ctx )
{
    uint8_t read_reg[ 2 ];
    uint16_t read_data;

    vacuum_read( ctx, read_reg, 2 );

    read_data = read_reg[ 0 ];
    read_data = read_data << 8; 
    read_data = read_data | read_reg[ 1 ];  
    
    return read_data;
}

float vacuum_get_voltage ( vacuum_t *ctx )
{
    uint16_t read_data;
    float voltage;

    read_data = vacuum_read_data( ctx );
    voltage = ( read_data * 5.0 ) / 4096.0;
    
    return voltage;
}

float vacuum_get_pressure ( vacuum_t *ctx )
{    
    uint16_t pressure;
    float pressure_mbar;

    pressure = vacuum_read_data( ctx );
    pressure_mbar = ( ( pressure - 2400.0 ) / ( ( 13107.0 ) / 100.0 ) );
    pressure_mbar *= 100.0;// mBar

    return pressure_mbar;
}

float vacuum_get_percentage_of_vacuum ( vacuum_t *ctx )
{    
    float pressure_mbar;
    float vacuum;

    pressure_mbar = vacuum_get_pressure( ctx );
    vacuum = ( ctx->pressure - pressure_mbar ) / 18.0;

    if( vacuum < 1 )
    {
        return 0;
    }
    else if( vacuum > 100 )
    {
        return 100;
    }

    return  vacuum;
}

void vacuum_calibration ( vacuum_t *ctx )
{
    float pressure_m_bar;
    ctx->pressure = vacuum_get_pressure( ctx );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void vacuum_read ( vacuum_t *ctx, uint8_t *data_buf, uint8_t len )
{
    i2c_master_read( &ctx->i2c, data_buf, len );   
}
// ------------------------------------------------------------------------- END

