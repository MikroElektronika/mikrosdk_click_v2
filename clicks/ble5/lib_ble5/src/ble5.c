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
 * @file ble5.c
 * @brief BLE 5 Click Driver.
 */

#include "ble5.h"

void ble5_cfg_setup ( ble5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wp0 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->wp1 = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ble5_init ( ble5_t *ctx, ble5_cfg_t *cfg ) 
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
    digital_out_init( &ctx->wp0, cfg->wp0 );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->wp1, cfg->wp1 );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    // Hold reset until the wake-up outputs have been configured.
    digital_out_low( &ctx->rst );

    return UART_SUCCESS;
}

err_t ble5_default_cfg ( ble5_t *ctx ) 
{
    // Apply the module startup levels required for normal operation.
    ble5_set_wp0_pin( ctx, 1 );
    ble5_set_wp1_pin( ctx, 1 );
    ble5_set_rts_pin( ctx, 1 );
    ble5_device_reset( ctx );

    return BLE5_OK;
}

err_t ble5_generic_write ( ble5_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ble5_generic_read ( ble5_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t ble5_cmd_run ( ble5_t *ctx, uint8_t *cmd )
{
    return ble5_cmd_set( ctx, cmd, NULL, 0 );
}

err_t ble5_cmd_set ( ble5_t *ctx, uint8_t *cmd, uint8_t *params, uint16_t len )
{
    uint8_t packet[ BLE5_CMD_BUFFER_SIZE ];
    uint16_t cmd_len = 0;
    uint16_t packet_len;
    uint16_t offset;
    uint16_t timeout_cnt = 0;
    err_t written;

    if ( ( NULL == cmd ) || ( ( 0 != len ) && ( NULL == params ) ) )
    {
        return BLE5_ERROR;
    }
    while ( ( cmd_len < BLE5_CMD_BUFFER_SIZE ) && ( 0 != cmd[ cmd_len ] ) )
    {
        cmd_len++;
    }
    if ( ( 0 == cmd_len ) ||
         ( ( uint32_t ) cmd_len + len + BLE5_PACKET_HEADER_SIZE + BLE5_PACKET_END_SIZE +
           ( 0 != len ) > BLE5_CMD_BUFFER_SIZE ) )
    {
        return BLE5_ERROR;
    }

    packet_len = cmd_len + len + BLE5_PACKET_HEADER_SIZE + BLE5_PACKET_END_SIZE + ( 0 != len );
    // Only the packet length uses little-endian order. Copy parameters unchanged.
    packet[ 0 ] = ( uint8_t ) packet_len;
    packet[ 1 ] = ( uint8_t ) ( packet_len >> 8 );
    packet[ 2 ] = 0;
    offset = BLE5_PACKET_HEADER_SIZE;
    memcpy( &packet[ offset ], cmd, cmd_len );
    offset += cmd_len;
    if ( 0 != len )
    {
        packet[ offset++ ] = ' ';
        memcpy( &packet[ offset ], params, len );
        offset += len;
    }
    packet[ offset++ ] = '\r';
    packet[ offset ] = '\n';

    offset = 0;
    while ( offset < packet_len )
    {
        written = ble5_generic_write( ctx, &packet[ offset ], packet_len - offset );
        if ( written > 0 )
        {
            if ( written > packet_len - offset )
            {
                return BLE5_ERROR;
            }
            offset += written;
        }
        else
        {
            // The nonblocking UART may need time to free transmit-buffer space.
            if ( ++timeout_cnt >= 1000 )
            {
                return BLE5_ERROR_TIMEOUT;
            }
            Delay_1ms( );
        }
    }
    return BLE5_OK;
}

void ble5_device_reset ( ble5_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    // Discard incomplete packets before the firmware sends its new ready event.
    uart_clear( &ctx->uart );
    digital_out_high( &ctx->rst );
}

void ble5_set_wp0_pin ( ble5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wp0, state );
}

void ble5_set_wp1_pin ( ble5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wp1, state );
}

void ble5_set_rts_pin ( ble5_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rts, state );
}

uint8_t ble5_get_cts_pin ( ble5_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

// ------------------------------------------------------------------------- END
