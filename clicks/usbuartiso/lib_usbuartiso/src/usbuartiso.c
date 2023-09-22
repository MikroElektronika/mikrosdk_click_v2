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
 * @file usbuartiso.c
 * @brief USB-UART ISO Click Driver.
 */

#include "usbuartiso.h"

void usbuartiso_cfg_setup ( usbuartiso_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->slp = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->pwr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t usbuartiso_init ( usbuartiso_t *ctx, usbuartiso_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->pwr, cfg->pwr );

    // Input pins
    digital_in_init( &ctx->slp, cfg->slp );
    digital_in_init( &ctx->rts, cfg->rts );

    return UART_SUCCESS;
}

void usbuartiso_default_cfg ( usbuartiso_t *ctx ) 
{
    usbuartiso_power_on( ctx );
}

err_t usbuartiso_generic_write ( usbuartiso_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t usbuartiso_generic_read ( usbuartiso_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void usbuartiso_power_on ( usbuartiso_t *ctx ) 
{
    digital_out_high( &ctx->pwr );
}

void usbuartiso_power_off ( usbuartiso_t *ctx ) 
{
    digital_out_low( &ctx->pwr );
}

uint8_t usbuartiso_get_slp_ind ( usbuartiso_t *ctx ) 
{
    return digital_in_read( &ctx->slp );
}

uint8_t usbuartiso_request_to_send ( usbuartiso_t *ctx ) 
{
    return digital_in_read( &ctx->rts );
}

void usbuartiso_clear_to_send ( usbuartiso_t *ctx, uint8_t cts ) 
{
    digital_out_write( &ctx->cts, cts );
}

// ------------------------------------------------------------------------- END
