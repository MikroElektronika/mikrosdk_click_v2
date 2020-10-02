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

#include "eeprom3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeprom3_cfg_setup ( eeprom3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x54;
}

EEPROM3_RETVAL eeprom3_init ( eeprom3_t *ctx, eeprom3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EEPROM3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return EEPROM3_OK;
}

void eeprom3_write_byte ( eeprom3_t *ctx, uint16_t reg_address, uint8_t data_in )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = ( reg_address >> 8 ) & 0x0F;
    tx_buf[ 1 ] = reg_address & 0x0F;
    tx_buf[ 2 ] = data_in;  

    i2c_master_write( &ctx->i2c, tx_buf, 3 );   
}

void eeprom3_write_page ( eeprom3_t *ctx, uint16_t reg_address, uint8_t* data_in, uint8_t count )
{
    uint8_t tx_buf[ 258 ] = { 0 };
    uint8_t cnt;

    tx_buf [ 0 ] = ( reg_address >> 8 ) & 0xFF;
    tx_buf [ 1 ] = reg_address & 0xFF;

    for ( cnt = 0; cnt < count; cnt++ )
    {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, count + 2 );   
}

void eeprom3_read ( eeprom3_t *ctx, uint16_t reg_address, uint8_t *data_out, uint16_t count )
{
    uint8_t tx_buf[ 2 ];

    tx_buf [ 0 ] = ( reg_address >> 8 ) & 0x0F;
    tx_buf [ 1 ] = reg_address & 0x0F;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_out, count );
}

// ------------------------------------------------------------------------- END

