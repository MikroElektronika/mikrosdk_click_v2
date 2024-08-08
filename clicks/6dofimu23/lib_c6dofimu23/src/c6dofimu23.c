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
 * @file c6dofimu23.c
 * @brief 6DOF IMU 23 Click Driver.
 */

#include "c6dofimu23.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/**
 * @brief 6DOF IMU 23 calculate crc function.
 * @details This function calculates the CRC from input data buffer.
 * @param[in] data_in : Input data buffer.
 * @param[in] len : Data buffer len (fixed to 3-bytes in this library).
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t c6dofimu23_calculate_crc ( uint8_t *data_in, uint8_t len );

void c6dofimu23_cfg_setup ( c6dofimu23_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->odr  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c6dofimu23_init ( c6dofimu23_t *ctx, c6dofimu23_cfg_t *cfg ) 
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

    digital_in_init( &ctx->odr, cfg->odr );

    ctx->acc_fs = C6DOFIMU23_ACCEL_FS_DEFAULT;
    ctx->gyro_fs = C6DOFIMU23_GYRO_FS_DEFAULT;

    return SPI_MASTER_SUCCESS;
}

err_t c6dofimu23_default_cfg ( c6dofimu23_t *ctx ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    
    c6dofimu23_device_enable( ctx );
    Delay_100ms ( );

    if ( C6DOFIMU23_OK != c6dofimu23_check_communication ( ctx ) )
    {
        return C6DOFIMU23_ERROR;
    }

    return error_flag;
}

err_t c6dofimu23_reg_write ( c6dofimu23_t *ctx, uint8_t address, uint16_t data_in ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    uint8_t wr_buf[ 4 ] = { 0 };
    uint8_t rd_buf[ 4 ] = { 0 };
    wr_buf[ 0 ] = ( address << 2 ) | 0x80;
    wr_buf[ 1 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    wr_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    wr_buf[ 3 ] = c6dofimu23_calculate_crc ( wr_buf, 3 );
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, wr_buf[ 0 ] );
    error_flag = spi_master_read( &ctx->spi, &rd_buf[ 0 ], 1 );
    if ( C6DOFIMU23_OK == error_flag )
    {
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 1 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 1 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 2 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 2 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 3 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 3 ], 1 );
        if ( rd_buf[ 3 ] != c6dofimu23_calculate_crc ( rd_buf, 3 ) )
        {
            error_flag |= C6DOFIMU23_ERROR;
        }
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c6dofimu23_reg_read ( c6dofimu23_t *ctx, uint8_t address, uint16_t *data_out ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    uint8_t wr_buf[ 4 ] = { 0 };
    uint8_t rd_buf[ 4 ] = { 0 };
    wr_buf[ 0 ] = ( address << 2 ) & 0x7F;
    wr_buf[ 1 ] = DUMMY;
    wr_buf[ 2 ] = DUMMY;
    wr_buf[ 3 ] = c6dofimu23_calculate_crc ( wr_buf, 3 );
    spi_master_select_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, wr_buf[ 0 ] );
    if ( C6DOFIMU23_OK == spi_master_read( &ctx->spi, &rd_buf[ 0 ], 1 ) )
    {
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 1 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 1 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 2 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 2 ], 1 );
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 3 ] );
        error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 3 ], 1 );
        if ( rd_buf[ 3 ] != c6dofimu23_calculate_crc ( rd_buf, 3 ) )
        {
            error_flag |= C6DOFIMU23_ERROR;
        }
    }
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    spi_master_deselect_device( ctx->chip_select );

    if ( C6DOFIMU23_OK == error_flag )
    {
        Delay_1ms ( );
        spi_master_select_device( ctx->chip_select );
        spi_master_set_default_write_data( &ctx->spi, wr_buf[ 0 ] );
        if ( C6DOFIMU23_OK == spi_master_read( &ctx->spi, &rd_buf[ 0 ], 1 ) )
        {
            spi_master_set_default_write_data( &ctx->spi, wr_buf[ 1 ] );
            error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 1 ], 1 );
            spi_master_set_default_write_data( &ctx->spi, wr_buf[ 2 ] );
            error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 2 ], 1 );
            spi_master_set_default_write_data( &ctx->spi, wr_buf[ 3 ] );
            error_flag |= spi_master_read( &ctx->spi, &rd_buf[ 3 ], 1 );
            if ( rd_buf[ 3 ] != c6dofimu23_calculate_crc ( rd_buf, 3 ) )
            {
                error_flag |= C6DOFIMU23_ERROR;
            }
            if ( 0x01 != ( rd_buf[ 0 ] & 0x03 ) )
            {
                error_flag |= C6DOFIMU23_ERROR;
            }
        }
        spi_master_set_default_write_data( &ctx->spi, DUMMY );
        spi_master_deselect_device( ctx->chip_select );
    }
    if ( C6DOFIMU23_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) rd_buf[ 1 ] << 8 ) | rd_buf[ 2 ];
    }
    return error_flag;
}

