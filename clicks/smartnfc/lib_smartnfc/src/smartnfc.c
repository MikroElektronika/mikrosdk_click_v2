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
 * @file smartnfc.c
 * @brief Smart NFC Click Driver.
 */

#include "smartnfc.h"

/** 
 * @brief CCITT-FALSE calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0xFFFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final result
 * @li @c  Example { CMD: 0x0B }- 0x509B
 * @param[in] cmd_frame : Command packet to calculate CRC from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t smartnfc_crc16_ccitt ( smartnfc_frame_t cmd_frame );

void smartnfc_cfg_setup ( smartnfc_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t smartnfc_init ( smartnfc_t *ctx, smartnfc_cfg_t *cfg ) 
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
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t smartnfc_generic_write ( smartnfc_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t smartnfc_generic_read ( smartnfc_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void smartnfc_set_rst_pin ( smartnfc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

err_t smartnfc_reset_device ( smartnfc_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rx_buf[ 20 ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = 0;
    smartnfc_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    while ( timeout_cnt < SMARTNFC_RSP_TIMEOUT_1000MS )
    {
        rx_size = smartnfc_generic_read( ctx, rx_buf, 20 );
        if ( rx_size > 0 )
        {
            if ( ( ctx->rsp_frame.payload_len + rx_size ) > SMARTNFC_PAYLOAD_BUFFER_SIZE ) 
            {
                overflow_bytes = ( ctx->rsp_frame.payload_len + rx_size ) - SMARTNFC_PAYLOAD_BUFFER_SIZE;
                ctx->rsp_frame.payload_len = SMARTNFC_PAYLOAD_BUFFER_SIZE - rx_size;
                memmove ( ctx->rsp_frame.payload, &ctx->rsp_frame.payload[ overflow_bytes ], ctx->rsp_frame.payload_len );
                memset ( &ctx->rsp_frame.payload[ ctx->rsp_frame.payload_len ], 0, overflow_bytes );
            }
            for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
            {
                if ( rx_buf[ rx_cnt ] ) 
                {
                    ctx->rsp_frame.payload[ ctx->rsp_frame.payload_len++ ] = rx_buf[ rx_cnt ];
                }
            }
            timeout_cnt = 0;
        }
        timeout_cnt++;
        Delay_1ms( );
    }
    if ( ( ctx->rsp_frame.payload_len > 0 ) && strstr ( ctx->rsp_frame.payload, "POWERON_RESET" ) )
    {
        return SMARTNFC_OK;
    }
    return SMARTNFC_ERROR;
}

err_t smartnfc_send_frame ( smartnfc_t *ctx )
{
    uint8_t cmd_buf[ 6 ] = { 0 };
    uint16_t crc_16 = 0;
    uint16_t cmd_len = ctx->cmd_frame.payload_len + 3;
    cmd_buf[ 0 ] = SMARTNFC_FRAME_STX;
    cmd_buf[ 1 ] = ( uint8_t ) ( cmd_len & 0xFF );
    cmd_buf[ 2 ] = ( uint8_t ) ( ( cmd_len >> 8 ) & 0xFF );
    cmd_buf[ 3 ] = ( uint8_t ) ( ( cmd_len ^ 0xFFFF ) & 0xFF );
    cmd_buf[ 4 ] = ( uint8_t ) ( ( ( cmd_len ^ 0xFFFF ) >> 8 ) & 0xFF );
    cmd_buf[ 5 ] = ctx->cmd_frame.cmd;
    smartnfc_clear_buffers ( ctx );
    smartnfc_generic_write ( ctx, cmd_buf, 6 );
    if ( ctx->cmd_frame.payload_len ) 
    {
        smartnfc_generic_write ( ctx, ctx->cmd_frame.payload, ctx->cmd_frame.payload_len );
    }
    crc_16 = smartnfc_crc16_ccitt ( ctx->cmd_frame );
    cmd_buf[ 0 ] = ( uint8_t ) ( crc_16 & 0xFF );
    cmd_buf[ 1 ] = ( uint8_t ) ( ( crc_16 >> 8 ) & 0xFF );
    smartnfc_generic_write ( ctx, cmd_buf, 2 );
    Delay_10ms( );
    return SMARTNFC_OK;
}

err_t smartnfc_read_frame ( smartnfc_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 6 ] = { 0 };
    uint16_t cmd_len = 0;
    uint16_t crc_16 = 0;
    while ( SMARTNFC_FRAME_STX != rsp_buf[ 0 ] )
    {
        if ( 1 == smartnfc_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= SMARTNFC_RSP_TIMEOUT_1000MS )
        {
            return SMARTNFC_ERROR;
        }
    }
    Delay_10ms( );
    if ( 5 == smartnfc_generic_read( ctx, &rsp_buf[ 1 ], 5 ) )
    {
        cmd_len = ( ( uint16_t ) rsp_buf[ 2 ] << 8 ) | rsp_buf[ 1 ];
        if ( ( cmd_len ^ 0xFFFF ) != ( ( ( uint16_t ) rsp_buf[ 4 ] << 8 ) | rsp_buf[ 3 ] ) )
        {
            return SMARTNFC_ERROR;
        }
        ctx->rsp_frame.cmd = rsp_buf[ 5 ];
        ctx->rsp_frame.payload_len = cmd_len - 3;
        for ( uint8_t cnt = 0; cnt < ctx->rsp_frame.payload_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->rsp_frame.payload_len == 
             smartnfc_generic_read( ctx, ctx->rsp_frame.payload, ctx->rsp_frame.payload_len ) )
        {
            if ( 2 == smartnfc_generic_read( ctx, rsp_buf, 2 ) )
            {
                crc_16 = ( ( uint16_t ) rsp_buf[ 1 ] << 8 ) | rsp_buf[ 0 ];
                if ( crc_16 == smartnfc_crc16_ccitt ( ctx->rsp_frame ) )
                {
                    return SMARTNFC_OK;
                }
            }
        }
    }
    return SMARTNFC_ERROR;
}

err_t smartnfc_read_ack_frame ( smartnfc_t *ctx, uint8_t cmd )
{
    for ( uint8_t num_tries = 0; num_tries < SMARTNFC_RSP_NUM_TRIES; num_tries++ )
    {
        smartnfc_read_frame ( ctx );
        if ( ( SMARTNFC_CMD_ACK == ctx->rsp_frame.cmd ) && ( cmd == ctx->rsp_frame.payload[ 0 ] ) )
        {
            return SMARTNFC_OK;
        }
    } 
    return SMARTNFC_ERROR;
}

void smartnfc_clear_buffers ( smartnfc_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->rsp_frame.cmd = 0;
    memset ( ctx->rsp_frame.payload, 0, SMARTNFC_PAYLOAD_BUFFER_SIZE );
    ctx->rsp_frame.payload_len = 0;
}

static uint16_t smartnfc_crc16_ccitt ( smartnfc_frame_t cmd_frame )
{
    uint16_t crc16 = 0xFFFF;
    uint16_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    crc16 ^= ( ( uint16_t ) cmd_frame.cmd << 8 );
    for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
    {
        if ( crc16 & 0x8000 )
        {
            crc16 = ( crc16 << 1 ) ^ 0x1021;
        }
        else
        {
            crc16 <<= 1;
        }
    }
    for ( byte_cnt = 0; byte_cnt < cmd_frame.payload_len; byte_cnt++ )
    {
        crc16 ^= ( ( uint16_t ) cmd_frame.payload[ byte_cnt ] << 8 );
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x1021;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16;
}

// ------------------------------------------------------------------------- END
