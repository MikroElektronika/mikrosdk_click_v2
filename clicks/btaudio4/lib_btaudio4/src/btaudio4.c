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
 * @file btaudio4.c
 * @brief BT Audio 4 Click Driver.
 */

#include "btaudio4.h"

void btaudio4_cfg_setup ( btaudio4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t btaudio4_init ( btaudio4_t *ctx, btaudio4_cfg_t *cfg ) 
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
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cts );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );

    return UART_SUCCESS;
}

err_t btaudio4_generic_write ( btaudio4_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t btaudio4_generic_read ( btaudio4_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void btaudio4_set_rst_pin ( btaudio4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void btaudio4_reset_device ( btaudio4_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void btaudio4_set_cts_pin ( btaudio4_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t btaudio4_get_rts_pin ( btaudio4_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void btaudio4_cmd_run ( btaudio4_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, carriage_return );
    btaudio4_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms( );
    Delay_100ms( );
}

void btaudio4_cmd_set ( btaudio4_t *ctx, uint8_t *param, uint8_t *value )
{
    uint8_t space_char[ 2 ] = { ' ', 0 };
    uint8_t equal_char[ 2 ] = { '=', 0 };
    strcpy( ctx->cmd_buffer, BTAUDIO4_CMD_SET );
    strcat( ctx->cmd_buffer, space_char );
    strcat( ctx->cmd_buffer, param );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );
    btaudio4_cmd_run( ctx, ctx->cmd_buffer );
}

void btaudio4_cmd_get ( btaudio4_t *ctx, uint8_t *param )
{
    uint8_t space_char[ 2 ] = { ' ', 0 };
    strcpy( ctx->cmd_buffer, BTAUDIO4_CMD_GET );
    strcat( ctx->cmd_buffer, space_char );
    strcat( ctx->cmd_buffer, param );
    btaudio4_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
