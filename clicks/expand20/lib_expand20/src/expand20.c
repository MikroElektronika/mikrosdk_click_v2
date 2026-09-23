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
 * @file expand20.c
 * @brief Expand 20 Click Driver.
 */

#include "expand20.h"

void expand20_cfg_setup ( expand20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND20_DEVICE_ADDRESS;
}

err_t expand20_init ( expand20_t *ctx, expand20_cfg_t *cfg ) 
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

    digital_out_high( &ctx->rst );

    return I2C_MASTER_SUCCESS;
}

err_t expand20_default_cfg ( expand20_t *ctx ) 
{
    err_t error_flag = EXPAND20_OK;
    
    expand20_reset_device ( ctx );

    /* Set all Port 0 pins as output pins */
    error_flag |= expand20_set_pin_direction ( ctx, EXPAND20_PORT_0, EXPAND20_OUTPUT_DIRECTION, EXPAND20_ALL_PINS_MASK );

    /* Set all Port 1 pins as input pins */
    error_flag |= expand20_set_pin_direction ( ctx, EXPAND20_PORT_1, EXPAND20_INPUT_DIRECTION, EXPAND20_ALL_PINS_MASK );

    /* Drive all Port 0 output pins low */
    error_flag |= expand20_set_port_value ( ctx, EXPAND20_PORT_0, EXPAND20_PINS_LOW );

    return error_flag;
}

err_t expand20_write_reg ( expand20_t *ctx, uint8_t cmd, uint8_t data_in ) 
{
    return expand20_write_regs( ctx, cmd, &data_in, 1 );
}

err_t expand20_write_regs ( expand20_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len ) 
{
    /* Write frame : S | addr + W | A | command byte | A | data_byte_0 | A | .... data_byte_N | A | P */
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = cmd;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t expand20_read_reg ( expand20_t *ctx, uint8_t cmd, uint8_t *data_out ) 
{
    return expand20_read_regs( ctx, cmd, data_out, 1 );
}

err_t expand20_read_regs ( expand20_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len ) 
{
    /* Read frame : S | addr + W | A | command byte | A | RS | addr + R | A | data_byte_0 | A | ... data_byte_N | NA | P */
    return i2c_master_write_then_read( &ctx->i2c, &cmd, 1, data_out, len );
}

void expand20_set_rst_pin ( expand20_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void expand20_reset_device ( expand20_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t expand20_get_int_pin ( expand20_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t expand20_set_pin_direction ( expand20_t *ctx, uint8_t port, uint8_t direction, uint8_t pin_mask )
{
    /* Reject an invalid port or direction value */
    if ( ( EXPAND20_PORT_1 < port ) || ( EXPAND20_INPUT_DIRECTION < direction ) )
    {
        return EXPAND20_ERROR;
    }

    /* Port registers are in consecutive pairs : configuration port 0(06h) then configuration port 1(07h) */
    uint8_t cmd = EXPAND20_CMD_CONFIG_0 + port;
    uint8_t port_value = 0;

    /* Perform a read-modify-write so untouched pins keep their setting  */
    err_t error_flag = expand20_read_reg ( ctx, cmd, &port_value );

    if ( EXPAND20_OUTPUT_DIRECTION == direction )
    {
        port_value &= ~pin_mask;
    }
    else
    {
        port_value |= pin_mask;
    }

    error_flag |= expand20_write_reg ( ctx, cmd, port_value );

    return error_flag;
}

err_t expand20_set_all_pins_direction ( expand20_t *ctx, uint8_t direction )
{
    /* Reject an invalid direction value */
    if ( EXPAND20_INPUT_DIRECTION < direction )
    {
        return EXPAND20_ERROR;
    }

    uint8_t data_buf[ 2 ] = { 0 };

    if ( EXPAND20_OUTPUT_DIRECTION == direction )
    {
        data_buf[ 0 ] = EXPAND20_OUTPUT_PINS;
        data_buf[ 1 ] = EXPAND20_OUTPUT_PINS;
    }
    else
    {
        data_buf[ 0 ] = EXPAND20_INPUT_PINS;
        data_buf[ 1 ] = EXPAND20_INPUT_PINS;
    }

    /* Autoincrement -> will automatically write to config port 1 after config port 0 */
    return expand20_write_regs ( ctx, EXPAND20_CMD_CONFIG_0, data_buf, 2 );
}

err_t expand20_set_pin_value ( expand20_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    /* Reject an invalid port value. */
    if ( EXPAND20_PORT_1 < port )
    {
        return EXPAND20_ERROR;
    }

    /* Port registers are in consecutive pairs : Output port 0(02h) then Output port 1(03h) */
    uint8_t cmd = EXPAND20_CMD_OUTPUT_PORT_0 + port;
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;

    /* Perform a read-modify-write so pins outside the masks are preserved. */
    err_t error_flag = expand20_read_reg ( ctx, cmd, &rx_data );

    tx_data = ( rx_data & ~clr_mask ) | set_mask;

    if ( rx_data != tx_data )
    {
        error_flag |= expand20_write_reg ( ctx, cmd, tx_data );
    }

    return error_flag;
}

err_t expand20_set_port_value ( expand20_t *ctx, uint8_t port, uint8_t set_mask )
{
    /* Reject an invalid port value. */
    if ( EXPAND20_PORT_1 < port )
    {
        return EXPAND20_ERROR;
    }

    /* Port registers are in consecutive pairs : Output port 0(02h) then Output port 1(03h) */
    uint8_t cmd = EXPAND20_CMD_OUTPUT_PORT_0 + port;

    /* Set the value of all output pins on the selected port */
    return expand20_write_reg ( ctx, cmd, set_mask );
}

err_t expand20_read_port_value ( expand20_t *ctx, uint8_t port, uint8_t *data_out )
{
    /* Reject an invalid port value. */
    if ( EXPAND20_PORT_1 < port )
    {
        return EXPAND20_ERROR;
    }

    /* Port registers are in consecutive pairs : Input port 0 register(00h) then Input port 1 register(01h) */
    uint8_t cmd = EXPAND20_CMD_INPUT_PORT_0 + port;

    return expand20_read_reg ( ctx, cmd, data_out );
}

// ------------------------------------------------------------------------- END
