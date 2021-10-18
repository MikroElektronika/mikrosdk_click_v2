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
 * @file nvsram2.c
 * @brief nvSRAM 2 Click Driver.
 */

#include "nvsram2.h"

/**
 * @brief Write delay of 100 milliseconds.
 */
static void dev_config_delay ( void );

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void nvsram2_cfg_setup ( nvsram2_cfg_t *cfg ) {    
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t nvsram2_init ( nvsram2_t *ctx, nvsram2_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

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

    digital_out_init( &ctx->hld, cfg->hld );
    return SPI_MASTER_SUCCESS;
}

err_t nvsram2_default_cfg ( nvsram2_t *ctx ) {    
    // Click default configuration.
    nvsram2_hold( ctx, NVSRAM2_HOLD_DISABLE );
    dev_config_delay( );
     
    nvsram2_set_cmd( ctx, NVSRAM2_STATUS_WREN );
    dev_config_delay( );
    return NVSRAM2_OK;
}

err_t nvsram2_generic_write ( nvsram2_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {    
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

err_t nvsram2_generic_read ( nvsram2_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void nvsram2_hold ( nvsram2_t *ctx, uint8_t en_hold ) {    
    if ( en_hold == NVSRAM2_HOLD_ENABLE ) {        
        digital_out_low( &ctx->hld );    
    }
    else {       
        digital_out_high( &ctx->hld );    
    }
}

void nvsram2_set_cmd ( nvsram2_t *ctx, uint8_t cmd ) {
    uint8_t tx_buf[ 1 ];

    tx_buf[ 0 ] = cmd;

    spi_master_select_device( ctx->chip_select ); 
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
}

uint8_t nvsram2_read_status ( nvsram2_t *ctx ) {    
    uint8_t tx_buf[ 2 ];
    uint8_t rx_buf[ 2 ];
    
    tx_buf[ 0 ] = NVSRAM2_STATUS_RDSR;

    spi_master_select_device( ctx->chip_select ); 
    spi_master_write_then_read( &ctx->spi, &tx_buf, 1, &rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select ); 
    return rx_buf[ 0 ];
}

uint8_t nvsram2_fast_read_status ( nvsram2_t *ctx ) {
    uint8_t tx_buf[ 3 ];
    uint8_t rx_buf[ 3 ];

    tx_buf[ 0 ] = NVSRAM2_STATUS_RDSR;
    tx_buf[ 1 ] = NVSRAM2_DUMMY_BYTE;
    tx_buf[ 2 ] = NVSRAM2_DUMMY_BYTE;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, &tx_buf, 2, &rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return rx_buf[ 2 ];
}

void nvsram2_write_status ( nvsram2_t *ctx, uint8_t data_byte ) {    
    uint8_t tx_buf[ 2 ];

    tx_buf[ 0 ] = NVSRAM2_STATUS_WRSR;
    tx_buf[ 1 ] = data_byte;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void nvsram2_burst_read ( nvsram2_t *ctx, uint32_t mem_addr, uint8_t *p_rx_data, uint8_t n_bytes ) {
    uint8_t tx_buf[ 4 ];
    
    if ( n_bytes != 0 ) {
        mem_addr &= 0x0001FFFF;

        tx_buf[ 0 ] = NVSRAM2_SRAM_READ;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, &tx_buf, 4 );
        spi_master_read( &ctx->spi, p_rx_data, n_bytes );
        spi_master_deselect_device( ctx->chip_select );
    }
}

void nvsram2_burst_write ( nvsram2_t *ctx, uint32_t mem_addr, uint8_t *p_tx_data, uint8_t n_bytes ) {    
    uint8_t tx_buf[ 260 ];
    uint16_t cnt;
    uint16_t len;
    
    len = n_bytes + 4;

    if ( n_bytes != 0 ) {        
        tx_buf[ 0 ] = NVSRAM2_SRAM_WRITE;
        tx_buf[ 1 ] = ( uint8_t )( mem_addr >> 16 );
        tx_buf[ 2 ] = ( uint8_t )( mem_addr >> 8 );
        tx_buf[ 3 ] = ( uint8_t ) mem_addr;

        for ( cnt = 0; cnt < n_bytes; cnt++ ) {
            tx_buf[ cnt + 4 ] = p_tx_data[ cnt ];
        }

        spi_master_select_device( ctx->chip_select );
        spi_master_write( &ctx->spi, &tx_buf, len );
        spi_master_deselect_device( ctx->chip_select );
    }
}

uint32_t nvsram2_read_id ( nvsram2_t *ctx ) {
    uint8_t tx_buf[ 1 ];
    uint8_t rx_buf[ 4 ];
    uint32_t result;

    tx_buf[ 0 ] = NVSRAM2_SPEC_RDID;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, &tx_buf, 1 );
    spi_master_read( &ctx->spi, &tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    result = rx_buf[ 0 ];
    result <<= 8;
    result |= rx_buf[ 1 ];
    result <<= 8;
    result |= rx_buf[ 2 ];
    result <<= 8;
    result |= rx_buf[ 3 ];
    return result;
}

static void dev_config_delay ( void ) {
    Delay_100ms( );
}

// ------------------------------------------------------------------------- END
