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

#include "gnss6.h"
#include "string.h"

// -------------------------------------------------------------- PRIVATE MACRO

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

void gnss6_cfg_setup ( gnss6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->wkp = HAL_PIN_NC;
    cfg->pps = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_8;
    cfg->parity_bit     = UART_PARITY_NO;
    cfg->stop_bit       = UART_STOP_BITS_ONE;
    cfg->uart_blocking  = false;
}

GNSS6_RETVAL gnss6_init ( gnss6_t *ctx, gnss6_cfg_t *cfg )
{
    uart_pins_t uart_pins;

    uart_pins.tx_pin = cfg->tx_pin;
    uart_pins.rx_pin = cfg->rx_pin;
    
    uart_open( &ctx->uart, &uart_pins,
        &ctx->uart_rx_buffer, sizeof( ctx->uart_rx_buffer ),
        &ctx->uart_tx_buffer, sizeof( ctx->uart_tx_buffer )
    );

    uart_set_baud( &ctx->uart, cfg->baud_rate );
    uart_set_parity( &ctx->uart, cfg->parity_bit );
    uart_set_stop_bits( &ctx->uart, cfg->stop_bit );
    uart_set_data_bits( &ctx->uart, cfg->data_bit );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wkp, cfg->wkp );

    // Input pins

    digital_in_init( &ctx->pps, cfg->pps );

    return GNSS6_OK;
}

void gnss6_module_wakeup ( gnss6_t *ctx )
{
    digital_out_write( &ctx->rst, 1 );
    digital_out_write( &ctx->wkp, 1 );
}

void gnss6_module_reset ( gnss6_t *ctx )
{
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 1 );
}

void gnss6_set_wkp_pin ( gnss6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->wkp, state );
}

void gnss6_set_rst_pin ( gnss6_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t gnss6_get_pps_pin ( gnss6_t *ctx )
{
    return digital_in_read( &ctx->pps );
}

void gnss6_generic_write ( gnss6_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t gnss6_generic_read ( gnss6_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

gnss6_error_t gnss6_generic_parser 
( 
    char *rsp,  uint8_t command, 
    uint8_t element, char *parser_buf 
)
{    
    char *start_rsp;
    char *end_rsp;
    char rsp_buf[ 200 ];
    
    uint8_t element_cnt = 0;
    char *element_start;
    char *element_end;
    
    char current_cmd_buf[ 10 ];
    
    // check command and element
    if ( check_support_command( command, element, current_cmd_buf ) != 0 )
    {
        return GNSS6_ERROR_COMMAND_OR_ELEMENT;
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
        return GNSS6_ERROR_START_OR_END_COMMAND;
    }
    
    return GNSS6_NO_ERROR;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t check_support_command ( uint8_t command, uint8_t element, char *command_buf )
{
    switch ( command )
    {
        case GNSS6_NEMA_GPGGA:
        {
            strcpy( command_buf, "$GPGGA" );
            if ( element > GNSS6_NEMA_GPGGA_NUM_ELEMENT )
            {
                return PARSER_ELEMENT_NOT_SUPPORTED;
            }
            return PARSER_READY;
        }
        case GNSS6_NEMA_GPGLL:
        {
            strcpy( command_buf, "$GPGLL" );
            if ( element > GNSS6_NEMA_GPGLL_NUM_ELEMENT )
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

