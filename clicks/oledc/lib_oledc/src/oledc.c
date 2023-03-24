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

#include "oledc.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define OLEDC_DUMMY 0

static uint8_t cols[ 2 ]    = { OLEDC_COL_OFF, OLEDC_COL_OFF + 95 };          
static uint8_t rows[ 2 ]    = { OLEDC_ROW_OFF, OLEDC_ROW_OFF + 95 };

static uint8_t OLEDC_DEFAULT_REMAP = OLEDC_RMP_INC_HOR | OLEDC_RMP_COLOR_REV |
                                OLEDC_RMP_SEQ_RGB | OLEDC_RMP_SCAN_REV |
                                OLEDC_RMP_SPLIT_ENABLE | OLEDC_COLOR_65K;

static  uint8_t OLEDC_DEFAULT_VSL[ 3 ]       = { 0xA0, 0xB5, 0x55 };
static  uint8_t OLEDC_DEFAULT_CONTRAST[ 3 ]  = { 0x8A, 0x51, 0x8A };

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void box_area 
( 
    oledc_t *ctx, 
    uint8_t start_col, 
    uint8_t start_row, 
    uint8_t end_col, 
    uint8_t end_row, 
    uint16_t color 
);


static void draw_area
( 
    oledc_t *ctx, 
    uint8_t start_col, 
    uint8_t start_row, 
    uint8_t end_col, 
    uint8_t end_row, 
    const uint8_t *img 
);

static void pixel( oledc_t *ctx, uint8_t col, uint8_t row, uint16_t color );

static void character( oledc_t *ctx, uint16_t ch );


// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void oledc_cfg_setup ( oledc_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;

    // Additional gpio pins

    cfg->rw = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->dc = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->spi_speed = 100000; 
    cfg->spi_mode = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

OLEDC_RETVAL oledc_init ( oledc_t *ctx, oledc_cfg_t *cfg )
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );
    spi_cfg.speed     = cfg->spi_speed;
    spi_cfg.sck       = cfg->sck;
    spi_cfg.miso      = cfg->miso;
    spi_cfg.mosi      = cfg->mosi;
    spi_cfg.default_write_data = OLEDC_DUMMY;

    digital_out_init( &ctx->cs, cfg->cs );
    ctx->chip_select = cfg->cs;

    if (  spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR )
    {
        return OLEDC_INIT_ERROR;
    }

    spi_master_set_default_write_data( &ctx->spi, OLEDC_DUMMY );
    spi_master_set_speed( &ctx->spi, cfg->spi_speed );
    spi_master_set_mode( &ctx->spi, cfg->spi_mode );
    spi_master_set_chip_select_polarity( cfg->cs_polarity );

    // Output pins 
    
    digital_out_init( &ctx->rw, cfg->rw );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->dc );
    spi_master_deselect_device( ctx->chip_select );   

    return OLEDC_OK;
}

void oledc_enable ( oledc_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en, state );
}

void oledc_reset( oledc_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_1ms();
    digital_out_low( &ctx->rst );
    Delay_1ms();
    digital_out_high( &ctx->rst );
    Delay_100ms();
}

void oledc_more_arg_commands ( oledc_t *ctx, uint8_t command, uint8_t *args, uint16_t args_len )
{
    uint16_t cnt;

    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->dc );
    spi_master_write( &ctx->spi, &command, 1 );
    digital_out_high( &ctx->dc );
    
    for ( cnt = 0; cnt < args_len; cnt++ )
    {
        spi_master_write( &ctx->spi, &args[cnt], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );  
}

void oledc_one_arg_commands ( oledc_t *ctx, uint8_t command, uint8_t args )
{
    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->dc );
    spi_master_write( &ctx->spi, &command, 1 );
    digital_out_high( &ctx->dc );
    spi_master_write( &ctx->spi, &args, 1 );
    spi_master_deselect_device( ctx->chip_select );  
}

