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
 * @file proteusii.c
 * @brief Proteus-II Click Driver.
 */

#include "proteusii.h"

void proteusii_cfg_setup ( proteusii_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->busy = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t proteusii_init ( proteusii_t *ctx, proteusii_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    err_t error_flag = UART_SUCCESS;

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
        error_flag = UART_ERROR;
    }
    else
    {
        uart_set_baud( &ctx->uart, cfg->baud_rate );
        uart_set_parity( &ctx->uart, cfg->parity_bit );
        uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
        uart_set_data_bits( &ctx->uart, cfg->data_bit );

        uart_set_blocking( &ctx->uart, cfg->uart_blocking );

        // Output pins
        digital_out_init( &ctx->rst, cfg->rst );
        digital_out_low( &ctx->rst );
        digital_out_init( &ctx->cts, cfg->cts );
        digital_out_high( &ctx->cts );
        digital_out_init( &ctx->wup, cfg->wup );
        digital_out_high( &ctx->wup );

        // Input pins
        digital_in_init( &ctx->busy, cfg->busy );
        digital_in_init( &ctx->rts, cfg->rts );

        // Dummy read to enable RX interrupt before releasing reset
        uint8_t dummy = 0;
        uart_read( &ctx->uart, &dummy, 1 );
    }
    return error_flag;
}

