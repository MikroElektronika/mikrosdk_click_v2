/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
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
 * @file printer.c
 * @brief Printer Click Driver.
 */

#include "printer.h"

void printer_cfg_setup ( printer_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t printer_init ( printer_t *ctx, printer_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;

    // Default config
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy = 0;
    uart_read( &ctx->uart, &dummy, 1 );

    Delay_1sec ( );
    Delay_1sec ( );

    return UART_SUCCESS;
}

err_t printer_default_cfg ( printer_t *ctx ) 
{
    err_t error_flag = PRINTER_OK;
    error_flag |= printer_set_com_mode ( ctx, PRINTER_COM_BAUD_RATE_115200, PRINTER_COM_FLOW_CTRL_OFF );
    Delay_1sec ( );
    error_flag |= printer_get_status ( ctx );
    error_flag |= printer_get_fw_info ( ctx );
    error_flag |= printer_set_printer_head ( ctx, PRINTER_HEAD_MM58_LTP02_245_13 );
    Delay_1sec ( );
    return error_flag;
}

err_t printer_generic_write ( printer_t *ctx, uint8_t *data_in, uint32_t len )
{
    uint32_t timeout_cnt = 0;
    uint32_t data_index = 0;
    // Wait device ready
    while ( printer_get_rts_pin ( ctx ) )
    {
        if ( ++timeout_cnt > PRINTER_READY_TIMEOUT )
        {
            return PRINTER_ERROR;
        }
        Delay_1ms ( );
    }
    for ( data_index = 0; data_index < len; data_index += PRINTER_TX_DRV_BUFFER_SIZE )
    {
        if ( ( len - data_index ) >= PRINTER_TX_DRV_BUFFER_SIZE )
        {
            if ( PRINTER_ERROR == uart_write( &ctx->uart, &data_in[ data_index ], PRINTER_TX_DRV_BUFFER_SIZE ) )
            {
                return PRINTER_ERROR;
            }
            Delay_1ms ( );
        }
        else
        {
            if ( PRINTER_ERROR == uart_write( &ctx->uart, &data_in[ data_index ], ( len - data_index ) ) )
            {
                return PRINTER_ERROR;
            }
        }
    }
    return PRINTER_OK;
}

err_t printer_generic_read ( printer_t *ctx, uint8_t *data_out, uint8_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

uint8_t printer_get_rts_pin ( printer_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

err_t printer_get_status ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_DLE;
    data_buf[ 1 ] = PRINTER_CMD_EOT;
    uart_clear ( &ctx->uart );
    memset ( ctx->status, 0, sizeof ( ctx->status ) );
    err_t error_flag = printer_generic_write ( ctx, data_buf, 2 );
    if ( PRINTER_ERROR != error_flag )
    {
        Delay_10ms ( );
        if ( printer_generic_read ( ctx, ctx->status, sizeof ( ctx->status ) ) <= 0 )
        {
            error_flag = PRINTER_ERROR;
        }
    }
    return error_flag;
}

err_t printer_get_fw_info ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_DLE;
    data_buf[ 1 ] = PRINTER_CMD_ENQ;
    uart_clear ( &ctx->uart );
    memset ( ctx->fw_info, 0, sizeof ( ctx->fw_info ) );
    err_t error_flag = printer_generic_write ( ctx, data_buf, 2 );
    if ( PRINTER_ERROR != error_flag )
    {
        Delay_10ms ( );
        if ( printer_generic_read ( ctx, ctx->fw_info, sizeof ( ctx->fw_info ) ) <= 0 )
        {
            error_flag = PRINTER_ERROR;
        }
    }
    return error_flag;
}

err_t printer_set_com_mode ( printer_t *ctx, uint8_t baud_rate, uint8_t flow_control )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( baud_rate > PRINTER_COM_BAUD_RATE_115200 ) || 
         ( flow_control > PRINTER_COM_FLOW_CTRL_HW ) )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = '(';
    data_buf[ 2 ] = baud_rate;
    data_buf[ 3 ] = flow_control;
    return printer_generic_write ( ctx, data_buf, 4 );
}

err_t printer_set_printer_head ( printer_t *ctx, uint8_t head_index )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( head_index > PRINTER_HEAD_MM58_LTP02_245_C1 )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'Z';
    data_buf[ 2 ] = head_index;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_soft_init ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = '@';
    return printer_generic_write ( ctx, data_buf, 2 );
}

err_t printer_print_lf ( printer_t *ctx )
{
    uint8_t data_buf[ 1 ] = { PRINTER_CMD_LF };
    return printer_generic_write ( ctx, data_buf, 1 );
}

err_t printer_print_cr ( printer_t *ctx )
{
    uint8_t data_buf[ 1 ] = { PRINTER_CMD_CR };
    return printer_generic_write ( ctx, data_buf, 1 );
}

err_t printer_print_string ( printer_t *ctx, char *data_in )
{
    return printer_generic_write ( ctx, ( uint8_t * ) data_in, strlen ( data_in ) );
}

