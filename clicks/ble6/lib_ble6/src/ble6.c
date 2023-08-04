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
 * @file ble6.c
 * @brief BLE 6 Click Driver.
 */

#include "ble6.h"

void ble6_cfg_setup ( ble6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->an   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->bl   = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_NONE;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ble6_init ( ble6_t *ctx, ble6_cfg_t *cfg ) 
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
    digital_out_init( &ctx->bl, cfg->bl );

    // Input pins
    digital_in_init( &ctx->an, cfg->an );

    digital_out_low( &ctx->rst );
    digital_out_low( &ctx->bl );

    return UART_SUCCESS;
}

err_t ble6_generic_write ( ble6_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t ble6_generic_read ( ble6_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

int8_t ble6_strncmp ( uint8_t *string1, uint8_t *string2, uint8_t len )
{
    while ( len-- )
    {
        if ( ( ( *string1 ) == 0 ) || ( ( *string1 ) != ( *string2 ) ) )
        {
            return ( ( *string1 ) - ( *string2 ) );
        }
        string1++;
        string2++;
    }
    return 0;
}

uint8_t ble6_byte_ready ( ble6_t *ctx )
{
    return uart_bytes_available( &ctx->uart );
}

void ble6_power_on ( ble6_t *ctx, uint8_t en_pwr )
{
    if ( en_pwr == BLE6_MODULE_POWER_ON )
    {
        digital_out_high( &ctx->rst );
    } 
    else 
    {
        digital_out_low( &ctx->rst );
    }
}

void ble6_send_command ( ble6_t *ctx, uint8_t *tx_data, uint8_t n_bytes )
{
    uart_write( &ctx->uart, tx_data, n_bytes );
}

void ble6_set_response_handler ( void ( *handler )( uint8_t* ), ble6_hdl_t driver_hdl )
{
    driver_hdl = handler;
}

void ble6_set_handlers ( ble6_handler_t event_handler, ble6_handler_t eve_hdlr )
{
    eve_hdlr = event_handler;
}

void ble6_parser_rsp ( ble6_t *ctx, ble6_rsp_t *response )
{
    uint16_t cnt;
    uint16_t tmp;
    uint8_t rx_storage[ 256 ];
    
    ble6_generic_read( ctx, rx_storage, 256 );
    
    response->event_code = rx_storage[ 1 ];
    response->length = rx_storage[ 2 ];
    response->num_hci_cmd = rx_storage[ 3 ];
    
    tmp = rx_storage[ 5 ];
    tmp <<= 8;
    tmp |= rx_storage[ 4 ];

    response->cmd_opcode = tmp;
    
    response->status = rx_storage[ 6 ];

    for ( cnt = 0; cnt < rx_storage[ 2 ] - 4; cnt++ ) 
    {
        response->payload[ cnt ] = rx_storage[ cnt + 7 ];
    }
}

// ------------------------------------------------------------------------- END
