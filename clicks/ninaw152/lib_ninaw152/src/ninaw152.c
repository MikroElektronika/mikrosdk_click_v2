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
 * @file ninaw152.c
 * @brief NINA-W152 Click Driver.
 */

#include "ninaw152.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

void ninaw152_cfg_setup ( ninaw152_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->sck = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->rx_pin = HAL_PIN_NC;
    cfg->tx_pin = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sry = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->cts = HAL_PIN_NC;
    cfg->esc = HAL_PIN_NC;
    cfg->rts = HAL_PIN_NC;

    cfg->baud_rate     = 115200;
    cfg->data_bit      = UART_DATA_BITS_DEFAULT;
    cfg->parity_bit    = UART_PARITY_DEFAULT;
    cfg->stop_bit      = UART_STOP_BITS_DEFAULT;
    cfg->uart_blocking = false;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = NINAW152_DRV_SEL_UART;
}

void ninaw152_drv_interface_sel ( ninaw152_cfg_t *cfg, ninaw152_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t ninaw152_init ( ninaw152_t *ctx, ninaw152_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    // Output pins
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->cts, cfg->cts );
    digital_out_init( &ctx->esc, cfg->esc );
    digital_out_low ( &ctx->rst );
    digital_out_low ( &ctx->cts );
    digital_out_low ( &ctx->esc );

    // Input pins
    digital_in_init( &ctx->sry, cfg->sry );
    digital_in_init( &ctx->rts, cfg->rts );

    if ( NINAW152_DRV_SEL_UART == ctx->drv_sel ) 
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
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cts;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
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

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );
    }
    Delay_100ms ( );

    return NINAW152_OK;
}

err_t ninaw152_generic_write ( ninaw152_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = NINAW152_OK;
    if ( NINAW152_DRV_SEL_UART == ctx->drv_sel ) 
    {
        error_flag = uart_write( &ctx->uart, data_in, len );
    }
    else
    {
        uint8_t header[ 4 ] = { 0 };
        header[ 0 ] = NINAW152_SPI_HEADER_0;
        header[ 1 ] = NINAW152_SPI_HEADER_1;
        header[ 2 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
        header[ 3 ] = ( uint8_t ) ( len & 0xFF );

        // check if the module can accept more data
        error_flag |= ninaw152_generic_read ( ctx, NULL, 0 );
        error_flag |= ninaw152_generic_read ( ctx, NULL, 0 );

        if ( NINAW152_OK == error_flag )
        {
            Delay_100ms ( );
            spi_master_select_device( ctx->chip_select );
            error_flag = spi_master_write( &ctx->spi, header, 4 );
            error_flag |= spi_master_write( &ctx->spi, data_in, len );
            memset ( header, DUMMY, 4 );
            if ( len % 4 )
            {
                // Number of transmitted bytes must be divisible by 4.
                error_flag |= spi_master_write( &ctx->spi, header, 4 - len % 4 );
            }
            // The last four sent bytes always become corrupt on the slave side,
            // so the master must always transmit four extra dummy bytes.
            error_flag |= spi_master_write( &ctx->spi, header, 4 );
            spi_master_deselect_device( ctx->chip_select );
            if ( NINAW152_OK == error_flag )
            {
                // return the number of bytes that are actually written, 
                // for compatibility with the UART version
                error_flag = len;
            }
        }
        Delay_100ms ( );
    }
    return error_flag;
}

err_t ninaw152_generic_read ( ninaw152_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = NINAW152_OK;
    if ( NINAW152_DRV_SEL_UART == ctx->drv_sel ) 
    {
        error_flag = uart_read( &ctx->uart, data_out, len );
    }
    else
    {
        if ( !ninaw152_get_sry_pin ( ctx ) )
        {
            return NINAW152_OK;
        }
        uint8_t header[ 4 ] = { 0 };
        uint16_t rx_len = 0;
        spi_master_select_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, NINAW152_SPI_HEADER_0 );
        error_flag = spi_master_read( &ctx->spi, &header[ 0 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, NINAW152_SPI_HEADER_1 );
        error_flag |= spi_master_read( &ctx->spi, &header[ 1 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, DUMMY );
        error_flag |= spi_master_read( &ctx->spi, &header[ 2 ], 2 );
        if ( ( NINAW152_SPI_HEADER_0 != header[ 0 ] ) || 
             ( NINAW152_SPI_HEADER_1 != header[ 1 ] ) )
        {
            // No header bytes read
            error_flag |= NINAW152_ERROR;
        }
        if ( NINAW152_OK == error_flag )
        {
            if ( ( NULL == data_out ) || ( 0 == len ) )
            {
                // Check NORX flag only
                if ( header[ 2 ] & NINAW152_SPI_NORX )
                {
                    error_flag |= NINAW152_ERROR;
                }
            }
            else
            {
                header[ 2 ] &= ( ~NINAW152_SPI_NORX );
                rx_len = ( ( uint16_t ) header[ 2 ] << 8 ) | header[ 3 ];
                if ( rx_len > len )
                {
                    // accept only up to len number of payload bytes
                    rx_len = len;
                }
                if ( rx_len > 0 )
                {
                    error_flag |= spi_master_read( &ctx->spi, data_out, rx_len );
                }
                if ( NINAW152_OK == error_flag )
                {
                    // return the number of bytes that are actually read
                    error_flag = rx_len;
                }
            }
        }
        spi_master_deselect_device( ctx->chip_select );
    }
    return error_flag;
}

void ninaw152_set_rst_pin ( ninaw152_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void ninaw152_reset_device ( ninaw152_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
    Delay_1sec ( );
    Delay_1sec ( );
}

void ninaw152_set_cts_pin ( ninaw152_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->cts, state );
}

void ninaw152_set_esc_pin ( ninaw152_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->esc, state );
}

uint8_t ninaw152_get_rts_pin ( ninaw152_t *ctx )
{
    return digital_in_read ( &ctx->rts );
}

uint8_t ninaw152_get_sry_pin ( ninaw152_t *ctx )
{
    return digital_in_read ( &ctx->sry );
}

void ninaw152_send_cmd ( ninaw152_t *ctx, uint8_t *cmd )
{
    uint8_t final_cmd[ NINAW152_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t carriage_return[ 2 ] = { '\r', 0 };
    strcpy( final_cmd, cmd );
    strcat( final_cmd, carriage_return );
    ninaw152_generic_write( ctx, final_cmd, strlen ( final_cmd ) );
    Delay_100ms(  );
}

void ninaw152_send_cmd_with_par ( ninaw152_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf )
{
    uint8_t final_cmd[ NINAW152_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t equal_char[ 2 ] = { '=', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, equal_char );
    strcat( final_cmd, param_buf );
    
    ninaw152_send_cmd( ctx, final_cmd );
}

void ninaw152_send_cmd_check ( ninaw152_t *ctx, uint8_t *at_cmd_buf )
{
    uint8_t final_cmd[ NINAW152_TX_DRV_BUFFER_SIZE ] = { 0 };
    uint8_t check_char[ 2 ] = { '?', 0 };
    
    strcpy( final_cmd, at_cmd_buf );
    strcat( final_cmd, check_char );
    
    ninaw152_send_cmd( ctx, final_cmd );
}

// ------------------------------------------------------------------------- END
