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
    cfg->i2c_address = 0;
}

err_t i2cisolator2_init ( i2cisolator2_t *ctx, i2cisolator2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    // Output pins 
    digital_out_init( &ctx->pdis, cfg->pdis );

    return I2CISOLATOR2_OK;
}

void i2cisolator2_enable_power ( i2cisolator2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->pdis, state );
}

err_t i2cisolator2_write ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t len )
{
    return i2c_master_write( &ctx->i2c, data_in, len );      
}

err_t i2cisolator2_read ( i2cisolator2_t *ctx, uint8_t *data_out, uint16_t len )
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

err_t i2cisolator2_write_then_read ( i2cisolator2_t *ctx, uint8_t *data_in, uint16_t in_len, 
                                     uint8_t *data_out, uint16_t out_len )
{
    return i2c_master_write_then_read( &ctx->i2c, data_in, in_len, data_out, out_len );
}

err_t i2cisolator2_set_slave_address ( i2cisolator2_t *ctx, uint8_t slave_addr )
{
    ctx->slave_address = slave_addr;
    return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );    
}

// ------------------------------------------------------------------------- END

