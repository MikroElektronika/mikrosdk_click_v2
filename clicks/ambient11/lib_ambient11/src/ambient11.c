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

#include "ambient11.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient11_cfg_setup ( ambient11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMBIENT11_SLAVE_ADDRESS;
}

AMBIENT11_RETVAL ambient11_init ( ambient11_t *ctx, ambient11_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT11_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AMBIENT11_OK;
}

void ambient11_default_cfg ( ambient11_t *ctx )
{
    ambient11_generic_write( ctx, AMBIENT11_ALS_CONF_WR, AMBIENT11_ALS_CONF_CHAN_EN );
    Delay_100ms();
}

void ambient11_generic_write ( ambient11_t *ctx, uint8_t wr_cmd, uint16_t wr_data )
{
    uint8_t tx_buf[ 3 ];
   
    tx_buf[ 0 ] = wr_cmd;
    tx_buf[ 1 ] = wr_data & 0xFF;
    tx_buf[ 2 ] = ( wr_data >> 8 ) & 0xFF;    

    i2c_master_write( &ctx->i2c, tx_buf, 3 );   
}

uint16_t ambient11_generic_read ( ambient11_t *ctx, uint8_t reg_addr )
{
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 2 ];
    uint16_t result;

    tx_buf [ 0 ] = reg_addr;

    i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, rx_buf, 2 );

    result = rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 0 ];

    return result;
}

float ambient11_calc_illumination ( ambient11_t *ctx, float typical_res )
{
    uint16_t raw_val;
    float lx_val;
    
    raw_val = ambient11_generic_read ( ctx, AMBIENT11_ALS_CONF_RD );
    lx_val = ( ( float )raw_val ) * typical_res;
    
    return lx_val;
}

uint8_t ambient11_check_int ( ambient11_t *ctx )
{
    return 	 digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

