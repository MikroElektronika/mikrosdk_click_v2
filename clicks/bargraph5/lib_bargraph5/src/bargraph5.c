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
 * @file bargraph5.c
 * @brief BarGraph 5 Click Driver.
 */

#include "bargraph5.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void bargraph5_cfg_setup ( bargraph5_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->blank = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t bargraph5_init ( bargraph5_t *ctx, bargraph5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->blank, cfg->blank );

    return SPI_MASTER_SUCCESS;
}

err_t bargraph5_default_cfg ( bargraph5_t *ctx ) 
{
    err_t error_flag = BARGRAPH5_OK;
    bargraph5_output_disable ( ctx );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_0, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_1, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_2, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_3, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_4, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    error_flag |= bargraph5_set_bar_level ( ctx, BARGRAPH5_BAR_5, BARGRAPH5_LEVEL_0, BARGRAPH5_BRIGHTNESS_DEFAULT );
    bargraph5_output_enable ( ctx );
    return error_flag;
}

err_t bargraph5_write_channels ( bargraph5_t *ctx ) 
{
    uint8_t data_buf[ ( BARGRAPH5_CHANNELS_NUM / 2 ) * 3 ] = { 0 };
    for ( uint8_t cnt = 0; cnt < ( BARGRAPH5_CHANNELS_NUM / 2 ); cnt++ )
    {
        data_buf[ cnt * 3 ] = 
            ( uint8_t ) ( ( ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 ] >> 4 ) & 0xFF );
        data_buf[ cnt * 3 + 1 ] = 
            ( uint8_t ) ( ( ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 ] << 4 ) & 0xF0 ) | 
            ( uint8_t ) ( ( ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 + 1 ] >> 8 ) & 0x0F );
        data_buf[ cnt * 3 + 2 ] = 
            ( uint8_t ) ( ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 + 1 ] & 0xFF );
    }
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, ( BARGRAPH5_CHANNELS_NUM / 2 ) * 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t bargraph5_read_channels ( bargraph5_t *ctx ) 
{
    uint8_t data_buf[ ( BARGRAPH5_CHANNELS_NUM / 2 ) * 3 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_buf, ( BARGRAPH5_CHANNELS_NUM / 2 ) * 3 );
    spi_master_deselect_device( ctx->chip_select );
    if ( BARGRAPH5_OK == error_flag )
    {
        for ( uint8_t cnt = 0; cnt < ( BARGRAPH5_CHANNELS_NUM / 2 ); cnt++ )
        {
            ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 ] = 
                ( ( uint16_t ) data_buf[ cnt * 3 ] << 4 ) | ( ( data_buf[ cnt * 3 + 1 ] & 0xF0 ) >> 4 );
            ctx->channels[ ( BARGRAPH5_CHANNELS_NUM / 2 - cnt - 1 ) * 2 + 1 ] = 
                ( ( uint16_t ) ( data_buf[ cnt * 3 + 1 ] & 0x0F ) << 8 ) | data_buf[ cnt * 3 + 2 ];
            error_flag |= bargraph5_write_channels( ctx );
        }
    }
    return error_flag;
}

void bargraph5_output_enable ( bargraph5_t *ctx )
{
    digital_out_low ( &ctx->blank );
}

void bargraph5_output_disable ( bargraph5_t *ctx )
{
    digital_out_high ( &ctx->blank );
}

err_t bargraph5_set_bar_level ( bargraph5_t *ctx, bargraph5_bar_sel_t bar_num, 
                                bargraph5_level_t level, uint16_t brightness )
{
    if ( ( bar_num > BARGRAPH5_BAR_5 ) || ( level > BARGRAPH5_LEVEL_4 ) || 
         ( brightness > BARGRAPH5_BRIGHTNESS_MAX ) )
    {
        return BARGRAPH5_ERROR;
    }

    ctx->channels[ ( bar_num ^ 1 ) * 4 ] = BARGRAPH5_BRIGHTNESS_MIN;
    ctx->channels[ ( bar_num ^ 1 ) * 4 + 1 ] = BARGRAPH5_BRIGHTNESS_MIN;
    ctx->channels[ ( bar_num ^ 1 ) * 4 + 2 ] = BARGRAPH5_BRIGHTNESS_MIN;
    ctx->channels[ ( bar_num ^ 1 ) * 4 + 3 ] = BARGRAPH5_BRIGHTNESS_MIN;

    for ( uint8_t cnt = BARGRAPH5_LEVEL_0; cnt < level; cnt++ )
    {
        // The last bit of the bar number and level is inverted to match the bars order
        ctx->channels[ ( bar_num ^ 1 ) * 4 + cnt ^ 1 ] = brightness;
    }

    return bargraph5_write_channels ( ctx );
}

// ------------------------------------------------------------------------- END
