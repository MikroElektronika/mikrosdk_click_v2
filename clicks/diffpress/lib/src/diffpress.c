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

#include "diffpress.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void diffpress_cfg_setup ( diffpress_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = DIFFPRESS_DEVICE_ADDRESS;
}

DIFFPRESS_RETVAL diffpress_init ( diffpress_t *ctx, diffpress_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return DIFFPRESS_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_speed( &ctx->i2c, 0 );

    return DIFFPRESS_OK;
}

uint16_t diffpress_get_adc_data( diffpress_t *ctx )
{
    uint16_t adc_data;
    uint8_t read_buffer[ 2 ];
    
    i2c_master_read( &ctx->i2c, read_buffer, 2 );

    adc_data = read_buffer[ 0 ];
    adc_data <<= 8;
    adc_data |= read_buffer[ 1 ];
    
    return adc_data;
}

float diffpress_get_pressure_difference( diffpress_t *ctx )
{
    float pressure_difference;
    uint16_t adc_data;
    
    adc_data = diffpress_get_adc_data( ctx );
    
    pressure_difference = ( float )adc_data - 2048.0;
    pressure_difference /= 2048.0;
    pressure_difference *= 3.5;
    
    return pressure_difference;
}


// ------------------------------------------------------------------------- END

