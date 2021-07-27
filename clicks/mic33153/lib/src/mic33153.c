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

#include "mic33153.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MIC33153_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mic33153_cfg_setup ( mic33153_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->an = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->pg = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MIC33153_RETVAL mic33153_init ( mic33153_t *ctx, mic33153_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MIC33153_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_MASTER_SUCCESS )
    {
        return MIC33153_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MIC33153_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->pg, cfg->pg );

    return MIC33153_OK;
}

void mic33153_generic_transfer 
( 
    mic33153_t *ctx, 
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

void mic33153_write_dac ( mic33153_t *ctx, const uint16_t value_dac )
{
    uint8_t data_buffer[ 2 ] = { 0 };
    
    data_buffer[ 0 ] |= 0x30;
    data_buffer[ 0 ] |= ( ( value_dac >> 8 ) & 0x0F );
    data_buffer[ 1 ] |= value_dac;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &data_buffer[ 0 ], 1 );
    spi_master_write( &ctx->spi, &data_buffer[ 1 ], 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void mic33153_enable_out ( mic33153_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

uint8_t mic33153_check_power_good ( mic33153_t *ctx )
{
    return digital_in_read( &ctx->pg );
}

// ------------------------------------------------------------------------- END

