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

#include "thermo7.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void thermo7_cfg_setup ( thermo7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x48;
}

THERMO7_RETVAL thermo7_init ( thermo7_t *ctx, thermo7_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return THERMO7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return THERMO7_OK;
}

void thermo7_generic_write ( thermo7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void thermo7_generic_read ( thermo7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

float thermo7_read_ambient_temperature ( thermo7_t *ctx )
{
    uint8_t read_reg[ 2 ] = { 0 };
    float temp_msb;
    uint8_t temp_lsb;
    
    thermo7_generic_read( ctx, THERMO7_REG_AMBIENT_TEMPERATURE, read_reg, 2 );
    
    temp_msb = read_reg[ 0 ];
    temp_lsb = read_reg[ 1 ] & 0xF0;

    if ( temp_lsb & 0x80 )
    {
        temp_msb += 0.50;
    } 
    if ( temp_lsb & 0x40 ) 
    {
        temp_msb += 0.25;
    }
    if ( temp_lsb & 0x20 ) 
    {
        temp_msb += 0.125;
    }
    if ( temp_lsb & 0x10 ) 
    {
        temp_msb += 0.0625;
    }

    return temp_msb;
}

void thermo7_set_configuration ( thermo7_t *ctx, uint8_t configuration )
{
    thermo7_generic_write( ctx, THERMO7_REG_CONFIGURATION, &configuration, 1 );
}

int16_t thermo7_get_hysteresis_temperature ( thermo7_t *ctx )
{
    uint8_t read_reg[ 2 ] = { 0 };
    int16_t hysteresis_temperature;

    thermo7_generic_read( ctx, THERMO7_REG_HYSTERESIS_TEMPERATURE, read_reg, 2 );

    hysteresis_temperature =  read_reg[ 0 ];
    hysteresis_temperature <<= 8;
    hysteresis_temperature |= ( read_reg[ 1 ] & 0x80 );

    return hysteresis_temperature;
}

void thermo7_set_hysteresis_temperature ( thermo7_t *ctx, int8_t temperature )
{
    uint8_t write_reg[ 2 ];
    uint8_t negative_lower = 0;
    
    if ( temperature < 0 )
    {
        negative_lower = 1;
    }    
        
    write_reg[ 0 ] = ( temperature & 0x7F ) | ( negative_lower << 7 );
    write_reg[ 1 ] = 0x00;

    thermo7_generic_write( ctx, THERMO7_REG_HYSTERESIS_TEMPERATURE, write_reg, 2 );
}

int16_t thermo7_get_limit_temperature ( thermo7_t *ctx )
{
    uint8_t read_reg[ 2 ] = { 0 };
    int16_t limit_temperature;

    thermo7_generic_read( ctx, THERMO7_REG_TEMPERATURE_LIMIT_SET, read_reg, 2 );

    limit_temperature =  read_reg[ 0 ];
    limit_temperature <<= 8;
    limit_temperature |= ( read_reg[ 1 ] & 0x80 );

    return limit_temperature;
}

void thermo7_set_limit_temperature ( thermo7_t *ctx, int16_t temperature )
{
    uint8_t write_reg[ 2 ];
    uint8_t negative_upper = 0;

    if ( temperature < 0 )
    {
        negative_upper = 1;
    }

    write_reg[ 0 ] = ( temperature & 0x7F ) | ( negative_upper << 7 );
    write_reg[ 1 ] = 0x00;

    thermo7_generic_write( ctx, THERMO7_REG_TEMPERATURE_LIMIT_SET, write_reg, 2 
);
}

uint8_t thermo7_get_interrupt ( thermo7_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void thermo7_set_resolution ( thermo7_t *ctx, uint8_t resolution )
{
    uint8_t write_reg;
    uint8_t read_reg;
    
    thermo7_generic_read( ctx, THERMO7_REG_CONFIGURATION, &read_reg, 1 );
    write_reg = read_reg | resolution;

    thermo7_generic_write( ctx, THERMO7_REG_CONFIGURATION, &write_reg, 1 );
}

// ------------------------------------------------------------------------- END

