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
 * @file flash12.c
 * @brief Flash 12 Click Driver.
 */

#include "flash12.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash12_cfg_setup ( flash12_cfg_t *cfg ) 
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

err_t flash12_init ( flash12_t *ctx, flash12_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t flash12_default_cfg ( flash12_t *ctx ) 
{
    flash12_hold_disable( ctx );
    Delay_10ms( );
    
    flash12_hw_write_enable( ctx );
    Delay_10ms( );

    uint8_t mfr_id = DUMMY, dev_id = DUMMY;
    err_t err_flag = flash12_get_device_id( ctx, &mfr_id, &dev_id );
    if ( ( FLASH12_MANUFACTURER_ID != mfr_id ) || ( FLASH12_DEVICE_ID != dev_id ) )
    {
        err_flag = FLASH12_ERROR;
    }
    return err_flag;
}

void flash12_hw_write_enable ( flash12_t *ctx )
{
    digital_out_high( &ctx->wp );
}

void flash12_hw_write_disable ( flash12_t *ctx )
{
    digital_out_low( &ctx->wp );
}

void flash12_hold_disable ( flash12_t *ctx )
{
    digital_out_high( &ctx->hld );
}

void flash12_hold_enable ( flash12_t *ctx )
{
    digital_out_low( &ctx->hld );
}

err_t flash12_write_cmd ( flash12_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t flash12_write_cmd_data ( flash12_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t err_flag = FLASH12_ERROR;
    if ( ( NULL != data_in ) && ( FLASH12_CMD_MAX_LEN >= len ) )
    {
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write( &ctx->spi, &cmd, 1 );
        err_flag |= spi_master_write( &ctx->spi, data_in, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash12_read_cmd_data ( flash12_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    err_t err_flag = FLASH12_ERROR;
    if ( ( NULL != data_out ) && ( FLASH12_CMD_MAX_LEN >= len ) )
    {
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write_then_read( &ctx->spi, &cmd, 1, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash12_write_cmd_address_data ( flash12_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    err_t err_flag = FLASH12_ERROR;
    if ( ( NULL != data_in ) && ( FLASH12_MAX_ADDRESS > ( mem_addr + len ) ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) ( mem_addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )   mem_addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write( &ctx->spi, data_buf, 4 );
        err_flag |= spi_master_write( &ctx->spi, data_in, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash12_read_cmd_address_data ( flash12_t *ctx, uint8_t cmd, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    err_t err_flag = FLASH12_ERROR;
    if ( ( NULL != data_out ) && ( FLASH12_MAX_ADDRESS > ( mem_addr + len ) ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) ( mem_addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )   mem_addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash12_memory_write ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    err_t err_flag = FLASH12_ERROR;
    if ( len < FLASH12_PAGE_SIZE )
    {
        err_flag = flash12_write_enable( ctx );
        err_flag |= flash12_write_cmd_address_data( ctx, FLASH12_CMD_BYTE_PAGE_PROGRAM, mem_addr, data_in, len );
        err_flag |= flash12_write_disable( ctx );
    }
    return err_flag;
}

err_t flash12_memory_read ( flash12_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    return flash12_read_cmd_address_data( ctx, FLASH12_CMD_READ_ARRAY, mem_addr, data_out, len );
}

err_t flash12_soft_reset ( flash12_t *ctx )
{
    err_t err_flag = flash12_write_cmd( ctx, FLASH12_CMD_ENABLE_RESET );
    err_flag |= flash12_write_cmd( ctx, FLASH12_CMD_RESET_DEVICE );
    return err_flag;
}

err_t flash12_write_disable ( flash12_t *ctx )
{
    uint8_t status = DUMMY;
    flash12_hw_write_disable( ctx );
    err_t err_flag = flash12_write_cmd( ctx, FLASH12_CMD_WRITE_DISABLE );
    err_flag |= flash12_read_status( ctx, FLASH12_CMD_READ_STATUS_1, &status );
    if ( !( status & FLASH12_STATUS1_WEL ) )
    {
        err_flag = FLASH12_ERROR;
    }
    return err_flag;
}

err_t flash12_write_enable ( flash12_t *ctx )
{
    uint8_t status = DUMMY;
    flash12_hw_write_disable( ctx );
    err_t err_flag = flash12_write_cmd( ctx, FLASH12_CMD_WRITE_ENABLE );
    err_flag |= flash12_read_status( ctx, FLASH12_CMD_READ_STATUS_1, &status );
    if ( FLASH12_STATUS1_WEL != ( status & FLASH12_STATUS1_WEL ) )
    {
        err_flag = FLASH12_ERROR;
    }
    return err_flag;
}

err_t flash12_read_status ( flash12_t *ctx, uint8_t reg_num, uint8_t *status )
{
    err_t err_flag = FLASH12_ERROR;
    if ( FLASH12_CMD_READ_STATUS_1 == reg_num )
    {
        err_flag = flash12_read_cmd_data( ctx, FLASH12_CMD_READ_STATUS_1, status, 1 );
    }
    else if ( FLASH12_CMD_READ_STATUS_2 == reg_num )
    {
        err_flag = flash12_read_cmd_data( ctx, FLASH12_CMD_READ_STATUS_2, status, 1 );
    }
    return err_flag;
}

err_t flash12_write_status ( flash12_t *ctx, uint8_t status )
{
    err_t err_flag = flash12_write_enable ( ctx );
    err_flag |= flash12_write_cmd_data( ctx, FLASH12_CMD_WRITE_STATUS_1, &status, 1 );
    err_flag |= flash12_write_disable ( ctx );
    return err_flag;
}

err_t flash12_erase_memory ( flash12_t *ctx, uint8_t erase_cmd, uint32_t mem_addr )
{
    err_t err_flag = FLASH12_OK;
    if ( (  FLASH12_MAX_ADDRESS < mem_addr ) || 
         ( ( FLASH12_CMD_BLOCK_ERASE_4KB != erase_cmd ) && 
           ( FLASH12_CMD_BLOCK_ERASE_32KB != erase_cmd ) && 
           ( FLASH12_CMD_BLOCK_ERASE_64KB != erase_cmd ) && 
           ( FLASH12_CMD_CHIP_ERASE != erase_cmd ) ) )
    {
        err_flag = FLASH12_ERROR;
    }
    else
    {
        err_flag = flash12_write_enable( ctx );
        if ( FLASH12_CMD_CHIP_ERASE == erase_cmd )
        {
            err_flag |= flash12_write_cmd ( ctx, erase_cmd );
        }
        else
        {
            uint8_t data_buf[ 3 ] = { 0 };
            data_buf[ 0 ] = ( uint8_t ) ( mem_addr >> 16 );
            data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 8 );
            data_buf[ 2 ] = ( uint8_t )   mem_addr;
            err_flag |= flash12_write_cmd_data( ctx, erase_cmd, data_buf, 3 );
        }
        uint8_t status = DUMMY;
        do 
        {
            Delay_100ms( );
            err_flag |= flash12_read_status( ctx, FLASH12_CMD_READ_STATUS_1, &status );
        }
        while ( status & FLASH12_STATUS1_BSY );
    }
    return err_flag;
}

err_t flash12_get_device_id ( flash12_t *ctx, uint8_t *mfr_id, uint8_t *dev_id )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = flash12_read_cmd_address_data( ctx, FLASH12_CMD_MANUFACTURER_ID, DUMMY, data_buf, 2 );
    *mfr_id = data_buf[ 0 ];
    *dev_id = data_buf[ 1 ];
    return err_flag;
}

// ------------------------------------------------------------------------- END
