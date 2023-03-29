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
 * @file currentlimit6.c
 * @brief Current Limit 6 Click Driver.
 */

#include "currentlimit6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                                   0x00

#define CURRENTLIMIT6_DIGIPOT_RES_10_kohm   100000.0

#define CURRENTLIMIT6_Rset_1500_ohm           1500.0

#define CURRENTLIMIT6_TAP_POINTS_MIN           217
#define CURRENTLIMIT6_TAP_POINTS_MAX           252
#define CURRENTLIMIT6_DIFF_TAP_POINTS          256


void currentlimit6_cfg_setup ( currentlimit6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->er2   = HAL_PIN_NC;
    cfg->en = HAL_PIN_NC;
    cfg->er1 = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t currentlimit6_init ( currentlimit6_t *ctx, currentlimit6_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );

    digital_in_init( &ctx->er2, cfg->er2 );
    digital_in_init( &ctx->er1, cfg->er1 );

    return SPI_MASTER_SUCCESS;
}

err_t currentlimit6_default_cfg ( currentlimit6_t *ctx ) 
{
    return currentlimit6_power_mode( ctx, CURRENTLIMIT6_PWR_ON );
}

err_t currentlimit6_power_mode ( currentlimit6_t *ctx, currentlimit6_pwr_mode_value_t pwr_mode ) 
{
    digital_out_write( &ctx->en, pwr_mode );

    return CURRENTLIMIT6_OK;
}

err_t currentlimit6_generic_write ( currentlimit6_t *ctx, uint8_t data_in ) 
{
    if ( data_in > CURRENTLIMIT6_TAP_POINTS_MAX )
    {
        data_in = CURRENTLIMIT6_TAP_POINTS_MAX;    
    } 
    else if  ( data_in < CURRENTLIMIT6_TAP_POINTS_MIN )
    {
        data_in = CURRENTLIMIT6_TAP_POINTS_MIN;    
    }
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, &data_in, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t currentlimit6_set_current_limit ( currentlimit6_t *ctx, float current_limit_a ) 
{   
    return currentlimit6_generic_write( ctx, ( uint8_t ) ( ( CURRENTLIMIT6_DIGIPOT_RES_10_kohm - 
                                                           ( CURRENTLIMIT6_Rset_1500_ohm / current_limit_a ) ) / 
                                                           ( CURRENTLIMIT6_DIGIPOT_RES_10_kohm / CURRENTLIMIT6_DIFF_TAP_POINTS ) ) );
}

uint8_t currentlimit6_check_limit_exceeded ( currentlimit6_t *ctx ) 
{
    return digital_in_read( &ctx->er1 );
}

uint8_t currentlimit6_check_voltage_err ( currentlimit6_t *ctx ) 
{
    return digital_in_read( &ctx->er2 );
}

// ------------------------------------------------------------------------- END
