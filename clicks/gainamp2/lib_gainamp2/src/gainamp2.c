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

#include "gainamp2.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define GAINAMP2_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gainamp2_cfg_setup ( gainamp2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->vout = HAL_PIN_NC;
    
    cfg->resolution = ANALOG_IN_RESOLUTION_10_BIT;
    cfg->vref       = 3.3;
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

GAINAMP2_RETVAL gainamp2_init ( gainamp2_t *ctx, gainamp2_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;
    analog_in_config_t adc_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = GAINAMP2_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return GAINAMP2_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, GAINAMP2_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 
    
    analog_in_configure_default( &adc_cfg );

    adc_cfg.input_pin = cfg->vout;

    if ( analog_in_open( &ctx->adc, &adc_cfg ) == ADC_ERROR )
    {
        return ADC_ERROR;
    }

    analog_in_set_vref_value( &ctx->adc, cfg->vref );
    analog_in_set_resolution( &ctx->adc, cfg->resolution );

    return GAINAMP2_OK;
}

void gainamp2_generic_transfer ( gainamp2_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf,  uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );  
}

void gainamp2_write_command ( gainamp2_t *ctx, uint8_t instruction, uint8_t input )
{
    uint8_t tmp[ 2 ];

    tmp[ 0 ] = instruction;
    tmp[ 1 ] = input;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 2 );
    spi_master_deselect_device( ctx->chip_select );  

    Delay_1us( );
}

void gainamp2_set_channel_gain ( gainamp2_t *ctx, uint8_t channel, uint8_t gain )
{
    gainamp2_write_command( ctx, GAINAMP2_WRITE_INS | GAINAMP2_CH, channel );
    gainamp2_write_command( ctx, GAINAMP2_WRITE_INS | GAINAMP2_GAIN, gain );
}

float gainamp2_get_voltage ( gainamp2_t *ctx )
{
    float rx_data = 0;

    analog_in_read_voltage( &ctx->adc, &rx_data );

    return rx_data;
}

// ------------------------------------------------------------------------- END

