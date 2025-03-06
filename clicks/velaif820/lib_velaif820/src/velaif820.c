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
 * @file velaif820.c
 * @brief Vela IF820 Click Driver.
 */

#include "velaif820.h"
#include "conversions.h"
#include "generic_pointer.h"

void velaif820_cfg_setup ( velaif820_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->hwe = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->spp = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t velaif820_init ( velaif820_t *ctx, velaif820_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->spp, cfg->spp );
    digital_out_low ( &ctx->rts );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->spp );

    // Input pins
    digital_in_init( &ctx->hwe, cfg->hwe );
    digital_in_init( &ctx->cts, cfg->cts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t velaif820_generic_write ( velaif820_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    uint32_t timeout_cnt = 0;
    while ( !velaif820_get_hwe_pin ( ctx ) )
    {
        if ( ++timeout_cnt > VELAIF820_CMD_TIMEOUT_5000MS )
        {
            return VELAIF820_ERROR_TIMEOUT;
        }
        Delay_1ms ( );
    }
    uart_write( &ctx->uart, data_in, len );
    Delay_100ms ( );
    return VELAIF820_OK;
}

err_t velaif820_generic_read ( velaif820_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void velaif820_set_rst_pin ( velaif820_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void velaif820_reset_device ( velaif820_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void velaif820_set_rts_pin ( velaif820_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rts, state );
}

uint8_t velaif820_get_cts_pin ( velaif820_t *ctx )
{
    return digital_in_read ( &ctx->cts );
}

uint8_t velaif820_get_hwe_pin ( velaif820_t *ctx )
{
    return digital_in_read ( &ctx->hwe );
}

void velaif820_set_cmd_mode ( velaif820_t *ctx )
{
    digital_out_high ( &ctx->spp );
}

void velaif820_set_data_mode ( velaif820_t *ctx )
{
    digital_out_low ( &ctx->spp );
}

void velaif820_cmd_action ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, VELAIF820_PACKET_CMD_ACTION );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, VELAIF820_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, VELAIF820_PACKET_END );
    velaif820_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void velaif820_cmd_set ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, VELAIF820_PACKET_CMD_SET );
    strcat( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, VELAIF820_PACKET_PARAM_DELIMITER );
    strcat( ctx->cmd_buffer, params );
    strcat( ctx->cmd_buffer, VELAIF820_PACKET_END );
    velaif820_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void velaif820_cmd_get ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, VELAIF820_PACKET_CMD_GET );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, VELAIF820_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, VELAIF820_PACKET_END );
    velaif820_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

void velaif820_cmd_profile ( velaif820_t *ctx, uint8_t *cmd, uint8_t *params )
{
    strcpy( ctx->cmd_buffer, VELAIF820_PACKET_CMD_PROFILE );
    strcat( ctx->cmd_buffer, cmd );
    if ( NULL != params )
    {
        strcat( ctx->cmd_buffer, VELAIF820_PACKET_PARAM_DELIMITER );
        strcat( ctx->cmd_buffer, params );
    }
    strcat( ctx->cmd_buffer, VELAIF820_PACKET_END );
    velaif820_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
}

err_t velaif820_read_packet ( velaif820_t *ctx )
{
    uint32_t timeout_cnt = 0;
    uint16_t read_cnt = 0;
    uint16_t read_len = 0;
    uint8_t read_len_buf[ 5 ] = { 0 };
    uint8_t * __generic_ptr start_ptr = NULL;
    uint8_t * __generic_ptr end_ptr = NULL;
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
        if ( ++timeout_cnt >= VELAIF820_RSP_TIMEOUT_1000MS )
        {
            return VELAIF820_ERROR_TIMEOUT;
        }
    }
    Delay_10ms( );

    // Read packet type and length
    if ( 6 != uart_read( &ctx->uart, &ctx->cmd_buffer[ 1 ], 6 ) )
    {
        return VELAIF820_ERROR;
    }

    // Checking packet type and delimiter byte
    if ( ( ( 'R' != ctx->cmd_buffer[ 1 ] ) && ( 'E' != ctx->cmd_buffer[ 1 ] ) ) || 
         ( ',' != ctx->cmd_buffer[ 2 ] ) )
    {
        return VELAIF820_ERROR;
    }

    // Extracting packet length
    memcpy ( read_len_buf, &ctx->cmd_buffer[ 3 ], 4 );
    read_len = hex_to_int16 ( read_len_buf );
    if ( read_len > ( VELAIF820_PAYLOAD_BUFFER_SIZE - 10 ) )
    {
        return VELAIF820_ERROR;
    }
    for ( read_cnt = 0; read_cnt < read_len; read_cnt++ )
    {
        Delay_1ms( ); // The higher the payload, the more we wait for all bytes to arrive
    }
    
    // Read packet command and payload
    if ( read_len != uart_read( &ctx->uart, &ctx->cmd_buffer[ 7 ], read_len ) )
    {
        return VELAIF820_ERROR;
    }

    // Read and check packet end bytes
    if ( 2 != uart_read( &ctx->uart, &ctx->cmd_buffer[ read_len + 7 ], 2 ) )
    {
        return VELAIF820_ERROR;
    }
    if ( ( '\r' != ctx->cmd_buffer[ read_len + 7 ] ) || 
         ( '\n' != ctx->cmd_buffer[ read_len + 8 ] ) )
    {
        return VELAIF820_ERROR;
    }
    
    // Output packet type
    if ( 'R' == ctx->cmd_buffer[ 1 ] )
    {
        ctx->evt_pkt.rsp_flag = VELAIF820_PACKET_TYPE_RESPONSE;
    }
    else
    {
        ctx->evt_pkt.rsp_flag = VELAIF820_PACKET_TYPE_EVENT;
    }
    
    // Extract command code
    start_ptr = &ctx->cmd_buffer[ 8 ];
    end_ptr = strstr( &ctx->cmd_buffer[ 8 ], VELAIF820_PACKET_PARAM_DELIMITER );
    if ( NULL == end_ptr )
    {
        end_ptr = strstr( &ctx->cmd_buffer[ 8 ], VELAIF820_PACKET_END );
    }
    if ( ( NULL == end_ptr ) || ( ( end_ptr - start_ptr ) > VELAIF820_CMD_CODE_BUFFER_SIZE ) )
    {
        return VELAIF820_ERROR;
    }
    memcpy ( ctx->evt_pkt.command, start_ptr, end_ptr - start_ptr );

    // Check and read payload bytes
    start_ptr = end_ptr + 1;
    end_ptr = strstr( start_ptr, VELAIF820_PACKET_PARAM_DELIMITER );
    if ( ctx->evt_pkt.rsp_flag )
    {
        memcpy ( read_len_buf, start_ptr, 4 );
        ctx->evt_pkt.rsp_result = hex_to_int16 ( read_len_buf );
        start_ptr = start_ptr + 5;
    }
    if ( NULL != end_ptr )
    {
        if ( ( end_ptr - &ctx->cmd_buffer[ 6 ] ) > VELAIF820_PAYLOAD_BUFFER_SIZE )
        {
            return VELAIF820_ERROR;
        }
        memcpy ( ctx->evt_pkt.payload, start_ptr, read_len - ( start_ptr - &ctx->cmd_buffer[ 6 ] - 1 ) );
    }
    return VELAIF820_OK;
}

// ------------------------------------------------------------------------- END
