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
 * @file eeprom5.c
 * @brief EEPROM 5 Click Driver.
 */

#include "eeprom5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void eeprom5_cfg_setup ( eeprom5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hld = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t eeprom5_init ( eeprom5_t *ctx, eeprom5_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

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

    digital_out_init( &ctx->hld, cfg->hld );
    digital_out_init( &ctx->wp, cfg->wp );

    return SPI_MASTER_SUCCESS;
}

void eeprom5_generic_write ( eeprom5_t *ctx, uint32_t addr, uint8_t tx_data ) 
{
    uint8_t tx_buf[ 5 ] = { 0 };
    
    addr &= EEPROM5_MEMORY_ADDR_END;

    tx_buf[ 0 ] = EEPROM5_CMD_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) addr;
    tx_buf[ 4 ] = tx_data;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t eeprom5_generic_read ( eeprom5_t *ctx, uint32_t addr ) 
{
    uint8_t tx_buf[ 4 ] = { 0 };
    uint8_t rx_buf[ 1 ] = { 0 };
    
    addr &= EEPROM5_MEMORY_ADDR_END;

    tx_buf[ 0 ] = EEPROM5_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) addr;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, rx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return rx_buf[ 0 ];
}

void eeprom5_set_hold ( eeprom5_t *ctx, uint8_t en_hold ) 
{
    if ( EEPROM5_HOLD_ENABLE == en_hold ) 
    {
        digital_out_low( &ctx->hld );
    } 
    else 
    {
        digital_out_high( &ctx->hld );
    }
}

void eeprom5_set_write_protect ( eeprom5_t *ctx, uint8_t en_wr_prot ) 
{
    if ( EEPROM5_WRITE_PROTECT_ENABLE == en_wr_prot ) 
    {
        digital_out_low( &ctx->wp );
    } 
    else 
    {
        digital_out_high( &ctx->wp );
    }
}

void eeprom5_send_cmd ( eeprom5_t *ctx, uint8_t cmd ) 
{
    uint8_t tx_buf[ 1 ] = { 0 };
    
    tx_buf[ 0 ] = cmd;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );
}

void eeprom5_enable_memory_write ( eeprom5_t *ctx, uint8_t en_wr_mem ) 
{
    uint8_t tx_cmd = 0;
    
    tx_cmd = EEPROM5_CMD_WRDI;
    
    if ( EEPROM5_WRITE_MEMORY_ENABLE == en_wr_mem ) 
    {
        tx_cmd = EEPROM5_CMD_WREN;
    }

    eeprom5_send_cmd( ctx, tx_cmd );
}

void eeprom5_get_status ( eeprom5_t *ctx, status_data_t *stat_data ) 
{
    uint8_t tx_buf[ 3 ] = { 0 };
    uint8_t rx_buf[ 3 ] = { 0 };

    tx_buf[ 0 ] = EEPROM5_CMD_RDSR;
    tx_buf[ 1 ] = EEPROM5_DUMMY;
    tx_buf[ 2 ] = EEPROM5_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 3, rx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    stat_data->write_in_progress  = rx_buf[ 1 ] & 0x01;
    stat_data->write_enable_latch = ( rx_buf[ 1 ] >> 1 ) & 0x01;
    stat_data->block_protect      = ( rx_buf[ 1 ] >> 2 ) & 0x03;
    stat_data->write_protect      = ( rx_buf[ 1 ] >> 7 ) & 0x01;
}

void eeprom5_set_status ( eeprom5_t *ctx, status_data_t stat_data ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ]  = EEPROM5_CMD_WRSR;
    tx_buf[ 1 ]  = stat_data.write_protect      << 7;
    tx_buf[ 1 ] |= stat_data.block_protect      << 2;
    tx_buf[ 1 ] |= stat_data.write_enable_latch << 1;
    tx_buf[ 1 ] |= stat_data.write_in_progress;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void eeprom5_read_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_rx_data, uint8_t n_bytes ) 
{
    uint8_t tx_buf[ 4 ] = { 0 };
    
    addr &= EEPROM5_MEMORY_ADDR_END;

    tx_buf[ 0 ] = EEPROM5_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) addr;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 4, p_rx_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

