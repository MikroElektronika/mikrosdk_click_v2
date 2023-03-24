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
 * @file dcmotor16.c
 * @brief DC Motor 16 Click Driver.
 */

#include "dcmotor16.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void dcmotor16_cfg_setup ( dcmotor16_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->fwd = HAL_PIN_NC;
    cfg->rev = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t dcmotor16_init ( dcmotor16_t *ctx, dcmotor16_cfg_t *cfg ) {
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

    digital_out_init( &ctx->fwd, cfg->fwd );
    digital_out_init( &ctx->rev, cfg->rev );

    return SPI_MASTER_SUCCESS;
}

err_t dcmotor16_generic_write ( dcmotor16_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) {
    uint8_t tx_buf[ 257 ] = { 0 };

    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_in[ cnt - 1 ];
    }

    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

err_t dcmotor16_generic_read ( dcmotor16_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) {
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write_then_read( &ctx->spi, &reg, 1, data_out, len );
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

void dcmotor16_set_direction( dcmotor16_t *ctx, uint8_t dir ) {
    if ( dir == DCMOTOR16_DIR_FORWARD ) {
        digital_out_high( &ctx->fwd );
        digital_out_low( &ctx->rev );
    } else {
        digital_out_low( &ctx->fwd );
        digital_out_high( &ctx->rev );
    }
}

void dcmotor16_ctrl_fwd_pin( dcmotor16_t *ctx, uint8_t state ) {
    if ( state == DCMOTOR16_ENABLE ) {
        digital_out_high( &ctx->fwd );
    } else {
        digital_out_low( &ctx->fwd );
    }
}

void dcmotor16_ctrl_rev_pin( dcmotor16_t *ctx, uint8_t state ) {
    if ( state == DCMOTOR16_ENABLE ) {
        digital_out_high( &ctx->rev );
    } else {
        digital_out_low( &ctx->rev );
    }
}

void dcmotor16_ctrl_vref( dcmotor16_t *ctx, uint16_t value ) {
    uint8_t tx_buf[ 2 ];

    if ( value >= 0x0100 ) { 
        value = 0x0100;
    }
    tx_buf[ 0 ] = ( value >> 8 ) & 0x000F;
    tx_buf[ 1 ] = ( value ) & 0x00FF;
    
    spi_master_select_device( ctx->chip_select );
    spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
}

void dcmotor16_stop( dcmotor16_t *ctx ) {
    digital_out_low( &ctx->fwd );
    digital_out_low( &ctx->rev );
}


// ------------------------------------------------------------------------- END
