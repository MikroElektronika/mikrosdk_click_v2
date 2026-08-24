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
 * @file dac23.c
 * @brief DAC 23 Click Driver.
 */

#include "dac23.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dac23_cfg_setup ( dac23_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->mux  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->ldac = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->resolution = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                        Different MCU's have different resolutions. 
                                                        Change only if necessary.*/
    cfg->vref       = DAC23_ADC_VREF;
}

err_t dac23_init ( dac23_t *ctx, dac23_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->mux;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    ctx->vref = cfg->vref;

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->ldac, cfg->ldac );

    return DAC23_OK;
}

err_t dac23_default_cfg ( dac23_t *ctx ) 
{
    err_t error_flag = DAC23_OK;
    dac23_set_ldac_pin ( ctx, 1 );
    dac23_reset_device ( ctx );
    if ( DAC23_ERROR == dac23_check_com ( ctx ) )
    {
        return DAC23_ERROR;
    }
    error_flag |= dac23_write_reg ( ctx, DAC23_REG_REFERENCE_CONTROL_0, DAC23_REFERENCE_CONTROL_0_SEL_EXT_IN );
    error_flag |= dac23_set_out_range ( ctx, DAC23_OUT_RANGE_0_TO_2_5V );
    error_flag |= dac23_set_out_op_mode ( ctx, DAC23_CHANNEL_ALL, DAC23_OUT_OP_MODE_NORMAL_OP );
    error_flag |= dac23_set_mux_sel ( ctx, DAC23_MUX_SEL_POWERED_DOWN );
    return error_flag;
}

err_t dac23_write_reg ( dac23_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    return dac23_write_regs( ctx, reg, &data_in, 1 );
}

