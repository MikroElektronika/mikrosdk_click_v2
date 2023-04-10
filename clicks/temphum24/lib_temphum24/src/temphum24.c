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
 * @file temphum24.c
 * @brief TempHum 24 Click Driver.
 */

#include "temphum24.h"

/**
 * @brief TempHum 24 crc constants.
 * @details Specified constants for crc of TempHum 24 Click driver.
 */
#define TEMPHUM24_POLYNOM               0x31
#define TEMPHUM24_INIT_VALUE            0xFF

/** 
 * @brief TempHum 24 calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xABCD) = 0x6F
 * @param[in] crc_source : 2 bytes array to calculate crc from.
 * @return Calculated CRC8 output.
 * @note None.
 */
static uint8_t temphum24_calculate_crc ( uint8_t *crc_source );

void temphum24_cfg_setup ( temphum24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM24_DEVICE_ADDRESS_A1A0_00;
}

err_t temphum24_init ( temphum24_t *ctx, temphum24_cfg_t *cfg ) 
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

    digital_out_init( &ctx->rst, cfg->rst );

    digital_in_init( &ctx->alert, cfg->alert );
    
    return I2C_MASTER_SUCCESS;
}

err_t temphum24_default_cfg ( temphum24_t *ctx ) 
{
    err_t error_flag = TEMPHUM24_OK;
    temphum24_reset_device ( ctx );
    if ( TEMPHUM24_ERROR == temphum24_check_communication ( ctx ) )
    {
        return TEMPHUM24_ERROR;
    }
    error_flag |= temphum24_start_measurement ( ctx );
    Delay_1sec ( );
    return error_flag;
}

err_t temphum24_write_cmd ( temphum24_t *ctx, uint16_t cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t temphum24_write_cmd_config ( temphum24_t *ctx, uint16_t cmd, uint16_t config )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( config >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( config & 0xFF );
    data_buf[ 4 ] = temphum24_calculate_crc ( &data_buf[ 2 ] );
    return i2c_master_write( &ctx->i2c, data_buf, 5 );
}

err_t temphum24_read_single ( temphum24_t *ctx, uint16_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( data_buf[ 2 ] != temphum24_calculate_crc ( &data_buf[ 0 ] ) )
    {
        error_flag = TEMPHUM24_ERROR;
    }
    if ( TEMPHUM24_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t temphum24_read_multi ( temphum24_t *ctx, uint16_t *data1_out, uint16_t *data2_out )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( data_buf[ 2 ] != temphum24_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != temphum24_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        error_flag = TEMPHUM24_ERROR;
    }
    if ( TEMPHUM24_OK == error_flag )
    {
        *data1_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        *data2_out = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    }
    return error_flag;
}

err_t temphum24_write_then_read_single ( temphum24_t *ctx, uint16_t cmd, uint16_t *data_out )
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 2, &data_buf[ 2 ], 3 );
    if ( data_buf[ 4 ] != temphum24_calculate_crc ( &data_buf[ 2 ] ) )
    {
        error_flag = TEMPHUM24_ERROR;
    }
    if ( TEMPHUM24_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
    }
    return error_flag;
}

