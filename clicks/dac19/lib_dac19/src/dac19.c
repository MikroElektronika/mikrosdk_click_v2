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
 * @file dac19.c
 * @brief DAC 19 Click Driver.
 */

#include "dac19.h"

void dac19_cfg_setup ( dac19_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gpi = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = DAC19_DEVICE_ADDRESS_GND;
}

err_t dac19_init ( dac19_t *ctx, dac19_cfg_t *cfg ) 
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

    digital_out_init( &ctx->gpi, cfg->gpi );
    digital_out_high( &ctx->gpi );

    return I2C_MASTER_SUCCESS;
}

err_t dac19_default_cfg ( dac19_t *ctx ) 
{
    err_t error_flag = DAC19_OK;
    
    if ( DAC19_ERROR == dac19_check_communication ( ctx ) )
    {
        return DAC19_ERROR;
    }

    return dac19_enable_output ( ctx );
}

err_t dac19_reg_write ( dac19_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 3 ] = { 0 };

    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );

    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t dac19_reg_read ( dac19_t *ctx, uint8_t reg, uint16_t *data_in ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, 2 );
    
    *data_in = rx_buf[ 0 ];
    *data_in <<= 8;
    *data_in |= rx_buf[ 1 ];
    
    return error_flag;
}

void dac19_set_gpi_pin ( dac19_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->gpi, state );
}

err_t dac19_set_value ( dac19_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC19_MAX_DAC_VALUE )
    {
        data_in = DAC19_MAX_DAC_VALUE;
    }
    
    return dac19_reg_write( ctx, DAC19_REG_DAC_DATA, data_in << 2 );
}

err_t dac19_set_voltage ( dac19_t *ctx, uint16_t vref_mv, uint16_t voltage_mv )
{
    uint16_t dac_value = 0;
    uint16_t tmp_data = 0;
    err_t error_flag = dac19_reg_read ( ctx, DAC19_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC19_GEN_CONFIG_INT_REF_EN_MASK;
    tmp_data |= DAC19_GEN_CONFIG_INT_REF_DISABLE;
    error_flag |= dac19_reg_write( ctx, DAC19_REG_GENERAL_CONFIG, tmp_data );
    
    dac_value = ( uint16_t ) ( ( float ) voltage_mv * ( DAC19_MAX_DAC_VALUE + 1 ) / ( float ) vref_mv );
    
    if ( dac_value > DAC19_MAX_DAC_VALUE )
    {
        dac_value = DAC19_MAX_DAC_VALUE;
    }
    error_flag |= dac19_reg_write( ctx, DAC19_REG_DAC_DATA, dac_value << 2 );
    return error_flag;
}

err_t dac19_set_voltage_int_vref ( dac19_t *ctx, uint16_t voltage_mv )
{
    uint16_t dac_value = 0;
    uint16_t tmp_data = 0;
    err_t error_flag = dac19_reg_read ( ctx, DAC19_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC19_GEN_CONFIG_INT_REF_EN_MASK;
    tmp_data |= DAC19_GEN_CONFIG_INT_REF_ENABLE;
    error_flag |= dac19_reg_write( ctx, DAC19_REG_GENERAL_CONFIG, tmp_data );
    tmp_data &= DAC19_GEN_CONFIG_DAC_SPAN_MASK;
            
    if ( DAC19_GEN_CONFIG_DAC_SPAN_GAIN_1_5X == tmp_data )
    {
        dac_value = ( uint16_t ) ( ( float ) voltage_mv * ( DAC19_MAX_DAC_VALUE + 1 ) / 
                                   ( float ) ( DAC19_VREF_INT * 1.5 ) );
    }
    else
    {
        dac_value = ( uint16_t ) ( ( float ) voltage_mv * ( DAC19_MAX_DAC_VALUE + 1 ) / 
                                   ( float ) ( DAC19_VREF_INT * ( tmp_data + 1 ) ) );
    }
    
    if ( dac_value > DAC19_MAX_DAC_VALUE )
    {
        dac_value = DAC19_MAX_DAC_VALUE;
    }
    
    error_flag |= dac19_reg_write( ctx, DAC19_REG_DAC_DATA, dac_value << 2 );
    
    return error_flag;
}

err_t dac19_set_margin_high ( dac19_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC19_MAX_DAC_VALUE )
    {
        data_in = DAC19_MAX_DAC_VALUE;
    }
    
    return dac19_reg_write( ctx, DAC19_REG_DAC_MARGIN_HIGH, data_in << 2 );
}

err_t dac19_set_margin_low ( dac19_t *ctx, uint16_t data_in ) 
{
    if ( data_in > DAC19_MAX_DAC_VALUE )
    {
        data_in = DAC19_MAX_DAC_VALUE;
    }
    
    return dac19_reg_write( ctx, DAC19_REG_DAC_MARGIN_LOW, data_in << 2 );
}

err_t dac19_check_communication ( dac19_t *ctx ) 
{
    uint16_t rx_data = 0;
    err_t error_flag = dac19_reg_read ( ctx, DAC19_REG_STATUS, &rx_data );
    
    if ( DAC19_STATUS_DEVICE_ID != ( rx_data & DAC19_STATUS_DEVICE_ID_MASK ) )
    {
        return DAC19_ERROR;
    }
    
    return error_flag;
}

err_t dac19_enable_output ( dac19_t *ctx ) 
{
    uint16_t tmp_data = 0;
    err_t error_flag = dac19_reg_read ( ctx, DAC19_REG_GENERAL_CONFIG, &tmp_data );
    tmp_data &= ~DAC19_GEN_CONFIG_DAC_PDN_MASK;
    tmp_data |= DAC19_GEN_CONFIG_DAC_PDN_POWER_UP;
    error_flag |= dac19_reg_write( ctx, DAC19_REG_GENERAL_CONFIG, tmp_data );
    return error_flag;
}

// ------------------------------------------------------------------------- END
