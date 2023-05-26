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
 * @file g2c3g.c
 * @brief G2C 3G Click Driver.
 */

#include "g2c3g.h"

void g2c3g_cfg_setup ( g2c3g_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->gp0 = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 57600;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t g2c3g_init ( g2c3g_t *ctx, g2c3g_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );

    // Input pins
    digital_in_init( &ctx->gp0, cfg->gp0 );
    digital_in_init( &ctx->gp1, cfg->gp1 );
    digital_in_init( &ctx->rts, cfg->rts );

    digital_out_low ( &ctx->cts );
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    
    return UART_SUCCESS;
}

err_t g2c3g_generic_write ( g2c3g_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t g2c3g_generic_read ( g2c3g_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void g2c3g_set_cts_pin ( g2c3g_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->cts, state );
}

void g2c3g_set_rst_pin ( g2c3g_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

uint8_t g2c3g_get_gp0_pin ( g2c3g_t *ctx ) 
{
    return digital_in_read( &ctx->gp0 );
}

uint8_t g2c3g_get_gp1_pin ( g2c3g_t *ctx ) 
{
    return digital_in_read( &ctx->gp1 );
}

uint8_t g2c3g_get_rts_pin ( g2c3g_t *ctx ) 
{
    return digital_in_read( &ctx->rts );
}

void g2c3g_reset_device ( g2c3g_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void g2c3g_send_cmd ( g2c3g_t *ctx, uint8_t *cmd )
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

void g2c3g_send_cmd_with_par ( g2c3g_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t equal_mark[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, equal_mark );
    strcat( final_cmd, param_buf );
    
    g2c3g_send_cmd( ctx, final_cmd );
}

void g2c3g_send_cmd_check ( g2c3g_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 22 ] = { 0 };
    uint8_t check_mark[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_mark );
    
    g2c3g_send_cmd( ctx, final_cmd );
}

void g2c3g_send_cmd_par_check ( g2c3g_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ 23 ] = { 0 };
    uint8_t test_cmd_mark[ 3 ] = { '=', '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, test_cmd_mark );
    
    g2c3g_send_cmd( ctx, final_cmd );
}

void g2c3g_set_net_creds ( g2c3g_t *ctx, uint8_t *sim_apn, uint8_t *username, uint8_t *password )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t cmd_separator[ 2 ] = { ',', 0 };
    uint8_t quote_mark[ 2 ] = { '\"', 0 };
    
    strcpy( final_cmd, quote_mark );
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, cmd_separator );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, username );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, cmd_separator );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, password );
    strcat( final_cmd, quote_mark );
    
    g2c3g_send_cmd_with_par( ctx, G2C3G_CMD_NWCR, final_cmd );
}

void g2c3g_set_broker_creds ( g2c3g_t *ctx, uint8_t *dev_key, uint8_t *password )
{
    uint8_t final_cmd[ 100 ] = { 0 };
    uint8_t cmd_separator[ 2 ] = { ',', 0 };
    uint8_t quote_mark[ 2 ] = { '\"', 0 };
    
    strcpy( final_cmd, quote_mark );
    strcat( final_cmd, dev_key );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, cmd_separator );
    strcat( final_cmd, quote_mark );
    strcat( final_cmd, password );
    strcat( final_cmd, quote_mark );
    
    g2c3g_send_cmd_with_par( ctx, G2C3G_CMD_BRCR, final_cmd );
}

// ------------------------------------------------------------------------- END
