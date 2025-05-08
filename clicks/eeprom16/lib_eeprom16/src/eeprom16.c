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
 * @file eeprom16.c
 * @brief EEPROM 16 Click Driver.
 */

#include "eeprom16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void eeprom16_cfg_setup ( eeprom16_cfg_t *cfg ) 
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

err_t eeprom16_init ( eeprom16_t *ctx, eeprom16_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

err_t eeprom16_default_cfg ( eeprom16_t *ctx ) 
{
    err_t error_flag = EEPROM16_OK;
    eeprom16_set_hold_pin ( ctx, 1 );
    Delay_10ms( );
    return eeprom16_write_status ( ctx, EEPROM16_STATUS_WPEN_MASK );
}

err_t eeprom16_write_opcode ( eeprom16_t *ctx, uint8_t opcode ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeprom16_read_opcode ( eeprom16_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void eeprom16_set_wp_pin ( eeprom16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void eeprom16_set_hold_pin ( eeprom16_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hold, state );
}

err_t eeprom16_enable_write ( eeprom16_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeprom16_write_opcode ( ctx, EEPROM16_OPCODE_WREN );
    Delay_50us( );
    error_flag |= eeprom16_read_opcode ( ctx, EEPROM16_OPCODE_RDSR, &status, 1 );
    
    if ( status & EEPROM16_STATUS_WEL_MASK )
    {
        return error_flag;
    }
    return EEPROM16_ERROR;
}

err_t eeprom16_disable_write ( eeprom16_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeprom16_write_opcode ( ctx, EEPROM16_OPCODE_WRDI );
    Delay_50us( );
    error_flag |= eeprom16_read_opcode ( ctx, EEPROM16_OPCODE_RDSR, &status, 1 );
    
    if ( status & EEPROM16_STATUS_WEL_MASK )
    {
        return EEPROM16_ERROR;
    }
    return error_flag;
}

err_t eeprom16_write_status ( eeprom16_t *ctx, uint8_t status )
{
    uint8_t tx_buf[ 2 ] = { EEPROM16_OPCODE_WRDI, status };
    
    eeprom16_set_wp_pin ( ctx, 1 );
    err_t error_flag = eeprom16_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeprom16_read_status ( eeprom16_t *ctx, uint8_t *status )
{
    return eeprom16_read_opcode ( ctx, EEPROM16_OPCODE_RDSR, status, 1 );
}

err_t eeprom16_set_block_protection ( eeprom16_t *ctx, uint8_t block_protect )
{
    uint8_t status = 0;
    err_t error_flag = eeprom16_read_status ( ctx, &status );
    status = ( status & ~EEPROM16_STATUS_BLOCK_PROTECT_MASK ) | ( block_protect & EEPROM16_STATUS_BLOCK_PROTECT_MASK );
    error_flag |= eeprom16_write_status ( ctx, status );
    return error_flag;
}

err_t eeprom16_memory_write ( eeprom16_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len )
{
    err_t error_flag = EEPROM16_OK;
    uint8_t status = 0;
    uint8_t tx_buf[ 3 ] = { 0 };
    if ( ( NULL == data_in ) || 
         ( ( ( address & EEPROM16_PAGE_MASK ) + len ) > EEPROM16_PAGE_SIZE ) || 
         ( address > EEPROM16_MAX_ADDRESS ) )
    {
        return EEPROM16_ERROR;
    }
    
    tx_buf[ 0 ] = EEPROM16_OPCODE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    error_flag |= eeprom16_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 3 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    do
    {
        error_flag |= eeprom16_read_status ( ctx, &status );
    }
    while ( ( EEPROM16_OK == error_flag ) && ( status & EEPROM16_STATUS_RDY_MASK ) );
    return error_flag;
}

err_t eeprom16_memory_read ( eeprom16_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    if ( ( NULL == data_out ) || 
         ( ( address + len ) > ( EEPROM16_MAX_ADDRESS + 1 ) ) )
    {
        return EEPROM16_ERROR;
    }
    
    tx_buf[ 0 ] = EEPROM16_OPCODE_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 3, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------- END
