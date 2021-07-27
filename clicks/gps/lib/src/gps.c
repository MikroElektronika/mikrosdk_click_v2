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

#include "gps.h"
#include "string.h"
#include "generic_pointer.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define PARSER_READY 0
#define PARSER_COMMAND_NOT_SUPPORTED 1
#define PARSER_ELEMENT_NOT_SUPPORTED 2

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t check_support_command 
( 
    uint8_t command, 
    uint8_t element, 
    char *command_buf 
);

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gps_cfg_setup ( gps_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->reset = HAL_PIN_NC;
    cfg->tmpls = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

GPS_RETVAL gps_init ( gps_t *ctx, gps_cfg_t *cfg )
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

    digital_out_init( &ctx->reset, cfg->reset );

    // Input pins
   
    digital_in_init( &ctx->tmpls, cfg->tmpls );
    
    return GPS_OK;
}

void gps_module_wakeup ( gps_t *ctx )
{
    digital_out_write( &ctx->reset, 1 );
    Delay_100ms( );
    digital_out_write( &ctx->reset, 0 );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_write( &ctx->reset, 1 );
    Delay_100ms( );
}

void gps_set_rst_pin ( gps_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->reset, state );
}

uint8_t gps_get_tmpls_pin ( gps_t *ctx )
{
    return digital_in_read( &ctx->tmpls );
}

void gps_generic_write ( gps_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t gps_generic_read ( gps_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

gps_error_t gps_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
)
{    
    char * __generic start_rsp;
    char * __generic end_rsp;
    char rsp_buf[ 200 ];
    
    uint8_t element_cnt = 0;
    char * __generic element_start;
    char * __generic element_end;
    
    char current_cmd_buf[ 10 ];
    
    // check command and element
    if ( check_support_command( command, element, current_cmd_buf ) != 0 )
    {
        return GPS_ERROR_COMMAND_OR_ELEMENT;
    }
    
    start_rsp = strstr( rsp, current_cmd_buf );
    end_rsp = strstr( start_rsp + 1 , "$" );
    
    if ( ( end_rsp != 0 ) && ( start_rsp != 0 ) )
    {
        strncpy( rsp_buf, start_rsp, end_rsp - start_rsp );
        element_start = rsp_buf;
        
        while ( element_cnt++ < element )
        {
            element_start = strstr( element_start, "," );
            if ( element_start != 0 )
            {
                element_start++;
            }
        }
        element_end = strstr( element_start, "," );
        
        if ( ( element_start != 0 ) && ( element_end != 0 ) )
        {
            strncpy( parser_buf, element_start, element_end - element_start );
        }
    }
    else
    {
        return GPS_ERROR_START_OR_END_COMMAND;
    }
    
    return GPS_NO_ERROR;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t check_support_command ( uint8_t command, uint8_t element, char *command_buf )
{
    switch ( command )
    {
        case GPS_NEMA_GPGGA:
        {
            strcpy( command_buf, "$GPGGA" );
            if ( element > GPS_NEMA_GPGGA_NUM_ELEMENT )
            {
                return PARSER_ELEMENT_NOT_SUPPORTED;
            }
            return PARSER_READY;
        }
        case GPS_NEMA_GPGLL:
        {
            strcpy( command_buf, "$GPGLL" );
            if ( element > GPS_NEMA_GPGLL_NUM_ELEMENT )
            {
                return PARSER_ELEMENT_NOT_SUPPORTED;
            }
            return PARSER_READY;
        }
        default:
        {
            return PARSER_COMMAND_NOT_SUPPORTED;
        }
    }
}

// ------------------------------------------------------------------------- END

