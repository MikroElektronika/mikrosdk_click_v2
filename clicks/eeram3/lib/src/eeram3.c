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
 * @file eeram3.c
 * @brief EERAM 3 Click Driver.
 */

#include "eeram3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief CCITT calculation for CRC16 function.
 * @details This function calculates CRC16 with parameteres: 
 * @li @c  Width 16 bit
 * @li @c  Polynomial 0x1021 ( x16 + x12 + x5 + x0 )
 * @li @c  Initialization 0xFFFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0xBF6D
 * @li @c  Example "123456789" - 0x96DC
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint16_t eeram3_calculate_crc16_ccitt ( uint8_t *data_buf, uint8_t len );

void eeram3_cfg_setup ( eeram3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hld  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t eeram3_init ( eeram3_t *ctx, eeram3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hld, cfg->hld );

    return SPI_MASTER_SUCCESS;
}

void eeram3_default_cfg ( eeram3_t *ctx ) 
{
    eeram3_set_hld_pin ( ctx, 1 );
    Delay_10ms( );
}

err_t eeram3_write_opcode ( eeram3_t *ctx, uint8_t opcode ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &opcode, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeram3_read_opcode ( eeram3_t *ctx, uint8_t opcode, uint8_t *data_out, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &opcode, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void eeram3_set_hld_pin ( eeram3_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->hld, state );
}

err_t eeram3_enable_write ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_write_opcode ( ctx, EERAM3_OPCODE_WREN );
    Delay_50us( );
    error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
    
    if ( status & EERAM3_WEL_BIT_MASK )
    {
        return error_flag;
    }
    return EERAM3_ERROR;
}

err_t eeram3_disable_write ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_write_opcode ( ctx, EERAM3_OPCODE_WRDI );
    Delay_50us( );
    error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
    
    if ( status & EERAM3_WEL_BIT_MASK )
    {
        return EERAM3_ERROR;
    }
    return error_flag;
}

err_t eeram3_write_status ( eeram3_t *ctx, uint8_t status )
{
    uint8_t tx_buf[ 2 ] = { EERAM3_OPCODE_WRDI, status };
    
    err_t error_flag = eeram3_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeram3_read_status ( eeram3_t *ctx, uint8_t *status )
{
    return eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, status, 1 );
}

err_t eeram3_set_block_protection ( eeram3_t *ctx, uint8_t block_protect )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_read_status ( ctx, &status );
    status = ( status & ~EERAM3_BLOCK_PROTECT_BITS_MASK ) | ( block_protect & EERAM3_BLOCK_PROTECT_BITS_MASK );
    error_flag |= eeram3_write_status ( ctx, status );
    return error_flag;
}

err_t eeram3_enter_hibernate_mode ( eeram3_t *ctx )
{
    return eeram3_write_opcode ( ctx, EERAM3_OPCODE_HIBERNATE );
}

void eeram3_wakeup_from_hibernate ( eeram3_t *ctx )
{
    spi_master_select_device( ctx->chip_select );
    Delay_1ms( );
    spi_master_deselect_device( ctx->chip_select );
}

err_t eeram3_memory_write ( eeram3_t *ctx, uint16_t address, uint8_t *data_in, uint16_t len )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    
    address &= EERAM3_MAX_ADDRESS;
    
    tx_buf[ 0 ] = EERAM3_OPCODE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    err_t error_flag = eeram3_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 3 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeram3_memory_read ( eeram3_t *ctx, uint16_t address, uint8_t *data_out, uint16_t len )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    
    address &= EERAM3_MAX_ADDRESS;
    
    tx_buf[ 0 ] = EERAM3_OPCODE_READ;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 3, data_out, len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeram3_memory_secure_write ( eeram3_t *ctx, uint16_t address, uint8_t *data_in, uint8_t len )
{
    uint8_t tx_buf[ 69 ] = { 0 };
    uint16_t crc = 0;
    uint8_t status = 0;
    
    if ( ( address & EERAM3_MAX_PAGE_ADDRESS ) || len > EERAM3_MAX_PAGE_ADDRESS )
    {
        return EERAM3_ERROR;
    }
    
    address &= EERAM3_MAX_ADDRESS;
    tx_buf[ 0 ] = EERAM3_OPCODE_SECURE_WRITE;
    tx_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    err_t error_flag = eeram3_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    memcpy ( &tx_buf[ 3 ], data_in, len );
    crc = eeram3_calculate_crc16_ccitt ( &tx_buf[ 1 ], 66 );
    tx_buf[ 67 ] = ( uint8_t ) ( ( crc >> 8 ) & 0xFF );
    tx_buf[ 68 ] = ( uint8_t ) ( crc & 0xFF );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 69 );
    spi_master_deselect_device( ctx->chip_select );
    
    error_flag |= eeram3_read_status ( ctx, &status );
    if ( EERAM3_SWM_BIT_MASK & status )
    {
        return EERAM3_ERROR;
    }
    
    return error_flag;
}

