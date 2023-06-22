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
 * \file
 *
 */

#include "voltmeter.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define VOLTMETER_DUMMY 0

void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, VOLTMETER_DUMMY ) ) 
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

    // Input pins
    digital_in_init( &ctx->an, cfg->an );
    
    return VOLTMETER_OK;
}

int16_t voltmeter_read_raw_data ( voltmeter_t *ctx )
{
    uint8_t buffer[ 2 ] = { 0 };
    int32_t adc_sum = 0;
    int16_t raw_adc = 0;
    uint16_t cnt = 0;
    
    for ( cnt = 0; cnt < VOLTMETER_NUM_ADC_CONVERSIONS; cnt++ )
    {
        spi_master_select_device( ctx->chip_select );
        spi_master_read ( &ctx->spi, buffer, 2 );
        spi_master_deselect_device( ctx->chip_select );
        
        raw_adc = buffer[ 0 ];
        raw_adc <<= 8;
        raw_adc |= buffer[ 1 ];
        raw_adc += VOLTMETER_DATA_OFFSET;
        raw_adc &= VOLTMETER_DATA_RESOLUTION;
        raw_adc <<= 4;
        raw_adc >>= 4;
        adc_sum += raw_adc;
        Delay_1ms ( );
    }
    raw_adc = ( int16_t ) ( adc_sum / cnt );

    return raw_adc;
}

float voltmeter_calculate_voltage ( voltmeter_t *ctx, int16_t raw_adc, uint8_t iso_gnd )
{
    float voltage = 0;
    
    voltage = ( float ) raw_adc / ( VOLTMETER_DATA_RESOLUTION / 2 );
    
    if ( iso_gnd )
    {
        voltage *= VOLTMETER_VREF_ISOLATED_GND;
    }
    else
    {
        voltage *= VOLTMETER_VREF_SHARED_GND;
    }

    return voltage;
}
// ------------------------------------------------------------------------- END

