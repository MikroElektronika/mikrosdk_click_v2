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
 * @file isoadc.c
 * @brief ISO ADC Click Driver.
 */

#include "isoadc.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void isoadc_cfg_setup ( isoadc_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;

    cfg->spi_speed   = 5000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t isoadc_init ( isoadc_t *ctx, isoadc_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    return SPI_MASTER_SUCCESS;
}

err_t isoadc_read_raw_adc ( isoadc_t *ctx, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( ISOADC_ERROR == spi_master_read( &ctx->spi, data_buf, 2 ) ) || ( NULL == data_out ) )
    {
        return ISOADC_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return ISOADC_OK;
}

void isoadc_set_vext ( isoadc_t *ctx, float vext )
{
    if ( ( vext >= ISOADC_VEXT_MIN ) && ( vext <= ISOADC_VEXT_MAX ) )
    {
        ctx->vext = vext;
    }
}

err_t isoadc_read_voltage ( isoadc_t *ctx, float *voltage )
{
    uint16_t raw_adc = 0;
    uint32_t adc_sum = 0;
    uint32_t cnt = 0;
    uint32_t timeout_cnt = 0;
    if ( NULL == voltage )
    {
        return ISOADC_ERROR;
    }
    while ( cnt < ISOADC_ADC_NUM_AVERAGES )
    {
        if ( ISOADC_OK == isoadc_read_raw_adc ( ctx, &raw_adc ) )
        {
            adc_sum += raw_adc;
            cnt++;
        }
        else
        {
            timeout_cnt++;
            if ( timeout_cnt >= ISOADC_TIMEOUT_COUNT )
            {
                return ISOADC_ERROR;
            }
        }
    }
    adc_sum /= ISOADC_ADC_NUM_AVERAGES;
    *voltage = ( float ) adc_sum / ISOADC_ADC_RESOLUTION * ISOADC_ADC_2FSR - ISOADC_ADC_FSR;
    return ISOADC_OK;
}

float isoadc_get_current ( float voltage )
{
    return voltage / ISOADC_VOLTAGE_TO_CURRENT;
}

float isoadc_get_power ( isoadc_t *ctx, float voltage )
{
    return ( ctx->vext - voltage / ISOADC_MILLI_TO_ONE ) * ( voltage / ISOADC_VOLTAGE_TO_CURRENT / ISOADC_MILLI_TO_ONE );
}

// ------------------------------------------------------------------------- END
