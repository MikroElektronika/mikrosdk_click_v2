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
 * @file angle9.c
 * @brief Angle 9 Click Driver.
 */

#include "angle9.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief Angle 9 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #angle9_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t angle9_calculate_parity_bit ( uint16_t data_in );

void angle9_cfg_setup ( angle9_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->pwm  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_3;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t angle9_init ( angle9_t *ctx, angle9_cfg_t *cfg ) 
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

    digital_in_init( &ctx->pwm, cfg->pwm );

    return SPI_MASTER_SUCCESS;
}

err_t angle9_write_register ( angle9_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( reg > ANGLE9_REG_KEY ) || ( reg % 2 ) )
    {
        return ANGLE9_ERROR;
    }
    data_buf[ 0 ] = reg | ANGLE9_WRITE_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    data_buf[ 0 ] = ( reg + 1 ) | ANGLE9_WRITE_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t angle9_read_register ( angle9_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ( reg > ANGLE9_REG_KEY ) || ( reg % 2 ) )
    {
        return ANGLE9_ERROR;
    }
    data_buf[ 0 ] = reg;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ANGLE9_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

uint8_t angle9_get_pwm_pin ( angle9_t *ctx )
{
    return digital_in_read ( &ctx->pwm );
}

err_t angle9_read_angle ( angle9_t *ctx, float *angle )
{
    uint16_t raw_angle = 0;
    err_t error_flag = angle9_read_register ( ctx, ANGLE9_REG_ANG, &raw_angle );
    if ( ( ( raw_angle >> 12 ) & ANGLE9_ODD_PARITY ) != angle9_calculate_parity_bit ( raw_angle ) )
    {
        error_flag = ANGLE9_ERROR;
    }
    if ( ANGLE9_OK == error_flag )
    {
        *angle = ( float ) ( raw_angle & ANGLE9_DATA_RESOLUTION ) * ANGLE9_FULL_CIRCLE / ANGLE9_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t angle9_read_temperature ( angle9_t *ctx, float *temperature )
{
    int16_t signed_raw_temp = 0;
    err_t error_flag = angle9_read_register ( ctx, ANGLE9_REG_TSEN, ( uint16_t * ) &signed_raw_temp );
    if ( ANGLE9_OK == error_flag )
    {
        signed_raw_temp = ( signed_raw_temp & ANGLE9_DATA_RESOLUTION );
        signed_raw_temp <<= 4;
        signed_raw_temp >>= 4;
        *temperature = signed_raw_temp / ANGLE9_TEMP_RESOLUTION + ANGLE9_TEMP_OFFSET;
    }
    return error_flag;
}

err_t angle9_read_field_strength ( angle9_t *ctx, uint16_t *field_str )
{
    uint16_t raw_field = 0;
    err_t error_flag = angle9_read_register ( ctx, ANGLE9_REG_FIELD, &raw_field );
    if ( ANGLE9_OK == error_flag )
    {
        *field_str = raw_field & ANGLE9_DATA_RESOLUTION;
    }
    return error_flag;
}

static uint8_t angle9_calculate_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;
    for ( uint8_t cnt = 0; cnt < 16; cnt++ )
    {
        parity += ( ( data_in >> cnt ) & ANGLE9_ODD_PARITY );
    }
    return parity & ANGLE9_ODD_PARITY;
}

// ------------------------------------------------------------------------- END
