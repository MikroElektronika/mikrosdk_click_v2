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
 * @file dac10.c
 * @brief DAC 10 Click Driver.
 */

#include "dac10.h"

void dac10_cfg_setup ( dac10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC10_DEV_ADDR_GND;
}

err_t dac10_init ( dac10_t *ctx, dac10_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t dac10_reg_write ( dac10_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t dac10_reg_read ( dac10_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 2 );
    
    *data_in = rx_buf[ 0 ];
    *data_in <<= 8;
    *data_in |= rx_buf[ 1 ];
    
    return error_flag;
}

err_t dac10_set_dac_value ( dac10_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC10_MAX_DAC_VALUE )
    {
        data_in = DAC10_MAX_DAC_VALUE;
    }
    
    return dac10_reg_write( ctx, DAC10_REG_DAC_DATA, data_in << 2 );
}

err_t dac10_set_output_voltage ( dac10_t *ctx, float vref, float voltage )
{
    uint16_t dac_value = 0;
    uint16_t tmp_data = 0;
    err_t error_flag = dac10_reg_read ( ctx, DAC10_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC10_GEN_CONFIG_INT_REF_EN_MASK;
    tmp_data |= DAC10_GEN_CONFIG_INT_REF_DISABLE;
    error_flag |= dac10_reg_write( ctx, DAC10_REG_GENERAL_CONFIG, tmp_data );
    
    dac_value = ( uint16_t ) ( voltage * ( DAC10_MAX_DAC_VALUE + 1 ) / vref );
    
    if ( dac_value > DAC10_MAX_DAC_VALUE )
    {
        dac_value = DAC10_MAX_DAC_VALUE;
    }
    error_flag |= dac10_reg_write( ctx, DAC10_REG_DAC_DATA, dac_value << 2 );
    return error_flag;
}

err_t dac10_set_output_voltage_int_vref ( dac10_t *ctx, float voltage )
{
    uint16_t dac_value = 0;
    uint16_t tmp_data = 0;
    err_t error_flag = dac10_reg_read ( ctx, DAC10_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC10_GEN_CONFIG_INT_REF_EN_MASK;
    tmp_data |= DAC10_GEN_CONFIG_INT_REF_ENABLE;
    error_flag |= dac10_reg_write( ctx, DAC10_REG_GENERAL_CONFIG, tmp_data );
    tmp_data &= DAC10_GEN_CONFIG_DAC_SPAN_MASK;
            
    if ( tmp_data == DAC10_GEN_CONFIG_DAC_SPAN_GAIN_1p5X )
    {
        dac_value = ( uint16_t ) ( voltage * ( DAC10_MAX_DAC_VALUE + 1 ) / ( DAC10_VREF_INT * 1.5 ) );
    }
    else
    {
        dac_value = ( uint16_t ) ( voltage * ( DAC10_MAX_DAC_VALUE + 1 ) / ( DAC10_VREF_INT * ( tmp_data + 1 ) ) );
    }
    
    if ( dac_value > DAC10_MAX_DAC_VALUE )
    {
        dac_value = DAC10_MAX_DAC_VALUE;
    }
    
    error_flag |= dac10_reg_write( ctx, DAC10_REG_DAC_DATA, dac_value << 2 );
    
    return error_flag;
}

err_t dac10_set_dac_margin_high ( dac10_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC10_MAX_DAC_VALUE )
    {
        data_in = DAC10_MAX_DAC_VALUE;
    }
    
    return dac10_reg_write( ctx, DAC10_REG_DAC_MARGIN_HIGH, data_in << 2 );
}

err_t dac10_set_dac_margin_low ( dac10_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC10_MAX_DAC_VALUE )
    {
        data_in = DAC10_MAX_DAC_VALUE;
    }
    
    return dac10_reg_write( ctx, DAC10_REG_DAC_MARGIN_LOW, data_in << 2 );
}

err_t dac10_check_device_id ( dac10_t *ctx ) 
{
    uint16_t rx_data;
    err_t error_flag = dac10_reg_read ( ctx, DAC10_REG_STATUS, &rx_data );
    
    if ( ( rx_data & DAC10_STATUS_DEVICE_ID_MASK ) != DAC10_STATUS_DEVICE_ID )
    {
        return DAC10_ERROR;
    }
    
    return error_flag;
}

err_t dac10_enable_dac ( dac10_t *ctx ) 
{
    uint16_t tmp_data = 0;
    err_t error_flag = dac10_reg_read ( ctx, DAC10_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC10_GEN_CONFIG_DAC_PDN_MASK;
    tmp_data |= DAC10_GEN_CONFIG_DAC_PDN_POWER_UP;
    error_flag |= dac10_reg_write( ctx, DAC10_REG_GENERAL_CONFIG, tmp_data );
    return error_flag;
}

// ------------------------------------------------------------------------- END
