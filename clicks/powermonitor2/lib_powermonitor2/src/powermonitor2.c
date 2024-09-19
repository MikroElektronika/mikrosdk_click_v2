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
 * @file powermonitor2.c
 * @brief Power Monitor 2 Click Driver.
 */

#include "powermonitor2.h"

void powermonitor2_cfg_setup ( powermonitor2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address_3v3 = POWERMONITOR2_DEVICE_ADDRESS_3V3_1;
    cfg->i2c_address_5v = POWERMONITOR2_DEVICE_ADDRESS_5V_1;
}

err_t powermonitor2_init ( powermonitor2_t *ctx, powermonitor2_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address_3v3;
    ctx->address_3v3 = cfg->i2c_address_3v3;
    ctx->address_5v = cfg->i2c_address_5v;

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

    return I2C_MASTER_SUCCESS;
}

err_t powermonitor2_default_cfg ( powermonitor2_t *ctx ) 
{
    err_t error_flag = POWERMONITOR2_OK;
    error_flag |= powermonitor2_set_address ( ctx, ctx->address_3v3 );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CONFIGURATION, 
                                                 POWERMONITOR2_CONFIGURATION_RST );
    Delay_100ms ( );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CONFIGURATION, 
                                                 POWERMONITOR2_CONFIGURATION_BRNG_16V |
                                                 POWERMONITOR2_CONFIGURATION_PGA_DIV_1 | 
                                                 POWERMONITOR2_CONFIGURATION_BADC_532_US | 
                                                 POWERMONITOR2_CONFIGURATION_SADC_532_US | 
                                                 POWERMONITOR2_CONFIGURATION_MODE_SHT_BUS_V_CONT );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CALIBRATION, 
                                                 POWERMONITOR2_CALIBRATION_FOR_SHUNT_0_01_OHM );
    
    error_flag |= powermonitor2_set_address ( ctx, ctx->address_5v );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CONFIGURATION, 
                                                 POWERMONITOR2_CONFIGURATION_RST );
    Delay_100ms ( );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CONFIGURATION, 
                                                 POWERMONITOR2_CONFIGURATION_BRNG_16V |
                                                 POWERMONITOR2_CONFIGURATION_PGA_DIV_1 | 
                                                 POWERMONITOR2_CONFIGURATION_BADC_532_US | 
                                                 POWERMONITOR2_CONFIGURATION_SADC_532_US | 
                                                 POWERMONITOR2_CONFIGURATION_MODE_SHT_BUS_V_CONT );
    error_flag |= powermonitor2_write_reg ( ctx, POWERMONITOR2_REG_CALIBRATION, 
                                                 POWERMONITOR2_CALIBRATION_FOR_SHUNT_0_01_OHM );
    return error_flag;
}

err_t powermonitor2_set_address ( powermonitor2_t *ctx, uint8_t slave_address )
{
    ctx->slave_address = slave_address;
    return i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
}

err_t powermonitor2_write_reg ( powermonitor2_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( reg > POWERMONITOR2_REG_CALIBRATION )
    {
        return POWERMONITOR2_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t powermonitor2_read_reg ( powermonitor2_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( reg > POWERMONITOR2_REG_CALIBRATION )
    {
        return POWERMONITOR2_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ( POWERMONITOR2_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t powermonitor2_read_data ( powermonitor2_t *ctx, powermonitor2_data_t *data_out )
{
    if ( NULL == data_out )
    {
        return POWERMONITOR2_ERROR;
    }
    uint16_t reg_data = 0;
    err_t error_flag = powermonitor2_read_reg ( ctx, POWERMONITOR2_REG_SHUNT_VOLTAGE, &reg_data );
    if ( POWERMONITOR2_OK == error_flag )
    {
        data_out->shunt_mv = ( ( int16_t ) reg_data ) * POWERMONITOR2_SHUNT_LSB_MV;
        error_flag |= powermonitor2_read_reg ( ctx, POWERMONITOR2_REG_BUS_VOLTAGE, &reg_data );
    }
    if ( POWERMONITOR2_OK == error_flag )
    {
        data_out->bus_v = ( reg_data >> 3 ) * POWERMONITOR2_BUS_V_LSB_V;
        error_flag |= powermonitor2_read_reg ( ctx, POWERMONITOR2_REG_CURRENT, &reg_data );
    }
    if ( POWERMONITOR2_OK == error_flag )
    {
        data_out->current = ( ( int16_t ) reg_data ) * POWERMONITOR2_CURRENT_LSB_A;
        error_flag |= powermonitor2_read_reg ( ctx, POWERMONITOR2_REG_POWER, &reg_data );
    }
    if ( POWERMONITOR2_OK == error_flag )
    {
        data_out->power = reg_data * POWERMONITOR2_POWER_LSB_W;
    }
    return error_flag;
}

err_t powermonitor2_read_data_avg ( powermonitor2_t *ctx, uint16_t num_conv, powermonitor2_data_t *data_out )
{
    powermonitor2_data_t pm_data_sum;
    pm_data_sum.shunt_mv = 0;
    pm_data_sum.bus_v = 0;
    pm_data_sum.current = 0;
    pm_data_sum.power = 0;
    for ( uint16_t cnt = 0; cnt < num_conv; cnt++ )
    {
        if ( POWERMONITOR2_OK == powermonitor2_read_data ( ctx, data_out ) )
        {
            pm_data_sum.shunt_mv += data_out->shunt_mv;
            pm_data_sum.bus_v += data_out->bus_v;
            pm_data_sum.current += data_out->current;
            pm_data_sum.power += data_out->power;
        }
        else
        {
            return POWERMONITOR2_ERROR;
        }
    }
    if ( num_conv )
    {
        data_out->shunt_mv = pm_data_sum.shunt_mv / num_conv;
        data_out->bus_v = pm_data_sum.bus_v / num_conv;
        data_out->current = pm_data_sum.current / num_conv;
        data_out->power = pm_data_sum.power / num_conv;
    }
    return POWERMONITOR2_OK;
}

// ------------------------------------------------------------------------- END
