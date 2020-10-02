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

#include "lcdmono.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define LCDMONO_DUMMY 0
#define NULL 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t bits_rotate ( uint8_t byte );
static void spi_send_data ( lcdmono_t *ctx, uint8_t *data_buf, uint16_t len );
static void set_frame_px ( lcdmono_t *ctx, uint16_t x, uint16_t y );
static void set_char_to_frame ( lcdmono_t *ctx, uint16_t ch_idx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void lcdmono_cfg_setup ( lcdmono_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    // Additional gpio pins

    cfg->com = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
    cfg->spi_speed = 100000; 

    cfg->dev_lcd_frame_color = 0x00;
}

LCDMONO_RETVAL lcdmono_init ( lcdmono_t *ctx, lcdmono_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = LCDMONO_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    ctx->lcd_frame_color = cfg->dev_lcd_frame_color;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return LCDMONO_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, LCDMONO_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 

    digital_out_init( &ctx->com, cfg->com );
    
    digital_out_write( &ctx->com, 1 );
    spi_master_select_device( ctx->chip_select );

    return LCDMONO_OK;
}

void lcdmono_generic_transfer 
( 
    lcdmono_t *ctx, 
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

void lcdmono_send_line_package ( lcdmono_t *ctx, uint8_t addr, uint8_t *tx_data )
{
    uint8_t cnt;
    uint8_t send_buf[ 20 ];
    
    send_buf[ 0 ] = LCDMONO_CMD_DISPLAY_FLAG;
    send_buf[ 1 ] = bits_rotate( addr );

    for ( cnt = 2; cnt <= 18; cnt++ )
    {
        send_buf[ cnt ] = tx_data[ cnt - 2 ];
    }
    
    // 2 Dummy bytes
    send_buf[ 18 ] = LCDMONO_DUMMY_BYTE;
    send_buf[ 19 ] = LCDMONO_DUMMY_BYTE;
    
    spi_send_data( ctx, send_buf, 20 );
}

void lcdmono_clear ( lcdmono_t *ctx )
{
    uint8_t send_buf[ 2 ];

    send_buf[ 0 ] = LCDMONO_CMD_CLEAR_FLAG;
    send_buf[ 1 ] = LCDMONO_DUMMY_BYTE;

    spi_send_data( ctx, send_buf, 2 );
}

void lcdmono_draw_frame ( lcdmono_t *ctx, uint8_t *frame_data )
{
    uint8_t cnt;
    uint8_t row_cnt;
    uint16_t byte_cnt = 0;
    uint16_t frame_cnt = 0;
    uint8_t send_buf[ 2307 ];

    send_buf[ byte_cnt++ ] = LCDMONO_CMD_DISPLAY_FLAG;
    
    for ( row_cnt = 1; row_cnt <= 128; row_cnt++ )
    {
        send_buf[ byte_cnt++ ] = bits_rotate( row_cnt );
        
        for ( cnt = 0; cnt < 16; cnt++ )
        {
            send_buf[ byte_cnt++ ] = frame_data[ frame_cnt++ ];
        }
        send_buf[ byte_cnt++ ] = LCDMONO_DUMMY_BYTE;
    }
    send_buf[ byte_cnt ] = LCDMONO_DUMMY_BYTE;
            
    spi_send_data( ctx, send_buf, 2307 );
}

void lcdmono_draw_const_frame ( lcdmono_t *ctx, const uint8_t *frame_data )
{
	uint8_t cnt;
    uint8_t row_cnt;
    uint16_t byte_cnt = 0;
    uint16_t frame_cnt = 0;
    static uint8_t send_buf[ 2307 ];

    send_buf[ byte_cnt++ ] = LCDMONO_CMD_DISPLAY_FLAG;
    
    for ( row_cnt = 1; row_cnt <= 128; row_cnt++ )
    {
        send_buf[ byte_cnt++ ] = bits_rotate( row_cnt );
        
        for ( cnt = 0; cnt < 16; cnt++ )
        {
            send_buf[ byte_cnt++ ] = frame_data[ frame_cnt++ ];
        }
        send_buf[ byte_cnt++ ] = LCDMONO_DUMMY_BYTE;
    }
    send_buf[ byte_cnt ] = LCDMONO_DUMMY_BYTE;
            
    spi_send_data( ctx, send_buf, 2307 );
}

void lcdmono_draw_text ( lcdmono_t *ctx, char *text_buf, lcdmono_text_settings_t *tx_set , uint8_t end_mode)
{
    uint32_t cnt;
    uint8_t tmp;

    // Convert char to pixels
    ctx->lcd_cord.x = tx_set->start_cord_x / 2;
    ctx->lcd_cord.y = tx_set->start_cord_y;

    // Set background color
    if ( tx_set->bg_color == LCDMONO_COLOR_WHITE )
    {
        // Text color WHITE
        ctx->lcd_frame_color = 0x00;
          
        if ( ( end_mode & 0x10 ) != 0 )
        {
            // Set backround frame buffers
            for ( cnt = 0; cnt < 2307; cnt++ )
            {
                // Frame buffer
                ctx->lcd_frame[ cnt ] = 0xFF;
            }
        }
    }
    else
    {
        // Text color BLACK
        ctx->lcd_frame_color = 0xFF;

        if ( ( end_mode & 0x10 ) != 0 )
        {
            // Set backround frame buffers
            for ( cnt = 0; cnt < 2307; cnt++ )
            {
                // Frame buffer
                ctx->lcd_frame[ cnt ] = 0x00;
            }
        }
    }

    for ( cnt = 0; cnt < tx_set->len; cnt++ )
    {
        set_char_to_frame( ctx, text_buf[ cnt ] );
    }
    
    // Refresh display frame
    if ( ( end_mode & 0x01 ) == 0x01 )
    {
        lcdmono_draw_frame( ctx, ctx->lcd_frame );
    }
}

void lcdmono_set_font ( lcdmono_t *ctx, lcdmono_font_t *dev_lcd_font )
{
    ctx->lcd_font.this_font     = dev_lcd_font->this_font;
    ctx->lcd_font.first_char    = dev_lcd_font->this_font[ 2 ] + ( dev_lcd_font->this_font[ 3 ] << 8 );
    ctx->lcd_font.last_char     = dev_lcd_font->this_font[ 4 ] + ( dev_lcd_font->this_font[ 5 ] << 8 );
    ctx->lcd_font.height        = dev_lcd_font->this_font[ 6 ];
}

void lcdmono_display_power ( lcdmono_t *ctx, uint8_t ctrl )
{
    digital_out_write( &ctx->com, ctrl );
}

void lcdmono_display_reset ( lcdmono_t *ctx )
{
    digital_out_high( &ctx->com );
    Delay_100ms( );
    digital_out_low( &ctx->com );
    Delay_100ms( );
    digital_out_high( &ctx->com );
    Delay_100ms( );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t bits_rotate ( uint8_t in_byte )
{
    uint8_t new_data = 0;

    new_data |= ( in_byte & 0x01 ) << 7;
    new_data |= ( in_byte & 0x02 ) << 5;
    new_data |= ( in_byte & 0x04 ) << 3;
    new_data |= ( in_byte & 0x08 ) << 1;
    new_data |= ( in_byte & 0x10 ) >> 1;
    new_data |= ( in_byte & 0x20 ) >> 3;
    new_data |= ( in_byte & 0x40 ) >> 5;
    new_data |= ( in_byte & 0x80 ) >> 7;

    return new_data;
}

static void spi_send_data ( lcdmono_t *ctx, uint8_t *data_buf, uint16_t len )
{
    spi_master_select_device( ctx->chip_select );
    Delay_10us( );  // tsSCS time
    spi_master_write( &ctx->spi, data_buf, len );
    Delay_1us( );   // thSCS time
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    Delay_1us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_select_device( ctx->chip_select );
    Delay_80us( );  // twSCS-LOW time
    Delay_80us( );
    spi_master_deselect_device( ctx->chip_select ); 
    spi_master_select_device( ctx->chip_select );
}

static void set_frame_px ( lcdmono_t *ctx, uint16_t x, uint16_t y )
{
    uint8_t  off;
    uint32_t pos;

    pos = ( y * ( LCDMONO_DISPLAY_WIDTH / 8 ) ) + ( x / 4 );
    off = ( 3 - ( x % 4 ) ) * 2;

    ctx->lcd_frame[ pos ] &= ~( 0x03 << off );
    ctx->lcd_frame[ pos ] |= ( ( ctx->lcd_frame_color & 0x03 ) << off );
}

static void set_char_to_frame ( lcdmono_t *ctx, uint16_t ch_idx )
{
    static volatile uint16_t x = 0;
    static volatile uint16_t y = 0;
    uint8_t ch_width = 0;
    uint8_t x_cnt;
    uint8_t y_cnt;
    uint16_t tmp;
    uint8_t temp = 0;
    uint8_t mask = 0;
    uint32_t offset;
    const uint8_t *ch_table;
    const uint8_t *ch_bitmap;

    if ( ch_idx < ctx->lcd_font.first_char )
    {
        return;
    }
    if ( ch_idx > ctx->lcd_font.last_char )
    {
        return;
    }

    offset = 0;
    tmp = ( ch_idx - ctx->lcd_font.first_char ) << 2;
    ch_table = ( const uint8_t* ) ( ctx->lcd_font.this_font + ( 8 + tmp ) );
    ch_width = *ch_table;

    offset = ( uint32_t ) ch_table[ 1 ] + ( ( uint32_t ) ch_table[ 2 ] << 8 ) + ( ( uint32_t ) ch_table[ 3 ] << 16 );

    ch_bitmap = ctx->lcd_font.this_font + offset;

    y = ctx->lcd_cord.y;
    for ( y_cnt = 0; y_cnt < ctx->lcd_font.height; y_cnt++ )
    {
        x = ctx->lcd_cord.x;
        mask = 0;
        for ( x_cnt = 0; x_cnt < ch_width; x_cnt++ )
        {
            if ( !mask )
            {
                temp = *ch_bitmap++;
                mask = 0x01;
            }

            if ( temp & mask )
            {
                set_frame_px( ctx, x, y );
            }

            x++;
            mask <<= 1;
        }
        y++;
    }
    ctx->lcd_cord.x = x + 1;
}

// ------------------------------------------------------------------------- END

