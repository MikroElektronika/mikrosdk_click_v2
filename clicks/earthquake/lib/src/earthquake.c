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

#include "earthquake.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void earthquake_cfg_setup ( earthquake_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->st   = HAL_PIN_NC;
    cfg->int2 = HAL_PIN_NC;
    cfg->int1 = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = EARTHQUAKE_I2C_ADDRESS;
}

EARTHQUAKE_RETVAL earthquake_init ( earthquake_t *ctx, earthquake_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return EARTHQUAKE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins 

    digital_in_init( &ctx->int2, cfg->int2 );
    digital_in_init( &ctx->int1, cfg->int1 );

    // Output pins

    digital_out_init( &ctx->st, cfg->st );

    return EARTHQUAKE_OK;
}

void earthquake_generic_write ( earthquake_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = ( uint8_t ) ( ( reg & 0xFF00 ) >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( reg & 0x00FF );
    
    for ( cnt = 2; cnt <= len + 1; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 2 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 2 );     
}

void earthquake_generic_read ( earthquake_t *ctx, uint16_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = ( uint8_t ) ( ( reg & 0xFF00 ) >> 8 );
    tx_buf[ 1 ] = ( uint8_t ) ( reg & 0x00FF );
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_buf, len );
}

uint8_t earthquake_shutoff_output ( earthquake_t *ctx )
{
    return digital_in_read( &ctx->int1 );   
}

uint8_t earthquake_proc_notify ( earthquake_t *ctx )
{
    return !digital_in_read( &ctx->int2 ); 
}

uint8_t earthquake_read_status ( earthquake_t *ctx )
{
    uint8_t res;
    
    earthquake_generic_read( ctx, EARTHQUAKE_STATE, &res, 1 );
    
    return res;
}

uint16_t earthquake_read_si ( earthquake_t *ctx )
{
    uint8_t rx_buf[ 2 ];
    uint16_t result;
    
    earthquake_generic_read( ctx, EARTHQUAKE_MAIN_SI_H, rx_buf, 2 );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    
    return result;
}

void earthquake_clear_mememory ( earthquake_t *ctx  )
{
    earthquake_generic_write( ctx, EARTHQUAKE_CLEAR_COMMAND, 0x00, 1 );
}

// ------------------------------------------------------------------------- END

