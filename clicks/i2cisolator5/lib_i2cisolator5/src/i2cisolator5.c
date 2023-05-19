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
 * @file i2cisolator5.c
 * @brief I2C Isolator 5 Click Driver.
 */

#include "i2cisolator5.h"

void i2cisolator5_cfg_setup ( i2cisolator5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->otb = HAL_PIN_NC;
    cfg->ota = HAL_PIN_NC;
    cfg->ina = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = I2CISOLATOR5_DEVICE_ADDRESS;
}

err_t i2cisolator5_init ( i2cisolator5_t *ctx, i2cisolator5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->otb, cfg->otb );
    digital_out_init( &ctx->ota, cfg->ota );

    digital_in_init( &ctx->ina, cfg->ina );

    digital_out_low( &ctx->otb );
    digital_out_low( &ctx->ota );

    return I2C_MASTER_SUCCESS;
}

err_t i2cisolator5_write ( i2cisolator5_t *ctx, uint8_t *data_in, uint8_t len )
{
    return i2c_master_write( &ctx->i2c, data_in, len );
}

err_t i2cisolator5_read ( i2cisolator5_t *ctx, uint8_t *data_out, uint8_t len )
{
    return i2c_master_read( &ctx->i2c, data_out, len );
}

err_t i2cisolator5_write_then_read ( i2cisolator5_t *ctx, uint8_t *data_in, uint8_t data_in_len, 
                                     uint8_t *data_out, uint8_t data_out_len )
{
    return i2c_master_write_then_read( &ctx->i2c, data_in, data_in_len, data_out, data_out_len );
}

err_t i2cisolator5_set_slave_address ( i2cisolator5_t *ctx, uint8_t address ) 
{
    ctx->slave_address = address;

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

void i2cisolator5_set_outa_state ( i2cisolator5_t *ctx, uint8_t outa_state )
{
    if ( I2CISOLATOR5_PIN_STATE_HIGH == outa_state )
    {
        digital_out_high( &ctx->ota );
    }
    else
    {
        digital_out_low( &ctx->ota );
    }
}

void i2cisolator5_set_outb_state ( i2cisolator5_t *ctx, uint8_t outb_state )
{
    if ( I2CISOLATOR5_PIN_STATE_HIGH == outb_state )
    {
        digital_out_high( &ctx->otb );
    }
    else
    {
        digital_out_low( &ctx->otb );
    }
}

uint8_t i2cisolator5_get_ina_state ( i2cisolator5_t *ctx )
{
    if ( I2CISOLATOR5_PIN_STATE_HIGH == digital_in_read( &ctx->ina ) )
    {
        return I2CISOLATOR5_PIN_STATE_HIGH;
    }
    else
    {
        return I2CISOLATOR5_PIN_STATE_LOW;
    }
}

// ------------------------------------------------------------------------- END
