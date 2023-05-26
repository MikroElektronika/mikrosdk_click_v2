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

#include "eink290inch.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define EINK290INCH_DUMMY 0

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void wait_until_idle ( eink290inch_t *ctx );
static void frame_px ( eink290inch_t *ctx, uint16_t x, uint16_t y, uint8_t font_col );
static void char_wr ( eink290inch_t *ctx, uint16_t ch_idx );
static void display_delay ( );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void eink290inch_cfg_setup ( eink290inch_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->dc = HAL_PIN_NC;
    cfg->bsy = HAL_PIN_NC;

    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
    cfg->spi_speed = 100000; 
}

err_t eink290inch_init ( eink290inch_t *ctx, eink290inch_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.mode      = cfg->spi_mode;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = EINK290INCH_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return EINK290INCH_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, EINK290INCH_DUMMY );
    spi_master_set_mode( &ctx->spi, spi_cfg.mode );
    spi_master_set_speed( &ctx->spi, spi_cfg.speed );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select ); 

    // Output pins 
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );

    // Input pins
    digital_in_init( &ctx->bsy, cfg->bsy );

    return EINK290INCH_OK;
}

void eink290inch_send_cmd ( eink290inch_t *ctx, uint8_t command )
{
    digital_out_low( &ctx->dc );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &command, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void eink290inch_send_data ( eink290inch_t *ctx, uint8_t c_data )
{
    digital_out_high( &ctx->dc );
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &c_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void eink290inch_reset ( eink290inch_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

void eink290inch_sleep_mode ( eink290inch_t *ctx )
{
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_DEEP_SLEEP_MODE );
    wait_until_idle( ctx );
}

void eink290inch_set_lut ( eink290inch_t *ctx, const uint8_t *lut, uint8_t lut_cnt )
{
    uint8_t cnt;
    
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_WRITE_LUT_REGISTER );
    
    for ( cnt = 0; cnt < lut_cnt; cnt++ )
    {
        eink290inch_send_data( ctx, lut[ cnt ] );
    }
}
 
void eink290inch_start_config ( eink290inch_t *ctx )
{
    eink290inch_reset( ctx );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_DRIVER_OUTPUT_CONTROL );
    eink290inch_send_data( ctx, ( ( EINK290INCH_DISPLAY_HEIGHT - 1 ) & 0xFF ) );
    eink290inch_send_data( ctx, ( ( ( EINK290INCH_DISPLAY_HEIGHT - 1 ) >> 8 ) & 0xFF ) );
    eink290inch_send_data( ctx, 0x00 );                                                
    
    /* New eink display sttings */
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_DUMMY_LINE_PERIOD );		           
    eink290inch_send_data( ctx, 0x1A );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_GATE_TIME );		                   
    eink290inch_send_data( ctx, 0x08 );

    eink290inch_send_cmd( ctx, EINK290INCH_CMD_DATA_ENTRY_MODE_SETTING );		       
    eink290inch_send_data( ctx, 0x01 );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_X_ADDRESS_START_END_POSITION );
    eink290inch_send_data( ctx, 0x00 );		                                           
    eink290inch_send_data( ctx, 0x0f );		                                           
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_Y_ADDRESS_START_END_POSITION );
    eink290inch_send_data( ctx, 0x27 );		                                           
    eink290inch_send_data( ctx, 0x01 ); 
    eink290inch_send_data( ctx, 0x00 );		                                           
    eink290inch_send_data( ctx, 0x00 );

    eink290inch_send_cmd( ctx, EINK290INCH_CMD_WRITE_VCOM_REGISTER );                  
    eink290inch_send_data( ctx, 0x6E );                                                
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_BORDER_WAVEFORM_CONTROL );		       
    eink290inch_send_data( ctx, 0x33 );		                                           
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_DATA_ENTRY_MODE_SETTING );
    eink290inch_send_data( ctx, 0x03 );
    
    display_delay( );
}

void eink290inch_set_mem_pointer ( eink290inch_t *ctx, uint16_t x, uint16_t y )
{
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_X_ADDRESS_COUNTER );
    eink290inch_send_data( ctx, ( ( x >> 3 ) & 0xFF ) );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_Y_ADDRESS_COUNTER );
    eink290inch_send_data( ctx, ( y & 0xFF ) );
    eink290inch_send_data( ctx, ( ( y >> 8 ) & 0xFF ) );
}

