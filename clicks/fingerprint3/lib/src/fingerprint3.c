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

#include "fingerprint3.h"
#include "string.h"

// ------------------------------------------------------------- PRIVATE MACROS 

typedef void (*dev_log)( uint8_t* ,uint8_t );

static uint16_t rsp_idx;
static uint8_t rx_buf[ 256 ] = "";
static dev_log log_write;

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 57600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

FINGERPRINT3_RETVAL fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg )
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

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    digital_out_high( &ctx->rst );

    return FINGERPRINT3_OK;
}

void fingerprint3_set_rst_pin ( fingerprint3_t *ctx, uint8_t rst_pin )
{
    if ( rst_pin == 1 )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void fingerprint3_generic_write ( fingerprint3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

uint16_t fingerprint3_generic_read ( fingerprint3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

void fingerprint3_process ( uint8_t tmp )
{
    uint16_t len;
    
    rx_buf[ rsp_idx ] = tmp;
    
    if ( rsp_idx == 8 )
    {
        len = rx_buf[ 7 ];
        len <<= 8;
        len |= rx_buf[ 8 ];
    }

    if ( ( rsp_idx < len + 9 ) && ( rsp_idx < 256 ) )
    {
        rsp_idx++;
    }
    else
    {
        memset( rx_buf, FINGERPRINT3_EMPTY_LOG, 255 );
        rsp_idx = 0;
    }
}

void fingerprint3_buf_clear ( void )
{
    memset( rx_buf, FINGERPRINT3_EMPTY_LOG, 255 );
    rsp_idx = 0;
}

void fingerprint3_parser_and_display_rsp ( fingerprint3_rsp_t *response )
{
    uint16_t tmp;
    uint32_t temp;
    uint16_t cnt;
    
    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    
    response->header = tmp;
    log_write( " \r\n", FINGERPRINT3_EMPTY_LOG );
    log_write( "* Header             : 0x%x \r\n", tmp );
    
    temp = rx_buf[ 2 ];
    temp <<= 8;
    temp |= rx_buf[ 3 ];
    temp <<= 8;
    temp |= rx_buf[ 4 ];
    temp <<= 8;
    temp |= rx_buf[ 5 ];
    
    response->addr = temp;
    log_write( "* Address            : 0x%x \r\n", temp );
    
    response->pkg_ident = rx_buf[ 6 ];
    log_write( "* Package identifier : 0x%s \r\n", rx_buf[ 6 ] );
    
    tmp = rx_buf[ 7 ];
    tmp <<= 8;
    tmp |= rx_buf[ 8 ];
    
    response->pkg_len = tmp;
    log_write( "* Package length     : 0x%x \r\n", tmp );
    
    response->confirm_code = rx_buf[ 9 ];
    log_write( "* Confirmation code  : ", FINGERPRINT3_EMPTY_LOG );
    
    if ( rx_buf[ 9 ] == 0x00 )
    {
        log_write( "OK \r\n", FINGERPRINT3_EMPTY_LOG );
    }
    else
    {
        log_write( " %x \r\n", rx_buf[ 9 ] );
    }
    
    if ( tmp > 3 )
    {
        log_write( " \r\n", FINGERPRINT3_EMPTY_LOG );
    }
    
    for ( cnt = 0; cnt < tmp - 3; cnt++ )
    {
        response->pkg_contents[ cnt ] = rx_buf[ cnt + 10 ];
        

        log_write( "* Message Content[", FINGERPRINT3_EMPTY_LOG );
        
        if ( cnt < 10 )
        {
            log_write( "0", FINGERPRINT3_EMPTY_LOG );
        }
        
        log_write( "%d ", cnt );
        log_write( "]: 0x%x \r\n", rx_buf[ cnt + 10 ] );
    }
    
    log_write( " \r\n", FINGERPRINT3_EMPTY_LOG );
    tmp = rx_buf[ cnt + 10 ];
    tmp <<= 8;
    tmp |= rx_buf[ cnt + 11 ];
    
    response->checksum = tmp;
    log_write( "** Checksum           : 0x%x \r\n", tmp );
    
    memset( rx_buf, FINGERPRINT3_EMPTY_LOG, 255 );
    rsp_idx = 0;
}

void fingerprint3_parser_rsp ( fingerprint3_rsp_t *response )
{
    uint16_t tmp;
    uint32_t temp;
    uint16_t cnt;

    tmp = rx_buf[ 0 ];
    tmp <<= 8;
    tmp |= rx_buf[ 1 ];
    response->header = tmp;

    temp = rx_buf[ 2 ];
    temp <<= 8;
    temp |= rx_buf[ 3 ];
    temp <<= 8;
    temp |= rx_buf[ 4 ];
    temp <<= 8;
    temp |= rx_buf[ 5 ];
    response->addr = temp;

    response->pkg_ident = rx_buf[ 6 ];

    tmp = rx_buf[ 7 ];
    tmp <<= 8;
    tmp |= rx_buf[ 8 ];
    response->pkg_len = tmp;

    response->confirm_code = rx_buf[ 9 ];

    for ( cnt = 0; cnt < tmp - 3; cnt++ )
    {
        response->pkg_contents[ cnt ] = rx_buf[ cnt + 10 ];
    }

    tmp = rx_buf[ cnt + 10 ];
    tmp <<= 8;
    tmp |= rx_buf[ cnt + 11 ];

    response->checksum = tmp;

    memset( rx_buf, 0, 255 );
    rsp_idx = 0;
}

uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

