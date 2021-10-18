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
 * @file expand10.c
 * @brief Expand 10 Click Driver.
 */

#include "expand10.h"

void expand10_cfg_setup ( expand10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND10_SET_DEV_ADDR_0;
}

err_t expand10_init ( expand10_t *ctx, expand10_cfg_t *cfg ) 
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

err_t expand10_default_cfg ( expand10_t *ctx ) 
{
    // Click default configuration.
    expand10_set_rst_pin ( ctx, EXPAND10_PIN_HIGH_LEVEL );
    Delay_10ms( );
    
    err_t error_flag = expand10_software_reset ( ctx );
    Delay_10ms( );
    
    error_flag |= expand10_check_device_id ( ctx );
    
    error_flag |= expand10_set_pin_direction ( ctx, EXPAND10_OUTPUT_DIRECTION, EXPAND10_PORT_0, EXPAND10_ALL_PINS_MASK );
    error_flag |= expand10_set_pin_direction ( ctx, EXPAND10_OUTPUT_DIRECTION, EXPAND10_PORT_1, EXPAND10_ALL_PINS_MASK );
    error_flag |= expand10_set_pin_direction ( ctx, EXPAND10_INPUT_DIRECTION, EXPAND10_PORT_2, EXPAND10_ALL_PINS_MASK );
    error_flag |= expand10_set_all_pins_value ( ctx, EXPAND10_NO_PIN_MASK );
    error_flag |= expand10_write_register ( ctx, EXPAND10_REG_PULL_SELECTION_P2, EXPAND10_NO_PIN_MASK );
    error_flag |= expand10_write_register ( ctx, EXPAND10_REG_PULL_ENABLE_P2, EXPAND10_ALL_PINS_MASK );
    
    return error_flag;
}

err_t expand10_generic_write ( expand10_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 7 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t expand10_generic_read ( expand10_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

void expand10_set_rst_pin ( expand10_t *ctx, uint8_t logic_level )
{
    digital_out_write ( &ctx->rst, logic_level );
}

uint8_t expand10_get_int_pin ( expand10_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t expand10_write_register ( expand10_t *ctx, uint8_t reg, uint8_t data_in )
{
    return expand10_generic_write ( ctx, reg, &data_in, 1 );
}

err_t expand10_read_register ( expand10_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return expand10_generic_read ( ctx, reg, data_out, 1 );
}

err_t expand10_check_device_id ( expand10_t *ctx )
{
    uint8_t rx_buf[ 3 ] = { 0 };
    uint32_t device_id = 0;
    
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, EXPAND10_DEV_ID_ADDR );
    
    error_flag |= expand10_generic_read ( ctx, ctx->slave_address << 1, rx_buf, 3 );
    
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    device_id = ( uint32_t ) rx_buf[ 0 ] << 16;
    device_id |= ( uint32_t ) rx_buf[ 1 ] << 8;
    device_id |= ( uint32_t ) rx_buf[ 2 ];
    
    if ( ( EXPAND10_DEVICE_ID != device_id ) || ( EXPAND10_OK != error_flag ) )
    {
        return EXPAND10_ERROR;
    }
    
    return EXPAND10_OK;
}

err_t expand10_software_reset ( expand10_t *ctx )
{
    err_t error_flag = i2c_master_set_slave_address( &ctx->i2c, EXPAND10_GEN_CALL_ADDR );
    
    error_flag |= expand10_generic_write ( ctx, EXPAND10_SOFTWARE_RESET, 0, 0 );
    
    error_flag |= i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    
    return error_flag;
}

err_t expand10_set_pin_direction ( expand10_t *ctx, uint8_t direction, uint8_t port, uint8_t pin_mask )
{
    if ( ( port > EXPAND10_PORT_2 ) || ( direction > EXPAND10_INPUT_DIRECTION ) )
    {
        return EXPAND10_ERROR;
    }
    
    uint8_t port_value = 0;
    err_t error_flag = expand10_read_register ( ctx, EXPAND10_REG_CONFIG_P0 + port, &port_value );
    
    if ( EXPAND10_OUTPUT_DIRECTION == direction )
    {
        port_value &= ~pin_mask;
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P0 + port, port_value );
    }
    else
    {
        port_value |= pin_mask;
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P0 + port, port_value );
    }
    
    return error_flag;
}

err_t expand10_set_all_pins_direction ( expand10_t *ctx, uint8_t direction )
{
    if ( direction > EXPAND10_INPUT_DIRECTION )
    {
        return EXPAND10_ERROR;
    }
    
    err_t error_flag = EXPAND10_OK;
    
    if ( EXPAND10_OUTPUT_DIRECTION == direction )
    {
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P0, ~EXPAND10_ALL_PINS_MASK );
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P1, ~EXPAND10_ALL_PINS_MASK );
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P2, ~EXPAND10_ALL_PINS_MASK );
    }
    else
    {
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P0, EXPAND10_ALL_PINS_MASK );
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P1, EXPAND10_ALL_PINS_MASK );
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_CONFIG_P2, EXPAND10_ALL_PINS_MASK );
    }
    
    return error_flag;
}

err_t expand10_set_pin_value ( expand10_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    if ( port > EXPAND10_PORT_2 )
    {
        return EXPAND10_ERROR;
    }
    
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    
    err_t error_flag = expand10_read_register ( ctx, EXPAND10_REG_OUTPUT_P0 + port, &rx_data );
    
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    
    if ( rx_data != tx_data )
    {
        error_flag |= expand10_write_register ( ctx, EXPAND10_REG_OUTPUT_P0 + port, tx_data );
    }
    
    return error_flag;
}

err_t expand10_set_all_pins_value ( expand10_t *ctx, uint8_t set_mask )
{    
    err_t error_flag = expand10_write_register ( ctx, EXPAND10_REG_OUTPUT_P0, set_mask );
    error_flag |= expand10_write_register ( ctx, EXPAND10_REG_OUTPUT_P1, set_mask );
    error_flag |= expand10_write_register ( ctx, EXPAND10_REG_OUTPUT_P2, set_mask );
    
    return error_flag;
}

err_t expand10_read_port_value ( expand10_t *ctx, uint8_t port, uint8_t *data_out )
{
    if ( port > EXPAND10_PORT_2 )
    {
        return EXPAND10_ERROR;
    }
    
    return expand10_read_register ( ctx, EXPAND10_REG_INPUT_P0 + port, data_out );
}

// ------------------------------------------------------------------------- END
