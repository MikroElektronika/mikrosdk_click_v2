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
 * @file mram4.c
 * @brief MRAM 4 Click Driver.
 */

#include "mram4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void mram4_cfg_setup ( mram4_cfg_t *cfg ) 
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

err_t mram4_init ( mram4_t *ctx, mram4_cfg_t *cfg ) 
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

err_t mram4_default_cfg ( mram4_t *ctx ) 
{
    err_t err_flag = MRAM4_OK;
    mram4_hw_write_protect( ctx, MRAM4_WRITE_PROTECT_DISABLE );
    mram4_set_hold( ctx, MRAM4_HOLD_DISABLE );
    Delay_100ms( );

    err_flag = mram4_write_enable( ctx );
    Delay_100ms( );

    return err_flag;
}

err_t mram4_generic_write ( mram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, &reg, 1 );
    err_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t mram4_generic_read ( mram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t mram4_write_cmd_addr_data ( mram4_t *ctx, uint8_t cmd, uint32_t addr, uint8_t *data_in, uint32_t len )
{
    err_t err_flag = MRAM4_ERROR;
    if ( MRAM4_MEMORY_ADDRESS_MAX >= ( addr + len - 1 ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = ( uint8_t ) (  addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) (  addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )    addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write( &ctx->spi, data_buf, 4 );
        err_flag |= spi_master_write( &ctx->spi, data_in, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t mram4_read_cmd_addr_data ( mram4_t *ctx, uint8_t cmd, uint32_t addr, uint8_t *data_out, uint32_t len )
{
    err_t err_flag = MRAM4_ERROR;
    if ( MRAM4_MEMORY_ADDRESS_MAX >= ( addr + len - 1 ) )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = cmd;
        data_buf[ 1 ] = ( uint8_t ) (  addr >> 16 );
        data_buf[ 2 ] = ( uint8_t ) (  addr >> 8 );
        data_buf[ 3 ] = ( uint8_t )    addr;
        spi_master_select_device( ctx->chip_select );
        err_flag = spi_master_write_then_read( &ctx->spi, data_buf, 4, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
    }
    return err_flag;
}

err_t mram4_memory_write ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_in, uint8_t len ) 
{    
    err_t err_flag = MRAM4_OK;
    if ( MRAM4_PAGE_SIZE >= len )
    {
        err_flag |= mram4_write_cmd_addr_data( ctx, MRAM4_CMD_WRITE_PR_PAGE, mem_addr, data_in, len );
    }
    else
    {
        err_flag = MRAM4_ERROR;
    }
    return err_flag;
}

err_t mram4_memory_read ( mram4_t *ctx, uint32_t mem_addr, uint8_t *data_out, uint8_t len ) 
{
    return mram4_read_cmd_addr_data( ctx, MRAM4_CMD_READ, mem_addr, data_out, len );
}

err_t mram4_memory_reset ( mram4_t *ctx )
{
    err_t err_flag = mram4_set_command( ctx, MRAM4_CMD_RESET_ENABLE );
    Delay_1ms( );
    err_flag |= mram4_set_command( ctx, MRAM4_CMD_RESET_MEMORY );
    Delay_100ms( );
    return err_flag;
}

err_t mram4_set_command ( mram4_t *ctx, uint8_t cmd ) 
{
    spi_master_select_device( ctx->chip_select ); 
    err_t err_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t mram4_write_enable ( mram4_t *ctx )
{
    uint8_t status = DUMMY;
    mram4_hw_write_protect( ctx, MRAM4_WRITE_PROTECT_DISABLE );
    err_t err_flag = mram4_set_command( ctx, MRAM4_CMD_WRITE_ENABLE );
    err_flag |= mram4_get_status( ctx, &status );
    status &= MRAM4_STATUS_WEL_BIT_MASK;
    if ( status == MRAM4_STATUS_WEL_CLR )
    {
        err_flag = MRAM4_ERROR;
    }
    return err_flag;
}

err_t mram4_write_disable ( mram4_t *ctx )
{
    uint8_t status = DUMMY;
    mram4_hw_write_protect( ctx, MRAM4_WRITE_PROTECT_ENABLE );
    err_t err_flag = mram4_set_command( ctx, MRAM4_CMD_WRITE_DISABLE );
    err_flag |= mram4_get_status( ctx, &status );
    status &= MRAM4_STATUS_WEL_BIT_MASK;
    if ( status == MRAM4_STATUS_WEL_SET )
    {
        err_flag = MRAM4_ERROR;
    }
    return err_flag;
}

err_t mram4_block_erase ( mram4_t *ctx, uint8_t cmd_block_erase, uint32_t mem_addr )
{
    err_t err_flag = MRAM4_ERROR;
    if ( ( MRAM4_CMD_ERASE_4KB  == cmd_block_erase ) || 
         ( MRAM4_CMD_ERASE_32KB == cmd_block_erase ) || 
         ( MRAM4_CMD_ERASE_SECTOR == cmd_block_erase ) )
    {
        uint8_t data_buf[ 3 ] = { 0 };
        uint8_t status = DUMMY;
        err_flag = mram4_write_enable( ctx );
        
        data_buf[ 0 ] = ( uint8_t ) ( mem_addr >> 16 );
        data_buf[ 1 ] = ( uint8_t ) ( mem_addr >> 8 );
        data_buf[ 2 ] = ( uint8_t )   mem_addr;
        err_flag |= mram4_generic_write( ctx, cmd_block_erase, data_buf, 3 );
        do 
        {
            err_flag |= mram4_get_status( ctx, &status );
            Delay_10ms( );
        }
        while ( status & MRAM4_STATUS_WIP_BIT_MASK );
    }
    return err_flag;
}

err_t mram4_chip_erase ( mram4_t *ctx )
{
    uint8_t status = DUMMY;
    err_t err_flag = mram4_write_enable( ctx );
    err_flag |= mram4_set_command( ctx, MRAM4_CMD_ERASE_CHIP );
    do 
    {
        err_flag |= mram4_get_status( ctx, &status );
        Delay_1sec( );
    }
    while ( status & MRAM4_STATUS_WIP_BIT_MASK );
    return err_flag;
}

err_t mram4_set_status ( mram4_t *ctx, uint8_t st_reg, uint8_t status )
{
    err_t err_flag = mram4_write_enable( ctx );
    err_flag |= mram4_generic_write( ctx, st_reg, &status, 1 );
    err_flag |= mram4_write_disable( ctx );
    return err_flag;
}

err_t mram4_get_status ( mram4_t *ctx, uint8_t *status ) 
{    
    return mram4_generic_read( ctx, MRAM4_CMD_READ_STATUS_REG, status, 1 );
}

void mram4_hw_write_protect ( mram4_t *ctx, uint8_t en_wp )
{
    digital_out_write( &ctx->wp, en_wp );
}

void mram4_set_hold ( mram4_t *ctx, uint8_t en_hld )
{
    digital_out_write( &ctx->hld, en_hld );
}

// ------------------------------------------------------------------------- END
