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

#include "mp3.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MP3_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mp3_cfg_setup ( mp3_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dreq = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->dcs = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg )
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, MP3_DUMMY ) ) 
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

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dcs, cfg->dcs );

    // Input pins
    digital_in_init( &ctx->dreq, cfg->dreq );
    
    digital_out_high( &ctx->dcs );
    digital_out_high ( &ctx->rst );

    return MP3_OK;
}

void mp3_reset( mp3_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );

    while ( !digital_in_read( &ctx->dreq ) );
}

uint8_t mp3_is_busy( mp3_t *ctx )
{
    return digital_in_read( &ctx->dreq );
}

void mp3_cmd_write( mp3_t *ctx, uint8_t address, uint16_t input )
{
    uint8_t tmp[ 4 ] = { 0 };

    tmp[ 0 ] = MP3_WRITE_CMD;
    tmp[ 1 ] = address;
    tmp[ 2 ] = ( uint8_t ) ( ( input >> 8 ) & 0xFF );
    tmp[ 3 ] = ( uint8_t ) ( input & 0xFF );

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tmp, 4 ); 
    spi_master_deselect_device( ctx->chip_select );

    // Poll DREQ pin and block until module is ready to receive another command
    while ( !digital_in_read( &ctx->dreq ) );
}

uint16_t mp3_cmd_read( mp3_t *ctx, uint8_t address )
{
    uint8_t tmp[ 4 ] = { 0 };
    uint16_t result = 0;

    tmp[ 0 ] = MP3_READ_CMD;
    tmp[ 1 ] = address;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tmp[ 0 ], 2, &tmp[ 2 ], 2 ); 
    spi_master_deselect_device( ctx->chip_select );

    result = tmp[ 2 ];
    result <<= 8;
    result |= tmp[ 3 ];

    // Poll DREQ pin and block until module is ready to receive another command
    while ( !digital_in_read( &ctx->dreq ) );

    return result;
}

err_t mp3_data_write( mp3_t *ctx, uint8_t input )
{
    if ( !digital_in_read( &ctx->dreq ) )
    {
        return MP3_ERROR;
    }
    digital_out_low( &ctx->dcs );
    spi_master_write( &ctx->spi, &input, 1 );
    digital_out_high( &ctx->dcs );
    return MP3_OK;
}

err_t mp3_data_write_32( mp3_t *ctx, uint8_t *input32 )
{
    if ( !digital_in_read( &ctx->dreq ) )
    {
        return MP3_ERROR;
    }
    digital_out_low( &ctx->dcs );
    spi_master_write( &ctx->spi, input32, 32 );
    digital_out_high( &ctx->dcs );
    return MP3_OK;
}

void mp3_set_volume ( mp3_t *ctx, uint8_t vol_left, uint8_t vol_right )
{
    mp3_cmd_write( ctx, MP3_VOL_ADDR, ( ( uint16_t ) vol_left << 8 ) | vol_right );    
}

// ------------------------------------------------------------------------- END