err_t temphum24_write_then_read_multi ( temphum24_t *ctx, uint16_t cmd, uint16_t *data1_out, uint16_t *data2_out )
{
    uint8_t data_buf[ 8 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &data_buf[ 0 ], 2, &data_buf[ 2 ], 6 );
    if ( ( data_buf[ 4 ] != temphum24_calculate_crc ( &data_buf[ 2 ] ) ) || 
         ( data_buf[ 7 ] != temphum24_calculate_crc ( &data_buf[ 5 ] ) ) )
    {
        error_flag = TEMPHUM24_ERROR;
    }
    if ( TEMPHUM24_OK == error_flag )
    {
        *data1_out = ( ( uint16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 3 ];
        *data2_out = ( ( uint16_t ) data_buf[ 5 ] << 8 ) | data_buf[ 6 ];
    }
    return error_flag;
}

void temphum24_enable_device ( temphum24_t *ctx )
{
    digital_out_high ( &ctx->rst );
}

void temphum24_disable_device ( temphum24_t *ctx )
{
    digital_out_low ( &ctx->rst );
}

void temphum24_reset_device ( temphum24_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t temphum24_get_alert_pin ( temphum24_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

err_t temphum24_check_communication ( temphum24_t *ctx )
{
    uint16_t manufacturer_id = 0;
    err_t error_flag = temphum24_write_then_read_single( ctx, TEMPHUM24_CMD_READ_MANUFACTURER_ID, 
                                                         &manufacturer_id );
    if ( TEMPHUM24_MANUFACTURER_ID != manufacturer_id )
    {
        error_flag = TEMPHUM24_ERROR;
    }
    return error_flag;
}

err_t temphum24_read_temp_and_rh ( temphum24_t *ctx, float *temp, float *hum )
{
    uint16_t raw_temp = 0, raw_hum = 0;
    err_t error_flag = temphum24_write_then_read_multi( ctx, TEMPHUM24_CMD_AUTO_MEAS_ROUT_T_RH, 
                                                        &raw_temp, &raw_hum );
    if ( TEMPHUM24_OK == error_flag )
    {
        *temp = TEMPHUM24_TEMP_MIN + ( TEMPHUM24_TEMP_MAX - TEMPHUM24_TEMP_MIN ) * 
                                     ( float ) raw_temp / TEMPHUM24_DATA_RESOLUTION;
        *hum = TEMPHUM24_HUM_MAX * ( float ) raw_hum / TEMPHUM24_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t temphum24_read_temp_history ( temphum24_t *ctx, float *temp_min, float *temp_max )
{
    uint16_t raw_temp_min = 0, raw_temp_max = 0;
    err_t error_flag = temphum24_write_then_read_single( ctx, TEMPHUM24_CMD_AUTO_MEAS_MIN_T, &raw_temp_min );
    error_flag |= temphum24_write_then_read_single( ctx, TEMPHUM24_CMD_AUTO_MEAS_MAX_T, &raw_temp_max );
    if ( TEMPHUM24_OK == error_flag )
    {
        *temp_min = TEMPHUM24_TEMP_MIN + ( TEMPHUM24_TEMP_MAX - TEMPHUM24_TEMP_MIN ) * 
                                         ( float ) raw_temp_min / TEMPHUM24_DATA_RESOLUTION;
        *temp_max = TEMPHUM24_TEMP_MIN + ( TEMPHUM24_TEMP_MAX - TEMPHUM24_TEMP_MIN ) * 
                                         ( float ) raw_temp_max / TEMPHUM24_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t temphum24_read_rh_history ( temphum24_t *ctx, float *hum_min, float *hum_max )
{
    uint16_t raw_hum_min = 0, raw_hum_max = 0;
    err_t error_flag = temphum24_write_then_read_single( ctx, TEMPHUM24_CMD_AUTO_MEAS_MIN_RH, &raw_hum_min );
    error_flag |= temphum24_write_then_read_single( ctx, TEMPHUM24_CMD_AUTO_MEAS_MAX_RH, &raw_hum_max );
    if ( TEMPHUM24_OK == error_flag )
    {
        *hum_min = TEMPHUM24_HUM_MAX * ( float ) raw_hum_min / TEMPHUM24_DATA_RESOLUTION;
        *hum_max = TEMPHUM24_HUM_MAX * ( float ) raw_hum_max / TEMPHUM24_DATA_RESOLUTION;
    }
    return error_flag;
}

err_t temphum24_start_measurement ( temphum24_t *ctx )
{
    return temphum24_write_cmd ( ctx, TEMPHUM24_CMD_AUTO_MEAS_1_HZ_LP0 );
}

err_t temphum24_stop_measurement ( temphum24_t *ctx )
{
    return temphum24_write_cmd ( ctx, TEMPHUM24_CMD_AUTO_MEAS_EXIT );
}

static uint8_t temphum24_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = TEMPHUM24_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ TEMPHUM24_POLYNOM );
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