err_t eeram3_memory_secure_read ( eeram3_t *ctx, uint16_t address, uint8_t *data_out, uint8_t len )
{
    uint8_t tr_buf[ 69 ] = { 0 };
    uint16_t crc = 0;
    
    if ( ( address & EERAM3_MAX_PAGE_ADDRESS ) || len > EERAM3_MAX_PAGE_ADDRESS )
    {
        return EERAM3_ERROR;
    }
    
    address &= EERAM3_MAX_ADDRESS;
    tr_buf[ 0 ] = EERAM3_OPCODE_SECURE_READ;
    tr_buf[ 1 ] = ( uint8_t ) ( ( address >> 8 ) & 0xFF );
    tr_buf[ 2 ] = ( uint8_t ) ( address & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tr_buf, 3 );
    error_flag |= spi_master_read( &ctx->spi, &tr_buf[ 3 ], 66 );
    spi_master_deselect_device( ctx->chip_select );
    crc = ( uint16_t ) ( ( ( uint16_t ) tr_buf[ 67 ] << 8 ) | tr_buf[ 68 ] );
    if ( eeram3_calculate_crc16_ccitt ( &tr_buf[ 1 ], 66 ) != crc )
    {
        return EERAM3_ERROR;
    }
    memcpy ( data_out, &tr_buf[ 3 ], len );
    return error_flag;
}

err_t eeram3_read_last_written_address ( eeram3_t *ctx, uint16_t *address )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = eeram3_read_opcode( ctx, EERAM3_OPCODE_RDLSWA, rx_buf, 2 );
    *address = ( uint16_t ) ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] );
    return error_flag;
}

err_t eeram3_nv_user_space_write ( eeram3_t *ctx, uint16_t data_in )
{
    uint8_t tx_buf[ 3 ] = { 0 };
    
    tx_buf[ 0 ] = EERAM3_OPCODE_WRNUR;
    tx_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    
    err_t error_flag = eeram3_enable_write ( ctx );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t eeram3_nv_user_space_read ( eeram3_t *ctx, uint16_t *data_out )
{
    uint8_t rx_buf[ 2 ] = { 0 };
    err_t error_flag = eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDNUR, rx_buf, 2 );
    *data_out = ( uint16_t ) ( ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ] );
    return error_flag;
}

err_t eeram3_store_data ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_enable_write ( ctx );
    error_flag |= eeram3_write_opcode ( ctx, EERAM3_OPCODE_STORE );
    Delay_50us( );
    error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
    
    while ( EERAM3_RDY_BIT_MASK == ( status & EERAM3_RDY_BIT_MASK ) )
    {
        error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
        Delay_50us( );
    }
    return error_flag;
}

err_t eeram3_recall_data ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_enable_write ( ctx );
    error_flag |= eeram3_write_opcode ( ctx, EERAM3_OPCODE_RECALL );
    Delay_50us( );
    error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
    
    while ( EERAM3_RDY_BIT_MASK == ( status & EERAM3_RDY_BIT_MASK ) )
    {
        error_flag |= eeram3_read_opcode ( ctx, EERAM3_OPCODE_RDSR, &status, 1 );
        Delay_50us( );
    }
    return error_flag;
}

err_t eeram3_autostore_enable ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_read_status ( ctx, &status );
    
    if ( EERAM3_ASE_BIT_MASK == ( status & EERAM3_ASE_BIT_MASK ) )
    {
        status &= ~EERAM3_ASE_BIT_MASK;
        error_flag |= eeram3_write_status ( ctx, status );
    }
    return error_flag;
}

err_t eeram3_autostore_disable ( eeram3_t *ctx )
{
    uint8_t status = 0;
    err_t error_flag = eeram3_read_status ( ctx, &status );
    
    if ( EERAM3_ASE_BIT_MASK != ( status & EERAM3_ASE_BIT_MASK ) )
    {
        status |= EERAM3_ASE_BIT_MASK;
        error_flag |= eeram3_write_status ( ctx, status );
    }
    return error_flag;
}

static uint16_t eeram3_calculate_crc16_ccitt ( uint8_t *data_buf, uint8_t len )
{
    uint16_t crc16 = 0xFFFF;

    for ( uint8_t cnt = 0; cnt < len; ++cnt )
    {
        crc16 ^= ( data_buf[ cnt ] << 8 );

        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc16 & 0x8000 )
            {
                crc16 = ( crc16 << 1 ) ^ 0x1021;
            }
            else
            {
                crc16 <<= 1;
            }
        }
    }
    return crc16 ^ 0xBF6D;
}

// ------------------------------------------------------------------------- END
