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
 * @file smartbuck7.c
 * @brief Smart Buck 7 Click Driver.
 */

#include "smartbuck7.h"

void smartbuck7_cfg_setup ( smartbuck7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->on = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SMARTBUCK7_DEVICE_ADDRESS;
}

err_t smartbuck7_init ( smartbuck7_t *ctx, smartbuck7_cfg_t *cfg ) 
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

    digital_out_init( &ctx->on, cfg->on );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t smartbuck7_default_cfg ( smartbuck7_t *ctx ) 
{
    err_t error_flag = SMARTBUCK7_OK;
    
    Delay_100ms ( );
    smartbuck7_disable_device ( ctx );
    Delay_1sec ( );
    smartbuck7_enable_device ( ctx );
    Delay_100ms ( );

    return error_flag;
}

err_t smartbuck7_write_reg ( smartbuck7_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( SMARTBUCK7_REG_EN != reg ) && 
         ( SMARTBUCK7_REG_STATUS_2 != reg ) )
    {
        return SMARTBUCK7_ERROR;
    }
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t smartbuck7_read_reg ( smartbuck7_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( ( SMARTBUCK7_REG_SLAVE_ADDRESS != reg ) && 
         ( SMARTBUCK7_REG_EN != reg ) && 
         ( SMARTBUCK7_REG_STATUS_1 != reg ) && 
         ( SMARTBUCK7_REG_STATUS_2 != reg ) )
    {
        return SMARTBUCK7_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void smartbuck7_enable_device ( smartbuck7_t *ctx )
{
    digital_out_low ( &ctx->on );
}

void smartbuck7_disable_device ( smartbuck7_t *ctx )
{
    digital_out_high ( &ctx->on );
}

uint8_t smartbuck7_get_pg_pin ( smartbuck7_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t smartbuck7_read_status ( smartbuck7_t *ctx, smartbuck7_status_t *status )
{
    err_t error_flag = SMARTBUCK7_OK;
    error_flag |= smartbuck7_read_reg( ctx, SMARTBUCK7_REG_STATUS_1, &status->status_1 );
    error_flag |= smartbuck7_read_reg( ctx, SMARTBUCK7_REG_STATUS_2, &status->status_2 );
    return error_flag;
}

err_t smartbuck7_clear_status ( smartbuck7_t *ctx )
{
    return smartbuck7_write_reg( ctx, SMARTBUCK7_REG_STATUS_2, SMARTBUCK7_STATUS_2_CLEAR );
}

err_t smartbuck7_enable_buck ( smartbuck7_t *ctx, uint8_t buck_sel )
{
    err_t error_flag = SMARTBUCK7_OK;
    uint8_t buckx_ctrl = 0;
    if ( ( !buck_sel ) || ( buck_sel > SMARTBUCK7_BUCK_ALL ) )
    {
        return SMARTBUCK7_ERROR;
    }
    error_flag |= smartbuck7_read_reg ( ctx, SMARTBUCK7_REG_EN, &buckx_ctrl );
    if ( SMARTBUCK7_OK == error_flag )
    {
        buckx_ctrl |= ( buck_sel << 4 );
        error_flag |= smartbuck7_write_reg ( ctx, SMARTBUCK7_REG_EN, buckx_ctrl );
    }
    return error_flag;
}

err_t smartbuck7_disable_buck ( smartbuck7_t *ctx, uint8_t buck_sel )
{
    err_t error_flag = SMARTBUCK7_OK;
    uint8_t buckx_ctrl = 0;
    if ( ( !buck_sel ) || ( buck_sel > SMARTBUCK7_BUCK_ALL ) )
    {
        return SMARTBUCK7_ERROR;
    }
    error_flag |= smartbuck7_read_reg ( ctx, SMARTBUCK7_REG_EN, &buckx_ctrl );
    if ( SMARTBUCK7_OK == error_flag )
    {
        buckx_ctrl &= ( ~( buck_sel << 4 ) );
        error_flag |= smartbuck7_write_reg ( ctx, SMARTBUCK7_REG_EN, buckx_ctrl );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
