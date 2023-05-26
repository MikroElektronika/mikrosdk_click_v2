/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "uartmux.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uartmux_cfg_setup ( uartmux_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->inh = HAL_PIN_NC;
    cfg->a   = HAL_PIN_NC;
    cfg->b = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

UARTMUX_RETVAL uartmux_init ( uartmux_t *ctx, uartmux_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 
    digital_out_init( &ctx->inh, cfg->inh );
    digital_out_init( &ctx->a, cfg->a );
    digital_out_init( &ctx->b, cfg->b );

    return UARTMUX_OK;
}

void uartmux_generic_write ( uartmux_t *ctx, char *data_buf, uint16_t data_len, uartmux_channel_t *channel )
{
    digital_out_write( &ctx->a, channel->state_a );
    digital_out_write( &ctx->b, channel->state_b );

    uart_write( &ctx->uart, data_buf, data_len );
}

int32_t uartmux_generic_read ( uartmux_t *ctx, char *data_buf, uint16_t max_len, uartmux_channel_t *channel )
{
    digital_out_write( &ctx->a, channel->state_a );
    digital_out_write( &ctx->b, channel->state_b );

    return uart_read( &ctx->uart, data_buf, max_len );
}

void uartmux_set_inhibit_communication ( uartmux_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->inh, state );
}

void uartmux_choose_channel ( uartmux_t *ctx, uartmux_channel_t *channel )
{
    digital_out_write( &ctx->a, channel->state_a );
    digital_out_write( &ctx->b, channel->state_b );
}

// ------------------------------------------------------------------------- END

