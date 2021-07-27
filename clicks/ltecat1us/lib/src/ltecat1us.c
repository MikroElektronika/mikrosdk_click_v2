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
 * @file ltecat1us.c
 * @brief LTE Cat.1-US Click Driver.
 */

#include "ltecat1us.h"
#include "string.h"

void ltecat1us_cfg_setup ( ltecat1us_cfg_t *cfg ) {
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts   = HAL_PIN_NC;
    cfg->cs = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t ltecat1us_init ( ltecat1us_t *ctx, ltecat1us_cfg_t *cfg ) {
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
    digital_out_init( &ctx->cs, cfg->cs );
    digital_out_init( &ctx->rts, cfg->rts );

    // Input pins

    digital_in_init( &ctx->cts, cfg->cts );

    digital_out_high( &ctx->cs );

    return UART_SUCCESS;
}

void ltecat1us_generic_write ( ltecat1us_t *ctx, char *data_buf, uint16_t len ) {
    uart_write( &ctx->uart, data_buf, len );
}

int32_t ltecat1us_generic_read ( ltecat1us_t *ctx, char *data_buf, uint16_t max_len ) {
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ltecat1us_power_on ( ltecat1us_t *ctx ) {
    digital_out_high( &ctx->rst );
    Delay_100ms();
    digital_out_low( &ctx->rst );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

void ltecat1us_set_rst ( ltecat1us_t *ctx, uint8_t state ) {
    if ( state > 0 ) {
        digital_out_high( &ctx->rst );
    } else {
        digital_out_low( &ctx->rst );
    }
}

void ltecat1us_set_rts ( ltecat1us_t *ctx, uint8_t state ) {
    if ( state > 0 ) {
        digital_out_high( &ctx->rts );
    } else {
        digital_out_low( &ctx->rts );
    }
}

uint8_t ltecat1us_get_cts ( ltecat1us_t *ctx ) {
    return digital_in_read( &ctx->cts );
}

void ltecat1us_send_cmd ( ltecat1us_t *ctx, char *cmd ) {
    char cr_lf[ 3 ] = { 13, 10, 0 };
    
    while ( *cmd != 0 ) {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    
    uart_write( &ctx->uart, cr_lf, 2 );
    Delay_100ms(  );
}

void ltecat1us_send_cmd_with_parameter ( ltecat1us_t *ctx, char *at_cmd_buf, char *param_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    strcat( final_cmd, param_buf );
    
    ltecat1us_send_cmd( ctx, final_cmd );
}

void ltecat1us_send_cmd_check ( ltecat1us_t *ctx, char *at_cmd_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    ltecat1us_send_cmd( ctx, final_cmd );
}

void ltecat1us_send_cmd_parameter_check ( ltecat1us_t *ctx, char *at_cmd_buf ) {
    char final_cmd[ 100 ] = { 0 };
    char check_char[ 3 ] = { '=' , '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    ltecat1us_send_cmd( ctx, final_cmd );
}

void ltecat1us_set_sim_apn ( ltecat1us_t *ctx, char *sim_apn ) {
    char final_cmd[ 50 ] = "1,\"IP\",\"";
    char end_cmd[ 3 ] = "\"";
    
    strcat( final_cmd, sim_apn );
    strcat( final_cmd, end_cmd );
    
    ltecat1us_send_cmd_with_parameter( ctx, LTECAT1US_CMD_CGDCONT, final_cmd );
}

void ltecat1us_send_text_message ( ltecat1us_t *ctx, char *phone_number, char *message_context ) {
    char text[ 200 ] = { 0 };
    char cmd_start[] = "AT+CMGS=\"";
    char cmd_end[] = "\"\r\032";
    
    char txt_end[] = "\032";
    
    strcpy( text, cmd_start );
    strcat( text, phone_number );
    strcat( text, cmd_end );
    
    ltecat1us_send_cmd( ctx, text );
    memset( text, 0 , 200 );
    
    strcpy( text, message_context );
    strcat( text, txt_end );
    ltecat1us_send_cmd( ctx, text );
}

// ------------------------------------------------------------------------- END
