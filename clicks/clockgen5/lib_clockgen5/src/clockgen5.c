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
 * @file clockgen5.c
 * @brief Clock Gen 5 Click Driver.
 */

#include "clockgen5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

// -------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

/**
 * @brief Get dac function.
 * @details Function for geting dac value.
 */
static uint16_t dev_get_dac_value( double freq );

/**
 * @brief Get power function.
 * @details Function for getting a value of 2 on the power of exp.
 */
static uint32_t drv_pow_2 ( uint8_t exp );

/**
 * @brief Get oct function.
 * @details Function for geting oct value.
 */
static uint8_t dev_get_oct( double freq );


// --------------------------------------------------------- PUBLIC FUNCTIONS 

void clockgen5_cfg_setup ( clockgen5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->oe = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t clockgen5_init ( clockgen5_t *ctx, clockgen5_cfg_t *cfg ) 
{
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

    digital_out_init( &ctx->oe, cfg->oe );
    
    return SPI_MASTER_SUCCESS;
    
    ctx->dev_config = 0x00;
}

void clockgen5_out_enable ( clockgen5_t *ctx, uint8_t en_out ) {
    if ( en_out == CLOCKGEN5_OUTPUT_ENABLE ) {
        digital_out_high( &ctx->oe );
    } else {
        digital_out_high( &ctx->oe );
    }
}


void clockgen5_set_config ( clockgen5_t *ctx, uint8_t cfg ) {
    ctx->dev_config = ( cfg & 0x03 );
}

void clockgen5_set_freq ( clockgen5_t *ctx, float freq ) {
    uint8_t tx_data[ 2 ];
    uint16_t set_value;

    set_value = dev_get_oct( freq ) << 12;
    set_value |= dev_get_dac_value( freq ) << 2;
    set_value |= ctx->dev_config & 0x03;

    tx_data[ 0 ] = set_value >> 8;
    tx_data[ 1 ] = set_value;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_data, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

// --------------------------------------------- PRIVATE FUNCTION DEFINITIONS 

static uint16_t dev_get_dac_value( double freq ) {
    uint8_t oct;
    uint16_t dac_value;
    double calc_data;

    oct = dev_get_oct( freq );

    calc_data = 2078.0 / ( float )( freq * 1000 );
    calc_data *= 1024;
    calc_data *= drv_pow_2( oct );
    dac_value = 2048 - calc_data;
    dac_value = dac_value & 0x03FF;

    return dac_value;
}

static uint32_t drv_pow_2 ( uint8_t exp ) {
    uint8_t cnt;
    uint32_t res = 2;

    if ( exp == 0 ) {
        return 1;
    } else if ( exp == 1 ) {
        return 2;
    } else {
        for ( cnt = 2; cnt <= exp; cnt++ ) {
            res *= 2;
        }
    }
    return res;
}

static uint8_t dev_get_oct( double freq ) {
    if ( ( freq >= 1.039 ) && ( freq < 2.078 ) ) {
        return CLOCKGEN5_OCT_0;
    } else if ( ( freq >= 2.078 ) && ( freq < 4.152 ) ) {
        return CLOCKGEN5_OCT_1;
    } else if ( ( freq >= 4.152 ) && ( freq < 8.304 ) ) {
        return CLOCKGEN5_OCT_2;
    } else if ( ( freq >= 8.304 ) && ( freq < 16.61 ) ) {
        return CLOCKGEN5_OCT_3;
    } else if ( ( freq >= 16.61 ) && ( freq < 33.22 ) ) {
        return CLOCKGEN5_OCT_4;
    } else if ( ( freq >= 33.22 ) && ( freq < 66.43 ) ) {
        return CLOCKGEN5_OCT_5;
    } else if ( ( freq >= 66.43 ) && ( freq < 132.9 ) ) {
        return CLOCKGEN5_OCT_6;
    } else if ( ( freq >= 132.9 ) && ( freq < 265.7 ) ) {
        return CLOCKGEN5_OCT_7;
    } else if ( ( freq >= 265.7 ) && ( freq < 531.4 ) ) {
        return CLOCKGEN5_OCT_8;
    } else if ( ( freq >= 531.4 ) && ( freq < 1063.0 ) ) {
        return CLOCKGEN5_OCT_9;
    } else if ( ( freq >= 1063.0 ) && ( freq < 2126.0 ) ) {
        return CLOCKGEN5_OCT_10;
    } else if ( ( freq >= 2126.0 ) && ( freq < 4252.0 ) ) {
        return CLOCKGEN5_OCT_11;
    } else if ( ( freq >= 4252.0 ) && ( freq < 8503.0 ) ) {
        return CLOCKGEN5_OCT_12;
    } else if ( ( freq >= 8053.0 ) && ( freq < 17010.0 ) ) {
        return CLOCKGEN5_OCT_13;
    } else if ( ( freq >= 17010.0 ) && ( freq < 34010.0 ) ) {
        return CLOCKGEN5_OCT_14;
    } else if ( ( freq >= 34010.0 ) && ( freq < 68030.0 ) ) {
        return CLOCKGEN5_OCT_15;
    }
    
    return CLOCKGEN5_OCT_0;
}

// ------------------------------------------------------------------------- END
