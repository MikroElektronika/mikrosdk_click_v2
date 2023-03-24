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
 * @file buck20.c
 * @brief Buck 20 Click Driver.
 */

#include "buck20.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void buck20_cfg_setup ( buck20_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->rdy  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t buck20_init ( buck20_t *ctx, buck20_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );
    digital_out_low ( &ctx->rst );

    digital_in_init( &ctx->rdy, cfg->rdy );

    return SPI_MASTER_SUCCESS;
}

err_t buck20_generic_write ( buck20_t *ctx, uint8_t command, uint8_t address, uint16_t data_in ) 
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

err_t buck20_generic_read ( buck20_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    uint8_t tx_buf;
    spi_master_select_device( ctx->chip_select );
    tx_buf = ( ( command & 0x0F ) << 4 ) | ( address & 0x0F );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &tx_buf, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    tx_buf = BUCK20_CMD_NOP;
    error_flag |= spi_master_write_then_read( &ctx->spi, &tx_buf, 1, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    return error_flag;
}

err_t buck20_set_wiper_1 ( buck20_t *ctx, uint16_t data_in ) 
{
    return buck20_generic_write ( ctx, BUCK20_CMD_WRITE_DATA, BUCK20_ADDRESS_RDAC1, data_in );
}

err_t buck20_write_user_data ( buck20_t *ctx, uint8_t address, uint16_t data_in ) 
{
    if ( address < BUCK20_ADDRESS_USER_DATA_0 )
    {
        address = BUCK20_ADDRESS_USER_DATA_0;
    }
    if ( address > BUCK20_ADDRESS_USER_DATA_12 )
    {
        address = BUCK20_ADDRESS_USER_DATA_12;
    }
    err_t error_flag = buck20_generic_write ( ctx, BUCK20_CMD_STORE_USER_DATA, address, data_in );
    while ( buck20_get_rdy_pin ( ctx ) );
    while ( !buck20_get_rdy_pin ( ctx ) );
    return error_flag;
}

err_t buck20_read_user_data ( buck20_t *ctx, uint8_t address, uint16_t *data_out ) 
{
    if ( address < BUCK20_ADDRESS_USER_DATA_0 )
    {
        address = BUCK20_ADDRESS_USER_DATA_0;
    }
    if ( address > BUCK20_ADDRESS_USER_DATA_12 )
    {
        address = BUCK20_ADDRESS_USER_DATA_12;
    }    
    return buck20_generic_read ( ctx, BUCK20_CMD_READ_EEMEM, address, data_out );
}

uint8_t buck20_get_rdy_pin ( buck20_t *ctx )
{
    return digital_in_read ( &ctx->rdy );
}

void buck20_enable_device ( buck20_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void buck20_disable_device ( buck20_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

// ------------------------------------------------------------------------- END