err_t printer_print_string_lf ( printer_t *ctx, char *data_in )
{
    err_t error_flag = printer_generic_write ( ctx, ( uint8_t * ) data_in, strlen ( data_in ) );
    error_flag |= printer_print_lf ( ctx );
    return error_flag;
}

err_t printer_print_dots ( printer_t *ctx, uint8_t num_dots )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'J';
    data_buf[ 2 ] = num_dots;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_print_lines ( printer_t *ctx, uint8_t num_lines )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'd';
    data_buf[ 2 ] = num_lines;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_font_type ( printer_t *ctx, uint8_t font_type )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = '!';
    data_buf[ 2 ] = font_type;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_alignment ( printer_t *ctx, uint8_t align )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( align > PRINTER_ALIGN_RIGHT )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'a';
    data_buf[ 2 ] = align;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_line_spacing ( printer_t *ctx, uint8_t num_dots )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = '3';
    data_buf[ 2 ] = num_dots;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_default_line_spacing ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = '2';
    return printer_generic_write ( ctx, data_buf, 2 );
}

err_t printer_set_horizontal_tab ( printer_t *ctx, uint8_t *col_pos, uint8_t num_tabs )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'D';
    data_buf[ 2 ] = 0;
    err_t error_flag = printer_generic_write ( ctx, data_buf, 2 );
    error_flag |= printer_generic_write ( ctx, col_pos, num_tabs );
    error_flag |= printer_generic_write ( ctx, &data_buf[ 2 ], 1 );
    return error_flag;
}

err_t printer_horizontal_tab ( printer_t *ctx )
{
    uint8_t data_buf[ 1 ] = { PRINTER_CMD_HT };
    return printer_generic_write ( ctx, data_buf, 1 );
}

err_t printer_print_picture ( printer_t *ctx, uint8_t *pic_buf, uint16_t h_size, uint16_t v_size )
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint32_t pic_size = ( uint32_t ) h_size * v_size;
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'v';
    data_buf[ 2 ] = '0';
    data_buf[ 3 ] = PRINTER_PICTURE_TYPE_NORMAL;
    data_buf[ 4 ] = ( uint8_t ) ( h_size & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( h_size >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( v_size & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( v_size >> 8 ) & 0xFF );
    err_t error_flag = printer_generic_write ( ctx, data_buf, 8 );
    if ( NULL == pic_buf )
    {
        data_buf[ 0 ] = 0;
        for ( uint32_t cnt = 0; cnt < pic_size; cnt++ )
        {
            error_flag |= printer_generic_write ( ctx, data_buf, 1 );
        }
    }
    else
    {
        error_flag |= printer_generic_write ( ctx, pic_buf, pic_size );
    }
    return error_flag;
}

err_t printer_set_left_margin ( printer_t *ctx, uint8_t num_dots )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'l';
    data_buf[ 2 ] = num_dots;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_right_margin ( printer_t *ctx, uint8_t num_dots )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'Q';
    data_buf[ 2 ] = num_dots;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_abs_print_pos ( printer_t *ctx, uint16_t num_dots )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = '$';
    data_buf[ 2 ] = ( uint8_t ) ( num_dots & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( num_dots >> 8 ) & 0xFF );
    return printer_generic_write ( ctx, data_buf, 4 );
}

err_t printer_set_font_grayscale ( printer_t *ctx, uint8_t grayscale )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( grayscale > PRINTER_GRAYSCALE_8 )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'm';
    data_buf[ 2 ] = grayscale;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_db_mode ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_FS;
    data_buf[ 1 ] = '&';
    return printer_generic_write ( ctx, data_buf, 2 );
}

err_t printer_cancel_db_mode ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_FS;
    data_buf[ 1 ] = '.';
    return printer_generic_write ( ctx, data_buf, 2 );
}

err_t printer_set_font_size ( printer_t *ctx, uint8_t size )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( ( size != PRINTER_FONT_SIZE_SMALL ) && ( size != PRINTER_FONT_SIZE_LARGE ) )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_ESC;
    data_buf[ 1 ] = 'M';
    data_buf[ 2 ] = size;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_hide_barcode_text ( printer_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'H';
    data_buf[ 2 ] = 0;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_show_barcode_text ( printer_t *ctx )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'H';
    data_buf[ 2 ] = 1;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_barcode_height ( printer_t *ctx, uint8_t height )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'h';
    data_buf[ 2 ] = height;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_set_barcode_width ( printer_t *ctx, uint8_t width )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'w';
    data_buf[ 2 ] = width;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_print_barcode ( printer_t *ctx, uint8_t barcode_sys, uint8_t *barcode, uint8_t barcode_len )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( barcode_sys > PRINTER_BARCODE_SYS_CODE128 )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'k';
    data_buf[ 2 ] = barcode_sys + 'A';
    data_buf[ 3 ] = barcode_len;
    err_t error_flag = printer_generic_write ( ctx, data_buf, 4 );
    error_flag |= printer_generic_write ( ctx, barcode, barcode_len );
    return error_flag;
}

