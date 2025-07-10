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
 * @file xportedge.c
 * @brief XPort EDGE Click Driver.
 */

#include "xportedge.h"

void xportedge_cfg_setup ( xportedge_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->dtr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t xportedge_init ( xportedge_t *ctx, xportedge_cfg_t *cfg ) 
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
    digital_in_init( &ctx->dtr, cfg->dtr );
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

err_t xportedge_generic_write ( xportedge_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t xportedge_generic_read ( xportedge_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void xportedge_send_cmd ( xportedge_t *ctx, uint8_t *cmd )
{
    uart_write( &ctx->uart, cmd, strlen ( cmd ) );
    uart_write( &ctx->uart, XPORTEDGE_CMD_ENTER, strlen ( XPORTEDGE_CMD_ENTER ) );
    Delay_100ms( );
}

void xportedge_list_commands ( xportedge_t *ctx )
{
    uart_write( &ctx->uart, XPORTEDGE_CMD_LIST_COMMANDS, strlen ( XPORTEDGE_CMD_LIST_COMMANDS ) );
    Delay_100ms( );
}

void xportedge_send_enter ( xportedge_t *ctx )
{
    uart_write( &ctx->uart, XPORTEDGE_CMD_ENTER, strlen ( XPORTEDGE_CMD_ENTER ) );
    Delay_100ms( );
}

void xportedge_set_rst_pin ( xportedge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void xportedge_set_cts_pin ( xportedge_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t xportedge_get_rts_pin ( xportedge_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

uint8_t xportedge_get_dtr_pin ( xportedge_t *ctx )
{
    return digital_in_read ( &ctx->dtr );
}

void xportedge_reset_device ( xportedge_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

// ------------------------------------------------------------------------- END
