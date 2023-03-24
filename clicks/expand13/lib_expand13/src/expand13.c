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
 * @file expand13.c
 * @brief Expand 13 Click Driver.
 */

#include "expand13.h"

void expand13_cfg_setup ( expand13_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND13_SET_DEV_ADDR_A2A1A0_000;
}

err_t expand13_init ( expand13_t *ctx, expand13_cfg_t *cfg ) 
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

void expand13_enable_device ( expand13_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void expand13_disable_device ( expand13_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

uint8_t expand13_get_int_pin ( expand13_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t expand13_write_all_ports ( expand13_t *ctx, uint8_t *ports )
{
    return i2c_master_write ( &ctx->i2c, ports, 6 );
}

err_t expand13_read_all_ports ( expand13_t *ctx, uint8_t *ports )
{
    return i2c_master_read ( &ctx->i2c, ports, 6 );
}

err_t expand13_set_port_value ( expand13_t *ctx, uint8_t port, uint8_t clr_mask, uint8_t set_mask )
{
    if ( port > EXPAND13_PORT_5 )
    {
        return EXPAND13_ERROR;
    }
    uint8_t ports_buf[ 6 ] = { 0 };
    uint8_t port_value = 0;
    
    err_t error_flag = expand13_read_all_ports ( ctx, ports_buf );
    port_value = ( ports_buf[ port ] & ~clr_mask ) | set_mask;

    if ( port_value != ports_buf[ port ] )
    {
        ports_buf[ port ] = port_value;
        error_flag |= expand13_write_all_ports ( ctx, ports_buf );
    }
    return error_flag;
}

err_t expand13_read_port_value ( expand13_t *ctx, uint8_t port, uint8_t *data_out )
{
    if ( port > EXPAND13_PORT_5 )
    {
        return EXPAND13_ERROR;
    }
    uint8_t rx_data[ 6 ] = { 0 };
    err_t error_flag = expand13_read_all_ports ( ctx, rx_data );
    *data_out = rx_data[ port ];
    return error_flag;
}

// ------------------------------------------------------------------------- END
