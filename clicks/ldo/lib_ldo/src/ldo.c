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
 * @file ldo.c
 * @brief LDO Click Driver.
 */

#include "ldo.h"

/**
 * @brief LDO invert bits function.
 * @details This function inverts six LSBs in a byte.
 * @param[in] data_in : Input data byte to invert.
 * @return Inverted byte.
 * @note None.
 */
static uint8_t ldo_invert_bits ( uint8_t data_in );

void ldo_cfg_setup ( ldo_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = LDO_DEVICE_ADDRESS_0;
}

err_t ldo_init ( ldo_t *ctx, ldo_cfg_t *cfg ) 
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
    
    digital_out_init ( &ctx->en, cfg->en );

    return I2C_MASTER_SUCCESS;
}

err_t ldo_default_cfg ( ldo_t *ctx ) 
{
    err_t error_flag = LDO_OK;
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
    error_flag |= ldo_write_register ( ctx, LDO_REG_OUTPUT_PORT, LDO_PIN_NONE );
    error_flag |= ldo_set_pin_state ( ctx, LDO_PIN_ALL, LDO_PIN_OPEN );
    return error_flag;
}

err_t ldo_write_register ( ldo_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t ldo_read_register ( ldo_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t ldo_set_pin_state ( ldo_t *ctx, uint8_t pin_mask, uint8_t state )
{
    if ( ( pin_mask > LDO_PIN_ALL ) || ( state > LDO_PIN_OPEN ) )
    {
        return LDO_ERROR;
    }
    uint8_t reg_data = 0;
    err_t error_flag = ldo_read_register ( ctx, LDO_REG_CONFIG, &reg_data );
    reg_data &= ~pin_mask;
    if ( LDO_PIN_OPEN == state )
    {
        reg_data |= pin_mask;
    }
    error_flag |= ldo_write_register ( ctx, LDO_REG_CONFIG, reg_data );
    return error_flag;
}

err_t ldo_set_vout ( ldo_t *ctx, uint16_t vout )
{
    if ( ( vout < LDO_VOUT_MIN ) || ( vout > LDO_VOUT_MAX ) )
    {
        return LDO_ERROR;
    }
    uint8_t reg_data = ( uint8_t ) ( ( ( vout - LDO_VOUT_MIN ) / LDO_VOUT_STEP ) & LDO_PIN_ALL );
    reg_data = LDO_PIN_ALL ^ ldo_invert_bits ( reg_data );
    return ldo_write_register ( ctx, LDO_REG_CONFIG, reg_data );
}

void ldo_enable_device ( ldo_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void ldo_disable_device ( ldo_t *ctx )
{
    digital_out_low ( &ctx->en );
}

static uint8_t ldo_invert_bits ( uint8_t data_in )
{
    uint8_t inv_data = 0;
    for ( uint8_t bit_cnt = 0; bit_cnt < 6; bit_cnt++ )
    {
        inv_data <<= 1;
        inv_data |= ( ( data_in >> bit_cnt ) & 1 );
    }
    return inv_data;
}

// ------------------------------------------------------------------------- END