err_t proteusii_generic_write ( proteusii_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t proteusii_generic_read ( proteusii_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void proteusii_set_rst_pin ( proteusii_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void proteusii_set_cts_pin ( proteusii_t *ctx, uint8_t state )
{
    // The ClickID mux connects CS to module CTS while reset is released.
    digital_out_write ( &ctx->cts, state );
}

uint8_t proteusii_get_busy_pin ( proteusii_t *ctx )
{
    return digital_in_read ( &ctx->busy );
}

uint8_t proteusii_get_rts_pin ( proteusii_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

err_t proteusii_reset_device ( proteusii_t *ctx )
{
    digital_out_high ( &ctx->cts );
    digital_out_high ( &ctx->wup );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    proteusii_clear_buffers ( ctx );
    digital_out_high ( &ctx->rst );
    digital_out_low ( &ctx->cts );
    return proteusii_wait_for_event ( ctx, PROTEUSII_CMD_CNF_GET_STATE, PROTEUSII_WAIT_TIME_1S );
}

void proteusii_set_wup_pin ( proteusii_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void proteusii_wake_up ( proteusii_t *ctx )
{
    digital_out_low ( &ctx->wup );
    Delay_10ms ( );
    digital_out_high ( &ctx->wup );
    Delay_10ms ( );
}

void proteusii_send_cmd ( proteusii_t *ctx )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    cmd_buf[ 0 ] = PROTEUSII_START_BYTE;
    cmd_buf[ 1 ] = ctx->cmd_pkt.cmd;
    cmd_buf[ 2 ] = ctx->cmd_pkt.payload_len;
    cmd_buf[ 3 ] = 0; // Payload len MSB (unused because MPS is 243+7)
    // Preserve pending events when sending a command or echoing received data.
    proteusii_generic_write ( ctx, cmd_buf, 4 );
    checksum = cmd_buf[ 0 ] ^ cmd_buf[ 1 ] ^ cmd_buf[ 2 ] ^ cmd_buf[ 3 ];
    if ( ctx->cmd_pkt.payload_len )
    {
        proteusii_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
        for ( cnt = 0; cnt < ctx->cmd_pkt.payload_len; cnt++ )
        {
            checksum ^= ctx->cmd_pkt.payload[ cnt ];
        }
    }
    proteusii_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
}

err_t proteusii_read_event ( proteusii_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 4 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    err_t error_flag = PROTEUSII_ERROR;

    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, PROTEUSII_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
    while ( ( PROTEUSII_START_BYTE != rsp_buf[ 0 ] ) &&
            ( timeout_cnt < PROTEUSII_RSP_TIMEOUT_1000MS ) )
    {
        proteusii_generic_read( ctx, rsp_buf, 1 );
        Delay_1ms( );
        timeout_cnt++;
    }
    if ( PROTEUSII_START_BYTE == rsp_buf[ 0 ] )
    {
        Delay_10ms( );
        // UART output may pause between bytes; wait for the complete header.
        timeout_cnt = 0;
        while ( ( uart_bytes_available( &ctx->uart ) < 3 ) &&
                ( timeout_cnt < PROTEUSII_RSP_TIMEOUT_1000MS ) )
        {
            Delay_1ms( );
            timeout_cnt++;
        }
        if ( ( 3 == proteusii_generic_read( ctx, &rsp_buf[ 1 ], 3 ) ) && ( !rsp_buf[ 3 ] ) )
        {
            ctx->evt_pkt.cmd = rsp_buf[ 1 ];
            ctx->evt_pkt.payload_len = rsp_buf[ 2 ];
            // Keep the payload and checksum together, including a zero-length payload.
            while ( ( uart_bytes_available( &ctx->uart ) < ( uint16_t ) ctx->evt_pkt.payload_len + 1 ) &&
                    ( timeout_cnt < PROTEUSII_RSP_TIMEOUT_1000MS ) )
            {
                Delay_1ms( );
                timeout_cnt++;
            }
            if ( ( !ctx->evt_pkt.payload_len ) || ( ctx->evt_pkt.payload_len ==
                 proteusii_generic_read( ctx, ctx->evt_pkt.payload, ctx->evt_pkt.payload_len ) ) )
            {
                if ( 1 == proteusii_generic_read( ctx, &checksum_read, 1 ) )
                {
                    checksum = rsp_buf[ 0 ] ^ rsp_buf[ 1 ] ^ rsp_buf[ 2 ] ^ rsp_buf[ 3 ];
                    for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
                    {
                        checksum ^= ctx->evt_pkt.payload[ cnt ];
                    }
                    if ( checksum == checksum_read )
                    {
                        error_flag = PROTEUSII_OK;
                    }
                }
            }
        }
    }
    return error_flag;
}

err_t proteusii_wait_for_event ( proteusii_t *ctx, uint8_t cmd, uint8_t max_time_s )
{
    err_t error_flag = PROTEUSII_ERROR;
    for ( uint8_t cnt = 0; cnt < max_time_s; cnt++ )
    {
        if ( ( PROTEUSII_OK == proteusii_read_event ( ctx ) ) && ( ctx->evt_pkt.cmd == cmd ) )
        {
            error_flag = PROTEUSII_OK;
            break;
        }
    }
    return error_flag;
}

void proteusii_clear_buffers ( proteusii_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, PROTEUSII_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
}

err_t proteusii_set_user_setting ( proteusii_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = PROTEUSII_OK;
    if ( len < 255 )
    {
        ctx->cmd_pkt.cmd = PROTEUSII_CMD_REQ_SET;
        ctx->cmd_pkt.payload_len = len + 1;
        ctx->cmd_pkt.payload[ 0 ] = set_idx;
        memcpy ( &ctx->cmd_pkt.payload[ 1 ], data_in, len );
        proteusii_send_cmd ( ctx );
        error_flag |= proteusii_wait_for_event ( ctx, PROTEUSII_CMD_CNF_SET, PROTEUSII_WAIT_TIME_1S );
        // Check if setting is set successful
        if ( ( ctx->evt_pkt.payload[ 0 ] ) || ( 1 != ctx->evt_pkt.payload_len ) )
        {
            error_flag |= PROTEUSII_ERROR;
        }
    }
    else
    {
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

err_t proteusii_get_user_setting ( proteusii_t *ctx, uint8_t set_idx )
{
    err_t error_flag = PROTEUSII_OK;
    ctx->cmd_pkt.cmd = PROTEUSII_CMD_REQ_GET;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    proteusii_send_cmd ( ctx );
    error_flag |= proteusii_wait_for_event ( ctx, PROTEUSII_CMD_CNF_GET, PROTEUSII_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( ctx->evt_pkt.payload[ 0 ] ) || ( ctx->evt_pkt.payload_len <= 1 ) )
    {
        error_flag |= PROTEUSII_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
