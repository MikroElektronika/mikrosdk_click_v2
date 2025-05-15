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
 * @file ism7.c
 * @brief ISM 7 Click Driver.
 */

#include "ism7.h"

void ism7_cfg_setup ( ism7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ism7_init ( ism7_t *ctx, ism7_cfg_t *cfg ) 
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
    digital_out_init( &ctx->wup, cfg->wup );
    Delay_100ms( );
    digital_out_low( &ctx->wup );
    digital_out_low( &ctx->rst );
    Delay_100ms( );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t ism7_generic_write ( ism7_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ism7_generic_read ( ism7_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ism7_set_wup_pin ( ism7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void ism7_set_rst_pin ( ism7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t ism7_get_rts_pin ( ism7_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

err_t ism7_reset_device ( ism7_t *ctx )
{
    ism7_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    return ism7_wait_for_event ( ctx, ISM7_CMD_IND_RESET, ISM7_WAIT_TIME_3S );
}

err_t ism7_send_cmd ( ism7_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t cmd_buf[ 3 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    cmd_buf[ 0 ] = ISM7_START_BYTE;
    cmd_buf[ 1 ] = ctx->cmd_pkt.cmd;
    cmd_buf[ 2 ] = ctx->cmd_pkt.payload_len;
    while ( ism7_get_rts_pin ( ctx ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt >= ISM7_RSP_TIMEOUT_1000MS )
        {
            return ISM7_ERROR;
        }
    }
    ism7_clear_buffers ( ctx );    
    ism7_generic_write ( ctx, cmd_buf, 3 );
    checksum = cmd_buf[ 0 ] ^ cmd_buf[ 1 ] ^ cmd_buf[ 2 ];
    if ( ctx->cmd_pkt.payload_len ) 
    {
        ism7_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
        for ( cnt = 0; cnt < ctx->cmd_pkt.payload_len; cnt++ )
        {
            checksum ^= ctx->cmd_pkt.payload[ cnt ];
        }
    }    
    ism7_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
    return ISM7_OK;
}

err_t ism7_read_event ( ism7_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 3 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    while ( ISM7_START_BYTE != rsp_buf[ 0 ] )
    {
        if ( 1 == ism7_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= ISM7_RSP_TIMEOUT_1000MS )
        {
            return ISM7_ERROR;
        }
    }
    Delay_10ms( );
    if ( 2 == ism7_generic_read( ctx, &rsp_buf[ 1 ], 2 ) )
    {
        ctx->evt_pkt.cmd = rsp_buf[ 1 ];
        ctx->evt_pkt.payload_len = rsp_buf[ 2 ];
        for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->evt_pkt.payload_len == 
             ism7_generic_read( ctx, ctx->evt_pkt.payload, ctx->evt_pkt.payload_len ) )
        {
            if ( 1 == ism7_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = rsp_buf[ 0 ] ^ rsp_buf[ 1 ] ^ rsp_buf[ 2 ];
                for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
                {
                    checksum ^= ctx->evt_pkt.payload[ cnt ];
                }
                if ( checksum == checksum_read )
                {
                    return ISM7_OK;
                }
            }
        }
    }
    return ISM7_ERROR;
}

err_t ism7_wait_for_event ( ism7_t *ctx, uint8_t cmd, uint8_t max_time_s )
{
    for ( uint8_t cnt = 0; cnt < max_time_s; cnt++ )
    {
        ism7_read_event ( ctx );
        if ( ctx->evt_pkt.cmd == cmd )
        {
            return ISM7_OK;
        }
    } 
    return ISM7_ERROR;
}

void ism7_clear_buffers ( ism7_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, ISM7_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
}

err_t ism7_set_user_setting ( ism7_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = ISM7_OK;
    ctx->cmd_pkt.cmd = ISM7_CMD_REQ_SET;
    ctx->cmd_pkt.payload_len = len + 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    memcpy ( &ctx->cmd_pkt.payload[ 1 ], data_in, len );
    ism7_send_cmd ( ctx );
    error_flag |= ism7_wait_for_event ( ctx, ISM7_CMD_CNF_SET, ISM7_WAIT_TIME_1S );
    // Check if setting is set successful
    if ( ctx->evt_pkt.payload[ 0 ] )
    {
        error_flag |= ISM7_ERROR;
    }
    return error_flag;
}

err_t ism7_get_user_setting ( ism7_t *ctx, uint8_t set_idx )
{
    err_t error_flag = ISM7_OK;
    ctx->cmd_pkt.cmd = ISM7_CMD_REQ_GET;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    ism7_send_cmd ( ctx );
    error_flag |= ism7_wait_for_event ( ctx, ISM7_CMD_CNF_GET, ISM7_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( ctx->evt_pkt.payload[ 0 ] ) && ( ctx->evt_pkt.payload_len <= 1 ) )
    {
        error_flag |= ISM7_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
