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
 * @file anynet3gea.c
 * @brief AnyNet 3G-EA Click Driver.
 */

#include "anynet3gea.h"

void anynet3gea_cfg_setup ( anynet3gea_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->slp   = HAL_PIN_NC;
    cfg->dsr   = HAL_PIN_NC;
    cfg->dtr   = HAL_PIN_NC;
    cfg->iot   = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t anynet3gea_init ( anynet3gea_t *ctx, anynet3gea_cfg_t *cfg ) 
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
    digital_out_init( &ctx->dtr, cfg->dtr );
    digital_out_init( &ctx->iot, cfg->iot );

    // Input pins
    digital_in_init( &ctx->dsr, cfg->dsr );
    
    digital_out_low ( &ctx->slp );
    digital_out_low ( &ctx->dtr );
    digital_out_low ( &ctx->iot );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t anynet3gea_generic_write ( anynet3gea_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t anynet3gea_generic_read ( anynet3gea_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void anynet3gea_set_slp_pin ( anynet3gea_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->slp, state );
}

void anynet3gea_set_dtr_pin ( anynet3gea_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->dtr, state );
}

void anynet3gea_set_iot_pin ( anynet3gea_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->iot, state );
}

uint8_t anynet3gea_get_dsr_pin ( anynet3gea_t *ctx ) 
{
    return digital_in_read( &ctx->dsr );
}

void anynet3gea_send_cmd ( anynet3gea_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return = 13;
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    uart_write( &ctx->uart, &carriage_return, 1 );
    Delay_100ms(  );
}

void anynet3gea_send_cmd_with_par ( anynet3gea_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    anynet3gea_send_cmd( ctx, final_cmd );
}

void anynet3gea_send_cmd_check ( anynet3gea_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    anynet3gea_send_cmd( ctx, final_cmd );
}

void anynet3gea_send_cmd_par_check ( anynet3gea_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    anynet3gea_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
