/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file flash15.c
 * @brief Flash 15 Click Driver.
 */

#include "flash15.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void flash15_cfg_setup ( flash15_cfg_t *cfg ) 
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

err_t flash15_init ( flash15_t *ctx, flash15_cfg_t *cfg ) 
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

err_t flash15_write_cmd ( flash15_t *ctx, uint8_t cmd )
{
    err_t error_flag = FLASH15_OK;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash15_write_cmd_data ( flash15_t *ctx, uint8_t cmd, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = FLASH15_OK;
    if ( NULL == data_in )
    {
        return FLASH15_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash15_read_cmd_data ( flash15_t *ctx, uint8_t cmd, uint8_t *data_out, uint8_t len )
{
    err_t error_flag = FLASH15_OK;
    if ( NULL == data_out )
    {
        return FLASH15_ERROR;
    }
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, &cmd, 1 );
    error_flag |= spi_master_read( &ctx->spi, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash15_get_feature ( flash15_t *ctx, uint8_t reg, uint8_t *data_out )
{
    err_t error_flag = FLASH15_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( NULL == data_out )
    {
        return FLASH15_ERROR;
    }
    data_buf[ 0 ] = FLASH15_CMD_GET_FEATURE;
    data_buf[ 1 ] = reg;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    error_flag |= spi_master_read( &ctx->spi, data_out, 1 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash15_set_feature ( flash15_t *ctx, uint8_t reg, uint8_t data_in )
{
    err_t error_flag = FLASH15_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = FLASH15_CMD_SET_FEATURE;
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = data_in;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    Delay_10ms ( );
    return error_flag;
}

err_t flash15_memory_write ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_in, uint16_t len )
{
    err_t error_flag = FLASH15_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t status = 0;
    if ( ( NULL == data_in ) || ( page > FLASH15_PAGE_ADDRESS_MAX ) || 
         ( ( column + len - 1 ) > ( FLASH15_COLUMN_ADDRESS_MAX + 64 ) ) )
    {
        return FLASH15_ERROR;
    }

    data_buf[ 0 ] = FLASH15_CMD_PROGRAM_DATA_LOAD;
    data_buf[ 1 ] = ( uint8_t ) ( ( column >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( column & 0xFF );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    error_flag |= flash15_write_enable ( ctx );
    data_buf[ 0 ] = DUMMY;
    data_buf[ 1 ] = ( uint8_t ) ( ( page >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( page & 0xFF );
    error_flag |= flash15_write_cmd_data ( ctx, FLASH15_CMD_PROGRAM_EXECUTE, data_buf, 3 );
    do 
    {
        Delay_100ms ( );
        error_flag |= flash15_get_feature ( ctx, FLASH15_REG_STATUS, &status );
    }
    while ( ( FLASH15_OK == error_flag ) && ( FLASH15_STATUS_OIP == ( status & FLASH15_STATUS_OIP ) ) );
    
    error_flag |= flash15_write_protect ( ctx );
    return error_flag;
}

err_t flash15_memory_read ( flash15_t *ctx, uint16_t page, uint16_t column, uint8_t *data_out, uint16_t len )
{
    err_t error_flag = FLASH15_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    uint8_t status = 0;
    if ( ( NULL == data_out ) || ( page > FLASH15_PAGE_ADDRESS_MAX ) || 
         ( ( column + len - 1 ) > ( FLASH15_COLUMN_ADDRESS_MAX + 64 ) ) )
    {
        return FLASH15_ERROR;
    }
    data_buf[ 0 ] = DUMMY;
    data_buf[ 1 ] = ( uint8_t ) ( ( page >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( page & 0xFF );
    error_flag |= flash15_write_cmd_data ( ctx, FLASH15_CMD_PAGE_READ, data_buf, 3 );
    do 
    {
        Delay_100ms ( );
        error_flag |= flash15_get_feature ( ctx, FLASH15_REG_STATUS, &status );
    }
    while ( ( FLASH15_OK == error_flag ) && ( FLASH15_STATUS_OIP == ( status & FLASH15_STATUS_OIP ) ) );
    
    if ( FLASH15_OK == error_flag )
    {
        data_buf[ 0 ] = FLASH15_CMD_READ_FROM_CACHE;
        data_buf[ 1 ] = ( uint8_t ) ( ( column >> 8 ) & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( column & 0xFF );
        data_buf[ 3 ] = DUMMY;
        spi_master_select_device( ctx->chip_select );
        error_flag |= spi_master_write( &ctx->spi, data_buf, 4 );
        error_flag |= spi_master_read( &ctx->spi, data_out, len );
        spi_master_deselect_device( ctx->chip_select );
        Delay_10ms ( );
    }
    return error_flag;
}

err_t flash15_erase_memory ( flash15_t *ctx, uint16_t page )
{
    err_t error_flag = FLASH15_OK;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t status = 0;
    if ( page > FLASH15_PAGE_ADDRESS_MAX )
    {
        return FLASH15_ERROR;
    }
    data_buf[ 0 ] = DUMMY;
    data_buf[ 1 ] = ( uint8_t ) ( ( page >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( page & 0xFF );
    error_flag |= flash15_write_enable ( ctx );
    error_flag |= flash15_write_cmd_data ( ctx, FLASH15_CMD_BLOCK_ERASE, data_buf, 3 );
    do 
    {
        Delay_100ms ( );
        error_flag |= flash15_get_feature ( ctx, FLASH15_REG_STATUS, &status );
    }
    while ( ( FLASH15_OK == error_flag ) && ( FLASH15_STATUS_OIP == ( status & FLASH15_STATUS_OIP ) ) );
    
    error_flag |= flash15_write_protect ( ctx );
    return error_flag;
}

err_t flash15_check_communication ( flash15_t *ctx )
{
    uint8_t device_id[ 4 ] = { 0 };
    if ( FLASH15_OK == flash15_read_cmd_data( ctx, FLASH15_CMD_READ_JEDEC_ID, device_id, 4 ) )
    {
        if ( ( FLASH15_MANUFACTURER_ID == device_id[ 1 ] ) && 
             ( FLASH15_DEVICE_ID == device_id[ 2 ] ) && 
             ( FLASH15_DEVICE_ID == device_id[ 3 ] ) )
        {
            return FLASH15_OK;
        }
    }
    return FLASH15_ERROR;
}

err_t flash15_write_protect ( flash15_t *ctx )
{
    err_t error_flag = FLASH15_OK;
    uint8_t status = 0;
    digital_out_low ( &ctx->wp );
    error_flag |= flash15_write_cmd ( ctx, FLASH15_CMD_WRITE_DISABLE );
    error_flag |= flash15_get_feature ( ctx, FLASH15_REG_STATUS, &status );
    if ( ( FLASH15_OK == error_flag ) && ( FLASH15_STATUS_WEL != ( status & FLASH15_STATUS_WEL ) ) )
    {
        return FLASH15_OK;
    }
    return FLASH15_ERROR;
}

err_t flash15_write_enable ( flash15_t *ctx )
{
    err_t error_flag = FLASH15_OK;
    uint8_t status = 0;
    digital_out_high ( &ctx->wp );
    error_flag |= flash15_write_cmd ( ctx, FLASH15_CMD_WRITE_ENABLE );
    error_flag |= flash15_get_feature ( ctx, FLASH15_REG_STATUS, &status );
    if ( ( FLASH15_OK == error_flag ) && ( FLASH15_STATUS_WEL == ( status & FLASH15_STATUS_WEL ) ) )
    {
        return FLASH15_OK;
    }
    return FLASH15_ERROR;
}

err_t flash15_soft_reset ( flash15_t *ctx )
{
    return flash15_write_cmd ( ctx, FLASH15_CMD_SOFT_RESET );
}

void flash15_set_wp_pin ( flash15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void flash15_set_hold_pin ( flash15_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hold, state );
}

// ------------------------------------------------------------------------- END
