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
 * @file eeprom9.c
 * @brief EEPROM 9 Click Driver.
 */

#include "eeprom9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void eeprom9_cfg_setup ( eeprom9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->hld  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t eeprom9_init ( eeprom9_t *ctx, eeprom9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_init( &ctx->hld, cfg->hld );

    digital_out_high( &ctx->hld );
    digital_out_high( &ctx->wp );

    return SPI_MASTER_SUCCESS;
}

err_t eeprom9_generic_write ( eeprom9_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeprom9_generic_read ( eeprom9_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void eeprom9_set_hold ( eeprom9_t *ctx, uint8_t en_hold )
{
    if ( EEPROM9_HOLD_ENABLE == en_hold )
    {
        digital_out_low( &ctx->hld );
    }
    else
    {
        digital_out_high( &ctx->hld );
    }
}

void eeprom9_set_write_protection ( eeprom9_t *ctx, uint8_t en_wp )
{
    if ( EEPROM9_WRITE_PROTECT_ENABLE == en_wp )
    {
        digital_out_low( &ctx->wp );
    }
    else
    {
        digital_out_high( &ctx->wp );
    }
}

err_t eeprom9_send_cmd ( eeprom9_t *ctx, uint8_t cmd )
{
    err_t error_flag = EEPROM9_OK;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t eeprom9_set_write_enable ( eeprom9_t *ctx, uint8_t en_write )
{
    err_t error_flag = EEPROM9_OK;
    
    if ( EEPROM9_WRITE_ENABLE == en_write )
    {
        error_flag |= eeprom9_send_cmd( ctx, EEPROM9_CMD_WREN );
    }
    else
    {
        error_flag |= eeprom9_send_cmd( ctx, EEPROM9_CMD_WRDI );
    }
    
    return error_flag;
}

err_t eeprom9_read_memory ( eeprom9_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t tx_buf[ 4 ];
    mem_addr &= EEPROM9_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM9_CMD_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( mem_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) mem_addr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t eeprom9_write_memory ( eeprom9_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t tx_buf[ 4 ];
    mem_addr &= EEPROM9_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM9_CMD_PGWR;
    tx_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( mem_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) mem_addr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t eeprom5_get_status_reg ( eeprom9_t *ctx, uint8_t *status_data )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t tx_data = EEPROM9_CMD_RDSR;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &tx_data, 1, status_data, 1 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

err_t eeprom9_chip_erase ( eeprom9_t *ctx )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t status_data = 0;
    
    error_flag |= eeprom9_send_cmd( ctx, EEPROM9_CMD_CHER );
    
    error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
    
    while ( EEPROM9_WIP_MASK & status_data )
    {
        error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
        Delay_10ms( );
    }
    
    return error_flag;
}

err_t eeprom9_block_erase ( eeprom9_t *ctx, uint32_t block_addr )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t status_data = 0;
    uint8_t tx_buf[ 4 ];
    block_addr &= EEPROM9_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM9_CMD_BKER;
    tx_buf[ 1 ] = ( uint8_t ) ( block_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( block_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) block_addr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
    
    while ( EEPROM9_WIP_MASK & status_data )
    {
        error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
        Delay_10ms( );
    }
    
    return error_flag;
}

err_t eeprom9_sector_erase ( eeprom9_t *ctx, uint32_t sector_addr )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t status_data = 0;
    uint8_t tx_buf[ 4 ];
    sector_addr &= EEPROM9_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM9_CMD_SCER;
    tx_buf[ 1 ] = ( uint8_t ) ( sector_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( sector_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) sector_addr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
    
    while ( EEPROM9_WIP_MASK & status_data )
    {
        error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
        Delay_10ms( );
    }
    
    return error_flag;
}

err_t eeprom9_page_erase ( eeprom9_t *ctx, uint32_t page_addr )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t status_data = 0;
    uint8_t tx_buf[ 4 ];
    page_addr &= EEPROM9_MEMORY_ADDR_END;
    
    tx_buf[ 0 ] = EEPROM9_CMD_SCER;
    tx_buf[ 1 ] = ( uint8_t ) ( page_addr >> 16 );
    tx_buf[ 2 ] = ( uint8_t ) ( page_addr >> 8 );
    tx_buf[ 3 ] = ( uint8_t ) page_addr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    
    error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
    
    while ( EEPROM9_WIP_MASK & status_data )
    {
        error_flag |= eeprom5_get_status_reg ( ctx, &status_data );
        Delay_10ms( );
    }
    
    return error_flag;
}

err_t eeprom9_read_identification ( eeprom9_t *ctx, id_data_t *id_data  )
{
    err_t error_flag = EEPROM9_OK;
    uint8_t tx_data = EEPROM9_CMD_JEDPC;
    uint8_t rx_data[ 3 ];
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &tx_data, 1, rx_data, 3 );
    spi_master_deselect_device( ctx->chip_select );
    
    id_data->manufact_code = rx_data[ 0 ];
    id_data->spi_code = rx_data[ 1 ];
    id_data->memory_density = rx_data[ 2 ];
    
    return error_flag;
}

// ------------------------------------------------------------------------- END
