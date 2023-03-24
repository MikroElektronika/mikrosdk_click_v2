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
 * @file vumeter.c
 * @brief VU Meter Click Driver.
 */

#include "vumeter.h"
#include "math.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void vumeter_cfg_setup ( vumeter_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->an   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    
    cfg->resolution  = ANALOG_IN_RESOLUTION_DEFAULT; /*< Should leave this by default for portability purposes. 
                                                         Different MCU's have different resolutions. 
                                                         Change only if necessary.*/
    cfg->vref        = VUMETER_VCC_3V3;
}

err_t vumeter_init ( vumeter_t *ctx, vumeter_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t vumeter_read_an_pin_value ( vumeter_t *ctx, uint16_t *data_out ) 
{
    return analog_in_read( &ctx->adc, data_out );
}

err_t vumeter_read_an_pin_voltage ( vumeter_t *ctx, float *data_out ) 
{
    return analog_in_read_voltage( &ctx->adc, data_out );
}

err_t vumeter_set_gain_level ( vumeter_t *ctx, uint8_t gain_lvl ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &gain_lvl, 1 );
    spi_master_deselect_device( ctx->chip_select );   
    return error_flag;
}

float vumeter_calculate_vu_level ( vumeter_t *ctx, uint16_t sample_rate_ms ) 
{
    float rms_voltage = 0;
    float an_voltage = 0;
    uint32_t timeout = ( uint32_t ) sample_rate_ms * 2;
    uint32_t cnt = 0;
    
    while ( timeout-- )
    {
        if ( ADC_ERROR != vumeter_read_an_pin_voltage ( ctx, &an_voltage ) ) 
        {
            if ( ( an_voltage > ( ( ctx->adc.config.vref_value / 2.0 ) + VUMETER_RMS_FOR_20VU ) ) || 
                 ( an_voltage < ( ( ctx->adc.config.vref_value / 2.0 ) - VUMETER_RMS_FOR_20VU ) ) )
            {
                rms_voltage += pow ( an_voltage - ( ctx->adc.config.vref_value / 2.0 ), 2.0 );
                cnt++;
            }
        }
        Delay_500us( );
    }
    if ( cnt > 0 )
    {
        rms_voltage = sqrt ( rms_voltage / cnt );
        return ( ( 20.0 * log10 ( rms_voltage / VUMETER_DBU_VREF ) ) - VUMETER_DBU_TO_VU );
    }
    return VUMETER_MIN_VU;
}

// ------------------------------------------------------------------------- END
