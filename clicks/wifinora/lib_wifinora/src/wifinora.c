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
 * @file wifinora.c
 * @brief WiFi NORA Click Driver.
 */

#include "wifinora.h"

void wifinora_cfg_setup ( wifinora_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wkp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->whs = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wifinora_init ( wifinora_t *ctx, wifinora_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->whs, cfg->whs );
    digital_in_init( &ctx->rts, cfg->rts );

    wifinora_set_rst_pin ( ctx, WIFINORA_PIN_STATE_HIGH );

    return UART_SUCCESS;
}

err_t wifinora_generic_write ( wifinora_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wifinora_generic_read ( wifinora_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void wifinora_set_rst_pin ( wifinora_t *ctx, uint8_t pin_state )
{
    if ( WIFINORA_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void wifinora_set_wkp_pin ( wifinora_t *ctx, uint8_t pin_state )
{
    if ( WIFINORA_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->wkp );
    }
    else
    {
        digital_out_low( &ctx->wkp );
    }
}

void wifinora_set_cts_pin ( wifinora_t *ctx, uint8_t pin_state )
{
    if ( WIFINORA_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

uint8_t wifinora_get_whs_pin ( wifinora_t *ctx )
{
    return digital_in_read( &ctx->whs );
}

uint8_t wifinora_get_rts_pin ( wifinora_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

void wifinora_hw_reset ( wifinora_t *ctx )
{
    wifinora_set_rst_pin ( ctx, WIFINORA_PIN_STATE_LOW );
    Delay_100ms( );
    wifinora_set_rst_pin ( ctx, WIFINORA_PIN_STATE_HIGH );
}

void wifinora_send_cmd ( wifinora_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t cmd_end[ 2 ] = { '\r', '\n' };
    while ( *at_cmd_buf != 0 )
    {
        uart_write( &ctx->uart, at_cmd_buf, 1 );
        at_cmd_buf++;
    }
    uart_write( &ctx->uart, cmd_end, 2 );
    Delay_100ms(  );
}

void wifinora_send_cmd_with_par ( wifinora_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    wifinora_send_cmd( ctx, final_cmd );
}

void wifinora_send_cmd_check ( wifinora_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    wifinora_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
