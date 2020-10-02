
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

#include "wifi3.h"
#include "string.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void wifi3_write_at( wifi3_t* ctx , uint8_t* cmd , uint8_t len );
static uint8_t response_success( uint8_t* data_buf );

// ------------------------------------------------ PUBLIC CONSTANT DEFINITIONS

const wifi3_atcmd_t WIFI3_CHECK = { "AT" , 2 };
const wifi3_atcmd_t WIFI3_RST = { "AT+RST" , 6 };
const wifi3_atcmd_t WIFI3_CHECK_FIRMWARE = { "AT+GMR" , 6 };
const wifi3_atcmd_t WIFI3_SET_MODE = { "AT+CWMODE" , 9 };
const wifi3_atcmd_t WIFI3_CONNECT = { "AT+CWJAP" , 8 };
const wifi3_atcmd_t WIFI3_LIST_AP = { "AT+CWLAP" , 8 };
const wifi3_atcmd_t WIFI3_QUIT_AP = { "AT+CWQAP" , 8 };
const wifi3_atcmd_t WIFI3_SET_AP_PARAMETERS = { "AT+CWSAP" , 8 };
const wifi3_atcmd_t WIFI3_JOIN_DEV_IP = { "AT+CWLIF" , 8 };
const wifi3_atcmd_t WIFI3_CONNESTION_STATUS = { "AT+CIPSTATUS" , 12 };
const wifi3_atcmd_t WIFI3_START = { "AT+CIPSTART" , 11 };
const wifi3_atcmd_t WIFI3_MODE = { "AT+CIPMODE" , 10 };
const wifi3_atcmd_t WIFI3_SEND = { "AT+CIPSEND" , 10 };
const wifi3_atcmd_t WIFI3_CLOSE = { "AT+CIPCLOSE" , 11 };
const wifi3_atcmd_t WIFI3_GET_IP = { "AT+CIFSR" , 8 };
const wifi3_atcmd_t WIFI3_SET_MULTIPLE_CONNECTION = { "AT+CIPMUX" , 9 };
const wifi3_atcmd_t WIFI3_SET_AS_SERVER = { "AT+CIPSERVER" , 12 };
const wifi3_atcmd_t WIFI3_SET_SERVER_TIMEOUT = { "AT+CIPSTO?" , 10 };
const wifi3_atcmd_t WIFI3_RECEIVE = { "+IPD" , 4 };

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void wifi3_cfg_setup ( wifi3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->baud_rate      = 74880;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

WIFI3_RETVAL wifi3_init ( wifi3_t *ctx, wifi3_cfg_t *cfg )
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

    uart_open( &ctx->uart, &uart_cfg );
    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );  
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    uart_set_blocking( &ctx->uart, cfg->uart_blocking );

    // Output pins 

    digital_out_init( &ctx->an, cfg->an );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cs, cfg->cs );
    
    return WIFI3_OK;
}

void wifi3_generic_write ( wifi3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t wifi3_generic_read ( wifi3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

uint8_t wifi3_send_cmd( wifi3_t* ctx , log_t* logger , const wifi3_atcmd_t* cmd , uint8_t* args )
{
    uint16_t rsp_size = 0xFFFF;
    uint8_t r_buffer[ PROCESS_RX_BUFFER_SIZE ] = {0};
    uint8_t i = 0;
    volatile wifi3_atcmd_t tmp = {{0} , 0};
    
    memcpy( tmp.cmd , cmd->cmd , cmd->str_len);
    tmp.str_len = cmd->str_len;
    
    if( NULL != args )
    {
        strcat( tmp.cmd , "=" );
        strcat( tmp.cmd , args );
        strcat( tmp.cmd , "\r\n" );
        tmp.str_len += ( strlen( args ) + 3 );
    }
    
    for( i = 0; ( i < 10 ) & !response_success( r_buffer ); i++)
    {
       wifi3_write_at( ctx , tmp.cmd , tmp.str_len );
       Delay_1sec( );
       Delay_1sec( );
       rsp_size = wifi3_generic_read( ctx , r_buffer , PROCESS_RX_BUFFER_SIZE ); 
       if( 0xFFFF != rsp_size )
        {
            log_printf( logger , r_buffer );
            log_printf( logger , "\r\n" );
        }
    }
    
    if( i == 10 )
        return 0;
    
    return 1;
}

uint8_t wifi3_read( wifi3_t* ctx , uint8_t* read_buf )
{
    uint16_t rsp_size = 0xFFFF;
    uint8_t tmp_r_buffer[ PROCESS_RX_BUFFER_SIZE ] = {0};
    uint16_t i = 0;
    
    wifi3_write_at( ctx , WIFI3_RECEIVE.cmd , WIFI3_RECEIVE.str_len );
    Delay_1sec( );
    Delay_1sec( );
    
    for( i = 0; ( i < 65000 ) & ( 0xFFFF == rsp_size ) ; i++ )
    {
       rsp_size = wifi3_generic_read( ctx , read_buf , PROCESS_RX_BUFFER_SIZE );
    }
    
    if( 65000 == i )
        return 0;
    
    return 1;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void wifi3_write_at( wifi3_t* ctx , uint8_t* cmd , uint8_t len )
{
   uint8_t cr = 0x0D;
   uint8_t lf = 0x0A;
    
   wifi3_generic_write( ctx , cmd , len );
   wifi3_generic_write( ctx , &cr , 1 );
   wifi3_generic_write( ctx , &lf , 1 );
}

static uint8_t response_success( uint8_t* data_buf ) 
{
    if ( ( strstr( data_buf , "OK" ) ) || ( strstr( data_buf , "no change" ) ) || ( strstr( data_buf , "ready" ) )) 
    {
       return 1;
    }
    return 0;
}

// ------------------------------------------------------------------------- END

