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
 * @file digipot9.c
 * @brief DIGI POT 9 Click Driver.
 */

#include "digipot9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void digipot9_cfg_setup ( digipot9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pr   = HAL_PIN_NC;
    cfg->wp   = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t digipot9_init ( digipot9_t *ctx, digipot9_cfg_t *cfg ) 
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

    digital_out_init( &ctx->pr, cfg->pr );
    digital_out_init( &ctx->wp, cfg->wp );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

void digipot9_default_cfg ( digipot9_t *ctx ) 
{
    digital_out_high( &ctx->pr );
    digital_out_high( &ctx->wp );
}

err_t digipot9_generic_write ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t data_in ) 
{
    uint8_t tx_buf[ 3 ] = { 0 };
    
    tx_buf[ 0 ] = ( ( command & 0x0F ) << 4 ) | ( address & 0x0F );
    tx_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    tx_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t digipot9_generic_read ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint8_t tx_buf;
    
    spi_master_select_device( ctx->chip_select );
    tx_buf = ( ( command & 0x0F ) << 4 ) | ( address & 0x0F );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tx_buf, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    tx_buf = DIGIPOT9_CMD_NOP;
    error_flag |= spi_master_write_then_read( &ctx->spi, &tx_buf, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );

    *data_out = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    return error_flag;
}

err_t digipot9_set_wiper_1 ( digipot9_t *ctx, uint16_t data_in ) 
{
    return digipot9_generic_write ( ctx, DIGIPOT9_CMD_WRITE_DATA, DIGIPOT9_ADDRESS_RDAC1, data_in );
}

err_t digipot9_set_wiper_2 ( digipot9_t *ctx, uint16_t data_in ) 
{
    return digipot9_generic_write ( ctx, DIGIPOT9_CMD_WRITE_DATA, DIGIPOT9_ADDRESS_RDAC2, data_in );
}

void digipot9_set_pr_pin ( digipot9_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->pr, state );
}

void digipot9_set_wp_pin ( digipot9_t *ctx, uint8_t state ) 
{
    digital_out_write ( &ctx->wp, state );
}

uint8_t digipot9_get_rdy_pin ( digipot9_t *ctx ) 
{
    return digital_in_read ( &ctx->rdy );
}

err_t digipot9_write_user_data ( digipot9_t *ctx, uint8_t address, uint16_t data_in ) 
{
    if ( address < DIGIPOT9_ADDRESS_USER_DATA_0 )
    {
        address = DIGIPOT9_ADDRESS_USER_DATA_0;
    }
    if ( address > DIGIPOT9_ADDRESS_USER_DATA_12 )
    {
        address = DIGIPOT9_ADDRESS_USER_DATA_12;
    }
    err_t error_flag = digipot9_generic_write ( ctx, DIGIPOT9_CMD_STORE_USER_DATA, address, data_in );
    
    while ( digipot9_get_rdy_pin ( ctx ) );
    while ( !digipot9_get_rdy_pin ( ctx ) );
    
    return error_flag;
}

err_t digipot9_read_user_data ( digipot9_t *ctx, uint8_t address, uint16_t *data_out ) 
{
    if ( address < DIGIPOT9_ADDRESS_USER_DATA_0 )
    {
        address = DIGIPOT9_ADDRESS_USER_DATA_0;
    }
    if ( address > DIGIPOT9_ADDRESS_USER_DATA_12 )
    {
        address = DIGIPOT9_ADDRESS_USER_DATA_12;
    }    
    return digipot9_generic_read ( ctx, DIGIPOT9_CMD_READ_EEMEM, address, data_out );
}

// ------------------------------------------------------------------------- END
