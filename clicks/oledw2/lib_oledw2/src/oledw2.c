/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file oledw2.c
 * @brief OLED W 2 Click Driver.
 */

#include "oledw2.h"
#include "oledw2_resources.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief OLED W 2 rotate bits function.
 * @details This function rotates bits in a byte, MSb becomes LSb.
 * @param[in] in_byte : Input byte.
 * @return Rotated byte.
 * @note None.
 */
static uint8_t oledw2_rotate_bits ( uint8_t in_byte );

void oledw2_cfg_setup ( oledw2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->dc   = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t oledw2_init ( oledw2_t *ctx, oledw2_cfg_t *cfg ) 
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

    if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->dc, cfg->dc );
    Delay_1ms ( );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->dc );

    return SPI_MASTER_SUCCESS;
}

err_t oledw2_default_cfg ( oledw2_t *ctx ) 
{
    err_t error_flag = OLEDW2_OK;

    oledw2_enter_cmd_mode( ctx );
    oledw2_reset_device ( ctx );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_OFF );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_CLOCK_DIV );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_CLOCK_DIV );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_MULTIPLEX_RATIO );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_HEIGHT_MAX );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_OFFSET );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_DISPLAY_OFFSET );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_START_LINE );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_CHARGE_PUMP );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_CHARGE_PUMP_ENABLE );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_COM_SCAN_DEC );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_COM_PINS );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_COM_PINS );
    
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_CONTRAST );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CONTRAST_DEFAULT );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_PRECHARGE );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_PRECHARGE );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_VCOM_DESELECT );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_DEF_VCOM_DESELECT );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_ENTIRE_DISPLAY_RESUME );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_NORMAL_DISPLAY );

    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_ON );

    oledw2_set_rotation ( ctx, OLEDW2_ROTATION_0 );
    Delay_100ms ( );
    return error_flag;
}

err_t oledw2_write_cmd ( oledw2_t *ctx, uint8_t cmd )
{
    err_t error_flag = OLEDW2_OK;
    oledw2_enter_cmd_mode( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t oledw2_write_data ( oledw2_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = OLEDW2_OK;
    oledw2_enter_data_mode( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void oledw2_disable_device ( oledw2_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void oledw2_enable_device ( oledw2_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void oledw2_reset_device ( oledw2_t *ctx )
{
    Delay_10ms ( );
    digital_out_low ( &ctx->rst );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
}

void oledw2_enter_cmd_mode ( oledw2_t *ctx )
{
    digital_out_low ( &ctx->dc );
}

void oledw2_enter_data_mode ( oledw2_t *ctx )
{
    digital_out_high ( &ctx->dc );
}

void oledw2_set_font ( oledw2_t *ctx, uint8_t font_sel )
{
    switch ( font_sel )
    {
    #ifdef OLEDW2_FONT_5X7
        case OLEDW2_FONT_5X7:
        {
            ctx->font.font_buf = oledw2_font_5x7;
            ctx->font.width = 5;
            ctx->font.height = 7;
            break;
        }
    #endif
    #ifdef OLEDW2_FONT_6X8
        case OLEDW2_FONT_6X8:
        {
            ctx->font.font_buf = oledw2_font_6x8;
            ctx->font.width = 6;
            ctx->font.height = 8;
            break;
        }
    #endif
    #ifdef OLEDW2_FONT_8X16
        case OLEDW2_FONT_8X16:
        {
            ctx->font.font_buf = oledw2_font_8x16;
            ctx->font.width = 8;
            ctx->font.height = 16;
            break;
        }
    #endif
        default:
        {
            break;
        }
    }
}

void oledw2_set_rotation ( oledw2_t *ctx, uint8_t rotation )
{
    ctx->rotation = rotation;
}

err_t oledw2_set_column ( oledw2_t *ctx, uint8_t column )
{
    err_t error_flag = OLEDW2_OK;
    if ( column > OLEDW2_POS_WIDTH_MAX )
    {
        error_flag = OLEDW2_ERROR;
    }
    if ( OLEDW2_OK == error_flag )
    {
        error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_COLUMN_ADDR );
        error_flag |= oledw2_write_cmd ( ctx, column );
        error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_WIDTH_MAX );
    }
    return error_flag;
}

err_t oledw2_set_page ( oledw2_t *ctx, uint8_t page )
{
    err_t error_flag = OLEDW2_OK;
    if ( page > OLEDW2_POS_PAGE_MAX )
    {
        error_flag = OLEDW2_ERROR;
    }
    if ( OLEDW2_OK == error_flag )
    {
        error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_PAGE_ADDR );
        error_flag |= oledw2_write_cmd ( ctx, page );
        error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_PAGE_MAX );
    }
    return error_flag;
}

err_t oledw2_fill_screen ( oledw2_t *ctx )
{
    err_t error_flag = OLEDW2_OK;
    uint8_t col_data = 0xFF;
    uint8_t page_num = 0;
    uint8_t col_num = 0;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_ON );
    for ( page_num = OLEDW2_POS_PAGE_MIN; page_num <= OLEDW2_POS_PAGE_MAX; page_num++ )
    {
        error_flag |= oledw2_set_column ( ctx, OLEDW2_POS_WIDTH_MIN );
        error_flag |= oledw2_set_page ( ctx, page_num );
        for ( col_num = OLEDW2_POS_WIDTH_MIN; col_num <= OLEDW2_POS_WIDTH_MAX; col_num++ )
        {
            error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
        }
    }
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_ON );
    return error_flag;
}

