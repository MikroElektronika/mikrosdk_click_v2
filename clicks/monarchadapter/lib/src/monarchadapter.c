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

#include "monarchadapter.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void monarchadapter_cfg_setup ( monarchadapter_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rng = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

MONARCHADAPTER_RETVAL monarchadapter_init ( monarchadapter_t *ctx, monarchadapter_cfg_t *cfg )
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins

    digital_in_init( &ctx->rng, cfg->rng );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return MONARCHADAPTER_OK;
}

void monarchadapter_power_on ( monarchadapter_t *ctx )
{
    digital_out_low( &ctx->rts );
    
    digital_out_low( &ctx->rst );
    Delay_100ms();
    digital_out_high( &ctx->rst );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

void monarchadapter_set_rst_pin ( monarchadapter_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

void monarchadapter_set_rts_pin ( monarchadapter_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rts, state );
}

uint8_t monarchadapter_get_int_pin ( monarchadapter_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t monarchadapter_get_rng_pin ( monarchadapter_t *ctx )
{
    return digital_in_read( &ctx->rng );
}

void monarchadapter_generic_write ( monarchadapter_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t monarchadapter_generic_read ( monarchadapter_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void monarchadapter_send_command ( monarchadapter_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r\n" );

    monarchadapter_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

// ------------------------------------------------------------------------- END

