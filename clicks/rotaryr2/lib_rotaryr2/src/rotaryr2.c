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
 * @file rotaryr2.c
 * @brief Rotary R 2 Click Driver.
 */

#include "rotaryr2.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void rotaryr2_cfg_setup ( rotaryr2_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->enb  = HAL_PIN_NC;
    cfg->ena  = HAL_PIN_NC;
    cfg->sw   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t rotaryr2_init ( rotaryr2_t *ctx, rotaryr2_cfg_t *cfg ) 
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

    digital_in_init( &ctx->enb, cfg->enb );
    digital_in_init( &ctx->ena, cfg->ena );
    digital_in_init( &ctx->sw, cfg->sw );

    return SPI_MASTER_SUCCESS;
}

err_t rotaryr2_default_cfg ( rotaryr2_t *ctx ) 
{
    return rotaryr2_set_led_data( ctx, DUMMY );
}

err_t rotaryr2_set_led_data ( rotaryr2_t *ctx, uint16_t led_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( led_data >> 8 );
    data_buf[ 1 ] = ( uint8_t )  led_data;
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return err_flag;
}

err_t rotaryr2_get_led_data ( rotaryr2_t *ctx, uint16_t *led_data ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t err_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *led_data = data_buf[ 0 ];
    *led_data <<= 8;
    *led_data |= data_buf[ 1 ];
    return err_flag;
}

err_t rotaryr2_set_led_pos ( rotaryr2_t *ctx, uint8_t led_pos ) 
{
    err_t err_flag = ROTARYR2_ERROR;
    if ( ( led_pos >= ROTARYR2_SET_LED_POS_1 ) || ( led_pos <= ROTARYR2_SET_LED_POS_16 ) )
    {
        err_flag = rotaryr2_set_led_data( ctx, ROTARYR2_SET_LED_POS_1 << ( led_pos - 1 ) );
    }
    return err_flag;
}

uint8_t rotaryr2_get_state_switch ( rotaryr2_t *ctx ) 
{
    return digital_in_read( &ctx->sw );
}

uint8_t rotaryr2_get_state_ena ( rotaryr2_t *ctx ) 
{
    return digital_in_read( &ctx->ena );
}

uint8_t rotaryr2_get_state_enb ( rotaryr2_t *ctx ) 
{
    return digital_in_read( &ctx->enb );
}

// ------------------------------------------------------------------------- END
