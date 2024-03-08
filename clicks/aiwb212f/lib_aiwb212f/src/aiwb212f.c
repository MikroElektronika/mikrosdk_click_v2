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
 * @file aiwb212f.c
 * @brief Ai-WB2-12F Click Driver.
 */

#include "aiwb212f.h"

void aiwb212f_cfg_setup ( aiwb212f_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t aiwb212f_init ( aiwb212f_t *ctx, aiwb212f_cfg_t *cfg ) 
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
    digital_out_init( &ctx->en, cfg->en );

    digital_out_high( &ctx->en );

    aiwb212f_send_cmd ( ctx, " " );

    return UART_SUCCESS;
}

err_t aiwb212f_generic_write ( aiwb212f_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t aiwb212f_generic_read ( aiwb212f_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void aiwb212f_hw_reset ( aiwb212f_t *ctx )
{
    digital_out_low( &ctx->en );
    Delay_100ms( );
    digital_out_high( &ctx->en );
}

void aiwb212f_send_cmd ( aiwb212f_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t cmd_end[ 2 ] = { '\r', '\n' };
    while ( *at_cmd_buf != 0 )
    {
        uart_write( &ctx->uart, at_cmd_buf, 1 );
        at_cmd_buf++;
    }
    uart_write( &ctx->uart, cmd_end, 2 );
    Delay_100ms(  );
}

void aiwb212f_send_cmd_with_par ( aiwb212f_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    aiwb212f_send_cmd( ctx, final_cmd );
}

void aiwb212f_send_cmd_check ( aiwb212f_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    aiwb212f_send_cmd( ctx, final_cmd );
}

void aiwb212f_set_gpio ( aiwb212f_t *ctx, uint8_t *pin, uint8_t *state ) 
{
    uint8_t command_data[ 10 ] = { 0 };

    strcpy( command_data, pin );
    strcat( command_data, "," );
    strcat( command_data, state );

    aiwb212f_send_cmd_with_par( ctx, AIWB212F_CMD_AT_SYSGPIOWRITE, command_data );
}

// ------------------------------------------------------------------------- END
