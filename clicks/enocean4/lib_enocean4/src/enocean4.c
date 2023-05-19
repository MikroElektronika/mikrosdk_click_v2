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

#include "enocean4.h"
#include "string.h"

static uint8_t u8crc8table[ 256 ] = {

    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15,
    0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65,
    0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5,
    0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85,
    0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2,
    0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2,
    0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32,
    0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42,
    0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c,
    0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec,
    0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c,
    0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c,
    0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b,
    0x76, 0x71, 0x78, 0x7f, 0x6A, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b,
    0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb,
    0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8D, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb,
    0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t proccrc8 ( uint8_t u8crc, uint8_t u8data );

static uint8_t crc8_calc ( uint8_t *data_b, uint16_t size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void enocean4_cfg_setup ( enocean4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

ENOCEAN4_RETVAL enocean4_init ( enocean4_t *ctx, enocean4_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    digital_out_high( &ctx->rst );
    ctx->response_ready = ENOCEAN4_RESPONSE_NOT_READY;

    return ENOCEAN4_OK;
}

void enocean4_set_rst_pin ( enocean4_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void enocean4_generic_write ( enocean4_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t enocean4_generic_read ( enocean4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void enocean4_response_handler_set ( enocean4_t *ctx, void ( *handler )( enocean4_packet_t*, uint8_t* ) )
{
    ctx->driver_hdl = handler;
}

void enocean4_uart_isr( enocean4_t *ctx )
{
    static uint16_t rx_idx = 0;
    static uint16_t rx_size_cnt = 0;
    static uint8_t rx_size_check = 1;

    if ( enocean4_generic_read( ctx, &ctx->rx_dat[ rx_idx ], 1 ) <= 0 )
    {
        return;
    }
    
    if ( rx_size_check == 1 )
    {
        if ( ( rx_idx == 1 ) && ( ctx->rx_dat[ rx_idx ] == ENOCEAN4_SYNC_BYTE ) )
        {
            return;
        }
        else if ( rx_idx == 1 )
        {
            rx_size_cnt = ctx->rx_dat[ rx_idx ];
            rx_size_cnt <<= 8;
        }
        else if ( rx_idx == 2 )
        {
            rx_size_cnt |= ctx->rx_dat[ rx_idx ];
        }
        else if ( rx_idx == 3 )
        {
            rx_size_cnt += ctx->rx_dat[ rx_idx ];
        }
    }

    if ( rx_size_cnt > ENOCEAN4_MAX_BUFF_SIZE )
    {
        if ( ( rx_idx == 261 ) && ( rx_size_check == 1 ) )
        {
            ctx->response_ready = ENOCEAN4_RESPONSE_READY;
            rx_size_cnt -= ENOCEAN4_MAX_BUFF_SIZE;
            rx_idx = 0;
            rx_size_check = 0;

            return;
        }
        if ( ( rx_idx == 255 ) && ( rx_size_check == 0 ) )
        {
            ctx->response_ready = ENOCEAN4_RESPONSE_READY;
            rx_size_cnt -= ENOCEAN4_MAX_BUFF_SIZE;
            rx_idx = 0;

            return;
        }
    }
    else
    {
        if ( rx_size_check == 0 )
        {
            if ( rx_idx == rx_size_cnt )
            {
                ctx->response_ready = ENOCEAN4_RESPONSE_READY;
                rx_size_cnt = 0;
                rx_size_check = 1;
                rx_idx = 0;

                return;
            }
        }
        else
        {
            if ( ( rx_idx == rx_size_cnt + 6 ) && ( rx_idx > 3 ) )
            {
                ctx->response_ready = ENOCEAN4_RESPONSE_READY;
                rx_size_cnt = 0;
                rx_idx = 0;

                return;
            }
        }
    }

    rx_idx++;
}

uint8_t enocean4_process ( enocean4_t *ctx )
{
    static enocean4_packet_t  resp;
    static uint8_t rx_buff_tmp[ 4 ];
    static uint16_t rx_cnt;
    static uint16_t rx_max;
    static uint8_t rx_size_cnt;
    static uint8_t first_check = 1;
    static uint8_t crc_check_en;
    uint8_t crc_byte_rd;
    uint8_t crc_byte_calc;

    if ( first_check == 1 )
    {
        if ( ctx->rx_dat[ 0 ] != ENOCEAN4_SYNC_BYTE )
        {
            return ENOCEAN4_SYNC_BYTE_ERROR;
        }

        resp.data_length =ctx->rx_dat[ 1 ];
        resp.data_length <<= 8;
        rx_buff_tmp[ 0 ] = ctx->rx_dat[ 1 ];

        resp.data_length |= ctx->rx_dat[ 2 ];
        rx_buff_tmp[ 1 ] = ctx->rx_dat[ 2 ];

        resp.opt_length = ctx->rx_dat[ 3 ];
        rx_buff_tmp[ 2 ] = ctx->rx_dat[ 3 ];

        resp.packet_type = ctx->rx_dat[ 4 ];
        rx_buff_tmp[ 3 ] = ctx->rx_dat[ 4 ];

        crc_byte_rd = ctx->rx_dat[ 5 ];
        crc_byte_calc = crc8_calc( rx_buff_tmp, ENOCEAN4_HEADER_SIZE );

        if ( crc_byte_calc != crc_byte_rd )
        {
            return ENOCEAN4_CRC8H_ERROR;
        }

        rx_max = resp.data_length + resp.opt_length;
        crc_check_en = 1;
    }

    if ( rx_max > ENOCEAN4_MAX_BUFF_SIZE )
    {
        resp.data_length = ENOCEAN4_MAX_BUFF_SIZE;
        rx_max -= ENOCEAN4_MAX_BUFF_SIZE;
        rx_size_cnt = 1;
        crc_check_en = 0;
    }
    else
    {
        resp.data_length = rx_max;
        rx_size_cnt = 0;
    }

    for ( rx_cnt = 0; rx_cnt < resp.data_length; rx_cnt++ )
    {
        if ( first_check == 1 )
        {
            resp.data_buff[ rx_cnt ] = ctx->rx_dat[ rx_cnt + 6 ];
        }
        else
        {
            resp.data_buff[ rx_cnt ] = ctx->rx_dat[ rx_cnt ];
        }
    }

    if ( crc_check_en )
    {
        crc_byte_rd = ctx->rx_dat[ resp.data_length + 6 ];
        crc_byte_calc = crc8_calc( resp.data_buff, resp.data_length );

        if ( crc_byte_calc != crc_byte_rd )
        {
            return ENOCEAN4_CRC8D_ERROR;
        }
    }

    if ( rx_size_cnt == 0 )
    {
        first_check = 1;
    }
    else
    {
        first_check = 0;
    }

    ctx->driver_hdl( &resp, &rx_size_cnt );

    return ENOCEAN4_OK;
}

uint8_t enocean4_response_ready ( enocean4_t *ctx )
{
    if ( ctx->response_ready )
    {
        ctx->response_ready = ENOCEAN4_RESPONSE_NOT_READY;

        return ENOCEAN4_RESPONSE_READY;
    }

    return ENOCEAN4_RESPONSE_NOT_READY;
}

void enocean4_reset ( enocean4_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1sec( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

uint8_t enocean4_send_packet ( enocean4_t *ctx, enocean4_packet_t *packet )
{
    uint8_t tx_data[ 5 ];
    uint8_t tmp;
    
    if ( ( ( packet->data_length + packet->opt_length ) == ENOCEAN4_BUFF_EMPTY ) || 
         ( ( packet->data_length + packet->opt_length ) > ENOCEAN4_MAX_BUFF_SIZE ) )
    {
        return ENOCEAN4_INVALID_PACKET_SIZE;
    }

    tx_data[ 0 ] = packet->data_length >> 8;
    tx_data[ 1 ] = packet->data_length;
    tx_data[ 2 ] = packet->opt_length;
    tx_data[ 3 ] = packet->packet_type;
    tx_data[ 4 ] = crc8_calc( tx_data, 4 );

    tmp = ENOCEAN4_SYNC_BYTE;
    enocean4_generic_write( ctx, &tmp, 1 );

    enocean4_generic_write( ctx, &tx_data[ 0 ], 5 );

    enocean4_generic_write( ctx, &packet->data_buff[ 0 ], packet->data_length + packet->opt_length );

    tmp = crc8_calc( packet->data_buff, packet->data_length + packet->opt_length );
    enocean4_generic_write( ctx, &tmp, 1 );

    return ENOCEAN4_OK;
}
 
// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t proccrc8 ( uint8_t u8crc, uint8_t u8data )
{
    return u8crc8table[ u8crc ^ u8data ];
}

static uint8_t crc8_calc ( uint8_t *data_b, uint16_t size )
{
    uint8_t crc8;
    uint16_t i;

    crc8 = 0;

    for ( i = 0; i < size; i++ )
    {
        crc8 = proccrc8( crc8, data_b[ i ] );
    }

    return crc8;
}
// ------------------------------------------------------------------------- END