err_t c6dofimu23_check_communication ( c6dofimu23_t *ctx )
{
    uint16_t fixed_value = 0;
    if ( C6DOFIMU23_OK == c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_FIXED_VALUE, &fixed_value ) )
    {
        if ( C6DOFIMU23_FIXED_VALUE == fixed_value )
        {
            return C6DOFIMU23_OK;
        }
    }
    return C6DOFIMU23_ERROR;
}

void c6dofimu23_device_enable ( c6dofimu23_t *ctx ) 
{
    digital_out_high( &ctx->rst );
}

void c6dofimu23_device_disable ( c6dofimu23_t *ctx ) 
{
    digital_out_low( &ctx->rst );
}

uint8_t c6dofimu23_get_odr ( c6dofimu23_t *ctx ) 
{
    return digital_in_read( &ctx->odr );
}

err_t c6dofimu23_get_accel_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *acc_axis ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    uint16_t reg_data = 0;

    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_ACCEL_X_DATA, &reg_data );

    acc_axis->x = ( int16_t ) reg_data;
    acc_axis->x *= ctx->acc_fs;
    acc_axis->x /= C6DOFIMU23_DATA_RESOLUTION;

    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_ACCEL_Y_DATA, &reg_data );

    acc_axis->y = ( int16_t ) reg_data;
    acc_axis->y *= ctx->acc_fs;
    acc_axis->y /= C6DOFIMU23_DATA_RESOLUTION;
    
    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_ACCEL_Z_DATA, &reg_data );

    acc_axis->z = ( int16_t ) reg_data;
    acc_axis->z *= ctx->acc_fs;
    acc_axis->z /= C6DOFIMU23_DATA_RESOLUTION;

    return error_flag;
}

err_t c6dofimu23_get_gyro_data ( c6dofimu23_t *ctx, c6dofimu23_axis_t *gyro_axis ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    uint16_t reg_data = 0;

    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_X_DATA, &reg_data );

    gyro_axis->x = ( int16_t ) reg_data;
    gyro_axis->x *= ctx->gyro_fs;
    gyro_axis->x /= C6DOFIMU23_DATA_RESOLUTION;

    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_Y_DATA, &reg_data );

    gyro_axis->y = ( int16_t ) reg_data;
    gyro_axis->y *= ctx->gyro_fs;
    gyro_axis->y /= C6DOFIMU23_DATA_RESOLUTION;
    
    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_Z_DATA, &reg_data );

    gyro_axis->z = ( int16_t ) reg_data;
    gyro_axis->z *= ctx->gyro_fs;
    gyro_axis->z /= C6DOFIMU23_DATA_RESOLUTION;

    return error_flag;
}

err_t c6dofimu23_get_temperature ( c6dofimu23_t *ctx, float *temperature ) 
{
    err_t error_flag = C6DOFIMU23_OK;
    uint16_t reg_data = 0;

    error_flag |= c6dofimu23_reg_read ( ctx, C6DOFIMU23_OFFSET_TEMPERATURE_1, &reg_data );

    *temperature = ( int16_t ) reg_data;
    *temperature /= C6DOFIMU23_TEMP_DATA_RESOLUTION;
    *temperature += C6DOFIMU23_TEMP_DATA_OFFSET;

    return error_flag;
}

static uint8_t c6dofimu23_calculate_crc ( uint8_t *data_in, uint8_t len )
{
    uint8_t crc = 0xFF;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    uint8_t curr_byte = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ )
    {
        curr_byte = data_in[ byte_cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ )
        {
            if ( crc & 0x80 )
            {
                crc <<= 1;
                crc |= ( ( curr_byte >> 7 ) & 0x01 );
                crc ^= 0x1D;
            }
            else
            {
                crc <<= 1;
                crc |= ( ( curr_byte >> 7 ) & 0x01 );
            }
            curr_byte <<= 1;
        }
    }
    return crc ^ 0xFF;
}

// ------------------------------------------------------------------------- END
