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
 * @file usbuart4.c
 * @brief USB UART 4 Click Driver.
 */

#include "usbuart4.h"

void usbuart4_cfg_setup ( usbuart4_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cts = HAL_PIN_NC;
    cfg->slp   = HAL_PIN_NC;
    cfg->pwr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t usbuart4_init ( usbuart4_t *ctx, usbuart4_cfg_t *cfg ) {
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->pwr, cfg->pwr );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

void usbuart4_generic_write ( usbuart4_t *ctx, char *data_buf, uint16_t len ) {
    uart_write( &ctx->uart, data_buf, len );
}

uint32_t usbuart4_generic_read ( usbuart4_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void usbuart4_pwr_ctrl ( usbuart4_t *ctx, uint8_t state ) {
    if ( state == 1 ) {
        digital_out_high( &ctx->pwr );
    } else {
        digital_out_low( &ctx->pwr );
    }
}

void usbuart4_set_cts ( usbuart4_t *ctx, uint8_t state ) {
    if ( state == 1 ) {
        digital_out_high( &ctx->cts );
    } else {
        digital_out_low( &ctx->cts );
    }
}

void usbuart4_set_mode ( usbuart4_t *ctx, uint8_t mode ) {
    if ( mode == 1 ) {
        digital_out_high( &ctx->slp );
    } else {
        digital_out_low( &ctx->slp );
    }
}

uint8_t usbuart4_get_rts ( usbuart4_t *ctx ) {
   return  digital_in_read( &ctx->rts );
}

void usbuart4_send_command ( usbuart4_t *ctx, char *command ) {
    char tmp_buf[ 100 ];
    uint8_t len;

    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );

    usbuart4_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

// ------------------------------------------------------------------------- END
