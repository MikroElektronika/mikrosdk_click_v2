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
 * @file magneticrotary3.c
 * @brief Magnetic Rotary 3 Click Driver.
 */

#include "magneticrotary3.h"

/**
 * @brief Dummy data and SPI read bit.
 * @details Definition of dummy data and SPI read bit.
 */
#define DUMMY           0x00
#define DUMMY_CRC       0xF1
#define SPI_READ_BIT    0x40

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D (x4 + x3 + x2 + 1)
 * @li @c  Initialization 0xC4
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0xFF
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t magneticrotary3_calculate_crc( uint8_t *data_buf, uint8_t len );

void magneticrotary3_cfg_setup ( magneticrotary3_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t magneticrotary3_init ( magneticrotary3_t *ctx, magneticrotary3_cfg_t *cfg ) 
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
    
    MAGNETICROTARY3_SET_DATA_SAMPLE_EDGE;

    return SPI_MASTER_SUCCESS;
}

err_t magneticrotary3_write_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0x3F ) & ( ~SPI_READ_BIT );
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 2 ] = magneticrotary3_calculate_crc ( data_buf, 2 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    data_buf[ 0 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = magneticrotary3_calculate_crc ( data_buf, 2 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t magneticrotary3_read_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( reg >> 8 ) & 0x3F ) | SPI_READ_BIT;
    data_buf[ 1 ] = ( uint8_t ) ( reg & 0xFF );
    data_buf[ 2 ] = magneticrotary3_calculate_crc ( data_buf, 2 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 3 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY_CRC );
    error_flag |= spi_master_read( &ctx->spi, &data_buf[ 2 ], 1 );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    if ( data_buf[ 2 ] == magneticrotary3_calculate_crc ( data_buf, 2 ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return error_flag;
    }
    return MAGNETICROTARY3_ERROR;
}

err_t magneticrotary3_get_angle ( magneticrotary3_t *ctx, float *angle )
{
    uint16_t raw_data;
    if ( MAGNETICROTARY3_OK == magneticrotary3_read_register ( ctx, MAGNETICROTARY3_REG_ANGLECOM, &raw_data ) )
    {
        *angle = ( raw_data & MAGNETICROTARY3_DATA_RESOLUTION ) * 
                 ( float ) MAGNETICROTARY3_FULL_CIRCLE / MAGNETICROTARY3_DATA_RESOLUTION;
        return MAGNETICROTARY3_OK;
    }
    return MAGNETICROTARY3_ERROR;
}

static uint8_t magneticrotary3_calculate_crc( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xC4;
    for ( uint8_t byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {    
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x1D );
            }
            else
            {
                crc <<= 1;
            }    
        }
    }
    return crc ^ 0xFF;
}

// ------------------------------------------------------------------------- END
