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
 * @file xsensmti8.c
 * @brief XSENS MTi-8 Click Driver.
 */

#include "xsensmti8.h"

void xsensmti8_cfg_setup ( xsensmti8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t xsensmti8_init ( xsensmti8_t *ctx, xsensmti8_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    digital_out_low( &ctx->cts );
    digital_out_low( &ctx->rst );

    return UART_SUCCESS;
}

err_t xsensmti8_generic_write ( xsensmti8_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t xsensmti8_generic_read ( xsensmti8_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void xsensmti8_set_rst_pin ( xsensmti8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void xsensmti8_set_cts_pin ( xsensmti8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t xsensmti8_get_rts_pin ( xsensmti8_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void xsensmti8_reset_device ( xsensmti8_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void xsensmti8_clear_buffers ( xsensmti8_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->cmd_msg.msg_id = 0;
    memset ( ctx->cmd_msg.data_buf, 0, XSENSMTI8_DATA_BUFFER_SIZE );
    ctx->cmd_msg.data_len = 0;
    ctx->rsp_msg.msg_id = 0;
    memset ( ctx->rsp_msg.data_buf, 0, XSENSMTI8_DATA_BUFFER_SIZE );
    ctx->rsp_msg.data_len = 0;
}

err_t xsensmti8_send_message ( xsensmti8_t *ctx )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    cmd_buf[ 0 ] = XSENSMTI8_PREAMBLE;
    cmd_buf[ 1 ] = XSENSMTI8_BID;
    cmd_buf[ 2 ] = ctx->cmd_msg.msg_id;
    cmd_buf[ 3 ] = ctx->cmd_msg.data_len;
    if ( ctx->cmd_msg.data_len > XSENSMTI8_DATA_BUFFER_SIZE )
    {
        return XSENSMTI8_ERROR;
    }
    uart_clear ( &ctx->uart );
    xsensmti8_generic_write ( ctx, cmd_buf, 4 );
    checksum = cmd_buf[ 1 ] + cmd_buf[ 2 ] + cmd_buf[ 3 ];
    if ( ctx->cmd_msg.data_len )
    {
        xsensmti8_generic_write ( ctx, ctx->cmd_msg.data_buf, ctx->cmd_msg.data_len );
        for ( cnt = 0; cnt < ctx->cmd_msg.data_len; cnt++ )
        {
            checksum += ctx->cmd_msg.data_buf[ cnt ];
        }
    }
    checksum = 256 - checksum;
    xsensmti8_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
    return XSENSMTI8_OK;
}

err_t xsensmti8_read_message ( xsensmti8_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 4 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    ctx->rsp_msg.msg_id = 0;
    memset ( ctx->rsp_msg.data_buf, 0, XSENSMTI8_DATA_BUFFER_SIZE );
    ctx->rsp_msg.data_len = 0;
    while ( ( XSENSMTI8_PREAMBLE != rsp_buf[ 0 ] ) || ( XSENSMTI8_BID != rsp_buf[ 1 ] ) )
    {
        if ( 1 == xsensmti8_generic_read( ctx, &rsp_buf[ 0 ], 1 ) )
        {
            if ( XSENSMTI8_PREAMBLE == rsp_buf[ 0 ] )
            {
                Delay_1ms( );
                xsensmti8_generic_read( ctx, &rsp_buf[ 1 ], 1 );
            }
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= XSENSMTI8_RSP_TIMEOUT_1S )
        {
            return XSENSMTI8_ERROR;
        }
    }
    Delay_10ms( );
    if ( 2 == xsensmti8_generic_read( ctx, &rsp_buf[ 2 ], 2 ) )
    {
        if ( rsp_buf[ 3 ] > XSENSMTI8_DATA_BUFFER_SIZE )
        {
            return XSENSMTI8_ERROR;
        }
        ctx->rsp_msg.msg_id = rsp_buf[ 2 ];
        ctx->rsp_msg.data_len = rsp_buf[ 3 ];
        for ( cnt = 0; cnt < ctx->rsp_msg.data_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->rsp_msg.data_len == 
             xsensmti8_generic_read( ctx, ctx->rsp_msg.data_buf, ctx->rsp_msg.data_len ) )
        {
            if ( 1 == xsensmti8_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = rsp_buf[ 1 ] + rsp_buf[ 2 ] + rsp_buf[ 3 ];
                for ( cnt = 0; cnt < ctx->rsp_msg.data_len; cnt++ )
                {
                    checksum += ctx->rsp_msg.data_buf[ cnt ];
                }
                checksum = 256 - checksum;
                if ( checksum == checksum_read )
                {
                    return XSENSMTI8_OK;
                }
            }
        }
    }
    return XSENSMTI8_ERROR;
}

err_t xsensmti8_wait_message ( xsensmti8_t *ctx, uint8_t msg_id )
{
    for ( uint8_t num_tries = 0; num_tries < XSENSMTI8_RSP_NUM_TRIES; num_tries++ )
    {
        if ( XSENSMTI8_OK == xsensmti8_read_message ( ctx ) )
        {
            if ( msg_id == ctx->rsp_msg.msg_id )
            {
                return XSENSMTI8_OK;
            }
        }
    } 
    return XSENSMTI8_ERROR;
}

// ------------------------------------------------------------------------- END
