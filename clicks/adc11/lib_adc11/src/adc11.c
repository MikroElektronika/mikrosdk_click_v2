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
 * @file adc11.c
 * @brief ADC 11 Click Driver.
 */

#include "adc11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                0x00

/**
 * @brief Sample number.
 * @details Number of ADC samples.
 */
#define SAMPLE_NUM            100

/**
 * @brief Resolution.
 * @details 12-bit resolution.
 */
#define DATA_RES_12_BITS     4096

/**
 * @brief Calculation divider.
 * @details Conversion calculation divider.
 */
#define CALC_DIV_V        1000000

void adc11_cfg_setup ( adc11_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc11_init ( adc11_t *ctx, adc11_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
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

    return SPI_MASTER_SUCCESS;
}

err_t adc11_generic_read ( adc11_t *ctx, uint16_t *adc_data ) {
    uint8_t rx_buf[ 2 ];
    uint16_t result;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    
    *adc_data = result;

    return error_flag;
}

err_t adc11_set_calibration ( adc11_t *ctx, adc11_calibration_data_t *adc_val ) {
    float avg_val = 0;
    uint16_t adc_data;
    err_t error_flag;
    
    for ( uint8_t n_cnt = 0; n_cnt < SAMPLE_NUM; n_cnt++ ) {
        error_flag = adc11_generic_read ( ctx, &adc_data );
        avg_val += ( float ) adc_data;
        Delay_1ms( );
    }
    
    avg_val /= SAMPLE_NUM;
    
    adc_val->zero_adc_val = ( uint16_t ) avg_val;
    
    return error_flag;
}


err_t adc11_get_voltage ( adc11_t *ctx, adc11_calibration_data_t *adc_val, float *voltage ) {
    float avg_val = 0;
    float tmp_voltage;
    uint16_t adc_data;
    err_t error_flag;

    for ( uint8_t n_cnt = 0; n_cnt < SAMPLE_NUM; n_cnt++ ) {
        error_flag = adc11_generic_read ( ctx, &adc_data );
        avg_val += ( float ) adc_data;
        Delay_1ms( );
    }

    avg_val /= SAMPLE_NUM;
    avg_val -= adc_val->zero_adc_val;
    avg_val *= DATA_RES_12_BITS;
    avg_val /= CALC_DIV_V;
    
    *voltage = avg_val;

    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
