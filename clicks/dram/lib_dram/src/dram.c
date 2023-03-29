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
 * @file dram.c
 * @brief DRAM Click Driver.
 */

#include "dram.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dram_cfg_setup ( dram_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->io3  = HAL_PIN_NC;
    cfg->io2  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dram_init ( dram_t *ctx, dram_cfg_t *cfg ) 
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

    digital_out_init( &ctx->io3, cfg->io3 );
    digital_out_init( &ctx->io2, cfg->io2 );

    digital_out_low ( &ctx->io3 );
    digital_out_low ( &ctx->io2 );
    
    return SPI_MASTER_SUCCESS;
}

err_t dram_memory_write ( dram_t *ctx, uint32_t address, uint8_t *data_in, uint32_t len )
{
    if ( ( NULL == data_in ) || ( ( address + len ) > DRAM_MAX_ADDRESS ) )
    {
        return DRAM_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = DRAM_CMD_WRITE;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_memory_read ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    if ( ( NULL == data_out ) || ( ( address + len ) > DRAM_MAX_ADDRESS ) )
    {
        return DRAM_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = DRAM_CMD_READ;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_memory_read_fast ( dram_t *ctx, uint32_t address, uint8_t *data_out, uint32_t len )
{
    if ( ( NULL == data_out ) || ( ( address + len ) > DRAM_MAX_ADDRESS ) )
    {
        return DRAM_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = DRAM_CMD_FAST_READ;
    data_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    data_buf[ 4 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 5 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_reset ( dram_t *ctx )
{
    uint8_t cmd = DRAM_CMD_RESET_ENABLE;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_1ms ( );
    cmd = DRAM_CMD_RESET;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_toggle_wrap_boundary ( dram_t *ctx )
{
    uint8_t cmd = DRAM_CMD_WRAP_BOUNDARY_TOGGLE;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_read_id ( dram_t *ctx, uint8_t *device_id )
{
    if ( NULL == device_id )
    {
        return DRAM_ERROR;
    }
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = DRAM_CMD_READ_ID;
    data_buf[ 1 ] = DUMMY;
    data_buf[ 2 ] = DUMMY;
    data_buf[ 3 ] = DUMMY;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    error_flag |= spi_master_read( &ctx->spi, device_id, 8 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t dram_check_communication ( dram_t *ctx )
{
    uint8_t device_id[ 8 ] = { 0 };
    if ( DRAM_OK == dram_read_id ( ctx, device_id ) )
    {
        if ( DRAM_MANUFACTURER_ID == device_id[ 0 ] )
        {
            return DRAM_OK;
        }
    }
    return DRAM_ERROR;
}

void dram_set_io3_pin ( dram_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->io3, state );
}

void dram_set_io2_pin ( dram_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->io2, state );
}

// ------------------------------------------------------------------------- END
