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
 * @file btez2.c
 * @brief BT-EZ 2 Click Driver.
 */

#include "btez2.h"
#include "conversions.h"
#include "generic_pointer.h"

void btez2_cfg_setup ( btez2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cyspp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t btez2_init ( btez2_t *ctx, btez2_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cyspp, cfg->cyspp );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_low ( &ctx->cts );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cyspp );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t btez2_generic_write ( btez2_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    uart_write( &ctx->uart, data_in, len );
    Delay_100ms ( );
    return BTEZ2_OK;
}

err_t btez2_generic_read ( btez2_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void btez2_set_rst_pin ( btez2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void btez2_reset_device ( btez2_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void btez2_set_cts_pin ( btez2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t btez2_get_rts_pin ( btez2_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void btez2_set_cmd_mode ( btez2_t *ctx )
{
    digital_out_high ( &ctx->cyspp );
    Delay_1sec ( );
}

void btez2_set_data_mode ( btez2_t *ctx )
{
    digital_out_low ( &ctx->cyspp );
    Delay_1sec ( );
}

void btez2_cmd_action ( btez2_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, BTEZ2_PACKET_CMD_ACTION );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, BTEZ2_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, BTEZ2_PACKET_END );
    btez2_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void btez2_cmd_set ( btez2_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, BTEZ2_PACKET_CMD_SET );
    strcat( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, BTEZ2_PACKET_PARAM_DELIMITER );
    strcat( ctx->cmd_buffer, params );
    strcat( ctx->cmd_buffer, BTEZ2_PACKET_END );
    btez2_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void btez2_cmd_get ( btez2_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, BTEZ2_PACKET_CMD_GET );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, BTEZ2_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, BTEZ2_PACKET_END );
    btez2_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void btez2_cmd_profile ( btez2_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, BTEZ2_PACKET_CMD_PROFILE );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, BTEZ2_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, BTEZ2_PACKET_END );
    btez2_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

err_t btez2_read_packet ( btez2_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint16_t read_cnt = 0;
    uint16_t read_len = 0;
    uint8_t read_len_buf[ 5 ] = { 0 };
    uint8_t * __generic_ptr start_ptr = NULL;
    uint8_t * __generic_ptr end_ptr = NULL;
    ctx->evt_pkt.command_type = 0;
    memset ( ctx->evt_pkt.command, 0, sizeof ( ctx->evt_pkt.command ) );
    memset ( ctx->evt_pkt.payload, 0, sizeof ( ctx->evt_pkt.payload ) );
    memset ( ctx->cmd_buffer, 0, sizeof ( ctx->cmd_buffer ) );

    // Waiting for a packet start byte
    while ( '@' != ctx->cmd_buffer[ 0 ] )
    {
        if ( 1 == uart_read( &ctx->uart, &ctx->cmd_buffer[ 0 ], 1 ) )
        {
            timeout_cnt = 0;
        }
        Delay_1ms( );
        if ( ++timeout_cnt >= BTEZ2_RSP_TIMEOUT_1000MS )
        {
            return BTEZ2_ERROR_TIMEOUT;
        }
    }
    Delay_10ms( );

    // Read packet type and length
    if ( 6 != uart_read( &ctx->uart, &ctx->cmd_buffer[ 1 ], 6 ) )
    {
        return BTEZ2_ERROR;
    }

    // Checking packet type and delimiter byte
    if ( ( ( 'R' != ctx->cmd_buffer[ 1 ] ) && ( 'E' != ctx->cmd_buffer[ 1 ] ) ) || 
         ( ',' != ctx->cmd_buffer[ 2 ] ) )
    {
        return BTEZ2_ERROR;
    }

    // Extracting packet length
    memcpy ( read_len_buf, &ctx->cmd_buffer[ 3 ], 4 );
    read_len = hex_to_int16 ( read_len_buf );
    if ( read_len > ( BTEZ2_PAYLOAD_BUFFER_SIZE - 10 ) )
    {
        return BTEZ2_ERROR;
    }
    for ( read_cnt = 0; read_cnt < read_len; read_cnt++ )
    {
        Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
    }
    
    // Read packet command and payload
    if ( read_len != uart_read( &ctx->uart, &ctx->cmd_buffer[ 7 ], read_len ) )
    {
        return BTEZ2_ERROR;
    }

    // Read and check packet end bytes
    if ( 2 != uart_read( &ctx->uart, &ctx->cmd_buffer[ read_len + 7 ], 2 ) )
    {
        return BTEZ2_ERROR;
    }
    if ( ( '\r' != ctx->cmd_buffer[ read_len + 7 ] ) || 
         ( '\n' != ctx->cmd_buffer[ read_len + 8 ] ) )
    {
        return BTEZ2_ERROR;
    }
    
    // Output packet type
    if ( 'R' == ctx->cmd_buffer[ 1 ] )
    {
        ctx->evt_pkt.rsp_flag = BTEZ2_PACKET_TYPE_RESPONSE;
    }
    else
    {
        ctx->evt_pkt.rsp_flag = BTEZ2_PACKET_TYPE_EVENT;
    }
    
    // Extract command code
    start_ptr = &ctx->cmd_buffer[ 8 ];
    end_ptr = strstr( &ctx->cmd_buffer[ 8 ], BTEZ2_PACKET_PARAM_DELIMITER );
    if ( NULL == end_ptr )
    {
        end_ptr = strstr( &ctx->cmd_buffer[ 8 ], BTEZ2_PACKET_END );
    }
    if ( ( NULL == end_ptr ) || ( ( end_ptr - start_ptr ) > BTEZ2_CMD_CODE_BUFFER_SIZE ) )
    {
        return BTEZ2_ERROR;
    }
    if ( 'R' == ctx->cmd_buffer[ 1 ] )
    {
        ctx->evt_pkt.command_type = *start_ptr;
        start_ptr++;
    }
    memcpy ( ctx->evt_pkt.command, start_ptr, end_ptr - start_ptr );

    // Check and read payload bytes
    start_ptr = end_ptr + 1;
    end_ptr = strstr( start_ptr, BTEZ2_PACKET_PARAM_DELIMITER );
    if ( ctx->evt_pkt.rsp_flag )
    {
        memcpy ( read_len_buf, start_ptr, 4 );
        ctx->evt_pkt.rsp_result = hex_to_int16 ( read_len_buf );
        start_ptr = start_ptr + 5;
    }
    if ( NULL != end_ptr )
    {
        if ( ( end_ptr - &ctx->cmd_buffer[ 6 ] ) > BTEZ2_PAYLOAD_BUFFER_SIZE )
        {
            return BTEZ2_ERROR;
        }
        memcpy ( ctx->evt_pkt.payload, start_ptr, read_len - ( start_ptr - &ctx->cmd_buffer[ 6 ] - 1 ) );
    }
    return BTEZ2_OK;
}

// ------------------------------------------------------------------------- END
