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

#include "temphum5.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum5_cfg_setup ( temphum5_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->all = HAL_PIN_NC;
    cfg->alh = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPHUM5_DEVICE_SLAVE_ADDRESS;

    cfg->dev_temperature = 0;
    cfg->dev_humidity = 0;
}

TEMPHUM5_RETVAL temphum5_init ( temphum5_t *ctx, temphum5_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM5_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->all, cfg->all );
    digital_in_init( &ctx->alh, cfg->alh );
    
    return TEMPHUM5_OK;
}

void temphum5_generic_write ( temphum5_t *ctx, uint8_t cmd )
{
    uint8_t tmp = cmd;

    i2c_master_write( &ctx->i2c, &tmp, 1 );   
}

void temphum5_generic_read ( temphum5_t *ctx, uint8_t *data_out )
{
    i2c_master_read( &ctx->i2c, data_out, 4 );
}

uint8_t temphum5_start_measurement ( temphum5_t *ctx )
{
    uint8_t read_reg[ 4 ];
    uint8_t status;
    
    temphum5_generic_write( ctx, 0x00 );
    Delay_100ms( );
    temphum5_generic_read( ctx, read_reg );

    ctx->humidity = read_reg[ 0 ];
    ctx->humidity <<= 8;
    ctx->humidity |= read_reg[ 1 ];
    ctx->humidity = ctx->humidity & 0x3FFF;

    ctx->temperature = read_reg[ 2 ];
    ctx->temperature <<= 8;
    ctx->temperature |= read_reg[ 3 ];
    ctx->temperature = ( ctx->temperature >> 2 ) & 0x3FFF;
    
    status = ( read_reg[ 0 ] & 0x3F ) >> 6;
    
    if ( status == TEMPHUM5_STATUS_STALE_DATA )
    {
        return TEMPHUM5_STATUS_STALE_DATA;
    }
    else if ( status == TEMPHUM5_STATUS_COMMAND_MODE )
    {
        return TEMPHUM5_STATUS_COMMAND_MODE;
    }
    return TEMPHUM5_STATUS_NORMAL_OPERATION;
}

float temphum5_get_temperature ( temphum5_t *ctx, uint8_t temp_in )
{
    float temp;
    
    temp = ( float ) ( ctx->temperature / 16382.0 ) * 165.0 - 40;
    
    if ( temp_in == TEMPHUM5_TEMP_DATA_IN_KELVIN )
    {
        return temp + 273.15;
    }
    else if ( temp_in == TEMPHUM5_TEMP_DATA_IN_FAHRENHEIT )
    {
        return ( temp * 9.0/5.0 ) + 32;
    }
    return temp;
}

float temphum5_get_humidity ( temphum5_t *ctx )
{
    float hum;
    
    hum = ( float ) ( ctx->humidity / 16382.0 ) * 100.0;
    return hum;
}

uint8_t temphum5_get_alarm ( temphum5_t *ctx, uint8_t alarm )
{
    if ( alarm == TEMPHUM5_ALARM_OUTPUT_HIGH )
    {
        return digital_in_read( &ctx->alh );
    }
    else
    {
        return digital_in_read( &ctx->all );
    }
}

// ------------------------------------------------------------------------- END

