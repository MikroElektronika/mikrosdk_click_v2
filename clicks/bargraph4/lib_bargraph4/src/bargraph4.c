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
 * @file bargraph4.c
 * @brief BarGraph 4 Click Driver.
 */

#include "bargraph4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void bargraph4_cfg_setup ( bargraph4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed   = 5000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_HIGH;
}

err_t bargraph4_init ( bargraph4_t *ctx, bargraph4_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );

    return SPI_MASTER_SUCCESS;
}

err_t bargraph4_set_output ( bargraph4_t *ctx, uint16_t ch_mask )
{
    uint8_t tx_buf[ 2 ] = { 0 };
    
    tx_buf[ 0 ] = ( uint8_t ) ( ( ch_mask >> 8 ) & 0xFF );
    tx_buf[ 1 ] = ( uint8_t ) ( ch_mask & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t bargraph4_read_output ( bargraph4_t *ctx, uint16_t *ch_mask )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    
    *ch_mask = ( uint16_t ) rx_buf[ 0 ] << 8;
    *ch_mask |= ( rx_buf[ 1 ] & 0xFF );
    
    return error_flag;
}

void bargraph4_disable_output ( bargraph4_t *ctx )
{
    digital_out_high( &ctx->rst );
}

void bargraph4_enable_output ( bargraph4_t *ctx )
{
    digital_out_low( &ctx->rst );
}

err_t bargraph4_set_channel_level ( bargraph4_t *ctx, bargraph4_sel_ch_t channel, bargraph4_level_t level )
{
    uint16_t out_write = 0;
    uint16_t out_read = 0;
    uint8_t shift_ch_bits = ( 3 - channel ) * 4;
    
    for ( uint8_t cnt = BARGRAPH4_LEVEL_0; cnt < level; cnt++ )
    {
        out_write |= ( BARGRAPH4_LEVEL_1 << cnt );
    }
    
    // Switch last two bits
    out_write = ( out_write & 0x0C ) | ( ( out_write >> 1 ) & 0x01 ) | ( ( out_write & 0x01 ) << 1 );
    
    // Channel selection
    out_write <<= shift_ch_bits;
    
    // Add other channels bits
    err_t error_flag = bargraph4_read_output ( ctx, &out_read );
    out_write |= ( out_read & ~( 0x0F << shift_ch_bits ) );
    
    // Set output
    error_flag |= bargraph4_set_output ( ctx, out_write );
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
