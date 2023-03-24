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
 * @file buck22.c
 * @brief Buck 22 Click Driver.
 */

#include "buck22.h"

void buck22_cfg_setup ( buck22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCK22_DEVICE_ADDRESS;
}

err_t buck22_init ( buck22_t *ctx, buck22_cfg_t *cfg ) 
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

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t buck22_set_vout ( buck22_t *ctx, uint16_t vout_mv )
{
    if ( ( vout_mv < BUCK22_VOUT_MIN ) || ( vout_mv > BUCK22_VOUT_MAX ) )
    {
        return BUCK22_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = BUCK22_REG_VOUT;
    data_buf[ 1 ] = ( vout_mv - BUCK22_VOUT_MIN ) / BUCK22_VOUT_RESOLUTION;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck22_read_vout ( buck22_t *ctx, uint16_t *vout_mv )
{
    uint8_t reg = BUCK22_REG_VOUT;
    uint8_t vout;
    if ( BUCK22_OK == i2c_master_write_then_read( &ctx->i2c, &reg, 1, &vout, 1 ) )
    {
        *vout_mv = BUCK22_VOUT_MIN + ( vout * BUCK22_VOUT_RESOLUTION );
        return BUCK22_OK;
    }
    return BUCK22_ERROR;
}

err_t buck22_set_control ( buck22_t *ctx, uint8_t control )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = BUCK22_REG_CONTROL;
    data_buf[ 1 ] = control;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t buck22_read_status ( buck22_t *ctx, uint8_t *status )
{
    uint8_t reg = BUCK22_REG_STATUS;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, status, 1 );
}

uint8_t buck22_get_pg_pin ( buck22_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

// ------------------------------------------------------------------------- END