void oledc_default_cfg ( oledc_t *ctx )
{
    oledc_enable( ctx, 1 ); 
    oledc_reset( ctx );

    /* Unlock display and turn off */
    oledc_one_arg_commands( ctx, OLEDC_COMMAND_LOCK, OLEDC_DEFAULT_OLED_LOCK );
    oledc_one_arg_commands( ctx, OLEDC_COMMAND_LOCK, OLEDC_DEFAULT_CMD_LOCK  );
    oledc_more_arg_commands( ctx, OLEDC_SLEEP_ON,  0,  0 );

    /* Setup SSD1351 */
    oledc_one_arg_commands( ctx, OLEDC_SET_REMAP,       OLEDC_DEFAULT_REMAP        );
    oledc_one_arg_commands( ctx, OLEDC_MUX_RATIO,       OLEDC_DEFAULT_MUX_RATIO    );
    oledc_one_arg_commands( ctx, OLEDC_SET_START_LINE,  OLEDC_DEFAULT_START_LINE   );
    oledc_one_arg_commands( ctx, OLEDC_SET_OFFSET,      OLEDC_DEFAULT_OFFSET       );
    oledc_one_arg_commands( ctx, OLEDC_VCOMH,           OLEDC_DEFAULT_VCOMH        );
    oledc_one_arg_commands( ctx, OLEDC_CLOCK_DIV,       OLEDC_DEFAULT_DIVSET       );
    oledc_one_arg_commands( ctx, OLEDC_SET_RESET_PRECH, OLEDC_DEFAULT_PRECHARGE    );
    oledc_one_arg_commands( ctx, OLEDC_SETSEC_PRECH,    OLEDC_DEFAULT_PRECHARGE_2  );
    oledc_one_arg_commands( ctx, OLEDC_MASTER_CONTRAST, OLEDC_DEFAULT_MASTER_CONT  );

    oledc_more_arg_commands( ctx, OLEDC_CONTRAST,   OLEDC_DEFAULT_CONTRAST, 3 );
    oledc_more_arg_commands( ctx, OLEDC_VSL,        OLEDC_DEFAULT_VSL,      3 );

    /* Set normal mode and turn on display */
    oledc_more_arg_commands( ctx, OLEDC_MODE_NORMAL, 0, 0 );
    oledc_more_arg_commands( ctx, OLEDC_SLEEP_OFF,   0, 0 );
    oledc_fill_screen( ctx, 0 );
}

void oledc_fill_screen ( oledc_t *ctx, uint16_t color )
{
    box_area( ctx, 0, 0, 96, 96, color );
}

void oledc_rectangle
( 
    oledc_t *ctx, 
    uint8_t col_off, 
    uint8_t row_off, 
    uint8_t col_end, 
    uint8_t row_end, 
    uint16_t color 
)
{
    box_area( ctx, col_off, row_off, col_end, row_end, color );
}

void oledc_image( oledc_t *ctx, const uint8_t* img, uint8_t col_off, uint8_t row_off )
{
    const uint8_t *ptr = img;
    draw_area( ctx, col_off, row_off, col_off + ptr[2], row_off + ptr[4], ptr );
}

void oledc_text( oledc_t *ctx, uint8_t *text, uint16_t x, uint16_t y )
{
    uint8_t *ptr = text;

    if ( ( x >= OLEDC_SCREEN_WIDTH ) || ( y >= OLEDC_SCREEN_HEIGHT ) )
    {
        return;
    }
    
    ctx->x_cord = x;
    ctx->y_cord = y;

    while( *ptr )
    {
        character( ctx, *ptr++ );
    }
}

void oledc_set_font( oledc_t *ctx, const uint8_t *font_s, uint16_t color )
{
    ctx->font_obj               = font_s;
    ctx->font_first_char    = font_s[2] + (font_s[3] << 8);
    ctx->font_last_char     = font_s[4] + (font_s[5] << 8);
    ctx->font_height        = font_s[6];
    ctx->font_color         = color;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void box_area 
( 
    oledc_t *ctx, 
    uint8_t start_col, 
    uint8_t start_row, 
    uint8_t end_col, 
    uint8_t end_row, 
    uint16_t color 
)
{
    uint8_t   cmd       = OLEDC_WRITE_RAM;
    uint16_t  cnt       = ( end_col - start_col ) * ( end_row - start_row );
    uint8_t   clr[ 2 ]  = { 0 };

    if( ( start_col > OLEDC_SCREEN_WIDTH ) ||
        ( end_col > OLEDC_SCREEN_WIDTH ) )
        return;

    if( ( start_row > OLEDC_SCREEN_HEIGHT ) ||
        ( end_row > OLEDC_SCREEN_HEIGHT ) )
        return;

    if( ( end_col < start_col ) ||
        ( end_row < start_row ) )
        return;

    cols[ 0 ] = OLEDC_COL_OFF + start_col;
    cols[ 1 ] = OLEDC_COL_OFF + end_col - 1;
    rows[ 0 ] = OLEDC_ROW_OFF + start_row;
    rows[ 1 ] = OLEDC_ROW_OFF + end_row - 1;
    clr[ 0 ] |= color >> 8;
    clr[ 1 ] |= color & 0x00FF;

    oledc_more_arg_commands( ctx, OLEDC_SET_COL_ADDRESS, cols, 2 );
    oledc_more_arg_commands( ctx, OLEDC_SET_ROW_ADDRESS, rows, 2 );
    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->dc );
    spi_master_write( &ctx->spi, &cmd, 1 );
    digital_out_high( &ctx->dc );
    
    while( cnt-- )
    {
       spi_master_write( &ctx->spi, &clr[0], 1 );
       spi_master_write( &ctx->spi, &clr[1], 1 ); 
    }
    spi_master_deselect_device( ctx->chip_select );  
}

