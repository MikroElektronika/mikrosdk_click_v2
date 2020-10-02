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

#include "ltecat1.h"
#include "string.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void ltecat1_cfg_setup ( ltecat1_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

LTECAT1_RETVAL ltecat1_init ( ltecat1_t *ctx, ltecat1_cfg_t *cfg )
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
    digital_out_init( &ctx->int_pin, cfg->int_pin );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->cs, cfg->cs );
    digital_in_init( &ctx->pwm, cfg->pwm );

    return LTECAT1_OK;
}

void ltecat1_module_power ( ltecat1_t *ctx, uint8_t power_state )
{
    if ( 0 != power_state )
    {
        //  POWER ON SEQUENCE
        digital_out_high( &ctx->rst );
        Delay_1sec();
        digital_out_low( &ctx->rst );
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
    }
    else
    {
        //  POWER OFF SEQUENCE
        digital_out_high( &ctx->rst );
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        digital_out_low( &ctx->rst );
        Delay_1sec();
        Delay_1sec();
        Delay_1sec();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
        Delay_100ms();
    }
}

void ltecat1_generic_write ( ltecat1_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t ltecat1_generic_read ( ltecat1_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void ltecat1_send_command ( ltecat1_t *ctx, char *command )
{
    char tmp_buf[ 100 ];
    uint8_t len;
    memset( tmp_buf, 0, 100 );
    len = strlen( command );
    
    strncpy( tmp_buf, command, len );
    strcat( tmp_buf, "\r\n" );

    ltecat1_generic_write( ctx, tmp_buf, strlen( tmp_buf ) );
}

char *ltecat1_gps_parser(char *data_in, char *cmd, uint8_t data_pos)
{
    volatile char *p_com;     // Pointer Start 
    volatile char *p_new;     // Pointer End 
    volatile char *p_return = 0;    // Pointer for return data 

    volatile char rsp_com[ 1000 ] = {0};     // Buffer for storage response of the cmd 
    volatile char p_data[ 100 ] = {0};       // Buffer for storage data 
    uint8_t n_pos = data_pos;                // Number of position data 
    uint8_t cur_pos = 0;                     // Current position 

    // Extracting the cmd 
    p_com = strstr( data_in, cmd );
    if ( p_com == 0 )
    {
        return p_return;
    }

    p_new = strchr( p_com + 1, '$' );
    if ( p_new == 0 )
    {
        return p_return;
    }

    strncpy( rsp_com, p_com, p_new - ( p_com ) );

    p_com = rsp_com;

    // Extracting the data

    while ( cur_pos != n_pos )
    {
        p_new = strchr( p_com, ',' );
        p_com = p_new + 1;

        if ( ( *(p_com) == ',' ) && ( ( cur_pos + 1 ) == n_pos ) ) 
        {
            return p_return;
        }
        cur_pos++;
    }
    p_new = strchr( p_com + 1, ',' );

    strncpy( p_data, p_com, p_new - ( p_com ) );
    p_return = p_data;

    return p_return;
}

// ------------------------------------------------------------------------- END