err_t dac23_write_regs ( dac23_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t reg_addr[ 2 ] = { DUMMY, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, reg_addr, 2 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac23_read_reg ( dac23_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    return dac23_read_regs( ctx, reg, data_out, 1 );
}

err_t dac23_read_regs ( dac23_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    uint8_t reg_addr[ 2 ] = { DAC23_SPI_READ_BIT, reg };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, reg_addr, 2, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dac23_write_reg_word ( dac23_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    return dac23_write_regs( ctx, reg, data_buf, 2 );
}

err_t dac23_read_reg_word ( dac23_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( DAC23_OK == dac23_read_regs ( ctx, reg, data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return DAC23_OK;
    }
    return DAC23_ERROR;
}

err_t dac23_read_raw_adc ( dac23_t *ctx, uint16_t *raw_adc ) 
{
    return analog_in_read( &ctx->adc, raw_adc );
}

err_t dac23_read_voltage ( dac23_t *ctx, float *voltage ) 
{
    return analog_in_read_voltage( &ctx->adc, voltage );
}

err_t dac23_read_voltage_avg ( dac23_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    if ( 0 == num_conv )
    {
        return DAC23_ERROR;
    }
    while ( cnt < num_conv )
    {
        if ( DAC23_OK == dac23_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > DAC23_TIMEOUT_MS )
        {
            return DAC23_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return DAC23_OK;
}

err_t dac23_set_vref ( dac23_t *ctx, float vref ) 
{
    ctx->vref = vref;
    return analog_in_set_vref_value( &ctx->adc, vref );
}

void dac23_set_ldac_pin ( dac23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->ldac, state );
}

void dac23_set_rst_pin ( dac23_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void dac23_reset_device ( dac23_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t dac23_check_com ( dac23_t *ctx )
{
    uint16_t product_id = 0;
    uint16_t vendor_id = 0;
    if ( DAC23_ERROR == dac23_read_reg_word ( ctx, DAC23_REG_PRODUCT_ID_H, &product_id ) )
    {
        return DAC23_ERROR;
    }
    if ( DAC23_ERROR == dac23_read_reg_word ( ctx, DAC23_REG_VENDOR_ID_H, &vendor_id ) )
    {
        return DAC23_ERROR;
    }
    if ( ( DAC23_PRODUCT_ID != product_id ) || ( DAC23_VENDOR_ID != vendor_id ) )
    {
        return DAC23_ERROR;
    }
    return DAC23_OK;
}

err_t dac23_set_out_range ( dac23_t *ctx, uint8_t range )
{
    switch ( range )
    {
        case DAC23_OUT_RANGE_0_TO_2_5V:
        {
            ctx->v_zero_scale = DAC23_VZS_OUT_RANGE_0_TO_2_5V;
            ctx->v_full_scale = DAC23_VFS_OUT_RANGE_0_TO_2_5V;
            break;
        }
        case DAC23_OUT_RANGE_0_TO_5V:
        {
            ctx->v_zero_scale = DAC23_VZS_OUT_RANGE_0_TO_5V;
            ctx->v_full_scale = DAC23_VFS_OUT_RANGE_0_TO_5V;
            break;
        }
        default:
        {
            return DAC23_ERROR;
        }
    }
    return dac23_write_reg ( ctx, DAC23_REG_OUTPUT_CONTROL_0, range << 2 );
}

err_t dac23_set_out_op_mode ( dac23_t *ctx, uint8_t channel, uint8_t op_mode )
{
    err_t error_flag = DAC23_OK;
    uint8_t reg_data = 0;
    if ( ( op_mode > DAC23_OUT_OP_MODE_POWERED_DOWN_16K ) || ( channel > DAC23_CHANNEL_ALL ) )
    {
        return DAC23_ERROR;
    }
    if ( DAC23_CHANNEL_ALL == channel )
    {
        reg_data = ( op_mode << ( DAC23_CHANNEL_3 * 2 ) ) | 
                   ( op_mode << ( DAC23_CHANNEL_2 * 2 ) ) | 
                   ( op_mode << ( DAC23_CHANNEL_1 * 2 ) ) | 
                   ( op_mode << ( DAC23_CHANNEL_0 * 2 ) );
    }
    else
    {
        error_flag = dac23_read_reg ( ctx, DAC23_REG_OUTPUT_OPERATING_MODE_0, &reg_data );
        if ( DAC23_OK == error_flag )
        {
            reg_data &= ( ~( DAC23_OUT_OP_MODE_MASK << ( channel * 2 ) ) );
            reg_data |= ( op_mode << ( channel * 2 ) );
        }
    }
    if ( DAC23_OK == error_flag )
    {
        error_flag = dac23_write_reg ( ctx, DAC23_REG_OUTPUT_OPERATING_MODE_0, reg_data );
    }
    return error_flag;
}

err_t dac23_set_mux_sel ( dac23_t *ctx, uint8_t mux_sel )
{
    if ( mux_sel > DAC23_MUX_SEL_AGND )
    {
        return DAC23_ERROR;
    }
    return dac23_write_reg ( ctx, DAC23_REG_MUX_OUT_SELECT_0, mux_sel );
}

err_t dac23_set_dac_value ( dac23_t *ctx, uint8_t channel, uint16_t dac_value )
{
    err_t error_flag = DAC23_OK;
    uint16_t reg_data = 0;
    if ( channel > DAC23_CHANNEL_ALL )
    {
        return DAC23_ERROR;
    }
    if ( DAC23_CHANNEL_ALL == channel )
    {
        error_flag = dac23_write_reg_word ( ctx, DAC23_REG_INPUT_CH0, dac_value );
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_write_reg_word ( ctx, DAC23_REG_INPUT_CH1, dac_value );
        }
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_write_reg_word ( ctx, DAC23_REG_INPUT_CH2, dac_value );
        }
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_write_reg_word ( ctx, DAC23_REG_INPUT_CH3, dac_value );
        }
        if ( DAC23_OK == error_flag )
        {
            dac23_set_ldac_pin ( ctx, 0 );
            Delay_50us ( );
            dac23_set_ldac_pin ( ctx, 1 );
            Delay_1ms ( );
            error_flag = dac23_read_reg_word ( ctx, DAC23_REG_DAC_CH0, &reg_data );
            if ( reg_data != dac_value )
            {
                error_flag = DAC23_ERROR;
            }
        }
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_read_reg_word ( ctx, DAC23_REG_DAC_CH1, &reg_data );
            if ( reg_data != dac_value )
            {
                error_flag = DAC23_ERROR;
            }
        }
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_read_reg_word ( ctx, DAC23_REG_DAC_CH2, &reg_data );
            if ( reg_data != dac_value )
            {
                error_flag = DAC23_ERROR;
            }
        }
        if ( DAC23_OK == error_flag )
        {
            error_flag = dac23_read_reg_word ( ctx, DAC23_REG_DAC_CH3, &reg_data );
            if ( reg_data != dac_value )
            {
                error_flag = DAC23_ERROR;
            }
        }
    }
    else
    {
        error_flag = dac23_write_reg_word ( ctx, DAC23_REG_INPUT_CH0 + channel * 2, dac_value );
        if ( DAC23_OK == error_flag )
        {
            dac23_set_ldac_pin ( ctx, 0 );
            Delay_50us ( );
            dac23_set_ldac_pin ( ctx, 1 );
            Delay_1ms ( );
            error_flag = dac23_read_reg_word ( ctx, DAC23_REG_DAC_CH0 + channel * 2, &reg_data );
            if ( reg_data != dac_value )
            {
                error_flag = DAC23_ERROR;
            }
        }
    }
    return error_flag;
}

err_t dac23_set_out_voltage ( dac23_t *ctx, uint8_t channel, float voltage )
{
    uint16_t dac_value = 0;
    if ( ( voltage < ctx->v_zero_scale ) || ( voltage > ctx->v_full_scale ) )
    {
        return DAC23_ERROR;
    }
    dac_value = ( uint16_t ) ( ( ( voltage - ctx->v_zero_scale ) / 
                                 ( ctx->v_full_scale - ctx->v_zero_scale ) ) * DAC23_DAC_RES_16BIT );
    return dac23_set_dac_value ( ctx, channel, dac_value );
}

// ------------------------------------------------------------------------- END