err_t printer_clear_print_buffer ( printer_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_DLE;
    data_buf[ 1 ] = PRINTER_CMD_DC4;
    return printer_generic_write ( ctx, data_buf, 2 );
}

err_t printer_set_printer_cb ( printer_t *ctx, uint8_t callback )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = 'a';
    data_buf[ 2 ] = callback;
    return printer_generic_write ( ctx, data_buf, 3 );
}

err_t printer_download_nv_bitmap ( printer_t *ctx, uint8_t location, uint8_t h_size, uint8_t v_size, uint8_t *bitmap )
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint32_t bm_size = ( uint32_t ) h_size * v_size;
    if ( ( location < PRINTER_BITMAP_LOCATION_1 ) || 
         ( location > PRINTER_BITMAP_LOCATION_4 ) )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_FS;
    data_buf[ 1 ] = 'q';
    data_buf[ 2 ] = location;
    data_buf[ 3 ] = PRINTER_BITMAP_ALIGN;
    data_buf[ 4 ] = ( uint8_t ) ( h_size & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( ( h_size >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( v_size & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( ( v_size >> 8 ) & 0xFF );
    err_t error_flag = printer_generic_write ( ctx, data_buf, 8 );
    if ( NULL == bitmap )
    {
        data_buf[ 0 ] = 0;
        for ( uint32_t cnt = 0; cnt < bm_size; cnt++ )
        {
            error_flag |= printer_generic_write ( ctx, data_buf, 1 );
        }
    }
    else
    {
        error_flag |= printer_generic_write ( ctx, bitmap, bm_size );
    }
    return error_flag;
}

err_t printer_print_nv_bitmap ( printer_t *ctx, uint8_t location )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( location < PRINTER_BITMAP_LOCATION_1 ) || 
         ( location > PRINTER_BITMAP_LOCATION_4 ) )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_FS;
    data_buf[ 1 ] = 'p';
    data_buf[ 2 ] = location;
    data_buf[ 3 ] = PRINTER_BITMAP_MODE_NORMAL;
    return printer_generic_write ( ctx, data_buf, 4 );
}

err_t printer_set_qr_size ( printer_t *ctx, uint8_t size )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( size > PRINTER_QR_SIZE_125_177 )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = '(';
    data_buf[ 2 ] = 'k';
    data_buf[ 3 ] = 3; // LSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 4 ] = 0; // MSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 5 ] = 0x31; // fixed value
    data_buf[ 6 ] = 0x43; // fixed value
    data_buf[ 7 ] = size;
    return printer_generic_write ( ctx, data_buf, 8 );
}

err_t printer_set_qr_error_corr ( printer_t *ctx, uint8_t corr_level )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( corr_level > PRINTER_QR_ERROR_30_PCT )
    {
        return PRINTER_ERROR;
    }
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = '(';
    data_buf[ 2 ] = 'k';
    data_buf[ 3 ] = 3; // LSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 4 ] = 0; // MSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 5 ] = 0x31; // fixed value
    data_buf[ 6 ] = 0x45; // fixed value
    data_buf[ 7 ] = corr_level;
    return printer_generic_write ( ctx, data_buf, 8 );
}

err_t printer_transfer_qr_code ( printer_t *ctx, uint8_t *qr_code, uint16_t code_len )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = '(';
    data_buf[ 2 ] = 'k';
    data_buf[ 3 ] = ( uint8_t ) ( ( code_len + 3 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( ( ( code_len + 3 ) >> 8 ) & 0xFF );
    data_buf[ 5 ] = 0x31; // fixed value
    data_buf[ 6 ] = 0x50; // fixed value
    data_buf[ 7 ] = 0x30; // fixed value
    err_t error_flag = printer_generic_write ( ctx, data_buf, 8 );
    if ( NULL == qr_code )
    {
        data_buf[ 0 ] = 0;
        for ( uint32_t cnt = 0; cnt < code_len; cnt++ )
        {
            error_flag |= printer_generic_write ( ctx, data_buf, 1 );
        }
    }
    else
    {
        error_flag |= printer_generic_write ( ctx, qr_code, code_len );
    }
    return error_flag;
}

err_t printer_print_qr_code ( printer_t *ctx )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = PRINTER_CMD_GS;
    data_buf[ 1 ] = '(';
    data_buf[ 2 ] = 'k';
    data_buf[ 3 ] = 3; // LSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 4 ] = 0; // MSB of num bytes starting from data_buf[ 5 ]
    data_buf[ 5 ] = 0x31; // fixed value
    data_buf[ 6 ] = 0x51; // fixed value
    data_buf[ 7 ] = 0x30; // fixed value
    return printer_generic_write ( ctx, data_buf, 8 );
}

// ------------------------------------------------------------------------- END
