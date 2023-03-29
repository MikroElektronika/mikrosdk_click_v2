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

#include "temphum10.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void temphum10_cfg_setup ( temphum10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->cs  = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL; 
    cfg->i2c_address = 0x7F;
}

TEMPHUM10_RETVAL temphum10_init ( temphum10_t *ctx, temphum10_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;
    
    // Output pins 

    digital_out_init( &ctx->cs, cfg->cs );
    
    digital_out_low( &ctx->cs );
    Delay_100ms( );

    // I2C config
    
    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPHUM10_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );
    
    return TEMPHUM10_OK;
}

void temphum10_generic_write ( temphum10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void temphum10_generic_read ( temphum10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );  
    Delay_1ms( );
}

float temphum10_get_humidity ( temphum10_t *ctx )
{
    uint8_t hum_msb;
    uint8_t hum_lsb;
    uint16_t read_data;
    float humidity;
    
    temphum10_generic_read( ctx, TEMPHUM10_REG_HUMIDITY_LSB, &hum_lsb, 1 );
    temphum10_generic_read( ctx, TEMPHUM10_REG_HUMIDITY_MSB, &hum_msb, 1 );
    
    read_data = ( hum_msb & 0x03 );
    read_data = read_data << 8;
    read_data = read_data | hum_lsb;
    
    humidity = ( float ) ( ( 100.0/1024.0 ) * read_data );
    return humidity;
}

float temphum10_get_temperature ( temphum10_t *ctx )
{
    uint8_t temp_msb;
    uint8_t temp_lsb;
    uint16_t read_data;
    float temperature;

    temphum10_generic_read( ctx, TEMPHUM10_REG_TEMPERATURE_MSB, &temp_msb, 1 );
    temphum10_generic_read( ctx, TEMPHUM10_REG_TEMPERATURE_LSB, &temp_lsb, 1 );

    read_data = ( temp_msb & 0x07 );
    read_data = read_data << 8;
    read_data = read_data | temp_lsb;
    
    temperature = ( float ) ( read_data - 774.0 ) * 0.1;
    return temperature;
}

void temphum10_set_device_mode ( temphum10_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->cs, mode );
}

void temphum10_repeat_measurement ( temphum10_t *ctx, uint8_t average )
{
    uint8_t tmp;
    tmp = average | TEMPHUM10_AM_MANUAL_MODE_DETECTION_OP_START;
    temphum10_generic_write( ctx, TEMPHUM10_REG_AVERAGE_MODE, &tmp, 1 );
    while ( (tmp & 0x01) == 0x01 ){
        temphum10_generic_read( ctx, TEMPHUM10_REG_AVERAGE_MODE, &tmp, 1 );
        Delay_10ms( );
    }
}

// ------------------------------------------------------------------------- END

