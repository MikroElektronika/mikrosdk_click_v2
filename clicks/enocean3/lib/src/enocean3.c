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

#include "enocean3.h"
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

static void check_rx_max_size( uint16_t rx_max, uint16_t *rx_max_calc, uint16_t *rx_size_calc );
static uint8_t proccrc8( uint8_t u8crc, uint8_t u8data );
static uint8_t crc8_calc( uint8_t *data_, uint16_t size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void enocean3_cfg_setup ( enocean3_cfg_t *cfg )
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

ENOCEAN3_RETVAL enocean3_init ( enocean3_t *ctx, enocean3_cfg_t *cfg )
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
    ctx->response_ready = ENOCEAN3_RESPONSE_NOT_READY;

    return ENOCEAN3_OK;
}

void enocean3_set_rst_pin ( enocean3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void enocean3_generic_write ( enocean3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t enocean3_generic_read ( enocean3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void enocean3_uart_isr ( enocean3_t *ctx )
{
    static enocean3_packet_t  resp;
    static uint8_t rx_buff_tmp[ 4 ];
    static uint16_t rx_cnt;
    static uint16_t rx_idx = 0;
    static uint16_t rx_max_tmp;
    static uint16_t rx_size_cnt = 0;
    static uint16_t rx_size_cnt_prev = 0;
    static uint8_t first_check = 1;
    static uint8_t crc_check_en = 1;
    uint8_t crc_byte_rd;
    uint8_t crc_byte_calc;
    uint8_t rx_byte;
    
    if ( enocean3_generic_read( ctx, &rx_byte, 1 ) <= 0 )
    {
        return;
    }
    
    if ( first_check )
    {
        if ( ( rx_idx == 0 ) && ( rx_byte == ENOCEAN3_SYNC_BYTE ) && ( rx_size_cnt == 0 ) )
        {
            first_check = 0;
            
            return;
        }
    }

    if ( ( rx_idx == 0 ) && ( rx_byte != ENOCEAN3_SYNC_BYTE ) && ( rx_size_cnt == 0 ) )
    {
        rx_idx = 0;
        rx_cnt = 0;
        resp.data_length = 0;

        return;
    }
    else if ( ( rx_idx == 1 ) && ( rx_size_cnt == 0 ) )
    {
        resp.data_length = rx_byte;
        resp.data_length <<= 8;
        rx_buff_tmp[ 0 ] = rx_byte;
    }
    else if ( ( rx_idx == 2 ) && ( rx_size_cnt == 0 ) )
    {
        resp.data_length |= rx_byte;
        rx_buff_tmp[ 1 ] = rx_byte;
    }
    else if ( ( rx_idx == 3 ) && ( rx_size_cnt == 0 ) )
    {
        resp.opt_length = rx_byte;
        rx_buff_tmp[ 2 ] = rx_byte;
    }
    else if ( ( rx_idx == 4 ) && ( rx_size_cnt == 0 ) )
    {
        resp.packet_type = rx_byte;
        rx_buff_tmp[ 3 ] = rx_byte;
    }
    else if ( ( rx_idx == 5 ) && ( rx_size_cnt == 0 ) )
    {
        crc_byte_rd = rx_byte;
        crc_byte_calc = crc8_calc( rx_buff_tmp, ENOCEAN3_HEADER_SIZE );
        
        if ( crc_byte_calc != crc_byte_rd )
        {
            rx_idx = 0;
            rx_cnt = 0;
            resp.data_length = 0;

            return;
        }
        
        check_rx_max_size( resp.data_length + resp.opt_length, &rx_max_tmp, &rx_size_cnt );
        rx_size_cnt_prev = rx_size_cnt;
        rx_cnt = 0;
        crc_check_en = 1;
    }
    else if ( ( rx_idx > 5 ) || ( rx_size_cnt != rx_size_cnt_prev ) )
    {
        if ( rx_size_cnt > 1 )
        {
            resp.data_length = ENOCEAN3_MAX_BUFF_SIZE;
        }
        else if ( rx_size_cnt == 1 )
        {
            resp.data_length = rx_max_tmp;
        }

        if ( rx_cnt < resp.data_length )
        {
            resp.data_buff[ rx_cnt ] = rx_byte;

            if ( rx_cnt == ( resp.data_length - 1 ) )
            {
                ctx->driver_hdl( &resp, &rx_size_cnt );

                if ( rx_size_cnt != 1 )
                {
                    rx_idx = 0;
                    rx_cnt = 0;
                    resp.data_length = 0;
                    rx_size_cnt--;
                    crc_check_en = 0;
                    ctx->response_ready = ENOCEAN3_RESPONSE_READY;

                    return;
                }
            }
        }
        else
        {
            if ( crc_check_en )
            {
                crc_byte_rd = rx_byte;
                crc_byte_calc = crc8_calc( resp.data_buff, resp.data_length );
            
                if ( crc_byte_calc == crc_byte_rd )
                {
                    ctx->response_ready = ENOCEAN3_RESPONSE_READY;
                }
            }
            else
            {
                ctx->response_ready = ENOCEAN3_RESPONSE_READY;
            }
        
            rx_idx = 0;
            rx_cnt = 0;
            resp.data_length = 0;
            rx_size_cnt_prev = 0;
            rx_size_cnt--;

            return;
        }

        rx_cnt++;
    }
    
    rx_idx++;
}

uint8_t enocean3_response_ready ( enocean3_t *ctx )
{
    if ( ctx->response_ready )
    {
        ctx->response_ready = ENOCEAN3_RESPONSE_NOT_READY;

        return ENOCEAN3_RESPONSE_READY;
    }

    return ENOCEAN3_RESPONSE_NOT_READY;
}

uint8_t enocean3_send_packet ( enocean3_t *ctx, enocean3_packet_t *packet )
{
    uint8_t tx_data[ 5 ];
    uint16_t tx_cnt;
    uint8_t tmp;
    tmp = ENOCEAN3_SYNC_BYTE;
    
    if ( ( ( packet->data_length + packet->opt_length ) == ENOCEAN3_BUFF_EMPTY ) || 
         ( ( packet->data_length + packet->opt_length ) > ENOCEAN3_MAX_BUFF_SIZE ) )
    {
        return ENOCEAN3_INVALID_PACKET_SIZE;
    }

    tx_data[ 0 ] = packet->data_length >> 8;
    tx_data[ 1 ] = packet->data_length;
    tx_data[ 2 ] = packet->opt_length;
    tx_data[ 3 ] = packet->packet_type;
    tx_data[ 4 ] = crc8_calc( tx_data, 4 );
    
    enocean3_generic_write( ctx, &tmp, 1 );
    
    for (tx_cnt = 0; tx_cnt < 5; tx_cnt++)
    {
        enocean3_generic_write( ctx, &tx_data[ tx_cnt ], 1 );
    }
    
    for (tx_cnt = 0; tx_cnt < (packet->data_length + packet->opt_length); tx_cnt++)
    {
        enocean3_generic_write( ctx, &packet->data_buff[ tx_cnt ], 1 );
    }
    
    tx_data[ 0 ] = crc8_calc( packet->data_buff, packet->data_length + packet->opt_length );
    
    enocean3_generic_write( ctx, &tx_data[ 0 ], 1 );
    
    return ENOCEAN3_OK;
}   

void enocean3_response_handler_set ( enocean3_t *ctx, enocean3_hdl_t handler )
{
    ctx->driver_hdl = handler;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void check_rx_max_size ( uint16_t rx_max, uint16_t *rx_max_calc, uint16_t *rx_size_calc )
{
    int32_t rx_size;
    uint16_t rx_max_tmp;
    uint16_t rx_size_cnt;

    rx_max_tmp = rx_max;
    rx_size_cnt = 1;
    rx_size = ( int32_t )( ENOCEAN3_MAX_BUFF_SIZE - rx_max_tmp );

    while ( rx_size < 0 )
    {
        rx_max_tmp -= ENOCEAN3_MAX_BUFF_SIZE;
        rx_size_cnt++;
        rx_size = ( int32_t )( ENOCEAN3_MAX_BUFF_SIZE - rx_max_tmp );
    }

    *rx_max_calc = rx_max_tmp;
    *rx_size_calc = rx_size_cnt;
}

static uint8_t proccrc8( uint8_t u8crc, uint8_t u8data )
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
        crc8 = proccrc8(  crc8, data_b[ i ] );
    }

    return crc8;
}

// ------------------------------------------------------------------------- END

