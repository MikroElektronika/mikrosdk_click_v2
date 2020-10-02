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

#include "rn4870.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rn4870_cfg_setup ( rn4870_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->uart_rts = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->uart_cts = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

RN4870_RETVAL rn4870_init ( rn4870_t *ctx, rn4870_cfg_t *cfg )
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
    digital_out_init( &ctx->uart_rts, cfg->uart_rts );
    digital_out_init( &ctx->pwm, cfg->pwm );

    // Input pins

    digital_in_init( &ctx->uart_cts, cfg->uart_cts );

    return RN4870_OK;
}

void rn4870_uart_write ( rn4870_t *ctx, uint8_t *tx_data )
{
    uint16_t cnt;
    
    cnt = 0;

    while ( tx_data[ cnt ] != 0x00 )
    {
        rn4870_generic_write( ctx, &tx_data[ cnt ], 1 );
        cnt++;
    }
}

void rn4870_reset ( rn4870_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
}

void rn4870_initialize ( rn4870_t *ctx, char *dev_addr )
{
    rn4870_reset( ctx );

    rn4870_uart_write( ctx, "$$$" );
    Delay_100ms();
    
    rn4870_uart_write( ctx, "$$$\r" );
    Delay_1sec();
    
    rn4870_uart_write( ctx, "SF,1\r" );
    Delay_1sec();
    Delay_1sec();
    
    rn4870_uart_write( ctx, "$$$" );
    Delay_100ms();
    
    rn4870_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4870_uart_write( ctx, "SW,0A,0A\r" );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    
    rn4870_uart_write( ctx, "SW,0B,0B\r" );
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    
    rn4870_uart_write( ctx, "R,1\r" );
    Delay_1sec();
    Delay_1sec();
    
    rn4870_uart_write( ctx, "$$$" );
    Delay_100ms();
    
    rn4870_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4870_uart_write( ctx, "&," );
    rn4870_uart_write( ctx, dev_addr );
    
    rn4870_uart_write( ctx, "\r" );
    Delay_100ms();

    ctx->end_flag = 0;
    ctx->sen_flag = 0;
    ctx->tmp_pos = 0;
    memset( ctx->device_buffer, 0, 255 );
}


void rn4870_connect ( rn4870_t *ctx, char *dev_addr )
{
    rn4870_uart_write( ctx, "C,1," );
    rn4870_uart_write( ctx, dev_addr );
    rn4870_uart_write( ctx, "\r" );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();

    rn4870_uart_write( ctx, "B\r" );
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

void rn4870_disconnect ( rn4870_t *ctx )
{
    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
    
    rn4870_uart_write( ctx, "$$$" );
    Delay_100ms();
    
    rn4870_uart_write( ctx, "$$$\r" );
    Delay_1sec();

    rn4870_uart_write( ctx, "K,1\r" );
    Delay_1sec();
}

void rn4870_send ( rn4870_t *ctx, uint8_t msg_type, uint16_t data_type, uint8_t dev_id, uint8_t *tx_data )
{
    char msg_text[ 255 ];
    uint8_t d_buff[ 2 ];
    
    d_buff[ 0 ] = ( uint8_t ) ( data_type >> 8 );
    d_buff[ 1 ] = ( uint8_t ) data_type;

    msg_text[ 0 ] = '#';
    msg_text[ 1 ] = msg_type;
    msg_text[ 2 ] = ',';
    msg_text[ 3 ] = d_buff[ 0 ];
    msg_text[ 4 ] = d_buff[ 1 ];
    msg_text[ 5 ] = ',';
    msg_text[ 6 ] = dev_id;
    msg_text[ 7 ] = ',';
    msg_text[ 8 ] = '\0';
    strcat( msg_text, tx_data );
    strcat( msg_text, "*\r\n" );

    rn4870_uart_write( ctx, msg_text );
}

void rn4870_receive ( rn4870_t *ctx, char character )
{
    if ( character == '#' )
    {
        ctx->end_flag = 0x01;
        return;
    }

    if ( character == '\r' && ctx->end_flag == 0x01 )
    {
        ctx->end_flag = 0xFF;
        return;
    }

    if ( character == '\n' && ctx->end_flag == 0xFF )
    {
        ctx->device_buffer[ ctx->tmp_pos ] = '\0';
        ctx->tmp_pos = 0;

        ctx->end_flag = 0x00;
        ctx->sen_flag = 1;
        return;
    }

    if ( ctx->end_flag == 0x01 )
    {
        ctx->device_buffer[ ctx->tmp_pos ] = character;
        ctx->tmp_pos++;
        return;
    }
}

uint8_t rn4870_read ( rn4870_t *ctx, uint8_t *rx_data )
{
    uint8_t cnt;

    if ( ctx->sen_flag )
    {
        for ( cnt = 0; cnt <= 255; cnt++ )
        {
            if ( ctx->device_buffer[ cnt ] == '*' )
            {
                ctx->device_buffer[ cnt ] = 0;
                break;
            }
        }

        strcpy( rx_data, ctx->device_buffer );
        ctx->sen_flag = 0;
        
        return 1;
    }
    else
    {
        return 0;
    }
}

void rn4870_generic_write ( rn4870_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int16_t rn4870_generic_read ( rn4870_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t rn4870_get_interrupt ( rn4870_t *ctx )
{
    return digital_in_read( &ctx->uart_cts );
}

void rn4870_set_rst ( rn4870_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void rn4870_clear_rst ( rn4870_t *ctx )
{
    digital_out_low( &ctx->rst );
}

void rn4870_set_rts ( rn4870_t *ctx )
{
    digital_out_high( &ctx->uart_rts );
}

void rn4870_clear_rts ( rn4870_t *ctx )
{
    digital_out_low( &ctx->uart_rts );
}

void rn4870_set_pwm ( rn4870_t *ctx )
{
    digital_out_high( &ctx->pwm );
}

void rn4870_clear_pwm ( rn4870_t *ctx )
{
    digital_out_low( &ctx->pwm );
}

// ------------------------------------------------------------------------- END

