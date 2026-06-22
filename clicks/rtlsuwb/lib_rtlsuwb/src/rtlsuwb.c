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
 * @file rtlsuwb.c
 * @brief RTLS UWB Click Driver.
 */

#include "rtlsuwb.h"

void rtlsuwb_cfg_setup ( rtlsuwb_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->irq = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t rtlsuwb_init ( rtlsuwb_t *ctx, rtlsuwb_cfg_t *cfg ) 
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
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );

    // Input pins
    digital_in_init( &ctx->irq, cfg->irq );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t rtlsuwb_generic_write ( rtlsuwb_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t rtlsuwb_generic_read ( rtlsuwb_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void rtlsuwb_set_rst_pin ( rtlsuwb_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t rtlsuwb_get_irq_pin ( rtlsuwb_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

void rtlsuwb_reset_device ( rtlsuwb_t *ctx )
{
    uint8_t dummy_read = 0;
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1ms ( );
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_1sec( );
}

void rtlsuwb_cmd_run ( rtlsuwb_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, carriage_return );

    rtlsuwb_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms( );
}

void rtlsuwb_cmd_set ( rtlsuwb_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t space_char[ 2 ] = { ' ', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, space_char );
    strcat( ctx->cmd_buffer, value );

    rtlsuwb_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
