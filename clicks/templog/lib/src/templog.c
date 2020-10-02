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

#include "templog.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void templog_cfg_setup ( templog_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

TEMPLOG_RETVAL templog_init ( templog_t *ctx, templog_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed   = cfg->i2c_speed;
    i2c_cfg.scl     = cfg->scl;
    i2c_cfg.sda     = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->alt, cfg->alt );
    
    return TEMPLOG_OK;
}

void templog_default_cfg ( templog_t *ctx )
{
    templog_generic_write( ctx, TEMP_LOG_CONFIGURATION_NONVOL, 0x0000, TEMP_LOG_16_BITS_DATA );
    templog_generic_write( ctx, TEMP_LOG_TLOW_LIMIT_NONVOL, TEMP_LOG_100_CELSIUS, TEMP_LOG_16_BITS_DATA );
    templog_generic_write( ctx, TEMP_LOG_THIGH_LIMIT_NONVOL, TEMP_LOG_125_CELSIUS, TEMP_LOG_16_BITS_DATA );
}

void templog_generic_write ( templog_t *ctx, uint8_t reg, uint16_t transfer_data, uint8_t len )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = ( transfer_data >> 8 );
    tx_buf[ 2 ] = ( transfer_data & 0x00FF );

    i2c_master_write( &ctx->i2c, tx_buf, 3 );  
}

uint16_t templog_generic_read ( templog_t *ctx, uint8_t reg )
{
    uint8_t data_buf[ 2 ];
    uint8_t tx_buf[ 1 ];
    uint16_t register_data = 0;
    
    tx_buf [ 0 ] = reg;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_buf, 2 );

    //AD converting
    register_data = data_buf[ 0 ];
    register_data <<= 8;
    register_data |= data_buf[ 1 ];

    return register_data;
}

uint16_t temp_log_read_temp_dec ( templog_t *ctx, uint16_t resolution )
{
    templog_generic_write(ctx, TEMP_LOG_CONFIGURATION, resolution, TEMP_LOG_8_BITS_DATA );
    
    return templog_generic_read(ctx, TEMP_LOG_TEMPERATURE );
}

float temp_log_convert_to_celsius ( uint16_t temperature_data )
{
    if ( ( temperature_data & 0x8000 ) == 0 )
    {
        return ( float )temperature_data / 256.0;
    }
    else
    {
        temperature_data = ~temperature_data;
        return ( 0.0 - ( float )temperature_data )/256.0;
    }
}

uint8_t temp_log_get_alert ( templog_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

// ------------------------------------------------------------------------- END

