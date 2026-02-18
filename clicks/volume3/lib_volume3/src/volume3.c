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
 * @file volume3.c
 * @brief Volume 3 Click Driver.
 */

#include "volume3.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void volume3_cfg_setup ( volume3_cfg_t *cfg ) 
{
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

err_t volume3_init ( volume3_t *ctx, volume3_cfg_t *cfg ) 
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

    digital_out_init( &ctx->zce, cfg->zce );
    digital_out_init( &ctx->sen, cfg->sen );

    return SPI_MASTER_SUCCESS;
}

err_t volume3_set_gain ( volume3_t *ctx, float gain_left, float gain_right )
{
    err_t error_flag = VOLUME3_OK;
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( gain_left < ( VOLUME3_GAIN_DB_MIN - VOLUME3_GAIN_DB_STEP / 2 ) ) || 
         ( gain_left > ( VOLUME3_GAIN_DB_MAX + VOLUME3_GAIN_DB_STEP / 2 ) ) || 
         ( gain_right < ( VOLUME3_GAIN_DB_MIN - VOLUME3_GAIN_DB_STEP / 2 ) ) || 
         ( gain_right > ( VOLUME3_GAIN_DB_MAX + VOLUME3_GAIN_DB_STEP / 2 ) ) )
    {
        return VOLUME3_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ( gain_right - VOLUME3_GAIN_DB_MIN ) / VOLUME3_GAIN_DB_STEP ) + VOLUME3_GAIN_DB_STEP / 2 );
    data_buf[ 1 ] = ( uint8_t ) ( ( ( gain_left - VOLUME3_GAIN_DB_MIN ) / VOLUME3_GAIN_DB_STEP ) + VOLUME3_GAIN_DB_STEP / 2 );
    ctx->gain_right = data_buf[ 0 ] * VOLUME3_GAIN_DB_STEP + VOLUME3_GAIN_DB_MIN;
    ctx->gain_left = data_buf[ 1 ] * VOLUME3_GAIN_DB_STEP + VOLUME3_GAIN_DB_MIN;
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t volume3_set_volume ( volume3_t *ctx, uint8_t volume_left, uint8_t volume_right )
{
    float gain_left = 0;
    float gain_right = 0;
    if ( ( volume_left < VOLUME3_VOLUME_MUTE ) || 
         ( volume_left > VOLUME3_VOLUME_MAX ) || 
         ( volume_right < VOLUME3_VOLUME_MUTE ) || 
         ( volume_right > VOLUME3_VOLUME_MAX ) )
    {
        return VOLUME3_ERROR;
    }
    if ( VOLUME3_VOLUME_MUTE == volume_left )
    {
        gain_left = VOLUME3_GAIN_DB_MIN;
    }
    else
    {
        gain_left = ( float ) ( VOLUME3_GAIN_DB_VOLUME_MAX - VOLUME3_GAIN_DB_VOLUME_MIN ) / 
                              ( VOLUME3_VOLUME_MAX - VOLUME3_VOLUME_MIN ) * volume_left + VOLUME3_GAIN_DB_VOLUME_MIN; 
    }
    if ( VOLUME3_VOLUME_MUTE == volume_right )
    {
        gain_right = VOLUME3_GAIN_DB_MIN;
    }
    else
    {
        gain_right = ( float ) ( VOLUME3_GAIN_DB_VOLUME_MAX - VOLUME3_GAIN_DB_VOLUME_MIN ) / 
                               ( VOLUME3_VOLUME_MAX - VOLUME3_VOLUME_MIN ) * volume_right + VOLUME3_GAIN_DB_VOLUME_MIN;
    }
    return volume3_set_gain ( ctx, gain_left, gain_right );
}

void volume3_zero_crossing_enable ( volume3_t *ctx )
{
    digital_out_high ( &ctx->zce );
}

void volume3_zero_crossing_disable ( volume3_t *ctx )
{
    digital_out_low ( &ctx->zce );
}

void volume3_sound_enable ( volume3_t *ctx )
{
    digital_out_high ( &ctx->sen );
}

void volume3_sound_disable ( volume3_t *ctx )
{
    digital_out_low ( &ctx->sen );
}

// ------------------------------------------------------------------------- END
