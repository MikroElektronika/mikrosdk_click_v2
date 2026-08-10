/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file usbcsink5.c
 * @brief USB-C Sink 5 Click Driver.
 */

#include "usbcsink5.h"

void usbcsink5_cfg_setup ( usbcsink5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCSINK5_DEVICE_ADDRESS_1;
}

err_t usbcsink5_init ( usbcsink5_t *ctx, usbcsink5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alert, cfg->alert );

    return I2C_MASTER_SUCCESS;
}

err_t usbcsink5_write_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t data_in )
{
    return usbcsink5_write_reg_block( ctx, reg, &data_in, 1 );
}

err_t usbcsink5_read_reg_byte ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return usbcsink5_read_reg_block( ctx, reg, data_out, 1 );
}

err_t usbcsink5_write_reg_word ( usbcsink5_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return usbcsink5_write_reg_block( ctx, reg, data_buf, 2 );
}

err_t usbcsink5_read_reg_word ( usbcsink5_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = USBCSINK5_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = usbcsink5_read_reg_block( ctx, reg, data_buf, 2 );
    if ( ( NULL != data_out ) && ( USBCSINK5_OK == error_flag ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t usbcsink5_write_reg_dword ( usbcsink5_t *ctx, uint8_t reg, uint32_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 24 ) & 0xFF );
    return usbcsink5_write_reg_block( ctx, reg, data_buf, 4 );
}

err_t usbcsink5_read_reg_dword ( usbcsink5_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = USBCSINK5_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    error_flag = usbcsink5_read_reg_block( ctx, reg, data_buf, 4 );
    if ( ( NULL != data_out ) && ( USBCSINK5_OK == error_flag ) )
    {
        *data_out = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t usbcsink5_write_reg_block ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t usbcsink5_read_reg_block ( usbcsink5_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

uint8_t usbcsink5_get_alert_pin ( usbcsink5_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

err_t usbcsink5_read_info ( usbcsink5_t *ctx )
{
    err_t error_flag = USBCSINK5_OK;
    error_flag = usbcsink5_read_reg_word ( ctx, USBCSINK5_REG_VID_LOW, &ctx->info.vendor_id );
    if ( USBCSINK5_OK == error_flag )
    {
        if ( USBCSINK5_VENDOR_ID != ctx->info.vendor_id )
        {
            error_flag = USBCSINK5_ERROR;
        }
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_word ( ctx, USBCSINK5_REG_PID_LOW, &ctx->info.product_id );
    }
    if ( USBCSINK5_OK == error_flag )
    {
        if ( USBCSINK5_PRODUCT_ID != ctx->info.product_id )
        {
            error_flag = USBCSINK5_ERROR;
        }
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_dword ( ctx, USBCSINK5_REG_XID_0, &ctx->info.usb_xid );
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( ctx, USBCSINK5_REG_FW_REVISION, &ctx->info.fw_ver );
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( ctx, USBCSINK5_REG_HW_REVISION, &ctx->info.hw_ver );
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( ctx, USBCSINK5_REG_PD_REVISION, &ctx->info.pd_rev );
    }
    if ( USBCSINK5_OK == error_flag )
    {
        error_flag = usbcsink5_read_reg_byte ( ctx, USBCSINK5_REG_PD_VERSION, &ctx->info.pd_ver );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
