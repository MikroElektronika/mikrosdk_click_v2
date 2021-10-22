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
 * @file gnss8.c
 * @brief GNSS 8 Click Driver.
 */

#include "gnss8.h"

void gnss8_cfg_setup ( gnss8_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rdy   = HAL_PIN_NC;
    cfg->req = HAL_PIN_NC;
   //cfg->cs   = HAL_PIN_NC;
    cfg->apr = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t gnss8_init ( gnss8_t *ctx, gnss8_cfg_t *cfg ) 
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) 
    {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins
    digital_out_init( &ctx->apr, cfg->apr );

    // Input pins
    digital_in_init( &ctx->rdy, cfg->rdy );
    digital_in_init( &ctx->req, cfg->req );
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return UART_SUCCESS;
}

err_t gnss8_generic_write ( gnss8_t *ctx, char *data_buf, uint16_t len ) 
{
    err_t error_flag = uart_write( &ctx->uart, data_buf, len );
    return error_flag;
}

err_t gnss8_generic_read ( gnss8_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void gnss8_set_ap_req ( gnss8_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->apr );
    }
    else
    {
        digital_out_low( &ctx->apr );
    }
}

uint8_t gnss8_get_req ( gnss8_t *ctx )
{
    return digital_in_read( &ctx->req );
}

uint8_t gnss8_get_int ( gnss8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t gnss8_get_rdy ( gnss8_t *ctx )
{
    return digital_in_read( &ctx->rdy );
}

// ------------------------------------------------------------------------- END
