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
 * @file environment7.c
 * @brief Environment 7 Click Driver.
 */

#include "environment7.h"

/**
 * @brief Environment 7 crc constants.
 * @details Specified constants for crc of Environment 7 Click driver.
 */
#define ENVIRONMENT7_POLYNOM            0x31
#define ENVIRONMENT7_INIT_VALUE         0xFF

/** 
 * @brief Environment 7 Dallas/Maxim calculation for CRC8 function.
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
static uint8_t environment7_calculate_crc ( uint8_t *crc_source );

void environment7_cfg_setup ( environment7_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT7_DEVICE_ADDRESS;
}

err_t environment7_init ( environment7_t *ctx, environment7_cfg_t *cfg ) 
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

err_t environment7_send_cmd ( environment7_t *ctx, uint16_t cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t environment7_send_cmd_data ( environment7_t *ctx, uint16_t cmd, uint16_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 8 ] = { 0 };
    if ( ( len > 2 ) || ( NULL == data_in ) )
    {
        return ENVIRONMENT7_ERROR;
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt * 3 + 2 ] = ( uint8_t ) ( ( data_in[ cnt ] >> 8 ) & 0xFF );
        data_buf[ cnt * 3 + 3 ] = ( uint8_t ) ( data_in[ cnt ] & 0xFF );
        data_buf[ cnt * 3 + 4 ] = environment7_calculate_crc ( &data_buf[ cnt * 3 + 2 ] );
    }
    return i2c_master_write( &ctx->i2c, data_buf, len * 3 + 2 );
}

err_t environment7_read_data ( environment7_t *ctx, uint16_t *data_out, uint8_t len )
{
    err_t error_flag = ENVIRONMENT7_OK;
    uint8_t data_buf[ 18 ] = { 0 };
    uint8_t cnt = 0;
    if ( ( len > 6 ) || ( NULL == data_out ) )
    {
        return ENVIRONMENT7_ERROR;
    }
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, len * 3 );
    for ( cnt = 0; ( cnt < len ) && ( ENVIRONMENT7_OK == error_flag ); cnt++ )
    {
        if ( data_buf[ cnt * 3 + 2 ] == environment7_calculate_crc ( &data_buf[ cnt * 3 ] ) )
        {
            data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 3 ] << 8 ) | data_buf[ cnt * 3 + 1 ];
        }
        else
        {
            error_flag |= ENVIRONMENT7_ERROR;
        }
    }
    return error_flag;
}

err_t environment7_read_id ( environment7_t *ctx, uint32_t *prod_num, uint32_t *serial_num_msb, uint32_t *serial_num_lsb )
{
    err_t error_flag = ENVIRONMENT7_OK;
    uint16_t prod_id[ 6 ] = { 0 };
    error_flag |= environment7_send_cmd ( ctx, ENVIRONMENT7_CMD_GET_PRODUCT_ID );
    if ( ENVIRONMENT7_OK == error_flag )
    {
        Delay_10ms ( );
        error_flag |= environment7_read_data ( ctx, prod_id, 6 );
    }
    if ( ENVIRONMENT7_OK == error_flag )
    {
        if ( NULL != prod_num )
        {
            *prod_num = ( ( uint32_t ) prod_id[ 0 ] << 16 ) | prod_id[ 1 ];
        }
        if ( NULL != serial_num_msb )
        {
            *serial_num_msb = ( ( uint32_t ) prod_id[ 2 ] << 16 ) | prod_id[ 3 ];
        }
        if ( NULL != serial_num_lsb )
        {
            *serial_num_lsb = ( ( uint32_t ) prod_id[ 4 ] << 16 ) | prod_id[ 5 ];
        }
    }
    return error_flag;
}

err_t environment7_set_rht ( environment7_t *ctx, float temp, float hum )
{
    uint16_t raw_data[ 2 ] = { 0 };
    raw_data[ 0 ] = ( temp - ENVIRONMENT7_ABS_MIN_TEMP ) * 
                    ENVIRONMENT7_DATA_RESOLUTION / 
                    ( ENVIRONMENT7_ABS_MAX_TEMP - ENVIRONMENT7_ABS_MIN_TEMP );
    raw_data[ 1 ] = ( hum - ENVIRONMENT7_ABS_MIN_HUM ) * 
                    ENVIRONMENT7_DATA_RESOLUTION / 
                    ( ENVIRONMENT7_ABS_MAX_HUM - ENVIRONMENT7_ABS_MIN_HUM );
    return environment7_send_cmd_data ( ctx, ENVIRONMENT7_CMD_SET_RHT_COMPENSATION, raw_data, 2 );
}

err_t environment7_set_pressure ( environment7_t *ctx, uint32_t pressure )
{
    uint16_t raw_data = ( uint16_t ) ( pressure / ENVIRONMENT7_PRESSURE_RES );
    return environment7_send_cmd_data ( ctx, ENVIRONMENT7_CMD_SET_PRESSURE_COMPENSATION, &raw_data, 1 );
}

err_t environment7_set_meas_mode ( environment7_t *ctx, uint8_t mode )
{
    err_t error_flag = ENVIRONMENT7_OK;
    if ( ENVIRONMENT7_MEAS_MODE_START_CONTINUOUS == mode )
    {
        error_flag |= environment7_send_cmd ( ctx, ENVIRONMENT7_CMD_START_CONT_MEASUREMENT );
        Delay_1sec ( );
        Delay_100ms ( );
    }
    else if ( ENVIRONMENT7_MEAS_MODE_STOP_CONTINUOUS == mode )
    {
        error_flag |= environment7_send_cmd ( ctx, ENVIRONMENT7_CMD_STOP_CONT_MEASUREMENT );
        Delay_1sec ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
    }
    else if ( ENVIRONMENT7_MEAS_MODE_START_SINGLE_SHOT == mode )
    {
        error_flag |= environment7_send_cmd ( ctx, ENVIRONMENT7_CMD_MEASURE_SINGLE_SHOT );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
        Delay_100ms ( );
    }
    else
    {
        error_flag |= ENVIRONMENT7_ERROR;
    }
    return error_flag;
}

err_t environment7_read_meas ( environment7_t *ctx, uint16_t *gas, float *temp, float *hum )
{
    uint16_t data_out[ 4 ] = { 0 };
    err_t error_flag = environment7_read_data ( ctx, data_out, 4 );
    if ( ENVIRONMENT7_OK == error_flag )
    {
        if ( NULL != gas )
        {
            *gas = data_out[ 0 ];
        }
        if ( NULL != temp )
        {
            *temp = ENVIRONMENT7_ABS_MIN_TEMP + 
                    ( ENVIRONMENT7_ABS_MAX_TEMP - ENVIRONMENT7_ABS_MIN_TEMP ) * 
                    data_out[ 1 ] / ENVIRONMENT7_DATA_RESOLUTION;
        }
        if ( NULL != hum )
        {
            *hum = ENVIRONMENT7_ABS_MIN_HUM + 
                   ( ENVIRONMENT7_ABS_MAX_HUM - ENVIRONMENT7_ABS_MIN_HUM ) * 
                   data_out[ 2 ] / ENVIRONMENT7_DATA_RESOLUTION;
            if ( *hum > ENVIRONMENT7_MAX_RH )
            {
                *hum = ENVIRONMENT7_MAX_RH;
            }
            if ( *hum < ENVIRONMENT7_MIN_RH )
            {
                *hum = ENVIRONMENT7_MIN_RH;
            }
        }
    }
    return error_flag;
}

static uint8_t environment7_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = ENVIRONMENT7_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ ENVIRONMENT7_POLYNOM );
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
