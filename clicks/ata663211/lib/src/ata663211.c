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

#include "ata663211.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ata663211_cfg_setup ( ata663211_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->inh   = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = true;
}

ATA663211_RETVAL ata663211_init ( ata663211_t *ctx, ata663211_cfg_t *cfg )
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

    digital_out_init( &ctx->en, cfg->en );

    // Input pins

    digital_in_init( &ctx->inh, cfg->inh );

    return ATA663211_OK;

}

void ata663211_generic_multi_write ( ata663211_t *ctx, char *data_buf,  uint8_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

void ata663211_generic_multi_read ( ata663211_t *ctx, char *data_buf,  uint8_t len )
{
    uart_read( &ctx->uart, data_buf, len );  
}

char ata663211_generic_single_read ( ata663211_t *ctx )
{
    char rx_data;

    uart_read( &ctx->uart, &rx_data, 1 );   
    
    return rx_data;
}

void ata663211_generic_single_write ( ata663211_t *ctx, char tx_data )
{
    uart_write( &ctx->uart, &tx_data, 1 );
}

void ata663211_wake_up_device ( ata663211_t *ctx )
{
    digital_out_high( &ctx->en );
}

void ata663211_sleep_mode ( ata663211_t *ctx )
{
    digital_out_low( &ctx->en );
}

uint8_t ata663211_check_inh ( ata663211_t *ctx )
{
    return digital_in_read( &ctx->inh );
}

// ------------------------------------------------------------------------- END

