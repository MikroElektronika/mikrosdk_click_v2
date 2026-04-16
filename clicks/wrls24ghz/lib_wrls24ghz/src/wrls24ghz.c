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
 * @file wrls24ghz.c
 * @brief WRLS 2.4GHz Click Driver.
 */

#include "wrls24ghz.h"

void wrls24ghz_cfg_setup ( wrls24ghz_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->status = HAL_PIN_NC;

    cfg->baud_rate     = 19200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wrls24ghz_init ( wrls24ghz_t *ctx, wrls24ghz_cfg_t *cfg ) 
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
    Delay_1ms ( );
    digital_out_high( &ctx->rst );
    Delay_1ms ( );

    // Input pins
    digital_in_init( &ctx->status, cfg->status );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t wrls24ghz_generic_write ( wrls24ghz_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wrls24ghz_generic_read ( wrls24ghz_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void wrls24ghz_set_rst_pin ( wrls24ghz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t wrls24ghz_get_status_pin ( wrls24ghz_t *ctx )
{
    return digital_in_read ( &ctx->status );
}

void wrls24ghz_reset_device ( wrls24ghz_t *ctx )
{
    uint8_t dummy_read = 0;
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    digital_out_low ( &ctx->rst );
    Delay_1ms ( );
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_1sec( );
}

void wrls24ghz_send_cmd ( wrls24ghz_t *ctx, uint8_t *cmd )
{
    wrls24ghz_wake_uart ( ctx );
    wrls24ghz_generic_write( ctx, cmd, strlen ( cmd ) );
    Delay_100ms ( );
}

void wrls24ghz_wake_uart ( wrls24ghz_t *ctx )
{
    uint8_t wake_byte = 0x00;
    wrls24ghz_generic_write( ctx, &wake_byte, 1 );
    Delay_10ms(  );
}

// ------------------------------------------------------------------------- END
