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
 * @file inclinometer.c
 * @brief Inclinometer Click Driver.
 */

#include "inclinometer.h"

/**
 * @brief Driver helping macros.
 * @details Definition of driver helping macros.
 */
#define DUMMY               0x00
#define WRITE_BIT           0x80
#define TEMPERATURE_RES     18.9
#define TEMPERATURE_OFFSET  -273
#define ANGLE_RES1          16384.0
#define ANGLE_RES2          90.0
#define RESOLUTION_MODE1    6000.0
#define RESOLUTION_MODE2    3000.0
#define RESOLUTION_MODE34   12000.0

/**
 * @brief Calculate CRC for 4 byte data.
 * @details This function returns crc byte for input data.
 * @param[in] data_val : Data to calculate CRC for.
 * @return CRC data
 * @note Calculate CRC for 24 MSB's of the 32 bit dword (8 LSB's 
 * are the CRC field and are not included in CRC calculation).
 */
static uint8_t inclinometer_calculate_crc ( uint32_t data_val );

/**
 * @brief Calculate CRC for bit and current crc data.
 * @details This function returns crc byte for 
 * input bit and current crc data value.
 * @param[in] bit_value : Bit value.
 * @param[in] crc : Current CRC value.
 * @return CRC data
 */
static uint8_t inclinometer_crc8 ( uint8_t bit_value, uint8_t crc );

/**
 * @brief Write of 4 bytes data.
 * @details This function writes 4 bytes of @b raw_val data.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] cmd : Input write data.
 * @param[out] raw_val : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t inclinometer_raw_write ( inclinometer_t *ctx, uint32_t raw_val );

/**
 * @brief Transfer of 4 bytes data.
 * @details This function writes 4 bytes of @b cmd data and reads 
 * output and places data int @b raw_val.
 * @param[in] ctx : Click context object.
 * See #inclinometer_t object definition for detailed explanation.
 * @param[in] cmd : Input write data.
 * @param[out] raw_val : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t inclinometer_raw_read ( inclinometer_t *ctx, uint32_t cmd, uint32_t *raw_val);

/**
 * @brief Get resolution for mode value.
 * @details This function returns resolution for parameter mode selected.
 * @param[in] mode : Device mode.
 * @return Resolution value
 */
static float inclinometer_resolution ( uint8_t mode );

void inclinometer_cfg_setup ( inclinometer_cfg_t *cfg ) 
{
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_0;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;
}

