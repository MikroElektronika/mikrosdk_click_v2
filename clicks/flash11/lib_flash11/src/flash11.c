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
 * @file flash11.c
 * @brief Flash 11 Click Driver.
 */

#include "flash11.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash11_cfg_setup ( flash11_cfg_t *cfg ) 
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

err_t flash11_init ( flash11_t *ctx, flash11_cfg_t *cfg ) 
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

err_t flash11_default_cfg ( flash11_t *ctx ) 
{
    flash11_hw_write_protect( ctx, FLASH11_WRITE_PROTECT_DISABLE );
    Delay_10ms( );
    
    flash11_en_hold( ctx, FLASH11_HOLD_DISABLE );
    Delay_10ms( );
    
    uint8_t device_id = DUMMY;
    err_t err_flag = flash11_get_device_id( ctx, &device_id );
    if ( FLASH11_MANUFACTURER_ID != device_id )
    {
        err_flag = FLASH11_ERROR;
    }
    return err_flag;
}

err_t flash11_generic_write ( flash11_t *ctx, uint8_t opcode, uint8_t *data_in, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &opcode, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t flash11_generic_read ( flash11_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t flash11_set_cmd ( flash11_t *ctx, uint8_t opcode )
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t flash11_write_cmd_addr_data ( flash11_t *ctx, uint8_t opcode, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    err_t err_flag = FLASH11_ERROR;
    if ( FLASH11_MAX_ADDRESS >= ( mem_addr + len ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = opcode;
        data_buf[ 1 ] = ( uint8_t ) (  mem_addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) (  mem_addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )    mem_addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write( &ctx->spi, data_buf, 4 );
        err_flag |= spi_master_write( &ctx->spi, data_in, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash11_read_cmd_addr_data ( flash11_t *ctx, uint8_t opcode, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    err_t err_flag = FLASH11_ERROR;
    if ( FLASH11_MAX_ADDRESS >= ( mem_addr + len ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = opcode;
        data_buf[ 1 ] = ( uint8_t ) (  mem_addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) (  mem_addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )    mem_addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t flash11_sw_reset ( flash11_t *ctx )
{
    err_t err_flag = flash11_set_cmd( ctx, FLASH11_CMD_ENABLE_RESET );
    err_flag |= flash11_set_cmd( ctx, FLASH11_CMD_RESET_DEVICE );
    return err_flag;
}
err_t flash11_memory_write ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint32_t len )
{
    err_t err_flag = FLASH11_ERROR;
    if ( FLASH11_PAGE_SIZE >= len )
    {
        err_flag = flash11_write_enable( ctx );
        err_flag |= flash11_write_cmd_addr_data( ctx, FLASH11_CMD_BYTE_PAGE_PROGRAM, mem_addr, data_in, len );
        err_flag |= flash11_write_disable( ctx );
    }
    return err_flag;
}

err_t flash11_memory_read ( flash11_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint32_t len )
{
    return flash11_read_cmd_addr_data( ctx, FLASH11_CMD_READ_ARRAY, mem_addr, data_out, len );
}

err_t flash11_write_enable ( flash11_t *ctx )
{
    uint8_t status = DUMMY;
    flash11_hw_write_protect( ctx, FLASH11_WRITE_PROTECT_DISABLE );
    err_t err_flag = flash11_set_cmd( ctx, FLASH11_CMD_WRITE_ENABLE );
    err_flag |= flash11_get_status( ctx, FLASH11_CMD_READ_STATUS_1, &status );
    status &= FLASH11_STATUS1_WEL_EN;
    if ( status == FLASH11_STATUS1_WEL_DIS )
    {
        err_flag = FLASH11_ERROR;
    }
    return err_flag;
}

err_t flash11_write_disable ( flash11_t *ctx )
{
    uint8_t status = DUMMY;
    flash11_hw_write_protect( ctx, FLASH11_WRITE_PROTECT_ENABLE );
    err_t err_flag = flash11_set_cmd( ctx, FLASH11_CMD_WRITE_DISABLE );
    err_flag |= flash11_get_status( ctx, FLASH11_CMD_READ_STATUS_1, &status );
    status &= FLASH11_STATUS1_WEL_EN;
    if ( status != FLASH11_STATUS1_WEL_EN )
    {
        err_flag = FLASH11_ERROR;
    }
    return err_flag;
}

err_t flash11_block_erase ( flash11_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr )
{
    err_t err_flag = FLASH11_ERROR;
    if ( ( FLASH11_CMD_BLOCK_ERASE_4KB  == cmd_block_erase ) || 
         ( FLASH11_CMD_BLOCK_ERASE_32KB == cmd_block_erase ) || 
         ( FLASH11_CMD_BLOCK_ERASE_64KB == cmd_block_erase ) )
    {
        uint8_t data_buf[ 3 ] = { 0 };
        uint8_t status = DUMMY;
        err_flag = flash11_write_enable( ctx );
        
        data_buf[ 0 ] = ( uint8_t ) ( ( mem_addr >> 16 ) & 0xFF );
        data_buf[ 1 ] = ( uint8_t ) ( ( mem_addr >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( mem_addr & 0xFF );
        err_flag |= flash11_generic_write( ctx, cmd_block_erase, data_buf, 3 );
        do 
        {
            err_flag |= flash11_get_status( ctx, FLASH11_CMD_READ_STATUS_1, &status );
            Delay_10ms( );
        }
        while ( status & FLASH11_STATUS1_BSY );
    }
    return err_flag;
}

err_t flash11_chip_erase ( flash11_t *ctx )
{
    uint8_t status = DUMMY;
    err_t err_flag = flash11_write_enable( ctx );
    err_flag |= flash11_set_cmd( ctx, FLASH11_CMD_CHIP_ERASE );
    do 
    {
        err_flag |= flash11_get_status( ctx, FLASH11_CMD_READ_STATUS_1, &status );
        Delay_1sec( );
    }
    while ( status & FLASH11_STATUS1_BSY );
    return err_flag;
}

err_t flash11_set_status ( flash11_t *ctx, uint8_t status_reg, uint8_t status )
{
    err_t err_flag = flash11_write_enable( ctx );
    err_flag |= flash11_write_cmd_addr_data( ctx, status_reg, DUMMY, &status, 1 );
    err_flag |= flash11_write_disable( ctx );
    return err_flag;
}

err_t flash11_get_status ( flash11_t *ctx, uint8_t status_reg, uint8_t *status )
{
    return flash11_read_cmd_addr_data( ctx, status_reg, DUMMY, status, 1 );
}

err_t flash11_get_device_id ( flash11_t *ctx, uint8_t *device_id )
{
    return flash11_read_cmd_addr_data( ctx, FLASH11_CMD_MANUFACTURER_ID, DUMMY, device_id, 1 );
}

void flash11_hw_write_protect ( flash11_t *ctx, uint8_t en_wp )
{
    digital_out_write( &ctx->wp, en_wp );
}

void flash11_en_hold ( flash11_t *ctx, uint8_t en_hold )
{
    digital_out_write( &ctx->hld, en_hold );
}

// ------------------------------------------------------------------------- END
