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
 * @file canbus.c
 * @brief CAN Bus Click Driver.
 */

#include "canbus.h"

void canbus_cfg_setup ( canbus_cfg_t *cfg ) {
    // Communication gpio pins
    
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->stb   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t canbus_init ( canbus_t *ctx, canbus_cfg_t *cfg ) {
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
    
    digital_out_init( &ctx->stb, cfg->stb );

    return UART_SUCCESS;
}

err_t canbus_default_cfg ( canbus_t *ctx ) {
    // Click default configuration
    
    canbus_set_high_speed_mode( ctx );
    
    return CANBUS_OK;
}

err_t canbus_generic_write ( canbus_t *ctx, char *data_buf, uint16_t len ) {
    return uart_write( &ctx->uart, data_buf, len );
}

err_t canbus_generic_read ( canbus_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

err_t canbus_set_low_current_standby_mode ( canbus_t *ctx ) {
    digital_out_high( &ctx->stb );
    
    return CANBUS_OK;
}

err_t canbus_set_high_speed_mode ( canbus_t *ctx ) {
    digital_out_low( &ctx->stb );
    
    return CANBUS_OK;
}

err_t canbus_send_data ( canbus_t *ctx, char *tx_data ) {
    char tmp_buf[ 100 ];
    uint8_t len;
    err_t error_flag;

    memset( tmp_buf, 0, 100 );

    len = strlen( tx_data );

    strncpy( tmp_buf, tx_data, len );
    
    for ( uint8_t cnt = 0; cnt < len; cnt ++ ) {
        error_flag |= canbus_generic_write( ctx, &tmp_buf[ cnt ], 1 );
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
