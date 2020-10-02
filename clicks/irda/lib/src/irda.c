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
 * \file irda.c
 *
 */

#include "irda.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void
irda_cfg_setup( irda_cfg_t *cfg )
{
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->mod    = HAL_PIN_NC;
    cfg->rst    = HAL_PIN_NC;
    cfg->en     = HAL_PIN_NC;

    cfg->baud_rate  = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

irda_err_t
irda_init( irda_t *ctx, irda_cfg_t *cfg )
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
    
    digital_out_init( &ctx->mod, cfg->mod );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->en, cfg->en );

    return IRDA_OK;
}

void
irda_default_cfg( irda_t *ctx )
{
    digital_out_high( &ctx->rst );
    irda_pwr_setup( ctx, IRDA_PWR_ON );
    irda_mode_setup( ctx, IRDA_MODE_DATA );
}

void
irda_mode_setup( irda_t *ctx, irda_mode_t state )
{
    digital_out_write( &ctx->mod, state );
}

void
irda_pwr_setup( irda_t *ctx, irda_pwr_t state )
{
    digital_out_write( &ctx->en, state );
}

void
irda_reset( irda_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_1sec( );
}

void
irda_generic_multiple_send( irda_t *ctx, char *tx_data )
{
    while ( *tx_data )
    {
        uart_write( &ctx->uart, tx_data, 1 );
        *tx_data++;
    }
}

void
irda_generic_multiple_receive( irda_t *ctx, char *rx_data,
                               char termination_char )
{
    char rx_dat;
    int32_t rsp_size;

    rx_dat = termination_char + 1;

    while ( rx_dat != termination_char )
    {
        rsp_size = uart_read( &ctx->uart, &rx_dat, 1 );
        if ( rsp_size != -1 )
        {       
            *rx_data++ = rx_dat;
        }
    }

    *rx_data = '\0';
}

void
irda_generic_single_send( irda_t *ctx, char tx_data )
{
    uart_write( &ctx->uart, &tx_data, 1 );
}

char
irda_generic_single_receive( irda_t *ctx )
{ 
    char rx_data;
    uart_read( &ctx->uart, &rx_data, 1 );
    return rx_data;
}

// ------------------------------------------------------------------------ END