void eink290inch_set_mem_area ( eink290inch_t *ctx, eink290inch_xy_t *xy )
{
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_X_ADDRESS_START_END_POSITION );
    eink290inch_send_data( ctx, ( xy->x_start >> 3 ) & 0xFF );
    eink290inch_send_data( ctx, ( xy->x_end >> 3 ) & 0xFF );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_SET_RAM_Y_ADDRESS_START_END_POSITION );
    eink290inch_send_data( ctx, xy->y_start & 0xFF );
    eink290inch_send_data( ctx, ( xy->y_start >> 8 ) & 0xFF );
    eink290inch_send_data( ctx, xy->y_end & 0xFF );
    eink290inch_send_data( ctx, ( xy->y_end >> 8 ) & 0xFF );
}

void eink290inch_update_display ( eink290inch_t *ctx )
{
    Delay_100ms( );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_DISPLAY_UPDATE_CONTROL_2 );
    eink290inch_send_data( ctx, 0xC7 );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_MASTER_ACTIVATION );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_TERMINATE_FRAME_READ_WRITE );
    wait_until_idle( ctx );
}

void eink290inch_fill_screen ( eink290inch_t *ctx, uint8_t color )              
{
    uint16_t cnt;
    eink290inch_xy_t xy;
    
    xy.x_start = 0;
    xy.y_start = 0; 
    xy.x_end = EINK290INCH_DISPLAY_WIDTH - 1;
    xy.y_end = EINK290INCH_DISPLAY_HEIGHT - 1;

    eink290inch_set_mem_area( ctx, &xy );
    eink290inch_set_mem_pointer( ctx, 0, 0 );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_WRITE_RAM );

    for ( cnt = 0; cnt < EINK290INCH_DISPLAY_RESOLUTIONS; cnt++ )
    {
        eink290inch_send_data( ctx, color );
    }

    display_delay( );
    eink290inch_update_display( ctx );
}

void eink290inch_display_image ( eink290inch_t *ctx, const uint8_t* image_buffer )
{
    uint16_t cnt;
    eink290inch_xy_t xy;
    
    xy.x_start = 0;
    xy.y_start = 0; 
    xy.x_end = EINK290INCH_DISPLAY_WIDTH - 1;
    xy.y_end = EINK290INCH_DISPLAY_HEIGHT - 1;

    eink290inch_set_mem_area( ctx, &xy );
    eink290inch_set_mem_pointer( ctx, 0, 0 );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_WRITE_RAM );

    for ( cnt = 0; cnt < EINK290INCH_DISPLAY_RESOLUTIONS; cnt++)
    {
        eink290inch_send_data( ctx, image_buffer[ cnt ]);
    }

    display_delay( );
    eink290inch_update_display( ctx );
}

#ifndef IMAGE_MODE_ONLY
void eink290inch_text ( eink290inch_t *ctx, uint8_t *text, eink290inch_set_text_t *text_set )
{
    uint16_t cnt;
    eink290inch_xy_t xy;
    
    if ( ( text_set->text_x >= EINK290INCH_DISPLAY_WIDTH ) || ( text_set->text_y >= EINK290INCH_DISPLAY_HEIGHT ) )
    {
        return;
    }
    
    xy.x_start = 0;
    xy.y_start = 0; 
    xy.x_end = EINK290INCH_DISPLAY_WIDTH - 1;
    xy.y_end = EINK290INCH_DISPLAY_HEIGHT - 1;
    
    ctx->dev_cord.x = text_set->text_x;
    ctx->dev_cord.y = text_set->text_y;

    for ( cnt = 0; cnt < text_set->n_char; cnt++ )
    {
        char_wr( ctx, text[ cnt ] );
    }
    
    eink290inch_set_mem_area( ctx, &xy );
    eink290inch_set_mem_pointer( ctx, 0, 0 );
    eink290inch_send_cmd( ctx, EINK290INCH_CMD_WRITE_RAM );

    for ( cnt = 0; cnt < EINK290INCH_DISPLAY_RESOLUTIONS; cnt++ )
    {
        eink290inch_send_data( ctx, ctx->frame[ cnt ]);
    }

    display_delay( );
    eink290inch_update_display( ctx );
}

