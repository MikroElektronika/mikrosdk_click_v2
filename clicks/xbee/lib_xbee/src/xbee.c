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
 * @file xbee.c
 * @brief XBEE Click Driver.
 */

#include "xbee.h"

void xbee_cfg_setup ( xbee_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rts = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->att_dtr = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t xbee_init ( xbee_t *ctx, xbee_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );
    digital_in_init( &ctx->att_dtr, cfg->att_dtr );

    digital_out_high ( &ctx->cs );
    digital_out_low ( &ctx->rts );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t xbee_generic_write ( xbee_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t xbee_generic_read ( xbee_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void xbee_set_rts_pin ( xbee_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rts, state );
}

void xbee_set_rst_pin ( xbee_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

void xbee_set_cs_pin ( xbee_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->cs, state );
}

uint8_t xbee_get_cts_pin ( xbee_t *ctx ) 
{
    return digital_in_read ( &ctx->cts );
}

uint8_t xbee_get_att_dtr_pin ( xbee_t *ctx ) 
{
    return digital_in_read ( &ctx->att_dtr );
}

err_t xbee_write_command ( xbee_t *ctx, char *data_buf )
{
    err_t error_flag = uart_write( &ctx->uart, XBEE_CMD_AT, strlen( XBEE_CMD_AT ) );
    error_flag |= uart_write( &ctx->uart, data_buf, strlen( data_buf ) );
    error_flag |= uart_write( &ctx->uart, XBEE_CARRIAGE_RETURN, strlen( XBEE_CARRIAGE_RETURN ) );
    return error_flag;
}

void xbee_hw_reset ( xbee_t *ctx )
{
    xbee_set_rst_pin( ctx, 0 );
    Delay_100ms ( );
    xbee_set_rst_pin( ctx, 1 );
    Delay_1sec ( );
}

err_t xbee_enter_command_mode ( xbee_t *ctx )
{
    Delay_1sec ( );
    err_t error_flag = xbee_generic_write ( ctx, XBEE_ENTER_CMD_MODE, strlen ( XBEE_ENTER_CMD_MODE ) );
    Delay_1sec ( );
    return error_flag;
}

err_t xbee_exit_command_mode ( xbee_t *ctx )
{
    return xbee_write_command ( ctx, XBEE_EXIT_CMD_MODE );
}

err_t xbee_factory_reset ( xbee_t *ctx )
{
    return xbee_write_command ( ctx, XBEE_FACTORY_RESET );
}

err_t xbee_get_serial_number ( xbee_t *ctx )
{
    return xbee_write_command ( ctx, XBEE_GET_SERIAL_NUMBER );
}

err_t xbee_set_device_name ( xbee_t *ctx, char *dev_name )
{
    if ( strlen( dev_name ) > 20 || strlen( dev_name ) < 1 )
    {
        return XBEE_ERROR;
    }
    uint8_t cmd_buf[ 23 ] = { 0 };
    strcpy ( cmd_buf, XBEE_SET_NODE_IDENTIFIER );
    strcat ( cmd_buf, dev_name );
    return xbee_write_command ( ctx, cmd_buf );
}

err_t xbee_set_destination_address ( xbee_t *ctx, char *dest_addr_high, char *dest_addr_low )
{
    if ( strlen( dest_addr_high ) > 8 || strlen( dest_addr_low ) > 8 )
    {
        return XBEE_ERROR;
    }
    uint8_t cmd_buf[ 22 ] = { 0 };
    strcpy ( cmd_buf, XBEE_SET_DEST_ADDR_HIGH );
    strcat ( cmd_buf, dest_addr_high );
    strcat ( cmd_buf, XBEE_DELIMITER );
    strcat ( cmd_buf, XBEE_SET_DEST_ADDR_LOW );
    strcat ( cmd_buf, dest_addr_low );
    return xbee_write_command ( ctx, cmd_buf );
}

err_t xbee_set_api_mode ( xbee_t *ctx, uint8_t api_mode )
{
    if ( api_mode > XBEE_MODE_API_WITH_ESC )
    {
        return XBEE_ERROR;
    }
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t api_mode_buf[ 2 ] = { api_mode + 48, 0 };
    strcpy ( cmd_buf, XBEE_API_MODE );
    strcat ( cmd_buf, api_mode_buf );
    return xbee_write_command ( ctx, cmd_buf );
}

err_t xbee_apply_changes ( xbee_t *ctx )
{
    return xbee_write_command ( ctx, XBEE_APPLY_CHANGES );
}

err_t xbee_save_changes ( xbee_t *ctx )
{
    return xbee_write_command ( ctx, XBEE_SAVE_CHANGES );
}

// ------------------------------------------------------------------------- END
