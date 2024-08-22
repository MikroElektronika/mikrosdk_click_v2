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
 * @file joystick4.c
 * @brief Joystick 4 Click Driver.
 */

#include "joystick4.h"

void joystick4_cfg_setup ( joystick4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = JOYSTICK4_DEVICE_ADDRESS_0;
}

err_t joystick4_init ( joystick4_t *ctx, joystick4_cfg_t *cfg ) 
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

err_t joystick4_default_cfg ( joystick4_t *ctx ) 
{
    joystick4_reset_device ( ctx );
    // Configure all pins as INPUT
    return joystick4_write_reg ( ctx, JOYSTICK4_REG_CONFIG, JOYSTICK4_DEFAULT_PIN_CONFIG );
}

err_t joystick4_write_reg ( joystick4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t joystick4_read_reg ( joystick4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void joystick4_reset_device ( joystick4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void joystick4_set_rst_pin ( joystick4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t joystick4_get_int_pin ( joystick4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t joystick4_get_pins ( joystick4_t *ctx, uint8_t *pin_mask )
{
    return joystick4_read_reg ( ctx, JOYSTICK4_REG_INPUT, pin_mask );
}

uint8_t joystick4_get_position ( uint8_t pin_mask )
{
    uint8_t position = JOYSTICK4_POSITION_IDLE;
    if ( JOYSTICK4_PIN_CE != ( pin_mask & JOYSTICK4_PIN_CE ) )
    {
        if ( JOYSTICK4_PIN_A != ( pin_mask & JOYSTICK4_PIN_A ) )
        {
            position = JOYSTICK4_POSITION_CENTER_UP;
        }
        else if ( JOYSTICK4_PIN_B != ( pin_mask & JOYSTICK4_PIN_B ) )
        {
            position = JOYSTICK4_POSITION_CENTER_RIGHT;
        }
        else if ( JOYSTICK4_PIN_C != ( pin_mask & JOYSTICK4_PIN_C ) )
        {
            position = JOYSTICK4_POSITION_CENTER_LEFT;
        }
        else if ( JOYSTICK4_PIN_D != ( pin_mask & JOYSTICK4_PIN_D ) )
        {
            position = JOYSTICK4_POSITION_CENTER_DOWN;
        }
        else
        {
            position = JOYSTICK4_POSITION_CENTER;
        }
    }
    else if ( JOYSTICK4_PIN_A != ( pin_mask & JOYSTICK4_PIN_A ) )
    {
        if ( JOYSTICK4_PIN_B != ( pin_mask & JOYSTICK4_PIN_B ) )
        {
            position = JOYSTICK4_POSITION_UPPER_RIGHT;
        }
        else if ( JOYSTICK4_PIN_C != ( pin_mask & JOYSTICK4_PIN_C ) )
        {
            position = JOYSTICK4_POSITION_UPPER_LEFT;
        }
        else
        {
            position = JOYSTICK4_POSITION_UP;
        }
    }
    else if ( JOYSTICK4_PIN_B != ( pin_mask & JOYSTICK4_PIN_B ) )
    {
        if ( JOYSTICK4_PIN_D != ( pin_mask & JOYSTICK4_PIN_D ) )
        {
            position = JOYSTICK4_POSITION_LOWER_RIGHT;
        }
        else
        {
            position = JOYSTICK4_POSITION_RIGHT;
        }
    }
    else if ( JOYSTICK4_PIN_C != ( pin_mask & JOYSTICK4_PIN_C ) )
    {
        if ( JOYSTICK4_PIN_D != ( pin_mask & JOYSTICK4_PIN_D ) )
        {
            position = JOYSTICK4_POSITION_LOWER_LEFT;
        }
        else
        {
            position = JOYSTICK4_POSITION_LEFT;
        }
    }
    else if ( JOYSTICK4_PIN_D != ( pin_mask & JOYSTICK4_PIN_D ) )
    {
        position = JOYSTICK4_POSITION_DOWN;
    }
    return position;
}

// ------------------------------------------------------------------------- END
