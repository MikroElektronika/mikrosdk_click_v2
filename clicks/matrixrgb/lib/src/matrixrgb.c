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

#include "matrixrgb.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define MATRIXRGB_DUMMY                                     0

#define MAX_ram_sizeIZE                                  4096

#define MATRIXRGB_CMD_POWER                              0x01
#define MATRIXRGB_CMD_BRIGHTNESS                         0x02
#define MATRIXRGB_CMD_LOAD_IMG                           0x03
#define MATRIXRGB_CMD_LOAD_PIX                           0x04
#define MATRIXRGB_CMD_PAN_SETUP                          0x10

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void send_command ( matrixrgb_t *ctx,  uint8_t cmd, uint8_t arg );
static void write_char ( matrixrgb_t *ctx, uint16_t ch );
static void wait_int_pin ( matrixrgb_t *ctx );
static void pattern_delay ( uint16_t delay_us );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void matrixrgb_cfg_setup ( matrixrgb_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->slp = HAL_PIN_NC;
    cfg->rdy = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

MATRIXRGB_RETVAL matrixrgb_init ( matrixrgb_t *ctx, matrixrgb_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = MATRIXRGB_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return MATRIXRGB_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, MATRIXRGB_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->slp, cfg->slp );
    spi_master_deselect_device( ctx->chip_select ); 

    // Input pins

    digital_in_init( &ctx->rdy, cfg->rdy );

    return MATRIXRGB_OK;
}

void matrixrgb_pattern_settings ( matrixrgb_t *ctx, uint8_t pattern_type, uint16_t pattern_delay_us )
{
    matrixrgb_device_settings( ctx, pattern_type );
    ctx->device_pattern_delay = pattern_delay_us;
}

void matrixrgb_generic_transfer 
( 
    matrixrgb_t *ctx, 
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

void matrixrgb_device_reset ( matrixrgb_t *ctx )
{
    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->rst );
    digital_out_high( &ctx->rst );
}

uint8_t matrixrgb_device_settings ( matrixrgb_t *ctx, uint8_t pattern_id )
{
    uint8_t tmp;
    switch  ( pattern_id )
    {
        case 0: case 1:
        {
            ctx->device_pixel.pixel_width = 32;
            ctx->device_pixel.pixel_height = 32;
            ctx->device_pixel.ram_size = 1024;
            break;
        }
        case 2: case 3:
        {
            ctx->device_pixel.pixel_width = 64;
            ctx->device_pixel.pixel_height = 32;
            ctx->device_pixel.ram_size = 2048;
            break;
        }
        case 4: case 5:
        {
            ctx->device_pixel.pixel_width = 32;
            ctx->device_pixel.pixel_height = 64;
            ctx->device_pixel.ram_size = 2048;
            break;
        }
        case 6: case 7:
        {
            ctx->device_pixel.pixel_width = 96;
            ctx->device_pixel.pixel_height = 32;
            ctx->device_pixel.ram_size = 3072;
            break;
        }
        case 8: case 9:
        {
            ctx->device_pixel.pixel_width = 32;
            ctx->device_pixel.pixel_height = 96;
            ctx->device_pixel.ram_size = 3072;
            break;
        }
        case 10: case 11:
        {
            ctx->device_pixel.pixel_width = 128;
            ctx->device_pixel.pixel_height = 32;
            ctx->device_pixel.ram_size = 4096;
            break;
        }
        case 12: case 13:
        {
            ctx->device_pixel.pixel_width = 32;
            ctx->device_pixel.pixel_height = 128;
            ctx->device_pixel.ram_size = 4096;
            break;
        }
        case 14: case 15:
        {
            ctx->device_pixel.pixel_width = 64;
            ctx->device_pixel.pixel_height = 64;
            ctx->device_pixel.ram_size = 4096;
            break;
        }
        default :
        {
            return 1;
        }
    }
    tmp = pattern_id;
    send_command( ctx, MATRIXRGB_CMD_PAN_SETUP, tmp );

    return 0;
}

