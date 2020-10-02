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

#include "eeram.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eeram_cfg_setup ( eeram_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->hs = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_control_address = EERAM_ADDRESS_CONTROL;
    cfg->i2c_sram_address = EERAM_ADDRESS_SRAM;
}

EERAM_RETVAL eeram_init ( eeram_t *ctx, eeram_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address_sram = cfg->i2c_sram_address;
    ctx->slave_address_control = cfg->i2c_control_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return EERAM_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address_sram );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->hs, cfg->hs );

    return EERAM_OK;
}

void eeram_generic_write ( eeram_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void eeram_generic_read ( eeram_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void eeram_status_write ( eeram_t *ctx, uint8_t command )
{
    uint8_t write_data[ 1 ];
    write_data[ 0 ] = command;
    eeram_generic_write( ctx,  0x00, write_data, 2 );
}

uint8_t eeram_status_read ( eeram_t *ctx )
{
    uint8_t read_data[ 1 ];
    eeram_generic_read( ctx, 0x00, read_data, 1 );
     
    return read_data[ 0 ];
}

void eeram_read ( eeram_t *ctx, uint16_t address, uint8_t *data_out, uint8_t count_out )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t )( address >> 8 );
    tx_buf[ 1 ] = ( uint8_t )( address & 0x00FF );
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_out, count_out );
}

void eeram_write ( eeram_t *ctx, uint16_t address, uint8_t * data_in, uint8_t count_in )
{
    uint8_t tx_buf[ 258 ];
    
    tx_buf[ 0 ] = ( uint8_t )( address >> 8 );
    tx_buf[ 1 ] = ( uint8_t )( address & 0x00FF );

    memcpy( ( void* )( tx_buf + 2 ), ( void* )data_in, count_in );

    i2c_master_write( &ctx->i2c, tx_buf, count_in + 2 ); 
}

// ------------------------------------------------------------------------- END

