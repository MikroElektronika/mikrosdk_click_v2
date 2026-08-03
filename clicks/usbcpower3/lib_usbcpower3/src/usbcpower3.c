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
 * @file usbcpower3.c
 * @brief USB-C Power 3 Click Driver.
 */

#include "usbcpower3.h"

void usbcpower3_cfg_setup ( usbcpower3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->fen = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->lim = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = USBCPOWER3_DEVICE_ADDRESS_PTN;
}

err_t usbcpower3_init ( usbcpower3_t *ctx, usbcpower3_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->lim, cfg->lim );

    digital_in_init( &ctx->fen, cfg->fen );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    Delay_100ms( );
    usbcpower3_set_high_current ( ctx );
    usbcpower3_restart_device ( ctx );
    Delay_100ms( );

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

    return usbcpower3_wait_tcpc_init ( ctx );
}

err_t usbcpower3_ptn_write_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t data_in )
{
    return usbcpower3_ptn_write_reg_block( ctx, reg, &data_in, 1 );
}

err_t usbcpower3_ptn_read_reg_byte ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return usbcpower3_ptn_read_reg_block( ctx, reg, data_out, 1 );
}

err_t usbcpower3_ptn_write_reg_word ( usbcpower3_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return usbcpower3_ptn_write_reg_block( ctx, reg, data_buf, 2 );
}

err_t usbcpower3_ptn_read_reg_word ( usbcpower3_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = USBCPOWER3_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    error_flag = usbcpower3_ptn_read_reg_block( ctx, reg, data_buf, 2 );
    if ( ( NULL != data_out ) && ( USBCPOWER3_OK == error_flag ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
    }
    return error_flag;
}

err_t usbcpower3_ptn_write_reg_block ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    if ( USBCPOWER3_DEVICE_ADDRESS_PTN != ctx->slave_address )
    {
        ctx->slave_address = USBCPOWER3_DEVICE_ADDRESS_PTN;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t usbcpower3_ptn_read_reg_block ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( USBCPOWER3_DEVICE_ADDRESS_PTN != ctx->slave_address )
    {
        ctx->slave_address = USBCPOWER3_DEVICE_ADDRESS_PTN;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t usbcpower3_act_write_reg ( usbcpower3_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    if ( USBCPOWER3_DEVICE_ADDRESS_ACT != ctx->slave_address )
    {
        ctx->slave_address = USBCPOWER3_DEVICE_ADDRESS_ACT;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t usbcpower3_act_read_reg ( usbcpower3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( USBCPOWER3_DEVICE_ADDRESS_ACT != ctx->slave_address )
    {
        ctx->slave_address = USBCPOWER3_DEVICE_ADDRESS_ACT;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t usbcpower3_ptn_read_info ( usbcpower3_t *ctx )
{
    err_t error_flag = USBCPOWER3_OK;
    error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_VENDOR_ID, &ctx->info.vendor_id );
    if ( USBCPOWER3_OK == error_flag )
    {
        if ( USBCPOWER3_PTN_VENDOR_ID != ctx->info.vendor_id )
        {
            error_flag = USBCPOWER3_ERROR;
        }
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_PRODUCT_ID, &ctx->info.product_id );
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        if ( USBCPOWER3_PTN_PRODUCT_ID != ctx->info.product_id )
        {
            error_flag = USBCPOWER3_ERROR;
        }
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_DEVICE_ID, &ctx->info.device_id );
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_USBTYPEC_REV, &ctx->info.usbtypec_rev );
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_USBPD_REV_VER, &ctx->info.usbpd_rev_ver );
    }
    if ( USBCPOWER3_OK == error_flag )
    {
        error_flag = usbcpower3_ptn_read_reg_word ( ctx, USBCPOWER3_PTN_REG_PD_INTERFACE_REV, &ctx->info.pd_interface_rev );
    }
    return error_flag;
}

void usbcpower3_enable_device ( usbcpower3_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void usbcpower3_disable_device ( usbcpower3_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
}

void usbcpower3_restart_device ( usbcpower3_t *ctx )
{
    usbcpower3_disable_device ( ctx );
    usbcpower3_enable_device ( ctx );
}

err_t usbcpower3_wait_tcpc_init ( usbcpower3_t *ctx )
{
    err_t error_flag = USBCPOWER3_OK;
    uint32_t timeout_cnt = 0;
    uint8_t status = 0;

    // Wait for TCPC Initialization to complete
    do
    {
        error_flag |= usbcpower3_ptn_read_reg_byte ( ctx, USBCPOWER3_PTN_REG_POWER_STATUS, &status );
        if ( USBCPOWER3_OK == error_flag )
        {
            if ( status )
            {
                error_flag |= usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_POWER_STATUS, status );
            }
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > USBCPOWER3_PTN_TIMEOUT_MS )
        {
            error_flag = USBCPOWER3_ERROR;
        }
    }
    while ( ( status & USBCPOWER3_PTN_POWER_STATUS_TCPC_INIT ) && ( USBCPOWER3_OK == error_flag ) );

    if ( USBCPOWER3_OK == error_flag )
    {
        // Read and clear fault status to clear All Registers Reset To Default flag
        error_flag = usbcpower3_ptn_read_reg_byte ( ctx, USBCPOWER3_PTN_REG_FAULT_STATUS, &status );
        if ( status && ( USBCPOWER3_OK == error_flag ) )
        {
            error_flag = usbcpower3_ptn_write_reg_byte ( ctx, USBCPOWER3_PTN_REG_FAULT_STATUS, status );
        }
    }

    return error_flag;
}

void usbcpower3_set_high_current ( usbcpower3_t *ctx )
{
    digital_out_high ( &ctx->lim );
}

void usbcpower3_set_low_current ( usbcpower3_t *ctx )
{
    digital_out_low ( &ctx->lim );
}

uint8_t usbcpower3_get_int_pin ( usbcpower3_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

uint8_t usbcpower3_get_fen_pin ( usbcpower3_t *ctx )
{
    return digital_in_read ( &ctx->fen );
}

// ------------------------------------------------------------------------- END
