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
 * @file isoadc2.c
 * @brief ISO ADC 2 Click Driver.
 */

#include "isoadc2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Conversion delay.
 * @details Conversion delay of 10 us.
 */
static void dev_conversion_delay ( void );

// --------------------------------------------------------- PUBLIC FUNCTIONS 

void isoadc2_cfg_setup ( isoadc2_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->crt = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t isoadc2_init ( isoadc2_t *ctx, isoadc2_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) {
        return SPI_MASTER_ERROR;
    }

    if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->crt, cfg->crt );

    return SPI_MASTER_SUCCESS;
}

err_t isoadc2_generic_write ( isoadc2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t isoadc2_generic_read ( isoadc2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t isoadc2_read_adc ( isoadc2_t *ctx, uint16_t *adc_val ) {
    uint8_t adc_data[ 2 ];
    uint16_t temp_adc;

    digital_out_low( &ctx->crt );
    dev_conversion_delay(  );
    digital_out_high( &ctx->crt );
    dev_conversion_delay(  );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, adc_data, 2 );
    spi_master_deselect_device( ctx->chip_select );

    temp_adc = adc_data[ 0 ];
    temp_adc <<= 8;
    temp_adc |= adc_data[ 1 ];
    temp_adc >>= 4;

    temp_adc &= ADC_MASK;
    *adc_val = temp_adc;
    
    return error_flag;
}

err_t isoadc2_get_mv ( isoadc2_t *ctx, uint16_t *voltage ) {
    float temp_data = 0;
    float val = ADC_RES * VREF;
    uint16_t adc_data = 0;
    
    err_t error_flag = isoadc2_read_adc( ctx, &adc_data );

    temp_data = adc_data;
    temp_data /= ADC_RES;
    temp_data *= VREF;
    
    *voltage = temp_data;
    
    return error_flag;
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static void dev_conversion_delay ( void ) {
    Delay_10us(  );
}

// ------------------------------------------------------------------------- END
