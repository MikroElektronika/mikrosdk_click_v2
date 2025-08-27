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
 * @file buck24.c
 * @brief Buck 24 Click Driver.
 */

#include "buck24.h"

void buck24_cfg_setup ( buck24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BUCK24_DEVICE_ADDRESS_1;
}

err_t buck24_init ( buck24_t *ctx, buck24_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->pg, cfg->pg );

    return I2C_MASTER_SUCCESS;
}

err_t buck24_default_cfg ( buck24_t *ctx ) 
{
    err_t error_flag = BUCK24_OK;
    buck24_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= buck24_write_reg ( ctx, BUCK24_REG_CONFIGURATION, BUCK24_CONFIGURATION_RST );
    Delay_100ms ( );
    error_flag |= buck24_write_reg ( ctx, BUCK24_REG_CONFIGURATION, BUCK24_CONFIGURATION_BRNG_16V |
                                                                    BUCK24_CONFIGURATION_PGA_DIV_1 | 
                                                                    BUCK24_CONFIGURATION_BADC_532_US | 
                                                                    BUCK24_CONFIGURATION_SADC_532_US | 
                                                                    BUCK24_CONFIGURATION_MODE_SHT_BUS_V_CONT );
    error_flag |= buck24_write_reg ( ctx, BUCK24_REG_CALIBRATION, BUCK24_CALIBRATION_FOR_SHUNT_0_01_OHM );

    return error_flag;
}

void buck24_enable_device ( buck24_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void buck24_disable_device ( buck24_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

uint8_t buck24_get_pg_pin ( buck24_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t buck24_write_reg ( buck24_t *ctx, uint8_t reg, uint16_t data_in )
{
    if ( reg > BUCK24_REG_CALIBRATION )
    {
        return BUCK24_ERROR;
    }
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t buck24_read_reg ( buck24_t *ctx, uint8_t reg, uint16_t *data_out )
{
    if ( reg > BUCK24_REG_CALIBRATION )
    {
        return BUCK24_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ( BUCK24_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t buck24_read_data ( buck24_t *ctx, buck24_data_t *data_out )
{
    if ( NULL == data_out )
    {
        return BUCK24_ERROR;
    }
    uint16_t reg_data = 0;
    err_t error_flag = buck24_read_reg ( ctx, BUCK24_REG_SHUNT_VOLTAGE, &reg_data );
    if ( BUCK24_OK == error_flag )
    {
        data_out->shunt_mv = ( ( int16_t ) reg_data ) * BUCK24_SHUNT_LSB_MV;
        error_flag |= buck24_read_reg ( ctx, BUCK24_REG_BUS_VOLTAGE, &reg_data );
    }
    if ( BUCK24_OK == error_flag )
    {
        data_out->bus_v = ( reg_data >> 3 ) * BUCK24_BUS_V_LSB_V;
        error_flag |= buck24_read_reg ( ctx, BUCK24_REG_CURRENT, &reg_data );
    }
    if ( BUCK24_OK == error_flag )
    {
        data_out->current = ( ( int16_t ) reg_data ) * BUCK24_CURRENT_LSB_A;
        error_flag |= buck24_read_reg ( ctx, BUCK24_REG_POWER, &reg_data );
    }
    if ( BUCK24_OK == error_flag )
    {
        data_out->power = reg_data * BUCK24_POWER_LSB_W;
    }
    return error_flag;
}

err_t buck24_read_data_avg ( buck24_t *ctx, uint16_t num_conv, buck24_data_t *data_out )
{
    buck24_data_t pm_data_sum;
    pm_data_sum.shunt_mv = 0;
    pm_data_sum.bus_v = 0;
    pm_data_sum.current = 0;
    pm_data_sum.power = 0;
    for ( uint16_t cnt = 0; cnt < num_conv; cnt++ )
    {
        if ( BUCK24_OK == buck24_read_data ( ctx, data_out ) )
        {
            pm_data_sum.shunt_mv += data_out->shunt_mv;
            pm_data_sum.bus_v += data_out->bus_v;
            pm_data_sum.current += data_out->current;
            pm_data_sum.power += data_out->power;
        }
        else
        {
            return BUCK24_ERROR;
        }
    }
    if ( num_conv )
    {
        data_out->shunt_mv = pm_data_sum.shunt_mv / num_conv;
        data_out->bus_v = pm_data_sum.bus_v / num_conv;
        data_out->current = pm_data_sum.current / num_conv;
        data_out->power = pm_data_sum.power / num_conv;
    }
    return BUCK24_OK;
}

// ------------------------------------------------------------------------- END
