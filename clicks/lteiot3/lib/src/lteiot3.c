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
 * @file lteiot3.c
 * @brief LTE IoT 3 Click Driver.
 */

#include "lteiot3.h"

void lteiot3_cfg_setup ( lteiot3_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->smi = HAL_PIN_NC;
    cfg->on  = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->cs  = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t lteiot3_init ( lteiot3_t *ctx, lteiot3_cfg_t *cfg ) 
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
    digital_out_init( &ctx->smi, cfg->smi );
    digital_out_init( &ctx->on, cfg->on );
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    digital_out_low( &ctx->smi );
    digital_out_low( &ctx->cs );
    digital_out_low( &ctx->rts );
    
    return UART_SUCCESS;
}

err_t lteiot3_default_cfg ( lteiot3_t *ctx ) 
{
    lteiot3_set_pin_on( ctx, 1 );
    Delay_1sec(  );
    
    return LTEIOT3_OK;
}

err_t lteiot3_generic_write ( lteiot3_t *ctx, char *data_buf, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_buf, len );
}

err_t lteiot3_generic_read ( lteiot3_t *ctx, char *data_buf, uint16_t max_len ) 
{
    return uart_read( &ctx->uart, data_buf, max_len );
}


void lteiot3_set_pin_on ( lteiot3_t *ctx, uint8_t state )
{
    if ( state == 1 ) 
    {
        digital_out_high( &ctx->on );
    } 
    else 
    {
        digital_out_low( &ctx->on );
    }
}

void lteiot3_send_cmd ( lteiot3_t *ctx, char *cmd )
{
    char cr_lf[ 3 ] = { 13, 10, 0 };
    
    digital_out_low( &ctx->rts );
    while ( digital_in_read( &ctx->cts ) );
    Delay_10ms(  );
    
    while ( *cmd != 0 ) {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
    Delay_100ms(  );
}

void lteiot3_send_cmd_with_parameter ( lteiot3_t *ctx, char *at_cmd_buf, char *param_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    lteiot3_send_cmd( ctx, final_cmd );
}

void lteiot3_send_cmd_check ( lteiot3_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot3_send_cmd( ctx, final_cmd );
}

void lteiot3_send_cmd_parameter_check ( lteiot3_t *ctx, char *at_cmd_buf )
{
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    lteiot3_send_cmd( ctx, final_cmd );
}

void lteiot3_set_sim_apn ( lteiot3_t *ctx, char *sim_apn )
{
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    lteiot3_send_cmd_with_parameter( ctx, LTEIOT3_CMD_CGDCONT, final_cmd );
}

void lteiot3_send_text_message ( lteiot3_t *ctx, char *phone_number, char *message_context )
{
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r\032";
    
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    lteiot3_send_cmd( ctx, text );
    memset( text, 0 , 200 );
    
    strcpy( text, message_context );
    strcat( text, txt_end );
    lteiot3_send_cmd( ctx, text );
}

// ------------------------------------------------------------------------- END
