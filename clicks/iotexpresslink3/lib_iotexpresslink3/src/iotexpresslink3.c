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
 * @file iotexpresslink3.c
 * @brief IoT ExpressLink 3 Click Driver.
 */

#include "iotexpresslink3.h"

void iotexpresslink3_cfg_setup ( iotexpresslink3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rsn = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wake = HAL_PIN_NC;
    cfg->event = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t iotexpresslink3_init ( iotexpresslink3_t *ctx, iotexpresslink3_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->rst );
    
    // Input pins
    digital_in_init( &ctx->event, cfg->event );
    digital_in_init( &ctx->wake, cfg->wake );
    digital_in_init( &ctx->rsn, cfg->rsn );
    
    // Perform a dummy read in order to enable RX interrupt
    uint8_t dummy = 0;
    iotexpresslink3_generic_read ( ctx, &dummy, 1 );

    return UART_SUCCESS;
}

err_t iotexpresslink3_generic_write ( iotexpresslink3_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t iotexpresslink3_generic_read ( iotexpresslink3_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void iotexpresslink3_send_cmd ( iotexpresslink3_t *ctx, uint8_t *cmd )
{
    uint8_t eol[ 2 ] = { 13, 10 };
    uart_clear( &ctx->uart );
    uart_write( &ctx->uart, cmd, strlen ( cmd ) );
    uart_write( &ctx->uart, eol, 2 );
    Delay_100ms( );
}

void iotexpresslink3_enable_device ( iotexpresslink3_t *ctx )
{
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

void iotexpresslink3_disable_device ( iotexpresslink3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
}

void iotexpresslink3_reset_device ( iotexpresslink3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

uint8_t iotexpresslink3_get_rsn_pin ( iotexpresslink3_t *ctx )
{
    return digital_in_read ( &ctx->rsn );
}

uint8_t iotexpresslink3_get_event_pin ( iotexpresslink3_t *ctx )
{
    return digital_in_read ( &ctx->event );
}

uint8_t iotexpresslink3_get_wake_pin ( iotexpresslink3_t *ctx )
{
    return digital_in_read ( &ctx->wake );
}

// ------------------------------------------------------------------------- END
