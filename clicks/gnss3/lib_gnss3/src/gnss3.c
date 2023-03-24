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

#include "gnss3.h"
#include "string.h"
#include "generic_pointer.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void gnss3_cfg_setup ( gnss3_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t gnss3_init ( gnss3_t *ctx, gnss3_cfg_t *cfg )
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return GNSS3_OK;
}

void gnss3_module_wakeup ( gnss3_t *ctx )
{
    digital_out_write( &ctx->rst, 1 );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 0 );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_write( &ctx->rst, 1 );
}

void gnss3_set_rst_pin ( gnss3_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->rst, state );
}

uint8_t gnss3_get_int_pin ( gnss3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void gnss3_generic_write ( gnss3_t *ctx, char *data_buf, uint16_t len )
{
    uart_write( &ctx->uart, data_buf, len );
}

int32_t gnss3_generic_read ( gnss3_t *ctx, char *data_buf, uint16_t max_len )
{
    return uart_read( &ctx->uart, data_buf, max_len );
}

err_t gnss3_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data )
{    
    if ( gngga_element > GNSS3_GNGGA_ELEMENT_SIZE )
    {
        return GNSS3_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, GNSS3_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr + 1, GNSS3_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS3_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS3_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, GNSS3_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS3_OK;
            }
        }
    }
    return GNSS3_ERROR;
}

// ------------------------------------------------------------------------- END

