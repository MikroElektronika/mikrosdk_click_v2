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
 * @file button3.c
 * @brief Button 3 Click Driver.
 */

#include "button3.h"

void button3_cfg_setup ( button3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUTTON3_DEVICE_ADDRESS_0;
}

err_t button3_init ( button3_t *ctx, button3_cfg_t *cfg ) 
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

err_t button3_default_cfg ( button3_t *ctx ) 
{
    err_t error_flag = BUTTON3_OK;
    button3_reset_device ( ctx );
    // Configure RK, GK, and BK pins as OUTPUT, others as INPUT
    error_flag |= button3_write_reg ( ctx, BUTTON3_REG_CONFIG, BUTTON3_DEFAULT_PIN_CONFIG );
    error_flag |= button3_disable_red_led ( ctx );
    error_flag |= button3_disable_green_led ( ctx );
    error_flag |= button3_disable_blue_led ( ctx );
    return error_flag;
}

err_t button3_write_reg ( button3_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t button3_read_reg ( button3_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void button3_reset_device ( button3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void button3_set_rst_pin ( button3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t button3_get_int_pin ( button3_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t button3_get_red_button ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_INPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_RED_BUTTON ) >> 0;
    return BUTTON3_OK;
}

err_t button3_get_green_button ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_INPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_GREEN_BUTTON ) >> 2;
    return BUTTON3_OK;
}

err_t button3_get_blue_button ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_INPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_BLUE_BUTTON ) >> 5;
    return BUTTON3_OK;
}

err_t button3_get_red_led ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_RED_LED ) >> 1;
    return BUTTON3_OK;
}

err_t button3_get_green_led ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_GREEN_LED ) >> 3;
    return BUTTON3_OK;
}

err_t button3_get_blue_led ( button3_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    *state = ( reg_data & BUTTON3_PIN_BLUE_LED ) >> 4;
    return BUTTON3_OK;
}

err_t button3_enable_red_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_RED_LED != ( reg_data & BUTTON3_PIN_RED_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data &= ~BUTTON3_PIN_RED_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_enable_green_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_GREEN_LED != ( reg_data & BUTTON3_PIN_GREEN_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data &= ~BUTTON3_PIN_GREEN_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_enable_blue_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_BLUE_LED != ( reg_data & BUTTON3_PIN_BLUE_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data &= ~BUTTON3_PIN_BLUE_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_disable_red_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_RED_LED == ( reg_data & BUTTON3_PIN_RED_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data |= BUTTON3_PIN_RED_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_disable_green_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_GREEN_LED == ( reg_data & BUTTON3_PIN_GREEN_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data |= BUTTON3_PIN_GREEN_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_disable_blue_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_BLUE_LED == ( reg_data & BUTTON3_PIN_BLUE_LED ) )
    {
        return BUTTON3_OK;
    }
    reg_data |= BUTTON3_PIN_BLUE_LED;
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_toggle_red_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_RED_LED == ( reg_data & BUTTON3_PIN_RED_LED ) )
    {
        reg_data &= ~BUTTON3_PIN_RED_LED;
    }
    else
    {
        reg_data |= BUTTON3_PIN_RED_LED;
    }
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_toggle_green_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_GREEN_LED == ( reg_data & BUTTON3_PIN_GREEN_LED ) )
    {
        reg_data &= ~BUTTON3_PIN_GREEN_LED;
    }
    else
    {
        reg_data |= BUTTON3_PIN_GREEN_LED;
    }
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

err_t button3_toggle_blue_led ( button3_t *ctx )
{
    uint8_t reg_data = 0;
    if ( BUTTON3_ERROR == button3_read_reg ( ctx, BUTTON3_REG_OUTPUT, &reg_data ) )
    {
        return BUTTON3_ERROR;
    }
    if ( BUTTON3_PIN_BLUE_LED == ( reg_data & BUTTON3_PIN_BLUE_LED ) )
    {
        reg_data &= ~BUTTON3_PIN_BLUE_LED;
    }
    else
    {
        reg_data |= BUTTON3_PIN_BLUE_LED;
    }
    return button3_write_reg ( ctx, BUTTON3_REG_OUTPUT, reg_data );
}

// ------------------------------------------------------------------------- END
