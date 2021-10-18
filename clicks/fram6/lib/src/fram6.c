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
 * @file fram6.c
 * @brief FRAM 6 Click Driver.
 */

#include "fram6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void fram6_cfg_setup ( fram6_cfg_t *cfg ) 
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

err_t fram6_init ( fram6_t *ctx, fram6_cfg_t *cfg ) 
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

err_t fram6_default_cfg ( fram6_t *ctx ) 
{
    fram6_set_hld_pin ( ctx, 1 );
    Delay_10ms( );
    
    if ( FRAM6_ERROR == fram6_check_communication ( ctx ) )
    {
        return FRAM6_ERROR;
    }
    
    err_t error_flag = fram6_write_status ( ctx, FRAM6_WPEN_BIT_MASK );
    return error_flag;
}

err_t fram6_write_opcode ( fram6_t *ctx, uint8_t opcode ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t fram6_read_opcode ( fram6_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t fram6_check_communication ( fram6_t *ctx ) 
{
    uint8_t rx_buf[ 9 ] = { 0 };
    uint8_t manufacturer_id[ 7 ] = { 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xC2 };
    uint8_t product_id[ 2 ] = { 0x25, 0xC8 };

    if ( FRAM6_OK == fram6_read_opcode ( ctx, FRAM6_OPCODE_RDID, rx_buf, 9 ) )
    {
        if ( ( 0 == memcmp( manufacturer_id, rx_buf, 7 ) ) && 
             ( 0 == memcmp( product_id, &rx_buf[ 7 ], 2 ) ) )
        {
            return FRAM6_OK;
        }
    }
    return FRAM6_ERROR;
}

void fram6_set_wp_pin ( fram6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wp, state );
}

void fram6_set_hld_pin ( fram6_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hld, state );
}

err_t fram6_enable_write ( fram6_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = fram6_write_opcode ( ctx, FRAM6_OPCODE_WREN );
    Delay_50us( );
    error_flag |= fram6_read_opcode ( ctx, FRAM6_OPCODE_RDSR, &status, 1 );
    
    if ( status & FRAM6_WEL_BIT_MASK )
    {
        return error_flag;
    }
    return FRAM6_ERROR;
}

err_t fram6_disable_write ( fram6_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = fram6_write_opcode ( ctx, FRAM6_OPCODE_WRDI );
    Delay_50us( );
    error_flag |= fram6_read_opcode ( ctx, FRAM6_OPCODE_RDSR, &status, 1 );
    
    if ( status & FRAM6_WEL_BIT_MASK )
    {
        return FRAM6_ERROR;
    }
    return error_flag;
}

err_t fram6_write_status ( fram6_t *ctx, uint8_t status )
{
    uint8_t tx_buf[ 2 ] = { FRAM6_OPCODE_WRDI, status };
    
    fram6_set_wp_pin ( ctx, 1 );
    err_t error_flag = fram6_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t fram6_read_status ( fram6_t *ctx, uint8_t *status )
{
    return fram6_read_opcode ( ctx, FRAM6_OPCODE_RDSR, status, 1 );
}

err_t fram6_set_block_protection ( fram6_t *ctx, uint8_t block_protect )
{
    uint8_t status = 0;
    err_t error_flag = fram6_read_status ( ctx, &status );
    status = ( status & ~FRAM6_BLOCK_PROTECT_BITS_MASK ) | ( block_protect & FRAM6_BLOCK_PROTECT_BITS_MASK );
    error_flag |= fram6_write_status ( ctx, status );
    return error_flag;
}

err_t fram6_enter_sleep_mode ( fram6_t *ctx )
{
    return fram6_write_opcode ( ctx, FRAM6_OPCODE_SLEEP );
}

void fram6_wakeup_from_sleep ( fram6_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
}

err_t fram6_memory_write ( fram6_t *ctx, uint32_t address, uint8_t *data_in, uint16_t len )
{
    uint8_t tx_buf[ 4 ] = { 0 };
    
    address &= FRAM6_MAX_ADDRESS;
    
    tx_buf[ 0 ] = FRAM6_OPCODE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    
    err_t error_flag = fram6_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 4 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t fram6_memory_read ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 4 ] = { 0 };
    
    address &= FRAM6_MAX_ADDRESS;
    
    tx_buf[ 0 ] = FRAM6_OPCODE_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 4, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t fram6_memory_read_fast ( fram6_t *ctx, uint32_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 5 ] = { 0 };
    
    address &= FRAM6_MAX_ADDRESS;
    
    tx_buf[ 0 ] = FRAM6_OPCODE_FSTRD;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 16 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 3 ] = ( uint8_t ) ( address & 0xFF );
    tx_buf[ 4 ] = DUMMY;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 5, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

// ------------------------------------------------------------------------- END
