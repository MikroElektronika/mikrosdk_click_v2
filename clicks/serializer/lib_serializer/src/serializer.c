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
 * @file serializer.c
 * @brief Serializer Click Driver.
 */

#include "serializer.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Calculation of CRC-5-ITU function.
 * @details This function calculates CRC-5-ITU with parameteres: 
 * @li @c  Width 5 bit
 * @li @c  Polynomial 0x15 (x5 + x4 + x2 + 1)
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t serializer_calculate_crc( uint8_t *data_buf, uint8_t len );

void serializer_cfg_setup ( serializer_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->flt  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t serializer_init ( serializer_t *ctx, serializer_cfg_t *cfg ) 
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

    digital_in_init( &ctx->flt, cfg->flt );

    return SPI_MASTER_SUCCESS;
}

uint8_t serializer_get_flt_pin ( serializer_t *ctx )
{
    return digital_in_read ( &ctx->flt );
}

err_t serializer_read_input ( serializer_t *ctx, uint8_t *data_out ) 
{
    uint8_t data_buf[ 2 ] = { 0 };
    uint8_t status = 0;
    uint8_t crc = 0;
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, data_buf, 2 );
    spi_master_deselect_device( ctx->chip_select );
    
    crc = data_buf[ 1 ] >> 3;
    status = ( data_buf[ 1 ] >> 1 ) & 0x03;
    
    if ( ( SERIALIZER_OK == error_flag ) &&
         ( serializer_calculate_crc ( data_buf, 1 ) == crc ) )
    {
        *data_out = data_buf[ 0 ];
        return status;
    }
    return SERIALIZER_ERROR;
}

static uint8_t serializer_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    uint8_t poly = 0x15;
    
    for ( uint8_t i = 0; i < len; i++ ) 
    {
        crc ^= data_buf[ i ];
        for ( uint8_t j = 0; j < 8; j++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {    
                crc = ( uint8_t )( ( crc << 1 ) ^ ( poly << 3 ) );
            }
            else
            {
                 crc <<= 1;
            }    
        }
    }
    crc >>= 3;
    return crc;
}


// ------------------------------------------------------------------------- END
