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
 * @file wizfi360.c
 * @brief WIZFI360 Click Driver.
 */

#include "wizfi360.h"

void wizfi360_cfg_setup ( wizfi360_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bt  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->wkp = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wizfi360_init ( wizfi360_t *ctx, wizfi360_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->wkp, cfg->wkp );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    wizfi360_set_rst_pin( ctx, WIZFI360_PIN_STATE_HIGH );
    wizfi360_set_bt_pin( ctx, WIZFI360_PIN_STATE_HIGH );
    wizfi360_wake_up( ctx );

    return UART_SUCCESS;
}

void wizfi360_set_rst_pin ( wizfi360_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

void wizfi360_set_bt_pin ( wizfi360_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->bt, state );
}

void wizfi360_wake_up ( wizfi360_t *ctx ) 
{
    digital_out_high( &ctx->wkp );
}

void wizfi360_standby ( wizfi360_t *ctx ) 
{
    digital_out_low( &ctx->wkp );
}

uint8_t wizfi360_request_to_send ( wizfi360_t *ctx ) 
{
    return digital_in_read( &ctx->rts );
}

void wizfi360_clear_to_send ( wizfi360_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->cts, state );
}

err_t wizfi360_generic_write ( wizfi360_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wizfi360_generic_read ( wizfi360_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t wizfi360_write_command ( wizfi360_t *ctx, uint8_t *command )
{
    err_t err_flag = wizfi360_generic_write( ctx, command, strlen( command ) );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_END, strlen( WIZFI360_PREFIX_SYMB_END ) );
    return err_flag;
}

err_t wizfi360_write_cmd_param ( wizfi360_t *ctx, uint8_t *command, uint8_t *prefix, uint8_t *param )
{
    err_t err_flag = wizfi360_generic_write( ctx, command, strlen( command ) );
    err_flag |= wizfi360_generic_write( ctx, prefix, strlen( prefix ) );
    err_flag |= wizfi360_generic_write( ctx, param, strlen( param ) );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_END, strlen( WIZFI360_PREFIX_SYMB_END ) );
    return err_flag;
}

err_t wizfi360_inquire_command ( wizfi360_t *ctx, uint8_t *command ) 
{
    err_t err_flag = wizfi360_generic_write( ctx, command, strlen( command ) );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_QUERY, 1 );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_END, strlen( WIZFI360_PREFIX_SYMB_END ) );
    return err_flag;
}

err_t wizfi360_send_message ( wizfi360_t *ctx, uint8_t *message )
{
    err_t err_flag = wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_SPACE, strlen( WIZFI360_PREFIX_SYMB_SPACE ) );
    err_flag |= wizfi360_generic_write( ctx, message, strlen( message ) );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_PREFIX_SYMB_SPACE, strlen( WIZFI360_PREFIX_SYMB_SPACE ) );
    err_flag |= wizfi360_generic_write( ctx, WIZFI360_MESSAGE_END, strlen( WIZFI360_MESSAGE_END ) );
    return err_flag;
}

// ------------------------------------------------------------------------- END
