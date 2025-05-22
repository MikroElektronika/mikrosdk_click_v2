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
 * @file currentsens.c
 * @brief Current Sens Click Driver.
 */

#include "currentsens.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void currentsens_cfg_setup ( currentsens_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;

    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->vref        = CURRENTSENS_VREF_3V3;
    cfg->drv_sel     = CURRENTSENS_DRV_SEL_SPI;
}

void currentsens_drv_interface_sel ( currentsens_cfg_t *cfg, currentsens_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t currentsens_init ( currentsens_t *ctx, currentsens_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;
    ctx->vref = cfg->vref;
    
    if ( CURRENTSENS_DRV_SEL_SPI == ctx->drv_sel ) 
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
    }
    else
    {
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
    }

    return SPI_MASTER_SUCCESS;
}

err_t currentsens_read_raw_adc ( currentsens_t *ctx, uint16_t *raw_adc ) 
{
    if ( CURRENTSENS_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        uint8_t rx_buf[ 2 ] = { 0 };
        spi_master_select_device( ctx->chip_select );
        err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
        spi_master_deselect_device( ctx->chip_select );
        *raw_adc = ( ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | ( rx_buf[ 1 ] & 0xFF ) ) >> 1 ) & CURRENTSENS_ADC_RESOLUTION;
        return error_flag;
    }
    else
    {
        return analog_in_read( &ctx->adc, raw_adc );
    }
}

err_t currentsens_read_voltage ( currentsens_t *ctx, float *voltage ) 
{
    if ( CURRENTSENS_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        uint16_t raw_adc = 0;
        err_t err_flag = currentsens_read_raw_adc( ctx, &raw_adc );
        *voltage = ( float ) raw_adc * ( CURRENTSENS_VREF_2V5 / ( float ) CURRENTSENS_ADC_RESOLUTION );
        return err_flag;
    }
    else
    {
        return analog_in_read_voltage( &ctx->adc, voltage );
    }
}

err_t currentsens_read_voltage_avg ( currentsens_t *ctx, uint16_t num_conv, float *voltage_avg )
{
    float voltage = 0;
    float voltage_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < num_conv )
    {
        if ( CURRENTSENS_OK == currentsens_read_voltage ( ctx, &voltage ) )
        {
            voltage_sum += voltage;
            cnt++;
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > CURRENTSENS_TIMEOUT_MS )
        {
            return CURRENTSENS_ERROR;
        }
    }
    *voltage_avg = ( voltage_sum / num_conv );
    return CURRENTSENS_OK;
}

err_t currentsens_set_vref ( currentsens_t *ctx, float vref ) 
{
    ctx->vref = vref;
    if ( CURRENTSENS_DRV_SEL_SPI == ctx->drv_sel ) 
    {
        return CURRENTSENS_OK;
    }
    else
    {
        return analog_in_set_vref_value( &ctx->adc, vref );
    }
}

err_t currentsens_calib_offset ( currentsens_t *ctx )
{
    float voltage = 0;
    err_t error_flag = currentsens_read_voltage_avg ( ctx, CURRENTSENS_NUM_CONVERSIONS, &voltage );
    ctx->zero_curr_offset = voltage;
    return error_flag;
}

err_t currentsens_calib_resolution ( currentsens_t *ctx, float calib_current )
{
    float voltage = 0;
    err_t error_flag = currentsens_read_voltage_avg ( ctx, CURRENTSENS_NUM_CONVERSIONS, &voltage );
    ctx->data_resolution = calib_current / ( voltage - ctx->zero_curr_offset );
    return error_flag;
}

err_t currentsens_read_current ( currentsens_t *ctx, float *current )
{
    float voltage = 0;
    err_t error_flag = currentsens_read_voltage_avg ( ctx, CURRENTSENS_NUM_CONVERSIONS, &voltage );
    *current = ( voltage - ctx->zero_curr_offset ) * ctx->data_resolution;
    return error_flag;
}

// ------------------------------------------------------------------------- END
