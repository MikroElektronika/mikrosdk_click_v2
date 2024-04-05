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
 * @file lr9.c
 * @brief LR 9 Click Driver.
 */

#include "lr9.h"

void lr9_cfg_setup ( lr9_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bt  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t lr9_init ( lr9_t *ctx, lr9_cfg_t *cfg ) 
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
    digital_out_init( &ctx->bt, cfg->bt );
    digital_out_init( &ctx->rst, cfg->rst );

    return UART_SUCCESS;
}

void lr9_hw_reset ( lr9_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void lr9_set_boot_pin ( lr9_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->bt, state );
}

err_t lr9_generic_write ( lr9_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t lr9_generic_read ( lr9_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t lr9_write_command ( lr9_t *ctx, uint8_t *command, uint8_t *param ) 
{
    err_t err_flag = lr9_generic_write( ctx, LR9_CMD_AT, strlen( LR9_CMD_AT ) );
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr9_generic_write( ctx, command, strlen( command ) );
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SET_VAL_CMD, 1 );
    err_flag |= lr9_generic_write( ctx, param, strlen( param ) );
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_END_CMD, strlen( LR9_SYMBOL_END_CMD ) );
    return err_flag;
}

err_t lr9_inquire_command ( lr9_t *ctx, uint8_t *command, lr9_en_set_t en_set ) 
{
    err_t err_flag = lr9_generic_write( ctx, LR9_CMD_AT, strlen( LR9_CMD_AT ) );
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_PREFIX_CMD, 1 );
    err_flag |= lr9_generic_write( ctx, command, strlen( command ) );
    if ( en_set == LR9_EQUAL_ENABLE )
    {
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SET_VAL_CMD, 1 );
    }
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_QUERY, 1 );
    err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_END_CMD, strlen( LR9_SYMBOL_END_CMD ) );
    return err_flag;
}

err_t lr9_send_data_frame ( lr9_t *ctx, uint8_t confirm, uint8_t nbtrials, uint8_t *data_frame ) 
{
    err_t err_flag = LR9_ERROR;
    uint8_t len = strlen( data_frame );
    if ( ( LR9_DATA_FRAME_MAX > len ) && 
         ( LR9_DTRX_UNCONFIG_DATA >= confirm ) && 
         ( LR9_NB_TRIALS_MAX >= nbtrials ) )
    {
        err_flag = lr9_generic_write( ctx, LR9_CMD_AT, strlen( LR9_CMD_AT ) );
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_PREFIX_CMD, 1 );
        err_flag |= lr9_generic_write( ctx, LR9_CMD_DTRX, strlen( LR9_CMD_DTRX ) );
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SET_VAL_CMD, 1 );
        if ( LR9_DTRX_CONFIG_DATA == confirm )
        {
            err_flag |= lr9_generic_write( ctx, LR9_DTRX_CONFIG, strlen( LR9_DTRX_CONFIG ) );
        }
        else 
        {
            err_flag |= lr9_generic_write( ctx, LR9_DTRX_UNCONFIG, strlen( LR9_DTRX_UNCONFIG ) );
        }
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SEPARATOR, strlen( LR9_SYMBOL_SEPARATOR ) );

        uint8_t ascii_val[ 2 ] = { 48, 48 };
        if ( nbtrials > 9 )
        {
            ascii_val[ 0 ] += nbtrials % 10;
            ascii_val[ 1 ] += nbtrials;
            err_flag |= lr9_generic_write( ctx, ascii_val, 2 );
        }
        else 
        {
            ascii_val[ 0 ] += nbtrials;
            err_flag |= lr9_generic_write( ctx, ascii_val, 1 );
        }
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SEPARATOR, strlen( LR9_SYMBOL_SEPARATOR ) );

        ascii_val[ 0 ] = 48;
        ascii_val[ 0 ] += len;
        err_flag |= lr9_generic_write( ctx, ascii_val, 1 );
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_SEPARATOR, strlen( LR9_SYMBOL_SEPARATOR ) );
        err_flag |= lr9_generic_write( ctx, data_frame, strlen( data_frame ) );
        err_flag |= lr9_generic_write( ctx, LR9_SYMBOL_END_CMD, strlen( LR9_SYMBOL_END_CMD ) );
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
