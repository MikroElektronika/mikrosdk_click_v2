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
 * @file thermo23.c
 * @brief Thermo 23 Click Driver.
 */

#include "thermo23.h"

void thermo23_cfg_setup ( thermo23_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    cfg->baud_rate      = 9600;
    cfg->data_bit       = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit     = UART_PARITY_DEFAULT;
    cfg->stop_bit       = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking  = false;
}

err_t thermo23_init ( thermo23_t *ctx, thermo23_cfg_t *cfg ) 
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

    return UART_SUCCESS;
}

err_t thermo23_default_cfg ( thermo23_t *ctx ) 
{
    err_t error_flag = THERMO23_OK;
    
    error_flag |= thermo23_set_config ( ctx, THERMO23_CONFIG_CR_1HZ | THERMO23_CONFIG_MODE_CONTINUOUS );
    Delay_100ms ( );
    
    return error_flag;
}

err_t thermo23_write_command ( thermo23_t *ctx, uint8_t cmd, uint16_t data_in )
{
    uint8_t data_buf[ 4 ];
    data_buf[ 0 ] = THERMO23_CALIBRATION_BYTE;
    data_buf[ 1 ] = cmd;
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    uart_clear ( &ctx->uart );
    uart_write( &ctx->uart, data_buf, 4 );
    uint16_t timeout_cnt = 0;
    while ( ( uart_read( &ctx->uart, data_buf, 1 ) <= 0 ) || ( THERMO23_CALIBRATION_BYTE != data_buf[ 0 ] ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt > THERMO23_TIMEOUT )
        {
            return THERMO23_ERROR;
        }
    }
    Delay_10ms( );
    if ( ( 3 != uart_read( &ctx->uart, &data_buf[ 1 ], 3 ) ) || 
         ( cmd != data_buf[ 1 ] ) || 
         ( ( uint8_t ) ( data_in & 0xFF ) != data_buf[ 2 ] ) || 
         ( ( uint8_t ) ( ( data_in >> 8 ) & 0xFF ) != data_buf[ 3 ] ) )
    {
        return THERMO23_ERROR;
    }
    return THERMO23_OK;
}

err_t thermo23_read_command ( thermo23_t *ctx, uint8_t cmd, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ];
    data_buf[ 0 ] = THERMO23_CALIBRATION_BYTE;
    data_buf[ 1 ] = cmd;
    uart_clear ( &ctx->uart );
    uart_write( &ctx->uart, data_buf, 2 );
    uint16_t timeout_cnt = 0;
    while ( ( uart_read( &ctx->uart, data_buf, 1 ) <= 0 ) || ( THERMO23_CALIBRATION_BYTE != data_buf[ 0 ] ) )
    {
        Delay_1ms( );
        if ( ++timeout_cnt > THERMO23_TIMEOUT )
        {
            return THERMO23_ERROR;
        }
    }
    Delay_10ms( );
    if ( ( 3 != uart_read( &ctx->uart, &data_buf[ 1 ], 3 ) ) || 
         ( cmd != data_buf[ 1 ] ) )
    {
        return THERMO23_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 2 ];
    return THERMO23_OK;
}

err_t thermo23_set_config ( thermo23_t *ctx, uint16_t config )
{
    ctx->config = config & ( ~THERMO23_CONFIG_RESERVED_BITS );
    return thermo23_write_command ( ctx, THERMO23_CMD_GLOBAL_WRITE_CONFIG, ctx->config );
}

err_t thermo23_read_temperature ( thermo23_t *ctx, float *temperature )
{
    uint16_t reg_data;
    if ( THERMO23_OK == thermo23_read_command( ctx, THERMO23_CMD_GLOBAL_READ_TEMP, &reg_data ) )
    {
        int16_t raw_temp = ( int16_t ) reg_data;
        if ( ctx->config & THERMO23_CONFIG_ETM )
        {
            raw_temp >>= 3;
        }
        else
        {
            raw_temp >>= 4;
        }
        *temperature = raw_temp * THERMO23_TEMP_RESOLUTION;
        return THERMO23_OK;
    }
    return THERMO23_ERROR;
}

// ------------------------------------------------------------------------- END
