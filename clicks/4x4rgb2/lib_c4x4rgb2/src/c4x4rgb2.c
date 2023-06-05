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
 * @file c4x4rgb2.c
 * @brief 4x4 RGB 2 Click Driver.
 */

#include "c4x4rgb2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void c4x4rgb2_cfg_setup ( c4x4rgb2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
}

err_t c4x4rgb2_init ( c4x4rgb2_t *ctx, c4x4rgb2_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

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

    return SPI_MASTER_SUCCESS;
}

err_t c4x4rgb2_default_cfg ( c4x4rgb2_t *ctx ) 
{
    err_t error_flag = C4X4RGB2_OK;
    c4x4rgb2_set_all_leds_brightness ( ctx, C4X4RGB2_LED_BRIGHTNESS_DEFAULT );
    c4x4rgb2_set_all_leds_color ( ctx, C4X4RGB2_COLOR_BLACK );
    error_flag |= c4x4rgb2_write_led_matrix ( ctx );
    return error_flag;
}

err_t c4x4rgb2_write_leds ( c4x4rgb2_t *ctx, c4x4rgb2_led_t *leds, uint8_t num_leds )
{
    if ( num_leds > C4X4RGB2_NUM_LEDS )
    {
        return C4X4RGB2_ERROR;
    }
    uint8_t data_buf[ 72 ] = { 0 };
    memset ( &data_buf[ 0 ], C4X4RGB2_FRAME_START, 4 );
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt < num_leds; led_cnt++ )
    {
        data_buf[ 4 + led_cnt * 4 ] = C4X4RGB2_LED_BRIGHTNESS_MASK | leds[ led_cnt ].brightness;
        data_buf[ 5 + led_cnt * 4 ] = leds[ led_cnt ].blue;
        data_buf[ 6 + led_cnt * 4 ] = leds[ led_cnt ].green;
        data_buf[ 7 + led_cnt * 4 ] = leds[ led_cnt ].red;
    }
    memset ( &data_buf[ 4 + num_leds * 4 ], C4X4RGB2_FRAME_END, 4 );
    return spi_master_write( &ctx->spi, data_buf, 8 + num_leds * 4 );
}

err_t c4x4rgb2_write_led_matrix ( c4x4rgb2_t *ctx )
{
    return c4x4rgb2_write_leds ( ctx, ctx->led_matrix, C4X4RGB2_NUM_LEDS );
}

void c4x4rgb2_set_led_brightness ( c4x4rgb2_t *ctx, uint8_t led_num, uint8_t brightness )
{
    ctx->led_matrix[ led_num % C4X4RGB2_NUM_LEDS ].brightness = brightness % ( C4X4RGB2_LED_BRIGHTNESS_MAX + 1 );
}

void c4x4rgb2_set_all_leds_brightness ( c4x4rgb2_t *ctx, uint8_t brightness )
{
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt <= C4X4RGB2_LED_15; led_cnt++ )
    {
        c4x4rgb2_set_led_brightness ( ctx, led_cnt, brightness );
    }
}

void c4x4rgb2_set_led_color ( c4x4rgb2_t *ctx, uint8_t led_num, uint32_t rgb )
{
    ctx->led_matrix[ led_num % C4X4RGB2_NUM_LEDS ].red = ( uint8_t ) ( ( rgb >> 16 ) & 0xFF );
    ctx->led_matrix[ led_num % C4X4RGB2_NUM_LEDS ].green = ( uint8_t ) ( ( rgb >> 8 ) & 0xFF );
    ctx->led_matrix[ led_num % C4X4RGB2_NUM_LEDS ].blue = ( uint8_t ) ( rgb & 0xFF );
}

void c4x4rgb2_set_all_leds_color ( c4x4rgb2_t *ctx, uint32_t rgb )
{
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt <= C4X4RGB2_LED_15; led_cnt++ )
    {
        c4x4rgb2_set_led_color ( ctx, led_cnt, rgb );
    }
}

// ------------------------------------------------------------------------- END
