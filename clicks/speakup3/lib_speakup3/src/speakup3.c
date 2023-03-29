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
 * @file speakup3.c
 * @brief SpeakUp 3 Click Driver.
 */

#include "speakup3.h"

void speakup3_cfg_setup ( speakup3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t speakup3_init ( speakup3_t *ctx, speakup3_cfg_t *cfg ) 
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

    return UART_SUCCESS;
}

err_t speakup3_generic_write ( speakup3_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t speakup3_generic_read ( speakup3_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t speakup3_wait_for_reply ( speakup3_t *ctx, uint8_t *reply_ins, uint32_t wait_ms )
{
    uint8_t data_buf[ 5 ] = { 0 };
    uint32_t timeout_cnt = 0;
    while ( ( speakup3_generic_read( ctx, data_buf, 1 ) <= 0 ) || ( SPEAKUP3_START_BYTE != data_buf[ 0 ] ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt > wait_ms )
        {
            return SPEAKUP3_ERROR;
        }
    }
    Delay_10ms( );
    if ( 4 != speakup3_generic_read( ctx, &data_buf[ 1 ], 4 ) )
    {
        return SPEAKUP3_ERROR;
    }
    uint8_t check_byte = data_buf[ 0 ] + data_buf[ 1 ];
    if ( data_buf[ 4 ] != check_byte )
    {
        return SPEAKUP3_ERROR;
    }
    *reply_ins = data_buf[ 1 ];
    return SPEAKUP3_OK;
}

// ------------------------------------------------------------------------- END