err_t inclinometer_init ( inclinometer_t *ctx, inclinometer_cfg_t *cfg ) 
{
    spi_master_config_t spi_cfg;

    spi_master_configure_default( &spi_cfg );

    spi_cfg.sck  = cfg->sck;
    spi_cfg.miso = cfg->miso;
    spi_cfg.mosi = cfg->mosi;

    ctx->chip_select = cfg->cs;

    if ( spi_master_open( &ctx->spi, &spi_cfg ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_default_write_data( &ctx->spi, DUMMY ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_mode( &ctx->spi, cfg->spi_mode ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    if ( spi_master_set_speed( &ctx->spi, cfg->spi_speed ) == SPI_MASTER_ERROR ) 
    {
        return SPI_MASTER_ERROR;
    }

    spi_master_set_chip_select_polarity( cfg->cs_polarity );
    spi_master_deselect_device( ctx->chip_select );

    ctx->resolution = 0;

    return SPI_MASTER_SUCCESS;
}

err_t inclinometer_default_cfg ( inclinometer_t *ctx ) 
{
    uint16_t temp_data;
    inclinometer_raw_write( ctx, INCLINOMETER_CMD_WAKE_UP );
    Delay_1ms( );
    inclinometer_raw_write( ctx, INCLINOMETER_CMD_SW_RESET );
    Delay_1ms( );
    inclinometer_raw_write( ctx, INCLINOMETER_CMD_CHANGE_TO_MODE1 );
    Delay_10ms( );
    Delay_10ms( );
    Delay_5ms( );
    inclinometer_generic_read( ctx, INCLINOMETER_REG_STATUS, &temp_data );
    inclinometer_generic_read( ctx, INCLINOMETER_REG_STATUS, &temp_data );
    inclinometer_generic_read( ctx, INCLINOMETER_REG_STATUS, &temp_data );

    inclinometer_raw_write( ctx, INCLINOMETER_CMD_EN_ANGLE_OUT );

    inclinometer_generic_read( ctx, INCLINOMETER_REG_WHOAMI, &temp_data );
    inclinometer_generic_read( ctx, INCLINOMETER_REG_WHOAMI, &temp_data );

    err_t ret_val = INCLINOMETER_OK;

    if ( 0xC1 != temp_data )
    {
        ret_val = INCLINOMETER_ERROR;
    }

    return INCLINOMETER_OK;
}

err_t inclinometer_generic_write ( inclinometer_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t tx_buf[ 4 ] = { 0 };
    uint8_t write_reg = reg& 0x1F;
    tx_buf[ 0 ] = write_reg << 2 | WRITE_BIT;
    tx_buf[ 1 ] = data_in >> 8;
    tx_buf[ 2 ] = data_in;
    tx_buf[ 3 ] = inclinometer_calculate_crc( ( ( uint32_t )tx_buf[ 0 ] << 24 ) | ( ( uint32_t )data_in << 8 ) );

    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_select_device( ctx->chip_select );
    err_t error_flag = spi_master_read( &ctx->spi, &ctx->rs, 1 );
    error_flag |= spi_master_write( &ctx->spi, &tx_buf[ 1 ], 3 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    Delay_10us( );
    ctx->rs &= 0x3;
    return error_flag;
}

err_t inclinometer_generic_read ( inclinometer_t *ctx, uint8_t reg, uint16_t *data_out )
{
    uint8_t write_reg = ( reg & 0x1F ) << 2;
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t dummy = 0;
    uint8_t crc = inclinometer_calculate_crc( ( ( uint32_t )write_reg << 24 ) );

    spi_master_select_device( ctx->chip_select );

    spi_master_set_default_write_data( &ctx->spi, write_reg );
    err_t error_flag = spi_master_read( &ctx->spi, &ctx->rs, 1 );

    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    error_flag |= spi_master_read( &ctx->spi, data_buf, 2 );

    spi_master_set_default_write_data( &ctx->spi, crc );
    error_flag = spi_master_read( &ctx->spi, &dummy, 1 );

    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );

    *data_out = ( ( uint16_t )data_buf[ 0 ] << 8 ) | data_buf[ 1 ];

    if ( data_buf[ 2 ]  != inclinometer_calculate_crc( ( ( uint32_t )ctx->rs << 24 ) | ( ( uint32_t )*data_out << 8 ) ) )
    {
        error_flag = INCLINOMETER_CRC_ERROR;
    }
    Delay_10us( );
    ctx->rs &= 0x3;
    return error_flag;
}

err_t inclinometer_cmd_write ( inclinometer_t *ctx, uint32_t cmd )
{
    return inclinometer_raw_write( ctx, cmd );
}

err_t inclinometer_cmd_read ( inclinometer_t *ctx, uint32_t cmd, uint16_t *cmd_data )
{
    uint32_t temp_data = 0;
    err_t ret_val = inclinometer_raw_read( ctx, cmd, &temp_data );
    *cmd_data = temp_data >> 8;
    ctx->rs = temp_data >> 24;
    ctx->rs &= 0x3;
    return ret_val;
}

err_t inclinometer_get_temperature ( inclinometer_t *ctx, float *temperature )
{
    err_t ret_val = INCLINOMETER_OK;
    uint16_t temp = 0;
    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_TEMP, &temp );
    *temperature = TEMPERATURE_OFFSET + ( temp / TEMPERATURE_RES );

    return ret_val;
}

err_t inclinometer_get_axes ( inclinometer_t *ctx, inclinometer_accel_t *axes_data )
{
    err_t ret_val = INCLINOMETER_OK;
    uint16_t temp = 0;

    if ( 0 == ctx->resolution )
    {
        ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_MODE, &temp );
        ctx->resolution = inclinometer_resolution( temp & 3 );
    }

    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ACC_X, &temp );
    axes_data->x = ( int16_t )temp / ctx->resolution;

    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ACC_Y, &temp );
    axes_data->y = ( int16_t )temp / ctx->resolution;

    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ACC_Z, &temp );
    axes_data->z = ( int16_t )temp / ctx->resolution;

    return ret_val;
}

