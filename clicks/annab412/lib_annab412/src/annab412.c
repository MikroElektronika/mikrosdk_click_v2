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
 * @file annab412.c
 * @brief ANNA-B412 Click Driver.
 */

#include "annab412.h"

void annab412_cfg_setup ( annab412_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->dtr = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->dsr = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t annab412_init ( annab412_t *ctx, annab412_cfg_t *cfg ) 
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
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->dsr, cfg->dsr );

    // Input pins
    digital_in_init( &ctx->dtr, cfg->dtr );
    digital_in_init( &ctx->rts, cfg->rts );
    
    return UART_SUCCESS;
}

err_t annab412_default_cfg ( annab412_t *ctx ) 
{
    err_t error_flag = ANNAB412_OK;
    
    annab412_hw_reset( ctx );
    Delay_100ms( );
    
    annab412_set_dsr_pin( ctx, ANNAB412_PIN_STATE_HIGH );
    Delay_100ms( );
    
    return annab412_send_command( ctx, ANNAB412_CMD_AT );
}

err_t annab412_generic_write ( annab412_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t annab412_generic_read ( annab412_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

void annab412_set_rst_pin ( annab412_t *ctx, uint8_t state ) 
{
    digital_out_write( &ctx->rst, state );
}

void annab412_set_dsr_pin ( annab412_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->dsr, state );
}

void annab412_set_cts_pin ( annab412_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->cts, state );
}

uint8_t annab412_get_dtr_pin ( annab412_t *ctx )
{
    return digital_in_read( &ctx->dtr );
}

uint8_t annab412_get_rts_pin ( annab412_t *ctx )
{
    return digital_in_read( &ctx->rts );
}

void annab412_hw_reset ( annab412_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

err_t annab412_send_command ( annab412_t *ctx, char *command )
{
    uint8_t data_buf[ 2 ] = { ANNAB412_DELIMITER_TERMINATION, ANNAB412_DELIMITER_END_CMD };
    annab412_set_cts_pin( ctx, ANNAB412_PIN_STATE_HIGH );
    err_t err_flag = annab412_generic_write( ctx, command, strlen( command ) );
    err_flag |= annab412_generic_write( ctx, data_buf, strlen( data_buf ) );
    Delay_1ms( );
    annab412_set_cts_pin( ctx, ANNAB412_PIN_STATE_LOW );
    return err_flag;
}

err_t annab412_set_cmd_echo_on ( annab412_t *ctx )
{
    return annab412_send_command( ctx, ANNAB412_CMD_ECHO_ON );
}

err_t annab412_set_cmd_echo_off ( annab412_t *ctx )
{
    return annab412_send_command( ctx, ANNAB412_CMD_ECHO_OFF );
}

err_t annab412_set_cmd_device_name ( annab412_t *ctx, char *device_name )
{  
    err_t err_flag = ANNAB412_OK;
    if ( strlen( device_name ) > ANNAB412_DEV_NAME_MAX || 
        strlen( device_name ) < ANNAB412_DEV_NAME_MIN )
    {
        err_flag = ANNAB412_ERROR;
    }
    else
    {
        uint8_t cmd_buf[ 41 ] = { 0 };
        uint8_t data_buf[ 1 ] = { ANNAB412_DELIMITER_QUOTATION };
        strncpy( cmd_buf, ANNAB412_CMD_DEV_NAME, strlen( ANNAB412_CMD_DEV_NAME ) );
        data_buf[ 0 ] = ANNAB412_DELIMITER_EQUAL;
        strncat( cmd_buf, data_buf, 1 );
        data_buf[ 0 ] = ANNAB412_DELIMITER_QUOTATION;
        strncat( cmd_buf, data_buf, 1 );
        strncat( cmd_buf, device_name, strlen( device_name ) );
        strncat( cmd_buf, data_buf, 1 );
        err_flag |= annab412_send_command( ctx, cmd_buf );
    }
    return err_flag;
}

err_t annab412_set_cmd_conn_mode ( annab412_t *ctx, uint8_t mode )
{
    err_t err_flag = ANNAB412_OK;
    if ( ( ANNAB412_CONNECTABLE_MODE_OFF != mode ) || ( ANNAB412_CONNECTABLE_MODE_ON != mode ) )
    {
        err_flag = ANNAB412_ERROR;
    }
    else
    {
        uint8_t cmd_buf[ 11 ] = { 0 };
        uint8_t data_buf[ 1 ] = { ANNAB412_DELIMITER_QUOTATION };
        strncpy( cmd_buf, ANNAB412_CMD_CONN_MODE, strlen( ANNAB412_CMD_CONN_MODE ) );
        data_buf[ 0 ] = ANNAB412_DELIMITER_EQUAL;
        strncat( cmd_buf, data_buf, 1 );
        data_buf[ 0 ] = mode + ANNAB412_ASCII_CHAR_0;
        strncat( cmd_buf, data_buf, 1 );
        err_flag |= annab412_send_command( ctx, cmd_buf );
    }
    return err_flag;
}

err_t annab412_set_cmd_discover_mode ( annab412_t *ctx, uint8_t mode )
{
    err_t err_flag = ANNAB412_OK;
    if ( ( mode < ANNAB412_DISCOVERABLE_MODE_OFF ) || ( mode > ANNAB412_DISCOVERABLE_MODE_ON ) )
    {
        err_flag = ANNAB412_ERROR;
    }
    else
    {
        uint8_t cmd_buf[ 11 ] = { 0 };
        uint8_t data_buf[ 1 ] = { ANNAB412_DELIMITER_QUOTATION };
        strncpy( cmd_buf, ANNAB412_CMD_DISCOVER_MODE, strlen( ANNAB412_CMD_DISCOVER_MODE ) );
        data_buf[ 0 ] = ANNAB412_DELIMITER_EQUAL;
        strncat( cmd_buf, data_buf, 1 );
        data_buf[ 0 ] = mode + ANNAB412_ASCII_CHAR_0;
        strncat( cmd_buf, data_buf, 1 );
        err_flag |= annab412_send_command( ctx, cmd_buf );
    }
    return err_flag;
}

err_t annab412_set_cmd_enter_mode ( annab412_t *ctx, uint8_t mode )
{
    err_t err_flag = ANNAB412_OK;
    if ( mode > ANNAB412_ENTER_MODE_PPP )
    {
        err_flag = ANNAB412_ERROR;
    }
    else
    {
        uint8_t cmd_buf[ 5 ] = { 0 };
        uint8_t data_buf[ 1 ] = { 0 };
        strncpy( cmd_buf, ANNAB412_CMD_ENTER_MODE, strlen( ANNAB412_CMD_ENTER_MODE ) );
        data_buf[ 0 ] = mode + ANNAB412_ASCII_CHAR_0;
        strncat( cmd_buf, data_buf, 1 );
        err_flag |= annab412_send_command( ctx, cmd_buf );
    }
    return err_flag;
}

// ------------------------------------------------------------------------- END
