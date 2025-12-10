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
 * @file dac21.c
 * @brief DAC 21 Click Driver.
 */

#include "dac21.h"

void dac21_cfg_setup ( dac21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->lt0 = HAL_PIN_NC;
    cfg->lt1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC21_DEVICE_ADDRESS_A1A0_00;
}

err_t dac21_init ( dac21_t *ctx, dac21_cfg_t *cfg ) 
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

    digital_out_init( &ctx->lt0, cfg->lt0 );
    digital_out_init( &ctx->lt1, cfg->lt1 );
    Delay_1ms ( );
    digital_out_high ( &ctx->lt0 );
    digital_out_high ( &ctx->lt1 );

    return I2C_MASTER_SUCCESS;
}

err_t dac21_default_cfg ( dac21_t *ctx ) 
{
    err_t error_flag = DAC21_OK;
    
    error_flag |= dac21_set_dac_value ( ctx, DAC21_CHANNEL_ALL, DAC21_DAC_VALUE_MIN );
    error_flag |= dac21_set_vref_control ( ctx, DAC21_CHANNEL_ALL, DAC21_VREF_BUFFERED );
    error_flag |= dac21_set_power_control ( ctx, DAC21_CHANNEL_ALL, DAC21_PWR_NORMAL_OPERATION );

    return error_flag;
}

err_t dac21_write_reg ( dac21_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC21_CMD_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t dac21_read_reg ( dac21_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = DAC21_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC21_CMD_READ;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( DAC21_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

void dac21_set_lat0_pin ( dac21_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->lt0, state );
}

void dac21_set_lat1_pin ( dac21_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->lt1, state );
}

err_t dac21_set_vref_control ( dac21_t *ctx, uint8_t channel, uint8_t vref )
{
    uint16_t vref_ctrl = 0;
    if ( vref > DAC21_VREF_BUFFERED )
    {
        return DAC21_ERROR;
    }
    for ( uint8_t ch_cnt = 0; ch_cnt < 8; ch_cnt++ )
    {
        if ( channel & ( 1 << ch_cnt ) )
        {
            vref_ctrl |= ( ( uint16_t ) vref << ( ch_cnt * 2 ) );
        }
    }
    return dac21_write_reg ( ctx, DAC21_REG_VOLATILE_VREF, vref_ctrl );
}

err_t dac21_set_power_control ( dac21_t *ctx, uint8_t channel, uint8_t pwr )
{
    uint16_t pwr_ctrl = 0;
    if ( pwr > DAC21_PWR_PDOWN_HIZ )
    {
        return DAC21_ERROR;
    }
    for ( uint8_t ch_cnt = 0; ch_cnt < 8; ch_cnt++ )
    {
        if ( channel & ( 1 << ch_cnt ) )
        {
            pwr_ctrl |= ( ( uint16_t ) pwr << ( ch_cnt * 2 ) );
        }
    }
    return dac21_write_reg ( ctx, DAC21_REG_VOLATILE_POWER_DOWN, pwr_ctrl );
}

err_t dac21_set_dac_value ( dac21_t *ctx, uint8_t channel, uint16_t value )
{
    err_t error_flag = DAC21_OK;
    if ( value > DAC21_DAC_VALUE_MAX )
    {
        return DAC21_ERROR;
    }
    for ( uint8_t ch_cnt = 0; ch_cnt < 8; ch_cnt++ )
    {
        if ( channel & ( 1 << ch_cnt ) )
        {
            error_flag |= dac21_write_reg ( ctx, DAC21_REG_VOLATILE_DAC_WIPER_0 + ch_cnt, value );
        }
    }
    dac21_set_lat0_pin ( ctx, 0 );
    dac21_set_lat1_pin ( ctx, 0 );
    Delay_10ms ( );
    dac21_set_lat0_pin ( ctx, 1 );
    dac21_set_lat1_pin ( ctx, 1 );
    return error_flag;
}

err_t dac21_set_dac_voltage ( dac21_t *ctx, uint8_t channel, uint16_t voltage_mv )
{
    err_t error_flag = DAC21_OK;
    uint16_t dac_value = 0;
    if ( voltage_mv > DAC21_VREF_INT_3V )
    {
        return DAC21_ERROR;
    }
    dac_value = ( uint16_t ) ( ( float ) voltage_mv / DAC21_VREF_INT_3V * DAC21_DAC_VALUE_MAX );
    return dac21_set_dac_value ( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
