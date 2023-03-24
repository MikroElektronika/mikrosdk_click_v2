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

#include "ledringr.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LEDRINGR_DUMMY 0

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ledringr_cfg_setup ( ledringr_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mr = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

LEDRINGR_RETVAL ledringr_init ( ledringr_t *ctx, ledringr_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LEDRINGR_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LEDRINGR_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LEDRINGR_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 

    digital_out_init( &ctx->mr, cfg->mr );

    return LEDRINGR_OK;
}

void ledringr_transfer_data 
(
    ledringr_t *ctx, 
    uint8_t *write_buf,
    uint16_t wbuf_size,
    uint8_t *read_buf,
    uint16_t rbuf_size
)
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, write_buf, wbuf_size, read_buf, rbuf_size );
    spi_master_deselect_device( ctx->chip_select );   
}

void ledringr_write_data ( ledringr_t *ctx, uint32_t data_to_write )
{
    uint8_t buffer[ 4 ];
    buffer[ 0 ] = data_to_write;
    buffer[ 1 ] = data_to_write >> 8;
    buffer[ 2 ] = data_to_write >> 16;
    buffer[ 3 ] = data_to_write >> 24;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &buffer[ 0 ], 4 );
//     spi_master_write( &ctx->spi, buffer[ 1 ], 1 );
//     spi_master_write( &ctx->spi, buffer[ 2 ], 1 );
//     spi_master_write( &ctx->spi, buffer[ 3 ], 1 );
    Delay_10us( );

    spi_master_deselect_device( ctx->chip_select ); 
}

void ledringr_turn_on_led ( ledringr_t *ctx, uint8_t led_position )
{
    uint32_t data_to_write;
    uint8_t buffer[ 4 ];

    uint32_t ledring_table [ 33 ] =
    {
        0x00000000,    //NO LED
        0x00000001,    //LED 1
        0x00000002,    //LED 2
        0x00000004,    //LED 3
        0x00000008,    //LED 4
        0x00000010,    //LED 5
        0x00000020,    //LED 6
        0x00000040,    //LED 7
        0x00000080,    //LED 8
        0x00000100,    //LED 9
        0x00000200,    //LED 10
        0x00000400,    //LED 11
        0x00000800,    //LED 12
        0x00001000,    //LED 13
        0x00002000,    //LED 14
        0x00004000,    //LED 15
        0x00008000,    //LED 16
        0x00010000,    //LED 17
        0x00020000,    //LED 18
        0x00040000,    //LED 19
        0x00080000,    //LED 20
        0x00100000,    //LED 21
        0x00200000,    //LED 22
        0x00400000,    //LED 23
        0x00800000,    //LED 24
        0x01000000,    //LED 25
        0x02000000,    //LED 26
        0x04000000,    //LED 27
        0x08000000,    //LED 28
        0x10000000,    //LED 29
        0x20000000,    //LED 30
        0x40000000,    //LED 31
        0x80000000,    //LED 32
    };

    if ( led_position >= 0 && led_position < 33 )
    {
        data_to_write = ledring_table[ led_position ];
    }
    else
    {
        data_to_write = 0x00000000;
    }

    buffer[ 0 ] = data_to_write;
    buffer[ 1 ] = data_to_write >> 8;
    buffer[ 2 ] = data_to_write >> 16;
    buffer[ 3 ] = data_to_write >> 24;

    spi_master_select_device( ctx->chip_select );

    spi_master_write( &ctx->spi, &buffer[ 0 ], 1 );
//     spi_master_write( &ctx->spi, buffer[ 1 ] );
//     spi_master_write( &ctx->spi, buffer[ 2 ] );
//     spi_master_write( &ctx->spi, buffer[ 3 ] );
    Delay_10us( );

    spi_master_deselect_device( ctx->chip_select ); 
}

void ledringr_led_ring_set ( ledringr_t *ctx )
{
    digital_out_low( &ctx->mr );
    Delay_10us( );
    digital_out_high( &ctx->mr );
}

void ledringr_led_ring_reset ( ledringr_t *ctx )
{
    ledringr_write_data( ctx, 0 );
}

// ------------------------------------------------------------------------- END
