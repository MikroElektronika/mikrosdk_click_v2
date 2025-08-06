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
 * @file adac4.c
 * @brief ADAC 4 Click Driver.
 */

#include "adac4.h"

void adac4_cfg_setup ( adac4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ADAC4_DEVICE_ADDRESS_1;
}

err_t adac4_init ( adac4_t *ctx, adac4_cfg_t *cfg ) 
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

    return I2C_MASTER_SUCCESS;
}

err_t adac4_default_cfg ( adac4_t *ctx ) 
{
    err_t error_flag = ADAC4_OK;
    adac4_reset_device ( ctx );

    if ( ADAC4_ERROR == adac4_check_communication ( ctx ) )
    {
        return ADAC4_ERROR;
    }

    // Enable internal 2.5V voltage reference
    error_flag |= adac4_write_reg ( ctx, ADAC4_REG_POWER_DOWN_CTRL, 
                                    ADAC4_POWER_DOWN_CTRL_EN_REF );
    ctx->vref = ADAC4_VREF_INT;

    // Enable all DAC channels
    error_flag |= adac4_write_reg ( ctx, ADAC4_REG_DAC_SEL, ADAC4_DAC_SEL_ALL_CHANNELS );

    // Dummy read die temperature to enable sensor
    float die_temp = 0;
    error_flag |= adac4_read_die_temp ( ctx, &die_temp );
    Delay_100ms ( );

    return error_flag;
}

err_t adac4_write_reg ( adac4_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t adac4_read_reg ( adac4_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
    if ( ( ADAC4_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

void adac4_set_rst_pin ( adac4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void adac4_reset_device ( adac4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t adac4_check_communication ( adac4_t *ctx )
{
    uint16_t chip_id = 0;
    if ( ADAC4_OK == adac4_read_reg ( ctx, ADAC4_REG_CHIP_ID, &chip_id ) )
    {
        if ( ADAC4_CHIP_ID == chip_id )
        {
            return ADAC4_OK;
        }
    }
    return ADAC4_ERROR;
}

err_t adac4_write_dac ( adac4_t *ctx, uint8_t channel, uint16_t dac_data )
{
    if ( ( channel > ADAC4_CHANNEL_7 ) || ( dac_data > ADAC4_DAC_DATA_MAX ) )
    {
        return ADAC4_ERROR;
    }
    return adac4_write_reg ( ctx, ADAC4_REG_DAC_WRITE | channel, ADAC4_ADC_DATA_MSB | dac_data );
}

err_t adac4_read_raw_adc ( adac4_t *ctx, uint8_t channel, uint16_t *raw_adc )
{
    err_t error_flag = ADAC4_OK;
    uint16_t adc_data = 0;
    if ( ( channel > ADAC4_CHANNEL_7 ) || ( NULL == raw_adc ) )
    {
        return ADAC4_ERROR;
    }
    error_flag |= adac4_write_reg ( ctx, ADAC4_REG_ADC_SEL, ADAC4_ADC_SEQ_ADC0_SEL << channel );
    if ( ADAC4_OK == error_flag )
    {
        error_flag |= adac4_write_reg ( ctx, ADAC4_REG_ADC_SEQ, ADAC4_ADC_SEQ_ADC0_SEL << channel );
    }
    if ( ADAC4_OK == error_flag )
    {
        error_flag |= adac4_read_reg ( ctx, ADAC4_REG_ADC_READ, &adc_data );
    }
    if ( ( ADAC4_OK == error_flag ) && 
         ( ADAC4_ADC_DATA_MSB != ( adc_data & ADAC4_ADC_DATA_MSB ) ) &&
         ( channel == ( ( adc_data & ADAC4_ADC_DATA_ADDR_MASK ) >> 12 ) ) )
    {
        *raw_adc = ( adc_data & ADAC4_ADC_DATA_DATA_MASK );
    }
    return error_flag;
}

err_t adac4_read_adc_voltage ( adac4_t *ctx, uint8_t channel, float *voltage )
{
    err_t error_flag = ADAC4_OK;
    uint16_t adc_dac_cfg = 0;
    uint16_t adc_data = 0;
    if ( ( channel > ADAC4_CHANNEL_7 ) || ( NULL == voltage ) )
    {
        return ADAC4_ERROR;
    }
    error_flag |= adac4_read_raw_adc ( ctx, channel, &adc_data );
    if ( ADAC4_OK == error_flag )
    {
        *voltage = ( ( float ) adc_data / ADAC4_ADC_DATA_DATA_MASK ) * ctx->vref;
    }
    return error_flag;
}

err_t adac4_read_die_temp ( adac4_t *ctx, float *die_temp )
{
    err_t error_flag = ADAC4_OK;
    uint16_t adc_data = 0;
    if ( NULL == die_temp )
    {
        return ADAC4_ERROR;
    }
    error_flag |= adac4_write_reg ( ctx, ADAC4_REG_ADC_SEQ, ADAC4_ADC_SEQ_TEMP_EN );
    if ( ADAC4_OK == error_flag )
    {
        error_flag |= adac4_read_reg ( ctx, ADAC4_REG_ADC_READ, &adc_data );
    }
    if ( ( ADAC4_OK == error_flag ) && ( adc_data & ADAC4_ADC_DATA_MSB ) )
    {
        *die_temp = ( ( adc_data & ADAC4_ADC_DATA_DATA_MASK ) - ADAC4_TEMP_OFFSET ) / ADAC4_TEMP_RES;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
