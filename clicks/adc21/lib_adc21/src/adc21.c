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
 * @file adc21.c
 * @brief ADC 21 Click Driver.
 */

#include "adc21.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc21_cfg_setup ( adc21_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc21_init ( adc21_t *ctx, adc21_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t adc21_read_raw_adc ( adc21_t *ctx, uint8_t channel, uint16_t *raw_adc )
{
    if ( ( channel > ADC21_CHANNEL_7 ) || ( NULL == raw_adc ) )
    {
        return ADC21_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    err_t error_flag = spi_master_set_default_write_data( &ctx->spi, channel << 3 );
    spi_master_select_device( ctx->chip_select );
    // Dummy read for power up
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    // Read raw data
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ADC21_OK == error_flag )
    {
        *raw_adc = ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) & ADC21_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t adc21_read_voltage ( adc21_t *ctx, uint8_t channel, float avcc, float *voltage )
{
    if ( ( channel > ADC21_CHANNEL_7 ) || ( NULL == voltage ) )
    {
        return ADC21_ERROR;
    }
    uint16_t raw_adc = 0;
    if ( ADC21_OK == adc21_read_raw_adc ( ctx, channel, &raw_adc ) )
    {
        *voltage = ( ( float ) raw_adc / ADC21_DATA_RESOLUTION ) * avcc;
        return ADC21_OK;
    }
    return ADC21_ERROR;
}

// ------------------------------------------------------------------------- END
