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
 * @file temphum22.c
 * @brief TempHum 22 Click Driver.
 */

#include "temphum22.h"

/**
 * @brief TempHum 22 crc constants.
 * @details Specified constants for crc of TempHum 22 Click driver.
 */
#define TEMPHUM22_POLYNOM               0x31
#define TEMPHUM22_INIT_VALUE            0xFF

/** 
 * @brief TempHum 22 Dallas/Maxim calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xBEEF) = 0x92
 * @param[in] crc_source : 2 bytes array to calculate crc from.
 * @return Calculated CRC8 output.
 * @note None.
 */
static uint8_t temphum22_calculate_crc ( uint8_t *crc_source );

void temphum22_cfg_setup ( temphum22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM22_DEVICE_ADDRESS;
}

err_t temphum22_init ( temphum22_t *ctx, temphum22_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );

    i2c_cfg.scl = cfg->scl;
    i2c_cfg.sda = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
    {
        return I2C_MASTER_ERROR;
    }

    return I2C_MASTER_SUCCESS;
}

err_t temphum22_send_cmd ( temphum22_t *ctx, uint8_t cmd )
{
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t temphum22_read_response ( temphum22_t *ctx, uint8_t *data_out )
{
    return i2c_master_read( &ctx->i2c, data_out, 6 );
}

err_t temphum22_soft_reset ( temphum22_t *ctx )
{
    return temphum22_send_cmd( ctx, TEMPHUM22_CMD_SOFT_RESET );
}

err_t temphum22_read_serial_num ( temphum22_t *ctx, uint32_t *serial_num )
{
    uint8_t data_buf[ 6 ];
    err_t error_flag = temphum22_send_cmd( ctx, TEMPHUM22_CMD_READ_SERIAL_NUM );
    Delay_1ms ( );
    error_flag |= temphum22_read_response( ctx, data_buf );
    if ( ( TEMPHUM22_OK != error_flag ) ||
         ( data_buf[ 2 ] != temphum22_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != temphum22_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return TEMPHUM22_ERROR;
    }
    *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                  ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    return TEMPHUM22_OK;
}

err_t temphum22_read_measurement_high_precision ( temphum22_t *ctx, float *temp, float *hum )
{
    uint8_t data_buf[ 6 ];
    err_t error_flag = temphum22_send_cmd( ctx, TEMPHUM22_CMD_MEAS_TH_HIGH_PREC );
    Delay_10ms ( );
    error_flag |= temphum22_read_response( ctx, data_buf );
    if ( ( TEMPHUM22_OK != error_flag ) ||
         ( data_buf[ 2 ] != temphum22_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != temphum22_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return TEMPHUM22_ERROR;
    }
    uint16_t raw_data = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *temp = TEMPHUM22_ABS_MIN_TEMP + ( TEMPHUM22_ABS_MAX_TEMP - TEMPHUM22_ABS_MIN_TEMP ) * raw_data / TEMPHUM22_DATA_RESOLUTION;
    raw_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    *hum = TEMPHUM22_ABS_MIN_HUM + ( TEMPHUM22_ABS_MAX_HUM - TEMPHUM22_ABS_MIN_HUM ) * raw_data / TEMPHUM22_DATA_RESOLUTION;
    if ( *hum > TEMPHUM22_MAX_RH )
    {
        *hum = TEMPHUM22_MAX_RH;
    }
    if ( *hum < TEMPHUM22_MIN_RH )
    {
        *hum = TEMPHUM22_MIN_RH;
    }
    return TEMPHUM22_OK;
}

static uint8_t temphum22_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = TEMPHUM22_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ TEMPHUM22_POLYNOM );
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
