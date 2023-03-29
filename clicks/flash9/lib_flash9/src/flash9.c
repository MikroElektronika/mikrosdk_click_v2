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
 * @file flash9.c
 * @brief Flash 9 Click Driver.
 */

#include "flash9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash9_cfg_setup ( flash9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->hld  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t flash9_init ( flash9_t *ctx, flash9_cfg_t *cfg ) 
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
    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->hld, cfg->hld );

    return SPI_MASTER_SUCCESS;
}

err_t flash9_default_cfg ( flash9_t *ctx ) 
{
    err_t error_flag = FLASH9_OK;
    
    flash9_set_rst_pin ( ctx, 1 );
    flash9_set_hld_pin ( ctx, 1 );
    flash9_set_wp_pin ( ctx, 1 );
    Delay_100ms ( );
    
    if ( FLASH9_ERROR == flash9_check_communication ( ctx ) )
    {
        return FLASH9_ERROR;
    }
    Delay_100ms ( );

    return error_flag;
}

err_t flash9_generic_write ( flash9_t *ctx, uint8_t *data_in, uint16_t in_len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, in_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash9_generic_read ( flash9_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint16_t out_len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_in, in_len, data_out, out_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash9_write_register ( flash9_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t in_len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    if ( in_len > 0 )
    {
        error_flag |= spi_master_write( &ctx->spi, data_in, in_len );
    }
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash9_read_register ( flash9_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t out_len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, out_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash9_write_command ( flash9_t *ctx, uint8_t cmd ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void flash9_set_wp_pin ( flash9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void flash9_set_hld_pin ( flash9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hld, state );
}

void flash9_set_rst_pin ( flash9_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

err_t flash9_check_communication ( flash9_t *ctx ) 
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( FLASH9_OK == flash9_read_register ( ctx, FLASH9_CMD_JEDEC_ID, data_buf, 3 ) )
    {
        if ( ( FLASH9_JEDEC_MANUFACTURER_ID == data_buf[ 0 ] ) && 
             ( FLASH9_JEDEC_MEMORY_TYPE == data_buf[ 1 ] ) && 
             ( FLASH9_JEDEC_CAPACITY == data_buf[ 2 ] ) )
        {
            return FLASH9_OK;
        }
    }
    return FLASH9_ERROR;
}

err_t flash9_erase_memory ( flash9_t *ctx, uint8_t erase_cmd, uint32_t address )
{
    if ( address > FLASH9_MAX_ADDRESS )
    {
        return FLASH9_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( FLASH9_CMD_SECTOR_ERASE == erase_cmd ) || ( FLASH9_CMD_BLOCK_ERASE_32KB == erase_cmd ) ||
         ( FLASH9_CMD_BLOCK_ERASE_64KB == erase_cmd ) || ( FLASH9_CMD_ERASE_SECURITY_REGISTER == erase_cmd ) )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
        
        err_t error_flag = flash9_write_command ( ctx, FLASH9_CMD_WRITE_ENABLE );
        error_flag |= flash9_write_register ( ctx, erase_cmd, data_buf, 3 );
        return error_flag;
    }
    else if ( ( FLASH9_CMD_SECTOR_ERASE_WITH_4BYTE_ADDRESS == erase_cmd ) || 
              ( FLASH9_CMD_BLOCK_ERASE_64KB_WITH_4BYTE_ADDRESS == erase_cmd ) )
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
        
        err_t error_flag = flash9_write_command ( ctx, FLASH9_CMD_WRITE_ENABLE );
        error_flag |= flash9_write_register ( ctx, erase_cmd, data_buf, 4 );
        return error_flag;
    }
    return FLASH9_ERROR;
}

err_t flash9_read_status ( flash9_t *ctx, uint8_t status_cmd, uint8_t *status )
{
    if ( ( FLASH9_CMD_READ_STATUS_REGISTER_1 == status_cmd ) || 
         ( FLASH9_CMD_READ_STATUS_REGISTER_2 == status_cmd ) ||
         ( FLASH9_CMD_READ_STATUS_REGISTER_3 == status_cmd ) )
    {
        return flash9_read_register ( ctx, status_cmd, status, 1 );
    }
    return FLASH9_ERROR;
}

err_t flash9_write_status ( flash9_t *ctx, uint8_t status_cmd, uint8_t status )
{
    if ( ( FLASH9_CMD_WRITE_STATUS_REGISTER_1 == status_cmd ) || 
         ( FLASH9_CMD_WRITE_STATUS_REGISTER_2 == status_cmd ) ||
         ( FLASH9_CMD_WRITE_STATUS_REGISTER_3 == status_cmd ) )
    {
        return flash9_write_register ( ctx, status_cmd, &status, 1 );
    }
    return FLASH9_ERROR;
}

err_t flash9_memory_write ( flash9_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len )
{
    if ( address > FLASH9_MAX_ADDRESS )
    {
        return FLASH9_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = FLASH9_CMD_PAGE_PROGRAM_WITH_4BYTE_ADDRESS;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( address & 0xFF );
    
    err_t error_flag = flash9_write_command ( ctx, FLASH9_CMD_WRITE_ENABLE );
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 5 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash9_memory_read ( flash9_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len )
{
    if ( address > FLASH9_MAX_ADDRESS )
    {
        return FLASH9_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = FLASH9_CMD_READ_DATA_WITH_4BYTE_ADDRESS;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( address & 0xFF );
    return flash9_generic_read( ctx, data_buf, 5, data_out, len );
}

err_t flash9_memory_read_fast ( flash9_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len )
{
    if ( address > FLASH9_MAX_ADDRESS )
    {
        return FLASH9_ERROR;
    }
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = FLASH9_CMD_FAST_READ_WITH_4BYTE_ADDRESS;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 24 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( address & 0xFF );
    data_buf[ 5 ] = DUMMY;
    return flash9_generic_read( ctx, data_buf, 6, data_out, len );
}

// ------------------------------------------------------------------------- END
