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
 * @file expand11.c
 * @brief Expand 11 Click Driver.
 */

#include "expand11.h"

void expand11_cfg_setup ( expand11_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND11_DEVICE_ADDRESS;
}

err_t expand11_init ( expand11_t *ctx, expand11_cfg_t *cfg ) 
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

err_t expand11_default_cfg ( expand11_t *ctx ) 
{
    err_t error_flag = EXPAND11_OK;
    error_flag |= expand11_set_pin_direction ( ctx, EXPAND11_OUTPUT_DIRECTION, 
                                               EXPAND11_PIN_0_MASK | EXPAND11_PIN_1_MASK );
    error_flag |= expand11_set_pin_direction ( ctx, EXPAND11_INPUT_DIRECTION, 
                                               EXPAND11_PIN_2_MASK | EXPAND11_PIN_3_MASK );
    error_flag |= expand11_set_all_pins_value ( ctx, EXPAND11_NO_PIN_MASK );
    error_flag |= expand11_set_p3_function ( ctx, EXPAND11_P3_AS_P3 );
    error_flag |= expand11_enable_pull_up ( ctx );
    return error_flag;
}

err_t expand11_write_register ( expand11_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t expand11_read_register ( expand11_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t expand11_set_pin_direction ( expand11_t *ctx, uint8_t direction, uint8_t pin_mask )
{
    if ( ( pin_mask > EXPAND11_ALL_PINS_MASK ) || ( direction > EXPAND11_INPUT_DIRECTION ) )
    {
        return EXPAND11_ERROR;
    }
    uint8_t config = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_CONFIG, &config );
    if ( EXPAND11_OUTPUT_DIRECTION == direction )
    {
        config &= ~pin_mask;
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_CONFIG, config );
    }
    else
    {
        config |= pin_mask;
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_CONFIG, config );
    }
    return error_flag;
}

err_t expand11_set_all_pins_direction ( expand11_t *ctx, uint8_t direction )
{
    if ( direction > EXPAND11_INPUT_DIRECTION )
    {
        return EXPAND11_ERROR;
    }
    err_t error_flag = EXPAND11_OK;
    if ( EXPAND11_OUTPUT_DIRECTION == direction )
    {
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_CONFIG, EXPAND11_NO_PIN_MASK );
    }
    else
    {
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_CONFIG, EXPAND11_ALL_PINS_MASK );
    }
    return error_flag;
}

err_t expand11_set_pin_polarity ( expand11_t *ctx, uint8_t polarity, uint8_t pin_mask )
{
    if ( ( pin_mask > EXPAND11_ALL_PINS_MASK ) || ( polarity > EXPAND11_POLARITY_INV ) )
    {
        return EXPAND11_ERROR;
    }
    uint8_t config = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_POLARITY_INV, &config );
    if ( EXPAND11_POLARITY_NO_INV == polarity )
    {
        config &= ~pin_mask;
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_POLARITY_INV, config );
    }
    else
    {
        config |= pin_mask;
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_POLARITY_INV, config );
    }
    return error_flag;
}

err_t expand11_set_all_pins_polarity ( expand11_t *ctx, uint8_t polarity )
{
    if ( polarity > EXPAND11_POLARITY_INV )
    {
        return EXPAND11_ERROR;
    }
    err_t error_flag = EXPAND11_OK;
    if ( EXPAND11_POLARITY_NO_INV == polarity )
    {
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_POLARITY_INV, EXPAND11_NO_PIN_MASK );
    }
    else
    {
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_POLARITY_INV, EXPAND11_ALL_PINS_MASK );
    }
    return error_flag;
}

err_t expand11_set_pin_value ( expand11_t *ctx, uint8_t clr_mask, uint8_t set_mask )
{
    if ( ( clr_mask > EXPAND11_ALL_PINS_MASK ) || ( set_mask > EXPAND11_ALL_PINS_MASK ) )
    {
        return EXPAND11_ERROR;
    }
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_OUTPUT_PORT, &rx_data );
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    if ( rx_data != tx_data )
    {
        error_flag |= expand11_write_register ( ctx, EXPAND11_REG_OUTPUT_PORT, tx_data );
    }
    return error_flag;
}

err_t expand11_set_all_pins_value ( expand11_t *ctx, uint8_t set_mask )
{
    if ( set_mask > EXPAND11_ALL_PINS_MASK )
    {
        return EXPAND11_ERROR;
    }
    return expand11_write_register ( ctx, EXPAND11_REG_OUTPUT_PORT, set_mask );
}

err_t expand11_read_port_value ( expand11_t *ctx, uint8_t *data_out )
{
    if ( NULL == data_out )
    {
        return EXPAND11_ERROR;
    }
    uint8_t rx_data = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_INPUT_PORT, &rx_data );
    *data_out = rx_data & EXPAND11_ALL_PINS_MASK;
    return error_flag;
}

err_t expand11_set_p3_function ( expand11_t *ctx, uint8_t p3_func )
{
    if ( p3_func > EXPAND11_P3_AS_INT )
    {
        return EXPAND11_ERROR;
    }
    uint8_t spec_func = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, &spec_func );
    spec_func &= ~EXPAND11_SPECIAL_FUNC_P3_AS_INT;
    spec_func |= ( p3_func << 7 );
    error_flag |= expand11_write_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, spec_func );
    return error_flag;
}

err_t expand11_disable_pull_up ( expand11_t *ctx )
{
    uint8_t spec_func = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, &spec_func );
    spec_func |= EXPAND11_SPECIAL_FUNC_PU_DISABLED;
    error_flag |= expand11_write_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, spec_func );
    return error_flag;
}

err_t expand11_enable_pull_up ( expand11_t *ctx )
{
    uint8_t spec_func = 0;
    err_t error_flag = expand11_read_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, &spec_func );
    spec_func &= ~EXPAND11_SPECIAL_FUNC_PU_DISABLED;
    error_flag |= expand11_write_register ( ctx, EXPAND11_REG_SPECIAL_FUNC, spec_func );
    return error_flag;
}

uint8_t expand11_get_int_pin ( expand11_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