err_t inclinometer_get_angle ( inclinometer_t *ctx, inclinometer_accel_t *angle_data )
{
    err_t ret_val = INCLINOMETER_OK;
    uint16_t temp;
    float angle;
    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ANG_X, &temp );
    angle_data->x = ( int16_t )temp / ANGLE_RES1 * ANGLE_RES2;
    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ANG_Y, &temp );
    angle_data->y = ( int16_t )temp / ANGLE_RES1 * ANGLE_RES2;
    ret_val |= inclinometer_cmd_read( ctx, INCLINOMETER_CMD_READ_ANG_Z, &temp );
    angle_data->z = ( int16_t )temp / ANGLE_RES1 * ANGLE_RES2;

    return ret_val;
}

static uint8_t inclinometer_calculate_crc ( uint32_t data_val )
{
    uint8_t bitindex;
    uint8_t bitvalue;
    uint8_t crc;
    crc = 0xFF;
    for ( uint8_t bitindex = 31; bitindex > 7; bitindex-- )
    {
        bitvalue = (uint8_t)((data_val >> bitindex) & 0x01);
        crc = inclinometer_crc8( bitvalue, crc );
    }
    crc = (uint8_t)~crc;
    return crc;
}

static uint8_t inclinometer_crc8 ( uint8_t bit_value, uint8_t crc )
{
    uint8_t temp;
    temp = ( uint8_t )( crc & 0x80 );
    if ( bit_value == 0x01 )
    {
        temp ^= 0x80;
    }
    crc <<= 1;
    if ( temp > 0 )
    {
        crc ^= 0x1D;
    }
    return crc;
}

static err_t inclinometer_raw_write ( inclinometer_t *ctx, uint32_t raw_val )
{
    err_t ret_val = INCLINOMETER_OK;
    uint8_t tx_buf[ 4 ] = { 0 };
    tx_buf[ 0 ] = raw_val >> 24;
    tx_buf[ 1 ] = raw_val >> 16;
    tx_buf[ 2 ] = raw_val >> 8;
    tx_buf[ 3 ] = raw_val;

    spi_master_set_default_write_data( &ctx->spi, tx_buf[ 0 ] );
    spi_master_select_device( ctx->chip_select );
    ret_val |= spi_master_read( &ctx->spi, &ctx->rs, 1 );
    ret_val |= spi_master_write( &ctx->spi, &tx_buf[ 1 ], 3 );
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );
    Delay_10us( );

    ctx->rs &= 0x3;

    return ret_val;
}

static err_t inclinometer_raw_read ( inclinometer_t *ctx, uint32_t cmd, uint32_t *raw_val)
{
    err_t ret_val = INCLINOMETER_OK;
    uint8_t tx_buf[ 4 ] = { 0 };
    uint8_t rx_buf[ 4 ] = { 0 };
    tx_buf[ 0 ] = cmd >> 24;
    tx_buf[ 1 ] = cmd >> 16;
    tx_buf[ 2 ] = cmd >> 8;
    tx_buf[ 3 ] = cmd;

    spi_master_select_device( ctx->chip_select );
    for ( uint8_t index = 0; index < 4; index++ )
    {
        spi_master_set_default_write_data( &ctx->spi, tx_buf[ index ] );
        ret_val |= spi_master_read( &ctx->spi, &rx_buf[ index ], 1 );
    }
    Delay_10us( );
    spi_master_deselect_device( ctx->chip_select );
    spi_master_set_default_write_data( &ctx->spi, DUMMY );

    *raw_val = ( (uint32_t)rx_buf[0] << 24 ) | ( (uint32_t)rx_buf[1] << 16 ) | 
               ( (uint32_t)rx_buf[2] << 8 ) | rx_buf[ 3 ];

    Delay_10us( );
    return ret_val;
}

static float inclinometer_resolution ( uint8_t mode )
{
    float ret_val = 0;
    switch ( mode )
    {
        case 1:
        {
            ret_val = RESOLUTION_MODE1;
            break;
        }
        case 0:
        {
            ret_val = RESOLUTION_MODE2;
            break;
        }
        case 2:
        case 3:
        {
            ret_val = RESOLUTION_MODE34;
            break;
        }
        default:
            break;
    }

    return ret_val;
}

// ------------------------------------------------------------------------- END
