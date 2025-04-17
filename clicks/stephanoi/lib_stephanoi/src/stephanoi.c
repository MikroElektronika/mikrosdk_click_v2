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
 * @file stephanoi.c
 * @brief Stephano-I Click Driver.
 */

#include "stephanoi.h"

void stephanoi_cfg_setup ( stephanoi_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t stephanoi_init ( stephanoi_t *ctx, stephanoi_cfg_t *cfg ) 
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
    digital_out_init( &ctx->wup, cfg->wup );
    Delay_100ms( );
    digital_out_low( &ctx->wup );
    digital_out_low( &ctx->cts );
    digital_out_low( &ctx->rst );
    Delay_100ms( );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_100ms( );

    return UART_SUCCESS;
}

err_t stephanoi_generic_write ( stephanoi_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t stephanoi_generic_read ( stephanoi_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void stephanoi_set_wup_pin ( stephanoi_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void stephanoi_set_rst_pin ( stephanoi_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void stephanoi_set_cts_pin ( stephanoi_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t stephanoi_get_rts_pin ( stephanoi_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void stephanoi_reset_device ( stephanoi_t *ctx )
{
    uint8_t dummy_read = 0;
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_1sec( );
}

void stephanoi_cmd_run ( stephanoi_t *ctx, uint8_t *cmd )
{
    uint8_t cr_lf[ 3 ] = { '\r', '\n', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, cr_lf );

    stephanoi_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void stephanoi_cmd_set ( stephanoi_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );

    stephanoi_cmd_run( ctx, ctx->cmd_buffer );
}

void stephanoi_cmd_get ( stephanoi_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, check_char );

    stephanoi_cmd_run( ctx, ctx->cmd_buffer );
}

void stephanoi_cmd_help ( stephanoi_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    stephanoi_cmd_set( ctx, cmd, check_char );
}

// ------------------------------------------------------------------------- END
