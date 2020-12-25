/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright (c) 2019, MikroElektronika - www.mikroe.com
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*!
 * \file
 *
 */

#include "c4glte.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void c4glte_cfg_setup ( c4glte_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->sta = HAL_PIN_NC;
    cfg->pwk = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ri  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

C4GLTE_RETVAL c4glte_init ( c4glte_t *ctx, c4glte_cfg_t *cfg )
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

    digital_out_init( &ctx->pwk, cfg->pwk );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins

    digital_in_init( &ctx->sta, cfg->sta );
    digital_in_init( &ctx->ri, cfg->ri );
    digital_in_init( &ctx->cts, cfg->cts );

    return C4GLTE_OK;
}

void c4glte_module_power ( c4glte_t *ctx, uint8_t power_state )
{
    if ( 0 != power_state )
    {
//  POWER ON SEQUENCE
        digital_out_low( &ctx->rts );
        digital_out_low( &ctx->pwk );
        Delay_100ms();
        digital_out_high( &ctx->pwk );
        Delay_100ms();
        digital_out_low( &ctx->pwk );
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
    }
    else
    {
//  POWER OFF SEQUENCE

    }
}

void c4glte_generic_write ( c4glte_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}


int32_t c4glte_generic_read ( c4glte_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void c4glte_send_command ( c4glte_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r\n" );

    c4glte_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

// ------------------------------------------------------------------------- END

