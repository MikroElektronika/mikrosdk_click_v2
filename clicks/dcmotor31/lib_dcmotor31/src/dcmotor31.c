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
 * @file dcmotor31.c
 * @brief DC Motor 31 Click Driver.
 */

#include "dcmotor31.h"

void dcmotor31_cfg_setup ( dcmotor31_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->sleep = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->pha = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DCMOTOR31_DEVICE_ADDRESS_A1A0_00;
}

err_t dcmotor31_init ( dcmotor31_t *ctx, dcmotor31_cfg_t *cfg ) 
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

    digital_out_init( &ctx->sleep, cfg->sleep );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->pha, cfg->pha );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t dcmotor31_default_cfg ( dcmotor31_t *ctx ) 
{
    err_t error_flag = DCMOTOR31_OK;
    
    error_flag |= dcmotor31_write_reg ( ctx, DCMOTOR31_REG_CONFIG, DCMOTOR31_DEFAULT_CONFIG );
    dcmotor31_exit_sleep ( ctx );
    dcmotor31_enable_device ( ctx );
    dcmotor31_disable_output ( ctx );
    dcmotor31_set_reverse_dir ( ctx );
    error_flag |= dcmotor31_set_torque ( ctx, DCMOTOR31_TORQUE_51 );

    return error_flag;
}

err_t dcmotor31_write_reg ( dcmotor31_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t dcmotor31_read_reg ( dcmotor31_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void dcmotor31_enter_sleep ( dcmotor31_t *ctx )
{
    digital_out_low ( &ctx->sleep );
}

void dcmotor31_exit_sleep ( dcmotor31_t *ctx )
{
    digital_out_high ( &ctx->sleep );
}

void dcmotor31_enable_device ( dcmotor31_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void dcmotor31_disable_device ( dcmotor31_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void dcmotor31_enable_output ( dcmotor31_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void dcmotor31_disable_output ( dcmotor31_t *ctx )
{
    digital_out_low ( &ctx->en );
}

void dcmotor31_set_forward_dir ( dcmotor31_t *ctx )
{
    digital_out_high ( &ctx->pha );
}

void dcmotor31_set_reverse_dir ( dcmotor31_t *ctx )
{
    digital_out_low ( &ctx->pha );
}

uint8_t dcmotor31_get_int_pin ( dcmotor31_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t dcmotor31_get_lo_pin ( dcmotor31_t *ctx, uint8_t *state )
{
    uint8_t reg_data = 0;
    if ( DCMOTOR31_ERROR == dcmotor31_read_reg ( ctx, DCMOTOR31_REG_INPUT, &reg_data ) )
    {
        return DCMOTOR31_ERROR;
    }
    *state = reg_data & DCMOTOR31_PIN_LO;
    return DCMOTOR31_OK;
}

err_t dcmotor31_set_torque ( dcmotor31_t *ctx, uint8_t torque )
{
    uint8_t reg_data = 0;
    if ( torque > DCMOTOR31_TORQUE_100 )
    {
        return DCMOTOR31_ERROR;
    }
    if ( DCMOTOR31_ERROR == dcmotor31_read_reg ( ctx, DCMOTOR31_REG_OUTPUT, &reg_data ) )
    {
        return DCMOTOR31_ERROR;
    }
    if ( torque == ( ( reg_data & DCMOTOR31_PINS_TRQ ) >> 1 ) )
    {
        return DCMOTOR31_OK;
    }
    reg_data &= ( ~DCMOTOR31_PINS_TRQ );
    reg_data |= ( torque << 1 );
    return dcmotor31_write_reg ( ctx, DCMOTOR31_REG_OUTPUT, reg_data );
}

void dcmotor31_set_mode ( dcmotor31_t *ctx, uint8_t mode )
{
    switch ( mode )
    {
        case DCMOTOR31_MODE_BRAKE:
        {
            dcmotor31_disable_output ( ctx );
            break;
        }
        case DCMOTOR31_MODE_FORWARD:
        {
            dcmotor31_enable_output ( ctx );
            dcmotor31_set_forward_dir ( ctx );
            break;
        }
        case DCMOTOR31_MODE_REVERSE:
        {
            dcmotor31_enable_output ( ctx );
            dcmotor31_set_reverse_dir ( ctx );
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------- END
