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

#include "manometer.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void manometer_cfg_setup ( manometer_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = MANOMETER_I2C_ADDRESS;
}

MANOMETER_RETVAL manometer_init ( manometer_t *ctx, manometer_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return MANOMETER_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return MANOMETER_OK;

}

void manometer_generic_write ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void manometer_generic_read ( manometer_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float manometer_get_pressure ( manometer_t *ctx )
{
    uint8_t read_reg[ 4 ];
    uint16_t result = 0x0000;
    float pressure;

    manometer_generic_read( ctx, MANOMETER_OUTPUT_ADDRESS, read_reg, 4 );

    result = read_reg[ 0 ];
    result <<= 8;
    result |= read_reg[ 1 ];

    pressure = ( float ) result;
    pressure = ( pressure - 1638.00 ) * ( ( 4.177 / 13107.00 ) * 1000.00 );
    
    return pressure;
}

float manometer_get_temperature ( manometer_t *ctx )
{
    uint8_t read_reg[ 4 ];
    uint16_t result = 0x0000;
    float temperature;

    manometer_generic_read( ctx, MANOMETER_OUTPUT_ADDRESS, read_reg, 4 );

    result = read_reg[ 2 ] ;
    result <<= 8;
    result |= read_reg[ 3 ];
    result >>= 5;
    result = result & 0x03E0;
     
    temperature = ( float ) result * 200.00;
    temperature = ( temperature / 2047.00 ) - 50.00;

    return temperature;
}

// ------------------------------------------------------------------------- END

