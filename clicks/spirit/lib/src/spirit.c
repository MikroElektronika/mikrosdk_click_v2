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
 * @file spirit.c
 * @brief SPIRIT Click Driver.
 */

#include "spirit.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void spirit_cfg_setup ( spirit_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    
    cfg->rst = HAL_PIN_NC;
    cfg->cmd   = HAL_PIN_NC;
    cfg->shd = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t spirit_init ( spirit_t *ctx, spirit_cfg_t *cfg ) {
    uart_config_t uart_cfg;

    // Default config
    
    uart_configure_default( &uart_cfg );

    // Ring buffer mapping
    
    ctx->uart.tx_ring_buffer = ctx->uart_tx_buffer;
    ctx->uart.rx_ring_buffer = ctx->uart_rx_buffer;

    // UART module config
    
    uart_cfg.rx_pin = cfg->rx_pin;         // UART RX pin.
    uart_cfg.tx_pin = cfg->tx_pin;         // UART TX pin.
    uart_cfg.tx_ring_size = sizeof( ctx->uart_tx_buffer );
    uart_cfg.rx_ring_size = sizeof( ctx->uart_rx_buffer );

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR ) {
        return UART_ERROR;
    }
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cmd, cfg->cmd );
    digital_out_init( &ctx->shd, cfg->shd );
    
    return UART_SUCCESS;
}

void spirit_power_module ( spirit_t *ctx, uint8_t power_state ) {
    if ( power_state != 0 ) {
        digital_out_high( &ctx->shd ); 
        Delay_100ms( );
        Delay_100ms( );
        Delay_100ms( );
    }
    else {
        digital_out_low( &ctx->shd ); 
        Delay_100ms( );
        Delay_100ms( );
        Delay_100ms( );
    }
}

void spirit_reset ( spirit_t *ctx ) {
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

void spirit_set_mode ( spirit_t *ctx, uint8_t mode ) {
    if ( mode != 0 ) {
        digital_out_high( &ctx->cmd ); 
        Delay_100ms( );
    }
    else  {
        digital_out_low( &ctx->shd ); 
        Delay_100ms( );
    }
}

void spirit_generic_write ( spirit_t *ctx, char *data_buf, uint16_t len ) {
    uart_write( &ctx->uart, data_buf, len );
}

int32_t spirit_generic_read ( spirit_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void spirit_send_cmd ( spirit_t *ctx, char *cmd )
{
    char cr_lf[ 3 ] = { 13, 10, 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
    Delay_100ms(  );
}

void spirit_send_cmd_with_parameter ( spirit_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    spirit_send_cmd( ctx, final_cmd );
}

void spirit_send_cmd_check ( spirit_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    spirit_send_cmd( ctx, final_cmd );
}

void spirit_send_cmd_parameter_check ( spirit_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    spirit_send_cmd( ctx, final_cmd );
}
// ------------------------------------------------------------------------- END
