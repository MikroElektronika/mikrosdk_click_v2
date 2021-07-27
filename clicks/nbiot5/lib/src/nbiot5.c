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
 * @file nbiot5.c
 * @brief NB IoT 5 Click Driver.
 */

#include "nbiot5.h"

void nbiot5_cfg_setup ( nbiot5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wkp   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg ) 
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

    if ( uart_open( &ctx->uart, &uart_cfg ) == UART_ERROR )
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
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->en, cfg->en );

    return UART_SUCCESS;
}

err_t nbiot5_default_cfg ( nbiot5_t *ctx ) 
{
    digital_out_high( &ctx->wkp );
    digital_out_high( &ctx->rst );
    digital_out_high( &ctx->cs );
    digital_out_high( &ctx->en );
    Delay_1sec( );
    digital_out_low( &ctx->en );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    
    return 0;
}

err_t nbiot5_generic_write ( nbiot5_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t nbiot5_generic_read ( nbiot5_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void nbiot5_set_wkp ( nbiot5_t *ctx, uint8_t state )
{
    if ( state > 0 )
        digital_out_high( &ctx->wkp );
    else
        digital_out_low( &ctx->wkp );
}

void nbiot5_set_en ( nbiot5_t *ctx, uint8_t state )
{
    if ( state > 0 )
        digital_out_high( &ctx->en );
    else
        digital_out_low( &ctx->en );
}

void nbiot5_set_rst ( nbiot5_t *ctx, uint8_t state )
{
    if ( state > 0 )
        digital_out_high( &ctx->rst );
    else
        digital_out_low( &ctx->rst );
}

void nbiot5_set_cs ( nbiot5_t *ctx, uint8_t state )
{
    if ( state > 0 )
        digital_out_high( &ctx->cs );
    else
        digital_out_low( &ctx->cs );
}

void nbiot5_send_cmd ( nbiot5_t *ctx, char *cmd )
{
    char final_cmd[ 100 ] = { 0 };
    char cr_lf[ 3 ] = { 13, 10, 0 };
    
    while ( *cmd != 0 )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
    Delay_100ms(  );
}

void nbiot5_set_sim_apn ( nbiot5_t *ctx, char *sim_apn )
{
    char final_cmd[ 100 ] = "AT+CGDCONT=1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    nbiot5_send_cmd( ctx, final_cmd );
}

void nbiot5_send_text_message ( nbiot5_t *ctx, char *phone_number, char *message_context )
{
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r";
    
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    strcat( text, message_context );
    strcat( text, txt_end );
    nbiot5_send_cmd( ctx, text );
}

// ------------------------------------------------------------------------- END
