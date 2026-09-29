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
 * @file ble2.c
 * @brief BLE2 Click Driver.
 */

#include "ble2.h"
#include <string.h>

void ble2_cfg_setup ( ble2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->con = HAL_PIN_NC;
    cfg->wake_sw = HAL_PIN_NC;
    cfg->cmd = HAL_PIN_NC;

    cfg->baud_rate     = BLE2_UART_BAUD_RATE;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t ble2_init ( ble2_t *ctx, ble2_cfg_t *cfg ) 
{
    uart_config_t uart_cfg;
    uint8_t dummy_read = 0;

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
    digital_out_init( &ctx->wake_sw, cfg->wake_sw );
    digital_out_init( &ctx->cmd, cfg->cmd );
    digital_out_low( &ctx->wake_sw );
    digital_out_low( &ctx->cmd );

    // Input pins
    digital_in_init( &ctx->con, cfg->con );

    // Start the non-blocking UART receive path before waking the module.
    uart_read( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t ble2_default_cfg ( ble2_t *ctx ) 
{
    // UART data is interpreted as commands while CMD/MLDP is low.
    ble2_set_mode_pin( ctx, BLE2_MODE_COMMAND );

    // WAKE_SW must remain high while the module is active.
    ble2_set_wake_pin( ctx, BLE2_WAKE_ACTIVE );

    return BLE2_OK;
}

err_t ble2_generic_write ( ble2_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t ble2_generic_read ( ble2_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void ble2_set_wake_pin ( ble2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wake_sw, state );
}

void ble2_set_mode_pin ( ble2_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cmd, state );
}

uint8_t ble2_get_connection_pin ( ble2_t *ctx )
{
    return digital_in_read( &ctx->con );
}

err_t ble2_cmd_run ( ble2_t *ctx, uint8_t *cmd )
{
    uint8_t terminator = BLE2_CMD_TERMINATOR;
    uint16_t cmd_len = ( uint16_t ) strlen( ( char * ) cmd );

    if ( 0 > ble2_generic_write( ctx, cmd, cmd_len ) )
    {
        return BLE2_ERROR;
    }

    if ( 0 > ble2_generic_write( ctx, &terminator, 1 ) )
    {
        return BLE2_ERROR;
    }

    return BLE2_OK;
}

err_t ble2_cmd_set ( ble2_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint16_t cmd_len = ( uint16_t ) strlen( ( char * ) cmd );
    uint16_t value_len = ( uint16_t ) strlen( ( char * ) value );

    // Reserve space for the prefix, separator, and string end.
    if ( BLE2_CMD_BUFFER_SIZE < ( cmd_len + value_len + 3 ) )
    {
        return BLE2_ERROR;
    }

    ctx->cmd_buffer[ 0 ] = BLE2_CMD_PREFIX_SET;
    strcpy( ( char * ) &ctx->cmd_buffer[ 1 ], ( char * ) cmd );
    ctx->cmd_buffer[ cmd_len + 1 ] = BLE2_CMD_SEPARATOR;
    strcpy( ( char * ) &ctx->cmd_buffer[ cmd_len + 2 ], ( char * ) value );

    return ble2_cmd_run( ctx, ctx->cmd_buffer );
}

err_t ble2_cmd_get ( ble2_t *ctx, uint8_t *cmd )
{
    uint16_t cmd_len = ( uint16_t ) strlen( ( char * ) cmd );

    // Reserve space for the prefix and string end.
    if ( BLE2_CMD_BUFFER_SIZE < ( cmd_len + 2 ) )
    {
        return BLE2_ERROR;
    }

    ctx->cmd_buffer[ 0 ] = BLE2_CMD_PREFIX_GET;
    strcpy( ( char * ) &ctx->cmd_buffer[ 1 ], ( char * ) cmd );

    return ble2_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
