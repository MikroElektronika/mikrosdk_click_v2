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
 * @file i2cmux6.c
 * @brief I2C MUX 6 Click Driver.
 */

#include "i2cmux6.h"

void i2cmux6_cfg_setup ( i2cmux6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en1 = HAL_PIN_NC;
    cfg->en2 = HAL_PIN_NC;
    cfg->en3 = HAL_PIN_NC;
    cfg->en4 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CMUX6_DEVICE_ADDRESS;
}

err_t i2cmux6_init ( i2cmux6_t *ctx, i2cmux6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );
    digital_out_init( &ctx->en3, cfg->en3 );
    digital_out_init( &ctx->en4, cfg->en4 );
    
    digital_out_low ( &ctx->en1 );
    digital_out_low ( &ctx->en2 );
    digital_out_low ( &ctx->en3 );
    digital_out_low ( &ctx->en4 );

    return I2C_MASTER_SUCCESS;
}

err_t i2cmux6_generic_write ( i2cmux6_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t i2cmux6_generic_read ( i2cmux6_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t i2cmux6_set_channel ( i2cmux6_t *ctx, uint8_t ch_sel, uint8_t ch_slave_addr )
{
    if ( ch_sel & I2CMUX6_CHANNEL_1 )
    {
        digital_out_high ( &ctx->en1 );
    }
    else
    {
        digital_out_low ( &ctx->en1 );
    }
    if ( ch_sel & I2CMUX6_CHANNEL_2 )
    {
        digital_out_high ( &ctx->en2 );
    }
    else
    {
        digital_out_low ( &ctx->en2 );
    }
    if ( ch_sel & I2CMUX6_CHANNEL_3 )
    {
        digital_out_high ( &ctx->en3 );
    }
    else
    {
        digital_out_low ( &ctx->en3 );
    }
    if ( ch_sel & I2CMUX6_CHANNEL_4 )
    {
        digital_out_high ( &ctx->en4 );
    }
    else
    {
        digital_out_low ( &ctx->en4 );
    }
    ctx->slave_address = ch_slave_addr;
    return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
}

// ------------------------------------------------------------------------- END
