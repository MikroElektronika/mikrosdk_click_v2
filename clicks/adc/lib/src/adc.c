/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file adc.c
 *
 */

#include "adc.h"


// ------------------------------------------------------------- PRIVATE MACROS

#define ADC_DUMMY         0x0
#define ADC_START_BIT     0x4
#define ADC_SINGLE_ENDED  0x2
#define ADC_DATA_RESOL    4095

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc_cfg_setup( adc_cfg_t *cfg )
{
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->sck = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->vref = ADC_VREF_3300MV;
}

ADC_RETVAL adc_init( adc_t *ctx, adc_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC_DUMMY );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    ctx->ch0 = 0;
    ctx->ch1 = 0;
    ctx->ch2 = 0;
    ctx->ch3 = 0;
    ctx->ch01 = 0;
    ctx->ch10 = 0;
    ctx->ch23 = 0;
    ctx->ch32 = 0;
    ctx->vref = cfg->vref;

    return ADC_OK;
}

uint16_t adc_get_single_ended_ch( adc_t *ctx, uint8_t channel )
{
    uint8_t tx_data[ 1 ];
    uint8_t rx_data[ 2 ];
    uint16_t adc_read;
    float res;

    tx_data[ 0 ] = ADC_START_BIT | ADC_SINGLE_ENDED;

    spi_master_set_default_write_data( &ctx->spi, channel << 6 );
    
    spi_master_select_device( ctx->chip_select ); 
    spi_master_write_then_read( &ctx->spi, tx_data, 1, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, ADC_DUMMY );

    adc_read = rx_data[ 0 ] & 0xF;
    adc_read <<= 8;
    adc_read |= rx_data[ 1 ];
    
    res = adc_read;
    res /= ADC_DATA_RESOL;
    res *= ctx->vref;

    switch ( channel )
    {
        case ADC_CH0_OR_CH01 :
        {
            ctx->ch0 = ( uint16_t )res;
        break;
        }
        case ADC_CH1_OR_CH10 :
        {
            ctx->ch1 = ( uint16_t )res;
        break;
        }
        case ADC_CH2_OR_CH23 :
        {
            ctx->ch2 = ( uint16_t )res;
        break;
        }
        case ADC_CH3_OR_CH32 :
        {
            ctx->ch3 = ( uint16_t )res;
        break;
        }
        default :
        {
        break;
        }
    }

    return ( uint16_t )res;
}

uint16_t adc_get_differential_ch( adc_t *ctx, uint8_t channel )
{
    uint8_t tx_data[ 1 ];
    uint8_t rx_data[ 2 ];
    uint16_t adc_read;
    float res;

    tx_data[ 0 ] = ADC_START_BIT;

    spi_master_set_default_write_data( &ctx->spi, channel << 6 );
    
    spi_master_select_device( ctx->chip_select ); 
    spi_master_write_then_read( &ctx->spi, tx_data, 1, rx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    spi_master_set_default_write_data( &ctx->spi, ADC_DUMMY );

    adc_read = rx_data[ 0 ] & 0xF;
    adc_read <<= 8;
    adc_read |= rx_data[ 1 ];

    res = adc_read;
    res /= ADC_DATA_RESOL;
    res *= ctx->vref;

    switch ( channel )
    {
        case ADC_CH0_OR_CH01 :
        {
            ctx->ch01 = ( uint16_t )res;
        break;
        }
        case ADC_CH1_OR_CH10 :
        {
            ctx->ch10 = ( uint16_t )res;
        break;
        }
        case ADC_CH2_OR_CH23 :
        {
            ctx->ch23 = ( uint16_t )res;
        break;
        }
        case ADC_CH3_OR_CH32 :
        {
            ctx->ch32 = ( uint16_t )res;
        break;
        }
        default :
        {
        break;
        }
    }

    return ( uint16_t )res;
}

// ------------------------------------------------------------------------ END
