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
 * @file enocean5.c
 * @brief EnOcean 5 Click Driver.
 */

#include "enocean5.h"

// CRC 8 table for ESP3 packet.
static uint8_t enocean5_crc8_table[ 256 ] =
{
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15,
	0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D,
	0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65,
	0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D,
	0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5,
	0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD,
	0x90, 0x97, 0x9E, 0x99, 0x8C, 0x8B, 0x82, 0x85,
	0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD,
	0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2,
	0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA,
	0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2,
	0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A,
	0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C, 0x35, 0x32,
	0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A,
	0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42,
	0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A,
	0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C,
	0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4,
	0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC,
	0xC1, 0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4,
	0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C,
	0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44,
	0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C,
	0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34,
	0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B,
	0x76, 0x71, 0x78, 0x7F, 0x6A, 0x6D, 0x64, 0x63,
	0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B,
	0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13,
	0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB,
	0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83,
	0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB,
	0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4, 0xF3
};

/**
 * @brief EnOcean 5 calculate CRC8 function.
 * @details This function calculates CRC8 from input data buffer.
 * @param[in] crc_init : CRC init value.
 * @param[in] data_in : Data buffer.
 * @param[in] len : Number of data bytes.
 * @return Calculated CRC byte.
 * @note None.
 */
static uint8_t enocean5_calculate_crc8 ( uint8_t crc_init, uint8_t *data_in, uint16_t len );

