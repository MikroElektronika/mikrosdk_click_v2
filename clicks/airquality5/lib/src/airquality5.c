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

#include "airquality5.h"
#include <math.h>

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void airquality5_cfg_setup ( airquality5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rdy = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

AIRQUALITY5_RETVAL airquality5_init ( airquality5_t *ctx, airquality5_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AIRQUALITY5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );
    
    return AIRQUALITY5_OK;
}

void airquality5_default_cfg ( airquality5_t *ctx )
{
    airq5_set_configuration( ctx, AIRQ5_CONFIG_OS_SINGLE |
                            AIRQ5_CONFIG_PGA_2_048V |
                            AIRQ5_CONFIG_SINGLE_MODE |
                            AIRQ5_CONFIG_DATA_RATE_1600SPS |
                            AIRQ5_CONFIG_COMP_MODE_TRADITIONAL |
                            AIRQ5_CONFIG_COMP_POL_ACTIVE_LOW |
                            AIRQ5_CONFIG_COMP_LAT_NOT_LATCH |
                            AIRQ5_CONFIG_COMP_QUE_0CONV );
}

void airquality5_generic_write ( airquality5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void airquality5_generic_read ( airquality5_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void airq5_write_data ( airquality5_t *ctx, uint8_t reg, uint16_t data_b )
{
    uint8_t write_reg[ 3 ];

    write_reg[ 0 ] = data_b >> 8;
    write_reg[ 1 ] = data_b & 0x00FF;

    airquality5_generic_write( ctx, reg, write_reg, 2 );
}

uint16_t airq5_read_data ( airquality5_t *ctx, uint8_t reg )
{
    uint8_t read_reg[ 2 ];
    uint16_t data_value;

    airquality5_generic_read( ctx, reg, read_reg, 1 );

    data_value = read_reg[ 0 ];
    data_value = data_value << 8;
    data_value = data_value | read_reg[ 1 ];

    return data_value;
}

void airq5_set_configuration ( airquality5_t *ctx, uint16_t config )
{
    ctx->data_config = config;
}

uint16_t airq5_read_sensor_data( airquality5_t *ctx, uint16_t channel_data )
{
    uint16_t set_config;
    uint16_t get_data;
   
    set_config = ctx->data_config;
    set_config = set_config | channel_data;
    
    while ( airq5_get_interrupt ( ctx ) != 1 );
    
    airq5_write_data( ctx, AIRQ5_REG_POINTER_CONFIG, set_config );
    get_data = airq5_read_data( ctx, AIRQ5_REG_POINTER_CONVERT );
    
    get_data = get_data >> 4;

    return get_data;
}

uint8_t airq5_get_interrupt ( airquality5_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

// ------------------------------------------------------------------------- END

