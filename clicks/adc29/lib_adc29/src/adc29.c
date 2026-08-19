/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file adc29.c
 * @brief ADC 29 Click Driver.
 */

#include "adc29.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void adc29_cfg_setup ( adc29_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t adc29_init ( adc29_t *ctx, adc29_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;
    ctx->vref = ADC29_VREF_3V0;

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

    /* CS low -> device is in acquisition state */
    spi_master_select_device( ctx->chip_select );
    
    /* 500ms wait time is necessary for auto-calibration after power on */
    Delay_1sec( );

    return SPI_MASTER_SUCCESS;
}

err_t adc29_read_raw_adc ( adc29_t *ctx, uint16_t *raw_adc )
{
    uint8_t rx_buf[ 2 ] = { 0 };

    if ( NULL == raw_adc )
    {
        return ADC29_ERROR;
    }
    
    /* Start conversion by setting CS high */
    spi_master_deselect_device( ctx->chip_select );
    
    /* It takes 1400ns for conversion to end */
    Delay_1ms( );
    
    /* By setting CS low the data is available to be read and device goes into acquisition mode */
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    
    /* Assemble read data to 12 bit unsigned, MSB first */
    if ( ADC29_OK == error_flag )
    {
        *raw_adc = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
        *raw_adc >>= 4;
    }

    return error_flag;
}

err_t adc29_read_voltage ( adc29_t *ctx, float *voltage )
{
    err_t error_flag = ADC29_OK;
    uint16_t raw_adc = 0;

    if ( NULL == voltage )
    {
        return ADC29_ERROR;
    }

    error_flag |= adc29_read_raw_adc( ctx, &raw_adc );
    
    /* Convert raw data to voltage:
     *     V = raw * LSB 
             = raw * Vref / res */
    *voltage = ( float ) raw_adc * ctx->vref / ADC29_ADC_RESOLUTION;

    return error_flag;
}

err_t adc29_recalibrate ( adc29_t *ctx )
{
    uint8_t dummy_buf[ ADC29_RECALIB_NUM_DATA ] = { 0 };
    
    /* CS low -> device enters acquisition phase */
    spi_master_select_device( ctx->chip_select );

    /* Recalibrate command is done by transmitting 1024 SCLK pulses while device is in the acquisition phase */
    err_t error_flag = spi_master_read( &ctx->spi, dummy_buf, ADC29_RECALIB_NUM_DATA );

    /* 500ms wait time is necessary for calibration to finish */
    Delay_1sec( );

    return error_flag;
}

// ------------------------------------------------------------------------- END
