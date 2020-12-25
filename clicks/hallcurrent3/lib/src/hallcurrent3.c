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

#include "hallcurrent3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallcurrent3_cfg_setup ( hallcurrent3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x4D;
}

HALLCURRENT3_RETVAL hallcurrent3_init ( hallcurrent3_t *ctx, hallcurrent3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HALLCURRENT3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return HALLCURRENT3_OK;
}

void hallcurrent3_generic_read ( hallcurrent3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t hallcurrent3_read_data ( hallcurrent3_t *ctx, uint8_t reg )
{
    uint8_t read_buf[ 2 ];
    uint16_t read_data;
    
    hallcurrent3_generic_read( ctx, reg, read_buf, 2 );

    read_data = read_buf[ 0 ];
    read_data = read_data << 8;
    read_data = read_data | read_buf[ 1 ];
    
    return read_data;
}

float hallcurrent3_get_current( hallcurrent3_t *ctx )
{
    float voltage;
    double sum_current = 0.0;
    uint16_t read_data;
    uint8_t cnt = 10;
    uint8_t flag = 0;
    
    while ( cnt > 0 )
    {
        read_data = hallcurrent3_read_data( ctx, 0x00 );

        if ( read_data < 2048 )
        {
            voltage = 2048 - read_data;
            flag = 1;
        }
        else
        {
            voltage = read_data - 2048;
        }
        voltage = voltage * ( float )( 5000 / 4095 ); // 5V / 12bit resolution
        voltage = ( voltage * 1000 ) / 65.57; // 65.57 -> nominal 80mV/A or 25A full scale
        sum_current += voltage;
        cnt--;
    }

    sum_current = ( sum_current - 100 ) / 10.0;
    sum_current = sum_current;
    
    if ( flag == 1 )
    {
        return ( -sum_current );
    }
   
    return sum_current;
}

// ------------------------------------------------------------------------- END

