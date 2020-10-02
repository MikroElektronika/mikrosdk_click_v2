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

    cfg->spi_speed = SPI_FAST; 
    cfg->spi_mode = SPI_MODE_0;
}

MP3_RETVAL mp3_init ( mp3_t *ctx, mp3_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.mode        = cfg->spi_mode;
    spi_cfg.speed       = cfg->spi_speed;
    spi_cfg.pins.sck    = cfg->sck;
    spi_cfg.pins.miso   = cfg->miso;
    spi_cfg.pins.mosi   = cfg->mosi;
    spi_cfg.chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) != SPI_SUCCESS )
    {
        return MP3_INIT_ERROR;
    }

    spi_master_set_dummy_data( &ctx->spi, MP3_DUMMY );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dcs, cfg->dcs );

    // Input pins

    digital_in_init( &ctx->dreq, cfg->dreq );
    
    // Example: Sets pin [high, low] 

    // digital_out_high( &ctx->rst );
    // digital_out_low( &ctx->rst );
	
	// Example: Get pin state 

	// digital_in_read( &ctx->dcs );

    digital_out_high( &ctx->dcs );
    spi_master_start( &ctx->spi );
    digital_out_high ( &ctx->rst );

    return MP3_OK;

}

void mp3_generic_transfer ( mp3_t *ctx, spi_master_transfer_data_t *block )
{
    spi_master_start(&ctx->spi);
    spi_master_transfer(&ctx->spi, block);
    spi_master_stop(&ctx->spi);    
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
    if ( digital_in_read( &ctx->dreq ) )
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void mp3_cmd_write( mp3_t *ctx, uint8_t address, uint16_t input )
{
    uint8_t tmp[ 4 ];
    uint8_t cnt;

    tmp[ 0 ] = MP3_WRITE_CMD;
    tmp[ 1 ] = address;
    tmp[ 2 ] = input >> 8;
    tmp[ 3 ] = input & 0x00FF;

    spi_master_start( &ctx->spi );
    for( cnt = 0; cnt < 4; cnt++ )
    {
        spi_master_write( &ctx->spi , tmp[ cnt ] ); 
    }
    spi_master_stop( &ctx->spi );

// Poll DREQ pin and block until module is ready to receive another command
    while ( !digital_in_read( &ctx->dreq ) );
}

uint16_t mp3_cmd_read( mp3_t *ctx, uint8_t address )
{
    spi_master_transfer_data_t block;
    uint8_t tmp_in[ 4 ];
    uint8_t tmp_out[ 4 ];
    uint16_t res;

    tmp_in[ 0 ] = MP3_READ_CMD;
    tmp_in[ 1 ] = address;
    tmp_in[ 2 ] = 0;
    tmp_in[ 3 ] = 0;

    block.tx_buffer = tmp_in;
    block.rx_buffer = tmp_out;
    block.tx_length = 4;
    block.rx_length = 4;

    spi_master_start( &ctx->spi );
    spi_master_transfer( &ctx->spi, &block );
    spi_master_stop( &ctx->spi );

    res = tmp_out[3];
    res <<= 8;
    res |= tmp_out[4];

// Poll DREQ pin and block until module is ready to receive another command
    while ( !digital_in_read( &ctx->dreq ) );

    return res;
}

uint8_t mp3_data_write( mp3_t *ctx, uint8_t input )
{
    uint8_t tmp;

    if ( !digital_in_read( &ctx->dreq ) )
    {
        return 1;
    }

    tmp = input;

    digital_out_low( &ctx->dcs );
    spi_master_write( &ctx->spi, tmp );
    digital_out_high( &ctx->dcs );

    return 0;
}

uint8_t mp3_data_write_32( mp3_t *ctx, uint8_t *input32 )
{
    uint8_t cnt;
    if ( !digital_in_read( &ctx->dreq ) )
    {
        return 1;
    }

    digital_out_low( &ctx->dcs );
    for( cnt = 0; cnt<32; cnt++ )
    {
        spi_master_write( &ctx->spi, input32[ cnt ] );
    }
    
    digital_out_high( &ctx->dcs );

    return 0;
}



// ------------------------------------------------------------------------- END

