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
 * @file lr10.c
 * @brief LR 10 Click Driver.
 */

#include "lr10.h"

void lr10_cfg_setup ( lr10_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t lr10_init ( lr10_t *ctx, lr10_cfg_t *cfg ) 
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

    return UART_SUCCESS;
}

void lr10_hw_reset ( lr10_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

err_t lr10_generic_write ( lr10_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t lr10_generic_read ( lr10_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t lr10_write_cmd ( lr10_t *ctx, uint8_t *command ) 
{
    err_t err_flag = lr10_generic_write( ctx, LR10_CMD_AT, strlen( LR10_CMD_AT ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, command, strlen( command ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_END_CMD, strlen( LR10_SYMBOL_END_CMD ) );
    return err_flag;
}

err_t lr10_write_cmd_param ( lr10_t *ctx, uint8_t *command, uint8_t *param ) 
{
    err_t err_flag = lr10_generic_write( ctx, LR10_CMD_AT, strlen( LR10_CMD_AT ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, command, strlen( command ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_SET_VAL_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, param, strlen( param ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_END_CMD, strlen( LR10_SYMBOL_END_CMD ) );
    return err_flag;
}

err_t lr10_write_cmd_sub_param ( lr10_t *ctx, uint8_t *command, uint8_t *sub_param, 
                                              uint8_t *param, lr10_en_quote_t en_quote ) 
{
    err_t err_flag = lr10_generic_write( ctx, LR10_CMD_AT, strlen( LR10_CMD_AT ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, command, strlen( command ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_SET_VAL_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, sub_param, strlen( sub_param ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_SPACE, 1 );
    if ( en_quote == LR10_QUOTE_ENABLE )
    {
        err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_QUOTE, strlen( LR10_SYMBOL_QUOTE ) );
    }
    err_flag |= lr10_generic_write( ctx, param, strlen( param ) );
    if ( en_quote == LR10_QUOTE_ENABLE )
    {
        err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_QUOTE, strlen( LR10_SYMBOL_QUOTE ) );
    }
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_END_CMD, strlen( LR10_SYMBOL_END_CMD ) );
    return err_flag;
}

err_t lr10_inquire_cmd ( lr10_t *ctx, uint8_t *command ) 
{
    err_t err_flag = lr10_generic_write( ctx, LR10_CMD_AT, strlen( LR10_CMD_AT ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, command, strlen( command ) );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_SET_VAL_CMD, 1 );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_QUERY, 1 );
    err_flag |= lr10_generic_write( ctx, LR10_SYMBOL_END_CMD, strlen( LR10_SYMBOL_END_CMD ) );
    return err_flag;
}

// ------------------------------------------------------------------------- END
