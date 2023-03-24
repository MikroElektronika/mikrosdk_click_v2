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

#include "dualee.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void dualee_cfg_setup ( dualee_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address_1 = DUALEE_SLAVEADDRESS_1;
    cfg->i2c_address_2 = DUALEE_SLAVEADDRESS_2;
}

DUALEE_RETVAL dualee_init ( dualee_t *ctx, dualee_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;
    ctx->slave_address_1 = cfg->i2c_address_1;
    ctx->slave_address_2 = cfg->i2c_address_2;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return DUALEE_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    return DUALEE_OK;
}

void dualee_generic_write ( dualee_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg[ 0 ];
    tx_buf[ 1 ] = reg[ 1 ];
    
    for ( cnt = 2; cnt <= len + 1; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 2 ]; 
    }

    i2c_master_write( &ctx->i2c, tx_buf, len + 2 );      
}

void dualee_generic_read ( dualee_t *ctx, uint8_t *reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 2 ];

    tx_buf [ 0 ] = reg[ 0 ];
    tx_buf [ 1 ] = reg[ 1 ];

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_buf, len );
}

uint8_t dualee_write ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes)
{
    uint8_t write_reg[ 2 ];

    if ( ( n_bytes > DUALEE_MAXIMUM_DATA ) || ( reg_address > DUALEE_PAGE_END_OF_SECOND ) )
    {
        return DUALEE_ERROR_RW;
    }

    if ( reg_address > DUALEE_PAGE_END_OF_FIRST )
    {
        reg_address -= DUALEE_PAGE_START_OF_SECOND;
        ctx->slave_address = ctx->slave_address_2;
    }
    else
    {
        ctx->slave_address = ctx->slave_address_1;
    }
    ctx->slave_address |= ( reg_address >> 16 );
    write_reg[ 0 ] = ( reg_address >> 8 );
    write_reg[ 1 ] = reg_address;
    
    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    dualee_generic_write( ctx, write_reg, data_buff, n_bytes );
    return DUALEE_SUCCESSFUL_RW;
}

uint8_t dualee_read ( dualee_t *ctx, uint32_t reg_address, uint8_t *data_buff, uint8_t n_bytes )
{
    uint8_t write_reg[ 2 ];

    if ( ( n_bytes > DUALEE_MAXIMUM_DATA ) || ( reg_address > DUALEE_PAGE_END_OF_SECOND ) )
    {
        return DUALEE_ERROR_RW;
    }

    if ( reg_address > DUALEE_PAGE_END_OF_FIRST )
    {
        reg_address -= DUALEE_PAGE_START_OF_SECOND;
        ctx->slave_address = ctx->slave_address_2;
    }
    else
    {
        ctx->slave_address = ctx->slave_address_1;
    }
    ctx->slave_address |= (reg_address >> 16);
    write_reg[ 0 ] = (reg_address >> 8);
    write_reg[ 1 ] = reg_address;

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    dualee_generic_read( ctx, write_reg, data_buff, n_bytes );

    return DUALEE_SUCCESSFUL_RW;
}

// ------------------------------------------------------------------------- END

