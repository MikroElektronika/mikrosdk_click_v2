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
 * @file spiisolator3.c
 * @brief SPI Isolator 3 Click Driver.
 */

#include "spiisolator3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void spiisolator3_cfg_setup ( spiisolator3_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->saa  = HAL_PIN_NC;
    cfg->oen = HAL_PIN_NC;
    cfg->aux = HAL_PIN_NC;
    cfg->flt = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t spiisolator3_init ( spiisolator3_t *ctx, spiisolator3_cfg_t *cfg ) {
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

    // It should contain the error status checking for every pin init.

    digital_out_init( &ctx->saa, cfg->saa );
    digital_out_init( &ctx->oen, cfg->oen );
    digital_out_init( &ctx->aux, cfg->aux );

    digital_in_init( &ctx->flt, cfg->flt );

    return SPI_MASTER_SUCCESS;
}

err_t spiisolator3_default_cfg ( spiisolator3_t *ctx ) {
    spiisolator3_set_side_a_active( ctx, SPIISOLATOR3_PIN_STATE_LOW );
    
    spiisolator3_set_sdo_enable( ctx, SPIISOLATOR3_PIN_STATE_LOW );
    
    spiisolator3_set_aux( ctx, SPIISOLATOR3_PIN_STATE_HIGH );
    
    return SPIISOLATOR3_OK;
}

err_t spiisolator3_generic_write ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ];
    uint8_t cnt;

    tx_buf[ 0 ] = reg;
    for ( cnt = 1; cnt <= len; cnt++ ) {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t spiisolator3_generic_read ( spiisolator3_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void spiisolator3_set_side_a_active ( spiisolator3_t *ctx, uint8_t saa_state ) {
    digital_out_write( &ctx->saa, saa_state );
}

void spiisolator3_set_sdo_enable ( spiisolator3_t *ctx, uint8_t sdo_state ) {
    digital_out_write( &ctx->oen, sdo_state );
}

void spiisolator3_set_aux ( spiisolator3_t *ctx, uint8_t aux_state ) {
    digital_out_write( &ctx->aux, aux_state );
}

uint8_t spiisolator3_get_fault ( spiisolator3_t *ctx ) {
    return digital_in_read( &ctx->flt );
}

// ------------------------------------------------------------------------- END
