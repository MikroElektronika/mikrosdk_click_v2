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
 * @file battmon2.c
 * @brief BATT-MON 2 Click Driver.
 */

#include "battmon2.h"

void battmon2_cfg_setup ( battmon2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTMON2_SET_DEV_ADDR;
}

err_t battmon2_init ( battmon2_t *ctx, battmon2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alert, cfg->alert );

    return I2C_MASTER_SUCCESS;
}

err_t battmon2_generic_write ( battmon2_t *ctx, uint8_t reg, uint16_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 513 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint16_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ ( cnt * 2 ) + 1 ] = ( uint8_t ) ( tx_buf[ cnt ] & 0xFF );
        data_buf[ ( cnt * 2 ) + 2 ] = ( uint8_t ) ( ( tx_buf[ cnt ] >> 8 ) & 0xFF );
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t battmon2_generic_read ( battmon2_t *ctx, uint8_t reg, uint16_t *rx_buf, uint8_t rx_len ) 
{
    uint8_t data_buf[ 512 ] = { 0 };
    if ( BATTMON2_OK == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, rx_len * 2 ) )
    {
        for ( uint16_t cnt = 0; cnt < rx_len; cnt++ )
        {
            rx_buf[ cnt ] = ( ( uint16_t ) data_buf[ ( cnt * 2 ) + 1 ] << 8 ) | data_buf[ cnt * 2 ];
        }
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_write_register ( battmon2_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    return battmon2_generic_write( ctx, reg, &data_in, 1 );
}

err_t battmon2_read_register ( battmon2_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    return battmon2_generic_read( ctx, reg, data_out, 1 );
}

err_t battmon2_check_communication ( battmon2_t *ctx )
{
    uint16_t device_id = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_DEV_NAME, &device_id ) )
    {
        if ( BATTMON2_DEVICE_ID == device_id )
        {
            return BATTMON2_OK;
        }
    }
    return BATTMON2_ERROR;
}

uint8_t battmon2_get_alert_pin ( battmon2_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

err_t battmon2_get_die_temperature ( battmon2_t *ctx, float *temperature )
{
    uint16_t raw_temp = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_DIE_TEMP, &raw_temp ) )
    {
        *temperature = ( int16_t ) raw_temp * BATTMON2_TEMPERATURE_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_capacity ( battmon2_t *ctx, float *capacity )
{
    uint16_t raw_cap = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_REP_CAP, &raw_cap ) )
    {
        *capacity = raw_cap * BATTMON2_CAPACITY_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_percentage ( battmon2_t *ctx, float *percentage )
{
    uint16_t raw_per = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_REP_SOC, &raw_per ) )
    {
        *percentage = raw_per * BATTMON2_PERCENTAGE_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_voltage ( battmon2_t *ctx, float *voltage )
{
    uint16_t raw_voltage = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_V_CELL, &raw_voltage ) )
    {
        *voltage = raw_voltage * BATTMON2_VOLTAGE_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_current ( battmon2_t *ctx, float *current )
{
    uint16_t raw_current = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_CURRENT, &raw_current ) )
    {
        *current = ( int16_t ) raw_current * BATTMON2_CURRENT_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_tte ( battmon2_t *ctx, uint32_t *time_to_empty )
{
    uint16_t raw_tte = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_TTE, &raw_tte ) )
    {
        *time_to_empty = ( uint32_t ) raw_tte * BATTMON2_TIME_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

err_t battmon2_get_battery_ttf ( battmon2_t *ctx, uint32_t *time_to_full )
{
    uint16_t raw_ttf = 0;
    if ( BATTMON2_OK == battmon2_read_register ( ctx, BATTMON2_REG_TTF, &raw_ttf ) )
    {
        *time_to_full = ( uint32_t ) raw_ttf * BATTMON2_TIME_RESOLUTION;
        return BATTMON2_OK;
    }
    return BATTMON2_ERROR;
}

// ------------------------------------------------------------------------- END
