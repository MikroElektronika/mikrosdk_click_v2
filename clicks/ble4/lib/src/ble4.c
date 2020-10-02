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

#include "ble4.h"
#include "string.h"

// ---------------------------------------------------------- PRIVATE VARIABLES

static uint8_t carriage_return = 13;

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void drv_send_cmd ( ble4_t *ctx, uint8_t *cmd );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ble4_cfg_setup ( ble4_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->dtr   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts   = HAL_PIN_NC;
    cfg->dsr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = true;
}

BLE4_RETVAL ble4_init ( ble4_t *ctx, ble4_cfg_t *cfg )
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->dsr, cfg->dsr );

    // Input pins

    digital_in_init( &ctx->dtr, cfg->dtr );
    digital_in_init( &ctx->rts, cfg->rts );

    // Pin configuration

    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->cts );
    digital_out_low( &ctx->dsr );

    return BLE4_OK;
}

void ble4_generic_write ( ble4_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t ble4_generic_read ( ble4_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ble4_uart_write ( ble4_t *ctx, uint8_t *w_data )
{
    uint16_t cnt;

    cnt = 0;

    while( w_data[ cnt ] != 0 )
    {
        ble4_generic_write( ctx, &w_data[ cnt++ ], 1 );
    }
}

void ble4_hardware_reset ( ble4_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void ble4_factory_reset ( ble4_t *ctx )
{
    drv_send_cmd( ctx, "AT+UFACTORY" );
    Delay_10ms( );
    Delay_10ms( );
    drv_send_cmd( ctx, "AT+CPWROFF" );
}

void ble4_set_device_name ( ble4_t *ctx, uint8_t *dev_name )
{
    uint8_t message[ 40 ] = "AT+UBTLN=";

    if ( strlen( dev_name ) > 29 )
    {
        ble4_uart_write( ctx, "AT+UBTLN=BLE Device" );
        ble4_generic_write( ctx, &carriage_return, 1 );
    }
    else
    {
        strcat( message, dev_name );

        ble4_uart_write( ctx, message );
        ble4_generic_write( ctx, &carriage_return, 1 );
    }
}

void ble4_set_data_mode ( ble4_t *ctx, uint8_t mode )
{
    uint8_t message[ 5 ] = "ATO";

    if ( mode < 4 )
    {
        message[ 3 ] = mode + 48;
    }
    else 
    {
        message[ 3 ] = 49;
    }

    message[ 4 ] = BLE4_END_BUFF;

    drv_send_cmd( ctx, message );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void drv_send_cmd ( ble4_t *ctx, uint8_t *cmd )
{
    while ( *cmd != BLE4_END_BUFF )
    {
        ble4_generic_write( ctx, cmd, 1 );
        cmd++;
    }

    ble4_generic_write( ctx, &carriage_return, 1 );
}

// ------------------------------------------------------------------------- END

