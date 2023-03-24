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
 * @file loadcell5.c
 * @brief Load Cell 5 Click Driver.
 */

#include "loadcell5.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY           0x00

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_rst_delay( void );

static void dev_measure_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void loadcell5_cfg_setup ( loadcell5_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->gn = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t loadcell5_init ( loadcell5_t *ctx, loadcell5_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->gn, cfg->gn );
    digital_in_init( &ctx->rdy, cfg->rdy );
    
    loadcell5_set_power_mode ( ctx, LOADCELL5_MODE_POWER_DOWN );
    
    loadcell5_filter_select ( ctx, LOADCELL5_UPDATE_RATE_16_7_Hz );

    loadcell5_set_gain( ctx, LOADCELL5_GAIN_1 );

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

err_t loadcell5_default_cfg ( loadcell5_t *ctx ) {
    return loadcell5_set_power_mode( ctx, LOADCELL5_MODE_POWER_UP ); 
}

err_t loadcell5_set_power_mode ( loadcell5_t *ctx, uint8_t pwr_mode ) {
    if ( pwr_mode == LOADCELL5_MODE_POWER_DOWN ) { 
        digital_out_low( &ctx->rst );
        return LOADCELL5_OK;
    } else if ( pwr_mode == LOADCELL5_MODE_POWER_UP ) { 
        digital_out_high( &ctx->rst );  
        return LOADCELL5_OK;
    }
    
    return LOADCELL5_ERROR;
}

void loadcell5_hw_reset ( loadcell5_t *ctx ) {
    loadcell5_set_power_mode ( ctx, LOADCELL5_MODE_POWER_DOWN );
    dev_rst_delay( );
    loadcell5_set_power_mode ( ctx, LOADCELL5_MODE_POWER_UP );
    dev_rst_delay( );
}

err_t loadcell5_filter_select ( loadcell5_t *ctx, uint8_t fil_sel ) {
    if ( fil_sel == LOADCELL5_UPDATE_RATE_16_7_Hz ) { 
        spi_master_select_device( ctx->chip_select );
        return LOADCELL5_OK;
    } else if ( fil_sel == LOADCELL5_UPDATE_RATE_10_Hz ) {
        spi_master_deselect_device( ctx->chip_select ); 
        return LOADCELL5_OK;
    }
    
    return LOADCELL5_ERROR;
}

err_t loadcell5_set_gain ( loadcell5_t *ctx, uint8_t gain ) {
    if ( gain == LOADCELL5_GAIN_1 ) {
        digital_out_high( &ctx->gn );
        return LOADCELL5_OK;
    } else if ( gain == LOADCELL5_GAIN_128 ) {
        digital_out_low( &ctx->gn );
        return LOADCELL5_OK;
    }
    
    return LOADCELL5_ERROR;
}

err_t loadcell5_get_data ( loadcell5_t *ctx, uint8_t *status, uint32_t *adc_data ) {
    uint8_t rx_buf[ 4 ];
    uint32_t adc_tmp;
       
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 4 );

    *status = rx_buf[ 0 ];
    
    adc_tmp = rx_buf[ 1 ];
    adc_tmp <<= 8;
    adc_tmp |= rx_buf[ 2 ];
    adc_tmp <<= 8;
    adc_tmp |= rx_buf[ 3 ];
    
    *adc_data = adc_tmp;

    return error_flag;
}

uint32_t loadcell5_read_adc ( loadcell5_t *ctx ) {
    uint8_t rx_buf[ 4 ];
    uint32_t adc_res;
    uint8_t status;
    
    status = DUMMY;

    while ( status != LOADCELL5_STATUS_CONVERSION_NOT_AVAILABLE ) { 
        err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 4 );
        status = rx_buf[ 0 ];
        adc_res = rx_buf[ 1 ];
        adc_res <<= 8;
        adc_res |= rx_buf[ 2 ];
        adc_res <<= 8;
        adc_res |= rx_buf[ 3 ]; 
        dev_measure_delay( );
    }
    
    return adc_res;
}

