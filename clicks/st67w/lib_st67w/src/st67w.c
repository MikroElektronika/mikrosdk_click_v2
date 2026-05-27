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
 * @file st67w.c
 * @brief ST67W Click Driver.
 */

#include "st67w.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void st67w_cfg_setup ( st67w_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->boot = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t st67w_init ( st67w_t *ctx, st67w_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    Delay_10ms ( );

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

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

    digital_out_init( &ctx->boot, cfg->boot );
    digital_out_init( &ctx->en, cfg->en );
    Delay_1ms ( );
    digital_out_low( &ctx->boot );
    digital_out_low( &ctx->en );

    digital_in_init( &ctx->rdy, cfg->rdy );
    Delay_10ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t st67w_generic_write ( st67w_t *ctx, uint8_t *data_in, uint16_t len ) 
{
    err_t error_flag = ST67W_OK;
    uint32_t timeout_cnt = 0;
    uint8_t header[ 8 ] = { 0 };
    header[ 0 ] = ST67W_SPI_SYNC_0;
    header[ 1 ] = ST67W_SPI_SYNC_1;
    header[ 2 ] = ( uint8_t ) ( len & 0xFF );
    header[ 3 ] = ( uint8_t ) ( ( len >> 8 ) & 0xFF );
    header[ 4 ] = ST67W_SPI_FRAME_BYTE;
    header[ 5 ] = ST67W_SPI_TYPE_BYTE;
    header[ 6 ] = ST67W_SPI_RESERVED_BYTE;
    header[ 7 ] = ST67W_SPI_RESERVED_BYTE;

    Delay_100ms ( );
    spi_master_select_device( ctx->chip_select );

    while ( !st67w_get_rdy_pin ( ctx ) )
    {
        timeout_cnt++;
        if ( timeout_cnt > ST67W_SPI_READY_TIMEOUT_MS )
        {
            spi_master_deselect_device( ctx->chip_select );
            return ST67W_ERROR_TIMEOUT;
        }
        Delay_1ms ( );
    }

    error_flag = spi_master_write( &ctx->spi, header, 8 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    memset ( header, ST67W_SPI_PADDING_BYTE, 3 );
    if ( len % 4 )
    {
        // Number of transmitted bytes must be divisible by 4.
        error_flag |= spi_master_write( &ctx->spi, header, 4 - len % 4 );
    }
    spi_master_deselect_device( ctx->chip_select );
    if ( ST67W_OK == error_flag )
    {
        // return the number of bytes that are actually written
        error_flag = len;
    }
    Delay_100ms ( );
    return error_flag;
}

err_t st67w_generic_read ( st67w_t *ctx, uint8_t *data_out, uint16_t len ) 
{
    err_t error_flag = ST67W_OK;
    if ( !st67w_get_rdy_pin ( ctx ) )
    {
        return ST67W_OK;
    }
    uint8_t header[ 8 ] = { 0 };
    uint16_t rx_len = 0;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, header, 8 );
    if ( ( ST67W_SPI_SYNC_0 != header[ 0 ] ) || ( ST67W_SPI_SYNC_1 != header[ 1 ] ) )
    {
        // No header bytes read
        error_flag |= ST67W_ERROR;
    }
    if ( ST67W_OK == error_flag )
    {
        if ( ( NULL == data_out ) || ( 0 == len ) )
        {
            error_flag |= ST67W_ERROR;
        }
        else
        {
            rx_len = ( ( uint16_t ) header[ 3 ] << 8 ) | header[ 2 ];
            if ( rx_len > len )
            {
                // accept only up to len number of payload bytes
                rx_len = len;
            }
            if ( rx_len > 0 )
            {
                error_flag |= spi_master_read( &ctx->spi, data_out, rx_len );
            }
            if ( ST67W_OK == error_flag )
            {
                // return the number of bytes that are actually read
                error_flag = rx_len;
            }
        }
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void st67w_set_boot_pin ( st67w_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->boot, state );
}

void st67w_enable_device ( st67w_t *ctx )
{
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

void st67w_disable_device ( st67w_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_1ms ( );
}

void st67w_reset_device ( st67w_t *ctx )
{
    digital_out_low ( &ctx->en );
    Delay_1ms ( );
    digital_out_high ( &ctx->en );
    Delay_100ms ( );
}

uint8_t st67w_get_rdy_pin ( st67w_t *ctx )
{
    return !!digital_in_read ( &ctx->rdy );
}

void st67w_cmd_run ( st67w_t *ctx, uint8_t *cmd )
{
    uint8_t cr_lf[ 3 ] = { '\r', '\n', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, cr_lf );

    st67w_generic_write( ctx, ctx->cmd_buffer, strlen ( ctx->cmd_buffer ) );
    Delay_100ms(  );
}

void st67w_cmd_set ( st67w_t *ctx, uint8_t *cmd, uint8_t *value )
{
    uint8_t equal_char[ 2 ] = { '=', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, equal_char );
    strcat( ctx->cmd_buffer, value );

    st67w_cmd_run( ctx, ctx->cmd_buffer );
}

void st67w_cmd_get ( st67w_t *ctx, uint8_t *cmd )
{
    uint8_t check_char[ 2 ] = { '?', 0 };

    strcpy( ctx->cmd_buffer, cmd );
    strcat( ctx->cmd_buffer, check_char );

    st67w_cmd_run( ctx, ctx->cmd_buffer );
}

// ------------------------------------------------------------------------- END
