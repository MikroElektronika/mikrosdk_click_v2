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
 * @file hallcurrent23.c
 * @brief Hall Current 23 Click Driver.
 */

#include "hallcurrent23.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void hallcurrent23_cfg_setup ( hallcurrent23_cfg_t *cfg ) 
{
    cfg->an   = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->ocf  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->vref        = HALLCURRENT23_VREF_3V3;
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
}

err_t hallcurrent23_init ( hallcurrent23_t *ctx, hallcurrent23_cfg_t *cfg ) 
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

    analog_in_config_t adc_cfg;

    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->an;

    if ( ADC_ERROR == analog_in_open( &ctx->adc, &adc_cfg ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_vref_value( &ctx->adc, cfg->vref ) ) 
    {
        return ADC_ERROR;
    }

    if ( ADC_ERROR == analog_in_set_resolution( &ctx->adc, cfg->resolution ) ) 
    {
        return ADC_ERROR;
    }

    digital_in_init( &ctx->ocf, cfg->ocf );

    ctx->vref = cfg->vref;

    return SPI_MASTER_SUCCESS;
}

err_t hallcurrent23_read_raw_adc ( hallcurrent23_t *ctx, uint8_t channel, uint16_t *raw_adc ) 
{
    if ( ( ( HALLCURRENT23_INPUT_CHANNEL_VREF != channel ) && 
           ( HALLCURRENT23_INPUT_CHANNEL_VOUT != channel ) ) || ( NULL == raw_adc ) )
    {
        return HALLCURRENT23_ERROR;
    }
    uint8_t rx_buf[ 2 ] = { 0 };

    // Set input channel
    spi_master_set_default_write_data( &ctx->spi, ( channel << 3 ) );

    // Dummy read
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    // Read channel data
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) & HALLCURRENT23_ADC_RESOLUTION;
    return error_flag;
}

err_t hallcurrent23_read_voltage ( hallcurrent23_t *ctx, uint8_t channel, float *voltage ) 
{
    uint16_t raw_adc = 0;
    err_t err_flag = hallcurrent23_read_raw_adc( ctx, channel, &raw_adc );
    *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) HALLCURRENT23_ADC_RESOLUTION );
    return err_flag;
}

err_t hallcurrent23_read_voltage_avg ( hallcurrent23_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( HALLCURRENT23_OK == hallcurrent23_read_voltage ( ctx, channel, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > HALLCURRENT23_TIMEOUT_MS )
        {
            return HALLCURRENT23_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return HALLCURRENT23_OK;
}

err_t hallcurrent23_read_an_pin_value ( hallcurrent23_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t hallcurrent23_read_an_pin_volt ( hallcurrent23_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

uint8_t hallcurrent23_get_ocf_pin ( hallcurrent23_t *ctx )
{
    return digital_in_read( &ctx->ocf );
}

void hallcurrent23_set_vref ( hallcurrent23_t *ctx, float vref ) 
{
    ctx->vref = vref;
}

err_t hallcurrent23_calib_resolution ( hallcurrent23_t *ctx, float calib_current )
{
    float voltage = 0;
    err_t error_flag = hallcurrent23_read_voltage_avg ( ctx, HALLCURRENT23_INPUT_CHANNEL_VREF, 
                                                        HALLCURRENT23_NUM_CONVERSIONS, &ctx->sensor_vref );
    error_flag |= hallcurrent23_read_voltage_avg ( ctx, HALLCURRENT23_INPUT_CHANNEL_VOUT, 
                                                   HALLCURRENT23_NUM_CONVERSIONS, &voltage );
    ctx->data_resolution = calib_current / ( voltage - ctx->sensor_vref );
    return error_flag;
}

err_t hallcurrent23_read_current ( hallcurrent23_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = hallcurrent23_read_voltage_avg ( ctx, HALLCURRENT23_INPUT_CHANNEL_VOUT, 
                                                        HALLCURRENT23_NUM_CONVERSIONS, &voltage );
    *current = ( voltage - ctx->sensor_vref ) * ctx->data_resolution;
    return error_flag;
}

// ------------------------------------------------------------------------- END