err_t oledw2_clear_screen ( oledw2_t *ctx )
{
    err_t error_flag = OLEDW2_OK;
    uint8_t col_data = 0;
    uint8_t page_num = 0;
    uint8_t col_num = 0;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_OFF );
    for ( page_num = OLEDW2_POS_PAGE_MIN; page_num <= OLEDW2_POS_PAGE_MAX; page_num++ )
    {
        error_flag |= oledw2_set_column ( ctx, OLEDW2_POS_WIDTH_MIN );
        error_flag |= oledw2_set_page ( ctx, page_num );
        for ( col_num = OLEDW2_POS_WIDTH_MIN; col_num <= OLEDW2_POS_WIDTH_MAX; col_num++ )
        {
            error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
        }
    }
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_ON );
    return error_flag;
}

err_t oledw2_write_char ( oledw2_t *ctx, uint8_t page, uint8_t position, uint8_t data_in )
{
    err_t error_flag = OLEDW2_OK;
    uint16_t font_ch_start = 0;
    uint8_t num_req_pages = 0;
    uint8_t font_num_bytes = 0;
    uint8_t col_data = 0;
    uint8_t page_cnt = 0;
    uint8_t col_cnt = 0;
    num_req_pages = ( ctx->font.height / 8 ) + ( !!( ctx->font.height % 8 ) );
    font_num_bytes = ctx->font.width * num_req_pages;
    font_ch_start = ( data_in - OLEDW2_FONT_ASCII_OFFSET ) * font_num_bytes;
    if ( ( ( page + num_req_pages ) > ( OLEDW2_POS_PAGE_MAX + 1 ) ) || 
         ( data_in < 32 ) || ( data_in > 127 ) ||
         ( ctx->font.width > 8 ) || 
         ( ( position * ctx->font.width ) > ( OLEDW2_RES_WIDTH - ctx->font.width ) ) )
    {
        error_flag = OLEDW2_ERROR;
    }
    if ( OLEDW2_OK == error_flag )
    {
        if ( ctx->rotation )
        {
            for ( page_cnt = 0; page_cnt < num_req_pages; page_cnt++ )
            {
                error_flag |= oledw2_set_column ( ctx, position * ctx->font.width );
                error_flag |= oledw2_set_page ( ctx, OLEDW2_POS_PAGE_MAX - ( page + page_cnt ) );
                for ( col_cnt = 0; col_cnt < ctx->font.width; col_cnt++ )
                {
                    col_data = oledw2_rotate_bits ( ctx->font.font_buf[ font_ch_start + ( font_num_bytes - 1 ) - 
                                                                        ( page_cnt * ctx->font.width + col_cnt ) ] );
                    error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
                }
            }
        }
        else
        {  
            for ( page_cnt = 0; page_cnt < num_req_pages; page_cnt++ )
            {
                error_flag |= oledw2_set_column ( ctx, OLEDW2_RES_WIDTH - ctx->font.width - position * ctx->font.width );
                error_flag |= oledw2_set_page ( ctx, page + num_req_pages - 1 - page_cnt );
                for ( col_cnt = 0; col_cnt < ctx->font.width; col_cnt++ )
                {
                    col_data = ctx->font.font_buf[ font_ch_start + page_cnt * ctx->font.width + col_cnt ];
                    error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
                }
            }
        }
    }
    return error_flag;
}

err_t oledw2_write_string ( oledw2_t *ctx, uint8_t page, uint8_t position, uint8_t *data_in )
{
    err_t error_flag = OLEDW2_OK;
    uint8_t data_len = strlen ( ( char * ) data_in );
    uint16_t char_cnt = 0;
    for ( char_cnt = 0; char_cnt < data_len; char_cnt++ )
    {
        error_flag |= oledw2_write_char ( ctx, page, position + char_cnt, data_in[ char_cnt ] );
    }
    return error_flag;
}

