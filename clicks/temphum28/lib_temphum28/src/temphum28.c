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
 * @file temphum28.c
 * @brief TempHum 28 Click Driver.
 */

#include "temphum28.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void temphum28_cfg_setup ( temphum28_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hte  = HAL_PIN_NC;
    cfg->rte  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->vref        = TEMPHUM28_VREF_3V3;
}

err_t temphum28_init ( temphum28_t *ctx, temphum28_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hte, cfg->hte );
    digital_out_init( &ctx->rte, cfg->rte );

    ctx->vref = cfg->vref;

    return SPI_MASTER_SUCCESS;
}

err_t temphum28_read_raw_adc ( temphum28_t *ctx, uint8_t channel, uint16_t *raw_adc ) 
{
    if ( ( ( TEMPHUM28_INPUT_CHANNEL_TEMP != channel ) && 
           ( TEMPHUM28_INPUT_CHANNEL_RH != channel ) ) || ( NULL == raw_adc ) )
    {
        return TEMPHUM28_ERROR;
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
    *raw_adc = ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] ) & TEMPHUM28_ADC_RESOLUTION;
    return error_flag;
}

err_t temphum28_read_voltage ( temphum28_t *ctx, uint8_t channel, float *voltage ) 
{
    uint16_t raw_adc = 0;
    err_t err_flag = temphum28_read_raw_adc( ctx, channel, &raw_adc );
    *voltage = ( float ) raw_adc * ( ctx->vref / ( float ) TEMPHUM28_ADC_RESOLUTION );
    return err_flag;
}

err_t temphum28_read_voltage_avg ( temphum28_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( TEMPHUM28_OK == temphum28_read_voltage ( ctx, channel, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > TEMPHUM28_TIMEOUT_MS )
        {
            return TEMPHUM28_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return TEMPHUM28_OK;
}

void temphum28_set_vref ( temphum28_t *ctx, float vref ) 
{
    ctx->vref = vref;
}

void temphum28_heater_enable ( temphum28_t *ctx )
{
    digital_out_high ( &ctx->hte );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
}

void temphum28_heater_disable ( temphum28_t *ctx )
{
    digital_out_low ( &ctx->hte );
    Delay_1ms ( );
}

void temphum28_device_enable ( temphum28_t *ctx )
{
    digital_out_high ( &ctx->rte );
    Delay_10ms ( );
    Delay_10ms ( );
}

void temphum28_device_disable ( temphum28_t *ctx )
{
    digital_out_low ( &ctx->rte );
    Delay_1ms ( );
}

err_t temphum28_read_humidity ( temphum28_t *ctx, float *hum )
{
    float voltage = 0;
    err_t error_flag = temphum28_read_voltage_avg ( ctx, TEMPHUM28_INPUT_CHANNEL_RH, 
                                                    TEMPHUM28_NUM_CONVERSIONS, &voltage );
    *hum = TEMPHUM28_RH_OFFSET + TEMPHUM28_RH_RESOLUTION * voltage / ctx->vref;
    return error_flag;
}

err_t temphum28_read_temperature ( temphum28_t *ctx, float *temp )
{
    float voltage = 0;
    err_t error_flag = temphum28_read_voltage_avg ( ctx, TEMPHUM28_INPUT_CHANNEL_TEMP, 
                                                    TEMPHUM28_NUM_CONVERSIONS, &voltage );
    *temp = TEMPHUM28_TEMP_OFFSET + TEMPHUM28_TEMP_RESOLUTION * voltage / ctx->vref;
    return error_flag;
}

// ------------------------------------------------------------------------- END
