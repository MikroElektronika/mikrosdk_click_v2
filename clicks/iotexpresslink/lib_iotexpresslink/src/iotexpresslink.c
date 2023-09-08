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
 * @file iotexpresslink.c
 * @brief IoT ExpressLink Click Driver.
 */

#include "iotexpresslink.h"

void iotexpresslink_cfg_setup ( iotexpresslink_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst    = HAL_PIN_NC;
    cfg->event  = HAL_PIN_NC;
    cfg->wake   = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t iotexpresslink_init ( iotexpresslink_t *ctx, iotexpresslink_cfg_t *cfg ) 
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
    digital_out_high( &ctx->rst );

    // Input pins
    digital_in_init( &ctx->event, cfg->event );
    digital_in_init( &ctx->wake, cfg->wake );
    
    // Perform a dummy read in order to enable RX interrupt
    uint8_t dummy = 0;
    iotexpresslink_generic_read ( ctx, &dummy, 1 );

    return UART_SUCCESS;
}

err_t iotexpresslink_generic_write ( iotexpresslink_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t iotexpresslink_generic_read ( iotexpresslink_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void iotexpresslink_send_cmd ( iotexpresslink_t *ctx, uint8_t *cmd )
{
    uint8_t eol[ 2 ] = { 13, 10 };
    uart_write( &ctx->uart, cmd, strlen ( cmd ) );
    uart_write( &ctx->uart, eol, 2 );
}

void iotexpresslink_enable_device ( iotexpresslink_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

void iotexpresslink_disable_device ( iotexpresslink_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

void iotexpresslink_reset_device ( iotexpresslink_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

uint8_t iotexpresslink_get_event_pin ( iotexpresslink_t *ctx )
{
    return digital_in_read ( &ctx->event );
}

uint8_t iotexpresslink_get_wake_pin ( iotexpresslink_t *ctx )
{
    return digital_in_read ( &ctx->wake );
}

// ------------------------------------------------------------------------- END
