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
 * @file boost10.c
 * @brief Boost 10 Click Driver.
 */

#include "boost10.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void boost10_cfg_setup ( boost10_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pg   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t boost10_init ( boost10_t *ctx, boost10_cfg_t *cfg ) 
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

    digital_in_init( &ctx->pg, cfg->pg );

    return SPI_MASTER_SUCCESS;
}

err_t boost10_set_wiper ( boost10_t *ctx, uint8_t wiper ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &wiper, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

uint8_t boost10_get_pg_pin ( boost10_t *ctx )
{
    return digital_in_read ( &ctx->pg );
}

err_t boost10_set_resistance ( boost10_t *ctx, float res_kohm )
{
    uint8_t wiper = BOOST10_WIPER_MIN;
    if ( res_kohm >= ( ( BOOST10_R8_RES_KOHM + BOOST10_DIGIPOT_RES_KOHM ) - 
                       BOOST10_DIGIPOT_RES_KOHM / BOOST10_WIPER_POS ) )
    {
        wiper = BOOST10_WIPER_MAX;
    }
    else if ( res_kohm > BOOST10_R8_RES_KOHM )
    {
        wiper = ( uint8_t ) ( ( float ) ( res_kohm - BOOST10_R8_RES_KOHM ) / 
                                        ( BOOST10_DIGIPOT_RES_KOHM / BOOST10_WIPER_POS ) );
    }
    return boost10_set_wiper ( ctx, wiper );
}

err_t boost10_set_vout ( boost10_t *ctx, float vout )
{
    float resistance = ( BOOST10_R8_RES_KOHM + BOOST10_DIGIPOT_RES_KOHM );
    if ( vout >= BOOST10_VOUT_MAX )
    {
        resistance = BOOST10_R8_RES_KOHM;
    }
    else if ( vout > BOOST10_VOUT_MIN )
    {
        resistance = BOOST10_R7_RES_KOHM / ( vout - BOOST10_VOUT_OFFSET );
    }
    return boost10_set_resistance ( ctx, resistance );
}

// ------------------------------------------------------------------------- END
