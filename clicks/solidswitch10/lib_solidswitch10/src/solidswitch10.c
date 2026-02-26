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
 * @file solidswitch10.c
 * @brief SolidSwitch 10 Click Driver.
 */

#include "solidswitch10.h"

void solidswitch10_cfg_setup ( solidswitch10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->in_pin = HAL_PIN_NC;
    cfg->ovt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = SOLIDSWITCH10_DEVICE_ADDRESS;
}

err_t solidswitch10_init ( solidswitch10_t *ctx, solidswitch10_cfg_t *cfg ) 
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

    digital_out_init( &ctx->in_pin, cfg->in_pin );

    digital_in_init( &ctx->ovt, cfg->ovt );

    return I2C_MASTER_SUCCESS;
}

err_t solidswitch10_default_cfg ( solidswitch10_t *ctx ) 
{
    err_t error_flag = SOLIDSWITCH10_OK;

    error_flag |= solidswitch10_write_reg ( ctx, SOLIDSWITCH10_REG_CONFIG, SOLIDSWITCH10_DEFAULT_CONFIG );
    solidswitch10_disable_output ( ctx );

    error_flag |= solidswitch10_set_ilimit ( ctx, SOLIDSWITCH10_ILIMIT_4A );

    return error_flag;
}

err_t solidswitch10_write_reg ( solidswitch10_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t solidswitch10_read_reg ( solidswitch10_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

void solidswitch10_enable_output ( solidswitch10_t *ctx )
{
    digital_out_high ( &ctx->in_pin );
}

void solidswitch10_disable_output ( solidswitch10_t *ctx )
{
    digital_out_low ( &ctx->in_pin );
}

uint8_t solidswitch10_get_ovt_pin ( solidswitch10_t *ctx )
{
    return digital_in_read ( &ctx->ovt );
}

err_t solidswitch10_set_ilimit ( solidswitch10_t *ctx, uint8_t ilimit )
{
    if ( ilimit > SOLIDSWITCH10_ILIMIT_25A )
    {
        return SOLIDSWITCH10_ERROR;
    }
    return solidswitch10_write_reg( ctx, SOLIDSWITCH10_REG_OUTPUT, ( SOLIDSWITCH10_ILIMIT_25A - ilimit ) );
}

// ------------------------------------------------------------------------- END
