/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file poesource.c
 * @brief PoE Source Click Driver.
 */

#include "poesource.h"

void poesource_cfg_setup ( poesource_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = POESOURCE_DEVICE_ADDRESS_0;
}

err_t poesource_init ( poesource_t *ctx, poesource_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t poesource_default_cfg ( poesource_t *ctx )
{
    err_t error_flag = POESOURCE_OK;
    uint8_t reg_data = 0;

    poesource_enable_device ( ctx );
    Delay_100ms ( );
    
    // Set to Automatic mode. The start-up, detection, and classification processes are automated
    error_flag = poesource_read_reg( ctx, POESOURCE_REG_MODE_SETTING, &reg_data );
    if ( POESOURCE_OK == error_flag )
    {
        reg_data &= ( ~POESOURCE_MODE_SETTING_MODE_MASK );
        reg_data |= POESOURCE_MODE_SETTING_MODE_AUTO;
        error_flag = poesource_write_reg( ctx, POESOURCE_REG_MODE_SETTING, reg_data );
    }
    
    // Enable midspan mode
    if ( POESOURCE_OK == error_flag )
    {
        error_flag = poesource_read_reg( ctx, POESOURCE_REG_MIDSPAN_SETTING, &reg_data );
        if ( POESOURCE_OK == error_flag )
        {
            reg_data &= ( ~POESOURCE_MIDSPAN_SETTING_MID_MASK );
            reg_data |= POESOURCE_MIDSPAN_SETTING_MID_ENABLE;
            error_flag = poesource_write_reg( ctx, POESOURCE_REG_MIDSPAN_SETTING, reg_data );
        }
    }

    // Enable all internal IC circuits and the port signals
    if ( POESOURCE_OK == error_flag )
    {
        error_flag = poesource_read_reg( ctx, POESOURCE_REG_PORT_ENABLE, &reg_data );
        if ( POESOURCE_OK == error_flag )
        {
            reg_data &= ( ~( POESOURCE_PORT_ENABLE_ENAL_MASK | POESOURCE_PORT_ENABLE_EN_MASK ) );
            reg_data |= ( POESOURCE_PORT_ENABLE_ENAL_ENABLE | POESOURCE_PORT_ENABLE_EN_ENABLE );
            error_flag = poesource_write_reg( ctx, POESOURCE_REG_PORT_ENABLE, reg_data );
        }
    }

    // Enable the classification and detection processes for the port
    if ( POESOURCE_OK == error_flag )
    {
        error_flag = poesource_read_reg( ctx, POESOURCE_REG_DET_CLS_ENABLE, &reg_data );
        if ( POESOURCE_OK == error_flag )
        {
            reg_data &= ( ~( POESOURCE_DET_CLS_ENABLE_CLSEN_MASK | POESOURCE_DET_CLS_ENABLE_DETEN_MASK ) );
            reg_data |= ( POESOURCE_DET_CLS_ENABLE_CLSEN_ENABLE | POESOURCE_DET_CLS_ENABLE_DETEN_ENABLE );
            error_flag = poesource_write_reg( ctx, POESOURCE_REG_DET_CLS_ENABLE, reg_data );
        }
    }

    // Enable DC load disconnection function
    if ( POESOURCE_OK == error_flag )
    {
        error_flag = poesource_read_reg( ctx, POESOURCE_REG_DISCONNECT_ENABLE, &reg_data );
        if ( POESOURCE_OK == error_flag )
        {
            reg_data &= ( ~POESOURCE_DISCONNECT_ENABLE_DISEN_MASK );
            reg_data |= POESOURCE_DISCONNECT_ENABLE_DISEN_ENABLE;
            error_flag = poesource_write_reg( ctx, POESOURCE_REG_DISCONNECT_ENABLE, reg_data );
        }
    }

    // Enable ADC and disable I2C watchdog
    if ( POESOURCE_OK == error_flag )
    {
        error_flag = poesource_read_reg( ctx, POESOURCE_REG_GENERAL_CONTROL, &reg_data );
        if ( POESOURCE_OK == error_flag )
        {
            reg_data &= ( ~( POESOURCE_GENERAL_CONTROL_ADCEN_MASK | POESOURCE_GENERAL_CONTROL_WDEN_MASK ) );
            reg_data |= POESOURCE_GENERAL_CONTROL_ADCEN_ENABLE;
            error_flag = poesource_write_reg( ctx, POESOURCE_REG_GENERAL_CONTROL, reg_data );
        }
    }

    return error_flag;
}

err_t poesource_write_reg ( poesource_t *ctx, uint8_t reg, uint8_t data_in )
{
    return poesource_write_regs( ctx, reg, &data_in, 1 );
}

err_t poesource_write_regs ( poesource_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t poesource_read_reg ( poesource_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return poesource_read_regs( ctx, reg, data_out, 1 );
}

err_t poesource_read_regs ( poesource_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void poesource_enable_device ( poesource_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void poesource_disable_device ( poesource_t *ctx )
{
    digital_out_low ( &ctx->en );
}

uint8_t poesource_get_int_pin ( poesource_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t poesource_read_adc ( poesource_t *ctx, uint8_t reg, uint16_t *adc_data )
{
    err_t error_flag = POESOURCE_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( POESOURCE_REG_PORT_CURRENT_LSB != reg ) && 
         ( POESOURCE_REG_OUT_PIN_VOLTAGE_LSB != reg ) && 
         ( POESOURCE_REG_INPUT_VOLTAGE_LSB != reg ) && 
         ( POESOURCE_REG_JUNCTION_TEMPERATURE_LSB != reg ) )
    {
        return POESOURCE_ERROR;
    }
    error_flag = poesource_read_regs ( ctx, reg, data_buf, 2 );
    if ( ( POESOURCE_OK == error_flag ) && ( NULL != adc_data ) )
    {
        *adc_data = ( ( uint16_t ) data_buf[ 1 ] << 1 ) | ( data_buf[ 0 ] & 0x01 );
    }
    return error_flag;
}

err_t poesource_read_adc_avg ( poesource_t *ctx, uint8_t reg, uint16_t num_conv, uint16_t *adc_data_avg )
{
    uint16_t adc_data = 0;
    uint32_t adc_data_sum = 0;
    uint16_t cnt = 0;
    uint32_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( POESOURCE_OK == poesource_read_adc ( ctx, reg, &adc_data ) )
        {
            adc_data_sum += adc_data;
            cnt++;
        }
        Delay_50us ( );
        if ( ++timeout_cnt > ( POESOURCE_ADC_TIMEOUT_MS * 20 ) )
        {
            return POESOURCE_ERROR;
        }
    }
    *adc_data_avg = ( adc_data_sum / num_conv );
    return POESOURCE_OK;
}

err_t poesource_read_iout ( poesource_t *ctx, float *current )
{
    err_t error_flag = POESOURCE_OK;
    uint16_t adc_data = 0;
    error_flag = poesource_read_adc_avg ( ctx, POESOURCE_REG_PORT_CURRENT_LSB, POESOURCE_ADC_NUM_CONVERSIONS, &adc_data );
    if ( ( POESOURCE_OK == error_flag ) && ( NULL != current ) )
    {
        *current = POESOURCE_ADC_IOUT_RES * adc_data - POESOURCE_ADC_IOUT_OFFSET;
        if ( *current < 0 )
        {
            *current = 0;
        }
    }
    return error_flag;
}

err_t poesource_read_vout ( poesource_t *ctx, float *voltage )
{
    err_t error_flag = POESOURCE_OK;
    uint16_t adc_data_vin = 0;
    uint16_t adc_data_vout = 0;
    error_flag = poesource_read_adc_avg ( ctx, POESOURCE_REG_OUT_PIN_VOLTAGE_LSB, POESOURCE_ADC_NUM_CONVERSIONS, &adc_data_vout );
    if ( ( POESOURCE_OK == error_flag ) && ( NULL != voltage ) )
    {
        error_flag = poesource_read_adc_avg ( ctx, POESOURCE_REG_INPUT_VOLTAGE_LSB, POESOURCE_ADC_NUM_CONVERSIONS, &adc_data_vin );
        if ( POESOURCE_OK == error_flag )
        {
            *voltage = POESOURCE_ADC_VOUT_RES * ( ( int16_t ) adc_data_vin - adc_data_vout );
        }
    }
    return error_flag;
}

err_t poesource_read_vin ( poesource_t *ctx, float *voltage )
{
    err_t error_flag = POESOURCE_OK;
    uint16_t adc_data = 0;
    error_flag = poesource_read_adc_avg ( ctx, POESOURCE_REG_INPUT_VOLTAGE_LSB, POESOURCE_ADC_NUM_CONVERSIONS, &adc_data );
    if ( ( POESOURCE_OK == error_flag ) && ( NULL != voltage ) )
    {
        *voltage = POESOURCE_ADC_VIN_RES * adc_data;
    }
    return error_flag;
}

err_t poesource_read_die_temp ( poesource_t *ctx, float *temperature )
{
    err_t error_flag = POESOURCE_OK;
    uint16_t adc_data = 0;
    error_flag = poesource_read_adc_avg ( ctx, POESOURCE_REG_JUNCTION_TEMPERATURE_LSB, POESOURCE_ADC_NUM_CONVERSIONS, &adc_data );
    if ( ( POESOURCE_OK == error_flag ) && ( NULL != temperature ) )
    {
        *temperature = POESOURCE_ADC_TEMP_RES * adc_data - POESOURCE_ADC_TEMP_OFFSET;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
