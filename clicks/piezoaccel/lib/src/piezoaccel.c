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
 * @file piezoaccel.c
 * @brief Piezo Accel Click Driver.
 */

#include "piezoaccel.h"

// ------------------------------------------------------------- PRIVATE MACROS

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Piezo Accel Click onboard Vref.
 * @details Value of LTC1864 Vref voltage.
 */
#define DEV_PIEZOACCEL_VREF              4.096

/**
 * @brief Piezo Accel Click resolution.
 * @details Max ADC value of LTC1864.
 */
#define DEV_PIEZOACCEL_MAX               65535

/**
 * @brief Piezo Accel Click zero position 5V.
 * @details This value represents 0g when sensor
 * is powered with 5V supply.
 */
#define DEV_PIEZOACCEL_ZERO_G_5V         2.5

/**
 * @brief Piezo Accel Click zero position 3.3V.
 * @details This value represents 0g when sensor
 * is powered with 3.3V supply.
 */
#define DEV_PIEZOACCEL_ZERO_G_3V3        1.65

/**
 * @brief Piezo Accel Click g unit coefficient.
 * @details Step coefficient for conversion from
 * voltage to g unit.
 */
#define DEV_PIEZOACCEL_ZERO_G_COEF       0.05

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS

static void adc_conv_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void piezoaccel_cfg_setup ( piezoaccel_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_12_BIT;
    cfg->vref       = 3.3;  // Should be set via CODEGRIP since it uses the dev board Vref
}

err_t piezoaccel_init ( piezoaccel_t *ctx, piezoaccel_cfg_t *cfg ) {
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
    
    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_vref_value( &ctx->adc, cfg->vref ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    if ( analog_in_set_resolution( &ctx->adc, cfg->resolution ) == ADC_ERROR ) {
        return ADC_ERROR;
    }

    return SPI_MASTER_SUCCESS;
}

void piezoaccel_default_cfg ( piezoaccel_t *ctx, piezoaccel_setup_t *setup_cfg_data ) {
    // Click default configuration.
    
    spi_master_select_device( ctx->chip_select );
    
    setup_cfg_data->measurement_mode = PIEZOACCEL_MEAS_MODE_ADC;
    setup_cfg_data->sensor_voltage = PIEZOACCEL_SENSOR_VOLTAGE_5V;
    piezoaccel_calibration( ctx, setup_cfg_data );
}

uint16_t piezoaccel_adc_raw_read ( piezoaccel_t *ctx ) {
    uint8_t rx_buf[ 2 ];
    uint16_t adc_val;
    
    spi_master_deselect_device( ctx->chip_select );
    adc_conv_delay( );
    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    adc_val = rx_buf[ 0 ];
    adc_val <<= 8;
    adc_val |= rx_buf[ 1 ];

    return adc_val;
}

float piezoaccel_adc_voltage_read ( piezoaccel_t *ctx ) {
    float adc_voltage;
    
    adc_voltage = piezoaccel_adc_raw_read( ctx );
    adc_voltage = ( adc_voltage * DEV_PIEZOACCEL_VREF ) / DEV_PIEZOACCEL_MAX;
    
    return adc_voltage;
}

err_t piezoaccel_read_an_pin_value ( piezoaccel_t *ctx, uint16_t *data_out ) {
    return analog_in_read( &ctx->adc, data_out );
}

err_t piezoaccel_read_an_pin_voltage ( piezoaccel_t *ctx, float *data_out ) {
    return analog_in_read_voltage( &ctx->adc, data_out );
}

float piezoaccel_g_unit_read ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data ) {
    float g_unit;
    
    if ( cfg_data->measurement_mode == PIEZOACCEL_MEAS_MODE_AN_PIN ) {
        if ( cfg_data->sensor_voltage == PIEZOACCEL_SENSOR_VOLTAGE_3V3 ) {
            analog_in_read_voltage( &ctx->adc, &g_unit );
            g_unit -= cfg_data->offset_data;
            g_unit = ( g_unit - DEV_PIEZOACCEL_ZERO_G_3V3 ) / DEV_PIEZOACCEL_ZERO_G_COEF;
        } else {
            return 0;                                 // ARM MCU Vref = 5V not supported.
        }
    } else {
        g_unit = piezoaccel_adc_voltage_read( ctx );
        g_unit -= cfg_data->offset_data;
        if ( cfg_data->sensor_voltage == PIEZOACCEL_SENSOR_VOLTAGE_3V3 ) {
            g_unit = ( g_unit - DEV_PIEZOACCEL_ZERO_G_3V3 ) / DEV_PIEZOACCEL_ZERO_G_COEF;
        } else {
            g_unit = ( g_unit - DEV_PIEZOACCEL_ZERO_G_5V ) / DEV_PIEZOACCEL_ZERO_G_COEF;
        }
    }
    return g_unit;
}

void piezoaccel_calibration ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data ) {
    float temp_data = 0;
    float average_data = 0;
    uint8_t cnt;
    uint8_t averaging_number = 100;
    
    cfg_data->offset_data = 0;
    
    if ( cfg_data->measurement_mode == PIEZOACCEL_MEAS_MODE_AN_PIN ) {
        for ( cnt = 0 ; cnt < averaging_number ; cnt++ ) {
            analog_in_read_voltage( &ctx->adc, &temp_data );
            average_data += temp_data;
        }
        cfg_data->offset_data = average_data / averaging_number - DEV_PIEZOACCEL_ZERO_G_3V3;
    } else {
        if ( cfg_data->sensor_voltage == PIEZOACCEL_SENSOR_VOLTAGE_3V3 ) {
            for ( cnt = 0 ; cnt < averaging_number ; cnt++ ) {
                temp_data = piezoaccel_adc_voltage_read( ctx );
                average_data += temp_data;
            }
            cfg_data->offset_data = average_data / averaging_number - DEV_PIEZOACCEL_ZERO_G_3V3;
        } else {
            for ( cnt = 0 ; cnt < averaging_number ; cnt++ ) {
                temp_data = piezoaccel_adc_voltage_read( ctx );
                average_data += temp_data;
            }
            cfg_data->offset_data = average_data / averaging_number - DEV_PIEZOACCEL_ZERO_G_5V;
        }
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void adc_conv_delay ( void ) {
    Delay_10us( );
}

// ------------------------------------------------------------------------- END
