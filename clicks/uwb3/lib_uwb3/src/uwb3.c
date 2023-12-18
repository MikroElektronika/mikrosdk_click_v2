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
 * @file uwb3.c
 * @brief UWB 3 Click Driver.
 */

#include "uwb3.h"

void uwb3_cfg_setup ( uwb3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t uwb3_init ( uwb3_t *ctx, uwb3_cfg_t *cfg ) 
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
    digital_out_init ( &ctx->rst, cfg->rst );
    
    uwb3_reset_device ( ctx );
    
    // Dummy write
    uwb3_send_cmd ( ctx, UWB3_CMD_HELP );
    Delay_1sec ( );
    
    return UART_SUCCESS;
}

err_t uwb3_generic_write ( uwb3_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t uwb3_generic_read ( uwb3_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void uwb3_send_cmd ( uwb3_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return = '\r';
    uart_clear ( &ctx->uart );
    while ( *cmd )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    uart_write( &ctx->uart, &carriage_return, 1 );
    Delay_100ms ( );
}

void uwb3_send_cmd_with_parameter ( uwb3_t *ctx, uint8_t *cmd, uint8_t *param )
{
    uint8_t carriage_return = '\r';
    uint8_t delimiter = ' ';
    uart_clear ( &ctx->uart );
    while ( *cmd )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    uart_write( &ctx->uart, &delimiter, 1 );
    while ( *param )
    {
        uart_write( &ctx->uart, param, 1 );
        param++;
    }
    uart_write( &ctx->uart, &carriage_return, 1 );
    Delay_100ms ( );
}

void uwb3_set_rst_pin ( uwb3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void uwb3_reset_device ( uwb3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

// ------------------------------------------------------------------------- END