void matrixrgb_set_power ( matrixrgb_t *ctx, uint8_t power_state )
{
    uint8_t tmp;
    tmp = power_state;
    send_command( ctx, MATRIXRGB_CMD_POWER, tmp  );
}

void matrixrgb_set_brightness ( matrixrgb_t *ctx, uint8_t brightness )
{
    uint8_t tmp;
    tmp = brightness;
    send_command( ctx, MATRIXRGB_CMD_BRIGHTNESS, tmp );
}

uint8_t matrixrgb_write_pixel ( matrixrgb_t *ctx, uint16_t x, uint16_t y, uint16_t color )
{
    uint16_t pos;
    uint8_t i;
    uint8_t tmp;
    uint8_t temp[ 2 ];

    if ( ( x >= ctx->device_pixel.pixel_width ) || ( y >= ctx->device_pixel.pixel_height ) )
    {
        return 1;
    }

    pos = ( ( y * ctx->device_pixel.pixel_width ) + x );

    wait_int_pin( ctx );
    spi_master_select_device( ctx->chip_select );
    tmp = MATRIXRGB_CMD_LOAD_PIX;
    spi_master_write( &ctx->spi, &tmp, 1 );
    temp[ 0 ] = color;
    temp[ 1 ] = color >> 8;
    spi_master_write( &ctx->spi, temp, 2 );
    tmp = color >> 8;
    spi_master_write( &ctx->spi, &tmp, 1 );
    temp[ 0 ] = pos;
    temp[ 1 ] = pos >> 8;
    spi_master_write( &ctx->spi, temp, 2 );
    tmp = pos >> 8;
    spi_master_write( &ctx->spi, &tmp, 1 );
    spi_master_deselect_device( ctx->chip_select );
    pattern_delay( ctx->device_pattern_delay );

    return 0;
}

void matrixrgb_fill_screen ( matrixrgb_t *ctx, uint16_t color )
{
    uint16_t pos;
    uint8_t tmp;
    uint8_t temp[ 2 ];

    wait_int_pin( ctx );
    spi_master_select_device( ctx->chip_select );
    tmp = MATRIXRGB_CMD_LOAD_IMG;
    spi_master_write( &ctx->spi, &tmp, 1 );
    
    for ( pos = 0; pos < ctx->device_pixel.ram_size; pos++ )
    {
        temp[ 0 ] = color;
        temp[ 1 ] = color << 8;
        spi_master_write( &ctx->spi, temp, 2 );
        tmp = color >> 8;
        spi_master_write( &ctx->spi, &tmp, 1 );
        pattern_delay( ctx->device_pattern_delay );
    }
    spi_master_deselect_device( ctx->chip_select ); 
}

void matrixrgb_draw_image ( matrixrgb_t *ctx, uint8_t *device_img )
{
    uint16_t pos;
    uint8_t tmp;

    wait_int_pin( ctx );
    spi_master_select_device( ctx->chip_select );
    tmp = MATRIXRGB_CMD_LOAD_IMG;
    spi_master_write( &ctx->spi, &tmp, 1 );

    for ( pos = 0; pos < ctx->device_pixel.ram_size; pos++ )
    {
        tmp = device_img[ pos * 2 ];
        spi_master_write( &ctx->spi, &tmp, 1 );
        tmp = device_img[ pos * 2 + 1 ];
        spi_master_write( &ctx->spi, &tmp, 1 );
        pattern_delay( ctx->device_pattern_delay );
    }
    spi_master_deselect_device( ctx->chip_select );  
}

void matrixrgb_set_font ( matrixrgb_t *ctx, matrixrgb_font_t *font_cfg )
{
    ctx->device_font.p_font       = font_cfg->p_font;
    ctx->device_font.first_char   = font_cfg->p_font[ 2 ] + ( font_cfg->p_font[ 3 ] << 8 );
    ctx->device_font.last_char    = font_cfg->p_font[ 4 ] + ( font_cfg->p_font[ 5 ] << 8 );
    ctx->device_font.height       = font_cfg->p_font[ 6 ];
    ctx->device_font.color        = font_cfg->color;
    ctx->device_font.orientation  = font_cfg->orientation;
}

