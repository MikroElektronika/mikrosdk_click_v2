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
 * @file mux9.c
 * @brief MUX 9 Click Driver.
 */

#include "mux9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY          0x00

void mux9_cfg_setup ( mux9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t mux9_init ( mux9_t *ctx, mux9_cfg_t *cfg ) 
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

    return SPI_MASTER_SUCCESS;
}

void mux9_reset ( mux9_t *ctx ) 
{
    digital_out_low( &ctx->rst );
    Delay_10ms();
    digital_out_high( &ctx->rst );
    Delay_10ms();
}

void mux9_enable ( mux9_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

void mux9_disable ( mux9_t *ctx ) 
{
    digital_out_low( &ctx->rst );
}

err_t mux9_generic_write ( mux9_t *ctx, uint8_t data_in ) 
{
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t mux9_active_channel ( mux9_t *ctx, uint8_t sel_ch )
{
    err_t error_flag;

    if ( ( sel_ch < MUX9_SELECT_CH_1 ) || ( sel_ch > MUX9_SELECT_CH_8 ) )
    {
        error_flag = MUX9_ERROR;
    }
    else
    {
        error_flag = mux9_generic_write( ctx, MUX9_SELECT_CH_1 << (--sel_ch) );
    }
    return error_flag;
}

// ------------------------------------------------------------------------- END
