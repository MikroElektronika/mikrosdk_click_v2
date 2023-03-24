/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file rtkbase.c
 * @brief RTK Base Click Driver.
 */

#include "rtkbase.h"

void rtkbase_cfg_setup ( rtkbase_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->shd = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->bt  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t rtkbase_init ( rtkbase_t *ctx, rtkbase_cfg_t *cfg ) 
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

    if ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->shd, cfg->shd );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->bt, cfg->bt );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_high( &ctx->shd );
    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->wup );
    digital_out_low( &ctx->bt );
    Delay_100ms ( );
    rtkbase_enable_rx_interrupt ( ctx );

    return UART_SUCCESS;
}

err_t rtkbase_generic_write ( rtkbase_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t rtkbase_generic_read ( rtkbase_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void rtkbase_clear_ring_buffers ( rtkbase_t *ctx )
{    
    uart_clear( &ctx->uart );
}

err_t rtkbase_rx_bytes_available ( rtkbase_t *ctx )
{    
    return uart_bytes_available ( &ctx->uart );
}

void rtkbase_enable_rx_interrupt ( rtkbase_t *ctx )
{
    uint8_t dummy;
    rtkbase_generic_read( ctx, &dummy, 1 );
}

void rtkbase_set_rst_pin ( rtkbase_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void rtkbase_set_wup_pin ( rtkbase_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void rtkbase_set_boot_pin ( rtkbase_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->bt, state );
}

void rtkbase_set_shd_pin ( rtkbase_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->shd, state );
}

uint8_t rtkbase_get_int_pin ( rtkbase_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

uint32_t rtkbase_calculate_crc24( uint8_t *data_buf, uint16_t data_len )
{
    static uint32_t crc_table[ ] = 
    {
        0x00000000ul, 0x01864CFBul, 0x038AD50Dul, 0x020C99F6ul,
        0x0793E6E1ul, 0x0615AA1Aul, 0x041933ECul, 0x059F7F17ul,
        0x0FA18139ul, 0x0E27CDC2ul, 0x0C2B5434ul, 0x0DAD18CFul,
        0x083267D8ul, 0x09B42B23ul, 0x0BB8B2D5ul, 0x0A3EFE2Eul
    };

    uint32_t crc = 0;
    for ( uint16_t cnt = 0; cnt < data_len; cnt++ )
    {
        crc ^= ( uint32_t ) data_buf[ cnt ] << 16;
        crc = ( crc << 4 ) ^ crc_table[ ( crc >> 20 ) & 0x0F ];
        crc = ( crc << 4 ) ^ crc_table[ ( crc >> 20 ) & 0x0F ];
    }

    return ( crc & 0xFFFFFFul );
}

// ------------------------------------------------------------------------- END
