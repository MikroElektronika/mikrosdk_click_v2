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
 * @file mbusrf5.c
 * @brief M-BUS RF 5 Click Driver.
 */

#include "mbusrf5.h"

void mbusrf5_cfg_setup ( mbusrf5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->busy = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t mbusrf5_init ( mbusrf5_t *ctx, mbusrf5_cfg_t *cfg ) 
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

err_t mbusrf5_generic_write ( mbusrf5_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t mbusrf5_generic_read ( mbusrf5_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void mbusrf5_set_wup_pin ( mbusrf5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void mbusrf5_set_rst_pin ( mbusrf5_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t mbusrf5_get_busy_pin ( mbusrf5_t *ctx )
{
    return digital_in_read ( &ctx->busy );
}

err_t mbusrf5_reset_device ( mbusrf5_t *ctx )
{
    mbusrf5_clear_buffers ( ctx );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    return mbusrf5_wait_for_event ( ctx, MBUSRF5_CMD_IND_RESET, MBUSRF5_WAIT_TIME_3S );
}

err_t mbusrf5_send_cmd ( mbusrf5_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    if ( ctx->cmd_pkt.payload_len > MBUSRF5_PAYLOAD_BUFFER_SIZE )
    {
        return MBUSRF5_ERROR;
    }
    cmd_buf[ 0 ] = MBUSRF5_START_BYTE;
    cmd_buf[ 1 ] = ctx->cmd_pkt.cmd;
    cmd_buf[ 2 ] = ( uint8_t ) ( ctx->cmd_pkt.payload_len & 0xFF );
    cmd_buf[ 3 ] = ( uint8_t ) ( ( ctx->cmd_pkt.payload_len >> 8 ) & 0xFF );
    while ( mbusrf5_get_busy_pin ( ctx ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt >= MBUSRF5_RSP_TIMEOUT_1000MS )
        {
            return MBUSRF5_ERROR;
        }
    }
    mbusrf5_clear_buffers ( ctx );    
    mbusrf5_generic_write ( ctx, cmd_buf, 4 );
    checksum = cmd_buf[ 0 ] ^ cmd_buf[ 1 ] ^ cmd_buf[ 2 ] ^ cmd_buf[ 3 ];
    if ( ctx->cmd_pkt.payload_len ) 
    {
        mbusrf5_generic_write ( ctx, ctx->cmd_pkt.payload, ctx->cmd_pkt.payload_len );
        for ( cnt = 0; cnt < ctx->cmd_pkt.payload_len; cnt++ )
        {
            checksum ^= ctx->cmd_pkt.payload[ cnt ];
        }
    }    
    mbusrf5_generic_write ( ctx, &checksum, 1 );
    Delay_10ms( );
    return MBUSRF5_OK;
}

err_t mbusrf5_read_event ( mbusrf5_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint8_t rsp_buf[ 4 ] = { 0 };
    uint8_t checksum_read = 0;
    uint8_t checksum = 0;
    uint8_t cnt = 0;
    while ( MBUSRF5_START_BYTE != rsp_buf[ 0 ] )
    {
        if ( 1 == mbusrf5_generic_read( ctx, rsp_buf, 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= MBUSRF5_RSP_TIMEOUT_1000MS )
        {
            return MBUSRF5_ERROR;
        }
    }
    Delay_10ms( );
    if ( 3 == mbusrf5_generic_read( ctx, &rsp_buf[ 1 ], 3 ) )
    {
        ctx->evt_pkt.cmd = rsp_buf[ 1 ];
        ctx->evt_pkt.payload_len = ( ( uint16_t ) rsp_buf[ 3 ] << 8 ) | rsp_buf[ 2 ];
        if ( ctx->evt_pkt.payload_len > MBUSRF5_PAYLOAD_BUFFER_SIZE )
        {
            ctx->evt_pkt.payload_len = MBUSRF5_PAYLOAD_BUFFER_SIZE;
        }
        for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
        {
            Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
        }
        if ( ctx->evt_pkt.payload_len == 
             mbusrf5_generic_read( ctx, ctx->evt_pkt.payload, ctx->evt_pkt.payload_len ) )
        {
            if ( 1 == mbusrf5_generic_read( ctx, &checksum_read, 1 ) )
            {
                checksum = rsp_buf[ 0 ] ^ rsp_buf[ 1 ] ^ rsp_buf[ 2 ] ^ rsp_buf[ 3 ];
                for ( cnt = 0; cnt < ctx->evt_pkt.payload_len; cnt++ )
                {
                    checksum ^= ctx->evt_pkt.payload[ cnt ];
                }
                if ( checksum == checksum_read )
                {
                    return MBUSRF5_OK;
                }
            }
        }
    }
    return MBUSRF5_ERROR;
}

err_t mbusrf5_wait_for_event ( mbusrf5_t *ctx, uint8_t cmd, uint8_t max_time_s )
{
    for ( uint8_t cnt = 0; cnt < max_time_s; cnt++ )
    {
        mbusrf5_read_event ( ctx );
        if ( ctx->evt_pkt.cmd == cmd )
        {
            return MBUSRF5_OK;
        }
    } 
    return MBUSRF5_ERROR;
}

void mbusrf5_clear_buffers ( mbusrf5_t *ctx )
{
    uart_clear ( &ctx->uart );
    ctx->evt_pkt.cmd = 0;
    memset ( ctx->evt_pkt.payload, 0, MBUSRF5_PAYLOAD_BUFFER_SIZE );
    ctx->evt_pkt.payload_len = 0;
}

err_t mbusrf5_set_user_setting_ram ( mbusrf5_t *ctx, uint8_t option, uint8_t data_in )
{
    err_t error_flag = MBUSRF5_OK;
    ctx->cmd_pkt.cmd = MBUSRF5_CMD_REQ_SETRAM;
    ctx->cmd_pkt.payload_len = 3;
    ctx->cmd_pkt.payload[ 0 ] = option;
    ctx->cmd_pkt.payload[ 1 ] = 1; // Option length
    ctx->cmd_pkt.payload[ 2 ] = data_in;
    error_flag |= mbusrf5_send_cmd ( ctx );
    error_flag |= mbusrf5_wait_for_event ( ctx, MBUSRF5_CMD_CNF_SETRAM, MBUSRF5_WAIT_TIME_1S );
    // Check if setting is set successful
    if ( ( MBUSRF5_OPT_STATUS != ctx->evt_pkt.payload[ 0 ] ) || 
         ( MBUSRF5_STATUS_OK != ctx->evt_pkt.payload[ 2 ] ) )
    {
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

err_t mbusrf5_get_user_setting_ram ( mbusrf5_t *ctx, uint8_t option )
{
    err_t error_flag = MBUSRF5_OK;
    ctx->cmd_pkt.cmd = MBUSRF5_CMD_REQ_GETRAM;
    ctx->cmd_pkt.payload_len = 3;
    ctx->cmd_pkt.payload[ 0 ] = MBUSRF5_OPT_PARAMETER;
    ctx->cmd_pkt.payload[ 1 ] = 1; // Option length
    ctx->cmd_pkt.payload[ 2 ] = option;
    error_flag |= mbusrf5_send_cmd ( ctx );
    error_flag |= mbusrf5_wait_for_event ( ctx, MBUSRF5_CMD_CNF_GETRAM, MBUSRF5_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( MBUSRF5_OPT_STATUS != ctx->evt_pkt.payload[ 0 ] ) || 
         ( MBUSRF5_STATUS_OK != ctx->evt_pkt.payload[ 2 ] ) || 
         ( ctx->evt_pkt.payload_len <= 3 ) )
    {
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

err_t mbusrf5_set_user_setting_flash ( mbusrf5_t *ctx, uint8_t option, uint8_t data_in )
{
    err_t error_flag = MBUSRF5_OK;
    ctx->cmd_pkt.cmd = MBUSRF5_CMD_REQ_SET;
    ctx->cmd_pkt.payload_len = 3;
    ctx->cmd_pkt.payload[ 0 ] = option;
    ctx->cmd_pkt.payload[ 1 ] = 1; // Option length
    ctx->cmd_pkt.payload[ 2 ] = data_in;
    error_flag |= mbusrf5_send_cmd ( ctx );
    error_flag |= mbusrf5_wait_for_event ( ctx, MBUSRF5_CMD_CNF_SET, MBUSRF5_WAIT_TIME_1S );
    // Check if setting is set successful
    if ( ( MBUSRF5_OPT_STATUS != ctx->evt_pkt.payload[ 0 ] ) || 
         ( MBUSRF5_STATUS_OK != ctx->evt_pkt.payload[ 2 ] ) )
    {
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

err_t mbusrf5_get_user_setting_flash ( mbusrf5_t *ctx, uint8_t option )
{
    err_t error_flag = MBUSRF5_OK;
    ctx->cmd_pkt.cmd = MBUSRF5_CMD_REQ_GET;
    ctx->cmd_pkt.payload_len = 3;
    ctx->cmd_pkt.payload[ 0 ] = MBUSRF5_OPT_PARAMETER;
    ctx->cmd_pkt.payload[ 1 ] = 1; // Option length
    ctx->cmd_pkt.payload[ 2 ] = option;
    error_flag |= mbusrf5_send_cmd ( ctx );
    error_flag |= mbusrf5_wait_for_event ( ctx, MBUSRF5_CMD_CNF_GET, MBUSRF5_WAIT_TIME_1S );
    // Check if read out of setting is successful
    if ( ( MBUSRF5_OPT_STATUS != ctx->evt_pkt.payload[ 0 ] ) || 
         ( MBUSRF5_STATUS_OK != ctx->evt_pkt.payload[ 2 ] ) || 
         ( ctx->evt_pkt.payload_len <= 3 ) )
    {
        error_flag |= MBUSRF5_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
