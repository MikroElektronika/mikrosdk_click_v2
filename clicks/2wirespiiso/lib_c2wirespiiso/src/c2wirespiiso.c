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
 * @file c2wirespiiso.c
 * @brief 2-Wire SPI ISO Click Driver.
 */

#include "c2wirespiiso.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void c2wirespiiso_cfg_setup ( c2wirespiiso_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->dis  = HAL_PIN_NC;
    cfg->txen = HAL_PIN_NC;
    cfg->bne  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c2wirespiiso_init ( c2wirespiiso_t *ctx, c2wirespiiso_cfg_t *cfg ) 
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

    digital_out_init( &ctx->dis, cfg->dis );
    digital_out_init( &ctx->txen, cfg->txen );

    digital_in_init( &ctx->bne, cfg->bne );

    return SPI_MASTER_SUCCESS;
}

void c2wirespiiso_default_cfg ( c2wirespiiso_t *ctx )
{
    SET_SPI_DATA_SAMPLE_EDGE;
    c2wirespiiso_enable_tx ( ctx );
    c2wirespiiso_enable_device ( ctx );
    Delay_100ms ( );
}

err_t c2wirespiiso_write ( c2wirespiiso_t *ctx, uint8_t *data_in, uint8_t in_len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_in, in_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c2wirespiiso_read ( c2wirespiiso_t *ctx, uint8_t *data_out, uint8_t out_len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_out, out_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c2wirespiiso_write_then_read ( c2wirespiiso_t *ctx, uint8_t *data_in, uint8_t in_len, 
                                                          uint8_t *data_out, uint8_t out_len )
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, data_in, in_len, data_out, out_len );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

void c2wirespiiso_disable_device ( c2wirespiiso_t *ctx )
{
    digital_out_high ( &ctx->dis );
}

void c2wirespiiso_enable_device ( c2wirespiiso_t *ctx )
{
    digital_out_low ( &ctx->dis );
}

void c2wirespiiso_disable_tx ( c2wirespiiso_t *ctx )
{
    digital_out_low ( &ctx->txen );
}

void c2wirespiiso_enable_tx ( c2wirespiiso_t *ctx )
{
    digital_out_high ( &ctx->txen );
}

uint8_t c2wirespiiso_get_bne_pin ( c2wirespiiso_t *ctx )
{
    return digital_in_read ( &ctx->bne );
}

// ------------------------------------------------------------------------- END
