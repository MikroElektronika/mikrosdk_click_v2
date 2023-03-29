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

#include "sram2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void sram2_cfg_setup ( sram2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->wp = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = SRAM2_SLAVE_ADDR_0_0;
}

SRAM2_RETVAL sram2_init ( sram2_t *ctx, sram2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return SRAM2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->wp, cfg->wp );

    digital_out_low( &ctx->wp );

    return SRAM2_OK;
}

void sram2_generic_write ( sram2_t *ctx, uint16_t reg, uint8_t wr_data )
{
    uint8_t tx_buf[ 3 ];
    
    tx_buf[ 0 ] = reg >> 8;
    tx_buf[ 1 ] = reg & 0xFF;
    tx_buf[ 2 ] = wr_data;

    i2c_master_write( &ctx->i2c, tx_buf, 3 );   
}

void sram2_generic_read ( sram2_t *ctx, uint16_t reg, uint8_t *rx_data )
{
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg >> 8;
    tx_buf[ 1 ] = reg & 0xFF;
    
    i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, rx_data, 1 );
}

void sram2_write_protect( sram2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wp, state );
}

// ------------------------------------------------------------------------- END

