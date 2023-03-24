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

#include "big7seg.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define BIG7SEG_DUMMY 0
#define NULL 0

// -------------------------------------------------------------------VARIABLES

static const uint8_t BIG7SEG_CHAR_TABLE[ 51 ] =
{
    0x40, // '-'
    0x80, // '.'   Sevensegment bit order
    0x52, // '/'   (dp)(g)(f)(e)(d)(c)(b)(a)
    0x3F, // '0'
    0x06, // '1'    _a_
    0x5B, // '2'  f|   |b
    0x4F, // '3'   |_g_|
    0x66, // '4'  e|   |c
    0x6D, // '5'   |_d_|.dp
    0x7D, // '6'
    0x07, // '7'
    0x7F, // '8'
    0x6F, // '9'
    0x00, // ':'
    0x00, // ';'
    0x00, // '<'
    0x00, // '='
    0x00, // '>'
    0x00, // '?'
    0x00, // '@'
    0x77, // 'A'
    0x7C, // 'B'
    0x39, // 'C'
    0x5E, // 'D'
    0x79, // 'E'
    0x71, // 'F'
    0x6F, // 'G'
    0x76, // 'H'
    0x30, // 'I'
    0x1E, // 'J'
    0x70, // 'K'
    0x38, // 'L'
    0x15, // 'M'
    0x54, // 'N'
    0x3F, // 'O'
    0x73, // 'P'
    0x67, // 'Q'
    0x50, // 'R'
    0x6D, // 'S'
    0x78, // 'T'
    0x3E, // 'U'
    0xBE, // 'V'
    0x2A, // 'W'
    0x76, // 'X'
    0x6E, // 'Y'
    0x5B, // 'Z'
    0xF0, // '['
    0x52, // '/'
    0x0F, // ']'
    0x23, // '^'
    0x08, // '_'
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t big7seg_get_char ( char character );

static uint8_t big7seg_get_digit ( uint8_t digit );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void big7seg_cfg_setup ( big7seg_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mr = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

BIG7SEG_RETVAL big7seg_init ( big7seg_t *ctx, big7seg_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = BIG7SEG_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return BIG7SEG_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, BIG7SEG_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->mr, cfg->mr );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return BIG7SEG_OK;
}

void big7seg_generic_transfer 
( 
    big7seg_t *ctx, 
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

void big7seg_write_data ( big7seg_t *ctx, uint8_t write_data )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &write_data, 1 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );   
}

void big7seg_set7seg ( big7seg_t *ctx )
{
    digital_out_low( &ctx->mr );
    Delay_10us( );
    digital_out_high( &ctx->mr );
}

void big7seg_reset7seg ( big7seg_t *ctx )
{
    big7seg_write_data( ctx, 0x00 );
}

void big7seg_display_on ( big7seg_t *ctx )
{
    digital_out_high( &ctx->pwm );
}

void big7seg_display_off ( big7seg_t *ctx )
{
    digital_out_low( &ctx->pwm );
}

void big7seg_write_data_number ( big7seg_t *ctx, uint8_t display_number )
{
    big7seg_write_data( ctx, big7seg_get_digit( display_number ) );
}

void big7seg_write_data_character ( big7seg_t *ctx, char display_char )
{
    big7seg_write_data( ctx, big7seg_get_char( display_char ) );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t big7seg_get_char ( char character )
{
    if ( ( character >= '-' ) && ( character <= '_' ) )
    {
        return BIG7SEG_CHAR_TABLE[ character - '-' ];
    }
    else
    {
        return 0;
    }
}

static uint8_t big7seg_get_digit ( uint8_t digit )
{
    if ( ( digit >= 0 ) && ( digit <= 9 ) )
    {
        return BIG7SEG_CHAR_TABLE[ digit + 3 ];
    }
    else
    {
        return 0;
    }
}

// ------------------------------------------------------------------------- END

