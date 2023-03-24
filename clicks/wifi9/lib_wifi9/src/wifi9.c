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

#include "wifi9.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void wifi9_cfg_setup ( wifi9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->adr   = HAL_PIN_NC;
     cfg->rst = HAL_PIN_NC;
     cfg->rts   = HAL_PIN_NC;
     cfg->mcr = HAL_PIN_NC;
     cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

WIFI9_RETVAL wifi9_init ( wifi9_t *ctx, wifi9_cfg_t *cfg )
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

     digital_out_init( &ctx->adr, cfg->adr );
     digital_out_init( &ctx->rst, cfg->rst );
     digital_out_init( &ctx->rts, cfg->rts );

    // Input pins

     digital_in_init( &ctx->mcr, cfg->mcr );
     digital_in_init( &ctx->cts, cfg->cts );

    return WIFI9_OK;

}

void wifi9_module_power ( wifi9_t *ctx )
{
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
}

void wifi9_select_uart ( wifi9_t *ctx, uint8_t uart_select )
{
    digital_out_write( &ctx->adr, uart_select );
}

uint8_t wifi9_get_state_net_led ( wifi9_t *ctx )
{
    return digital_in_read( &ctx->mcr );
}

uint8_t wifi9_get_state_conn_led ( wifi9_t *ctx )
{
    return digital_in_read( &ctx->rst );
}

void wifi9_generic_write ( wifi9_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t wifi9_generic_read ( wifi9_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void wifi9_send_command ( wifi9_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r\n" );

    wifi9_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

// ------------------------------------------------------------------------- END

