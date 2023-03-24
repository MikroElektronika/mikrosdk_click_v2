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

#include "adc2.h"

// ------------------------------------------------------------- PRIVATE VARIABLES

static float dev_vref = 0;

// ------------------------------------------------------------- PRIVATE MACROS 

#define ADC2_DUMMY          0

#define ADC2_RESOLUTION     2097151.0

#define ADC2_OL             0x80 
#define ADC2_OH             0x40

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void adc2_cfg_setup ( adc2_cfg_t *cfg )
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

ADC2_RETVAL adc2_init ( adc2_t *ctx, adc2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = ADC2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return ADC2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, ADC2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return ADC2_OK;

}

float adc2_read_adc_data ( adc2_t *ctx )
{
    uint8_t read_buf[ 4 ] = { 0 };
    int32_t raw_data = 0;
    int32_t sign_bit = 1;
    float adc_data = 0;
    float adc_res = ADC2_RESOLUTION;
    ctx->ovf_l = 0;
    ctx->ovf_h = 0;

    spi_master_select_device( ctx->chip_select );
    Delay_100ms( );
    spi_master_read( &ctx->spi, read_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    
    raw_data = read_buf[ 0 ];
    raw_data <<= 8;
    raw_data |= read_buf[ 1 ];
    raw_data <<= 8;
    raw_data |= read_buf[ 2 ];
    
    raw_data &= 0x003FFFFF;
    
    if ( ( read_buf[ 0 ] & ADC2_OL ) == ADC2_OL )
    {
        raw_data |= 0xFFB00000;
        ctx->ovf_l = 1;
    }
    else if ( ( read_buf[ 0 ] & ADC2_OH ) == ADC2_OH )
    {
        ctx->ovf_h = 1;
    }
    
    adc_data = ( float )raw_data;
    adc_data *= ctx->vref;  
    adc_data /= adc_res;

    return adc_data;
}

void adc2_set_vref ( adc2_t *ctx, float vref )
{
    ctx->vref = vref;
}


// ------------------------------------------------------------------------- END

