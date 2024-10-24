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
 * @file expand17.c
 * @brief Expand 17 Click Driver.
 */

#include "expand17.h"

void expand17_cfg_setup ( expand17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = EXPAND17_DEVICE_ADDRESS_0;
}

err_t expand17_init ( expand17_t *ctx, expand17_cfg_t *cfg ) 
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

    expand17_set_rst_pin( ctx, EXPAND17_PIN_STATE_HIGH );

    return I2C_MASTER_SUCCESS;
}

err_t expand17_default_cfg ( expand17_t *ctx ) 
{
    err_t error_flag = EXPAND17_OK;
    
    expand17_hw_reset( ctx );

    error_flag |= expand17_set_io_dir( ctx, EXPAND17_IO_1_PIN_MASK | EXPAND17_IO_2_PIN_MASK | EXPAND17_IO_3_PIN_MASK | EXPAND17_IO_4_PIN_MASK, 
                                            EXPAND17_IO_5_PIN_MASK | EXPAND17_IO_6_PIN_MASK | EXPAND17_IO_7_PIN_MASK | EXPAND17_IO_8_PIN_MASK );
    
    return error_flag;
}

err_t expand17_generic_write ( expand17_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t expand17_generic_read ( expand17_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void expand17_set_rst_pin ( expand17_t *ctx, uint8_t pin_state )
{
    if ( EXPAND17_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

uint8_t expand17_get_int_pin ( expand17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

void expand17_hw_reset ( expand17_t *ctx )
{
    expand17_set_rst_pin( ctx, EXPAND17_PIN_STATE_LOW );
    Delay_10ms();
    expand17_set_rst_pin( ctx, EXPAND17_PIN_STATE_HIGH );
    Delay_10ms();
}

err_t expand17_set_io_dir ( expand17_t *ctx, uint8_t input_pins, uint8_t output_pins )
{
    err_t error_flag = EXPAND17_OK;
    uint8_t tmp_data = 0;

    error_flag |= expand17_generic_read( ctx, EXPAND17_REG_CONFIGURATION, &tmp_data, 1 );
    tmp_data = ~output_pins | input_pins;
    error_flag |= expand17_generic_write( ctx, EXPAND17_REG_CONFIGURATION, &tmp_data, 1 );

    return error_flag;
}

err_t expand17_set_output_state ( expand17_t *ctx, uint8_t clr_mask, uint8_t set_mask )
{
    err_t error_flag = EXPAND17_OK;
    uint8_t tmp_data = 0;

    error_flag |= expand17_generic_read( ctx, EXPAND17_REG_OUTPUT_PORT, &tmp_data, 1 );
    tmp_data = ~clr_mask | set_mask;
    error_flag |= expand17_generic_write( ctx, EXPAND17_REG_OUTPUT_PORT, &tmp_data, 1 );

    return error_flag;
}

err_t expand17_get_input_state ( expand17_t *ctx, uint8_t *input_state )
{
    err_t error_flag = EXPAND17_OK;

    error_flag |= expand17_generic_read( ctx, EXPAND17_REG_INPUT_PORT, input_state, 1 );

    return error_flag;
}

// ------------------------------------------------------------------------- END
