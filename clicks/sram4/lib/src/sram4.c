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
 * @file sram4.c
 * @brief SRAM 4 Click Driver.
 */

#include "sram4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Check if memory is busy.
 * @details Reads status register value and returns RDY bit 
 * that indicates if memory access is busy(STORE or RECALL
 * cycle in progress) or it's free.
 * @param[in] ctx : Click context object.
 * See #sram4_t object definition for detailed explanation.
 * @return @li @c  0 - Free,
 *         @li @c  1 - Busy.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t sram4_check_busy ( sram4_t *ctx );

void sram4_cfg_setup ( sram4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->hold = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t sram4_init ( sram4_t *ctx, sram4_cfg_t *cfg ) 
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

    digital_out_init( &ctx->hold, cfg->hold );

    return SPI_MASTER_SUCCESS;
}

err_t sram4_default_cfg ( sram4_t *ctx ) 
{
    digital_out_high( &ctx->hold );


    uint8_t temp_id[ 4 ] = { 0 };
    uint8_t id_reg = SRAM4_REG_RDID;
    err_t ret_val = sram4_generic_write_then_read( ctx, &id_reg, 1, temp_id, 4 );

    ctx->device_id = ( ( uint32_t )temp_id[ 0 ] << 24 ) | 
                     ( ( uint32_t )temp_id[ 1 ] << 16 ) | 
                     ( ( uint32_t )temp_id[ 2 ] << 8 ) | 
                     ( ( uint32_t )temp_id[ 3 ] );

    if ( SRAM4_DEVICE_ID != ctx->device_id )
    {
        ret_val = SRAM4_ERROR;
    }
    else
    {
        uint8_t status_val = 0x82;/*< Disable memory protection and set write enable bit*/
        ret_val |= sram4_generic_write( ctx, SRAM4_REG_RDSR, &status_val, 1 );
    }

    return ret_val;
}

err_t sram4_generic_command ( sram4_t *ctx, uint8_t cmd )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &cmd, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t sram4_generic_write ( sram4_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &reg, 1 );
    error_flag |= spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t sram4_generic_read ( sram4_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    uint8_t tx_data[ 2 ] = { 0 };
    uint8_t tx_len = 1;
    tx_data[ 0 ] = reg;
    
    if ( ( SRAM4_REG_FAST_RDSR == reg ) || ( SRAM4_REG_FAST_RDSN == reg ) || ( SRAM4_REG_FAST_RDID == reg ) )
    {
        tx_len++;//Send dummy byte
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, tx_data, tx_len, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t sram4_generic_write_then_read ( sram4_t *ctx, uint8_t *data_in, uint8_t in_len, uint8_t *data_out, uint8_t out_len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_in, in_len, data_out, out_len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t sram4_memory_write ( sram4_t *ctx, uint16_t memory_adr, uint8_t *write_data, uint8_t write_len )
{
    uint8_t tx_data[ 3 ] = { 0 };
    tx_data[ 0 ] = SRAM4_REG_WRITE;
    tx_data[ 1 ] = memory_adr >> 8;
    tx_data[ 2 ] = memory_adr;
    
    while ( sram4_check_busy( ctx ) );
    
    err_t ret_val = sram4_generic_command( ctx, SRAM4_REG_WREN );
    
    spi_master_select_device( ctx->chip_select );
    ret_val |= spi_master_write( &ctx->spi, tx_data, 3 );
    ret_val |= spi_master_write( &ctx->spi, write_data, write_len );
    spi_master_deselect_device( ctx->chip_select );
    
    return ret_val;
}

err_t sram4_memory_read ( sram4_t *ctx, uint16_t memory_adr, uint8_t *read_data, uint8_t read_len )
{
    uint8_t tx_data[ 3 ] = { 0 };
    tx_data[ 0 ] = SRAM4_REG_READ;
    tx_data[ 1 ] = memory_adr >> 8;
    tx_data[ 2 ] = memory_adr;
    
    while ( sram4_check_busy( ctx ) );
    
    return sram4_generic_write_then_read( ctx, tx_data, 3, read_data, read_len );
}

void sram4_set_hold ( sram4_t *ctx, uint8_t state )
{
    if ( state )
    {
        digital_out_high( &ctx->hold );
    }
    else
    {
        digital_out_low( &ctx->hold );
    }
}

static err_t sram4_check_busy ( sram4_t *ctx )
{
    uint8_t status_data;
    sram4_generic_read( ctx, SRAM4_REG_RDSR, &status_data, 1 );
    status_data &= 1;
    
    return status_data;
}

// ------------------------------------------------------------------------- END
