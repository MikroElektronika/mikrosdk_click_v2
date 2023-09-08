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
 * @file esp8684.c
 * @brief ESP8684 Click Driver.
 */

#include "esp8684.h"
#include "string.h"
#include "conversions.h"

void esp8684_cfg_setup ( esp8684_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bt  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t esp8684_init ( esp8684_t *ctx, esp8684_cfg_t *cfg ) 
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
    digital_out_init( &ctx->bt, cfg->bt );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    return UART_SUCCESS;
}

void esp8684_default_cfg ( esp8684_t *ctx ) 
{
    esp8684_set_rst_pin( ctx, ESP8684_PIN_STATE_HIGH );
    esp8684_set_bt_pin( ctx, ESP8684_PIN_STATE_HIGH );
}

err_t esp8684_generic_write ( esp8684_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t esp8684_generic_read ( esp8684_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void esp8684_set_rst_pin ( esp8684_t *ctx, uint8_t pin_state )
{
    if ( ESP8684_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void esp8684_set_bt_pin ( esp8684_t *ctx, uint8_t pin_state )
{
    if ( ESP8684_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->bt );
    }
    else
    {
        digital_out_low( &ctx->bt );
    }
}

void esp8684_set_rts_pin ( esp8684_t *ctx, uint8_t pin_state )
{
    if ( ESP8684_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rts );
    }
    else
    {
        digital_out_low( &ctx->rts );
    }
}

uint8_t esp8684_get_cts_pin ( esp8684_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void esp8684_send_cmd ( esp8684_t *ctx, uint8_t *cmd, uint8_t *args )
{
    uint8_t final_cmd[ 100 ] = { 0 };

    strcpy( final_cmd, cmd );
    
    if( NULL != args )
    {
        strcat( final_cmd, "=" );
        strcat( final_cmd, args );
    }
    strcat( final_cmd, "\r\n" );

    esp8684_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}

void esp8684_send_query_cmd ( esp8684_t *ctx, uint8_t *cmd )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    
    strcpy( final_cmd, cmd );
    strcat( final_cmd, "?" );
    strcat( final_cmd, "\r\n" );
    
    esp8684_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}

void esp8684_send_test_cmd ( esp8684_t *ctx, uint8_t *cmd )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    
    strcpy( final_cmd, cmd );
    strcat( final_cmd, "=?" );
    strcat( final_cmd, "\r\n" );
    
    esp8684_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}

void esp8684_connect_to_network ( esp8684_t* ctx, uint8_t *ssid, uint8_t *password )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t at_cmd_buf[ 30 ] = "AT+CWJAP=\"";
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, ssid );
    strcat( final_cmd, "\",\"" );
    strcat( final_cmd, password );
    strcat( final_cmd, "\"\r\n" );
    
    esp8684_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}
void esp8684_connect_for_trans ( esp8684_t* ctx, uint8_t *type, uint8_t *link_id, 
                                        uint8_t *remote_host, uint8_t *remote_port )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t at_cmd_buf[ 30 ] = "AT+CIPSTART=";
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, link_id );
    strcat( final_cmd, ",\"" );
    strcat( final_cmd, type );
    strcat( final_cmd, "\",\"" );
    strcat( final_cmd, remote_host );
    strcat( final_cmd, "\"," );
    strcat( final_cmd, remote_port );
    strcat( final_cmd, "\r\n" );
    
    esp8684_generic_write( ctx, final_cmd, strlen( final_cmd ) );
}

// ------------------------------------------------------------------------- END
