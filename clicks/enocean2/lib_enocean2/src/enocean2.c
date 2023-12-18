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

#include "enocean2.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

static uint8_t u8_crc8_table[ 256 ] = 
{
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

static void serialize_header ( enocean2_packet_t *packet, uint8_t *buffer );

static void deserialize_header ( enocean2_t *ctx, enocean2_packet_t *packet, uint8_t *buffer );

static uint32_t calc_packet_size ( enocean2_packet_t *packet );

static void inc_tail ( enocean2_ring_buffer_t *rb, uint16_t size );

static void fetch_rx_buffer ( enocean2_ring_buffer_t *rb, uint8_t *input_buffer, uint8_t size );

static uint8_t proccrc8 ( uint8_t u8_crc, uint8_t u8_data );

static uint8_t crc8 ( uint8_t *data_in, uint32_t size );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void enocean2_cfg_setup ( enocean2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

ENOCEAN2_RETVAL enocean2_init ( enocean2_t *ctx, enocean2_cfg_t *cfg )
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


    return ENOCEAN2_OK;
}

void enocean2_generic_write ( enocean2_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t enocean2_generic_read ( enocean2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void enocean2_init_rx_buff ( enocean2_t *ctx, enocean2_ring_buffer_t *rb, enocean2_rx_data_t *rx_str )
{
    rb->rx_buffer_begin = rx_str->rx_buffer;
    rb->rx_buffer_end = &rx_str->rx_buffer[ rx_str->rx_size - 1 ];
    rb->rx_capacity = rx_str->rx_size;

    memset( rx_str->rx_buffer, 0x00, rx_str->rx_size );

    rb->rx_head = rb->rx_buffer_begin;
    rb->rx_tail = rb->rx_buffer_begin;

    rb->rx_size = 0;
    ctx->state = STATE_SYNC;

    ctx->rx_packet.data_buffer = rx_str->data_buffer;
    ctx->rx_packet_capacity = rx_str->data_size;
}

void enocean2_set_callback_handler ( enocean2_t *ctx, enocean2_callback_t recieve )
{
    ctx->recieve_callback = recieve;
}

uint8_t enocean2_send ( enocean2_t *ctx, enocean2_packet_t *packet )
{
    uint8_t write_data;
    uint8_t header[ ENOCEAN2_HEADER_SIZE ];
    uint32_t packet_size;
    uint16_t i;

    packet_size = calc_packet_size( packet );

    if ( packet_size == 0 )
    {
        return ENOCEAN2_ERR_INVALID_SIZE;
    }

    serialize_header( packet, header );
    write_data = ENOCEAN2_SYNC_BYTE;
    enocean2_generic_write( ctx, &write_data, 1 );

    for ( i = 0; i < ENOCEAN2_HEADER_SIZE; i++ )
    {
       enocean2_generic_write( ctx, &header[ i ], 1 );
    }

    write_data = crc8( header, ENOCEAN2_HEADER_SIZE );
    enocean2_generic_write( ctx, &write_data, 1 );

    for ( i = 0; i < packet_size; i++ )
    {
       enocean2_generic_write( ctx, &packet->data_buffer[ i ], 1 );
    }

    write_data = crc8( packet->data_buffer, packet_size );
    enocean2_generic_write( ctx, &write_data, 1 );

    return ENOCEAN2_ERR_OK;
}

uint8_t enocean2_rx ( enocean2_ring_buffer_t *rb, uint8_t rx_data )
{
    if ( rb->rx_size == rb->rx_capacity )
    {
        return ENOCEAN2_ERR_BUFFER_FULL;
    }

    *( rb->rx_head++ ) = rx_data;
    rb->rx_size++;

    if ( rb->rx_head > rb->rx_buffer_end )
    {
        rb->rx_head = rb->rx_buffer_begin;
    }

    return ENOCEAN2_ERR_OK;
}

uint8_t enocean2_packet_recieve ( enocean2_t *ctx, enocean2_ring_buffer_t *rb )
{
    uint8_t crc8h;
    uint8_t sync_buffer[ ENOCEAN2_SYNC_SIZE ];

    if ( rb->rx_tail == rb->rx_head ) 
    {
        return ENOCEAN2_ERR_OK;
    }

    switch ( ctx->state )
    {
        case 1:

            if ( *rb->rx_tail == ENOCEAN2_SYNC_BYTE )
            {
                if ( rb->rx_size < ENOCEAN2_SYNC_SIZE )
                {
                    return ENOCEAN2_ERR_OK;
                }
                fetch_rx_buffer( rb, sync_buffer, ENOCEAN2_SYNC_SIZE );
                crc8h = crc8( &sync_buffer[ ENOCEAN2_HEADER_OFFSET ], ENOCEAN2_HEADER_SIZE );

                if ( sync_buffer[ ENOCEAN2_CRC8H_OFFSET ] == crc8h )
                {
                    deserialize_header( ctx, &ctx->rx_packet, &sync_buffer[ ENOCEAN2_HEADER_OFFSET ] );
                    ctx->rx_packet_size = calc_packet_size( &ctx->rx_packet );

                    if ( ctx->rx_packet_size > ctx->rx_packet_capacity )
                    {
                        inc_tail( rb, 1 );
                        return ENOCEAN2_ERR_NO_MEMORY;
                    }

                    if ( ctx->rx_packet_size != 0 )
                    {
                        inc_tail( rb, ENOCEAN2_SYNC_SIZE );
                        ctx->rx_data_cnt = 0;
                        ctx->state = STATE_DATA;

                        return ENOCEAN2_ERR_OK;
                    }
                }
            }
            inc_tail( rb, 1 );

        break;
        case 2:

            if ( ctx->rx_data_cnt < ctx->rx_packet_size )
            {
                ctx->rx_packet.data_buffer[ ctx->rx_data_cnt++ ] = *rb->rx_tail;
                inc_tail( rb, 1 );
            }
            else
            {
                ctx->state = STATE_FINISH;
            }

        break;
        case 3:

            if ( *rb->rx_tail == crc8( ctx->rx_packet.data_buffer, ctx->rx_packet_size ) )
            {
                ctx->recieve_callback( &ctx->rx_packet );
                inc_tail( rb, 1 );
            }

            ctx->state = STATE_SYNC;

        break;
        default:

        break;
    }
    
    return ENOCEAN2_ERR_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void serialize_header ( enocean2_packet_t *packet, uint8_t *buffer )
{
    buffer[ 0 ] = packet->data_length >> 8;
    buffer[ 1 ] = packet->data_length & 0x00FF;
    buffer[ 2 ] = packet->option_length;
    buffer[ 3 ] = packet->type;
}

static void deserialize_header ( enocean2_t *ctx, enocean2_packet_t *packet, uint8_t *buffer )
{
    ctx->rx_packet.data_length = ( ( ( uint16_t )( buffer[ 0 ] << 8 ) ) | ( uint16_t ) buffer[ 1 ] );
    ctx->rx_packet.option_length = buffer[ 2 ];
    ctx->rx_packet.type = buffer[ 3 ];
}

static uint32_t calc_packet_size ( enocean2_packet_t *packet )
{
    uint32_t size;

    size = packet->data_length;
    size += packet->option_length;

    return size;
}

static void inc_tail ( enocean2_ring_buffer_t *rb, uint16_t size )
{
    rb->rx_tail += size;
    rb->rx_size -= size;

    if ( rb->rx_tail > rb->rx_buffer_end )
    {
        rb->rx_tail = rb->rx_buffer_begin + ( rb->rx_tail - rb->rx_buffer_end - 1 );
    }
}

static void fetch_rx_buffer ( enocean2_ring_buffer_t *rb, uint8_t *input_buffer, uint8_t size )
{
    uint8_t *rx_tail;

    rx_tail = rb->rx_tail;

    while ( size-- )
    {
        *input_buffer++ = *rx_tail++;

        if ( rx_tail > rb->rx_buffer_end )
        {
            rx_tail = rb->rx_buffer_begin;
        }
    }
}

static uint8_t proc_crc8 ( uint8_t u8_crc, uint8_t u8_data )
{
   return u8_crc8_table[ u8_crc ^ u8_data ];
}

static uint8_t crc8 ( uint8_t *data_in, uint32_t size )
{
    uint8_t crc8;
    uint16_t i;

    crc8 = 0;

    for ( i = 0 ; i < size ; i++ )
    {
        crc8 = proc_crc8( crc8, data_in[ i ] );
    }
    return crc8;
}


// ------------------------------------------------------------------------- END

