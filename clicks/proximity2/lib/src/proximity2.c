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

#include "proximity2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void proximity2_cfg_setup ( proximity2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_FULL; 
    cfg->i2c_address = PROXIMITY2_I2C_SLAVE_ADDR;
}

PROXIMITY2_RETVAL proximity2_init ( proximity2_t *ctx, proximity2_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return PROXIMITY2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
 
    return PROXIMITY2_OK;

}

void proximity2_default_cfg ( proximity2_t *ctx )
{
    // Click default configuration
    uint8_t buf[ 1 ];
    
    // Default configuratin of the main config  
    
    buf[ 0 ] = PROXIMITY2_MAIN_CONFIG_DEFAULT;
    proximity2_generic_write( ctx, PROXIMITY2_REG_MAIN_CONFIG, buf,  1 );
    
    // Default configuratin of the rece config   
    
    buf[ 0 ] = PROXIMITY2_RECE_CONFIG_DEFAULT;
    proximity2_generic_write( ctx, PROXIMITY2_REG_RECEIVE_CONFIG, buf,  1 );
    
    // Default configuratin of the trabsmit config   
    
    buf[ 0 ] = PROXIMITY2_LED_DRV_CURRENT_110_MA;
    proximity2_generic_write( ctx, PROXIMITY2_REG_TRANSMIT_CONFIG, buf,  1 );
}

void proximity2_generic_write ( proximity2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void proximity2_generic_read ( proximity2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}
 
uint8_t proximity2_read_prox ( proximity2_t *ctx )
{
    uint8_t buf[ 1 ];
    uint8_t result;
    
    proximity2_generic_read( ctx, PROXIMITY2_REG_PROX, buf, 1 );
    
    result = buf[ 0 ];
    
    return result;
}

uint16_t proximity2_read_als ( proximity2_t *ctx )
{
    uint8_t buf[ 2 ];
    uint16_t result;
    
    proximity2_generic_read( ctx, PROXIMITY2_REG_ALS_HI_BY, buf, 2 );
    
    result = buf[ 0 ];
    result <<= 8;
    result |= buf[ 1 ];
    result &= 0x3FFF;

    return result;
}

uint8_t proximity2_get_int_pin_status ( proximity2_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


// ------------------------------------------------------------------------- END

