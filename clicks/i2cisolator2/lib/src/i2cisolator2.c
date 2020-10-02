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

#include "i2cisolator2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void i2cisolator2_cfg_setup ( i2cisolator2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->pdis = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = I2CISOLATOR2_IRTHERMO2_I2C_ADDRESS_0;
}

I2CISOLATOR2_RETVAL i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return I2CISOLATOR2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->pdis, cfg->pdis );

    Delay_100ms( );
    digital_out_low( &ctx->pdis );
    Delay_100ms( );

    return I2CISOLATOR2_OK;
}

void i2cisolator2_default_cfg ( i2cisolator2_t *ctx )
{
    uint8_t w_buf[ 2 ];
    uint16_t cfg;

    cfg = I2CISOLATOR2_IRTHERMO2_CFG_MODEON | I2CISOLATOR2_IRTHERMO2_CFG_ALERTEN |
          I2CISOLATOR2_IRTHERMO2_CFG_TRANSC | I2CISOLATOR2_IRTHERMO2_CFG_16SAMPLE;

    w_buf[ 0 ] = ( cfg & 0xFF00 ) >> 8;
    w_buf[ 1 ] = cfg & 0x00FF;

    i2cisolator2_generic_write( ctx, I2CISOLATOR2_IRTHERMO2_CONFIGURATION, w_buf, 2 );

    cfg = I2CISOLATOR2_IRTHERMO2_STAT_ALERTEN | I2CISOLATOR2_IRTHERMO2_STAT_CRTEN;

    w_buf[ 0 ] = ( cfg & 0xFF00 ) >> 8;
    w_buf[ 1 ] = cfg & 0x00FF;

    i2cisolator2_generic_write( ctx, I2CISOLATOR2_IRTHERMO2_STATUS_MASK_AND_ENABLE, w_buf, 2 );

    Delay_100ms( );
}

void i2cisolator2_generic_write ( i2cisolator2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void i2cisolator2_generic_read ( i2cisolator2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

// ------------------------------------------------------------------------- END

