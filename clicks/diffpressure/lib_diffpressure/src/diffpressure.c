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

#include "diffpressure.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define DIFFPRESSURE_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void diffpressure_cfg_setup ( diffpressure_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

err_t diffpressure_init ( diffpressure_t *ctx, diffpressure_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DIFFPRESSURE_DUMMY ) ) 
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

    return DIFFPRESSURE_OK;
}

float diffpressure_read_adc_voltage ( diffpressure_t *ctx )
{
    uint8_t buffer[ 3 ] = { 0 };
    int32_t raw_adc = 0;
    float voltage = 0;

    spi_master_select_device( ctx->chip_select );
    Delay_100ms( );
    spi_master_read( &ctx->spi, buffer, 3 );
    spi_master_deselect_device( ctx->chip_select );  
        
    raw_adc = buffer[ 0 ];
    raw_adc <<= 8;
    raw_adc |= buffer[ 1 ];
    raw_adc <<= 8;
    raw_adc |= buffer[ 2 ];
        
    // Check overflow and sign
    if ( ( buffer[ 0 ] & 0x20 ) || ( buffer[ 0 ] & 0x80 ) )
    {
        raw_adc |= 0xFFC00000ul;
        voltage = 5.0f * ( float ) raw_adc / 0x00200000ul;
    }
    else
    {
        raw_adc &= 0x003FFFFFul;
        voltage = 5.0f * ( float ) raw_adc / 0x001FFFFFul;
    }

    return voltage;
}

int32_t diffpressure_get_pa_difference ( diffpressure_t *ctx, float adc_voltage )
{
    float press_kpa = 0;
    int32_t result = 0;

    press_kpa = ( adc_voltage / 5.0f - 0.04f ) / 0.09f;
    result = ( int32_t ) ( press_kpa * 1000.0f );

    return result;
}

// ------------------------------------------------------------------------- END
