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

#include "buck12.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BUCK12_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void buck12_cfg_setup ( buck12_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->en = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BUCK12_RETVAL buck12_init ( buck12_t *ctx, buck12_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BUCK12_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BUCK12_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BUCK12_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );

    return BUCK12_OK;
}

void buck12_generic_transfer 
( 
    buck12_t *ctx, 
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

void buck12_control ( buck12_t *ctx, uint8_t ctrl )
{
    if ( ctrl == BUCK12_ENABLE ) 
    {
        digital_out_high( &ctx->en );
    }
    else
    {
        digital_out_low( &ctx->en );
    }
}

uint16_t buck12_get_channel_adc ( buck12_t *ctx, uint8_t channel )
{
    uint8_t read_data[ 3 ];
    uint16_t adc_data;
    uint8_t tmp; 

    spi_master_select_device( ctx->chip_select );

    tmp = 0x01;
    spi_master_write ( &ctx->spi, &tmp, 1 );
    spi_master_write ( &ctx->spi, &channel, 1 );

    spi_master_read( &ctx->spi, &read_data[ 0 ], 1 );
    
    spi_master_deselect_device( ctx->chip_select );

    adc_data = channel & 0x0F;
    adc_data <<= 8;
    adc_data |= read_data[ 0 ];

    return adc_data;
}

float buck12_get_voltage ( buck12_t *ctx, uint8_t select_volt )
{
    uint16_t adc_data;
    float voltage;

    if( select_volt == BUCK12_INPUT_VOLTAGE )
    {
        adc_data = buck12_get_channel_adc( ctx, BUCK12_CHANNEL_0 );
    }
    else
    {
        adc_data = buck12_get_channel_adc( ctx, BUCK12_CHANNEL_1 );
        
        if( adc_data < 2255 )
        {
            return 0;
        }
        else
        {
            adc_data = adc_data - 2255;
        }
    }

    voltage = ( adc_data * 4095.0 ) / 5500.0;
    voltage = voltage * 10;
        
    return voltage;
}

// ------------------------------------------------------------------------- END

