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
 * @file boostinv3.c
 * @brief Boost-INV 3 Click Driver.
 */

#include "boostinv3.h"

void boostinv3_cfg_setup ( boostinv3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->enp = HAL_PIN_NC;
    cfg->enn = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BOOSTINV3_DEVICE_ADDRESS;
}

err_t boostinv3_init ( boostinv3_t *ctx, boostinv3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->enp, cfg->enp );
    digital_out_init( &ctx->enn, cfg->enn );

    digital_out_high( &ctx->enp );
    digital_out_high( &ctx->enn );
    
    return I2C_MASTER_SUCCESS;
}

err_t boostinv3_default_cfg ( boostinv3_t *ctx ) 
{
    err_t error_flag = BOOSTINV3_OK;
    
    boostinv3_set_enp( ctx, BOOSTINV3_PIN_STATE_HIGH );
    boostinv3_set_enn( ctx, BOOSTINV3_PIN_STATE_HIGH );
    
    error_flag = boostinv3_write_reg( ctx, BOOSTINV3_REG_CONFIG, BOOSTINV3_APPS_VALUE_80_MA | 
                                                                 BOOSTINV3_VPOS_NO_DISCHARGE | 
                                                                 BOOSTINV3_VPON_NO_DISCHARGE );
    
    return error_flag;
}

err_t boostinv3_generic_write ( boostinv3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t boostinv3_generic_read ( boostinv3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void boostinv3_set_enp ( boostinv3_t *ctx, uint8_t out_state )
{
    if ( BOOSTINV3_PIN_STATE_HIGH == out_state )
    {
        digital_out_high( &ctx->enp );
    }
    else
    {
        digital_out_low( &ctx->enp );
    }
}

void boostinv3_set_enn ( boostinv3_t *ctx, uint8_t out_state )
{
    if ( BOOSTINV3_PIN_STATE_HIGH == out_state )
    {
        digital_out_high( &ctx->enn );
    }
    else
    {
        digital_out_low( &ctx->enn );
    }
}

err_t boostinv3_write_reg ( boostinv3_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t boostinv3_set_pos_out ( boostinv3_t *ctx, uint8_t out_val )
{
    return boostinv3_write_reg( ctx, BOOSTINV3_REG_P_OUT_VOLTAGE, out_val );
}

err_t boostinv3_set_neg_out ( boostinv3_t *ctx, uint8_t out_val )
{
    return boostinv3_write_reg( ctx, BOOSTINV3_REG_N_OUT_VOLTAGE, out_val );
}

err_t boostinv3_set_config ( boostinv3_t *ctx, uint8_t config_val )
{
    return boostinv3_write_reg( ctx, BOOSTINV3_REG_CONFIG, config_val );
}

// ------------------------------------------------------------------------- END
