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
 * @file current5.c
 * @brief Current 5 Click Driver.
 */

#include "current5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void current5_cfg_setup ( current5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t current5_init ( current5_t *ctx, current5_cfg_t *cfg ) 
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
    
    digital_in_init( &ctx->alert, cfg->alert );
    
    return SPI_MASTER_SUCCESS;
}

err_t current5_generic_read ( current5_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

uint8_t current5_get_alert ( current5_t *ctx )
{
    return digital_in_read( &ctx->alert );
}

void current5_set_rst ( current5_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

err_t current5_get_adc ( current5_t *ctx, uint16_t *adc_data )
{
    uint8_t temp_buf[ 2 ] = { 0 };
    err_t ret_val = current5_generic_read( ctx, temp_buf, 2 );
    *adc_data = ( ( uint16_t )temp_buf[ 0 ] << 8 ) | temp_buf[ 1 ];
    return ret_val;
}

err_t current5_get_voltage ( current5_t *ctx, float *vout )
{
    uint16_t adc_data = 0;
    err_t ret_val = current5_get_adc( ctx, &adc_data );
    *vout = adc_data * CURRENT5_VREF_mV / CURRENT5_RESOLUTION;
    return ret_val;
}

err_t current5_get_current ( current5_t *ctx, float *current )
{
    float voltage = 0;
    float gain = CURRENT5_VOLTAGE_GAIN - ( CURRENT5_VOLTAGE_GAIN * CURRENT5_GAIN_ERROR_PERCENTS / 100.0 );
    err_t ret_val = current5_get_voltage( ctx, &voltage );
    *current = voltage / gain / CURRENT5_RSHUNT_mOHM;
    return ret_val;
}

// ------------------------------------------------------------------------- END
