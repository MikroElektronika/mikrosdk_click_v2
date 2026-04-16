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
 * @file ism9.c
 * @brief ISM 9 Click Driver.
 */

#include "ism9.h"

void ism9_cfg_setup ( ism9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->mode_1 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->busy = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ism9_init ( ism9_t *ctx, ism9_cfg_t *cfg ) 
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
    digital_out_init( &ctx->mode_1, cfg->mode_1 );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );
    Delay_100ms( );
    digital_out_low( &ctx->mode_1 );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->wup );
    Delay_100ms( );

    // Input pins
    digital_in_init( &ctx->busy, cfg->busy );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t ism9_generic_write ( ism9_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ism9_generic_read ( ism9_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ism9_set_mode_1_pin ( ism9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->mode_1, state );
}

void ism9_set_wup_pin ( ism9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void ism9_set_rst_pin ( ism9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t ism9_get_busy_pin ( ism9_t *ctx )
{
    return digital_in_read ( &ctx->busy );
}

err_t ism9_reset_device ( ism9_t *ctx )
{
    ism9_clear_buffers ( ctx );
    digital_out_low ( &ctx->mode_1 );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    return ism9_wait_for_event ( ctx, ISM9_CMD_IND_RESET, ISM9_WAIT_TIME_3S );
}

err_t ism9_send_cmd ( ism9_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t cmd_buf[ 3 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    cmd_buf[ 0 ] = ISM9_START_BYTE;
    cmd_buf[ 1 ] = ctx->cmd_pkt.cmd;
    cmd_buf[ 2 ] = ctx->cmd_pkt.payload_len;
    while ( ism9_get_busy_pin ( ctx ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt >= ISM9_RSP_TIMEOUT_1000MS )
        {
            return ISM9_ERROR;
        }
    }
    ism9_clear_buffers ( ctx );    
    ism9_generic_write ( ctx, cmd_buf, 3 );
    checksum = cmd_buf[ 0 ] ^ cmd_buf[ 1 ] ^ cmd_buf[ 2 ];
    if ( ctx->cmd_pkt.payload_len ) 
    {
        ism9_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
        for ( cnt = 0; cnt < ctx->cmd_pkt.payload_len; cnt++ )
        {
            checksum ^= ctx->cmd_pkt.payload[ cnt ];
        }
    }    
    ism9_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
    return ISM9_OK;
}

err_t ism9_read_event ( ism9_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 3 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    while ( ISM9_START_BYTE != rsp_buf[ 0 ] )
    {
        if ( 1 == ism9_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= ISM9_RSP_TIMEOUT_1000MS )
        {
            return ISM9_ERROR;
        }
    }
    Delay_10ms( );
    if ( 2 == ism9_generic_read( ctx, &rsp_buf[ 1 ], 2 ) )
    {
        ctx->evt_pkt.cmd = rsp_buf[ 1 ];
        ctx->evt_pkt.payload_len = rsp_buf[ 2 ];
        for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->evt_pkt.payload_len == 
             ism9_generic_read( ctx, ctx->evt_pkt.payload, ctx->evt_pkt.payload_len ) )
        {
            if ( 1 == ism9_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = rsp_buf[ 0 ] ^ rsp_buf[ 1 ] ^ rsp_buf[ 2 ];
                for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
                {
                    checksum ^= ctx->evt_pkt.payload[ cnt ];
                }
                if ( checksum == checksum_read )
                {
                    return ISM9_OK;
                }
            }
        }
    }
    return ISM9_ERROR;
}

err_t ism9_wait_for_event ( ism9_t *ctx, uint8_t cmd, uint8_t max_time_s )
{
    for ( uint8_t cnt = 0; cnt < max_time_s; cnt++ )
    {
        ism9_read_event ( ctx );
        if ( ctx->evt_pkt.cmd == cmd )
        {
            return ISM9_OK;
        }
    } 
    return ISM9_ERROR;
}

void ism9_clear_buffers ( ism9_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, ISM9_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
}

err_t ism9_set_user_setting ( ism9_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = ISM9_OK;
    ctx->cmd_pkt.cmd = ISM9_CMD_REQ_SET;
    ctx->cmd_pkt.payload_len = len + 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    memcpy ( &ctx->cmd_pkt.payload[ 1 ], data_in, len );
    ism9_send_cmd ( ctx );
    error_flag |= ism9_wait_for_event ( ctx, ISM9_CMD_CNF_SET, ISM9_WAIT_TIME_1S );
    // Check if setting is set successful
    if ( ctx->evt_pkt.payload[ 0 ] )
    {
        error_flag |= ISM9_ERROR;
    }
    return error_flag;
}

err_t ism9_get_user_setting ( ism9_t *ctx, uint8_t set_idx )
{
    err_t error_flag = ISM9_OK;
    ctx->cmd_pkt.cmd = ISM9_CMD_REQ_GET;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    ism9_send_cmd ( ctx );
    error_flag |= ism9_wait_for_event ( ctx, ISM9_CMD_CNF_GET, ISM9_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( ctx->evt_pkt.payload[ 0 ] ) && ( ctx->evt_pkt.payload_len <= 1 ) )
    {
        error_flag |= ISM9_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
