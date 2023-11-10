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
 * @file rtkrover.c
 * @brief RTK Rover Click Driver.
 */

#include "rtkrover.h"
#include "generic_pointer.h"

void rtkrover_cfg_setup ( rtkrover_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->shd = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->bt  = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t rtkrover_init ( rtkrover_t *ctx, rtkrover_cfg_t *cfg ) 
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
    digital_out_init( &ctx->shd, cfg->shd );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wup, cfg->wup );
    digital_out_init( &ctx->bt, cfg->bt );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    digital_out_high( &ctx->shd );
    digital_out_high( &ctx->rst );
    digital_out_low( &ctx->wup );
    digital_out_low( &ctx->bt );
    Delay_100ms ( );

    return UART_SUCCESS;
}

err_t rtkrover_generic_write ( rtkrover_t *ctx, char *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t rtkrover_generic_read ( rtkrover_t *ctx, char *data_out, uint16_t len )
{    
    return uart_read( &ctx->uart, data_out, len );
}

void rtkrover_clear_ring_buffers ( rtkrover_t *ctx )
{    
    uart_clear( &ctx->uart );
}

void rtkrover_set_rst_pin ( rtkrover_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void rtkrover_set_wup_pin ( rtkrover_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wup, state );
}

void rtkrover_set_boot_pin ( rtkrover_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->bt, state );
}

void rtkrover_set_shd_pin ( rtkrover_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->shd, state );
}

uint8_t rtkrover_get_int_pin ( rtkrover_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtkrover_parse_gngga ( char *rsp_buf, uint8_t gngga_element, char *element_data )
{    
    if ( gngga_element > RTKROVER_GNGGA_ELEMENT_SIZE )
    {
        return RTKROVER_ERROR;
    }
    char * __generic_ptr start_ptr = strstr( rsp_buf, RTKROVER_RSP_GNGGA );
    if ( start_ptr )
    {
        if ( !strstr( start_ptr, RTKROVER_RSP_END_SEQ ) )
        {
            return RTKROVER_ERROR;
        }
        if ( strstr( start_ptr + 1, RTKROVER_RSP_START ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gngga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, RTKROVER_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return RTKROVER_ERROR;
                }
            }
            char * __generic_ptr end_ptr = strstr( start_ptr, RTKROVER_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return RTKROVER_OK;
            }
        }
    }
    return RTKROVER_ERROR;
}

// ------------------------------------------------------------------------- END