void eink290inch_set_font ( eink290inch_t *ctx, eink290inch_font_t *cfg_font )
{
    ctx->dev_font.p_font        = cfg_font->p_font;
    ctx->dev_font.first_char    = cfg_font->p_font[ 2 ] + ( cfg_font->p_font[ 3 ] << 8 );
    ctx->dev_font.last_char     = cfg_font->p_font[ 4 ] + ( cfg_font->p_font[ 5 ] << 8 );
    ctx->dev_font.height        = cfg_font->p_font[ 6 ];
    ctx->dev_font.color         = cfg_font->color;
    ctx->dev_font.orientation   = cfg_font->orientation;
}
#endif

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void wait_until_idle ( eink290inch_t *ctx )
{
    uint8_t state;
    do
    {
        state = digital_in_read( &ctx->bsy );
        Delay_100ms( );
    } 
    while ( state == 1 );
}

#ifndef IMAGE_MODE_ONLY
static void frame_px ( eink290inch_t *ctx, uint16_t x, uint16_t y, uint8_t font_col )
{
    uint16_t off;
    uint16_t pos;

    pos = ( y * ( EINK290INCH_DISPLAY_WIDTH / 8 ) ) + ( x / 4 );
    off = ( 3 - ( x % 4 ) ) * 2;

    ctx->frame[ pos ] &= ~( 0x03 << off );
    ctx->frame[ pos ] |= ( ( font_col & 0x03 ) << off );
}

static void char_wr ( eink290inch_t *ctx, uint16_t ch_idx )
{
    uint8_t   ch_width = 0;
    uint8_t   x_cnt;
    uint8_t   y_cnt;
    uint16_t  x = 0;
    uint16_t  y = 0;
    uint16_t  tmp;
    uint8_t   temp = 0;
    uint8_t   mask = 0;
    uint32_t  offset;
    const uint8_t *ch_table;
    const uint8_t *ch_bitmap;

    if ( ch_idx < ctx->dev_font.first_char )
    {
        return;
    }
    if ( ch_idx > ctx->dev_font.last_char )
    {
        return;
    }

    offset = 0;
    tmp = ( ch_idx - ctx->dev_font.first_char ) << 2;
    ch_table = ( const uint8_t* ) ( ctx->dev_font.p_font + ( 8 + tmp ) );
    ch_width = *ch_table;

    offset = ( uint32_t ) ch_table[ 1 ] + ( ( uint32_t ) ch_table [ 2 ] << 8 ) + ( ( uint32_t ) ch_table[ 3 ] << 16 );

    ch_bitmap = ctx->dev_font.p_font + offset;

    if ( ( ctx->dev_font.orientation == EINK290INCH_FO_HORIZONTAL ) ||
        ( ctx->dev_font.orientation == EINK290INCH_FO_VERTICAL_COLUMN ) )
    {
        y = ctx->dev_cord.y;
        for ( y_cnt = 0; y_cnt < ctx->dev_font.height; y_cnt++ )
        {
            x = ctx->dev_cord.x;
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
                    frame_px( ctx, x, y, ctx->dev_font.color );
                    Delay_80us( );
                }

                x++;
                mask <<= 1;
            }
            y++;
        }

        if ( ctx->dev_font.orientation == EINK290INCH_FO_HORIZONTAL )
        {
            ctx->dev_cord.x = x + 1;
        }
        else
        {
            ctx->dev_cord.y = y;
        }
    }
    else
    {
        y = ctx->dev_cord.x;

        for ( y_cnt = 0; y_cnt < ctx->dev_font.height; y_cnt++ )
        {
            x = ctx->dev_cord.y;
            mask = 0;

            for ( x_cnt = 0; x_cnt < ch_width; x_cnt++ )
            {
                if ( mask == 0 )
                {
                    temp = *ch_bitmap++;
                    mask = 0x01;
                }

                if ( temp & mask )
                {
                    frame_px( ctx, x, y, ctx->dev_font.color );
                    Delay_80us( );
                }

                x--;
                mask <<= 1;
            }
            y++;
        }
        ctx->dev_cord.y = x - 1;
    }
}
#endif

static void display_delay ( )
{
    Delay_1ms( );
    Delay_1ms( );
}

// ------------------------------------------------------------------------- END

