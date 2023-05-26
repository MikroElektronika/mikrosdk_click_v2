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
 * @file usbtoi2c2.c
 * @brief USB to I2C 2 Click Driver.
 */

#include "usbtoi2c2.h"

void usbtoi2c2_cfg_setup ( usbtoi2c2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->tx_ind = HAL_PIN_NC;
    cfg->rx_ind = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBTOI2C2_DEVICE_SLAVE_ADDRESS;
}

err_t usbtoi2c2_init ( usbtoi2c2_t *ctx, usbtoi2c2_cfg_t *cfg ) 
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
    
    digital_in_init( &ctx->tx_ind, cfg->tx_ind );
    digital_in_init( &ctx->rx_ind, cfg->rx_ind );

    return I2C_MASTER_SUCCESS;
}

err_t usbtoi2c2_default_cfg ( usbtoi2c2_t *ctx ) 
{
    err_t error_flag = USBTOI2C2_OK;
    usbtoi2c2_reset_device ( ctx );
    error_flag |= usbtoi2c2_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= usbtoi2c2_flush_data ( ctx );
    Delay_100ms ( );
    return error_flag;
}

err_t usbtoi2c2_write_data ( usbtoi2c2_t *ctx, uint8_t *tx_buf, uint8_t tx_len )
{
    if ( !digital_in_read ( &ctx->tx_ind ) )
    {
        return i2c_master_write( &ctx->i2c, tx_buf, tx_len );
    }
    return USBTOI2C2_ERROR;
}

err_t usbtoi2c2_read_data ( usbtoi2c2_t *ctx, uint8_t *rx_buf, uint8_t rx_len )
{
    if ( !digital_in_read ( &ctx->rx_ind ) )
    {
        return i2c_master_read( &ctx->i2c, rx_buf, rx_len );
    }
    return USBTOI2C2_ERROR;
}

void usbtoi2c2_reset_device ( usbtoi2c2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t usbtoi2c2_soft_reset ( usbtoi2c2_t *ctx )
{
    uint8_t command = USBTOI2C2_CMD_SOFT_RESET;
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, USBTOI2C2_GENERAL_CALL_ADDRESS );
    error_flag |= i2c_master_write( &ctx->i2c, &command, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    return error_flag;
}

err_t usbtoi2c2_flush_data ( usbtoi2c2_t *ctx )
{
    uint8_t command = USBTOI2C2_CMD_FLUSH_DATA;
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, USBTOI2C2_GENERAL_CALL_ADDRESS );
    error_flag |= i2c_master_write( &ctx->i2c, &command, 1 );
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    return error_flag;
}

// ------------------------------------------------------------------------- END
