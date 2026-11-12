/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file wifi4.c
 * @brief WiFi 4 Click Driver.
 */

#include "wifi4.h"

void wifi4_cfg_setup ( wifi4_cfg_t *cfg )
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t wifi4_init ( wifi4_t *ctx, wifi4_cfg_t *cfg )
{
    uart_config_t uart_cfg;
    err_t error_flag = UART_SUCCESS;
    uint8_t dummy_read = 0;

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

    if ( ( UART_ERROR == uart_open( &ctx->uart, &uart_cfg ) ) ||
         ( UART_ERROR == uart_set_baud( &ctx->uart, cfg->baud_rate ) ) ||
         ( UART_ERROR == uart_set_parity( &ctx->uart, cfg->parity_bit ) ) ||
         ( UART_ERROR == uart_set_stop_bits( &ctx->uart, cfg->stop_bit ) ) ||
         ( UART_ERROR == uart_set_data_bits( &ctx->uart, cfg->data_bit ) ) )
    {
        error_flag = UART_ERROR;
    }
    else
    {
        uart_set_blocking( &ctx->uart, cfg->uart_blocking );

        // Output pins
        if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->rst, cfg->rst ) )
        {
            error_flag = WIFI4_ERROR;
        }
        else
        {
            wifi4_set_rst_pin( ctx, WIFI4_PIN_STATE_LOW );
            if ( DIGITAL_OUT_UNSUPPORTED_PIN == digital_out_init( &ctx->cts, cfg->cts ) )
            {
                error_flag = WIFI4_ERROR;
            }
            else
            {
                wifi4_set_cts_pin( ctx, WIFI4_PIN_STATE_LOW );

                // Input pins
                if ( DIGITAL_IN_UNSUPPORTED_PIN == digital_in_init( &ctx->rts, cfg->rts ) )
                {
                    error_flag = WIFI4_ERROR;
                }
                else if ( false == cfg->uart_blocking )
                {
                    // Enable RX before releasing the module from reset.
                    uart_read( &ctx->uart, &dummy_read, 1 );
                }
            }
        }
    }

    return error_flag;
}

err_t wifi4_generic_write ( wifi4_t *ctx, uint8_t *data_in, uint16_t len )
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t wifi4_generic_read ( wifi4_t *ctx, uint8_t *data_out, uint16_t len )
{
    return uart_read( &ctx->uart, data_out, len );
}

void wifi4_set_rst_pin ( wifi4_t *ctx, uint8_t pin_state )
{
    if ( WIFI4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void wifi4_set_cts_pin ( wifi4_t *ctx, uint8_t pin_state )
{
    if ( WIFI4_PIN_STATE_HIGH == pin_state )
    {
        digital_out_high( &ctx->cts );
    }
    else
    {
        digital_out_low( &ctx->cts );
    }
}

uint8_t wifi4_get_rts_pin ( wifi4_t *ctx )
{
    uint8_t state = WIFI4_PIN_STATE_LOW;
    if ( digital_in_read( &ctx->rts ) )
    {
        state = WIFI4_PIN_STATE_HIGH;
    }
    return state;
}

void wifi4_hw_reset ( wifi4_t *ctx )
{
    wifi4_set_rst_pin( ctx, WIFI4_PIN_STATE_LOW );
    wifi4_set_cts_pin( ctx, WIFI4_PIN_STATE_LOW );
    Delay_100ms( );
    uart_clear( &ctx->uart );
    memset( ctx->cmd_buffer, 0, sizeof( ctx->cmd_buffer ) );
    wifi4_set_rst_pin( ctx, WIFI4_PIN_STATE_HIGH );
}

err_t wifi4_cmd_run ( wifi4_t *ctx, char *cmd )
{
    err_t error_flag = WIFI4_ERROR;

    if ( NULL != cmd )
    {
        size_t cmd_len = strlen( cmd );
        if ( ( 0 != cmd_len ) && ( cmd_len < WIFI4_CMD_MAX_SIZE ) && ( NULL == strpbrk( cmd, "\r\n" ) ) )
        {
            uint16_t frame_len = ( uint16_t ) cmd_len + 1u;
            if ( cmd != ctx->cmd_buffer )
            {
                memcpy( ctx->cmd_buffer, cmd, cmd_len );
            }
            ctx->cmd_buffer[ cmd_len ] = '\r';
            ctx->cmd_buffer[ frame_len ] = 0;
            if ( frame_len == wifi4_generic_write( ctx, ( uint8_t * ) ctx->cmd_buffer, frame_len ) )
            {
                error_flag = WIFI4_OK;
            }
        }
    }

    return error_flag;
}

err_t wifi4_cmd_set ( wifi4_t *ctx, char *cmd, char *value )
{
    err_t error_flag = WIFI4_ERROR;

    if ( ( NULL != cmd ) && ( NULL != value ) )
    {
        size_t cmd_len = strlen( cmd );
        size_t value_len = strlen( value );

        // Reserve one byte each for '=' and the command CR.
        if ( ( 0 != cmd_len ) && ( cmd_len <= WIFI4_CMD_MAX_SIZE - 2u ) &&
             ( value_len <= WIFI4_CMD_MAX_SIZE - 2u - cmd_len ) )
        {
            strcpy( ctx->cmd_buffer, cmd );
            strcat( ctx->cmd_buffer, "=" );
            strcat( ctx->cmd_buffer, value );
            error_flag = wifi4_cmd_run( ctx, ctx->cmd_buffer );
        }
    }

    return error_flag;
}

// ------------------------------------------------------------------------- END
