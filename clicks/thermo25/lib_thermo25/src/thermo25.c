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
 * @file thermo25.c
 * @brief Thermo 25 Click Driver.
 */

#include "thermo25.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void thermo25_cfg_setup ( thermo25_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t thermo25_init ( thermo25_t *ctx, thermo25_cfg_t *cfg ) 
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
    Delay_100ms ( );

    return SPI_MASTER_SUCCESS;
}

err_t thermo25_set_mode ( thermo25_t *ctx, uint8_t mode )
{
    if ( ( THERMO25_MODE_SHUTDOWN != mode ) && ( THERMO25_MODE_CONTINUOUS != mode ) )
    {
        return THERMO25_ERROR;
    }
    ctx->dev_mode = mode;
    uint8_t data_buf[ 4 ] = { DUMMY, DUMMY, ctx->dev_mode, ctx->dev_mode };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t thermo25_read_data ( thermo25_t *ctx, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { DUMMY, DUMMY, ctx->dev_mode, ctx->dev_mode };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, &data_buf[ 0 ], 2 );
    error_flag |= spi_master_write( &ctx->spi, &data_buf[ 2 ], 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return error_flag;
}

err_t thermo25_check_communication ( thermo25_t *ctx )
{
    uint16_t device_id;
    if ( THERMO25_ERROR == thermo25_set_mode ( ctx, THERMO25_MODE_SHUTDOWN ) )
    {
        return THERMO25_ERROR;
    }
    if ( THERMO25_ERROR == thermo25_read_data ( ctx, &device_id ) )
    {
        return THERMO25_ERROR;
    }
    if ( THERMO25_DEVICE_ID != device_id )
    {
        return THERMO25_ERROR;
    }
    if ( THERMO25_ERROR == thermo25_set_mode ( ctx, THERMO25_MODE_CONTINUOUS ) )
    {
        return THERMO25_ERROR;
    }
    return THERMO25_OK;
}

err_t thermo25_read_temperature ( thermo25_t *ctx, float *temperature )
{
    uint16_t raw_temp;
    if ( THERMO25_ERROR == thermo25_read_data ( ctx, &raw_temp ) )
    {
        return THERMO25_ERROR;
    }
    *temperature = ( ( int16_t ) raw_temp >> 2 ) * THERMO25_DATA_RESOLUTION;
    return THERMO25_OK;
}

// ------------------------------------------------------------------------- END
