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

#include "hallcurrent4.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void hallcurrent4_cfg_setup ( hallcurrent4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = HALLCURRENT4_DEVICE_SLAVE_ADDRESS;
}

HALLCURRENT4_RETVAL hallcurrent4_init ( hallcurrent4_t *ctx, hallcurrent4_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return HALLCURRENT4_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return HALLCURRENT4_OK;
}

void hallcurrent4_generic_write ( hallcurrent4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void hallcurrent4_generic_read ( hallcurrent4_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint16_t hallcurrent4_get_raw_data( hallcurrent4_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t rx_data;

    hallcurrent4_generic_read( ctx, 0x00, rx_buf, 2 );

    rx_data = rx_buf[ 0 ];
    rx_data <<= 8;
    rx_data |= rx_buf[ 1 ];
    rx_data = rx_data & 0x0FFF;

    return rx_data;
}


float hallcurrent4_get_current_data( hallcurrent4_t *ctx )
{
    float current;
    float voltage;
    uint16_t sensor_value;
    uint8_t f_pol = 1;

    sensor_value = hallcurrent4_get_raw_data( ctx );

    if ( sensor_value < 1840 )
    {
        sensor_value = 1840 - sensor_value;
        f_pol = 1;
    }
    else
    {
        sensor_value -= 1840;
        f_pol = 0;
    }

    voltage = ( sensor_value / 4095.0 ) * 3300; // Vref 3V3
    current  = ( voltage / 200 ) * 1000;  // Sensitivity 200mV/A

    if ( f_pol == 1 )
    {
        current = -current;
    }
    return current;
}

// ------------------------------------------------------------------------- END

