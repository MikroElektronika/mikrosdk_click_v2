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
 * @file adc13.c
 * @brief ADC 13 Click Driver.
 */

#include "adc13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc13_cfg_setup ( adc13_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->str  = HAL_PIN_NC;
    cfg->dtr  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc13_init ( adc13_t *ctx, adc13_cfg_t *cfg ) 
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
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->str, cfg->str );

    digital_in_init( &ctx->dtr, cfg->dtr );

    return SPI_MASTER_SUCCESS;
}

err_t adc13_default_cfg ( adc13_t *ctx ) 
{
    SET_SPI_DATA_SAMPLE_EDGE;
    adc13_power_up ( ctx );
    err_t error_flag = adc13_reset_by_command( ctx );
    
    // Clear reset flag
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_POWER, ADC13_POWER_RESET_MASK, ADC13_POWER_RESET_NO_NEW_RESET );
    
    // Set sample rate and gain
    error_flag |= adc13_set_gain( ctx, ADC13_MODE2_GAIN_1 );
    error_flag |= adc13_set_sample_rate( ctx, ADC13_MODE2_DR_20SPS );
    
    // Set input channels
    error_flag |= adc13_set_input_channel( ctx, ADC13_INPMUX_MUXP_AIN0, ADC13_INPMUX_MUXN_AIN1 );
    
    // Set voltage reference
    error_flag |= adc13_set_voltage_reference( ctx, ADC13_REFMUX_RMUXP_INTERNAL, ADC13_REFMUX_RMUXN_INTERNAL );
    
    return error_flag;
}

err_t adc13_generic_write ( adc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t adc13_generic_read ( adc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t adc13_send_command ( adc13_t *ctx, uint8_t cmd ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void adc13_set_str_pin ( adc13_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->str, state );
}

void adc13_set_rst_pin ( adc13_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t adc13_get_dtr_pin ( adc13_t *ctx )
{
    return digital_in_read( &ctx->dtr );
}

void adc13_reset_by_pin ( adc13_t *ctx )
{
    adc13_set_rst_pin( ctx, 0 );
    Delay_1ms( );
    adc13_set_rst_pin( ctx, 1 );
    Delay_1ms( );
}

err_t adc13_reset_by_command ( adc13_t *ctx )
{
    err_t error_flag = adc13_send_command ( ctx, ADC13_CMD_RESET );
    Delay_10ms( );
    return error_flag;
}

void adc13_power_down ( adc13_t *ctx )
{
    adc13_set_rst_pin( ctx, 0 );
    Delay_10ms( );
}

void adc13_power_up ( adc13_t *ctx )
{
    adc13_set_rst_pin( ctx, 1 );
    Delay_10ms( );
}

err_t adc13_read_register ( adc13_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return adc13_read_registers( ctx, reg, data_out, 1 );
}

err_t adc13_write_register ( adc13_t *ctx, uint8_t reg, uint8_t data_in )
{
    return adc13_write_registers( ctx, reg, &data_in, 1 );
}

err_t adc13_read_registers ( adc13_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t count )
{
    uint8_t opcode[ 2 ] = { 0 };
    
    reg &= ADC13_REG_COUNT_MASK;
    count &= ADC13_REG_COUNT_MASK;
    
    if ( ( reg + count - 1 ) > ADC13_REG_GPIODAT || count < 1 )
    {
        return ADC13_ERROR;
    }
    opcode[ 0 ] = reg | ADC13_CMD_RREG;
    opcode[ 1 ] = count - 1;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, opcode, 2, data_out, count );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t adc13_write_registers ( adc13_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t count )
{
    uint8_t tx_buf[ ADC13_REG_GPIODAT + 3 ] = { 0 };
    
    reg &= ADC13_REG_COUNT_MASK;
    count &= ADC13_REG_COUNT_MASK;
    
    if ( ( reg + count - 1 ) > ADC13_REG_GPIODAT || count < 1 )
    {
        return ADC13_ERROR;
    }
    tx_buf[ 0 ] = reg | ADC13_CMD_WREG;
    tx_buf[ 1 ] = count - 1;
    
    for ( uint8_t cnt = 0; cnt < count; cnt++ )
    {
        tx_buf[ cnt + 2 ] = data_in[ cnt ];
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, count + 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t adc13_set_register_bits ( adc13_t *ctx, uint8_t reg, uint8_t bit_mask, uint8_t data_in )
{
    uint8_t reg_data = 0;
    err_t error_flag = adc13_read_register( ctx, reg, &reg_data );
    reg_data = SET_REG_BITS( reg_data, bit_mask, data_in );
    error_flag |= adc13_write_register( ctx, reg, reg_data );
    return error_flag;
}

err_t adc13_get_register_bits ( adc13_t *ctx, uint8_t reg, uint8_t bit_mask, uint8_t *data_out )
{
    uint8_t reg_data = 0;
    err_t error_flag = adc13_read_register( ctx, reg, &reg_data );
    *data_out = GET_REG_BITS( reg_data, bit_mask );
    return error_flag;
}

err_t adc13_read_raw_data ( adc13_t *ctx, int32_t *data_out )
{
    uint8_t rx_buf[ 6 ] = { 0 };
    uint16_t checksum = ADC13_CHECKSUM_CONSTANT;
    adc13_set_str_pin( ctx, 1 );
    while ( adc13_get_dtr_pin ( ctx ) );
    err_t error_flag = adc13_generic_read( ctx, ADC13_CMD_RDATA1, rx_buf, 6 );
    adc13_set_str_pin( ctx, 0 );
    
    if ( 0 == ( rx_buf[ 0 ] & ADC13_STATUS_ADC1_NEW_DATA ) )
    {
        return ADC13_ERROR;
    }
    checksum = checksum + rx_buf[ 1 ] + rx_buf[ 2 ] + rx_buf[ 3 ] + rx_buf[ 4 ];
    
    if ( ( checksum & 0x00FF ) != rx_buf[ 5 ] )
    {
        return ADC13_ERROR;
    }
    *data_out = rx_buf[ 1 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 2 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 3 ];
    *data_out <<= 8;
    *data_out |= rx_buf[ 4 ];

    return error_flag;
}

err_t adc13_measure_voltage ( adc13_t *ctx, float vref, float *voltage )
{
    int32_t raw_adc = 0;
    uint8_t gain = 0;
    err_t error_flag = adc13_read_raw_data ( ctx, &raw_adc );
    
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_GAIN_MASK, &gain );
    gain = 1 << gain;
    
    *voltage = vref / gain;
    *voltage /=  ( 1ul << 31 );
    *voltage *= raw_adc;
    
    return error_flag;
}

err_t adc13_measure_temperature ( adc13_t *ctx, float *temperature )
{
    float voltage = 0;
    uint8_t gain = 0;
    uint8_t pga = 0;
    uint8_t chop = 0;
    uint8_t vref_pos = 0;
    uint8_t vref_neg = 0;
    uint8_t inp_pos = 0;
    uint8_t inp_neg = 0;
    
    err_t error_flag = adc13_get_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_GAIN_MASK, &gain );
    error_flag |= adc13_set_gain( ctx, ADC13_MODE2_GAIN_1 );
    
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_BYPASS_MASK, &pga );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_BYPASS_MASK, ADC13_MODE2_BYPASS_PGA_ENABLED );
    
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_MODE0, ADC13_MODE0_CHOP_MASK, &chop );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_MODE0, ADC13_MODE0_CHOP_MASK, ADC13_MODE0_CHOP_DISABLE );
    
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_INPMUX, ADC13_INPMUX_MUXP_MASK, &inp_pos );
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_INPMUX, ADC13_INPMUX_MUXN_MASK, &inp_neg );
    error_flag |= adc13_set_input_channel( ctx, ADC13_INPMUX_MUXP_TEMP_SENSOR_POS, ADC13_INPMUX_MUXN_TEMP_SENSOR_NEG );
    
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_REFMUX, ADC13_REFMUX_RMUXP_MASK, &vref_pos );
    error_flag |= adc13_get_register_bits( ctx, ADC13_REG_REFMUX, ADC13_REFMUX_RMUXN_MASK, &vref_neg );
    error_flag |= adc13_set_voltage_reference( ctx, ADC13_REFMUX_RMUXP_INTERNAL, ADC13_REFMUX_RMUXN_INTERNAL );
    
    error_flag |= adc13_measure_voltage( ctx, ADC13_VREF_INTERNAL, &voltage );
    *temperature = ( ( voltage * ADC13_TEMP_V_TO_MV - ADC13_TEMP_MILIVOLTS ) / ADC13_TEMP_COEFF ) + ADC13_TEMP_OFFSET;
    *temperature -= ADC13_TEMP_HEAT_OFFSET;
    error_flag |= adc13_set_gain( ctx, gain );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_BYPASS_MASK, pga );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_MODE0, ADC13_MODE0_CHOP_MASK, chop );
    error_flag |= adc13_set_input_channel( ctx, inp_pos, inp_neg );
    error_flag |= adc13_set_voltage_reference( ctx, vref_pos, vref_neg );
    
    return error_flag;
}

