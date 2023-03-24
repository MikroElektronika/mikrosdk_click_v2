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

#include "templog6.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void templog6_cfg_setup ( templog6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = TEMPLOG6_DEVICE_SLAVE_ADDRESS;
}

TEMPLOG6_RETVAL templog6_init ( templog6_t *ctx, templog6_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return TEMPLOG6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return TEMPLOG6_OK;
}

void templog6_default_cfg ( templog6_t *ctx ) 
{
    // Configuration
    
    templog6_write_byte( ctx , TEMPLOG6_REG_WR_CONFIGURATION,  TEMPLOG6_CFG_ALERT_ON |
    TEMPLOG6_CFG_NORMAL_MODE | TEMPLOG6_CFG_LOCAL_MEASUREMENT_ON | TEMPLOG6_CFG_ALERT_2_FAULT );
}

void templog6_generic_write ( templog6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void templog6_generic_read ( templog6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void templog6_write_byte ( templog6_t *ctx, uint8_t reg, uint8_t data_buf )
{
    uint8_t write_reg[ 1 ];
    
    write_reg[ 0 ] = data_buf;
    
    templog6_generic_write( ctx, reg, write_reg, 1 );
}

uint8_t templog6_read_byte ( templog6_t *ctx, uint8_t reg ) 
{
    uint8_t read_buf[ 1 ];
    
    templog6_generic_read( ctx, reg, read_buf, 1 );
    
    return read_buf[ 0 ];
}

uint8_t templog6_get_interrupt ( templog6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

