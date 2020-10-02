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

#include "wifi11.h"
#include "string.h"


// ------------------------------------------------------------- PRIVATE MACROS 

// Buffer 
#define WIFI11_BUF_FIRST_CMD "=\""
#define WIFI11_BUF_MID_CMD   "\",\""
#define WIFI11_BUF_END_CMD   "\""

#define CONNECT_AP_CMD  "ATPN"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void wifi11_cfg_setup ( wifi11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->baud_rate      = 38400;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

WIFI11_RETVAL wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg )
{
    uart_config_t uart_cfg;

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

    digital_out_init( &ctx->rst, cfg->rst );

    return WIFI11_OK;
}

void wifi11_generic_write ( wifi11_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t wifi11_generic_read ( wifi11_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void wifi11_reset_device ( wifi11_t *ctx )
{
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void wifi11_send_command ( wifi11_t *ctx, char *command )
{
    uint8_t tmp_buf[ 100 ];
    uint8_t len;

    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r" );
    //strcat( tmp_buf, "\n" );
    wifi11_generic_write( ctx, tmp_buf, len );
}

void wifi11_set_conect_to_ap( wifi11_t *ctx, char *username, char *password )
{
    uint8_t tmp_buf[ 100 ];
    uint8_t i;
    
    memset( &tmp_buf[ 0 ], 0, 100 );

    strcat( &tmp_buf[ 0 ], CONNECT_AP_CMD );
    strcat( &tmp_buf[ 0 ], WIFI11_BUF_FIRST_CMD );
    strcat( &tmp_buf[ 0 ], &username[ 0 ] );
    strcat( &tmp_buf[ 0 ], WIFI11_BUF_MID_CMD );
    strcat( &tmp_buf[ 0 ], &password[ 0 ] );
    strcat( &tmp_buf[ 0 ], WIFI11_BUF_END_CMD );

    wifi11_send_command( ctx, &tmp_buf[ 0 ] );
}

// ------------------------------------------------------------------------- END

