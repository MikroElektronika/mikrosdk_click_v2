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
 * @file thermo18.c
 * @brief Thermo 18 Click Driver.
 */

#include "thermo18.h"
#include "math.h"

/**
 * @brief Conversion constants.
 * @details Specified constants for calculating temperature data and threshold.
 */
#define THERMO18_DATA_SENS          0.01
#define THERMO18_THRESHOLD_OFFSET   63
#define THERMO18_THRESHOLD_SENS     0.64

void thermo18_cfg_setup ( thermo18_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO18_SET_DEV_ADDR;
}

err_t thermo18_init ( thermo18_t *ctx, thermo18_cfg_t *cfg )
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

    if ( I2C_MASTER_ERROR == i2c_master_set_timeout( &ctx->i2c, 0 ) )
    {
        return I2C_MASTER_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t thermo18_default_cfg ( thermo18_t *ctx )
{
    err_t ret_val = thermo18_reset( ctx );
    ret_val |= thermo18_set_temperature_threshold( ctx, THERMO18_REG_T_H_LIMIT, 30 );
    ret_val |= thermo18_set_temperature_threshold( ctx, THERMO18_REG_T_L_LIMIT, 24 );
    return ret_val;
}

err_t thermo18_generic_write ( thermo18_t *ctx, uint8_t reg, uint8_t tx_data )
{
    uint8_t data_buf[ 2 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = tx_data;

    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t thermo18_generic_read ( thermo18_t *ctx, uint8_t reg, uint8_t *rx_data )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_data, 1 );
}

err_t thermo18_read_temperature ( thermo18_t *ctx, float *temperature )
{
    err_t ret_val;
    uint8_t read_data = { 0 };
    int16_t temp_data;

    ret_val = thermo18_generic_read( ctx, THERMO18_REG_DATA_T_H, &read_data );
    temp_data = read_data;
    temp_data <<= 8;
    ret_val |= thermo18_generic_read( ctx, THERMO18_REG_DATA_T_L, &read_data );
    temp_data |= read_data;
    *temperature = ( float )temp_data * THERMO18_DATA_SENS;

    return ret_val;
}

err_t thermo18_reset ( thermo18_t *ctx )
{
    err_t ret_val = thermo18_generic_write( ctx, THERMO18_REG_CTRL, 1 );
    Delay_10ms( );
    Delay_1ms( );
    Delay_1ms( );
    ret_val |= thermo18_generic_write( ctx, THERMO18_REG_CTRL, 0 );
    Delay_10ms( );
    Delay_1ms( );
    Delay_1ms( );
    return ret_val;
}

uint8_t thermo18_get_interrupt ( thermo18_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

err_t thermo18_set_temperature_threshold ( thermo18_t *ctx, uint8_t threshold_reg, float threshold_limit )
{
    err_t ret_val = THERMO18_ERROR;

    if ( ( THERMO18_REG_T_H_LIMIT == threshold_reg ) ||
         ( THERMO18_REG_T_L_LIMIT == threshold_reg ) )
    {
        volatile float reg_val = threshold_limit / THERMO18_THRESHOLD_SENS + THERMO18_THRESHOLD_OFFSET;
        ret_val = thermo18_generic_write( ctx, threshold_reg, ( uint8_t )floor( reg_val ) );
    }

    return ret_val;
}

// ------------------------------------------------------------------------- END
