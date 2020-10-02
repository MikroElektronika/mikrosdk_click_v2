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

#include "rs485isolator.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void commaunication_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rs485isolator_cfg_setup ( rs485isolator_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->re = HAL_PIN_NC;
    cfg->de   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

RS485ISOLATOR_RETVAL rs485isolator_init ( rs485isolator_t *ctx, rs485isolator_cfg_t *cfg )
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

    digital_out_init( &ctx->re, cfg->re );
    digital_out_init( &ctx->de, cfg->de );

    rs485isolator_set_receiver_mode( ctx, RS485ISOLATOR_RECEIVER_ENABLE );
    rs485isolator_set_driver_mode( ctx, RS485ISOLATOR_DRIVER_DISABLE );

    return RS485ISOLATOR_OK;
}

void rs485isolator_generic_write ( rs485isolator_t *ctx, char *data_buf, uint16_t len )
{
    rs485isolator_set_receiver_mode( ctx, RS485ISOLATOR_RECEIVER_DISABLE );
    rs485isolator_set_driver_mode( ctx, RS485ISOLATOR_DRIVER_ENABLE );

    uart_write( &ctx->uart, data_buf, len );
    commaunication_delay( );

    rs485isolator_set_receiver_mode( ctx, RS485ISOLATOR_RECEIVER_ENABLE );
    rs485isolator_set_driver_mode( ctx, RS485ISOLATOR_DRIVER_DISABLE );
}

int16_t rs485isolator_generic_read ( rs485isolator_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void rs485isolator_set_receiver_mode ( rs485isolator_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->re, state );
}

void rs485isolator_set_driver_mode ( rs485isolator_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->de, state );
}

void rs485isolator_send_command ( rs485isolator_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    uint8_t cnt;

    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r" );

    for ( cnt = 0; cnt < len; cnt++ )
    {
        rs485isolator_generic_write( ctx, &tmp_buf[ cnt ], 1 );
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void commaunication_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END