err_t adc13_set_input_channel ( adc13_t *ctx, uint8_t pos, uint8_t neg )
{
    if ( pos > ADC13_INPMUX_MUXP_FLOAT || neg > ADC13_INPMUX_MUXN_FLOAT )
    {
        return ADC13_ERROR;
    }
    err_t error_flag = adc13_set_register_bits( ctx, ADC13_REG_INPMUX, ADC13_INPMUX_MUXP_MASK, pos );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_INPMUX, ADC13_INPMUX_MUXN_MASK, neg );
    
    return error_flag;
}

err_t adc13_set_voltage_reference ( adc13_t *ctx, uint8_t pos, uint8_t neg )
{
    if ( pos > ADC13_REFMUX_RMUXP_INTERNAL_AVDD || neg > ADC13_REFMUX_RMUXN_INTERNAL_AVSS )
    {
        return ADC13_ERROR;
    }
    err_t error_flag = adc13_set_register_bits( ctx, ADC13_REG_REFMUX, ADC13_REFMUX_RMUXP_MASK, pos );
    error_flag |= adc13_set_register_bits( ctx, ADC13_REG_REFMUX, ADC13_REFMUX_RMUXN_MASK, neg );
    
    return error_flag;
}

err_t adc13_set_gain ( adc13_t *ctx, uint8_t gain )
{
    if ( gain > ADC13_MODE2_GAIN_32 )
    {
        return ADC13_ERROR;
    }
    return adc13_set_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_GAIN_MASK, gain );
}

err_t adc13_set_sample_rate ( adc13_t *ctx, uint8_t s_rate )
{
    if ( s_rate > ADC13_MODE2_DR_38400SPS )
    {
        return ADC13_ERROR;
    }
    return adc13_set_register_bits( ctx, ADC13_REG_MODE2, ADC13_MODE2_DR_MASK, s_rate );
}

// ------------------------------------------------------------------------- END