void eeprom5_write_memory ( eeprom5_t *ctx, uint32_t addr, uint8_t *p_tx_data, uint8_t n_bytes ) 
{
    uint8_t tx_buf[ 4 ] = { 0 };
    
    addr &= EEPROM5_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM5_CMD_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) addr;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_write( &ctx->spi, p_tx_data, n_bytes );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t eeprom5_read_ident_page ( eeprom5_t *ctx, uint16_t addr ) 
{
    uint8_t tx_buf[ 5 ] = { 0 };
    uint8_t rx_buf[ 5 ] = { 0 };

    addr &= EEPROM5_IDENT_PAGE_ADDR_END;

    tx_buf[ 0 ] = EEPROM5_CMD_READ_ID;
    tx_buf[ 1 ] = EEPROM5_DUMMY;
    tx_buf[ 2 ] = EEPROM5_DUMMY & EEPROM5_SIGNIFICANT_ADDR_BIT_0;
    tx_buf[ 2 ] |= ( uint8_t ) ( ( addr >> 8 ) & 0x01 );
    tx_buf[ 3 ] = ( uint8_t ) addr;
    tx_buf[ 4 ] = EEPROM5_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 5, rx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
    
    return rx_buf[ 4 ];
}

void eeprom5_write_ident_page ( eeprom5_t *ctx, uint16_t addr, uint8_t ident_data ) 
{
    uint8_t tx_buf[ 5 ] = { 0 };

    addr &= EEPROM5_IDENT_PAGE_ADDR_END;

    tx_buf[ 0 ] = EEPROM5_CMD_WRITE_ID;
    tx_buf[ 1 ] = EEPROM5_DUMMY;
    tx_buf[ 2 ] = EEPROM5_DUMMY & EEPROM5_SIGNIFICANT_ADDR_BIT_0;
    tx_buf[ 2 ] |= ( uint8_t ) ( ( addr >> 8 ) & 0x01 );
    tx_buf[ 3 ] = ( uint8_t ) addr;
    tx_buf[ 4 ] = ident_data;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
}

uint8_t eeprom5_read_lock_status ( eeprom5_t *ctx ) 
{
    uint8_t tx_buf[ 5 ] = { 0 };
    uint8_t rx_buf[ 5 ] = { 0 };

    tx_buf[ 0 ] = EEPROM5_CMD_READ_LOCK_STATUS;
    tx_buf[ 1 ] = EEPROM5_DUMMY;
    tx_buf[ 2 ] = EEPROM5_DUMMY | EEPROM5_SIGNIFICANT_ADDR_BIT_1;
    tx_buf[ 3 ] = EEPROM5_DUMMY;
    tx_buf[ 4 ] = EEPROM5_DUMMY;

    spi_master_select_device( ctx->chip_select );
    spi_master_write_then_read( &ctx->spi, tx_buf, 5, rx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );

    return rx_buf[ 4 ];
}

void eeprom5_lock_id ( eeprom5_t *ctx, uint8_t lock_id ) 
{
    uint8_t tx_buf[ 5 ] = { 0 };

    tx_buf[ 0 ] = EEPROM5_CMD_LOCK_ID;
    tx_buf[ 1 ] = EEPROM5_DUMMY;
    tx_buf[ 2 ] = EEPROM5_DUMMY | EEPROM5_SIGNIFICANT_ADDR_BIT_1;
    tx_buf[ 3 ] = EEPROM5_DUMMY;
    tx_buf[ 4 ] = lock_id | 0x02;

    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 5 );
    spi_master_deselect_device( ctx->chip_select );
}
// ------------------------------------------------------------------------- END
