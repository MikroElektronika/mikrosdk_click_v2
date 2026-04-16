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
 * @file ethwiz3.c
 * @brief ETH WIZ 3 Click Driver.
 */

#include "ethwiz3.h"

/**
 * @brief ETH WIZ 3 SPI write function.
 * @details This function sends a desired number of data bytes via SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] data_in : Pointer to the input data buffer.
 * @param[in] len : Number of data bytes to send.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ethwiz3_spi_write ( ethwiz3_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief ETH WIZ 3 SPI read function.
 * @details This function reads a desired number of data bytes via SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @param[in] data_out : Pointer to the output data buffer.
 * @param[in] len : Number of data bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ethwiz3_spi_read ( ethwiz3_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief ETH WIZ 3 wait ACK function.
 * @details This function waits for SPI ACK frame.
 * @param[in] ctx : Click context object.
 * See #ethwiz3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error,
 *         @li @c -2 - Timeout.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ethwiz3_wait_ack ( ethwiz3_t *ctx );

void ethwiz3_cfg_setup ( ethwiz3_cfg_t *cfg ) 
{
    cfg->tx_pin = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cts  = HAL_PIN_NC;
    cfg->atm  = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->tcp  = HAL_PIN_NC;
    cfg->rts  = HAL_PIN_NC;

    cfg->spi_speed = 100000;
    cfg->spi_mode  = SPI_MASTER_MODE_0;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->drv_sel = ETHWIZ3_DRV_SEL_UART;
}

void ethwiz3_drv_interface_sel ( ethwiz3_cfg_t *cfg, ethwiz3_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ethwiz3_init ( ethwiz3_t *ctx, ethwiz3_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->atm, cfg->atm );
    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->tcp, cfg->tcp );
    digital_in_init( &ctx->rts, cfg->rts );

    if ( ETHWIZ3_DRV_SEL_UART == ctx->drv_sel ) 
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

        // Dummy read to enable RX interrupt
        uint8_t dummy_read = 0;
        uart_read ( &ctx->uart, &dummy_read, 1 );
    } 
    else 
    {
        digital_out_high ( &ctx->cts );
        
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, ETHWIZ3_SPI_DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
        {
            return SPI_MASTER_ERROR;
        }
    }

    return ETHWIZ3_OK;
}

err_t ethwiz3_cmd_set ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_in )
{
    err_t error_flag = ETHWIZ3_OK;
    uint8_t cr_lf[ 3 ] = { '\r', '\n', 0 };
    if ( ( NULL == cmd ) || ( 2 != strlen ( cmd ) ) )
    {
        return ETHWIZ3_ERROR;
    }

    if ( ETHWIZ3_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_write( &ctx->uart, cmd, strlen ( cmd ) );
        if ( NULL != data_in )
        {
            uart_write( &ctx->uart, data_in, strlen ( data_in ) );
        }
        uart_write( &ctx->uart, cr_lf, strlen ( cr_lf ) );
    }
    else
    {
        uint8_t header[ 4 ] = { 0 };
        uint16_t data_len = 2;
        if ( NULL != data_in )
        {
            data_len += strlen ( data_in );
        }
        header[ 0 ] = cmd[ 0 ];
        header[ 1 ] = cmd[ 1 ];
        header[ 2 ] = ( uint8_t ) ( data_len & 0xFF );
        header[ 3 ] = ( uint8_t ) ( ( data_len >> 8 ) & 0xFF );
        digital_out_low ( &ctx->cts );
        error_flag = ethwiz3_spi_write( ctx, header, 4 );
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_wait_ack ( ctx );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            if ( NULL != data_in )
            {
                error_flag = ethwiz3_spi_write( ctx, data_in, strlen ( data_in ) );
            }
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_write( ctx, cr_lf, strlen ( cr_lf ) );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_wait_ack ( ctx );
        }
        digital_out_high ( &ctx->cts );
    }
    Delay_10ms( );
    return error_flag;
}

err_t ethwiz3_cmd_get ( ethwiz3_t *ctx, uint8_t *cmd, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len )
{
    err_t error_flag = ETHWIZ3_OK;
    uint8_t cr_lf[ 3 ] = { '\r', '\n', 0 };
    uint16_t timeout_ms = 0;
    if ( ( NULL == cmd ) || ( NULL == data_out ) || ( NULL == read_len ) || ( 2 != strlen ( cmd ) ) )
    {
        return ETHWIZ3_ERROR;
    }

    if ( ETHWIZ3_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_write( &ctx->uart, cmd, strlen ( cmd ) );
        uart_write( &ctx->uart, cr_lf, strlen ( cr_lf ) );
        
        uint8_t cmd_buf[ 2 ] = { 0 };

        while ( ETHWIZ3_OK == error_flag )
        {
            if ( 1 == uart_read( &ctx->uart, &cmd_buf[ 0 ], 1 ) )
            {
                if ( cmd_buf[ 0 ] == cmd[ 0 ] )
                {
                    Delay_1ms ( );
                    if ( 1 == uart_read( &ctx->uart, &cmd_buf[ 1 ], 1 ) )
                    {
                        if ( cmd_buf[ 1 ] == cmd[ 1 ] )
                        {
                            break;
                        }
                    }
                }
            }
            else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
            {
                error_flag = ETHWIZ3_ERROR_TIMEOUT;
            }
            Delay_1ms ( );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            Delay_10ms ( );
            error_flag = uart_read( &ctx->uart, data_out, data_buf_len );
            if ( error_flag > 0 )
            {
                *read_len = error_flag;
                error_flag = ETHWIZ3_OK;
            }
            else
            {
                error_flag = ETHWIZ3_ERROR;
            }
        }
    }
    else
    {
        uint8_t header[ 4 ] = { 0 };
        uint8_t rsp_buf[ 4 ] = { 0 };
        uint16_t data_len = 0;
        header[ 0 ] = cmd[ 0 ];
        header[ 1 ] = cmd[ 1 ];
        header[ 2 ] = cr_lf[ 0 ];
        header[ 3 ] = cr_lf[ 1 ];
        digital_out_low ( &ctx->cts );
        error_flag = ethwiz3_spi_write( ctx, header, 4 );
        while ( ETHWIZ3_OK == error_flag )
        {
            if ( !ethwiz3_get_rts_pin ( ctx ) )
            {
                break;
            }
            else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
            {
                error_flag = ETHWIZ3_ERROR_TIMEOUT;
            }
            Delay_1ms ( );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_read( ctx, rsp_buf, 4 );
            if ( ( ETHWIZ3_SPI_READ_LEN != rsp_buf[ 0 ] ) || ( ETHWIZ3_SPI_DUMMY != rsp_buf[ 3 ] ) )
            {
                error_flag = ETHWIZ3_ERROR;
            }
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            data_len = ( ( uint16_t ) rsp_buf[ 2 ] << 8 ) | rsp_buf[ 1 ];
            if ( data_buf_len < data_len )
            {
                data_len = data_buf_len;
            }
            error_flag = ethwiz3_spi_read( ctx, data_out, data_len );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            *read_len = data_len;
        }
        digital_out_high ( &ctx->cts );
    }
    Delay_10ms( );
    return error_flag;
}

err_t ethwiz3_data_write ( ethwiz3_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = ETHWIZ3_OK;
    if ( NULL == data_in )
    {
        return ETHWIZ3_ERROR;
    }

    if ( ETHWIZ3_DRV_SEL_UART == ctx->drv_sel ) 
    {
        uart_write( &ctx->uart, data_in, len );
    }
    else
    {
        uint8_t header[ 4 ] = { 0 };
        header[ 0 ] = ETHWIZ3_SPI_WRITE;
        header[ 1 ] = ( uint8_t ) ( len & 0xFF );
        header[ 2 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
        header[ 3 ] = ETHWIZ3_SPI_DUMMY;
        digital_out_low ( &ctx->cts );
        error_flag = ethwiz3_spi_write( ctx, header, 4 );
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_wait_ack ( ctx );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_write( ctx, data_in, len );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_wait_ack ( ctx );
        }
        digital_out_high ( &ctx->cts );
    }
    Delay_10ms( );
    return error_flag;
}

err_t ethwiz3_data_read ( ethwiz3_t *ctx, uint8_t *data_out, uint16_t *read_len, uint16_t data_buf_len )
{
    err_t error_flag = ETHWIZ3_OK;
    uint16_t timeout_ms = 0;
    if ( ( NULL == data_out ) || ( NULL == read_len ) )
    {
        return ETHWIZ3_ERROR;
    }

    if ( ETHWIZ3_DRV_SEL_UART == ctx->drv_sel ) 
    {
        while ( ETHWIZ3_OK == error_flag )
        {
            if ( 1 == uart_read( &ctx->uart, &data_out[ 0 ], 1 ) )
            {
                break;
            }
            else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
            {
                error_flag = ETHWIZ3_ERROR_TIMEOUT;
            }
            Delay_1ms ( );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            Delay_100ms ( );
            Delay_100ms ( );
            *read_len = 1;
            error_flag = uart_read( &ctx->uart, &data_out[ 1 ], data_buf_len - 1 );
            if ( error_flag > 0 )
            {
                *read_len = error_flag + 1;
                error_flag = ETHWIZ3_OK;
            }
        }
    }
    else
    {
        uint8_t header[ 4 ] = { 0 };
        uint8_t rsp_buf[ 4 ] = { 0 };
        uint16_t data_len = 0;
        header[ 0 ] = ETHWIZ3_SPI_READ;
        header[ 1 ] = ETHWIZ3_SPI_DUMMY;
        header[ 2 ] = ETHWIZ3_SPI_DUMMY;
        header[ 3 ] = ETHWIZ3_SPI_DUMMY;
        while ( ETHWIZ3_OK == error_flag )
        {
            if ( !ethwiz3_get_rts_pin ( ctx ) )
            {
                break;
            }
            else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
            {
                return ETHWIZ3_ERROR_TIMEOUT;
            }
            Delay_1ms ( );
        }
        digital_out_low ( &ctx->cts );
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_write( ctx, header, 4 );
            timeout_ms = 0;
        }
        while ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_read( ctx, rsp_buf, 1 );
            if ( ETHWIZ3_SPI_READ_LEN == rsp_buf[ 0 ] )
            {
                break;
            }
            else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
            {
                error_flag = ETHWIZ3_ERROR_TIMEOUT;
            }
            Delay_1ms ( );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            error_flag = ethwiz3_spi_read( ctx, &rsp_buf[ 1 ], 3 );
            if ( ETHWIZ3_SPI_DUMMY != rsp_buf[ 3 ] )
            {
                error_flag = ETHWIZ3_ERROR;
            }
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            data_len = ( ( uint16_t ) rsp_buf[ 2 ] << 8 ) | rsp_buf[ 1 ];
            if ( data_buf_len < data_len )
            {
                data_len = data_buf_len;
            }
            error_flag = ethwiz3_spi_read( ctx, data_out, data_len );
        }
        if ( ETHWIZ3_OK == error_flag )
        {
            *read_len = data_len;
        }
        digital_out_high ( &ctx->cts );
    }
    Delay_10ms( );
    return error_flag;
}

void ethwiz3_set_rst_pin ( ethwiz3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void ethwiz3_set_cts_pin ( ethwiz3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

void ethwiz3_set_at_mode ( ethwiz3_t *ctx )
{
    digital_out_low ( &ctx->atm );
}

void ethwiz3_set_data_mode ( ethwiz3_t *ctx )
{
    digital_out_high ( &ctx->atm );
}

uint8_t ethwiz3_get_rts_pin ( ethwiz3_t *ctx )
{
    return !!digital_in_read ( &ctx->rts );
}

uint8_t ethwiz3_get_tcp_pin ( ethwiz3_t *ctx )
{
    return !!digital_in_read ( &ctx->tcp );
}

void ethwiz3_reset_device ( ethwiz3_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
}

static err_t ethwiz3_spi_write ( ethwiz3_t *ctx, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = ETHWIZ3_OK;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        digital_out_low ( &ctx->cts );
        error_flag = spi_master_write( &ctx->spi, &data_in[ cnt ], 1 );
        Delay_10us ( );
        digital_out_high ( &ctx->cts );
    }
    return error_flag;
}

static err_t ethwiz3_spi_read ( ethwiz3_t *ctx, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = ETHWIZ3_OK;
    for ( uint16_t cnt = 0; cnt < len; cnt++ )
    {
        digital_out_low ( &ctx->cts );
        error_flag = spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
        Delay_10us ( );
        digital_out_high ( &ctx->cts );
    }
    return error_flag;
}

static err_t ethwiz3_wait_ack ( ethwiz3_t *ctx )
{
    err_t error_flag = ETHWIZ3_OK;
    uint8_t ack_buf[ 4 ] = { 0 };
    uint16_t timeout_ms = 0;

    while ( ETHWIZ3_OK == error_flag )
    {
        error_flag = ethwiz3_spi_read( ctx, &ack_buf[ 0 ], 1 );
        if ( ETHWIZ3_SPI_ACK == ack_buf[ 0 ] )
        {
            break;
        }
        else if ( ETHWIZ3_SPI_NACK == ack_buf[ 0 ] )
        {
            error_flag = ETHWIZ3_ERROR;
        }
        else if ( timeout_ms++ > ETHWIZ3_TIMEOUT_MS )
        {
            error_flag = ETHWIZ3_ERROR_TIMEOUT;
        }
        Delay_1ms ( );
    }
    if ( ETHWIZ3_OK == error_flag )
    {
        error_flag = ethwiz3_spi_read( ctx, &ack_buf[ 1 ], 3 );
        if ( ( ETHWIZ3_SPI_DUMMY != ack_buf[ 1 ] ) || 
             ( ETHWIZ3_SPI_DUMMY != ack_buf[ 2 ] ) || 
             ( ETHWIZ3_SPI_DUMMY != ack_buf[ 3 ] ) )
        {
            error_flag = ETHWIZ3_ERROR;
        }
    }
    return error_flag;
}

// ------------------------------------------------------------------------ END
