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
 * @file flash10.c
 * @brief Flash 10 Click Driver.
 */

#include "flash10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash10_cfg_setup ( flash10_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t flash10_init ( flash10_t *ctx, flash10_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wp, cfg->wp );
    digital_out_high ( &ctx->rst );
    digital_out_high ( &ctx->wp );

    return SPI_MASTER_SUCCESS;
}

err_t flash10_write_cmd ( flash10_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash10_write_cmd_data ( flash10_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    if ( ( NULL == data_in ) || ( len > 8 ) )
    {
        return FLASH10_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash10_read_cmd_data ( flash10_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    if ( ( NULL == data_out ) || ( len > 8 ) )
    {
        return FLASH10_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash10_write_cmd_address_data ( flash10_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_in, uint32_t len )
{
    if ( ( NULL == data_in ) || ( ( address + len ) > FLASH10_MAX_ADDRESS ) )
    {
        return FLASH10_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash10_read_cmd_address_data ( flash10_t *ctx, uint8_t cmd, uint32_t address, uint8_t *data_out, uint32_t len )
{
    if ( ( NULL == data_out ) || ( ( address + len ) > FLASH10_MAX_ADDRESS ) )
    {
        return FLASH10_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = cmd;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t flash10_memory_write ( flash10_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len )
{
    if ( len > FLASH10_PAGE_SIZE )
    {
        return FLASH10_ERROR;
    }
    err_t error_flag = flash10_write_enable ( ctx );
    error_flag |= flash10_write_cmd_address_data ( ctx, FLASH10_CMD_BYTE_PAGE_PROGRAM, address, data_in, len );
    error_flag |= flash10_write_protect ( ctx );
    return error_flag;
}

err_t flash10_memory_read ( flash10_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    return flash10_read_cmd_address_data ( ctx, FLASH10_CMD_READ_ARRAY, address, data_out, len );
}

err_t flash10_erase_memory ( flash10_t *ctx, uint8_t erase_cmd, uint32_t address )
{
    if ( ( address > FLASH10_MAX_ADDRESS ) || 
         ( ( FLASH10_CMD_BLOCK_ERASE_4KB != erase_cmd ) && 
           ( FLASH10_CMD_BLOCK_ERASE_32KB != erase_cmd ) && 
           ( FLASH10_CMD_BLOCK_ERASE_64KB != erase_cmd ) && 
           ( FLASH10_CMD_CHIP_ERASE != erase_cmd ) ) )
    {
        return FLASH10_ERROR;
    }
    err_t error_flag = flash10_write_enable ( ctx );
    if ( FLASH10_CMD_CHIP_ERASE == erase_cmd )
    {
        error_flag |= flash10_write_cmd ( ctx, erase_cmd );
    }
    else
    {
        uint8_t data_buf[ 3 ] = { 0 };
        data_buf[ 0 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
        error_flag |= flash10_write_cmd_data ( ctx, erase_cmd, data_buf, 3 );
    }
    uint8_t status;
    do 
    {
        Delay_100ms ( );
        error_flag |= flash10_read_status ( ctx, FLASH10_STATUS_REG_1, &status );
    }
    while ( ( FLASH10_OK == error_flag ) && ( FLASH10_STATUS1_BSY == ( status & FLASH10_STATUS1_BSY ) ) );
    return error_flag;
}

err_t flash10_check_communication ( flash10_t *ctx )
{
    uint8_t device_id[ 2 ];
    if ( FLASH10_OK == flash10_read_cmd_address_data( ctx, FLASH10_CMD_MANUFACTURER_ID, DUMMY, device_id, 2 ) )
    {
        if ( ( FLASH10_MANUFACTURER_ID == device_id[ 0 ] ) && 
             ( FLASH10_DEVICE_ID == device_id[ 1 ] ) )
        {
            return FLASH10_OK;
        }
    }
    return FLASH10_ERROR;
}

err_t flash10_write_protect ( flash10_t *ctx )
{
    digital_out_low ( &ctx->wp );
    err_t error_flag = flash10_write_cmd ( ctx, FLASH10_CMD_WRITE_DISABLE );
    uint8_t status;
    error_flag |= flash10_read_status ( ctx, FLASH10_STATUS_REG_1, &status );
    if ( ( FLASH10_OK == error_flag ) && ( FLASH10_STATUS1_WEL != ( status & FLASH10_STATUS1_WEL ) ) )
    {
        return FLASH10_OK;
    }
    return FLASH10_ERROR;
}

err_t flash10_write_enable ( flash10_t *ctx )
{
    digital_out_high ( &ctx->wp );
    err_t error_flag = flash10_write_cmd ( ctx, FLASH10_CMD_WRITE_ENABLE );
    uint8_t status;
    error_flag |= flash10_read_status ( ctx, FLASH10_STATUS_REG_1, &status );
    if ( ( FLASH10_OK == error_flag ) && ( FLASH10_STATUS1_WEL == ( status & FLASH10_STATUS1_WEL ) ) )
    {
        return FLASH10_OK;
    }
    return FLASH10_ERROR;
}

err_t flash10_soft_reset ( flash10_t *ctx )
{
    err_t error_flag = flash10_write_cmd ( ctx, FLASH10_CMD_ENABLE_RESET );
    error_flag |= flash10_write_cmd ( ctx, FLASH10_CMD_RESET_DEVICE );
    return error_flag;
}

err_t flash10_write_status ( flash10_t *ctx, uint8_t status_reg_num, uint8_t status )
{
    if ( ( status_reg_num < FLASH10_STATUS_REG_1 ) || ( status_reg_num > FLASH10_STATUS_REG_5 ) )
    {
        return FLASH10_ERROR;
    }
    err_t error_flag = flash10_write_enable ( ctx );
    error_flag |= flash10_write_cmd_address_data ( ctx, FLASH10_CMD_WRITE_STATUS, 
                                                   ( uint32_t ) status_reg_num, &status, 1 );
    error_flag |= flash10_write_protect ( ctx );
    return error_flag;
}

err_t flash10_read_status ( flash10_t *ctx, uint8_t status_reg_num, uint8_t *status )
{
    if ( ( status_reg_num < FLASH10_STATUS_REG_1 ) || ( status_reg_num > FLASH10_STATUS_REG_5 ) )
    {
        return FLASH10_ERROR;
    }
    return flash10_read_cmd_address_data ( ctx, FLASH10_CMD_READ_STATUS, ( uint32_t ) status_reg_num, status, 1 );
}

void flash10_set_wp_pin ( flash10_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void flash10_set_rst_pin ( flash10_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

// ------------------------------------------------------------------------- END
