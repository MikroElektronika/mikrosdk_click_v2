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
 * @file angle6.c
 * @brief Angle 6 Click Driver.
 */

#include "angle6.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

void angle6_cfg_setup ( angle6_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->mgh = HAL_PIN_NC;
    cfg->pwm = HAL_PIN_NC;
    cfg->mgl = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t angle6_init ( angle6_t *ctx, angle6_cfg_t *cfg ) 
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

    digital_in_init( &ctx->mgh, cfg->mgh );
    digital_in_init( &ctx->pwm, cfg->pwm );
    digital_in_init( &ctx->mgl, cfg->mgl );

    return SPI_MASTER_SUCCESS;
}

err_t angle6_default_cfg ( angle6_t *ctx ) 
{
    err_t error_flag = ANGLE6_OK;
    
    error_flag |= angle6_write_register ( ctx, ANGLE6_REG_ROTATION_DIRECTION, ANGLE6_ROTATION_DIRECTION_CW );

    return error_flag;
}

err_t angle6_write_register ( angle6_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    if ( ( reg > ANGLE6_REG_MAGNETIC_FIELD_CONFIG ) && ( ANGLE6_REG_ROTATION_DIRECTION != reg ) )
    {
        return ANGLE6_ERROR;
    }
    uint8_t tx_buf[ 2 ] = { reg | ANGLE6_CMD_WRITE_REGISTER, data_in };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( tx_buf[ 1 ] != rx_buf[ 1 ] )
    {
        return ANGLE6_ERROR;
    }
    return error_flag;
}

err_t angle6_read_register ( angle6_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    if ( ( reg > ANGLE6_REG_MAGNETIC_FIELD_CONFIG ) && 
         ( ANGLE6_REG_ROTATION_DIRECTION != reg ) && ( ANGLE6_REG_ALARM_FLAGS != reg ) )
    {
        return ANGLE6_ERROR;
    }
    uint8_t tx_buf[ 2 ] = { reg | ANGLE6_CMD_READ_REGISTER, 0 };
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write ( &ctx->spi, tx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    *data_out = rx_buf[ 1 ];
    return error_flag;
}

err_t angle6_read_angle ( angle6_t *ctx, float *angle ) 
{
    uint8_t rx_buf[ 2 ] = { 0 };
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, rx_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    uint16_t raw_angle = ( ( uint16_t ) rx_buf[ 0 ] << 8 ) | rx_buf[ 1 ];
    *angle = ( ( float ) raw_angle / ANGLE6_RESOLUTION ) * ANGLE6_FULL_CIRCLE;
    return error_flag;
}

uint8_t angle6_get_pwm_pin ( angle6_t *ctx )
{
    return digital_in_read ( &ctx->pwm );
}

uint8_t angle6_get_mgh_pin ( angle6_t *ctx )
{
    return digital_in_read ( &ctx->mgh );
}

uint8_t angle6_get_mgl_pin ( angle6_t *ctx )
{
    return digital_in_read ( &ctx->mgl );
}

// ------------------------------------------------------------------------- END
