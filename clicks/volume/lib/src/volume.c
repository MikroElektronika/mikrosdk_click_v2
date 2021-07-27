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
 * @file volume.c
 * @brief Volume Click Driver.
 */

#include "volume.h"

// ------------------------------------------------------------- PRIVATE MACROS 

#define VOLUME_ZERO_SCALE 192
#define VOLUME_GAIN_STEP  0.5

#define VOLUME_DUMMY      0x00

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void dev_reset_delay ( void );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void volume_cfg_setup ( volume_cfg_t *cfg ) {
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->zce  = HAL_PIN_NC;
    cfg->sen  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t volume_init ( volume_t *ctx, volume_cfg_t *cfg ) {
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, VOLUME_DUMMY ) == SPI_MASTER_ERROR ) {
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

    digital_out_init( &ctx->zce, cfg->zce );
    digital_out_init( &ctx->sen, cfg->sen );
    
    return SPI_MASTER_SUCCESS;
}

void volume_default_cfg ( volume_t *ctx ) {
    volume_power_up( ctx );
    volume_zero_crossing( ctx, VOLUME_ZCE_DISABLE );
    // Click default configuration.
}

void volume_power_up ( volume_t *ctx ) {
    digital_out_low( &ctx->sen );
    dev_reset_delay( );
    digital_out_high( &ctx->sen );
    dev_reset_delay( );
}

void volume_hw_mute ( volume_t *ctx, uint8_t mute_state ) {
    digital_out_write( &ctx->sen, mute_state );
}

void volume_zero_crossing ( volume_t *ctx, uint8_t zce_state ) {
    digital_out_write( &ctx->zce, zce_state );
}

err_t volume_set_vol_gain( volume_t *ctx, float volume_left_dB, float volume_right_dB ) {
    uint8_t data_buf[ 2 ];
    uint8_t vol_modifier;
    
    vol_modifier = ( uint8_t )( ( volume_left_dB / VOLUME_GAIN_STEP ) + VOLUME_ZERO_SCALE );
    data_buf[ 1 ] = vol_modifier;
    
    vol_modifier = ( uint8_t )( ( volume_right_dB / VOLUME_GAIN_STEP ) + VOLUME_ZERO_SCALE );
    data_buf[ 0 ] = vol_modifier;
    
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void dev_reset_delay ( void ) {
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
