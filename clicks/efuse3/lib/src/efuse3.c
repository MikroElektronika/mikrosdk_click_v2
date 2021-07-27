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
 * @file efuse3.c
 * @brief e Fuse 3 Click Driver.
 */

#include "efuse3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                               0x00

/**
 * @brief Voltage reference.
 * @details Definition of voltage [ V ] reference.
 */
#define EFUSE3_ADC_VREF_VAL                 4.096

/**
 * @brief Resistor Rmon value.
 * @details Definition of resistor R3 value of 1000 Ohm.
 */
#define EFUSE3_R_MON_R3                     1000

/**
 * @brief ADC SPI resolution.
 * @details Definition of 21 bit resolution.
 */
#define EFUSE3_ADC_SPI_RESOLUTION_21_BIT    0x0FFFFF

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Reset delay.
 * @details Definition of reset delay.
 */
static void dev_reset_delay ( void );

/**
 * @brief Communication delay.
 * @details Definition of communication delay.
 */
static void dev_communication_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS


void efuse3_cfg_setup ( efuse3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->vsel = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->flag = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t efuse3_init ( efuse3_t *ctx, efuse3_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->vsel, cfg->vsel );
    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->flag, cfg->flag );

    return SPI_MASTER_SUCCESS;
}

void efuse3_default_cfg ( efuse3_t *ctx ) {
    digital_out_high( &ctx->vsel );
    dev_reset_delay( );
    
    efuse3_reset( ctx );
    dev_reset_delay( );
    
    efuse3_enable_device( ctx );
    dev_reset_delay( );
}

err_t efuse3_generic_read ( efuse3_t *ctx, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    dev_reset_delay( );
    spi_master_deselect_device( ctx->chip_select );
    dev_communication_delay( );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t efuse3_get_monitor_output ( efuse3_t *ctx, float *voltage, uint8_t *overflow ) {
    uint8_t rx_buf[ 3 ];
    int32_t adc_tmp;
    float vtg_tmp;
    
    *overflow = EFUSE3_NO_OVERFLOW;
    
    err_t error_flag = efuse3_generic_read ( ctx, rx_buf, 3 );
    
    adc_tmp = rx_buf[ 0 ];
    adc_tmp <<= 8;
    adc_tmp |= rx_buf[ 1 ];
    adc_tmp <<= 8;
    adc_tmp |= rx_buf[ 2 ]; 
    
    if ( ( adc_tmp >> 22 ) == 2 ) {
        adc_tmp |= 0xFFC00000;
        *overflow |= EFUSE3_OVERFLOW_LOW;
    }
    else if ( ( adc_tmp >> 22 ) == 0 ) {
        if ( adc_tmp & 0x200000 ) {
            adc_tmp |= 0xFFC00000;
        }
        
        *overflow = EFUSE3_NO_OVERFLOW;
    }
    else if ( ( adc_tmp >> 22 ) == 1 ) {
        adc_tmp &= 0x003FFFFF;
        *overflow |= EFUSE3_OVERFLOW_HIGH;
    }
    
    vtg_tmp = ( float ) adc_tmp;    
    vtg_tmp /= EFUSE3_ADC_SPI_RESOLUTION_21_BIT;
    vtg_tmp *= EFUSE3_ADC_VREF_VAL;
    
    *voltage = vtg_tmp;

    return error_flag;
}

err_t efuse3_get_current ( efuse3_t *ctx, float *current ) {
    float voltage;
    uint8_t overflow;
    float current_tmp;
    
    err_t error_flag = efuse3_get_monitor_output ( ctx, &voltage, &overflow );
    
    current_tmp = voltage;
    current_tmp *= 1000;
    current_tmp /= 3.2;
    current_tmp /= EFUSE3_R_MON_R3;
    
    *current = current_tmp;
    
    return error_flag;
}

void efuse3_enable_device ( efuse3_t *ctx ) {
    digital_out_low( &ctx->en );
}

void efuse3_reset ( efuse3_t *ctx ) {
    digital_out_high( &ctx->en );
    dev_reset_delay( );
    digital_out_low( &ctx->en );
    dev_reset_delay( );
}

void efuse3_disable_device ( efuse3_t *ctx ) {
    digital_out_high( &ctx->en );
}

void efuse3_set_overvoltage_clamp ( efuse3_t *ctx, uint8_t vc_sel ) {
    digital_out_write( &ctx->vsel, vc_sel );    
}

uint8_t efuse3_get_flag ( efuse3_t *ctx ) {
    return digital_in_read( &ctx->flag );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_50us( );
}

static void dev_communication_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