err_t oledw2_draw_picture ( oledw2_t *ctx, const uint8_t *image )
{
    err_t error_flag = OLEDW2_OK;
    uint8_t col_data = 0;
    uint8_t page_num = 0;
    uint8_t col_num = 0;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_OFF );
    for ( page_num = OLEDW2_POS_PAGE_MIN; page_num <= OLEDW2_POS_PAGE_MAX; page_num++ )
    {
        if ( ctx->rotation )
        {
            error_flag |= oledw2_set_page ( ctx, OLEDW2_POS_PAGE_MAX - page_num );
            for ( col_num = OLEDW2_POS_WIDTH_MIN; col_num <= OLEDW2_POS_WIDTH_MAX; col_num++ )
            {
                col_data = oledw2_rotate_bits ( image[ page_num * OLEDW2_RES_WIDTH + col_num ] );
                error_flag |= oledw2_set_column ( ctx, OLEDW2_POS_WIDTH_MAX - col_num );
                error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
            }
        }
        else
        {
            error_flag |= oledw2_set_column ( ctx, OLEDW2_POS_WIDTH_MIN );
            error_flag |= oledw2_set_page ( ctx, page_num );
            for ( col_num = OLEDW2_POS_WIDTH_MIN; col_num <= OLEDW2_POS_WIDTH_MAX; col_num++ )
            {
                col_data = image[ page_num * OLEDW2_RES_WIDTH + col_num ];
                error_flag |= oledw2_write_data ( ctx, &col_data, 1 );
            }
        }
    }
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_DISPLAY_ON );
    return error_flag;
}

err_t oledw2_set_contrast ( oledw2_t *ctx, uint8_t value )
{
    err_t error_flag = OLEDW2_OK;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_CONTRAST );
    error_flag |= oledw2_write_cmd ( ctx, value );
    return error_flag;
}

err_t oledw2_scroll_right ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames )
{
    err_t error_flag = OLEDW2_OK;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_RIGHT_HORIZONTAL_SCROLL );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, start_page );
    error_flag |= oledw2_write_cmd ( ctx, num_frames );
    error_flag |= oledw2_write_cmd ( ctx, end_page );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, ~DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_ACTIVATE_SCROLL );
    return error_flag;
}

err_t oledw2_scroll_left ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames )
{
    err_t error_flag = OLEDW2_OK;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_LEFT_HORIZONTAL_SCROLL );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, start_page );
    error_flag |= oledw2_write_cmd ( ctx, num_frames );
    error_flag |= oledw2_write_cmd ( ctx, end_page );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, ~DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_ACTIVATE_SCROLL );
    return error_flag;
}

err_t oledw2_scroll_diag_right ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames, uint8_t vert_offset )
{
    err_t error_flag = OLEDW2_OK;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_VERTICAL_SCROLL_AREA );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_HEIGHT_MIN );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_HEIGHT_MAX );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, start_page );
    error_flag |= oledw2_write_cmd ( ctx, num_frames );
    error_flag |= oledw2_write_cmd ( ctx, end_page );
    error_flag |= oledw2_write_cmd ( ctx, vert_offset );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_ACTIVATE_SCROLL );
    return error_flag;
}

err_t oledw2_scroll_diag_left ( oledw2_t *ctx, uint8_t start_page, uint8_t end_page, uint8_t num_frames, uint8_t vert_offset )
{
    err_t error_flag = OLEDW2_OK;
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_SET_VERTICAL_SCROLL_AREA );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_HEIGHT_MIN );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_POS_HEIGHT_MAX );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL );
    error_flag |= oledw2_write_cmd ( ctx, DUMMY );
    error_flag |= oledw2_write_cmd ( ctx, start_page );
    error_flag |= oledw2_write_cmd ( ctx, num_frames );
    error_flag |= oledw2_write_cmd ( ctx, end_page );
    error_flag |= oledw2_write_cmd ( ctx, vert_offset );
    error_flag |= oledw2_write_cmd ( ctx, OLEDW2_CMD_ACTIVATE_SCROLL );
    return error_flag;
}

err_t oledw2_stop_scroll ( oledw2_t *ctx )
{
    return oledw2_write_cmd ( ctx, OLEDW2_CMD_DEACTIVATE_SCROLL );
}

static uint8_t oledw2_rotate_bits ( uint8_t in_byte )
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

// ------------------------------------------------------------------------- END
