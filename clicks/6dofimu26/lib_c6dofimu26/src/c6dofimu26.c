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
 * @file c6dofimu26.c
 * @brief 6DOF IMU 26 Click Driver.
 */

#include "c6dofimu26.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY  0x00

/** 
 * @brief Calculation for CRC 8 function.
 * @details This function calculates CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x2F (x8 + x5 + x3 + x2 + x + 1 )
 * @li @c  Initialization 0x42
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated CRC.
 * @note None.
 */
static uint8_t c6dofimu26_calc_crc8 ( uint8_t *data_buf, uint8_t len );

void c6dofimu26_cfg_setup ( c6dofimu26_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->rst  = HAL_PIN_NC;
    cfg->dry  = HAL_PIN_NC;

    cfg->spi_speed   = 1000000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t c6dofimu26_init ( c6dofimu26_t *ctx, c6dofimu26_cfg_t *cfg ) 
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

    digital_in_init( &ctx->dry, cfg->dry );

    return SPI_MASTER_SUCCESS;
}

err_t c6dofimu26_default_cfg ( c6dofimu26_t *ctx ) 
{
    err_t error_flag = C6DOFIMU26_OK;
    c6dofimu26_reset_device ( ctx );
    if ( C6DOFIMU26_ERROR == c6dofimu26_check_communication ( ctx ) )
    {
        return C6DOFIMU26_ERROR;
    }
    // Enable sensor
    error_flag |= c6dofimu26_write_reg ( ctx, C6DOFIMU26_REG_CTRL_MODE, C6DOFIMU26_CTRL_MODE_EN_SENSOR );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    // End of initialization
    error_flag |= c6dofimu26_write_reg ( ctx, C6DOFIMU26_REG_CTRL_MODE, C6DOFIMU26_CTRL_MODE_EOI_CTRL );
    Delay_100ms ( );
    return error_flag;
}

err_t c6dofimu26_write_reg ( c6dofimu26_t *ctx, uint8_t reg, uint32_t data_in )
{
    err_t error_flag = C6DOFIMU26_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    uint16_t reg_adr = 0;
    if ( ( reg < C6DOFIMU26_REG_CTRL_FILT_RATE ) || ( reg > C6DOFIMU26_REG_SYS_TEST ) )
    {
        return C6DOFIMU26_ERROR;
    }
    reg_adr = reg | ( ( uint16_t ) C6DOFIMU26_ADDRESS << 8 );
    data_buf[ 0 ] = ( uint8_t ) ( ( reg_adr >> 2 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg_adr << 6 ) & 0xC0 ) | C6DOFIMU26_RW_BIT | C6DOFIMU26_FT_48_BIT;
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 16 ) & 0x0F );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 4 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 5 ] = c6dofimu26_calc_crc8 ( data_buf, 5 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 6 );
    spi_master_deselect_device( ctx->chip_select );
    return error_flag;
}

err_t c6dofimu26_read_reg ( c6dofimu26_t *ctx, uint8_t reg, uint32_t *data_out )
{
    err_t error_flag = C6DOFIMU26_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    uint16_t reg_adr = 0;
    uint16_t read_reg_adr = 0;
    if ( ( reg < C6DOFIMU26_REG_RATE_X1 ) || ( reg > C6DOFIMU26_REG_SN_ID3 ) )
    {
        return C6DOFIMU26_ERROR;
    }
    reg_adr = reg | ( ( uint16_t ) C6DOFIMU26_ADDRESS << 8 );
    data_buf[ 0 ] = ( uint8_t ) ( ( reg_adr >> 2 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( reg_adr << 6 ) & 0xC0 ) | C6DOFIMU26_FT_48_BIT;
    data_buf[ 2 ] = DUMMY;
    data_buf[ 3 ] = DUMMY;
    data_buf[ 4 ] = DUMMY;
    data_buf[ 5 ] = c6dofimu26_calc_crc8 ( data_buf, 5 );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_write( &ctx->spi, data_buf, 6 );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_select_device( ctx->chip_select );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 6 );
    spi_master_deselect_device( ctx->chip_select );
    if ( C6DOFIMU26_OK == error_flag )
    {
        read_reg_adr = ( ( uint16_t ) ( data_buf[ 0 ] & 0x7F ) << 3 ) | ( data_buf[ 1 ] >> 5 );
        if ( ( read_reg_adr != reg_adr ) || 
             ( data_buf[ 5 ] != c6dofimu26_calc_crc8 ( data_buf, 5 ) ) ||
             ( ( reg <= C6DOFIMU26_REG_TEMP ) && ( !( data_buf[ 0 ] & C6DOFIMU26_D_BIT ) ) ) || 
             ( ( reg > C6DOFIMU26_REG_TEMP ) && ( ( data_buf[ 0 ] & C6DOFIMU26_D_BIT ) ) ) )
        {
            error_flag |= C6DOFIMU26_ERROR;
        }
    }
    if ( ( C6DOFIMU26_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( uint32_t ) ( data_buf[ 2 ] & 0x0F ) << 16 ) | 
                    ( ( uint16_t ) data_buf[ 3 ] << 8 ) | 
                    data_buf[ 4 ];
    }
    return error_flag;
}

