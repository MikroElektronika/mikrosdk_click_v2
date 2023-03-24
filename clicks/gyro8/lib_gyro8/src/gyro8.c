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
 * @file gyro8.c
 * @brief Gyro 8 Click Driver.
 */

#include "gyro8.h"

/**
 * @brief Dummy data and SPI read bit.
 * @details Definition of dummy data and SPI read bit.
 */
#define DUMMY                       0x00
#define GYRO8_SPI_READ_WRITE_BIT    0x80

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x1D (x4 + x3 + x2 + 1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0xFF
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t gyro8_calculate_crc( uint8_t *data_buf, uint8_t len );

void gyro8_cfg_setup ( gyro8_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t gyro8_init ( gyro8_t *ctx, gyro8_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    return SPI_MASTER_SUCCESS;
}

err_t gyro8_default_cfg ( gyro8_t *ctx ) 
{
    gyro8_reset_device ( ctx );
    if ( GYRO8_ERROR == gyro8_check_communication ( ctx ) )
    {
        return GYRO8_ERROR;
    }
    return GYRO8_OK;
}

err_t gyro8_write_register ( gyro8_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = GYRO8_SPI_READ_WRITE_BIT | ( ( reg & 0x1F ) << 2 );
    data_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = gyro8_calculate_crc ( data_buf, 3 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t gyro8_read_register ( gyro8_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = ( ( reg & 0x1F ) << 2 );
    data_buf[ 1 ] = DUMMY;
    data_buf[ 2 ] = DUMMY;
    data_buf[ 3 ] = gyro8_calculate_crc ( data_buf, 3 );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_write( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 4 );
    spi_master_deselect_device( ctx->chip_select );
    if ( data_buf[ 3 ] != gyro8_calculate_crc ( data_buf, 3 ) )
    {
        return GYRO8_ERROR;
    }
    *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 2 ];
    return error_flag;
}

void gyro8_set_rst_pin ( gyro8_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void gyro8_reset_device ( gyro8_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

err_t gyro8_check_communication ( gyro8_t *ctx )
{
    uint16_t product_id;
    if ( GYRO8_OK == gyro8_read_register ( ctx, GYRO8_REG_ID, &product_id ) )
    {
        if ( GYRO8_ID == product_id )
        {
            return GYRO8_OK;
        }
    }
    return GYRO8_ERROR;
}

err_t gyro8_read_serial_id ( gyro8_t *ctx, uint32_t *serial_id )
{
    uint16_t serial_id0, serial_id1;
    if ( GYRO8_ERROR == gyro8_read_register ( ctx, GYRO8_REG_SERIAL_ID0, &serial_id0 ) )
    {
        return GYRO8_ERROR;
    }
    if ( GYRO8_ERROR == gyro8_read_register ( ctx, GYRO8_REG_SERIAL_ID1, &serial_id1 ) )
    {
        return GYRO8_ERROR;
    }
    *serial_id = ( ( uint32_t ) serial_id1 << 16 ) | serial_id0;
    return GYRO8_OK;
}

err_t gyro8_read_temperature ( gyro8_t *ctx, float *temperature )
{
    uint16_t raw_temp;
    if ( GYRO8_ERROR == gyro8_read_register ( ctx, GYRO8_REG_TEMP, &raw_temp ) )
    {
        return GYRO8_ERROR;
    }
    *temperature = GYRO8_TEMP_OFFSET + ( ( int16_t ) raw_temp ) / GYRO8_TEMP_SENS;
    return GYRO8_OK;
}

err_t gyro8_read_angular_rate ( gyro8_t *ctx, float *rate )
{
    uint16_t raw_rate;
    if ( GYRO8_ERROR == gyro8_read_register ( ctx, GYRO8_REG_RATE, &raw_rate ) )
    {
        return GYRO8_ERROR;
    }
    *rate = ( ( int16_t ) raw_rate ) / GYRO8_GYRO_SENS;
    return GYRO8_OK;
}

static uint8_t gyro8_calculate_crc( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0xFF;
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
