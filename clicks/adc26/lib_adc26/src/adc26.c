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
 * @file adc26.c
 * @brief ADC 26 Click Driver.
 */

#include "adc26.h"

void adc26_cfg_setup ( adc26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADC26_DEVICE_ADDRESS_GND;
}

err_t adc26_init ( adc26_t *ctx, adc26_cfg_t *cfg ) 
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

err_t adc26_default_cfg ( adc26_t *ctx ) 
{
    err_t error_flag = ADC26_OK;
    error_flag |= adc26_write_reg ( ctx, ADC26_REG_CONFIG, ADC26_CONFIG_OS_NO_EFFECT | 
                                                           ADC26_CONFIG_MUX_P_AIN0_N_AIN1 | 
                                                           ADC26_CONFIG_PGA_2_048V | 
                                                           ADC26_CONFIG_MODE_SINGLE_SHOT | 
                                                           ADC26_CONFIG_DR_128_SPS | 
                                                           ADC26_CONFIG_COMP_MODE_TRADITIONAL | 
                                                           ADC26_CONFIG_COMP_POL_ACTIVE_LOW | 
                                                           ADC26_CONFIG_COMP_LAT_LATCHING | 
                                                           ADC26_CONFIG_COMP_QUE_FOUR_CONV );
    error_flag |= adc26_write_threshold ( ctx, ADC26_ADC_MAX, ADC26_ADC_MIN );
    return error_flag;
}

err_t adc26_write_reg ( adc26_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( reg > ADC26_REG_HI_THRESH )
    {
        return ADC26_ERROR;
    }
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t adc26_read_reg ( adc26_t *ctx, uint8_t reg, uint16_t *data_out )
{
    err_t error_flag = ADC26_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( reg > ADC26_REG_HI_THRESH ) || ( NULL == data_out ) )
    {
        return ADC26_ERROR;
    }
    error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ADC26_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

uint8_t adc26_get_alert_pin ( adc26_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

err_t adc26_start_conversion ( adc26_t *ctx, uint8_t mux, uint8_t pga )
{
    err_t error_flag = ADC26_OK;
    uint16_t config = 0;
    if ( ( mux > ADC26_MUX_P_AIN3_N_GND ) || ( pga > ADC26_PGA_4_096V ) )
    {
        return ADC26_ERROR;
    }
    error_flag = adc26_read_reg( ctx, ADC26_REG_CONFIG, &config );
    if ( ADC26_OK == error_flag )
    {
        config &= ( ~ADC26_CONFIG_MUX_MASK );
        config |= ( ( uint16_t ) mux << 12 );
        config &= ( ~ADC26_CONFIG_PGA_MASK );
        config |= ( ADC26_CONFIG_PGA_0_256V - ( ( uint16_t ) pga << 9 ) );
        config |= ADC26_CONFIG_OS_START_CONVERSION;
        error_flag = adc26_write_reg( ctx, ADC26_REG_CONFIG, config );
    }
    return error_flag;
}

err_t adc26_write_threshold ( adc26_t *ctx, int16_t lo_thresh, int16_t hi_thresh )
{
    err_t error_flag = ADC26_OK;
    uint16_t thresh = 0;
    if ( ( lo_thresh > ADC26_ADC_MAX ) || ( lo_thresh < ADC26_ADC_MIN ) || 
         ( hi_thresh > ADC26_ADC_MAX ) || ( hi_thresh < ADC26_ADC_MIN ) )
    {
        return ADC26_ERROR;
    }
    thresh = ( lo_thresh << 4 );
    error_flag = adc26_write_reg( ctx, ADC26_REG_LO_THRESH, thresh );
    if ( ADC26_OK == error_flag )
    {
        thresh = ( hi_thresh << 4 );
        error_flag = adc26_write_reg( ctx, ADC26_REG_HI_THRESH, thresh );
    }
    return error_flag;
}

err_t adc26_read_adc ( adc26_t *ctx, int16_t *data_out )
{
    err_t error_flag = ADC26_OK;
    uint16_t conversion = 0;
    if ( NULL == data_out )
    {
        return ADC26_ERROR;
    }
    error_flag = adc26_read_reg( ctx, ADC26_REG_CONVERSION, &conversion );
    if ( ADC26_OK == error_flag )
    {
        *data_out = conversion;
        *data_out >>= 4;
    }
    return error_flag;
}

err_t adc26_read_voltage ( adc26_t *ctx, float *voltage )
{
    err_t error_flag = ADC26_OK;
    uint16_t config = 0;
    int16_t raw_adc = 0;
    if ( NULL == voltage )
    {
        return ADC26_ERROR;
    }
    error_flag = adc26_read_reg( ctx, ADC26_REG_CONFIG, &config );
    if ( ADC26_OK == error_flag )
    {
        error_flag = adc26_read_adc( ctx, &raw_adc );
    }
    if ( ( ADC26_OK == error_flag ) && ( config & ADC26_CONFIG_OS_MASK ) )
    {
        config &= ADC26_CONFIG_PGA_MASK;
        config = ADC26_CONFIG_PGA_0_256V - config;
        config >>= 9;
        *voltage = raw_adc * ( ADC26_ADC_GAIN_MIN * ( 1 << config ) ) / ADC26_ADC_RESOLUTION;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
