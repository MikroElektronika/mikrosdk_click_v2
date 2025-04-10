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
 * @file flash13.c
 * @brief Flash 13 Click Driver.
 */

#include "flash13.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash13_cfg_setup ( flash13_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->hold = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t flash13_init ( flash13_t *ctx, flash13_cfg_t *cfg ) 
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
    digital_out_init( &ctx->hold, cfg->hold );
    Delay_100ms ( );
    digital_out_high ( &ctx->wp );
    digital_out_high ( &ctx->hold );
    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t flash13_write_cmd ( flash13_t *ctx, uint8_t cmd )
{
    err_t error_flag = FLASH13_OK;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash13_write_cmd_data ( flash13_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = FLASH13_OK;
    if ( ( NULL == data_in ) || ( len > 8 ) )
    {
        return FLASH13_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash13_read_cmd_data ( flash13_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = FLASH13_OK;
    if ( ( NULL == data_out ) || ( len > 8 ) )
    {
        return FLASH13_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash13_write_cmd_address_data ( flash13_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = FLASH13_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( NULL == data_in ) || ( ( address + len - 1 ) > FLASH13_MAX_ADDRESS ) )
    {
        return FLASH13_ERROR;
    }
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash13_read_cmd_address_data ( flash13_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len )
{
    err_t error_flag = FLASH13_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( NULL == data_out ) || ( ( address + len - 1 ) > FLASH13_MAX_ADDRESS ) )
    {
        return FLASH13_ERROR;
    }
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash13_memory_write ( flash13_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len )
{
    err_t error_flag = FLASH13_OK;
    if ( len > FLASH13_PAGE_SIZE )
    {
        return FLASH13_ERROR;
    }
    error_flag |= flash13_write_enable ( ctx );
    error_flag |= flash13_write_cmd_address_data ( ctx, FLASH13_CMD_PAGE_PROGRAM, address, data_in, len );
    error_flag |= flash13_write_protect ( ctx );
    return error_flag;
}

err_t flash13_memory_read ( flash13_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    return flash13_read_cmd_address_data ( ctx, FLASH13_CMD_READ_DATA, address, data_out, len );
}

err_t flash13_erase_memory ( flash13_t *ctx, uint8_t erase_cmd, uint32_t address )
{
    err_t error_flag = FLASH13_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t status = 0;
    if ( ( address > FLASH13_MAX_ADDRESS ) || 
         ( ( FLASH13_CMD_SECTOR_ERASE_4KB != erase_cmd ) && 
           ( FLASH13_CMD_BLOCK_ERASE_32KB != erase_cmd ) && 
           ( FLASH13_CMD_BLOCK_ERASE_64KB != erase_cmd ) && 
           ( FLASH13_CMD_CHIP_ERASE != erase_cmd ) ) )
    {
        return FLASH13_ERROR;
    }
    error_flag |= flash13_write_enable ( ctx );
    if ( FLASH13_CMD_CHIP_ERASE == erase_cmd )
    {
        error_flag |= flash13_write_cmd ( ctx, erase_cmd );
    }
    else
    {
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
        error_flag |= flash13_write_cmd_data ( ctx, erase_cmd, data_buf, 3 );
    }
    do 
    {
        Delay_100ms ( );
        error_flag |= flash13_read_cmd_data ( ctx, FLASH13_CMD_READ_STATUS_REG_1, &status, 1 );
    }
    while ( ( FLASH13_OK == error_flag ) && ( FLASH13_STATUS1_WIP == ( status & FLASH13_STATUS1_WIP ) ) );
    return error_flag;
}

err_t flash13_check_communication ( flash13_t *ctx )
{
    uint8_t device_id[ 2 ] = { 0 };
    if ( FLASH13_OK == flash13_read_cmd_address_data( ctx, FLASH13_CMD_MANUFACTURER_DEVICE_ID, DUMMY, device_id, 2 ) )
    {
        if ( ( FLASH13_MANUFACTURER_ID == device_id[ 0 ] ) && 
             ( FLASH13_DEVICE_ID == device_id[ 1 ] ) )
        {
            return FLASH13_OK;
        }
    }
    return FLASH13_ERROR;
}

err_t flash13_write_protect ( flash13_t *ctx )
{
    err_t error_flag = FLASH13_OK;
    uint8_t status = 0;
    digital_out_low ( &ctx->wp );
    error_flag |= flash13_write_cmd ( ctx, FLASH13_CMD_WRITE_DISABLE );
    error_flag |= flash13_read_cmd_data ( ctx, FLASH13_CMD_READ_STATUS_REG_1, &status, 1 );
    if ( ( FLASH13_OK == error_flag ) && ( FLASH13_STATUS1_WEL != ( status & FLASH13_STATUS1_WEL ) ) )
    {
        return FLASH13_OK;
    }
    return FLASH13_ERROR;
}

err_t flash13_write_enable ( flash13_t *ctx )
{
    err_t error_flag = FLASH13_OK;
    uint8_t status = 0;
    digital_out_high ( &ctx->wp );
    error_flag |= flash13_write_cmd ( ctx, FLASH13_CMD_WRITE_ENABLE );
    error_flag |= flash13_read_cmd_data ( ctx, FLASH13_CMD_READ_STATUS_REG_1, &status, 1 );
    if ( ( FLASH13_OK == error_flag ) && ( FLASH13_STATUS1_WEL == ( status & FLASH13_STATUS1_WEL ) ) )
    {
        return FLASH13_OK;
    }
    return FLASH13_ERROR;
}

err_t flash13_soft_reset ( flash13_t *ctx )
{
    err_t error_flag = FLASH13_OK;
    error_flag |= flash13_write_cmd ( ctx, FLASH13_CMD_ENABLE_RESET );
    error_flag |= flash13_write_cmd ( ctx, FLASH13_CMD_RESET_DEVICE );
    return error_flag;
}

void flash13_set_wp_pin ( flash13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void flash13_set_hold_pin ( flash13_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hold, state );
}

// ------------------------------------------------------------------------- END
