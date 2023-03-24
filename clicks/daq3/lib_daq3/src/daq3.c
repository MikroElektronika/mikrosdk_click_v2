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
 * @file daq3.c
 * @brief DAQ 3 Click Driver.
 */

#include "daq3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY_FULL              0xFF
#define DUMMY_EMPTY             0x00

/**
 * @brief Register bit mask.
 * @details Definition of register bit mask data.
 */
#define DAQ3_REG_BIT_MASK       0x03

/**
 * @brief Reference voltage.
 * @details Definition of reference voltage data.
 */
#define DAQ3_V_REF              2.048

/**
 * @brief Calculation data.
 * @details Definition of calculation data.
 */
#define DAQ_CALC_DIVIDER        131072.0
#define DAQ_NEG_CALC_V_COEFF    6.144
#define DAQ_CALC_V_TO_mV        1000.0
#define DAQ_CALC_RES            131072

/**
 * @brief Data range.
 * @details Definition of data range.
 */
#define DAQ_18_BIT_VAL          0x0003FFFF
#define DAQ_19_BIT_VAL          0x0007FFFF

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void daq3_cfg_setup ( daq3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dam   = HAL_PIN_NC;
    cfg->dre = HAL_PIN_NC;
    cfg->mod = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t daq3_init ( daq3_t *ctx, daq3_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY_FULL ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->dam, cfg->dam );
    digital_out_init( &ctx->dre, cfg->dre );
    digital_out_init( &ctx->mod, cfg->mod );

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return SPI_MASTER_SUCCESS;
}

void daq3_default_cfg ( daq3_t *ctx ) {
    // Click default configuration.

    // Full performance.
    daq3_set_pwr_mode( ctx, DAQ3_FULL_PERFORMANCE_MODE );

    // Power-Up Reference Buffer.
    daq3_set_pwr_down_ref_buf( ctx, DAQ3_PD_REF_POWER_UP );

    // Power-Up Amplifier.
    daq3_set_pwr_down_amp( ctx, DAQ3_PD_AMP_POWER_UP );
    
    daq3_get_voltage( ctx );
}

void daq3_set_pwr_mode ( daq3_t *ctx, uint8_t mode ) {
    if ( mode == DAQ3_FULL_PERFORMANCE_MODE ) {
        digital_out_high( &ctx->mod );
    } else {
        digital_out_low( &ctx->mod );    
    }
}

void daq3_set_pwr_down_ref_buf ( daq3_t *ctx, uint8_t pd_ref ) {
    if ( pd_ref == DAQ3_PD_REF_POWER_UP ) {
        digital_out_high( &ctx->dre );
    } else {
        digital_out_low( &ctx->dre );    
    }
}

void daq3_set_pwr_down_amp ( daq3_t *ctx, uint8_t pd_amp ) {
    if ( pd_amp == DAQ3_PD_AMP_POWER_UP ) {
        digital_out_high( &ctx->dam );
    } else {
        digital_out_low( &ctx->dam );    
    }
}

uint8_t daq3_get_sdo ( daq3_t *ctx ) {
    return digital_in_read( &ctx->int_pin ); 
}

err_t daq3_generic_write ( daq3_t *ctx, uint8_t reg, uint8_t data_in ) {
    uint8_t tx_buf[ 2 ];
    uint8_t tmp_cmd;
    uint8_t tmp_reg_val;
    err_t error_flag;

    reg &= DAQ3_REG_BIT_MASK;
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= DAQ3_REG_CMD;
    tx_buf[ 0 ] |= DAQ3_CMD_REG_READ;
    tx_buf[ 1 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, reg );
    error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, &tmp_cmd, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY_EMPTY );
    spi_master_read( &ctx->spi, &tmp_reg_val, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( ( tmp_cmd != tx_buf[ 0 ] ) || ( tmp_reg_val != data_in ) ) {
        error_flag = -1;    
    }

    return error_flag;
}

