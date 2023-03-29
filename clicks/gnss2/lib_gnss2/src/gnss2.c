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
 * @file gnss2.c
 * @brief GNSS 2 Click Driver.
 */

#include "gnss2.h"
#include "generic_pointer.h"

void gnss2_cfg_setup ( gnss2_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->fon = HAL_PIN_NC;
    cfg->stb = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t gnss2_init ( gnss2_t *ctx, gnss2_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins
    digital_in_init( &ctx->fon, cfg->fon );
    digital_in_init( &ctx->stb, cfg->stb );
    
    digital_out_high( &ctx->rst );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t gnss2_generic_write ( gnss2_t *ctx, char *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t gnss2_generic_read ( gnss2_t *ctx, char *data_out, uint16_t len )
{    
    return uart_read( &ctx->uart, data_out, len );
}

void gnss2_clear_ring_buffers ( gnss2_t *ctx )
{    
    uart_clear( &ctx->uart );
}

void gnss2_set_rst_pin ( gnss2_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t gnss2_get_fon_pin ( gnss2_t *ctx )
{
    return digital_in_read ( &ctx->fon );
}

uint8_t gnss2_get_stb_pin ( gnss2_t *ctx )
{
    return digital_in_read ( &ctx->stb );
}

err_t gnss2_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data )
{    
    if ( gpgga_element > GNSS2_GPGGA_ELEMENT_SIZE )
    {
        return GNSS2_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, GNSS2_RSP_GPGGA );
    if ( start_ptr )
    {
        if ( !strstr( start_ptr, GNSS2_RSP_END_SEQ ) )
        {
            return GNSS2_ERROR;
        }
        if ( strstr( start_ptr + 1, GNSS2_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gpgga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS2_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS2_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, GNSS2_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS2_OK;
            }
        }
    }
    return GNSS2_ERROR;
}

// ------------------------------------------------------------------------- END
