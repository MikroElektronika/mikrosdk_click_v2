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
 * @file excelonultra.c
 * @brief Excelon-Ultra Click Driver.
 */

#include "excelonultra.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void excelonultra_cfg_setup ( excelonultra_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->wp = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t excelonultra_init ( excelonultra_t *ctx, excelonultra_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_init( &ctx->wp, cfg->wp );

    return SPI_MASTER_SUCCESS;
}

err_t excelonultra_default_cfg ( excelonultra_t *ctx ) 
{
    digital_out_high( &ctx->wp );
    digital_out_high( &ctx->rst );
    excelonultra_hw_reset( ctx );
    
    excelonultra_get_device_identification( ctx );
    excelonultra_send_cmd( ctx, EXCELONULTRA_CMD_WREN );
    uint8_t status[] = { EXCELONULTRA_CMD_RDSR1, 0x1E };//Enable writing in status register and clear memory protection
    excelonultra_generic_write( ctx, status, 2 );
    
    return EXCELONULTRA_OK;
}

err_t excelonultra_send_cmd ( excelonultra_t *ctx, uint8_t cmd ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t excelonultra_generic_transfer 
( excelonultra_t *ctx, uint8_t *data_in, uint32_t len_in, uint8_t *data_out, uint32_t len_out ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_in, len_in, data_out, len_out );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t excelonultra_generic_write ( excelonultra_t *ctx, uint8_t *data_in, uint32_t len_in )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, len_in );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t excelonultra_get_device_identification ( excelonultra_t *ctx )
{
    uint8_t temp_data[ 8 ] = { 0 };
    uint8_t write_data = 0;
    err_t error_flag = EXCELONULTRA_OK;
    
    //Device ID
    write_data = EXCELONULTRA_CMD_RDID;
    error_flag |= excelonultra_generic_transfer( ctx, &write_data, 1, temp_data, 8 );
    
    ctx->manufacturer_id = ( ( ( (uint16_t)temp_data[ 3 ] << 8 ) | temp_data[ 2 ] ) & 0xFFE0 ) >> 5;
    ctx->product_id = ( ( (uint16_t)temp_data[ 2 ] << 8 ) | temp_data[ 1 ] ) & 0x1FFF;
    ctx->density_id = ( temp_data[ 0 ] & 0xF8 ) >> 3;
    ctx->die_rev = temp_data[ 0 ] & 0x7;
    
    //Unique ID
    write_data = EXCELONULTRA_CMD_RUID;
    error_flag |= excelonultra_generic_transfer( ctx, &write_data, 1, ctx->unique_id, 8 );
    
    return error_flag;
}

err_t excelonultra_write_byte_to_memory ( excelonultra_t *ctx, uint32_t mem_adr, uint8_t mem_data )
{
    uint8_t write_data[ 5 ] = { 0 };
    err_t error_flag = EXCELONULTRA_OK;
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_WRITE;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    write_data[ 4 ] = mem_data;
    
    return excelonultra_generic_write( ctx, write_data, 5 );
}

err_t excelonultra_write_data_to_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len )
{
    uint8_t write_data[ 5 ] = { 0 };
    err_t error_flag = EXCELONULTRA_OK;
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_WRITE;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, write_data, 4 );
    error_flag |= spi_master_write( &ctx->spi, mem_data, mem_data_len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t excelonultra_read_byte_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data )
{
    uint8_t write_data[ 4 ] = { 0 };
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_READ;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    
    return excelonultra_generic_transfer( ctx, write_data, 4, mem_data, 1 );
}

err_t excelonultra_read_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint8_t *mem_data, uint32_t mem_data_len )
{
    uint8_t write_data[ 4 ] = { 0 };
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_READ;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    
    return excelonultra_generic_transfer( ctx, write_data, 4, mem_data, mem_data_len );
}

err_t excelonultra_clear_byte_from_memory ( excelonultra_t *ctx, uint32_t mem_adr )
{
    uint8_t write_data[ 5 ] = { 0 };
    err_t error_flag = EXCELONULTRA_OK;
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_WRITE;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    write_data[ 4 ] = 0xFF;
    
    return excelonultra_generic_write( ctx, write_data, 5 );
}

err_t excelonultra_clear_data_from_memory 
( excelonultra_t *ctx, uint32_t mem_adr, uint32_t mem_data_len )
{
    uint8_t write_data[ 5 ] = { 0 };
    err_t error_flag = EXCELONULTRA_OK;
    uint8_t dummy_write = 0xFF;
    
    if ( EXCELONULTRA_MAX_MEMORY_ADDRESS < mem_adr )
        return EXCELONULTRA_ERROR;
    
    write_data[ 0 ] = EXCELONULTRA_CMD_WRITE;
    write_data[ 1 ] = mem_adr >> 16;
    write_data[ 2 ] = mem_adr >> 8;
    write_data[ 3 ] = mem_adr;
    
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, write_data, 4 );
    for ( uint32_t cnt = 0; cnt < mem_data_len; cnt++ )
    {
        error_flag |= spi_master_write( &ctx->spi, &dummy_write, 1 );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void excelonultra_set_rst_pin ( excelonultra_t *ctx, uint8_t state )
{
    if (state)
    {
        digital_out_high( &ctx->rst );
    }
    else
    {
        digital_out_low( &ctx->rst );
    }
}

void excelonultra_set_wp_pin ( excelonultra_t *ctx, uint8_t state )
{
    if (state)
    {
        digital_out_high( &ctx->wp );
    }
    else
    {
        digital_out_low( &ctx->wp );
    }
}

void excelonultra_hw_reset ( excelonultra_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_1us( );
    digital_out_high( &ctx->rst );
    Delay_500us( );
    digital_out_low( &ctx->rst );
    Delay_1us( );
    digital_out_high( &ctx->rst );
    Delay_500us( );
}


// ------------------------------------------------------------------------- END