void enocean5_cfg_setup ( enocean5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 57600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t enocean5_init ( enocean5_t *ctx, enocean5_cfg_t *cfg ) 
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

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t enocean5_generic_write ( enocean5_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t enocean5_generic_read ( enocean5_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void enocean5_set_rst_pin ( enocean5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

err_t enocean5_reset_device ( enocean5_t *ctx )
{
    enocean5_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    return enocean5_wait_packet ( ctx, ENOCEAN5_PKT_TYPE_EVENT, ENOCEAN5_EVT_READY, ENOCEAN5_WAIT_TIME_5S );
}

err_t enocean5_send_packet ( enocean5_t *ctx )
{
    uint8_t header_buf[ 6 ] = { 0 };
    uint8_t crc_calc = 0;
    if ( ( ctx->tx_pkt.pl_len > ENOCEAN5_PAYLOAD_BUFFER_SIZE ) || 
         ( ctx->tx_pkt.pl_opt_len > ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE ) )
    {
        return ENOCEAN5_ERROR;
    }
    header_buf[ 0 ] = ENOCEAN5_PKT_SYNC_BYTE;
    header_buf[ 1 ] = ( uint8_t ) ( ( ctx->tx_pkt.pl_len >> 8 ) & 0xFF );
    header_buf[ 2 ] = ( uint8_t ) ( ctx->tx_pkt.pl_len & 0xFF );
    header_buf[ 3 ] = ctx->tx_pkt.pl_opt_len;
    header_buf[ 4 ] = ctx->tx_pkt.type;
    header_buf[ 5 ] = enocean5_calculate_crc8 ( 0, &header_buf[ 1 ], 4 );
    enocean5_clear_buffers ( ctx );
    enocean5_generic_write ( ctx, header_buf, 6 );
    if ( ctx->tx_pkt.pl_len ) 
    {
        crc_calc = enocean5_calculate_crc8 ( 0, ctx->tx_pkt.payload, ctx->tx_pkt.pl_len );
        enocean5_generic_write ( ctx, ctx->tx_pkt.payload, ctx->tx_pkt.pl_len );
    }
    if ( ctx->tx_pkt.pl_opt_len ) 
    {
        crc_calc = enocean5_calculate_crc8 ( crc_calc, ctx->tx_pkt.payload_opt, ctx->tx_pkt.pl_opt_len );
        enocean5_generic_write ( ctx, ctx->tx_pkt.payload_opt, ctx->tx_pkt.pl_opt_len );
    }
    enocean5_generic_write ( ctx, &crc_calc, 1 );
    Delay_10ms( );
    return ENOCEAN5_OK;
}

err_t enocean5_read_packet ( enocean5_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t header_buf[ 6 ] = { 0 };
    uint8_t crc_calc = 0;
    uint8_t crc_read = 0;
    while ( ENOCEAN5_PKT_SYNC_BYTE != header_buf[ 0 ] )
    {
        if ( 1 == enocean5_generic_read( ctx, header_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= ENOCEAN5_RSP_TIMEOUT_1000MS )
        {
            return ENOCEAN5_ERROR;
        }
    }
    Delay_10ms( );
    if ( 5 == enocean5_generic_read( ctx, &header_buf[ 1 ], 5 ) )
    {
        ctx->rx_pkt.pl_len = ( ( uint16_t ) header_buf[ 1 ] << 8 ) | header_buf[ 2 ];
        if ( ctx->rx_pkt.pl_len > ENOCEAN5_PAYLOAD_BUFFER_SIZE )
        {
            ctx->rx_pkt.pl_len = ENOCEAN5_PAYLOAD_BUFFER_SIZE;
        }
        ctx->rx_pkt.pl_opt_len = header_buf[ 3 ];
        if ( ctx->rx_pkt.pl_opt_len > ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE )
        {
            ctx->rx_pkt.pl_opt_len = ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE;
        }
        ctx->rx_pkt.type = header_buf[ 4 ];
        if ( header_buf[ 5 ] != enocean5_calculate_crc8 ( 0, &header_buf[ 1 ], 4 ) )
        {
            return ENOCEAN5_ERROR;
        }
        for ( timeout_cnt = 0; timeout_cnt < ( ctx->rx_pkt.pl_len + ctx->rx_pkt.pl_opt_len ); timeout_cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->rx_pkt.pl_len )
        {
            if ( ctx->rx_pkt.pl_len != 
                 enocean5_generic_read( ctx, ctx->rx_pkt.payload, ctx->rx_pkt.pl_len ) )
            {
                return ENOCEAN5_ERROR;
            }
            crc_calc = enocean5_calculate_crc8 ( 0, ctx->rx_pkt.payload, ctx->rx_pkt.pl_len );
        }
        if ( ctx->rx_pkt.pl_opt_len )
        {
            if ( ctx->rx_pkt.pl_opt_len != 
                 enocean5_generic_read( ctx, ctx->rx_pkt.payload_opt, ctx->rx_pkt.pl_opt_len ) )
            {
                return ENOCEAN5_ERROR;
            }
            crc_calc = enocean5_calculate_crc8 ( crc_calc, ctx->rx_pkt.payload_opt, ctx->rx_pkt.pl_opt_len );
        }

        if ( 1 == enocean5_generic_read( ctx, &crc_read, 1 ) )
        {
            if ( crc_read == crc_calc )
            {
                return ENOCEAN5_OK;
            }
        }
    }
    return ENOCEAN5_ERROR;
}

err_t enocean5_wait_packet ( enocean5_t *ctx, uint8_t type, uint8_t cmd, uint8_t max_time_s )
{
    uint8_t timeout_cnt = 0;
    for ( timeout_cnt = 0; timeout_cnt < max_time_s; timeout_cnt++ )
    {
        if ( ENOCEAN5_OK == enocean5_read_packet ( ctx ) )
        {
            if ( ctx->rx_pkt.type == type )
            {
                if ( ENOCEAN5_PKT_TYPE_RESPONSE == ctx->rx_pkt.type )
                {
                    return ctx->rx_pkt.payload[ 0 ];
                }
                if ( ctx->rx_pkt.payload[ 0 ] == cmd )
                {
                    return ENOCEAN5_OK;
                }
            }
        }
    } 
    return ENOCEAN5_ERROR;
}

void enocean5_clear_buffers ( enocean5_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->rx_pkt.pl_len = 0;
    ctx->rx_pkt.pl_opt_len = 0;
    ctx->rx_pkt.type = 0;
    memset ( ctx->rx_pkt.payload, 0, ENOCEAN5_PAYLOAD_BUFFER_SIZE );
    memset ( ctx->rx_pkt.payload_opt, 0, ENOCEAN5_PAYLOAD_OPT_BUFFER_SIZE );
}

err_t enocean5_read_info ( enocean5_t *ctx )
{
    err_t error_flag = ENOCEAN5_OK;
    ctx->tx_pkt.pl_len = 1;
    ctx->tx_pkt.pl_opt_len = 0;
    ctx->tx_pkt.type = ENOCEAN5_PKT_TYPE_COMMON_CMD;
    ctx->tx_pkt.payload[ 0 ] = ENOCEAN5_CMD_RD_VERSION;
    error_flag = enocean5_send_packet ( ctx );
    if ( ENOCEAN5_OK == error_flag )
    {
        error_flag = enocean5_wait_packet ( ctx, ENOCEAN5_PKT_TYPE_RESPONSE, ENOCEAN5_RET_OK, ENOCEAN5_WAIT_TIME_1S );
    }
    if ( ENOCEAN5_OK == error_flag )
    {
        memcpy ( ctx->info.app_ver, &ctx->rx_pkt.payload[ 1 ], 4 );
        memcpy ( ctx->info.api_ver, &ctx->rx_pkt.payload[ 5 ], 4 );
        ctx->info.device_id = ( ( uint32_t ) ctx->rx_pkt.payload[ 9 ] << 24 ) | 
                              ( ( uint32_t ) ctx->rx_pkt.payload[ 10 ] << 16 ) | 
                              ( ( uint32_t ) ctx->rx_pkt.payload[ 11 ] << 8 ) | 
                              ( ( uint32_t ) ctx->rx_pkt.payload[ 12 ] << 0 );
        ctx->info.device_ver = ( ( uint32_t ) ctx->rx_pkt.payload[ 13 ] << 24 ) | 
                               ( ( uint32_t ) ctx->rx_pkt.payload[ 14 ] << 16 ) | 
                               ( ( uint32_t ) ctx->rx_pkt.payload[ 15 ] << 8 ) | 
                               ( ( uint32_t ) ctx->rx_pkt.payload[ 16 ] << 0 );
        memcpy ( ctx->info.app_desc, &ctx->rx_pkt.payload[ 17 ], 16 );
    }
    return error_flag;
}

err_t enocean5_send_radio_message ( enocean5_t *ctx, uint8_t rorg, uint8_t *data_in, uint8_t data_len )
{
    err_t error_flag = ENOCEAN5_OK;
    if ( ( data_len < 1 ) || ( data_len > 14 ) )
    {
        return ENOCEAN5_ERROR;
    }
    ctx->tx_pkt.pl_len = data_len + 2;
    ctx->tx_pkt.pl_opt_len = 10;
    ctx->tx_pkt.type = ENOCEAN5_PKT_TYPE_RADIO_MESSAGE;
    ctx->tx_pkt.payload[ 0 ] = ENOCEAN5_RORG_VLD;
    memcpy ( &ctx->tx_pkt.payload[ 1 ], data_in, data_len );
    ctx->tx_pkt.payload[ ctx->tx_pkt.pl_len - 1 ] = 0;
    ctx->tx_pkt.payload_opt[ 0 ] = ( uint8_t ) ( ( ENOCEAN5_BROADCAST_ID >> 24 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 1 ] = ( uint8_t ) ( ( ENOCEAN5_BROADCAST_ID >> 16 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 2 ] = ( uint8_t ) ( ( ENOCEAN5_BROADCAST_ID >> 8 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 3 ] = ( uint8_t ) ( ( ENOCEAN5_BROADCAST_ID >> 0 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 4 ] = ( uint8_t ) ( ( ENOCEAN5_TX_ID >> 24 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 5 ] = ( uint8_t ) ( ( ENOCEAN5_TX_ID >> 16 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 6 ] = ( uint8_t ) ( ( ENOCEAN5_TX_ID >> 8 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 7 ] = ( uint8_t ) ( ( ENOCEAN5_TX_ID >> 0 ) & 0xFF );
    ctx->tx_pkt.payload_opt[ 8 ] = 0xFF; // dBm field, set to 0xFF for transmission
    ctx->tx_pkt.payload_opt[ 9 ] = 0x00; // Security Level, ignored for transmission
    return enocean5_send_packet ( ctx );
}

static uint8_t enocean5_calculate_crc8 ( uint8_t crc_init, uint8_t *data_in, uint16_t len )
{
    uint16_t byte_cnt = 0;
    uint8_t crc = crc_init;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        crc = enocean5_crc8_table[ ( data_in[ byte_cnt ] ^ crc ) & 0xFF ];
    }
    return crc;
}

// ------------------------------------------------------------------------- END