void loadcell5_tare ( loadcell5_t *ctx, loadcell5_data_t *cell_data ) {
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;

    for ( n_cnt = 0; n_cnt < 5; n_cnt++ ) {
        results = loadcell5_read_adc( ctx );
        dev_measure_delay( );
    }

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 10; n_cnt++ ) {
        results = loadcell5_read_adc( ctx );
        sum_val += results;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 10.0;

    cell_data->tare = average_val;
    cell_data->tare_ok = LOADCELL5_DATA_OK;
    cell_data->weight_data_100g_ok = LOADCELL5_DATA_NO_DATA;
    cell_data->weight_data_500g_ok = LOADCELL5_DATA_NO_DATA;
    cell_data->weight_data_1000g_ok = LOADCELL5_DATA_NO_DATA;
    cell_data->weight_data_5000g_ok = LOADCELL5_DATA_NO_DATA;
    cell_data->weight_data_10000g_ok = LOADCELL5_DATA_NO_DATA;
}

err_t loadcell5_calibration ( loadcell5_t *ctx, uint16_t cal_val, loadcell5_data_t *cell_data ) {
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    err_t status;

    status = LOADCELL5_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 15; n_cnt++ ) {
        results = loadcell5_read_adc( ctx );
        sum_val += results;
        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 15.0;

    weight_val = average_val - tare_val;

    switch ( cal_val ) {
        case LOADCELL5_WEIGHT_100G : {
            cell_data->weight_coeff_100g = 100.0 / weight_val;
            cell_data->weight_data_100g_ok = LOADCELL5_DATA_OK;
            break;
        }
        case LOADCELL5_WEIGHT_500G : {
            cell_data->weight_coeff_500g = 500.0 / weight_val;
            cell_data->weight_data_500g_ok = LOADCELL5_DATA_OK;
            break;
        }
        case LOADCELL5_WEIGHT_1000G : {
            cell_data->weight_coeff_1000g = 1000.0 / weight_val;
            cell_data->weight_data_1000g_ok = LOADCELL5_DATA_OK;
            break;
        }
        case LOADCELL5_WEIGHT_5000G : {
            cell_data->weight_coeff_5000g = 5000.0 / weight_val;
            cell_data->weight_data_5000g_ok = LOADCELL5_DATA_OK;
            break;
        }
        case LOADCELL5_WEIGHT_10000G : {
            cell_data->weight_coeff_10000g = 10000.0 / weight_val;
            cell_data->weight_data_10000g_ok = LOADCELL5_DATA_OK;
            break;
        }
        default : {
            status = LOADCELL5_ERROR;
            cell_data->weight_data_100g_ok = LOADCELL5_DATA_NO_DATA;
            cell_data->weight_data_500g_ok = LOADCELL5_DATA_NO_DATA;
            cell_data->weight_data_1000g_ok = LOADCELL5_DATA_NO_DATA;
            cell_data->weight_data_5000g_ok = LOADCELL5_DATA_NO_DATA;
            cell_data->weight_data_10000g_ok = LOADCELL5_DATA_NO_DATA;
            break;
        }
    }

    return status;
}

float loadcell5_get_weight ( loadcell5_t *ctx, loadcell5_data_t *cell_data ) {
    uint32_t results;
    uint8_t n_cnt;
    uint32_t sum_val;
    float average_val;
    float tare_val;
    float weight_val;
    uint8_t status;

    status = LOADCELL5_OK;

    tare_val = cell_data->tare;

    sum_val = 0;

    for ( n_cnt = 0; n_cnt < 15; n_cnt++ ) {
        results = loadcell5_read_adc( ctx );

        sum_val += results;

        dev_measure_delay( );
    }

    average_val = ( float ) sum_val;
    average_val /= 15.0;

    weight_val = average_val - tare_val;

    if ( cell_data->weight_data_100g_ok == LOADCELL5_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_100g;
    }
    else if ( cell_data->weight_data_500g_ok == LOADCELL5_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_500g;
    }
    else if ( cell_data->weight_data_1000g_ok == LOADCELL5_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_1000g;
    }
    else if ( cell_data->weight_data_5000g_ok == LOADCELL5_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_5000g;
    }
    else if ( cell_data->weight_data_10000g_ok == LOADCELL5_DATA_OK ) {
        weight_val *= cell_data->weight_coeff_10000g;
    }

    if ( weight_val < 0 ) {
        weight_val = LOADCELL5_WEIGHT_ZERO;
    }

    return weight_val;
}

uint8_t loadcell5_check_data_ready ( loadcell5_t *ctx ) {
    return digital_in_read( &ctx->rdy );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_rst_delay( void ) {
    Delay_10ms( );
}

static void dev_measure_delay ( void ) {
    Delay_100ms( );
    Delay_10ms( );
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
