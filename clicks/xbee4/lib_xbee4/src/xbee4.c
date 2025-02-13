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
 * @file xbee4.c
 * @brief XBEE 4 Click Driver.
 */

#include "xbee4.h"

void xbee4_cfg_setup ( xbee4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->slp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->com = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 9600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t xbee4_init ( xbee4_t *ctx, xbee4_cfg_t *cfg ) 
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
    digital_out_init( &ctx->slp, cfg->slp );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->com, cfg->com );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    digital_out_low ( &ctx->slp );
    digital_out_low ( &ctx->com );
    digital_out_high ( &ctx->rts );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t xbee4_generic_write ( xbee4_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t xbee4_generic_read ( xbee4_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void xbee4_set_rts_pin ( xbee4_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rts, state );
}

void xbee4_set_rst_pin ( xbee4_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

void xbee4_set_slp_pin ( xbee4_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->slp, state );
}

void xbee4_set_com_pin ( xbee4_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->com, state );
}

uint8_t xbee4_get_cts_pin ( xbee4_t *ctx ) 
{
    return digital_in_read ( &ctx->cts );
}

void xbee4_write_command ( xbee4_t *ctx, uint8_t *data_buf )
{
    uart_write( &ctx->uart, XBEE4_CMD_AT, strlen( XBEE4_CMD_AT ) );
    uart_write( &ctx->uart, data_buf, strlen( data_buf ) );
    uart_write( &ctx->uart, XBEE4_CARRIAGE_RETURN, strlen( XBEE4_CARRIAGE_RETURN ) );
    Delay_100ms ( );
}

void xbee4_hw_reset ( xbee4_t *ctx )
{
    xbee4_set_rst_pin( ctx, 0 );
    Delay_100ms ( );
    xbee4_set_rst_pin( ctx, 1 );
    Delay_1sec ( );
}

void xbee4_enter_command_mode ( xbee4_t *ctx )
{
    Delay_1sec ( );
    xbee4_generic_write ( ctx, XBEE4_ENTER_CMD_MODE, strlen ( XBEE4_ENTER_CMD_MODE ) );
    Delay_1sec ( );
}

void xbee4_exit_command_mode ( xbee4_t *ctx )
{
    xbee4_write_command ( ctx, XBEE4_EXIT_CMD_MODE );
}

void xbee4_factory_reset ( xbee4_t *ctx )
{
    xbee4_write_command ( ctx, XBEE4_FACTORY_RESET );
}

void xbee4_get_serial_number ( xbee4_t *ctx )
{
    xbee4_write_command ( ctx, XBEE4_GET_SERIAL_NUMBER );
}

void xbee4_set_device_name ( xbee4_t *ctx, uint8_t *dev_name )
{
    uint8_t cmd_buf[ 23 ] = { 0 };
    if ( ( strlen( dev_name ) >= 1 ) && ( strlen( dev_name ) <= 20 ) )
    {
        strcpy ( cmd_buf, XBEE4_SET_NODE_IDENTIFIER );
        strcat ( cmd_buf, dev_name );
        xbee4_write_command ( ctx, cmd_buf );
    }
}

void xbee4_set_destination_address ( xbee4_t *ctx, uint8_t *dest_addr_high, uint8_t *dest_addr_low )
{
    uint8_t cmd_buf[ 22 ] = { 0 };
    if ( ( 8 == strlen( dest_addr_high ) ) && ( 8 == strlen( dest_addr_low ) ) )
    {
        strcpy ( cmd_buf, XBEE4_SET_DEST_ADDR_HIGH );
        strcat ( cmd_buf, dest_addr_high );
        strcat ( cmd_buf, XBEE4_DELIMITER );
        strcat ( cmd_buf, XBEE4_SET_DEST_ADDR_LOW );
        strcat ( cmd_buf, dest_addr_low );
        xbee4_write_command ( ctx, cmd_buf );
    }
}

void xbee4_set_api_mode ( xbee4_t *ctx, uint8_t api_mode )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t api_mode_buf[ 2 ] = { api_mode + 48, 0 };
    if ( api_mode <= XBEE4_MODE_API_WITH_ESC )
    {
        strcpy ( cmd_buf, XBEE4_API_MODE );
        strcat ( cmd_buf, api_mode_buf );
        xbee4_write_command ( ctx, cmd_buf );
    }
}

void xbee4_set_device_role ( xbee4_t *ctx, uint8_t dev_role )
{
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t dev_role_buf[ 2 ] = { dev_role + 48, 0 };
    if ( dev_role <= XBEE4_DEVICE_ROLE_FORM_NETWORK )
    {
        strcpy ( cmd_buf, XBEE4_DEV_ROLE );
        strcat ( cmd_buf, dev_role_buf );
        xbee4_write_command ( ctx, cmd_buf );
    }
}

void xbee4_apply_changes ( xbee4_t *ctx )
{
    xbee4_write_command ( ctx, XBEE4_APPLY_CHANGES );
}

void xbee4_save_changes ( xbee4_t *ctx )
{
    xbee4_write_command ( ctx, XBEE4_SAVE_CHANGES );
}

// ------------------------------------------------------------------------- END
