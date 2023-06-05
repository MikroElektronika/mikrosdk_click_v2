/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file i2cextend2.c
 * @brief I2C Extend 2 Click Driver.
 */

#include "i2cextend2.h"

void i2cextend2_cfg_setup ( i2cextend2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = C6DOFIMU11_I2C_SLAVE_ADDRESS_GND;
}

err_t i2cextend2_init ( i2cextend2_t *ctx, i2cextend2_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

void i2cextend2_rmt_write ( i2cextend2_t *ctx, uint8_t reg, uint8_t tx_data ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    i2c_master_write( &ctx->i2c, tx_buf, 2 );
}

uint8_t i2cextend2_rmt_read ( i2cextend2_t *ctx, uint8_t reg ) 
{
    uint8_t rx_buf = 0;

    i2c_master_write_then_read( &ctx->i2c, &reg, 1, &rx_buf, 1 );

    return rx_buf;
}

void i2cextend2_rmt_multi_write ( i2cextend2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes ) 
{
    uint8_t tx_buf[ 256 ] = { 0 };

    tx_buf[ 0 ] = reg;

    for ( uint8_t n_cnt = 0; n_cnt < n_bytes; n_cnt++ ) 
    {
        tx_buf[ n_cnt + 1 ] = p_tx_data[ n_cnt ];
    }

    i2c_master_write( &ctx->i2c, tx_buf, n_bytes + 1 );
}

void i2cextend2_rmt_multi_read ( i2cextend2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes ) 
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, p_rx_data, n_bytes );
}

void i2cextend2_enable ( i2cextend2_t *ctx, uint8_t en_extend ) 
{
    if ( I2CEXTEND2_EXTEND_DISABLE == en_extend ) 
    {
        digital_out_low( &ctx->en );
    } 
    else 
    {
        digital_out_high( &ctx->en );
    }
}

// ------------------------------------------------------------------------- END
