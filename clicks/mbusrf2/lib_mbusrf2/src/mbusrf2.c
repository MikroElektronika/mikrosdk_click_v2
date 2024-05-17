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
 * @file mbusrf2.c
 * @brief M-BUS RF 2 Click Driver.
 */

#include "mbusrf2.h"

/**
 * @brief M-BUS RF 2 get CRC value function.
 * @details This function is used to get CRC value. 
 * @param[in] ctx : Click context object.
 * See #mbusrf2_t object definition for detailed explanation.
 * @return CRC value.
 * @note None.
 */
static uint8_t mbusrf2_get_crc ( uint8_t *data_buf );

void mbusrf2_cfg_setup ( mbusrf2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t mbusrf2_init ( mbusrf2_t *ctx, mbusrf2_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );

    digital_out_high( &ctx->rst );

    return UART_SUCCESS;
}

err_t mbusrf2_generic_write ( mbusrf2_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t mbusrf2_generic_read ( mbusrf2_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void mbusrf2_set_rst_pin ( mbusrf2_t *ctx, uint8_t pin_state )
{
    if ( 1 == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

err_t mbusrf2_send_command ( mbusrf2_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = MBUSRF2_OK;
    uint8_t data_buf[ MBUSRF2_TX_DRV_BUFFER_SIZE ] = { 0 };

    data_buf[ 0 ] = MBUSRF2_CMD_SFD;
    data_buf[ 1 ] = cmd;
    data_buf[ 2 ] = len;
    if ( len > 0 )
    {
        for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
        {
            data_buf[ n_cnt + 3 ] = data_in[ n_cnt ];
        }
    }
    data_buf[ len + 3 ] = mbusrf2_get_crc( data_buf );

    error_flag |= mbusrf2_generic_write( ctx, data_buf, len + 4 );

    return error_flag;
}

err_t mbusrf2_send_data ( mbusrf2_t *ctx, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = MBUSRF2_OK;
    uint8_t data_buf[ MBUSRF2_TX_DRV_BUFFER_SIZE ] = { 0 };

    data_buf[ 0 ] = MBUSRF2_CMD_SFD;
    data_buf[ 1 ] = MBUSRF2_CMD_DATA_REQ;
    data_buf[ 2 ] = len;
    if ( len > 0 )
    {
        for ( uint8_t n_cnt = 0; n_cnt < len; n_cnt++ )
        {
            data_buf[ n_cnt + 3 ] = data_in[ n_cnt ];
        }
    }
    data_buf[ len + 3 ] = mbusrf2_get_crc( data_buf );

    error_flag |= mbusrf2_generic_write( ctx, data_buf, len + 4 );

    return error_flag;
}

static uint8_t mbusrf2_get_crc ( uint8_t *data_buf )
{
    uint8_t checksum = 0;
    uint8_t payload_length = data_buf[ 2 ];
    for (uint8_t n_cnt = 0; n_cnt < payload_length + 3; n_cnt++)
     {
        checksum ^= data_buf[ n_cnt ];
    }
     return checksum;

}

// ------------------------------------------------------------------------- END
