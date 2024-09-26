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
 * @file expand19.c
 * @brief Expand 19 Click Driver.
 */

#include "expand19.h"

void expand19_cfg_setup ( expand19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND19_DEVICE_ADDRESS_A1A0_11;
}

err_t expand19_init ( expand19_t *ctx, expand19_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t expand19_default_cfg ( expand19_t *ctx ) 
{
    err_t error_flag = EXPAND19_OK;
    expand19_reset_device ( ctx );
    error_flag |= expand19_set_pin_direction ( ctx, EXPAND19_OUTPUT_DIRECTION, EXPAND19_PIN_0_MASK | 
                                                                               EXPAND19_PIN_1_MASK | 
                                                                               EXPAND19_PIN_2_MASK | 
                                                                               EXPAND19_PIN_3_MASK );
    error_flag |= expand19_set_pin_direction ( ctx, EXPAND19_INPUT_DIRECTION, EXPAND19_PIN_4_MASK | 
                                                                              EXPAND19_PIN_5_MASK | 
                                                                              EXPAND19_PIN_6_MASK | 
                                                                              EXPAND19_PIN_7_MASK );
    error_flag |= expand19_set_all_pins_value ( ctx, EXPAND19_NO_PIN_MASK );
    error_flag |= expand19_write_register ( ctx, EXPAND19_REG_PULL_SELECTION, EXPAND19_ALL_PINS_MASK );
    error_flag |= expand19_write_register ( ctx, EXPAND19_REG_PULL_ENABLE, EXPAND19_PIN_4_MASK | 
                                                                           EXPAND19_PIN_5_MASK | 
                                                                           EXPAND19_PIN_6_MASK | 
                                                                           EXPAND19_PIN_7_MASK );
    return error_flag;
}

err_t expand19_write_register ( expand19_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t expand19_read_register ( expand19_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void expand19_set_rst_pin ( expand19_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void expand19_reset_device ( expand19_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t expand19_get_int_pin ( expand19_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t expand19_set_pin_direction ( expand19_t *ctx, uint8_t direction, uint8_t pin_mask )
{
    if ( direction > EXPAND19_INPUT_DIRECTION )
    {
        return EXPAND19_ERROR;
    }
    uint8_t port_value = 0;
    err_t error_flag = expand19_read_register ( ctx, EXPAND19_REG_CONFIG, &port_value );
    if ( EXPAND19_OUTPUT_DIRECTION == direction )
    {
        port_value &= ~pin_mask;
        error_flag |= expand19_write_register ( ctx, EXPAND19_REG_CONFIG, port_value );
    }
    else
    {
        port_value |= pin_mask;
        error_flag |= expand19_write_register ( ctx, EXPAND19_REG_CONFIG, port_value );
    }
    return error_flag;
}

err_t expand19_set_all_pins_direction ( expand19_t *ctx, uint8_t direction )
{
    if ( direction > EXPAND19_INPUT_DIRECTION )
    {
        return EXPAND19_ERROR;
    }
    err_t error_flag = EXPAND19_OK;
    if ( EXPAND19_OUTPUT_DIRECTION == direction )
    {
        error_flag |= expand19_write_register ( ctx, EXPAND19_REG_CONFIG, ~EXPAND19_ALL_PINS_MASK );
    }
    else
    {
        error_flag |= expand19_write_register ( ctx, EXPAND19_REG_CONFIG, EXPAND19_ALL_PINS_MASK );
    }
    return error_flag;
}

err_t expand19_set_pin_value ( expand19_t *ctx, uint8_t clr_mask, uint8_t set_mask )
{
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    err_t error_flag = expand19_read_register ( ctx, EXPAND19_REG_OUTPUT_PORT, &rx_data );
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    if ( rx_data != tx_data )
    {
        error_flag |= expand19_write_register ( ctx, EXPAND19_REG_OUTPUT_PORT, tx_data );
    }
    return error_flag;
}

err_t expand19_set_all_pins_value ( expand19_t *ctx, uint8_t set_mask )
{    
    return expand19_write_register ( ctx, EXPAND19_REG_OUTPUT_PORT, set_mask );
}

err_t expand19_read_port_value ( expand19_t *ctx, uint8_t *data_out )
{
    return expand19_read_register ( ctx, EXPAND19_REG_INPUT_PORT, data_out );
}

// ------------------------------------------------------------------------- END
