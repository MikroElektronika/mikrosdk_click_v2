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
 * @file proteuse.c
 * @brief Proteus-e Click Driver.
 */

#include "proteuse.h"

void proteuse_cfg_setup ( proteuse_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t proteuse_init ( proteuse_t *ctx, proteuse_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->rst, cfg->rst );
    
    // Dummy read to enable RX interrupt
    uint8_t dummy = 0;
    uart_read( &ctx->uart, &dummy, 1 );
    
    return UART_SUCCESS;
}

err_t proteuse_default_cfg ( proteuse_t *ctx ) 
{
    err_t error_flag = PROTEUSE_OK;
    proteuse_enable_uart ( ctx );
    if ( PROTEUSE_ERROR == proteuse_reset_device ( ctx ) )
    {
        return PROTEUSE_ERROR;
    }
    return error_flag;
}

err_t proteuse_generic_write ( proteuse_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t proteuse_generic_read ( proteuse_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void proteuse_set_rst_pin ( proteuse_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

err_t proteuse_reset_device ( proteuse_t *ctx )
{
    proteuse_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    return proteuse_wait_for_event ( ctx, PROTEUSE_CMD_CNF_GET_STATE, PROTEUSE_WAIT_TIME_1S );
}

void proteuse_set_en_pin ( proteuse_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void proteuse_enable_uart ( proteuse_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
}

void proteuse_send_cmd ( proteuse_t *ctx )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    cmd_buf[ 0 ] = PROTEUSE_START_BYTE;
    cmd_buf[ 1 ] = ctx->cmd_pkt.cmd;
    cmd_buf[ 2 ] = ctx->cmd_pkt.payload_len;
    cmd_buf[ 3 ] = 0; // Payload len MSB (unused because MPS is 243+7)
    proteuse_clear_buffers ( ctx );    
    proteuse_generic_write ( ctx, cmd_buf, 4 );
    checksum = cmd_buf[ 0 ] ^ cmd_buf[ 1 ] ^ cmd_buf[ 2 ] ^ cmd_buf[ 3 ];
    if ( ctx->cmd_pkt.payload_len ) 
    {
        proteuse_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
        for ( cnt = 0; cnt < ctx->cmd_pkt.payload_len; cnt++ )
        {
            checksum ^= ctx->cmd_pkt.payload[ cnt ];
        }
    }    
    proteuse_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
}

err_t proteuse_read_event ( proteuse_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 4 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    while ( PROTEUSE_START_BYTE != rsp_buf[ 0 ] )
    {
        if ( 1 == proteuse_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= PROTEUSE_RSP_TIMEOUT_1000MS )
        {
            return PROTEUSE_ERROR;
        }
    }
    Delay_10ms( );
    if ( 3 == proteuse_generic_read( ctx, &rsp_buf[ 1 ], 3 ) )
    {
        ctx->evt_pkt.cmd = rsp_buf[ 1 ];
        ctx->evt_pkt.payload_len = rsp_buf[ 2 ];
        for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->evt_pkt.payload_len == 
             proteuse_generic_read( ctx, ctx->evt_pkt.payload, ctx->evt_pkt.payload_len ) )
        {
            if ( 1 == proteuse_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = rsp_buf[ 0 ] ^ rsp_buf[ 1 ] ^ rsp_buf[ 2 ] ^ rsp_buf[ 3 ];
                for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
                {
                    checksum ^= ctx->evt_pkt.payload[ cnt ];
                }
                if ( checksum == checksum_read )
                {
                    return PROTEUSE_OK;
                }
            }
        }
    }
    return PROTEUSE_ERROR;
}

err_t proteuse_wait_for_event ( proteuse_t *ctx, uint8_t cmd, uint8_t max_time_s )
{
    for ( uint8_t cnt = 0; cnt < max_time_s; cnt++ )
    {
        proteuse_read_event ( ctx );
        if ( ctx->evt_pkt.cmd == cmd )
        {
            return PROTEUSE_OK;
        }
    } 
    return PROTEUSE_ERROR;
}

void proteuse_clear_buffers ( proteuse_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, PROTEUSE_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
}

err_t proteuse_set_user_setting ( proteuse_t *ctx, uint8_t set_idx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = PROTEUSE_OK;
    ctx->cmd_pkt.cmd = PROTEUSE_CMD_REQ_SET;
    ctx->cmd_pkt.payload_len = len + 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    memcpy ( &ctx->cmd_pkt.payload[ 1 ], data_in, len );
    proteuse_send_cmd ( ctx );
    error_flag |= proteuse_wait_for_event ( ctx, PROTEUSE_CMD_CNF_SET, PROTEUSE_WAIT_TIME_1S );
    // Check if setting is set successful
    if ( ctx->evt_pkt.payload[ 0 ] )
    {
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

err_t proteuse_get_user_setting ( proteuse_t *ctx, uint8_t set_idx )
{
    err_t error_flag = PROTEUSE_OK;
    ctx->cmd_pkt.cmd = PROTEUSE_CMD_REQ_GET;
    ctx->cmd_pkt.payload_len = 1;
    ctx->cmd_pkt.payload[ 0 ] = set_idx;
    proteuse_send_cmd ( ctx );
    error_flag |= proteuse_wait_for_event ( ctx, PROTEUSE_CMD_CNF_GET, PROTEUSE_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( ctx->evt_pkt.payload[ 0 ] ) && ( ctx->evt_pkt.payload_len <= 1 ) )
    {
        error_flag |= PROTEUSE_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
