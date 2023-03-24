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
 * @file xbee2.c
 * @brief XBEE 2 Click Driver.
 */

#include "xbee2.h"

void xbee2_cfg_setup ( xbee2_cfg_t *cfg ) 
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

err_t xbee2_init ( xbee2_t *ctx, xbee2_cfg_t *cfg ) 
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

err_t xbee2_generic_write ( xbee2_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t xbee2_generic_read ( xbee2_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void xbee2_set_rts_pin ( xbee2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rts, state );
}

void xbee2_set_rst_pin ( xbee2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->rst, state );
}

void xbee2_set_cs_pin ( xbee2_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->cs, state );
}

uint8_t xbee2_get_cts_pin ( xbee2_t *ctx ) 
{
    return digital_in_read ( &ctx->cts );
}

uint8_t xbee2_get_att_dtr_pin ( xbee2_t *ctx ) 
{
    return digital_in_read ( &ctx->att_dtr );
}

err_t xbee2_write_command ( xbee2_t *ctx, char *data_buf )
{
    err_t error_flag = uart_write( &ctx->uart, XBEE2_CMD_AT, strlen( XBEE2_CMD_AT ) );
    error_flag |= uart_write( &ctx->uart, data_buf, strlen( data_buf ) );
    error_flag |= uart_write( &ctx->uart, XBEE2_CARRIAGE_RETURN, strlen( XBEE2_CARRIAGE_RETURN ) );
    return error_flag;
}

void xbee2_hw_reset ( xbee2_t *ctx )
{
    xbee2_set_rst_pin( ctx, 0 );
    Delay_100ms ( );
    xbee2_set_rst_pin( ctx, 1 );
    Delay_1sec ( );
}

err_t xbee2_enter_command_mode ( xbee2_t *ctx )
{
    Delay_1sec ( );
    err_t error_flag = xbee2_generic_write ( ctx, XBEE2_ENTER_CMD_MODE, strlen ( XBEE2_ENTER_CMD_MODE ) );
    Delay_1sec ( );
    return error_flag;
}

err_t xbee2_exit_command_mode ( xbee2_t *ctx )
{
    return xbee2_write_command ( ctx, XBEE2_EXIT_CMD_MODE );
}

err_t xbee2_factory_reset ( xbee2_t *ctx )
{
    return xbee2_write_command ( ctx, XBEE2_FACTORY_RESET );
}

err_t xbee2_get_serial_number ( xbee2_t *ctx )
{
    return xbee2_write_command ( ctx, XBEE2_GET_SERIAL_NUMBER );
}

err_t xbee2_set_device_name ( xbee2_t *ctx, char *dev_name )
{
    if ( strlen( dev_name ) > 20 || strlen( dev_name ) < 1 )
    {
        return XBEE2_ERROR;
    }
    uint8_t cmd_buf[ 23 ] = { 0 };
    strcpy ( cmd_buf, XBEE2_SET_NODE_IDENTIFIER );
    strcat ( cmd_buf, dev_name );
    return xbee2_write_command ( ctx, cmd_buf );
}

err_t xbee2_set_destination_address ( xbee2_t *ctx, char *dest_addr_high, char *dest_addr_low )
{
    if ( strlen( dest_addr_high ) > 8 || strlen( dest_addr_low ) > 8 )
    {
        return XBEE2_ERROR;
    }
    uint8_t cmd_buf[ 22 ] = { 0 };
    strcpy ( cmd_buf, XBEE2_SET_DEST_ADDR_HIGH );
    strcat ( cmd_buf, dest_addr_high );
    strcat ( cmd_buf, XBEE2_DELIMITER );
    strcat ( cmd_buf, XBEE2_SET_DEST_ADDR_LOW );
    strcat ( cmd_buf, dest_addr_low );
    return xbee2_write_command ( ctx, cmd_buf );
}

err_t xbee2_set_api_mode ( xbee2_t *ctx, uint8_t api_mode )
{
    if ( api_mode > XBEE2_MODE_API_WITH_ESC )
    {
        return XBEE2_ERROR;
    }
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t api_mode_buf[ 2 ] = { api_mode + 48, 0 };
    strcpy ( cmd_buf, XBEE2_API_MODE );
    strcat ( cmd_buf, api_mode_buf );
    return xbee2_write_command ( ctx, cmd_buf );
}

err_t xbee2_set_device_role ( xbee2_t *ctx, uint8_t dev_role )
{
    if ( dev_role > XBEE2_DEVICE_ROLE_FORM_NETWORK )
    {
        return XBEE2_ERROR;
    }
    uint8_t cmd_buf[ 4 ] = { 0 };
    uint8_t dev_role_buf[ 2 ] = { dev_role + 48, 0 };
    strcpy ( cmd_buf, XBEE2_DEV_ROLE );
    strcat ( cmd_buf, dev_role_buf );
    return xbee2_write_command ( ctx, cmd_buf );
}

err_t xbee2_apply_changes ( xbee2_t *ctx )
{
    return xbee2_write_command ( ctx, XBEE2_APPLY_CHANGES );
}

err_t xbee2_save_changes ( xbee2_t *ctx )
{
    return xbee2_write_command ( ctx, XBEE2_SAVE_CHANGES );
}

// ------------------------------------------------------------------------- END
