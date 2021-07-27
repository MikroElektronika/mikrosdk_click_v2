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
 * @file powermux2.c
 * @brief Power MUX 2 Click Driver.
 */

#include "powermux2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY                           0x00

/**
 * @briefPower Power MUX 2 resistance 18 kOhm.
 * @details R11 resistance of 18 kOhm.
 */
#define RESISTANCE_R11_18_kOhm          18.0

/**
 * @briefPower Power MUX 2 max resistance of 100 kOhm.
 * @details Digital Potentiometer max resistance of 100 kOhm.
 */
#define MAX_RESISTANCE                 100

/**
 * @briefPower Power MUX 2 min resistance of 18 kOhm.
 * @details Digital Potentiometer min resistance of 18 kOhm.
 */
#define MIN_RESISTANCE                  18

/**
 * @briefPower Power MUX 2 wiper positions
 * @details Digital Potentiometer with 256 wiper positions.
 */
#define DIGPOT_NUM_WIPER_POSITIONS     256


void powermux2_cfg_setup ( powermux2_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t powermux2_init ( powermux2_t *ctx, powermux2_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    return SPI_MASTER_SUCCESS;
}

err_t powermux2_generic_write ( powermux2_t *ctx, uint8_t data_in ) {
    uint8_t tx_buf[ 1 ];
    
    tx_buf[ 0 ] = data_in;

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t powermux2_set_resistance ( powermux2_t *ctx, float resistance ) {
    uint8_t step;
    err_t error_flag;
    
    if ( ( resistance < MIN_RESISTANCE ) || ( resistance > MAX_RESISTANCE ) ) {
        error_flag = POWERMUX2_ERROR;    
    } else {      
        resistance -= RESISTANCE_R11_18_kOhm;
        resistance /= MAX_RESISTANCE;
        resistance *= DIGPOT_NUM_WIPER_POSITIONS;
    
        step = ( uint8_t ) resistance;

        error_flag = powermux2_generic_write( ctx, step );    
    }

    return error_flag;
}


// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

// ------------------------------------------------------------------------- END
