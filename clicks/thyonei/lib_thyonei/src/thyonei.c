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
 * @file thyonei.c
 * @brief Thyone-I Click Driver.
 */

#include "thyonei.h"

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Initialization 0x00
 * @param[in] buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t crc_from_buffer ( uint8_t *buf, uint16_t len );

void thyonei_cfg_setup ( thyonei_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->bt  = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;
    cfg->wup = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;
}

err_t thyonei_init ( thyonei_t *ctx, thyonei_cfg_t *cfg ) 
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
    digital_out_init( &ctx->bt, cfg->bt );
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->rts, cfg->rts );
    digital_out_init( &ctx->wup, cfg->wup );

    // Input pins
    digital_in_init( &ctx->cts, cfg->cts );

    return UART_SUCCESS;
}

void thyonei_default_cfg ( thyonei_t *ctx ) 
{
    thyonei_set_wup( ctx, THYONE_PIN_MODE_HIGH );
    thyonei_set_bt( ctx, THYONE_PIN_MODE_HIGH );
    thyonei_set_rst( ctx, THYONE_PIN_MODE_HIGH );

    thyonei_hw_reset( ctx );
}

err_t thyonei_generic_write ( thyonei_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    return uart_write( &ctx->uart, data_in, len );
}

err_t thyonei_generic_read ( thyonei_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    return uart_read( &ctx->uart, data_out, len );
}

uint8_t thyonei_get_cts_state ( thyonei_t *ctx )
{
    return digital_in_read( &ctx->cts );
}

void thyonei_set_bt ( thyonei_t *ctx, uint8_t pin_state )
{
    if ( THYONE_PIN_MODE_HIGH == pin_state )
    {
        digital_out_high( &ctx->bt );
    }
    else
    {
        digital_out_low( &ctx->bt );
    }
}

void thyonei_set_rst ( thyonei_t *ctx, uint8_t pin_state )
{
    if ( THYONE_PIN_MODE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void thyonei_set_rts ( thyonei_t *ctx, uint8_t pin_state )
{
    if ( THYONE_PIN_MODE_HIGH == pin_state )
    {
        digital_out_high( &ctx->rts );
    }
    else
    {
        digital_out_low( &ctx->rts );
    }
}

void thyonei_set_wup ( thyonei_t *ctx, uint8_t pin_state )
{
    if ( THYONE_PIN_MODE_HIGH == pin_state )
    {
        digital_out_high( &ctx->wup );
    }
    else
    {
        digital_out_low( &ctx->wup );
    }
}

void thyonei_hw_reset ( thyonei_t *ctx )
{
    thyonei_set_rst( ctx, THYONE_PIN_MODE_LOW );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    thyonei_set_rst( ctx, THYONE_PIN_MODE_HIGH );
    Delay_100ms( );
}

err_t thyonei_send_command ( thyonei_t *ctx, uint8_t command,
                             uint16_t payload_length, uint8_t *payload )
{
    err_t error_flag = THYONEI_OK;
    uint8_t crc_data = 0;
    uint8_t data_buf[ THYONEI_TX_DRV_BUFFER_SIZE ] = { 0 };
   
    data_buf[ 0 ] = THYONEI_START_SIGNAL;
    data_buf[ 1 ] = command;
    data_buf[ 2 ] = ( uint8_t ) payload_length;
    data_buf[ 3 ] = ( uint8_t ) ( payload_length >> 8 );
    
    if ( 0 != payload_length )
    {
        for ( uint8_t n_cnt = 0; n_cnt < payload_length; n_cnt++ )
        {
            data_buf[ n_cnt + 4 ] = payload[ n_cnt ];
        }
    }
    
    crc_data = crc_from_buffer( data_buf, payload_length + 4 );
    
    data_buf[ payload_length + 4 ] = crc_data; 
    
    error_flag = thyonei_generic_write( ctx, data_buf, ( payload_length + 5 ) );
    
    return error_flag;
}

err_t thyonei_set_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t parameters_length, uint8_t *parameters )
{
    err_t error_flag = THYONEI_OK;
    uint8_t data_buf[ THYONEI_TX_DRV_BUFFER_SIZE ] = { 0 };

    data_buf[ 0 ] = settings_index;
    for ( uint8_t n_cnt = 1; n_cnt <= parameters_length; n_cnt++ )
    {
        data_buf[ n_cnt ] = parameters[ n_cnt - 1 ];
    }
    error_flag |= thyonei_send_command( ctx, THYONEI_CMD_SET_REQ, ( uint16_t ) ( parameters_length + 1 ), data_buf );

    return error_flag;
}

err_t thyonei_get_req ( thyonei_t *ctx, uint8_t settings_index, uint8_t *param_len, uint8_t *parameter )
{
    err_t error_flag = THYONEI_OK;
    uint8_t data_buf[ THYONEI_RX_DRV_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;

    data_buf[ 0 ] = settings_index;
    
    error_flag |= thyonei_send_command( ctx, THYONEI_CMD_GET_REQ, 1, data_buf );
    Delay_100ms( );
    
    rx_size = thyonei_generic_read( ctx, data_buf, THYONEI_RX_DRV_BUFFER_SIZE );
    if ( rx_size > 0 )
    {    
        if ( ( THYONEI_CMD_GET_REQ | THYONEI_RESPONSE_CODE ) == data_buf[ 1 ] )
        {
            if ( 0 == data_buf[ 4 ] )
            {
                *param_len = data_buf[ 2 ] - 1;
                for ( uint8_t n_cnt = 0; n_cnt < data_buf[ 2 ] - 1; n_cnt++ )
                {
                    parameter[ ( data_buf[ 2 ] - 2 ) - n_cnt ] = data_buf[ n_cnt + 5 ];
                }
                error_flag = THYONEI_OK;
            }
            else 
            {
                error_flag = THYONEI_ERROR;
            }
        }
        else 
        {
            error_flag = THYONEI_ERROR;
        }
    }

    return error_flag;
}

err_t thyonei_broadcast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message )
{
    err_t error_flag = THYONEI_OK;

    error_flag = thyonei_send_command( ctx, THYONEI_CMD_BROADCAST_DATA_REQ, ( uint16_t ) message_len, message );

    return error_flag;
}

err_t thyonei_multicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message )
{
    err_t error_flag = THYONEI_OK;

    error_flag = thyonei_send_command( ctx, THYONEI_CMD_MULTICAST_DATA_REQ, ( uint16_t ) message_len, message );

    return error_flag;
}

err_t thyonei_unicast_data_req ( thyonei_t *ctx, uint8_t message_len, uint8_t *message )
{
    err_t error_flag = THYONEI_OK;

    error_flag = thyonei_send_command( ctx, THYONEI_CMD_UNICAST_DATA_REQ, ( uint16_t ) message_len, message );

    return error_flag;
}

static uint8_t crc_from_buffer ( uint8_t *buf, uint16_t len )
{
    uint8_t crc = 0x00;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        crc ^= buf[ cnt ];
    }
    return crc;

}


// ------------------------------------------------------------------------- END