static void draw_area
( 
    oledc_t *ctx, 
    uint8_t start_col, 
    uint8_t start_row, 
    uint8_t end_col,
    uint8_t end_row, 
    const uint8_t *img 
)
{
    uint16_t    tmp  = 0;
    uint8_t     cmd  = OLEDC_WRITE_RAM;
    uint8_t     frb  = 0;
    uint8_t     srb  = 0;
    uint16_t    cnt  = ( end_col - start_col ) * ( end_row - start_row );
    
    const uint8_t*  ptr = img + OLEDC_IMG_HEAD;

    if( ( start_col > OLEDC_SCREEN_WIDTH ) ||
        ( end_col > OLEDC_SCREEN_WIDTH ) )
        return;

    if( ( start_row > OLEDC_SCREEN_HEIGHT ) ||
        ( end_row > OLEDC_SCREEN_HEIGHT ) )
        return;

    if( ( end_col < start_col ) ||
        ( end_row < start_row ) )
        return;

    cols[ 0 ] = OLEDC_COL_OFF + start_col;
    cols[ 1 ] = OLEDC_COL_OFF + end_col - 1;
    rows[ 0 ] = OLEDC_ROW_OFF + start_row;
    rows[ 1 ] = OLEDC_ROW_OFF + end_row - 1;

    oledc_more_arg_commands( ctx, OLEDC_SET_COL_ADDRESS, cols, 2 );
    oledc_more_arg_commands( ctx, OLEDC_SET_ROW_ADDRESS, rows, 2 );
    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->dc );
    spi_master_write( &ctx->spi, &cmd, 1 );
    digital_out_high( &ctx->dc );
    
    while( cnt-- )
    {
        frb = ptr[ tmp + 1 ];
        srb = ptr[ tmp ];
        spi_master_write( &ctx->spi, &frb, 1 );
        spi_master_write( &ctx->spi, &srb, 1 ); 
       
        tmp += 2;
    }
    spi_master_deselect_device( ctx->chip_select );  
}

static void pixel( oledc_t *ctx, uint8_t col, uint8_t row, uint16_t color )
{
    uint8_t cmd       = OLEDC_WRITE_RAM;
    uint8_t clr[ 2 ]  = { 0 };

    if( ( col > OLEDC_SCREEN_WIDTH ) || ( row > OLEDC_SCREEN_HEIGHT ) )
    {
        return;
    }
    cols[ 0 ] = OLEDC_COL_OFF + col;
    cols[ 1 ] = OLEDC_COL_OFF + col;
    rows[ 0 ] = OLEDC_ROW_OFF + row;
    rows[ 1 ] = OLEDC_ROW_OFF + row;
    clr[ 0 ] |= color >> 8;
    clr[ 1 ] |= color & 0x00FF;

    oledc_more_arg_commands( ctx, OLEDC_SET_COL_ADDRESS, cols, 2 );
    oledc_more_arg_commands( ctx, OLEDC_SET_ROW_ADDRESS, rows, 2 );
    spi_master_select_device( ctx->chip_select );
    digital_out_low( &ctx->dc );
    spi_master_write( &ctx->spi, &cmd, 1 );
    digital_out_high( &ctx->dc );
    spi_master_write( &ctx->spi, &clr[0], 1 );
    spi_master_write( &ctx->spi, &clr[1], 1 ); 
    spi_master_deselect_device( ctx->chip_select ); 
}

static void character( oledc_t *ctx, uint16_t ch )
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
    const uint8_t *ch_table;
    const uint8_t *ch_bitmap;

    if( ch < ctx->font_first_char )
        return;

    if( ch > ctx->font_last_char )
        return;

    offset = 0;
    tmp = (ch - ctx->font_first_char) << 2;
    ch_table = ctx->font_obj + 8 + tmp;
    ch_width = *ch_table;

    offset = (uint32_t)ch_table[1] + ((uint32_t)ch_table[2] << 8) + ((uint32_t)ch_table[3] << 16);

    ch_bitmap = ctx->font_obj + offset;

    y = ctx->y_cord;
    for (y_cnt = 0; y_cnt < ctx->font_height; y_cnt++)
    {
        x = ctx->x_cord;
        mask = 0;
        for( x_cnt = 0; x_cnt < ch_width; x_cnt++ )
        {
            if( !mask )
            {
                temp = *ch_bitmap++;
                mask = 0x01;
            }
            if( temp & mask )
                 pixel( ctx, x, y, ctx->font_color );

            x++;
            mask <<= 1;
        }
        y++;
    }
    ctx->x_cord = x + 1;
}

// ------------------------------------------------------------------------- END

