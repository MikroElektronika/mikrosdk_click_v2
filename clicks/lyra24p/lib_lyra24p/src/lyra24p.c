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
 * @file lyra24p.c
 * @brief LYRA 24P Click Driver.
 */

#include "lyra24p.h"

void lyra24p_cfg_setup ( lyra24p_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->bt  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t lyra24p_init ( lyra24p_t *ctx, lyra24p_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->bt, cfg->bt );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    digital_out_high( &ctx->bt );

    return UART_SUCCESS;
}

void lyra24p_hw_reset ( lyra24p_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void lyra24p_set_bt_pin ( lyra24p_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

void lyra24p_request_to_send ( lyra24p_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rts, state );
}

uint8_t lyra24p_clear_to_send ( lyra24p_t *ctx ) 
{
    return digital_in_read( &ctx->cts );
}

err_t lyra24p_generic_write ( lyra24p_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t lyra24p_generic_read ( lyra24p_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

err_t lyra24p_write_command ( lyra24p_t *ctx, uint8_t *command )
{
    err_t err_flag = lyra24p_generic_write( ctx, command, strlen( command ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_END, strlen( LYRA24P_PREFIX_SYMBOL_END ) );
    return err_flag;
}

err_t lyra24p_write_cmd_param ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t *prefix, uint8_t *param )
{
    err_t err_flag = lyra24p_generic_write( ctx, command, strlen( command ) );
    if ( strlen( cmd_val ) > 0 )
    {
        err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_SPACE, 1 );
        err_flag |= lyra24p_generic_write( ctx, cmd_val, strlen( cmd_val ) );
    }
    err_flag |= lyra24p_generic_write( ctx, prefix, strlen( prefix ) );
    err_flag |= lyra24p_generic_write( ctx, param, strlen( param ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_END, strlen( LYRA24P_PREFIX_SYMBOL_END ) );
    return err_flag;
}

err_t lyra24p_set_device_name ( lyra24p_t *ctx, uint8_t *device_name )
{
    err_t err_flag = lyra24p_generic_write( ctx, LYRA24P_CMD_ATPS, strlen( LYRA24P_CMD_ATPS ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_ZERO, 1 );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_SET_VAL, strlen( LYRA24P_PREFIX_SYMBOL_SET_VAL ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_QUOTE, strlen( LYRA24P_PREFIX_SYMBOL_QUOTE ) );
    err_flag |= lyra24p_generic_write( ctx, device_name, strlen( device_name ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_QUOTE, strlen( LYRA24P_PREFIX_SYMBOL_QUOTE ) );
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_END, strlen( LYRA24P_PREFIX_SYMBOL_END ) );
    return err_flag;
}

err_t lyra24p_inquire_command ( lyra24p_t *ctx, uint8_t *command, uint8_t *cmd_val, uint8_t add_query ) 
{
    err_t err_flag = lyra24p_generic_write( ctx, command, strlen( command ) );
    if ( strlen( cmd_val ) > 0 )
    {
        err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_SPACE, 1 );
        err_flag |= lyra24p_generic_write( ctx, cmd_val, strlen( cmd_val ) );
    }
    if ( add_query == 1 )
    {
        err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_QUERY, 1 );
    }
    
    err_flag |= lyra24p_generic_write( ctx, LYRA24P_PREFIX_SYMBOL_END, strlen( LYRA24P_PREFIX_SYMBOL_END ) );
    return err_flag;
}

// ------------------------------------------------------------------------- END
