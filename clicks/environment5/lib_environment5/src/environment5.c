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
 * @file environment5.c
 * @brief Environment 5 Click Driver.
 */

#include "environment5.h"

/**
 * @brief Environment 5 crc constants.
 * @details Specified constants for crc of Environment 5 Click driver.
 */
#define ENVIRONMENT5_POLYNOM            0x31
#define ENVIRONMENT5_INIT_VALUE         0xFF

/** 
 * @brief Environment 5 Dallas/Maxim calculation for CRC8 function.
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
static uint8_t environment5_calculate_crc ( uint8_t *crc_source );

void environment5_cfg_setup ( environment5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->en = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT5_SHT_DEVICE_ADDRESS;
}

err_t environment5_init ( environment5_t *ctx, environment5_cfg_t *cfg ) 
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

    digital_out_init( &ctx->en, cfg->en );
    Delay_100ms ( );

    return I2C_MASTER_SUCCESS;
}

err_t environment5_default_cfg ( environment5_t *ctx ) 
{
    err_t error_flag = ENVIRONMENT5_OK;
    ctx->stc_crc_enabled = true;

    environment5_enable_device ( ctx );
    Delay_100ms ( );
    error_flag |= environment5_sht_soft_reset ( ctx );
    Delay_100ms ( );
    error_flag |= environment5_stc_send_cmd ( ctx, ENVIRONMENT5_STC_CMD_ENABLE_WEAK_FILTER );
    Delay_100ms ( );
    error_flag |= environment5_stc_set_meas_mode ( ctx, ENVIRONMENT5_STC_MODE_LC_CO2_IN_AIR_0_TO_40 );
    Delay_100ms ( );
    return error_flag;
}

void environment5_enable_device ( environment5_t *ctx ) 
{
    digital_out_high( &ctx->en );
}

void environment5_disable_device ( environment5_t *ctx ) 
{
    digital_out_low( &ctx->en );
}

err_t environment5_stc_send_cmd ( environment5_t *ctx, uint16_t cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ENVIRONMENT5_STC_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT5_STC_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t environment5_stc_send_cmd_data ( environment5_t *ctx, uint16_t cmd, uint16_t data_in )
{
    err_t error_flag = ENVIRONMENT5_OK;
    uint8_t data_buf[ 5 ] = { 0 };
    if ( ENVIRONMENT5_STC_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT5_STC_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( data_in & 0xFF );
    if ( ctx->stc_crc_enabled )
    {
        data_buf[ 4 ] = environment5_calculate_crc ( &data_buf[ 2 ] );
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 5 );
    }
    else
    {
        error_flag |= i2c_master_write( &ctx->i2c, data_buf, 4 );
    }
    return error_flag;
}

err_t environment5_stc_read_data ( environment5_t *ctx, uint16_t *data_out, uint8_t len )
{
    err_t error_flag = ENVIRONMENT5_OK;
    uint8_t data_buf[ 18 ] = { 0 };
    uint8_t cnt = 0;
    if ( ( len > 6 ) || ( NULL == data_out ) )
    {
        return ENVIRONMENT5_ERROR;
    }
    if ( ENVIRONMENT5_STC_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT5_STC_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    if ( ctx->stc_crc_enabled )
    {
        error_flag |= i2c_master_read( &ctx->i2c, data_buf, len * 3 );
        for ( cnt = 0; ( cnt < len ) && ( ENVIRONMENT5_OK == error_flag ); cnt++ )
        {
            if ( data_buf[ cnt * 3 + 2 ] == environment5_calculate_crc ( &data_buf[ cnt * 3 ] ) )
            {
                data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 3 ] << 8 ) | data_buf[ cnt * 3 + 1 ];
            }
            else
            {
                error_flag |= ENVIRONMENT5_ERROR;
            }
        }
    }
    else
    {
        error_flag |= i2c_master_read( &ctx->i2c, data_buf, len * 2 );
        for ( cnt = 0; ( cnt < len ) && ( ENVIRONMENT5_OK == error_flag ); cnt++ )
        {
            data_out[ cnt ] = ( ( uint16_t ) data_buf[ cnt * 2 ] << 8 ) | data_buf[ cnt * 2 + 1 ];
        }
    }
    return error_flag;
}

err_t environment5_stc_disable_crc ( environment5_t *ctx )
{
    err_t error_flag = ENVIRONMENT5_OK;
    error_flag |= environment5_stc_send_cmd ( ctx, ENVIRONMENT5_STC_CMD_DISABLE_CRC );
    if ( ENVIRONMENT5_OK == error_flag )
    {
        ctx->stc_crc_enabled = false;
    }
    return error_flag;
}

err_t environment5_stc_read_id ( environment5_t *ctx, uint32_t *prod_num, uint32_t *serial_num_msb, uint32_t *serial_num_lsb )
{
    err_t error_flag = ENVIRONMENT5_OK;
    uint16_t prod_id[ 6 ] = { 0 };
    error_flag |= environment5_stc_send_cmd ( ctx, ENVIRONMENT5_STC_CMD_READ_PRODUCT_ID_0 );
    error_flag |= environment5_stc_send_cmd ( ctx, ENVIRONMENT5_STC_CMD_READ_PRODUCT_ID_1 );
    if ( ENVIRONMENT5_OK == error_flag )
    {
        error_flag |= environment5_stc_read_data ( ctx, prod_id, 6 );
    }
    if ( ENVIRONMENT5_OK == error_flag )
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

err_t environment5_stc_set_temp ( environment5_t *ctx, float temperature )
{
    uint16_t raw_temp = ( uint16_t ) ( temperature * ENVIRONMENT5_STC_TEMP_DATA_RESOLUTION );
    return environment5_stc_send_cmd_data ( ctx, ENVIRONMENT5_STC_CMD_SET_TEMPERATURE, raw_temp );
}

err_t environment5_stc_set_hum ( environment5_t *ctx, float humidity )
{
    uint16_t raw_hum = ( uint16_t ) ( ( humidity * ENVIRONMENT5_STC_RH_DATA_RESOLUTION ) / ENVIRONMENT5_STC_MAX_RH );
    return environment5_stc_send_cmd_data ( ctx, ENVIRONMENT5_STC_CMD_SET_REL_HUMIDITY, raw_hum );
}

err_t environment5_stc_set_meas_mode ( environment5_t *ctx, uint16_t mode )
{
    return environment5_stc_send_cmd_data ( ctx, ENVIRONMENT5_STC_CMD_SET_MEAS_MODE_AND_BIN_GAS, mode );
}

err_t environment5_stc_read_meas ( environment5_t *ctx, float *gas, float *temp )
{
    uint16_t data_out[ 3 ] = { 0 };
    err_t error_flag = ENVIRONMENT5_OK;
    error_flag |= environment5_stc_send_cmd ( ctx, ENVIRONMENT5_STC_CMD_MEAS_GAS_CONCENTRATION );
    if ( ENVIRONMENT5_OK == error_flag )
    {
        Delay_100ms ( );
        Delay_100ms ( );
        error_flag |= environment5_stc_read_data ( ctx, data_out, 3 );
    }
    if ( ENVIRONMENT5_OK == error_flag )
    {
        if ( NULL != gas )
        {
            *gas = ( ENVIRONMENT5_STC_MAX_CO2 * ( data_out[ 0 ] - ENVIRONMENT5_STC_CO2_OFFSET ) ) / 
                   ENVIRONMENT5_STC_CO2_DATA_RESOLUTION;
            if ( *gas > ENVIRONMENT5_STC_MAX_CO2 )
            {
                *gas = ENVIRONMENT5_STC_MAX_CO2;
            }
            if ( *gas < ENVIRONMENT5_STC_MIN_CO2 )
            {
                *gas = ENVIRONMENT5_STC_MIN_CO2;
            }
        }
        if ( NULL != temp )
        {
            *temp = data_out[ 1 ] / ENVIRONMENT5_STC_TEMP_DATA_RESOLUTION;
        }
    }
    return error_flag;
}

err_t environment5_sht_send_cmd ( environment5_t *ctx, uint8_t cmd )
{
    if ( ENVIRONMENT5_SHT_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT5_SHT_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t environment5_sht_read_response ( environment5_t *ctx, uint8_t *data_out )
{
    if ( ENVIRONMENT5_SHT_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT5_SHT_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_read( &ctx->i2c, data_out, 6 );
}

err_t environment5_sht_soft_reset ( environment5_t *ctx )
{
    return environment5_sht_send_cmd( ctx, ENVIRONMENT5_SHT_CMD_SOFT_RESET );
}

err_t environment5_sht_read_serial ( environment5_t *ctx, uint32_t *serial_num )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = environment5_sht_send_cmd( ctx, ENVIRONMENT5_SHT_CMD_READ_SERIAL_NUM );
    Delay_1ms ( );
    error_flag |= environment5_sht_read_response( ctx, data_buf );
    if ( ( ENVIRONMENT5_OK != error_flag ) ||
         ( data_buf[ 2 ] != environment5_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment5_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return ENVIRONMENT5_ERROR;
    }
    *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                  ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    return ENVIRONMENT5_OK;
}

err_t environment5_sht_read_meas_hp ( environment5_t *ctx, float *temp, float *hum )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = environment5_sht_send_cmd( ctx, ENVIRONMENT5_SHT_CMD_MEAS_TH_HIGH_PREC );
    Delay_10ms ( );
    error_flag |= environment5_sht_read_response( ctx, data_buf );
    if ( ( ENVIRONMENT5_OK != error_flag ) ||
         ( data_buf[ 2 ] != environment5_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment5_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return ENVIRONMENT5_ERROR;
    }
    uint16_t raw_data = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *temp = ENVIRONMENT5_SHT_ABS_MIN_TEMP + ( ENVIRONMENT5_SHT_ABS_MAX_TEMP - ENVIRONMENT5_SHT_ABS_MIN_TEMP ) * 
                                            raw_data / ENVIRONMENT5_SHT_DATA_RESOLUTION;
    raw_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    *hum = ENVIRONMENT5_SHT_ABS_MIN_HUM + ( ENVIRONMENT5_SHT_ABS_MAX_HUM - ENVIRONMENT5_SHT_ABS_MIN_HUM ) * 
                                          raw_data / ENVIRONMENT5_SHT_DATA_RESOLUTION;
    if ( *hum > ENVIRONMENT5_SHT_MAX_RH )
    {
        *hum = ENVIRONMENT5_SHT_MAX_RH;
    }
    if ( *hum < ENVIRONMENT5_SHT_MIN_RH )
    {
        *hum = ENVIRONMENT5_SHT_MIN_RH;
    }
    return ENVIRONMENT5_OK;
}

static uint8_t environment5_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = ENVIRONMENT5_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ ENVIRONMENT5_POLYNOM );
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
