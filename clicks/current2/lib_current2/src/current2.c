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

#include "current2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define CURRENT2_DUMMY 0

#define RSENSE   0.05
#define ROUT     10000
#define VREF     2.048

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void current2_cfg_setup ( current2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

uint8_t current2_init ( current2_t *ctx, current2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = CURRENT2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return CURRENT2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, CURRENT2_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    return CURRENT2_OK;
}

void current2_generic_transfer 
( 
    current2_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

uint16_t current2_get_adc ( current2_t *ctx )
{
    uint8_t data_out[ 2 ];
    uint16_t adc_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_read( &ctx->spi, data_out, 2 );
    spi_master_deselect_device( ctx->chip_select );   

    adc_data = data_out[ 0 ];
    adc_data <<= 8;
    adc_data |= data_out[ 1 ];
    adc_data >>= 3;
    adc_data &= 0x03FF;

    return adc_data;
}

uint16_t current2_get_average_adc ( current2_t *ctx, uint8_t n_samp )
{
    uint16_t adc_data;
    uint32_t sum;
    uint16_t average;
    uint8_t cnt;

    sum = 0;
    for ( cnt = 0; cnt < n_samp; cnt++ )
    {
        adc_data = current2_get_adc( ctx );
        sum += adc_data;
        Delay_1ms( );
    }

    average = ( float ) sum / n_samp;

    return average;
}

uint16_t current2_get_current ( current2_t *ctx, uint8_t n_sample )
{
    uint16_t avrg_adc;
    float temp;

    avrg_adc = current2_get_average_adc( ctx, n_sample );

    temp = avrg_adc / 1023.0;
    temp *= VREF;
    temp *= 9.9;
    temp /= (0.01 * ROUT);
    temp /= RSENSE;
    avrg_adc = temp * 1000;

    return avrg_adc;
}

// ------------------------------------------------------------------------- END

