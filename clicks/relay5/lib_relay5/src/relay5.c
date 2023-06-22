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
 * @file relay5.c
 * @brief Relay 5 Click Driver.
 */

#include "relay5.h"

void relay5_cfg_setup ( relay5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RELAY5_DEVICE_ADDRESS_A1A0_00;
}

err_t relay5_init ( relay5_t *ctx, relay5_cfg_t *cfg ) 
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

err_t relay5_default_cfg ( relay5_t *ctx ) 
{
    err_t error_flag = RELAY5_OK;
    relay5_reset_device ( ctx );
    // Configure RL1, RL2, and RL3 pins as OUTPUT
    error_flag |= relay5_write_register ( ctx, RELAY5_REG_CONFIG, RELAY5_DEFAULT_CONFIG );
    error_flag |= relay5_set_relay1_open ( ctx );
    error_flag |= relay5_set_relay2_open ( ctx );
    error_flag |= relay5_set_relay3_open ( ctx );
    return error_flag;
}

err_t relay5_write_register ( relay5_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t relay5_read_register ( relay5_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t relay5_set_relay1_open ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( RELAY5_PIN_RL1 != ( reg_data & RELAY5_PIN_RL1 ) )
    {
        return RELAY5_OK;
    }
    reg_data &= ~RELAY5_PIN_RL1;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_set_relay1_close ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( reg_data & RELAY5_PIN_RL1 )
    {
        return RELAY5_OK;
    }
    reg_data |= RELAY5_PIN_RL1;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_switch_relay1 ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    reg_data ^= RELAY5_PIN_RL1;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_set_relay2_open ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( RELAY5_PIN_RL2 != ( reg_data & RELAY5_PIN_RL2 ) )
    {
        return RELAY5_OK;
    }
    reg_data &= ~RELAY5_PIN_RL2;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_set_relay2_close ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( reg_data & RELAY5_PIN_RL2 )
    {
        return RELAY5_OK;
    }
    reg_data |= RELAY5_PIN_RL2;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_switch_relay2 ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    reg_data ^= RELAY5_PIN_RL2;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_set_relay3_open ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( RELAY5_PIN_RL3 != ( reg_data & RELAY5_PIN_RL3 ) )
    {
        return RELAY5_OK;
    }
    reg_data &= ~RELAY5_PIN_RL3;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_set_relay3_close ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    if ( reg_data & RELAY5_PIN_RL3 )
    {
        return RELAY5_OK;
    }
    reg_data |= RELAY5_PIN_RL3;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

err_t relay5_switch_relay3 ( relay5_t *ctx )
{
    uint8_t reg_data = 0;
    if ( RELAY5_ERROR == relay5_read_register ( ctx, RELAY5_REG_OUTPUT, &reg_data ) )
    {
        return RELAY5_ERROR;
    }
    reg_data ^= RELAY5_PIN_RL3;
    return relay5_write_register ( ctx, RELAY5_REG_OUTPUT, reg_data );
}

void relay5_set_rst_pin ( relay5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void relay5_reset_device ( relay5_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

// ------------------------------------------------------------------------- END
