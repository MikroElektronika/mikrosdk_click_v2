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
 * @file magneticrotary4.c
 * @brief Magnetic Rotary 4 Click Driver.
 */

#include "magneticrotary4.h"

/**
 * @brief Two bytes to word macro.
 * @details Definition of two bytes to word conversion.
 */
#define TWO_BYTES_TO_WORD( x )  ( ( ( uint16_t ) x[ 0 ] << 8 ) | x[ 1 ] )  

/**
 * @brief Dummy data and SPI read bit.
 * @details Definition of dummy data and SPI read bit.
 */
#define DUMMY                   0xFF
#define SPI_READ_BIT            0x40

/**
 * @brief Magnetic Rotary 4 calculate parity bit function.
 * @details This function calculates the parity bit.
 * @param[in] ctx : Click context object.
 * See #magneticrotary4_t object definition for detailed explanation.
 * @param[in] data_in : Data from which it will calculate the parity bit.
 * @return @li @c  0 - Even parity,
 *         @li @c  1 - ODD parity.
 * @note None.
 */
static uint8_t magneticrotary4_calculate_parity_bit ( uint16_t data_in );

void magneticrotary4_cfg_setup ( magneticrotary4_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t magneticrotary4_init ( magneticrotary4_t *ctx, magneticrotary4_cfg_t *cfg ) 
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
    
    MAGNETICROTARY4_SET_DATA_SAMPLE_EDGE;
    
    return SPI_MASTER_SUCCESS;
}

err_t magneticrotary4_write_register ( magneticrotary4_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0x3F );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 0 ] |= ( magneticrotary4_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) << 7 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0x3F );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 0 ] |= ( magneticrotary4_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) << 7 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t magneticrotary4_read_register ( magneticrotary4_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0x3F ) | SPI_READ_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 0 ] |= ( magneticrotary4_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) << 7 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    if ( ( data_buf[ 0 ] >> 7 ) == magneticrotary4_calculate_parity_bit ( TWO_BYTES_TO_WORD ( data_buf ) ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return error_flag;
    }
    return MAGNETICROTARY4_ERROR;
}

err_t magneticrotary4_get_angle ( magneticrotary4_t *ctx, float *angle )
{
    uint16_t raw_data;
    if ( MAGNETICROTARY4_OK == magneticrotary4_read_register ( ctx, MAGNETICROTARY4_REG_ANGLECOM, &raw_data ) )
    {
        *angle = ( raw_data & MAGNETICROTARY4_DATA_RESOLUTION ) * 
                 ( float ) MAGNETICROTARY4_FULL_CIRCLE / MAGNETICROTARY4_DATA_RESOLUTION;
        return MAGNETICROTARY4_OK;
    }
    return MAGNETICROTARY4_ERROR;
}

err_t magneticrotary4_calibrate_zero_position ( magneticrotary4_t *ctx )
{
    err_t error_flag = MAGNETICROTARY4_OK;
    uint16_t raw_data = 0;
    error_flag |= magneticrotary4_write_register ( ctx, MAGNETICROTARY4_REG_ZPOSM, 0 );
    error_flag |= magneticrotary4_write_register ( ctx, MAGNETICROTARY4_REG_ZPOSL, 0 );
    Delay_100ms ( );
    while ( MAGNETICROTARY4_ERROR == magneticrotary4_read_register ( ctx, MAGNETICROTARY4_REG_ANGLEUNC, &raw_data ) )
    {
        Delay_10ms ( );
    }
    error_flag |= magneticrotary4_write_register ( ctx, MAGNETICROTARY4_REG_ZPOSM, ( raw_data >> 6 ) & 0xFF );
    error_flag |= magneticrotary4_write_register ( ctx, MAGNETICROTARY4_REG_ZPOSL, raw_data & 0x3F );
    Delay_100ms ( );
    return error_flag;
}

err_t magneticrotary4_set_rotation_direction ( magneticrotary4_t *ctx, uint8_t direction )
{
    if ( direction > MAGNETICROTARY4_DIRECTION_CCW )
    {
        return MAGNETICROTARY4_ERROR;
    }
    return magneticrotary4_write_register ( ctx, MAGNETICROTARY4_REG_SETTINGS1, direction << 2 );
}

static uint8_t magneticrotary4_calculate_parity_bit ( uint16_t data_in )
{
    uint8_t parity = 0;
    while ( data_in & 0x7FFF )
    {
        parity += ( data_in & MAGNETICROTARY4_ODD_PARITY );
        data_in >>= 1;
    }
    return parity & MAGNETICROTARY4_ODD_PARITY;
}

// ------------------------------------------------------------------------- END
