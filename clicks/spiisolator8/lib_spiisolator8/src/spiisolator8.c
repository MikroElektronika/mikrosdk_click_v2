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
 * @file spiisolator8.c
 * @brief SPI Isolator 8 Click Driver.
 */

#include "spiisolator8.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void spiisolator8_cfg_setup ( spiisolator8_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->enc  = HAL_PIN_NC;
    cfg->enp  = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t spiisolator8_init ( spiisolator8_t *ctx, spiisolator8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->enc, cfg->enc );
    digital_out_init( &ctx->enp, cfg->enp );

    digital_in_init( &ctx->flt, cfg->flt );

    return SPI_MASTER_SUCCESS;
}

void spiisolator8_default_cfg ( spiisolator8_t *ctx ) 
{
    // Enable channel output pins on side 1
    spiisolator8_enc_enable( ctx );
    // Enable channel output pins on side 2
    spiisolator8_enp_enable( ctx );
}

void spiisolator8_enc_enable ( spiisolator8_t *ctx ) 
{
    digital_out_high( &ctx->enc );
}

void spiisolator8_enc_disable ( spiisolator8_t *ctx ) 
{
    digital_out_low( &ctx->enc );
}

void spiisolator8_enp_enable ( spiisolator8_t *ctx ) 
{
    digital_out_high( &ctx->enp );
}

void spiisolator8_enp_disable ( spiisolator8_t *ctx ) 
{
    digital_out_low( &ctx->enp );
}

uint8_t spiisolator8_get_fault ( spiisolator8_t *ctx ) 
{
    return digital_in_read( &ctx->flt );
}

err_t spiisolator8_write ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t len ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_in, len );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t spiisolator8_read ( spiisolator8_t *ctx, uint8_t *data_out, uint8_t len_out ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_out, len_out );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t spiisolator8_write_then_read ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t len_in, 
                                                          uint8_t *data_out, uint8_t len_out ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write_then_read( &ctx->spi, data_in, len_in, data_out, len_out );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t spiisolator8_transfer ( spiisolator8_t *ctx, uint8_t *data_in, uint8_t *data_out, uint8_t len ) 
{
    err_t err_flag = SPIISOLATOR8_OK;
    spi_master_select_device( ctx->chip_select );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        err_flag |= spi_master_set_default_write_data( &ctx->spi, data_in[ cnt ] );
        err_flag |= spi_master_read( &ctx->spi, &data_out[ cnt ], 1 );
    }
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

// ------------------------------------------------------------------------- END
