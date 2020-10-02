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

#include "thermo15.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_conversion_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo15_cfg_setup ( thermo15_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = THERMO15_DEVICE_SLAVE_ADDR_000;
}

THERMO15_RETVAL thermo15_init ( thermo15_t *ctx, thermo15_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed = cfg->i2c_speed;
    i2c_cfg.scl   = cfg->scl;
    i2c_cfg.sda   = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO15_INIT_ERROR;
    }
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->alt, cfg->alt );

    return THERMO15_OK;
}

void thermo15_default_cfg ( thermo15_t *ctx )
{
    uint8_t reg_cfg;

    // Click default configuration

    reg_cfg = THERMO15_CFG_WMODE_NORMAL | THERMO15_CFG_FAULT_QUEUE_1 |
              THERMO15_CFG_ALERT_ACTIVE_HIGH | THERMO15_CFG_TMODE_COMPARATOR;

    thermo15_generic_write( ctx, THERMO15_REG_CONFIGURATION, &reg_cfg, 1 );
}

void thermo15_generic_write ( thermo15_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len )
{
    uint8_t tx_buffer[ 256 ];
    uint8_t cnt;

    tx_buffer[ 0 ] = reg;

    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buffer[ cnt ] = data_buffer[ cnt - 1 ];
    }

    i2c_master_write( &ctx->i2c, tx_buffer, len + 1 );
}

void thermo15_generic_read ( thermo15_t *ctx, uint8_t reg, uint8_t *data_buffer, uint8_t len )
{    
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buffer, len );
}

float thermo15_get_temperature_data ( thermo15_t *ctx,  uint8_t temp_format )
{
    uint16_t raw_temp;
    float temperature;
    uint8_t rx_buffer[ 2 ];

    thermo15_generic_read( ctx, THERMO15_REG_STORED_TEMPERATURE, rx_buffer, 2 );
    raw_temp = rx_buffer[ 0 ];
    raw_temp <<= 8;
    raw_temp |= rx_buffer[ 1 ];
    raw_temp >>= 4;

    if (raw_temp > 0x1000)
    {
        temperature = (float)((raw_temp - 4096) / 16.0);
    }
    else
    {
        temperature = (float)(raw_temp / 16.0);
    }

    dev_conversion_delay( );

    if ( temp_format == THERMO15_TEMP_IN_KELVIN )
    {
        temperature = temperature + 273.15;
    }
    else if ( temp_format == THERMO15_TEMP_IN_FAHRENHEIT )
    {
        temperature = ( temperature * 9.0/5.0 ) + 32;
    }

    return temperature;
}

void thermo15_set_temp_register ( thermo15_t *ctx, uint8_t temp_reg, float temp_data )
{
    uint16_t tx_data;
    uint8_t tx_buffer[ 2 ];

    tx_data = (uint16_t)(temp_data * 16);
    tx_data <<= 4;

    tx_buffer[ 0 ] = ( tx_data >> 8 );
    tx_buffer[ 1 ] = ( tx_data & 0x00FF );

    thermo15_generic_write( ctx, temp_reg, tx_buffer, 2 );
}

float thermo15_get_temp_register ( thermo15_t *ctx, uint8_t temp_reg )
{
    float temperature;
    uint16_t temp_data;
    uint8_t rx_buffer[ 2 ];

    thermo15_generic_read( ctx, temp_reg, rx_buffer, 2 );
    temp_data = rx_buffer[ 0 ];
    temp_data <<= 8;
    temp_data |= rx_buffer[ 1 ];
    temp_data >>= 4;

    temperature = (float)(temp_data / 16.0);

    return temperature;
}

uint8_t thermo15_get_interrupt_state ( thermo15_t *ctx )
{
    return digital_in_read( &ctx->alt );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_conversion_delay ( void )
{
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END

