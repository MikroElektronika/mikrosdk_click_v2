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
 * @file nbiot7.c
 * @brief NB IoT 7 Click Driver.
 */

#include "nbiot7.h"
#include "conversions.h"

void nbiot7_cfg_setup ( nbiot7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->wkp = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->ring = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t nbiot7_init ( nbiot7_t *ctx, nbiot7_cfg_t *cfg ) 
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
    digital_out_init( &ctx->wkp, cfg->wkp );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );
    Delay_100ms( );
    digital_out_low( &ctx->wkp );
    digital_out_low( &ctx->rts );
    digital_out_low( &ctx->rst );
    Delay_100ms( );

    // Input pins
    digital_in_init( &ctx->ring, cfg->ring );
    digital_in_init( &ctx->cts, cfg->cts );

    // Dummy read to enable RX interrupt
    uint8_t dummy_read = 0;
    uart_read ( &ctx->uart, &dummy_read, 1 );
    Delay_1sec( );

    return UART_SUCCESS;
}

err_t nbiot7_generic_write ( nbiot7_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t nbiot7_generic_read ( nbiot7_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void nbiot7_set_wkp_pin ( nbiot7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wkp, state );
}

void nbiot7_set_rst_pin ( nbiot7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void nbiot7_set_rts_pin ( nbiot7_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rts, state );
}

uint8_t nbiot7_get_ring_pin ( nbiot7_t *ctx )
{
    return digital_in_read ( &ctx->ring );
}

uint8_t nbiot7_get_cts_pin ( nbiot7_t *ctx )
{
    return digital_in_read ( &ctx->cts );
}

void nbiot7_set_power_state ( nbiot7_t *ctx, uint8_t state )
{
    uint8_t delay_cnt = 0;
    if ( NBIOT7_POWER_STATE_ON == state )
    {
        digital_out_high ( &ctx->rst );
        Delay_1sec ( );
        Delay_1sec ( );
        digital_out_high ( &ctx->wkp );
        Delay_1sec ( );
        digital_out_low ( &ctx->wkp );
        Delay_1sec ( );
    }
    else if ( NBIOT7_POWER_STATE_OFF == state )
    {
        digital_out_low ( &ctx->rst );
        Delay_1sec ( );
        Delay_1sec ( );
    }
}

void nbiot7_cmd_run ( nbiot7_t *ctx, uint8_t *cmd )
{
    uint8_t carriage_return[ 2 ] = { '\r', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, carriage_return );

    nbiot7_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void nbiot7_cmd_set ( nbiot7_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );

    nbiot7_cmd_run( ctx, ctx->cmd_buffer );
}

void nbiot7_cmd_get ( nbiot7_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, check_char );

    nbiot7_cmd_run( ctx, ctx->cmd_buffer );
}

void nbiot7_cmd_help ( nbiot7_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    nbiot7_cmd_set( ctx, cmd, check_char );
}

void nbiot7_set_sim_apn ( nbiot7_t *ctx, uint8_t *sim_apn )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };
    uint8_t quotation_char[ 2 ] = { '\"', 0 };
    
    strcpy( ctx->cmd_buffer, NBIOT7_CMD_DEFINE_PDP_CONTEXT );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, "1,\"IP\",\"" );
    strcat( ctx->cmd_buffer, sim_apn );
    strcat( ctx->cmd_buffer, quotation_char );
    
    nbiot7_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
