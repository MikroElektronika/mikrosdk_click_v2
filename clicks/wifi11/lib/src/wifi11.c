/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "wifi11.h"
#include "string.h"
#include "conversions.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void wifi11_cfg_setup ( wifi11_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->en  = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;

    cfg->baud_rate      = 38400;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

WIFI11_RETVAL wifi11_init ( wifi11_t *ctx, wifi11_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    uart_cfg.rx_pin = cfg->rx_pin;  // UART RX pin. 
    uart_cfg.tx_pin = cfg->tx_pin;  // UART TX pin. 
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );  
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->gp1, cfg->gp1 );
    
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->gp1 );

    return WIFI11_OK;
}

void wifi11_generic_write ( wifi11_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t wifi11_generic_read ( wifi11_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void wifi11_reset_device ( wifi11_t *ctx )
{
    digital_out_high( &ctx->en );
    Delay_100ms( );
    digital_out_low( &ctx->en );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->en );
    Delay_100ms( );
}

void wifi11_send_cmd ( wifi11_t *ctx, char *cmd )
{
    char carriage_return = '\r';
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, &carriage_return, 1 );
    Delay_100ms(  );
}

void wifi11_send_cmd_with_parameter ( wifi11_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ DRV_TX_BUFFER_SIZE ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    wifi11_send_cmd( ctx, final_cmd );
}

void wifi11_connect_to_ap ( wifi11_t *ctx, char *ssid, char *password )
{
    char param_buf[ 100 ] = { 0 };
    char quatation_mark[ 2 ] = { '\"', 0 };
    char comma[ 2 ] = { ',', 0 };
    
    strcpy( param_buf, quatation_mark );
    strcat( param_buf, ssid );
    strcat( param_buf, quatation_mark );
    if ( *password != 0 )
    {
        strcat( param_buf, comma );
        strcat( param_buf, quatation_mark );
        strcat( param_buf, password );
        strcat( param_buf, quatation_mark );
    }
    
    wifi11_send_cmd_with_parameter( ctx, WIFI11_CMD_ATPN, param_buf );
}

void wifi11_create_tcp_udp_server ( wifi11_t *ctx, uint8_t mode, uint16_t port )
{
    char param_buf[ 20 ] = { 0 };
    char mode_buf[ 5 ] = { 0 };
    char port_buf[ 10 ] = { 0 };
    char comma[ 2 ] = { ',', 0 };
    
    if ( port > 65535 || port == 0 || mode > 1 )
    {
        return;
    }
    
    uint8_to_str ( mode, mode_buf );
    l_trim ( mode_buf );
    strcpy( param_buf, mode_buf );
    
    strcat( param_buf, comma );
    
    uint16_to_str ( port, port_buf );
    l_trim ( port_buf );
    strcat( param_buf, port_buf );
    
    wifi11_send_cmd_with_parameter( ctx, WIFI11_CMD_ATPS, param_buf );
}

// ------------------------------------------------------------------------- END

