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
 * @file battmon4.c
 * @brief BATT-MON 4 Click Driver.
 */

#include "battmon4.h"

void battmon4_cfg_setup ( battmon4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bok  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTMON4_DEVICE_ADDRESS;
}

err_t battmon4_init ( battmon4_t *ctx, battmon4_cfg_t *cfg ) 
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

    digital_in_init( &ctx->bok, cfg->bok );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t battmon4_write_register ( battmon4_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( ( BATTMON4_REG_A != reg ) && ( BATTMON4_REG_B != reg ) && ( BATTMON4_REG_H != reg ) )
    {
        return BATTMON4_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t battmon4_read_register ( battmon4_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( ( reg < BATTMON4_REG_B ) || ( reg > BATTMON4_REG_G ) )
    {
        return BATTMON4_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    if ( BATTMON4_OK == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return BATTMON4_OK;
    }
    return BATTMON4_ERROR;
}

err_t battmon4_get_die_temperature ( battmon4_t *ctx, float *temperature )
{
    uint16_t reg_data;
    if ( BATTMON4_OK == battmon4_read_register ( ctx, BATTMON4_REG_C, &reg_data ) )
    {
        *temperature = BATTMON4_TEMPERATURE_LSB * ( ( reg_data >> 8 ) & BATTMON4_TEMPERATURE_RESOLUTION ) - 
                       BATTMON4_TEMPERATURE_OFFSET;
        return BATTMON4_OK;
    }
    return BATTMON4_ERROR;
}

err_t battmon4_get_batt_in_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off )
{
    uint16_t reg_data;
    if ( BATTMON4_ERROR == battmon4_read_register ( ctx, BATTMON4_REG_D, &reg_data ) )
    {
        return BATTMON4_ERROR;
    }
    *v_ipeak_on = BATTMON4_VOLTAGE_LSB * ( reg_data & BATTMON4_VOLTAGE_RESOLUTION );
    if ( BATTMON4_ERROR == battmon4_read_register ( ctx, BATTMON4_REG_E, &reg_data ) )
    {
        return BATTMON4_ERROR;
    }
    *v_ipeak_off = BATTMON4_VOLTAGE_LSB * ( reg_data & BATTMON4_VOLTAGE_RESOLUTION );
    return BATTMON4_OK;
}

err_t battmon4_get_batt_out_voltage ( battmon4_t *ctx, float *v_ipeak_on, float *v_ipeak_off )
{
    uint16_t reg_data;
    if ( BATTMON4_ERROR == battmon4_read_register ( ctx, BATTMON4_REG_F, &reg_data ) )
    {
        return BATTMON4_ERROR;
    }
    *v_ipeak_on = BATTMON4_VOLTAGE_LSB * ( reg_data & BATTMON4_VOLTAGE_RESOLUTION );
    if ( BATTMON4_ERROR == battmon4_read_register ( ctx, BATTMON4_REG_G, &reg_data ) )
    {
        return BATTMON4_ERROR;
    }
    *v_ipeak_off = BATTMON4_VOLTAGE_LSB * ( reg_data & BATTMON4_VOLTAGE_RESOLUTION );
    return BATTMON4_OK;
}

uint8_t battmon4_get_bok_pin ( battmon4_t *ctx )
{
    return digital_in_read ( &ctx->bok );
}

uint8_t battmon4_get_int_pin ( battmon4_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END
