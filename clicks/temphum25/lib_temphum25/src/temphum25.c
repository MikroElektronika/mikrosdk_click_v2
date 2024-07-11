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
 * @file temphum25.c
 * @brief TempHum 25 Click Driver.
 */

#include "temphum25.h"

/**
 * @brief TempHum 25 crc constants.
 * @details Specified constants for crc of TempHum 25 Click driver.
 */
#define TEMPHUM25_POLYNOM               0x31
#define TEMPHUM25_INIT_VALUE            0xFF

/** 
 * @brief TempHum 25 Dallas/Maxim calculation for CRC8 function.
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
static uint8_t temphum25_calculate_crc ( uint8_t *crc_source );

void temphum25_cfg_setup ( temphum25_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = TEMPHUM25_DEVICE_ADDRESS_0;
}

err_t temphum25_init ( temphum25_t *ctx, temphum25_cfg_t *cfg ) 
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

err_t temphum25_send_command ( temphum25_t *ctx, uint16_t cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t temphum25_start_measurement ( temphum25_t *ctx, uint16_t meas_cmd )
{
    err_t error_flag = temphum25_send_command ( ctx, meas_cmd );
    Delay_10ms ( );
    Delay_5ms ( );
    return error_flag;
}

err_t temphum25_stop_measurement ( temphum25_t *ctx )
{
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_CONT_MEAS_STOP );
    Delay_1ms ( );
    return error_flag;
}

err_t temphum25_read_measurement ( temphum25_t *ctx, float *temperature, float *humidity )
{
    uint16_t raw_data = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_FETCH_DATA );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( TEMPHUM25_OK != error_flag ) ||
         ( data_buf[ 2 ] != temphum25_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != temphum25_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return TEMPHUM25_ERROR;
    }
    if ( NULL != temperature )
    {
        raw_data = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        *temperature = TEMPHUM25_ABS_MIN_TEMP + ( TEMPHUM25_ABS_MAX_TEMP - TEMPHUM25_ABS_MIN_TEMP ) * 
                                                raw_data / TEMPHUM25_DATA_RESOLUTION;
    }
    if ( NULL != humidity )
    {
        raw_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
        *humidity = TEMPHUM25_MAX_RH * raw_data / TEMPHUM25_DATA_RESOLUTION;
    }
    return TEMPHUM25_OK;
}

err_t temphum25_read_serial_num ( temphum25_t *ctx, uint32_t *serial_num )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_GET_SERIAL_NUM_0 );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( TEMPHUM25_OK != error_flag ) ||
         ( data_buf[ 2 ] != temphum25_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != temphum25_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return TEMPHUM25_ERROR;
    }
    if ( NULL != serial_num )
    {
        *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                      ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    }
    return TEMPHUM25_OK;
}

err_t temphum25_read_status ( temphum25_t *ctx, uint16_t *status )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_READ_STATUS );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( ( TEMPHUM25_OK != error_flag ) ||
         ( data_buf[ 2 ] != temphum25_calculate_crc ( &data_buf[ 0 ] ) ) )
    {
        return TEMPHUM25_ERROR;
    }
    if ( NULL != status )
    {
        *status = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    }
    return TEMPHUM25_OK;
}

err_t temphum25_clear_status ( temphum25_t *ctx )
{
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_CLEAR_STATUS );
    Delay_1ms ( );
    return error_flag;
}

err_t temphum25_enable_heater ( temphum25_t *ctx )
{
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_HEATER_ENABLE );
    Delay_1ms ( );
    return error_flag;
}

err_t temphum25_disable_heater ( temphum25_t *ctx )
{
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_HEATER_DISABLE );
    Delay_1ms ( );
    return error_flag;
}

err_t temphum25_soft_reset ( temphum25_t *ctx )
{
    err_t error_flag = temphum25_send_command ( ctx, TEMPHUM25_CMD_SOFT_RESET );
    Delay_100ms ( );
    return error_flag;
}

void temphum25_set_rst_pin ( temphum25_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

void temphum25_reset_device ( temphum25_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_100ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

uint8_t temphum25_get_alert_pin ( temphum25_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

static uint8_t temphum25_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = TEMPHUM25_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ TEMPHUM25_POLYNOM );
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