err_t daq3_generic_read ( daq3_t *ctx, uint8_t reg, uint8_t *data_out ) {   
    uint8_t tx_buf[ 1 ];
    reg &= DAQ3_REG_BIT_MASK;
    
    tx_buf[ 0 ] = reg;
    tx_buf[ 0 ] |= DAQ3_REG_CMD;
    tx_buf[ 0 ] |= DAQ3_CMD_REG_READ;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t daq3_set_reg_cfg ( daq3_t *ctx, daq3_reg_cfg_t cfg_data ) {
    uint8_t tx_buf[ 2 ];
    uint8_t tmp_cmd;
    uint8_t tmp_reg_val;
    err_t error_flag;
    
    tx_buf[ 0 ] = DAQ3_REG_0;
    tx_buf[ 0 ] |= DAQ3_REG_CMD;
    tx_buf[ 0 ] |= DAQ3_CMD_REG_READ;
    
    tx_buf[ 1 ] = DUMMY_EMPTY;
    tx_buf[ 1 ] |= cfg_data.en_six_st_bits << 4;
    tx_buf[ 1 ] |= cfg_data.span_comp      << 3;
    tx_buf[ 1 ] |= cfg_data.high_z_mode    << 2;
    tx_buf[ 1 ] |= cfg_data.turbo_mode     << 1;

    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DAQ3_REG_0 );
    error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, &tmp_cmd, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY_EMPTY );
    spi_master_read( &ctx->spi, &tmp_reg_val, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    if ( ( tmp_cmd != tx_buf[ 0 ] ) || ( tmp_reg_val != tx_buf[ 1 ] ) ) {
        error_flag = -1;    
    }

    return error_flag;
}

err_t daq3_get_reg_cfg ( daq3_t *ctx, daq3_reg_cfg_t *cfg_data ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 1 ];
    
    tx_buf[ 0 ] = DAQ3_REG_0;
    tx_buf[ 0 ] |= DAQ3_REG_CMD;
    tx_buf[ 0 ] |= DAQ3_CMD_REG_READ;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 1, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    cfg_data->en_six_st_bits = ( rx_buf[ 0 ] >> 4 ) & 0x01;
    cfg_data->span_comp      = ( rx_buf[ 0 ] >> 3 ) & 0x01;
    cfg_data->high_z_mode    = ( rx_buf[ 0 ] >> 2 ) & 0x01;
    cfg_data->turbo_mode     = ( rx_buf[ 0 ] >> 1 ) & 0x01;
    cfg_data->ov_clamp_flag  =   rx_buf[ 0 ]        & 0x01;

    return error_flag;
}

int32_t daq3_get_conversion_result ( daq3_t *ctx, daq3_reg_cfg_t cfg_data ) {   
    uint8_t msb_rx;
    uint8_t lsb_rx;
    uint8_t xlsb_rx;
    uint32_t tmp;
    int32_t adc_data;
    uint8_t tx_buf;
    
    tx_buf &= DAQ3_REG_BIT_MASK;
    tx_buf |= DAQ3_REG_CMD;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, tx_buf );
    spi_master_read( &ctx->spi, &msb_rx, 1 );
    
    tx_buf = DUMMY_EMPTY;
    tx_buf |= cfg_data.en_six_st_bits << 4;
    tx_buf |= cfg_data.span_comp      << 3;
    tx_buf |= cfg_data.high_z_mode    << 2;
    tx_buf |= cfg_data.turbo_mode     << 1;
    
    spi_master_set_default_write_data( &ctx->spi, tx_buf );
    spi_master_read( &ctx->spi, &lsb_rx, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY_FULL );
    spi_master_read( &ctx->spi, &xlsb_rx, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    tmp = msb_rx;
    tmp <<= 8;
    tmp |= lsb_rx;
    tmp <<= 8;
    tmp |= xlsb_rx;
    tmp >>= 5;
    tmp &= DAQ_19_BIT_VAL;
    
    if ( tmp > DAQ_18_BIT_VAL ) {
        adc_data = DAQ_CALC_RES;
        adc_data -= tmp;
    }
    
    return adc_data;
}

float daq3_get_voltage ( daq3_t *ctx ) {   
    uint8_t msb_rx;
    uint8_t lsb_rx;
    uint8_t xlsb_rx;
    uint32_t adc_val;
    float voltage;
        
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DAQ3_REG_CMD );
    spi_master_read( &ctx->spi, &msb_rx, 1 );
    spi_master_set_default_write_data( &ctx->spi, DAQ3_CMD_REG_DEFAULT );
    spi_master_read( &ctx->spi, &lsb_rx, 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY_FULL );
    spi_master_read( &ctx->spi, &xlsb_rx, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    adc_val = msb_rx;
    adc_val <<= 8;
    adc_val |= lsb_rx;
    adc_val <<= 8;
    adc_val |= xlsb_rx;
    adc_val >>= 5;
    adc_val &= DAQ_19_BIT_VAL;
    
    if ( adc_val > DAQ_18_BIT_VAL ) {
        voltage = DAQ_CALC_RES;
        voltage -= ( float ) adc_val;
        voltage *= -DAQ3_V_REF;
        voltage /= DAQ_CALC_DIVIDER;
        voltage -= DAQ_NEG_CALC_V_COEFF;
        
    } else {
        voltage = ( float ) adc_val;
        voltage *= DAQ3_V_REF;
        voltage /= DAQ_CALC_DIVIDER;
    }
    
    voltage *= DAQ_CALC_V_TO_mV;

    return voltage;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
