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
 * @file expand14.c
 * @brief Expand 14 Click Driver.
 */

#include "expand14.h"

void expand14_cfg_setup ( expand14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND14_DEVICE_ADDRESS_A2A1A0_000;
}

err_t expand14_init ( expand14_t *ctx, expand14_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t expand14_default_cfg ( expand14_t *ctx ) 
{
    err_t error_flag = EXPAND14_OK;
    error_flag |= expand14_set_pin_direction ( ctx, EXPAND14_OUTPUT_DIRECTION, EXPAND14_PORT_0, EXPAND14_ALL_PINS_MASK );
    error_flag |= expand14_set_pin_direction ( ctx, EXPAND14_INPUT_DIRECTION, EXPAND14_PORT_1, EXPAND14_ALL_PINS_MASK );
    error_flag |= expand14_set_all_pins_value ( ctx, EXPAND14_NO_PIN_MASK );
    return error_flag;
}

err_t expand14_generic_write ( expand14_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    if ( len > 6 )
    {
        return EXPAND14_ERROR;
    }
    uint8_t data_buf[ 7 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t expand14_generic_read ( expand14_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t expand14_write_register ( expand14_t *ctx, uint8_t reg, uint8_t data_in )
{
    return expand14_generic_write ( ctx, reg, &data_in, 1 );
}

err_t expand14_read_register ( expand14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return expand14_generic_read ( ctx, reg, data_out, 1 );
}

err_t expand14_set_pin_direction ( expand14_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask )
{
    if ( ( port > EXPAND14_PORT_1 ) || ( direction > EXPAND14_INPUT_DIRECTION ) )
    {
        return EXPAND14_ERROR;
    }
    uint8_t port_value = 0;
    err_t error_flag = expand14_read_register ( ctx, EXPAND14_REG_CONFIG_PORT_0 + port, &port_value );
    if ( EXPAND14_OUTPUT_DIRECTION == direction )
    {
        port_value &= ~pin_mask;
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_0 + port, port_value );
    }
    else
    {
        port_value |= pin_mask;
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_0 + port, port_value );
    }
    return error_flag;
}

err_t expand14_set_all_pins_direction ( expand14_t *ctx, uint8_t direction )
{
    if ( direction > EXPAND14_INPUT_DIRECTION )
    {
        return EXPAND14_ERROR;
    }
    err_t error_flag = EXPAND14_OK;
    if ( EXPAND14_OUTPUT_DIRECTION == direction )
    {
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_0, ~EXPAND14_ALL_PINS_MASK );
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_1, ~EXPAND14_ALL_PINS_MASK );
    }
    else
    {
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_0, EXPAND14_ALL_PINS_MASK );
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_CONFIG_PORT_1, EXPAND14_ALL_PINS_MASK );
    }
    return error_flag;
}

err_t expand14_set_pin_value ( expand14_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    if ( port > EXPAND14_PORT_1 )
    {
        return EXPAND14_ERROR;
    }
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    err_t error_flag = expand14_read_register ( ctx, EXPAND14_REG_OUTPUT_PORT_0 + port, &rx_data );
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    if ( rx_data != tx_data )
    {
        error_flag |= expand14_write_register ( ctx, EXPAND14_REG_OUTPUT_PORT_0 + port, tx_data );
    }
    return error_flag;
}

err_t expand14_set_all_pins_value ( expand14_t *ctx, uint8_t set_mask )
{    
    err_t error_flag = expand14_write_register ( ctx, EXPAND14_REG_OUTPUT_PORT_0, set_mask );
    error_flag |= expand14_write_register ( ctx, EXPAND14_REG_OUTPUT_PORT_1, set_mask );
    return error_flag;
}

err_t expand14_read_port_value ( expand14_t *ctx, uint8_t port, uint8_t *data_out )
{
    if ( port > EXPAND14_PORT_1 )
    {
        return EXPAND14_ERROR;
    }
    return expand14_read_register ( ctx, EXPAND14_REG_INPUT_PORT_0 + port, data_out );
}

uint8_t expand14_get_int_pin ( expand14_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
