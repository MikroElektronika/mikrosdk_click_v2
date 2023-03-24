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
 * @file proximity14.c
 * @brief Proximity 14 Click Driver.
 */

#include "proximity14.h"

void proximity14_cfg_setup ( proximity14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = PROXIMITY14_SET_DEV_ADDR;
}

err_t proximity14_init ( proximity14_t *ctx, proximity14_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( i2c_master_set_timeout( &ctx->i2c, 0 ) == I2C_MASTER_ERROR ) 
    {
        return I2C_MASTER_ERROR;
    }
    
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t proximity14_default_cfg ( proximity14_t *ctx ) 
{    
    //Power on and callibration on
    err_t error_flag = proximity14_generic_write( ctx, PROXIMITY14_REG_CFG1, 0x0083 );
    //16bit output; 20mA <= I_VCSEL
    error_flag |= proximity14_generic_write( ctx, PROXIMITY14_REG_CFG3, 0x1708 );
    // 8T <= PS_IT; 50us <= ITB; PS high gain mode
    error_flag |= proximity14_generic_write( ctx, PROXIMITY14_REG_CFG2, 0xCC00 );
    
    return error_flag;
}

err_t proximity14_generic_write ( proximity14_t *ctx, uint8_t reg, uint16_t tx_data )
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;
    data_buf[ 2 ] = tx_data >> 8;

    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t proximity14_generic_read ( proximity14_t *ctx, uint8_t reg, uint16_t *rx_data )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 2 );
    
    if ( error_flag )
    {
        *rx_data = 0;
    }
    else
    {
        *rx_data = rx_buf[ 0 ] | ( ( uint16_t )rx_buf[ 1 ] << 8 );
    }
    
    return error_flag;
}

uint8_t proximity14_get_int ( proximity14_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
