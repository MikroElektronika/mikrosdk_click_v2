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

#include "thermok.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermok_cfg_setup ( thermok_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->al4   = HAL_PIN_NC;
    cfg->al3 = HAL_PIN_NC;
    cfg->al2 = HAL_PIN_NC;
    cfg->al1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMOK_DEVICE_SLAVE_ADDR_0;
}

THERMOK_RETVAL thermok_init ( thermok_t *ctx, thermok_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMOK_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );
    i2c_master_set_timeout( &ctx->i2c, 0 );

    // Input pins

    digital_in_init( &ctx->al4, cfg->al4 );
    digital_in_init( &ctx->al3, cfg->al3 );
    digital_in_init( &ctx->al2, cfg->al2 );
    digital_in_init( &ctx->al1, cfg->al1 );
    
    return THERMOK_OK;
}

void thermok_generic_write ( thermok_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermok_generic_read ( thermok_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write( &ctx->i2c, &reg, 1 );
    Delay_50us();
    i2c_master_read( &ctx->i2c, data_buf, len );
}

uint16_t thermok_get_device_info ( thermok_t *ctx )
{
    uint16_t device_info;
    uint8_t rx_data[ 2 ];

    thermok_generic_read( ctx, THERMOK_REG_DEVICE_ID, rx_data, 2 );
    device_info = rx_data[ 0 ];
    device_info <<= 8;
    device_info |= rx_data[ 1 ];

    return device_info;
}

void thermok_get_status ( thermok_t *ctx, thermok_alert_t *status )
{
    uint8_t rx_data;

    thermok_generic_read( ctx, THERMOK_REG_STATUS, &rx_data, 1 );

    status->burst_cmp     = ( rx_data & 0x80 ) >> 7;
    status->temp_h_update = ( rx_data & 0x40 ) >> 6;
    status->over_volt     = ( rx_data & 0x10 ) >> 4;
    status->alert_4       = ( rx_data & 0x08 ) >> 3;
    status->alert_3       = ( rx_data & 0x04 ) >> 2;
    status->alert_2       = ( rx_data & 0x02 ) >> 1;
    status->alert_1       = ( rx_data & 0x01 );

}

float thermok_get_temperature ( thermok_t *ctx, uint8_t reg, uint8_t temp_format )
{
    float temperature;

    uint8_t rx_data[ 2 ];

    thermok_generic_read( ctx, reg, rx_data, 2 );

    if ( ( rx_data[ 0 ] & 0x80 ) == 0x80 )
    {
        rx_data[ 0 ] = rx_data[ 0 ] & 0x7F;

        temperature = 1024.0;
        temperature -= ( ( float )rx_data[ 0 ] ) * 16;
        temperature -= ( ( float )rx_data[ 1 ] ) / 16;
    }
    else
    {
        temperature = ( ( float )rx_data[ 0 ] ) * 16;
        temperature += ( ( float )rx_data[ 1 ] ) / 16;
    }

    if ( temp_format == THERMOK_TEMP_IN_KELVIN )
    {
        temperature = temperature + 273.15;
    }
    else if ( temp_format == THERMOK_TEMP_IN_FAHRENHEIT )
    {
        temperature = ( temperature * 9.0/5.0 ) + 32;
    }

    return temperature;
}

uint8_t thermok_get_alert_state_1 ( thermok_t *ctx )
{
    return digital_in_read( &ctx->al1 );
}

uint8_t thermok_get_alert_state_2 ( thermok_t *ctx )
{
    return digital_in_read( &ctx->al2 );
}

uint8_t thermok_get_alert_state_3 ( thermok_t *ctx )
{
    return digital_in_read( &ctx->al3 );
}

uint8_t thermok_get_alert_state_4 ( thermok_t *ctx )
{
    return digital_in_read( &ctx->al4 );
}

void thermok_set_register_cfg ( thermok_t *ctx, uint8_t reg_cfg, uint8_t cfg_data )
{
    thermok_generic_write( ctx, reg_cfg, &cfg_data, 1 );
}

// ------------------------------------------------------------------------- END

