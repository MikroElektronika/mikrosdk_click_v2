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
 * @file rotaryswitch.c
 * @brief Rotary Switch Click Driver.
 */

#include "rotaryswitch.h"

void rotaryswitch_cfg_setup ( rotaryswitch_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ROTARYSWITCH_DEVICE_ADDRESS;
}

err_t rotaryswitch_init ( rotaryswitch_t *ctx, rotaryswitch_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t rotaryswitch_default_cfg ( rotaryswitch_t *ctx ) 
{
    err_t error_flag = ROTARYSWITCH_OK;
    // Set all pins as inverted inputs with internal pull-ups enabled
    error_flag |= rotaryswitch_write_reg ( ctx, ROTARYSWITCH_REG_CONFIG, ROTARYSWITCH_CONFIG_DEFAULT );
    error_flag |= rotaryswitch_write_reg ( ctx, ROTARYSWITCH_REG_POLARITY_INV, ROTARYSWITCH_POLARITY_INV_DEFAULT );
    error_flag |= rotaryswitch_write_reg ( ctx, ROTARYSWITCH_REG_SPECIAL_FUNC, ROTARYSWITCH_SPECIAL_FUNC_DEFAULT );
    return error_flag;
}

err_t rotaryswitch_write_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { reg, data_in };
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t rotaryswitch_read_reg ( rotaryswitch_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t rotaryswitch_get_position ( rotaryswitch_t *ctx, uint8_t *position )
{
    uint8_t reg_data = 0;
    err_t error_flag = rotaryswitch_read_reg( ctx, ROTARYSWITCH_REG_INPUT_PORT, &reg_data );
    if ( ( ROTARYSWITCH_OK == error_flag ) && ( NULL != position ) )
    {
        *position = reg_data & ROTARYSWITCH_ALL_PINS_MASK;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
