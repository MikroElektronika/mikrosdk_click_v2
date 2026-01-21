/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file i2cmux9.c
 * @brief I2C MUX 9 Click Driver.
 */

#include "i2cmux9.h"

void i2cmux9_cfg_setup ( i2cmux9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CMUX9_DEVICE_ADDRESS_A2A1A0_000;
}

err_t i2cmux9_init ( i2cmux9_t *ctx, i2cmux9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    return I2C_MASTER_SUCCESS;
}

err_t i2cmux9_set_channel ( i2cmux9_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr )
{
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    error_flag |= i2c_master_write( &ctx->i2c, &ch_sel, 1 );
    ctx->ch_slave_address = ch_slave_addr;
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->ch_slave_address );
    return error_flag;
}

err_t i2cmux9_read_channel ( i2cmux9_t *ctx, uint8_t *ch_sel )
{
    uint8_t control = 0;
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    error_flag |= i2c_master_read( &ctx->i2c, &control, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->ch_slave_address );
    if ( ( I2CMUX9_OK == error_flag ) && ( NULL != ch_sel ) )
    {
        control &= I2CMUX9_CHANNEL_MASK;
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            if ( control & ( I2CMUX9_CHANNEL_0 << cnt ) )
            {
                *ch_sel = cnt;
            }
        }
    }
    return error_flag;
}

void i2cmux9_set_rst_pin ( i2cmux9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void i2cmux9_reset_device ( i2cmux9_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t i2cmux9_i2c_write ( i2cmux9_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

err_t i2cmux9_i2c_read ( i2cmux9_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

err_t i2cmux9_i2c_write_then_read ( i2cmux9_t *ctx, uint8_t *data_in, uint16_t in_len, 
                                                    uint8_t *data_out, uint8_t out_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, data_in, in_len, data_out, out_len );
}

err_t i2cmux9_i2c_write_reg ( i2cmux9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t i2cmux9_i2c_read_reg ( i2cmux9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

// ------------------------------------------------------------------------- END
