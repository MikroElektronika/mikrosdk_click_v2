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
 * @file spiisolator2.c
 * @brief SPI Isolator 2 Click Driver.
 */

#include "spiisolator2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void spiisolator2_cfg_setup ( spiisolator2_cfg_t *cfg ) {    
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->en1 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t spiisolator2_init ( spiisolator2_t *ctx, spiisolator2_cfg_t *cfg ) {    
    spi_master_config_t spi_cfg;
    
    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }
    
    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }
    
    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }
    
    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {        
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->en1, cfg->en1 );
    return SPI_MASTER_SUCCESS;
}

err_t spiisolator2_generic_write ( spiisolator2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t spiisolator2_generic_read ( spiisolator2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void spiisolator2_output_enable( spiisolator2_t *ctx, uint8_t en_out ) {
    if( en_out = SPIISOLATOR2_OUT_ENABLE ) {
        digital_out_high( &ctx->en1 );
    }
    else {        
        digital_out_low( &ctx->en1 );
    }
}

void spiisolator2_set_cmd ( spiisolator2_t *ctx, uint8_t cmd ) {    
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void spiisolator2_write_byte ( spiisolator2_t *ctx, uint8_t reg, uint8_t tx_data ) {    
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = tx_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

}

uint8_t spiisolator2_read_byte ( spiisolator2_t *ctx, uint8_t reg ) {    
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];

    tx_buf[ 0 ] = reg;
    tx_buf[ 1 ] = SPIISOLATOR2_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_buf, 1, &rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return rx_buf[ 1 ];
}

void spiisolator2_burst_write ( spiisolator2_t *ctx, uint8_t reg, uint8_t *p_tx_data, uint8_t n_bytes ) {    
    uint8_t cnt;
    uint8_t tx_buf[ 256 ];

    tx_buf[ 0 ] = reg;

    for ( cnt = 0; cnt < n_bytes; cnt++ ) {
        tx_buf[ cnt + 1 ] = p_tx_data[ cnt ];
    }

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, n_bytes + 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void spiisolator2_burst_read ( spiisolator2_t *ctx, uint8_t reg, uint8_t *p_rx_data, uint8_t n_bytes ) {    
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = reg;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_read( &ctx->spi, p_rx_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

void spiisolator2_multi_write ( spiisolator2_t *ctx, uint32_t addr, uint8_t addr_n_bytes, uint8_t *p_tx_data, uint8_t tx_data_n_bytes ) {    
    uint8_t tx_buf[ 256 ];
    uint8_t n_cnt;

    if ( addr_n_bytes == 4 ) {        
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 24 );
        tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) addr;
    }
    else if ( addr_n_bytes == 3 ) {
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 16 );
        tx_buf[ 1 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 2 ] = ( uint8_t ) addr;
    }
    else if ( addr_n_bytes == 2 ) {
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 1 ] = ( uint8_t ) addr;
    }
    else {        
        tx_buf[ 0 ] = ( uint8_t ) addr;
    }

    for ( n_cnt = 0; n_cnt < tx_data_n_bytes; n_cnt++ ) {        
        tx_buf[ n_cnt + addr_n_bytes ] = p_tx_data[ n_cnt ];
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, tx_data_n_bytes + addr_n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

void spiisolator2_multi_read ( spiisolator2_t *ctx, uint32_t addr, uint8_t addr_n_bytes, uint8_t *p_rx_data, uint8_t tx_data_n_bytes ) {    
    uint8_t tx_buf[ 4 ];

    if ( addr_n_bytes == 4 ) {        
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 24 );
        tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) addr;
    }
    else if ( addr_n_bytes == 3 ) {        
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 16 );
        tx_buf[ 1 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 2 ] = ( uint8_t ) addr;
    }
    else if ( addr_n_bytes == 2 ) {        
        tx_buf[ 0 ] = ( uint8_t ) ( addr >> 8 );
        tx_buf[ 1 ] = ( uint8_t ) addr;
    }
    else {
        tx_buf[ 0 ] = ( uint8_t ) addr;
    }
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, addr_n_bytes );
    spi_master_read( &ctx->spi, p_rx_data, tx_data_n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

// ------------------------------------------------------------------------- END
