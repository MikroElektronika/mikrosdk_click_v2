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

#include "mbusrf4.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PARSER_READY 0
#define PARSER_COMMAND_NOT_SUPPORTED 1
#define PARSER_ELEMENT_NOT_SUPPORTED 2

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void calc_checksum ( uint8_t *crc_buff, uint8_t n_bytes );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void mbusrf4_cfg_setup ( mbusrf4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

     cfg->ind   = HAL_PIN_NC;
     cfg->cs    = HAL_PIN_NC;
     cfg->sel   = HAL_PIN_NC;
     cfg->rts   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

MBUSRF4_RETVAL mbusrf4_init ( mbusrf4_t *ctx, mbusrf4_cfg_t *cfg )
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

     digital_out_init( &ctx->cs, cfg->cs );
     digital_out_init( &ctx->sel, cfg->sel );

    // Input pins

     digital_in_init( &ctx->ind, cfg->ind );
     digital_in_init( &ctx->rts, cfg->rts );

     digital_out_low( &ctx->cs );
     digital_out_high( &ctx->sel ); 

    return MBUSRF4_OK;

}

void mbusrf4_generic_write ( mbusrf4_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t mbusrf4_generic_read ( mbusrf4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t mbusrf4_get_state_rts ( mbusrf4_t *ctx )
{
    uint8_t status;

    status = digital_in_read( &ctx->rts );

    return status;
}

void mbusrf4_set_communication_mode ( mbusrf4_t *ctx, uint8_t mode )
{
    digital_out_write( &ctx->sel, mode );
}

uint8_t mbusrf4_get_state_ind ( mbusrf4_t *ctx )
{
    uint8_t status;

    status = digital_in_read( &ctx->ind );

    return status;
}

void mbusrf4_send_command ( mbusrf4_t *ctx, uint8_t command, uint8_t length, uint8_t *payload_buff )
{
    uint8_t crc_buf[ 255 ] = { 0 };
    uint8_t crc_cnt = 3;
    
    crc_buf[ 0 ] = MBUSRF4_HEADER;
    crc_buf[ 1 ] = command;
    crc_buf[ 2 ] = length;
    
    for ( uint8_t cnt = 0; cnt < length; cnt++ )
    {
        crc_buf[ crc_cnt ] = *payload_buff;
        payload_buff++;
        crc_cnt++;
    }
    
    calc_checksum( crc_buf, crc_cnt );
    crc_cnt++;
    
    mbusrf4_generic_write( ctx, crc_buf, crc_cnt );
}

void mbusrf4_transmit_data ( mbusrf4_t *ctx, uint8_t *tx_buf, uint8_t tx_len )
{
    uint8_t crc_buf[ 255 ] = { 0 };
    uint8_t crc_cnt = 3;
    
    crc_buf[ 0 ] = MBUSRF4_HEADER;
    crc_buf[ 1 ] = MBUSRF4_CMD_TX_MSG;
    crc_buf[ 2 ] = tx_len;
    
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        crc_buf[ crc_cnt ] = *tx_buf;
        tx_buf++;
        crc_cnt++;
    }
    
    calc_checksum( crc_buf, crc_cnt );
    crc_cnt++;
    
    mbusrf4_generic_write( ctx, crc_buf, crc_cnt );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void calc_checksum ( uint8_t *crc_buff, uint8_t n_bytes )
{
    uint8_t cnt;
    uint8_t crc_data = 0;

    for ( cnt = 0; cnt < n_bytes; cnt++ )
    {
        crc_data ^= crc_buff[ cnt ];
    }

    crc_buff[ n_bytes ] = crc_data;
}

// ------------------------------------------------------------------------- END

