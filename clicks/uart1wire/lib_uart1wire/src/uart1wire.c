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

#include "uart1wire.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t calculate_crc8_maxim( uint8_t *data_buf, uint8_t len );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void uart1wire_cfg_setup ( uart1wire_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

UART1WIRE_RETVAL uart1wire_init ( uart1wire_t *ctx, uart1wire_cfg_t *cfg )
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

    return UART1WIRE_OK;
}

void uart1wire_generic_write ( uart1wire_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t uart1wire_generic_read ( uart1wire_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void uart1wire_write_command ( uart1wire_t *ctx, uint8_t cmd )
{
    uart1wire_generic_write( ctx, &cmd, 1 );
}

uint8_t uart1wire_read_byte ( uart1wire_t *ctx )
{
    uint8_t r_byte;

    uart1wire_generic_read( ctx, &r_byte, 1 );

    return r_byte; 
}

void uart1wire_reset ( uart1wire_t *ctx )
{
    Delay_10ms( );
    uart1wire_write_command( ctx, UART1WIRE_COMMAND_MODE );
    Delay_1ms( );
    uart1wire_write_command( ctx, UART1WIRE_RESET );
    Delay_1ms( );
}

int8_t uart1wire_read_data ( uart1wire_t *ctx, uint8_t *data_out, uint8_t num_bytes )
{
    int32_t rx_size;
    uint8_t rx_cnt = 0;
    
    // Clear RX buffer
    uint8_t tmp_buf[ DRV_RX_BUFFER_SIZE ] = { 0 };
    uart1wire_generic_read( ctx, tmp_buf, DRV_RX_BUFFER_SIZE );
    
    Delay_10ms( );
    
    for ( uint8_t cnt = 0; cnt < num_bytes; cnt++ )
    {
        uart1wire_write_command( ctx, UART1WIRE_READ_SEQ );
        Delay_10ms( );
        rx_size = uart1wire_generic_read( ctx, &data_out[ cnt ], 1 );
        if ( rx_size > 0 )
        {
            rx_cnt++;
        }
    }
    
    if ( rx_cnt != num_bytes )
    {
        return UART1WIRE_ERROR;
    }
    
    return UART1WIRE_OK;
}

int8_t uart1wire_read_temperature ( uart1wire_t *ctx, float *temperature, uint8_t resolution )
{
    uint8_t rx_buf[ 9 ] = { 0 };
    int16_t temp_word = 0;
    uint8_t crc = 0;
    uart1wire_reset ( ctx );
    uart1wire_write_command( ctx, UART1WIRE_DATA_MODE );
    Delay_10ms( );
    uart1wire_write_command( ctx, UART1WIRE_SKIP_ROM );
    uart1wire_write_command( ctx, UART1WIRE_CONVERT_TEMPERATURE );
    Delay_10ms( );
    uart1wire_reset ( ctx );
    uart1wire_write_command( ctx, UART1WIRE_DATA_MODE );
    Delay_10ms( );
    uart1wire_write_command( ctx, UART1WIRE_SKIP_ROM );
    uart1wire_write_command( ctx, UART1WIRE_READ_SCRATCHPAD );
    Delay_10ms( );
    
    if ( uart1wire_read_data ( ctx, rx_buf, 9 ) != UART1WIRE_OK )
    {
        return UART1WIRE_ERROR;
    }
    
    crc = calculate_crc8_maxim ( rx_buf, 8 );
    
    if ( crc != rx_buf[ 8 ] )
    {
        return UART1WIRE_ERROR;
    }
    
    temp_word = ( rx_buf[ 1 ] << 8 ) | rx_buf[ 0 ];
    
    *temperature = ( float ) temp_word;
    *temperature /= ( 1 << ( resolution - 8 ) );
    
    return UART1WIRE_OK;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t calculate_crc8_maxim( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    
    for ( uint8_t i = 0; i < len; i++ ) 
    {
        uint8_t in_byte = data_buf[ i ];
        for ( uint8_t j = 0; j < 8; j++ ) 
        {
            uint8_t mix = ( crc ^ in_byte ) & 0x01;
            crc >>= 1;
            if ( mix != 0 ) 
            {
                crc ^= 0x8C;
            }
            in_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END

