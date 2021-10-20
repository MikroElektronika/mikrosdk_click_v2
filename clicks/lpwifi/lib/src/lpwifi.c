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
 * @file lpwifi.c
 * @brief LP WiFi Click Driver.
 */

#include "lpwifi.h"
#include "conversions.h"

void lpwifi_cfg_setup ( lpwifi_cfg_t *cfg ) 
{
    // Communication gpio pins

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins

    cfg->wkp        = HAL_PIN_NC;
    cfg->int_pin    = HAL_PIN_NC;
    cfg->cs         = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t lpwifi_init ( lpwifi_t *ctx, lpwifi_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wkp, cfg->wkp );
    digital_out_init( &ctx->cs, cfg->cs );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return UART_SUCCESS;
}

void lpwifi_default_cfg ( lpwifi_t *ctx ) 
{
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->wkp );
    Delay_1sec( );
}

err_t lpwifi_generic_write ( lpwifi_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t lpwifi_generic_read ( lpwifi_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void lpwifi_factory_reset_device ( lpwifi_t *ctx )
{
    lpwifi_send_cmd( ctx, LPWIFI_CMD_ATF );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

void lpwifi_send_cmd ( lpwifi_t *ctx, char *cmd )
{
    char cr_lf[ 3 ] = { '\r', '\n', 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
}

void lpwifi_send_cmd_with_parameter ( lpwifi_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ DRV_BUFFER_SIZE ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    lpwifi_send_cmd( ctx, final_cmd );
}

void lpwifi_send_cmd_check ( lpwifi_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lpwifi_send_cmd( ctx, final_cmd );
}

void lpwifi_connect_to_ap ( lpwifi_t *ctx, char *ssid, char *password )
{
    char param_buf[ 100 ] = { 0 };
    char single_quote[ 2 ] = { '\'', 0 };
    char comma[ 2 ] = { ',', 0 };
    
    strcpy( param_buf, single_quote );
    strcat( param_buf, ssid );
    strcat( param_buf, single_quote );
    if ( 0 != *password  )
    {
        strcat( param_buf, comma );
        strcat( param_buf, single_quote );
        strcat( param_buf, password );
        strcat( param_buf, single_quote );
    }
    
    lpwifi_send_cmd_with_parameter( ctx, LPWIFI_CMD_WFJAPA, param_buf );
}

void lpwifi_set_wifi_mode ( lpwifi_t *ctx, uint8_t mode )
{
    char mode_buf[ 5 ] = { 0 };
    
    if ( mode > LPWIFI_MODE_SOFT_AP )
    {
        return;
    }
    uint8_to_str ( mode, mode_buf );
    l_trim ( mode_buf );
    lpwifi_send_cmd_with_parameter( ctx, LPWIFI_CMD_WFMODE, mode_buf );
}

void lpwifi_create_tcp_server ( lpwifi_t *ctx, uint16_t port )
{
    char port_buf[ 10 ] = { 0 };
    
    if ( 0 == port )
    {
        return;
    }
    
    uint16_to_str ( port, port_buf );
    l_trim ( port_buf );
    
    lpwifi_send_cmd_with_parameter( ctx, LPWIFI_CMD_TRTS, port_buf );
}

void lpwifi_create_udp_socket ( lpwifi_t *ctx, uint16_t port )
{
    char port_buf[ 10 ] = { 0 };
    
    if ( 0 == port )
    {
        return;
    }
    
    uint16_to_str ( port, port_buf );
    l_trim ( port_buf );
    
    lpwifi_send_cmd_with_parameter( ctx, LPWIFI_CMD_TRUSE, port_buf );
}

// ------------------------------------------------------------------------- END
