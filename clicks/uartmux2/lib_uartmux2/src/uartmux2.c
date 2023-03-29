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
 * @file uartmux2.c
 * @brief UART MUX 2 Click Driver.
 */

#include "uartmux2.h"

void uartmux2_cfg_setup ( uartmux2_cfg_t *cfg ) {
    // Communication gpio pins

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins

    cfg->off   = HAL_PIN_NC;
    cfg->a1 = HAL_PIN_NC;
    cfg->a0   = HAL_PIN_NC;
    cfg->on = HAL_PIN_NC;
    cfg->inv = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t uartmux2_init ( uartmux2_t *ctx, uartmux2_cfg_t *cfg ) {
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
    digital_out_init( &ctx->off, cfg->off );
    digital_out_init( &ctx->a1, cfg->a1 );
    digital_out_init( &ctx->a0, cfg->a0 );
    digital_out_init( &ctx->on, cfg->on );

    // Input pins
    digital_in_init( &ctx->inv, cfg->inv );

    return UART_SUCCESS;
}

void uartmux2_default_cfg ( uartmux2_t *ctx ) {

    uartmux2_set_operation_mode( ctx, UARTMUX2_OP_MODE_NORMAL );

    uartmux2_set_channel( ctx, UARTMUX2_CHANNEL_0 );
}

err_t uartmux2_generic_write ( uartmux2_t *ctx, char *data_buf, uint16_t len ) {
    return uart_write( &ctx->uart, data_buf, len );
}

err_t uartmux2_generic_read ( uartmux2_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

err_t uartmux2_set_operation_mode ( uartmux2_t *ctx, uint8_t op_mode ) {
    err_t status;
    
    status = UARTMUX2_SUCCESS;
    
    if ( op_mode == UARTMUX2_OP_MODE_NORMAL ) {
        digital_out_high( &ctx->off );
        digital_out_high( &ctx->on );    
    } else if ( op_mode == UARTMUX2_OP_MODE_POWER_DOWN ) {
        digital_out_high( &ctx->off );
        digital_out_low( &ctx->on );   
    } else {
        status = UARTMUX2_ERROR;    
    }
    
    return status;
}

err_t uartmux2_set_channel ( uartmux2_t *ctx, uint8_t mux_ch ) {
    err_t status;
    
    status = UARTMUX2_SUCCESS;
    
    switch ( mux_ch ) {
        case UARTMUX2_CHANNEL_0: {
            digital_out_low( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case UARTMUX2_CHANNEL_1: {
            digital_out_low( &ctx->a1 );
            digital_out_high( &ctx->a0 ); 
            break;
        }
        case UARTMUX2_CHANNEL_2: {
            digital_out_high( &ctx->a1 );
            digital_out_low( &ctx->a0 );
            break;
        }
        case UARTMUX2_CHANNEL_3: {
            digital_out_high( &ctx->a1 );
            digital_out_high( &ctx->a0 );
            break;
        }
        default: {
            status = UARTMUX2_ERROR;
            break;
        }
    }
    
    return status;
}

err_t uartmux2_send_data ( uartmux2_t *ctx, char *tx_data ) {
    char tmp_buf[ 100 ];
    uint8_t len;
    err_t status;
    
    status = UARTMUX2_SUCCESS;

    memset( tmp_buf, 0, 100 );

    len = strlen( tx_data );

    strncpy( tmp_buf, tx_data, len );
    
    for ( uint8_t cnt = 0; cnt < len; cnt ++ ) {
        status |= uartmux2_generic_write( ctx, &tmp_buf[ cnt ], 1 );
    }
    
    return status;
}

uint8_t uartmux2_get_inv_status ( uartmux2_t *ctx ) {
     return digital_in_read( &ctx->inv );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
