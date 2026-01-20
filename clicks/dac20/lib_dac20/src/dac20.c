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
 * @file dac20.c
 * @brief DAC 20 Click Driver.
 */

#include "dac20.h"

void dac20_cfg_setup ( dac20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->latch = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC20_DEVICE_ADDRESS_A1A0_00;
}

err_t dac20_init ( dac20_t *ctx, dac20_cfg_t *cfg ) 
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

    digital_out_init( &ctx->latch, cfg->latch );
    Delay_1ms ( );
    digital_out_high ( &ctx->latch );

    return I2C_MASTER_SUCCESS;
}

err_t dac20_default_cfg ( dac20_t *ctx ) 
{
    err_t error_flag = DAC20_OK;
    
    error_flag |= dac20_set_dac_value ( ctx, DAC20_CHANNEL_ALL, DAC20_DAC_VALUE_MIN );
    error_flag |= dac20_set_vref_control ( ctx, DAC20_CHANNEL_ALL, DAC20_VREF_BUFFERED );
    error_flag |= dac20_set_power_control ( ctx, DAC20_CHANNEL_ALL, DAC20_PWR_NORMAL_OPERATION );

    return error_flag;
}

err_t dac20_write_reg ( dac20_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC20_CMD_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t dac20_read_reg ( dac20_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = DAC20_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( reg << 3 ) | DAC20_CMD_READ;
    error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 1, &data_buf[ 1 ], 2 );
    if ( ( DAC20_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    }
    return error_flag;
}

void dac20_set_latch_pin ( dac20_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->latch, state );
}

err_t dac20_set_vref_control ( dac20_t *ctx, uint8_t channel, uint8_t vref )
{
    uint16_t vref_ctrl = 0;
    if ( vref > DAC20_VREF_BUFFERED )
    {
        return DAC20_ERROR;
    }
    if ( channel & DAC20_CHANNEL_0 )
    {
        vref_ctrl |= ( ( uint16_t ) vref );
    }
    if ( channel & DAC20_CHANNEL_1 )
    {
        vref_ctrl |= ( ( uint16_t ) vref << 2 );
    }
    return dac20_write_reg ( ctx, DAC20_REG_VOLATILE_VREF, vref_ctrl );
}

err_t dac20_set_power_control ( dac20_t *ctx, uint8_t channel, uint8_t pwr )
{
    uint16_t pwr_ctrl = 0;
    if ( pwr > DAC20_PWR_PDOWN_HIZ )
    {
        return DAC20_ERROR;
    }
    if ( channel & DAC20_CHANNEL_0 )
    {
        pwr_ctrl |= ( ( uint16_t ) pwr );
    }
    if ( channel & DAC20_CHANNEL_1 )
    {
        pwr_ctrl |= ( ( uint16_t ) pwr << 2 );
    }
    return dac20_write_reg ( ctx, DAC20_REG_VOLATILE_POWER_DOWN, pwr_ctrl );
}

err_t dac20_set_dac_value ( dac20_t *ctx, uint8_t channel, uint16_t value )
{
    err_t error_flag = DAC20_OK;
    if ( value > DAC20_DAC_VALUE_MAX )
    {
        return DAC20_ERROR;
    }
    if ( channel & DAC20_CHANNEL_0 )
    {
        error_flag |= dac20_write_reg ( ctx, DAC20_REG_VOLATILE_DAC_WIPER_0, value );
    }
    if ( channel & DAC20_CHANNEL_1 )
    {
        error_flag |= dac20_write_reg ( ctx, DAC20_REG_VOLATILE_DAC_WIPER_1, value );
    }
    dac20_set_latch_pin ( ctx, 0 );
    Delay_10ms ( );
    dac20_set_latch_pin ( ctx, 1 );
    return error_flag;
}

err_t dac20_set_dac_voltage ( dac20_t *ctx, uint8_t channel, uint16_t voltage_mv )
{
    err_t error_flag = DAC20_OK;
    uint16_t dac_value = 0;
    if ( voltage_mv > DAC20_VREF_INT )
    {
        return DAC20_ERROR;
    }
    dac_value = ( uint16_t ) ( ( float ) voltage_mv / DAC20_VREF_INT * DAC20_DAC_VALUE_MAX );
    return dac20_set_dac_value ( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
