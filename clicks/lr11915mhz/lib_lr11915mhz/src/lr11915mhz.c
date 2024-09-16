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
 * @file lr11915mhz.c
 * @brief LR 11 915MHz Click Driver.
 */

#include "lr11915mhz.h"

void lr11915mhz_cfg_setup ( lr11915mhz_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t lr11915mhz_init ( lr11915mhz_t *ctx, lr11915mhz_cfg_t *cfg ) 
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

err_t lr11915mhz_generic_write ( lr11915mhz_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t lr11915mhz_generic_read ( lr11915mhz_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void lr11915mhz_set_rst_pin ( lr11915mhz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void lr11915mhz_reset_device ( lr11915mhz_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void lr11915mhz_set_cts_pin ( lr11915mhz_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t lr11915mhz_get_rts_pin ( lr11915mhz_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void lr11915mhz_cmd_run ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    if ( NULL != param )
    {
        strcat( ctx->cmd_buffer, param );
    }
    strcat( ctx->cmd_buffer, carriage_return );
    lr11915mhz_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void lr11915mhz_cmd_set ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param_id, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, param_id );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );
    lr11915mhz_cmd_run( ctx, ctx->cmd_buffer, NULL );
}

void lr11915mhz_cmd_get ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param_id )
{
    uint8_t check_char[ 2 ] = { '?', 0 };
    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, param_id );
    strcat( ctx->cmd_buffer, check_char );
    lr11915mhz_cmd_run( ctx, cmd, NULL );
}

void lr11915mhz_cmd_help ( lr11915mhz_t *ctx, uint8_t *cmd, uint8_t *param_id )
{
    uint8_t check_char[ 2 ] = { '?', 0 };
    lr11915mhz_cmd_set( ctx, cmd, param_id, check_char );
}

// ------------------------------------------------------------------------- END
