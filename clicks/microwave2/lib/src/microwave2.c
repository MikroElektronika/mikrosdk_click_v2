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

#include "microwave2.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void microwave2_cfg_setup ( microwave2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->da   = HAL_PIN_NC;
    cfg->dl = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_ODD;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
    
}

MICROWAVE2_RETVAL microwave2_init ( microwave2_t *ctx, microwave2_cfg_t *cfg )
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

    // Input pins
    digital_in_init( &ctx->da, cfg->da );
    digital_in_init( &ctx->dl, cfg->dl );

    return MICROWAVE2_OK;
}

void microwave2_generic_multi_write ( microwave2_t *ctx, char *data_buf,  uint8_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t microwave2_generic_read ( microwave2_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

char microwave2_generic_single_read ( microwave2_t *ctx )
{
    uint8_t rx_data;

    uart_read( &ctx->uart, &rx_data, 1 ); 
    
    return rx_data;
}

void microwave2_generic_single_write ( microwave2_t *ctx, char tx_data )
{
    uart_write( &ctx->uart, &tx_data, 1 );
}

uint8_t microwave2_da_state( microwave2_t *ctx )
{
    return digital_in_read( &ctx->da );
}

uint8_t microwave2_dl_state( microwave2_t *ctx )
{
    return digital_in_read( &ctx->dl );
}

// ------------------------------------------------------------------------- END

