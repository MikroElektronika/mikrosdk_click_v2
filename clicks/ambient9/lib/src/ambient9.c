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

#include "ambient9.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ambient9_cfg_setup ( ambient9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = AMBIENT9_SLAVE_ADDR;
}

AMBIENT9_RETVAL ambient9_init ( ambient9_t *ctx, ambient9_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if (  i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return AMBIENT9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return AMBIENT9_OK;
}

uint8_t ambient9_get_int_status ( ambient9_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void ambient9_generic_write ( ambient9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void ambient9_generic_read ( ambient9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint32_t ambient9_als_data ( ambient9_t *ctx )
{
    uint8_t als_data[ 3 ] = { 0x00 };
    uint32_t temp_value = 0x00;
    
    ambient9_generic_read( ctx, AMBIENT9_REG_ALS_DATA_0, &als_data[ 0 ], 1 );
    ambient9_generic_read( ctx, AMBIENT9_REG_ALS_DATA_1, &als_data[ 1 ], 1 );
    ambient9_generic_read( ctx, AMBIENT9_REG_ALS_DATA_2, &als_data[ 2 ], 1 );

    temp_value = als_data[ 2 ] & 0x0F;
    temp_value <<= 16;
    temp_value |= als_data[ 1 ];
    temp_value <<= 8;
    temp_value |= als_data[ 0 ];

    return temp_value;
}

uint16_t ambient9_proxy_data ( ambient9_t *ctx )
{
    uint8_t proxy_data[ 2 ] = { 0x00 };
    uint16_t temp_value = 0x00;

    ambient9_generic_read( ctx, AMBIENT9_REG_PS_DATA_0, &proxy_data[ 0 ], 1 );
    ambient9_generic_read( ctx, AMBIENT9_REG_PS_DATA_1, &proxy_data[ 1 ], 1 );

    temp_value = proxy_data[ 1 ] & 0x07;
    temp_value <<= 8;
    temp_value |= proxy_data[ 0 ];

    return temp_value;
}

void ambient9_enable_data ( ambient9_t *ctx, uint8_t als_ps )
{
    uint8_t tmp;

    switch ( als_ps )
    {
        case AMBIENT9_ALS:
        {
            tmp = 0x02;
            ambient9_generic_write( ctx, AMBIENT9_REG_MAIN_CTRL, &tmp, 1 );
            return;
        }
        case AMBIENT9_PROXY:
        {
            tmp = 0x01;
            ambient9_generic_write( ctx, AMBIENT9_REG_MAIN_CTRL, &tmp, 1 );
            return;       
        }
        default:
        {
            return;
        }
    }
}

// ------------------------------------------------------------------------- END