uint8_t matrixrgb_write_text ( matrixrgb_t *ctx, char *text, uint16_t x, uint16_t y )
{
    uint16_t i;

    if ( ( x >= ctx->device_pixel.pixel_width ) || ( y >= ctx->device_pixel.pixel_height ) )
    {
        return 1;
    }

    i = 0;

    ctx->device_font_cord.x_cord = x;
    ctx->device_font_cord.y_cord = y;

    while ( text[ i ] != 0 )
    {
        write_char( ctx, text[ i ] );
        i++;
    }

    return 0;
}
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void send_command ( matrixrgb_t *ctx, uint8_t cmd, uint8_t arg )
{   
    uint8_t tx_buf[ 2 ];
    
    wait_int_pin( ctx );

    tx_buf[ 0 ] = cmd;
    tx_buf[ 1 ] = arg;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select ); 
}

static void write_char ( matrixrgb_t *ctx, uint16_t ch )
{
    uint8_t     ch_width = 0;
    uint8_t     x_cnt;
    uint8_t     y_cnt;
    uint16_t    x = 0;
    uint16_t    y = 0;
    uint16_t    tmp;
    uint8_t     temp = 0;
    uint8_t     mask = 0;
    uint32_t    offset;
    uint8_t     *ch_table;
    uint8_t     *ch_bitmap;

    if ( ch < ctx->device_font.first_char )
    {
        return;
    }

    if ( ch > ctx->device_font.last_char )
    {
        return;
    }

    offset = 0;
    tmp = ( ch - ctx->device_font.first_char ) << 2;
    ch_table = ctx->device_font.p_font + 8 + tmp;
    ch_width = *ch_table;
    
    offset = ( uint32_t ) ch_table[ 1 ] + ( ( uint32_t ) ch_table[ 2 ] << 8 ) + ( ( uint32_t ) ch_table[ 3 ] << 16 );
    ch_bitmap = ctx->device_font.p_font + offset;

    if ( ( ctx->device_font.orientation == MATRIXRGB_FONT_HORIZONTAL ) || ( ctx->device_font.orientation == MATRIXRGB_FONT_VERTICAL_COLUMN ) )
    {
        y = ctx->device_font_cord.y_cord;

        for ( y_cnt = 0; y_cnt < ctx->device_font.height; y_cnt++ )
        {
            x = ctx->device_font_cord.x_cord;
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
                    matrixrgb_write_pixel( ctx, x, y, ctx->device_font.color );
                }

                x++;
                mask <<= 1;
            }
            y++;
        }

        if ( ctx->device_font.orientation == MATRIXRGB_FONT_HORIZONTAL )
        {
            ctx->device_font_cord.x_cord = x + 1;
        }
        else
        {
            ctx->device_font_cord.y_cord = y;
        }
    }
    else
    {
        y = ctx->device_font_cord.x_cord;

        for ( y_cnt = 0; y_cnt < ctx->device_font.height; y_cnt++ )
        {
            x = ctx->device_font_cord.y_cord;
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
                    matrixrgb_write_pixel( ctx, x, y, ctx->device_font.color );
                }

                x--;
                mask <<= 1;
            }
            y++;
        }
        ctx->device_font_cord.y_cord = x - 1;
    }
}

static void wait_int_pin ( matrixrgb_t *ctx )
{
    uint8_t temp;
    temp = digital_in_read( &ctx->rdy );
    while ( temp != 1 )
    {
        temp = digital_in_read( &ctx->rdy );
    }
}

static void pattern_delay ( uint16_t delay_us )
{
    uint16_t cnt;
    
    for ( cnt = 0; cnt < delay_us; cnt++ )
    {
        Delay_1us( );
    }
}
// ------------------------------------------------------------------------- END