void c6dofimu26_set_rst_pin ( c6dofimu26_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t c6dofimu26_get_dry_pin ( c6dofimu26_t *ctx )
{
    return digital_in_read ( &ctx->dry );
}

void c6dofimu26_reset_device ( c6dofimu26_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

err_t c6dofimu26_check_communication ( c6dofimu26_t *ctx )
{
    uint32_t sys_test = 0;
    if ( C6DOFIMU26_OK == c6dofimu26_write_reg ( ctx, C6DOFIMU26_REG_SYS_TEST, C6DOFIMU26_SYS_TEST ) )
    {
        if ( C6DOFIMU26_OK == c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_SYS_TEST, &sys_test ) )
        {
            if ( C6DOFIMU26_SYS_TEST == sys_test )
            {
                return C6DOFIMU26_OK;
            }
        }
    }
    return C6DOFIMU26_ERROR;
}

err_t c6dofimu26_get_accel ( c6dofimu26_t *ctx, c6dofimu26_axes_t *accel )
{
    err_t error_flag = C6DOFIMU26_OK;
    uint32_t reg_data = 0;
    int32_t raw_data = 0;
    if ( NULL == accel )
    {
        error_flag = C6DOFIMU26_ERROR;
    }

    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_ACC_X1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        accel->x = ( float ) raw_data / C6DOFIMU26_ACCEL_LSB_RES / C6DOFIMU26_ACCEL_M_S2_TO_G;
    }
    
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_ACC_Y1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        accel->y = ( float ) raw_data / C6DOFIMU26_ACCEL_LSB_RES / C6DOFIMU26_ACCEL_M_S2_TO_G;
    }
    
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_ACC_Z1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        accel->z = ( float ) raw_data / C6DOFIMU26_ACCEL_LSB_RES / C6DOFIMU26_ACCEL_M_S2_TO_G;
    }
    return error_flag;
}

err_t c6dofimu26_get_gyro ( c6dofimu26_t *ctx, c6dofimu26_axes_t *gyro )
{
    err_t error_flag = C6DOFIMU26_OK;
    uint32_t reg_data = 0;
    int32_t raw_data = 0;
    if ( NULL == gyro )
    {
        error_flag = C6DOFIMU26_ERROR;
    }
    
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_RATE_X1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        gyro->x = ( float ) raw_data / C6DOFIMU26_GYRO_LSB_RES;
    }
    
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_RATE_Y1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        gyro->y = ( float ) raw_data / C6DOFIMU26_GYRO_LSB_RES;
    }
    
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_RATE_Z1, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 12;
        gyro->z = ( float ) raw_data / C6DOFIMU26_GYRO_LSB_RES;
    }
    return error_flag;
}

err_t c6dofimu26_get_temp ( c6dofimu26_t *ctx, float *temp )
{
    err_t error_flag = C6DOFIMU26_OK;
    uint32_t reg_data = 0;
    int32_t raw_data = 0;
    if ( NULL == temp )
    {
        error_flag = C6DOFIMU26_ERROR;
    }

    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag |= c6dofimu26_read_reg ( ctx, C6DOFIMU26_REG_TEMP, &reg_data );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        raw_data = reg_data << 12;
        raw_data >>= 16;
        *temp = ( float ) raw_data / C6DOFIMU26_TEMP_LSB_RES;
    }
    return error_flag;
}

err_t c6dofimu26_get_data ( c6dofimu26_t *ctx, c6dofimu26_data_t *data_out )
{
    err_t error_flag = C6DOFIMU26_OK;
    if ( NULL == data_out )
    {
        error_flag = C6DOFIMU26_ERROR;
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag = c6dofimu26_get_temp ( ctx, &data_out->temperature );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag = c6dofimu26_get_accel ( ctx, &data_out->accel );
    }
    if ( C6DOFIMU26_OK == error_flag )
    {
        error_flag = c6dofimu26_get_gyro ( ctx, &data_out->gyro );
    }
    return error_flag;
}

static uint8_t c6dofimu26_calc_crc8 ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x42;
    uint8_t cnt_0 = 0;
    uint8_t cnt_1 = 0;
    
    for ( cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        crc ^= data_buf[ cnt_0 ];
        for ( cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ 0x2F );
            }
            else 
            {
                crc = ( uint8_t ) ( crc << 1 );
            }
        }
    }
    
    return crc;
}

// ------------------------------------------------------------------------- END
