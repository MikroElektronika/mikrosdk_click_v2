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

#include "duallin.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void duallin_cfg_setup ( duallin_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en1 = HAL_PIN_NC;
    cfg->en2 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

DUALLIN_RETVAL duallin_init ( duallin_t *ctx, duallin_cfg_t *cfg )
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

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->en1, cfg->en1 );
    digital_out_init( &ctx->en2, cfg->en2 );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_high( &ctx->en1 );
    digital_out_low( &ctx->en2 );

    return DUALLIN_OK;
}

void duallin_generic_write ( duallin_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int16_t duallin_generic_read ( duallin_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void  duallin_bus1_status ( duallin_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en1, state );
}

void duallin_bus2_status ( duallin_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->en2, state );
}

void duallin_send_command ( duallin_t *ctx, char *command )
{
    for ( uint8_t cnt_len = 0; cnt_len < strlen(command); cnt_len++ )
    {
        duallin_generic_write( ctx, &command[ cnt_len ], 1 );
        Delay_100ms( ); 
    }
}

// ------------------------------------------------------------------------- END

