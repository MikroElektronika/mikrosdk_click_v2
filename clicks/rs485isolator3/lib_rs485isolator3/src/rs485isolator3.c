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
 * @file rs485isolator3.c
 * @brief RS485 Isolator 3 Click Driver.
 */

#include "rs485isolator3.h"

void rs485isolator3_cfg_setup ( rs485isolator3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->re =  HAL_PIN_NC;
    cfg->de =  HAL_PIN_NC;
    cfg->inv = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t rs485isolator3_init ( rs485isolator3_t *ctx, rs485isolator3_cfg_t *cfg ) 
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
    digital_out_init( &ctx->re, cfg->re );
    digital_out_init( &ctx->de, cfg->de );
    digital_out_init( &ctx->inv, cfg->inv );

    return UART_SUCCESS;
}

void rs485isolator3_default_cfg ( rs485isolator3_t *ctx ) 
{
    rs485isolator3_disable_receiver_input( ctx );
    rs485isolator3_disable_output( ctx );
    rs485isolator3_not_inverted_inputs( ctx );
}

err_t rs485isolator3_generic_write ( rs485isolator3_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t rs485isolator3_generic_read ( rs485isolator3_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void rs485isolator3_enable_receiver_input ( rs485isolator3_t *ctx )
{
    digital_out_low( &ctx->re );
}

void rs485isolator3_disable_receiver_input ( rs485isolator3_t *ctx )
{
    digital_out_high( &ctx->re );
}

void rs485isolator3_enable_output ( rs485isolator3_t *ctx )
{
    digital_out_high( &ctx->de );
}

void rs485isolator3_disable_output ( rs485isolator3_t *ctx )
{
    digital_out_low( &ctx->de );
}

void rs485isolator3_inverted_inputs ( rs485isolator3_t *ctx )
{
    digital_out_high( &ctx->inv );
}

void rs485isolator3_not_inverted_inputs ( rs485isolator3_t *ctx )
{
    digital_out_low( &ctx->inv );
}

err_t rs485isolator3_send_bit_by_bit ( rs485isolator3_t *ctx, char *command )
{
    err_t error_flag = RS485ISOLATOR3_OK;
    char tmp_buf[ 100 ];
    uint8_t len;
    uint8_t cnt;

    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    if ( len < 100 )
    {
        strncpy( tmp_buf, command, len );

        for( cnt = 0; cnt < len; cnt ++ )
        {
            error_flag |= rs485isolator3_generic_write( ctx, &tmp_buf[ cnt ], 1 );
            Delay_100ms( );
        }
    }
    else
    {
        error_flag = RS485ISOLATOR3_ERROR;
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
