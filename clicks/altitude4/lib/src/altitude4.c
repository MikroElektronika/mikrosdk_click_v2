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

#include "altitude4.h"
#include "math.h"

// ------------------------------------------------ PRIVATE FUNCTION DECLARATIONS


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void altitude4_cfg_setup ( altitude4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = ALTITUDE4_SLAVE_ADDRESS;
}

ALTITUDE4_RETVAL altitude4_init ( altitude4_t *ctx, altitude4_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return ALTITUDE4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return ALTITUDE4_OK;
}

void altitude4_generic_read ( altitude4_t *ctx, uint8_t reg, uint8_t *r_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, r_buf, len );
}

void altitude4_generic_write ( altitude4_t *ctx, uint8_t reg, uint8_t *w_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = w_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

uint8_t altitude4_read_sensor ( altitude4_t *ctx, altitude4_sensor_t *sensor_data )
{
    uint8_t r_buf[ 5 ] = { 0 };
    uint16_t temp_data;
    float temp_holder;
    float pressure;
    float temp;
    float altitude;

    altitude4_generic_read( ctx, ALTITUDE4_SENS_DATA, r_buf, 5 );

//-------------------------------------------------pressure
    temp_data = r_buf[ 1 ];
    temp_data <<= 8;
    temp_data |= r_buf[ 2 ];
    
    temp_holder = temp_data;
    temp_holder /= 65535;
    temp_holder *= 1000;;
    temp_holder += 260;
    pressure = temp_holder;

//-------------------------------------------------temp
    temp_data = r_buf[ 3 ];
    temp_data <<= 8;
    temp_data |= r_buf[ 4 ];

    temp_holder = temp_data;
    temp_holder /= 65535;
    temp_holder *= 125;;
    temp_holder -= 40;
    temp = temp_holder;

//-------------------------------------------------altitude
    temp_holder = 1013.25 / pressure;
    altitude = pow( temp_holder, 0.19022256 );
    altitude -= 1;
    temp_holder = temp + 273.15;
    altitude *= temp_holder;
    altitude /= 0.0065;

    sensor_data->altitude = altitude;
    sensor_data->pressure = pressure;
    sensor_data->temperature = temp;

    return r_buf[ 0 ];
}

// ------------------------------------------------ PRIVATE FUNCTION DEFINITIONS



// ------------------------------------------------------------------------- END

