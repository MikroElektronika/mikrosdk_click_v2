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
 * @file gnss17.c
 * @brief GNSS 17 Click Driver.
 */

#include "gnss17.h"
#include "generic_pointer.h"

void gnss17_cfg_setup ( gnss17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->aon = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->rtc = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t gnss17_init ( gnss17_t *ctx, gnss17_cfg_t *cfg ) 
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
    digital_out_init( &ctx->aon, cfg->aon );
    digital_out_init( &ctx->en, cfg->en );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->rtc, cfg->rtc );
    digital_out_high( &ctx->aon );
    digital_out_high( &ctx->en );
    digital_out_high( &ctx->rts );
    digital_out_high( &ctx->rtc );

    return UART_SUCCESS;
}

err_t gnss17_generic_write ( gnss17_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t gnss17_generic_read ( gnss17_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void gnss17_set_en_pin ( gnss17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->en, state );
}

void gnss17_set_aon_pin ( gnss17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->aon, state );
}

void gnss17_set_rts_pin ( gnss17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rts, state );
}

void gnss17_set_rtc_pin ( gnss17_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rtc, state );
}

void gnss17_reset_device ( gnss17_t *ctx )
{
    digital_out_low ( &ctx->aon );
    digital_out_low ( &ctx->en );
    Delay_100ms ( );
    digital_out_high ( &ctx->en );
    digital_out_high ( &ctx->aon );
    Delay_1sec ( );
}

err_t gnss17_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data )
{
    if ( gga_element > GNSS17_GGA_ELEMENT_SIZE )
    {
        return GNSS17_ERROR;
    }
    uint8_t * __generic_ptr start_ptr = strstr( rsp_buf, GNSS17_RSP_GGA );
    if ( start_ptr )
    {
        if ( strstr( start_ptr, ( char * ) GNSS17_RSP_END ) )
        {
            for ( uint8_t element_cnt = 0; element_cnt < gga_element; element_cnt++ )
            {
                start_ptr = strstr( start_ptr, GNSS17_RSP_DELIMITER );
                if ( start_ptr )
                {
                    start_ptr++;
                }
                else
                {
                    return GNSS17_ERROR;
                }
            }
            uint8_t * __generic_ptr end_ptr = strstr( start_ptr, GNSS17_RSP_DELIMITER );
            if ( end_ptr )
            {
                strncpy( element_data, start_ptr, end_ptr - start_ptr );
                return GNSS17_OK;
            }
        }
    }
    return GNSS17_ERROR;
}

// ------------------------------------------------------------------------- END
