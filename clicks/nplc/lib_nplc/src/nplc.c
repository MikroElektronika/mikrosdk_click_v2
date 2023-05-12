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
 * @file nplc.c
 * @brief N-PLC Click Driver.
 */

#include "nplc.h"

void nplc_cfg_setup ( nplc_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->cts = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->md1 = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate      = 115200;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t nplc_init ( nplc_t *ctx, nplc_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->md1, cfg->md1 );

    // Input pins
    digital_in_init( &ctx->rts, cfg->rts );
    
    digital_out_low ( &ctx->cts );
    digital_out_low ( &ctx->md1 );
    digital_out_high ( &ctx->rst );

    return UART_SUCCESS;
}

err_t nplc_generic_write ( nplc_t *ctx, char *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t nplc_generic_read ( nplc_t *ctx, char *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void nplc_set_rst_pin ( nplc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void nplc_set_md1_pin ( nplc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->md1, state );
}

void nplc_set_cts_pin ( nplc_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

uint8_t nplc_get_rts_pin ( nplc_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

void nplc_hw_reset ( nplc_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

void nplc_sw_reset ( nplc_t *ctx )
{
    nplc_send_cmd ( ctx, NPLC_CMD_Z );
}

void nplc_factory_reset ( nplc_t *ctx )
{
    nplc_send_cmd ( ctx, NPLC_CMD_F );
}

void nplc_firmware_version ( nplc_t *ctx )
{
    nplc_send_cmd ( ctx, NPLC_CMD_FWI );
}

void nplc_set_mode ( nplc_t *ctx, uint8_t mode )
{
    if ( NPLC_MODE_COMMAND == mode )
    {
        nplc_send_cmd ( ctx, NPLC_CMD_COMMAND_MODE );
    }
    else
    {
        nplc_send_cmd ( ctx, NPLC_CMD_DATA_MODE );
    }
}

void nplc_send_cmd ( nplc_t *ctx, char *cmd )
{
    char cr_lf[ 2 ] = { 13, 10 };
    while ( *cmd )
    {
        uart_write( &ctx->uart, cmd, 1 );
        cmd++;
    }
    uart_write( &ctx->uart, cr_lf, 2 );
}

void nplc_write_s_register ( nplc_t *ctx, char *s_reg, char *param_buf )
{
    char final_cmd[ 16 ] = { 0 };
    char equal_sign[ 2 ] = { '=', 0 };
    strcpy( final_cmd, s_reg );
    strcat( final_cmd, equal_sign );
    strcat( final_cmd, param_buf );
    nplc_send_cmd( ctx, final_cmd );
}

void nplc_read_s_register ( nplc_t *ctx, char *s_reg )
{
    char final_cmd[ 16 ] = { 0 };
    char check_mark[ 2 ] = { '?', 0 };
    strcpy( final_cmd, s_reg );
    strcat( final_cmd, check_mark );
    nplc_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
