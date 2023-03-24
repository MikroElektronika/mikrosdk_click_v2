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

#include "rn4871.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rn4871_cfg_setup ( rn4871_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst_n = HAL_PIN_NC;
    cfg->uart_rts = HAL_PIN_NC;
    cfg->uart_cts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

RN4871_RETVAL rn4871_init ( rn4871_t *ctx, rn4871_cfg_t *cfg )
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

     digital_out_init( &ctx->rst_n, cfg->rst_n );
     digital_out_init( &ctx->uart_rts, cfg->uart_rts );

    // Input pins

     digital_in_init( &ctx->uart_cts, cfg->uart_cts );  

    return RN4871_OK;
}

void rn4871_reset ( rn4871_t *ctx )
{
    digital_out_high( &ctx->rst_n );
    Delay_100ms( );
    digital_out_low( &ctx->rst_n );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_high( &ctx->rst_n );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

void rn4871_generic_write ( rn4871_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t rn4871_generic_read ( rn4871_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t rn4871_int_get ( rn4871_t *ctx )
{
    return digital_in_read ( &ctx->uart_cts );
}

void rn4871_rst_set ( rn4871_t *ctx, uint8_t pin_state )
{
   digital_out_write( &ctx->rst_n, pin_state );
}

void rn4871_cs_set ( rn4871_t *ctx, uint8_t pin_state )
{
    digital_out_write( &ctx->uart_rts, pin_state );
}

void rn4871_uart_write ( rn4871_t *ctx, uint8_t * wr_buf )
{
    uint16_t i = 0;

    while ( wr_buf[ i ] != 0x00 )
    {
        uart_write( &ctx->uart, &wr_buf[ i ], 1 );
        i ++;
    }
}

void rn4871_initialize ( rn4871_t *ctx, char *p_addr )
{
    digital_out_low( &ctx->rst_n );
    Delay_100ms( );
    digital_out_high( &ctx->rst_n );
    Delay_100ms( );
    Delay_100ms( );
    rn4871_uart_write( ctx, "$" );
    Delay_100ms( );
    rn4871_uart_write( ctx, "$$$" );
    Delay_100ms( );
    Delay_100ms( );
    rn4871_uart_write( ctx, "SF,1\r" );
    Delay_1sec( );
    Delay_1sec( );
    rn4871_uart_write( ctx, "$" );
    Delay_100ms( );
    rn4871_uart_write( ctx, "$$$" );
    Delay_100ms( );

    // Enables data transfer services 
    rn4871_uart_write( ctx, "SS,C0\r" );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    // Reboots the device for change to take effect 
    rn4871_uart_write( ctx, "R,1\r" );
    Delay_1sec( );
    Delay_1sec( );
    rn4871_uart_write( ctx, "$" );
    Delay_100ms( );
    rn4871_uart_write( ctx, "$$$" );
    Delay_1sec( );

    // Sets the address of the click 
    rn4871_uart_write( ctx, "&," );
    rn4871_uart_write( ctx, p_addr );
    rn4871_uart_write( ctx, "\r" );
    Delay_100ms( );

    // Initializes sentence buffer
    ctx->end_flag = 0;
    ctx->sentence_flag = 0;
    ctx->buffer_position = 0;
    memset( ctx->device_buffer, 0, 255 );
}

void rn4871_connect ( rn4871_t *ctx, char *p_addr )
{
    // Connects to a device with specified adress
    rn4871_uart_write( ctx, "C,1," );
    rn4871_uart_write( ctx, p_addr );
    rn4871_uart_write( ctx, "\r" );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    // Secures the connection, entering data stream mode
    rn4871_uart_write( ctx, "B\r" );
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
}

void rn4871_send ( rn4871_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t id, uint8_t *payload )
{
    char msg_txt[ 255 ];

    //Sentence construction
    msg_txt[ 0 ] = '#';
    msg_txt[ 1 ] = msg_type;
    msg_txt[ 2 ] = ',';
    msg_txt[ 3 ] = data_type / 0x100;
    msg_txt[ 4 ] = data_type % 0x100;
    msg_txt[ 5 ] = ',';
    msg_txt[ 6 ] = id;
    msg_txt[ 7 ] = ',';
    msg_txt[ 8 ] = '\0';
    strcat( msg_txt, payload );
    strcat( msg_txt, "*\r\n" );

    rn4871_uart_write( ctx, msg_txt );
}

void rn4871_disconnect ( rn4871_t *ctx )
{
    Delay_1sec( );
    Delay_1sec( );
    Delay_1sec( );
    // Enters CMD mode
    rn4871_uart_write( ctx, "$" );
    Delay_100ms( );
    rn4871_uart_write( ctx, "$$$" );
    Delay_1sec( );
    // Kills connection
    rn4871_uart_write( ctx, "K,1\r" );
    Delay_1sec( );
}

void rn4871_receive ( rn4871_t *ctx, char tmp )
{
    // Checks if first character of the sentence is #, to avoid parsing RN4xxx status messages
    if ( tmp == '#' )    
    {
        ctx->end_flag = 0x01;
        return;
    }

    if ( tmp == '\r' && ctx->end_flag == 0x01 )
    {
        ctx->end_flag = 0xFF;
        return;
    }

    if ( tmp == '\n' && ctx->end_flag == 0xFF )
    {
        ctx->device_buffer[ ctx->buffer_position ] = '\0';
        ctx->buffer_position = 0;

        ctx->end_flag = 0x00;
        ctx->sentence_flag = 1;
        return;
    }

    if ( ctx->end_flag == 0x01 )
    {
        ctx->device_buffer[ ctx->buffer_position ] = tmp;
        ctx->buffer_position++;
        return;
    }
}

uint8_t rn4871_read ( rn4871_t *ctx, uint8_t *process_buffer )
{
    uint8_t i;
    
    if ( ctx->sentence_flag )
    {
        for ( i = 0; i <= 255; i ++ )
        {
            if ( ctx->device_buffer[ i ] == '*' )
            {
                ctx->device_buffer[ i ] = 0;
                break;
            }
        }
        
        strcpy( process_buffer, ctx->device_buffer );
        ctx->sentence_flag = 0;
        return 1;
    }
    else return 0;
}

// ------------------------------------------------------------------------- END

