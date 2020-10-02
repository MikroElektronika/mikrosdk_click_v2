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

#include "c7seg.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define C7SEG_DUMMY 0

#define C7SEG_EMPTY_DISPLAY 0

// ------------------------------------------------------------------ CONSTANTS

static const uint8_t C7SEG_CHAR_TABLE[ 51 ]=
{
    0x80, // '-'
    0x01, // '.'   Sevensegment bit order
    0x00, // '/'   (g)(f)(e)(d)(c)(a)(b)(dp)
    0x7E, // '0'
    0x0A, // '1'    _a_
    0xB6, // '2'  f|   |b
    0x9E, // '3'   |_g_|
    0xCA, // '4'  e|   |c
    0xDC, // '5'   |_d_|.dp
    0xFC, // '6'
    0x0E, // '7'
    0xFE, // '8'
    0xDE, // '9'
    0x00, // ':'
    0x00, // ';'
    0x00, // '<'
    0x00, // '='
    0x00, // '>'
    0x00, // '?'
    0x00, // '@'
    0xEE, // 'A'
    0xF8, // 'B'
    0x74, // 'C'
    0xBA, // 'D'
    0xF4, // 'E'
    0xE4, // 'F'
    0x7C, // 'G'
    0xEA, // 'H'
    0x0A, // 'I'
    0x3A, // 'J'
    0xE0, // 'K'
    0x70, // 'L'
    0x2C, // 'M'
    0xA8, // 'N'
    0x7E, // 'O'
    0xE6, // 'P'
    0xCE, // 'Q'
    0x64, // 'R'
    0xDC, // 'S'
    0xF0, // 'T'
    0x7A, // 'U'
    0x7B, // 'V'
    0xFB, // 'W'
    0xEA, // 'X'
    0xDA, // 'Y'
    0xB6, // 'Z'
    0x00, // '['
    0x00, // '/'
    0x00, // ']'
    0x00, // '^'
    0x10, // '_'
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

// Reset delay
static void dev_reset_delay ( void );

// Function that defines a digit from C7SEG_CHAR_TABLE
static uint8_t dev_get_digit (  uint8_t digit );

// Function that defines a character from C7SEG_CHAR_TABLE
static uint8_t dev_get_char ( char character );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c7seg_cfg_setup ( c7seg_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->mr = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

C7SEG_RETVAL c7seg_init ( c7seg_t *ctx, c7seg_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = C7SEG_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return C7SEG_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, C7SEG_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    
    digital_out_init( &ctx->mr, cfg->mr );
    digital_out_init( &ctx->pwm, cfg->pwm );

    return C7SEG_OK;
}

void c7seg_default_cfg ( c7seg_t *ctx )
{
    // Sets MR pin high
    
    c7seg_reset ( ctx );
    
    // Turns display on
    
    digital_out_high( &ctx->pwm );
}

void c7seg_generic_transfer ( c7seg_t *ctx, uint8_t *wr_buf, uint16_t wr_len, uint8_t *rd_buf, uint16_t rd_len )
{
    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, wr_buf, wr_len, rd_buf, rd_len );
    spi_master_deselect_device( ctx->chip_select );   
}

void c7seg_write_data ( c7seg_t *ctx, uint8_t write_left, uint8_t write_right )
{
    uint8_t tx_buf[ 2 ];
    tx_buf[ 0 ] = write_right;
    tx_buf[ 1 ] = write_left;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

void c7seg_reset ( c7seg_t *ctx )
{
    digital_out_low( &ctx->mr );
    dev_reset_delay( );
    digital_out_high( &ctx->mr );
}

void c7seg_display_mode ( c7seg_t *ctx, uint8_t display_mode )
{
    if ( display_mode == C7SEG_DISPLAY_OFF )
    {
        digital_out_low( &ctx->pwm );
    }
    
    if ( display_mode == C7SEG_DISPLAY_ON )
    {
        digital_out_high( &ctx->pwm );
    }
}

void c7seg_write_data_number ( c7seg_t *ctx, uint8_t left_number, uint8_t right_number )
{
    c7seg_write_data( ctx, dev_get_digit( left_number ), dev_get_digit( right_number ) );
}

void c7seg_write_data_character ( c7seg_t *ctx, char left_char, char right_char )
{
    c7seg_write_data( ctx, dev_get_char( left_char ) , dev_get_char( right_char ) );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void )
{
    Delay_10ms( );
}

static uint8_t dev_get_digit (  uint8_t digit )
{
    if ( ( digit >= 0 ) && ( digit <= 9 ) )
    {
        return C7SEG_CHAR_TABLE[ digit + 3 ];
    }
    else
    {
        return C7SEG_EMPTY_DISPLAY;
    }
}

static uint8_t dev_get_char ( char character )
{
    if ( ( character >= '-' ) && ( character <= '_' ) )
    {
        return C7SEG_CHAR_TABLE[ character - '-' ];
    }
    else
    {
        return C7SEG_EMPTY_DISPLAY;
    }
}

// ------------------------------------------------------------------------- END

