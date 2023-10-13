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
 * @file speedradar.c
 * @brief Speed Radar Click Driver.
 */

#include "speedradar.h"

void speedradar_cfg_setup ( speedradar_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dir = HAL_PIN_NC;
    cfg->det = HAL_PIN_NC;

    cfg->baud_rate     = 38400;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t speedradar_init ( speedradar_t *ctx, speedradar_cfg_t *cfg ) 
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

    // Input pins
    digital_in_init( &ctx->dir, cfg->dir );
    digital_in_init( &ctx->det, cfg->det );
    return UART_SUCCESS;
}

err_t speedradar_default_cfg ( speedradar_t *ctx ) 
{
    err_t err_flag = speedradar_send_command_value( ctx, SPEEDRADAR_CMD_FUN_MISC_OUT, 
                                                SPEEDRADAR_SET_MISC_OUT_DIR );
    Delay_100ms( );
    err_flag |= speedradar_send_command_value( ctx, SPEEDRADAR_CMD_SAMPLING_RATE, 
                                                SPEEDRADAR_SET_SAMPLING_RATE_X4 );
    Delay_100ms( );
    err_flag |= speedradar_send_command( ctx, SPEEDRADAR_CMD_RESET_PROCESSOR );
    Delay_100ms( );
    return err_flag;
}

err_t speedradar_generic_write ( speedradar_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t speedradar_generic_read ( speedradar_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t speedradar_send_command ( speedradar_t *ctx, uint8_t *cmd ) 
{
    uint8_t cmd_buf[ 6 ] = { 0 };
    strncpy( cmd_buf, SPEEDRADAR_CMD_PREFIX, strlen( SPEEDRADAR_CMD_PREFIX ) );
    strncat( cmd_buf, cmd, strlen( cmd ) );
    strncat( cmd_buf, SPEEDRADAR_CMD_ENTER, strlen( SPEEDRADAR_CMD_ENTER ) );
    return speedradar_generic_write( ctx, cmd_buf, strlen( cmd_buf ) );
}

err_t speedradar_send_command_value ( speedradar_t *ctx, uint8_t *cmd, uint8_t *cmd_value ) 
{
    uint8_t cmd_buf[ 10 ] = { 0 };
    strncpy( cmd_buf, SPEEDRADAR_CMD_PREFIX, strlen( SPEEDRADAR_CMD_PREFIX ) );
    strncat( cmd_buf, cmd, strlen( cmd ) );
    strncat( cmd_buf, cmd_value, strlen( cmd_value ) );
    strncat( cmd_buf, SPEEDRADAR_CMD_ENTER, strlen( SPEEDRADAR_CMD_ENTER ) );
    return speedradar_generic_write( ctx, cmd_buf, strlen( cmd_buf ) );
}

uint8_t speedradar_get_direction ( speedradar_t *ctx )
{
    return digital_in_read( &ctx->dir );
}

uint8_t speedradar_get_detection ( speedradar_t *ctx )
{
    return digital_in_read( &ctx->det );
}

// ------------------------------------------------------------------------- END
