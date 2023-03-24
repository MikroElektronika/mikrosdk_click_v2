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
 * @file environment4.c
 * @brief Environment 4 Click Driver.
 */

#include "environment4.h"

/**
 * @brief Environment 4 crc constants.
 * @details Specified constants for crc of Environment 4 Click driver.
 */
#define ENVIRONMENT4_POLYNOM            0x31
#define ENVIRONMENT4_INIT_VALUE         0xFF

/** 
 * @brief Environment 4 Dallas/Maxim calculation for CRC8 function.
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
static uint8_t environment4_calculate_crc ( uint8_t *crc_source );

void environment4_cfg_setup ( environment4_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
}

err_t environment4_init ( environment4_t *ctx, environment4_cfg_t *cfg ) 
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

err_t environment4_sgp_exe_conditioning ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, 
                                          uint16_t *sraw_voc )
{
    uint8_t data_buf[ 9 ] = { 0 };
    if ( ENVIRONMENT4_SGP_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ENVIRONMENT4_SGP_CMD_EXE_CONDITIONING >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ENVIRONMENT4_SGP_CMD_EXE_CONDITIONING & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( comp_rh >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( comp_rh & 0xFF );
    data_buf[ 4 ] = environment4_calculate_crc ( &data_buf[ 2 ] );
    data_buf[ 5 ] = ( uint8_t ) ( ( comp_t >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( comp_t & 0xFF );
    data_buf[ 7 ] = environment4_calculate_crc ( &data_buf[ 5 ] );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 8 );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( ( ENVIRONMENT4_ERROR == error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    *sraw_voc = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    return ENVIRONMENT4_OK;
}

err_t environment4_sgp_meas_raw_signals ( environment4_t *ctx, uint16_t comp_rh, uint16_t comp_t, 
                                          uint16_t *sraw_voc, uint16_t *sraw_nox )
{
    uint8_t data_buf[ 9 ] = { 0 };
    if ( ENVIRONMENT4_SGP_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ENVIRONMENT4_SGP_CMD_MEAS_RAW_SIGNALS >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ENVIRONMENT4_SGP_CMD_MEAS_RAW_SIGNALS & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( comp_rh >> 8 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( comp_rh & 0xFF );
    data_buf[ 4 ] = environment4_calculate_crc ( &data_buf[ 2 ] );
    data_buf[ 5 ] = ( uint8_t ) ( ( comp_t >> 8 ) & 0xFF );
    data_buf[ 6 ] = ( uint8_t ) ( comp_t & 0xFF );
    data_buf[ 7 ] = environment4_calculate_crc ( &data_buf[ 5 ] );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 8 );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( ENVIRONMENT4_ERROR == error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment4_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    *sraw_voc = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *sraw_nox = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    return ENVIRONMENT4_OK;
}

err_t environment4_sgp_exe_self_test ( environment4_t *ctx, uint8_t *test_result )
{
    uint8_t data_buf[ 9 ] = { 0 };
    if ( ENVIRONMENT4_SGP_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ENVIRONMENT4_SGP_CMD_EXE_SELF_TEST >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ENVIRONMENT4_SGP_CMD_EXE_SELF_TEST & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_100ms ( );
    Delay_10ms ( );
    Delay_10ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( ( ENVIRONMENT4_ERROR == error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    *test_result = data_buf[ 1 ] & ENVIRONMENT4_SGP_SELF_TEST_MASK;
    return ENVIRONMENT4_OK;
}

err_t environment4_sgp_turn_heater_off ( environment4_t *ctx )
{
    uint8_t data_buf[ 2 ] = { 0 };
    if ( ENVIRONMENT4_SGP_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ENVIRONMENT4_SGP_TURN_HEATER_OFF >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ENVIRONMENT4_SGP_TURN_HEATER_OFF & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    Delay_1ms ( );
    return error_flag;
}

err_t environment4_sgp_get_serial_num ( environment4_t *ctx, uint16_t *serial_num )
{
    uint8_t data_buf[ 9 ] = { 0 };
    if ( ENVIRONMENT4_SGP_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SGP_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    data_buf[ 0 ] = ( uint8_t ) ( ( ENVIRONMENT4_SGP_GET_SERIAL_NUMBER >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ENVIRONMENT4_SGP_GET_SERIAL_NUMBER & 0xFF );
    err_t error_flag = i2c_master_write( &ctx->i2c, data_buf, 2 );
    Delay_1ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 9 );
    if ( ( ENVIRONMENT4_ERROR == error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment4_calculate_crc ( &data_buf[ 3 ] ) ) || 
         ( data_buf[ 8 ] != environment4_calculate_crc ( &data_buf[ 6 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    serial_num[ 0 ] = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    serial_num[ 1 ] = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    serial_num[ 2 ] = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
    return ENVIRONMENT4_OK;
}

err_t environment4_sht_send_cmd ( environment4_t *ctx, uint8_t cmd )
{
    if ( ENVIRONMENT4_SHT_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SHT_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_write( &ctx->i2c, &cmd, 1 );
}

err_t environment4_sht_read_response ( environment4_t *ctx, uint8_t *data_out )
{
    if ( ENVIRONMENT4_SHT_DEVICE_ADDRESS != ctx->slave_address )
    {
        ctx->slave_address = ENVIRONMENT4_SHT_DEVICE_ADDRESS;
        i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    }
    return i2c_master_read( &ctx->i2c, data_out, 6 );
}

err_t environment4_sht_soft_reset ( environment4_t *ctx )
{
    return environment4_sht_send_cmd( ctx, ENVIRONMENT4_SHT_CMD_SOFT_RESET );
}

err_t environment4_sht_read_serial_num ( environment4_t *ctx, uint32_t *serial_num )
{
    uint8_t data_buf[ 6 ];
    err_t error_flag = environment4_sht_send_cmd( ctx, ENVIRONMENT4_SHT_CMD_READ_SERIAL_NUM );
    Delay_1ms ( );
    error_flag |= environment4_sht_read_response( ctx, data_buf );
    if ( ( ENVIRONMENT4_OK != error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment4_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                  ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    return ENVIRONMENT4_OK;
}

err_t environment4_sht_read_meas_hp ( environment4_t *ctx, float *temp, float *hum )
{
    uint8_t data_buf[ 6 ];
    err_t error_flag = environment4_sht_send_cmd( ctx, ENVIRONMENT4_SHT_CMD_MEAS_TH_HIGH_PREC );
    Delay_10ms ( );
    error_flag |= environment4_sht_read_response( ctx, data_buf );
    if ( ( ENVIRONMENT4_OK != error_flag ) ||
         ( data_buf[ 2 ] != environment4_calculate_crc ( &data_buf[ 0 ] ) ) || 
         ( data_buf[ 5 ] != environment4_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        return ENVIRONMENT4_ERROR;
    }
    uint16_t raw_data = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
    *temp = ENVIRONMENT4_SHT_ABS_MIN_TEMP + ( ENVIRONMENT4_SHT_ABS_MAX_TEMP - ENVIRONMENT4_SHT_ABS_MIN_TEMP ) * 
                                            raw_data / ENVIRONMENT4_SHT_DATA_RESOLUTION;
    raw_data = ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
    *hum = ENVIRONMENT4_SHT_ABS_MIN_HUM + ( ENVIRONMENT4_SHT_ABS_MAX_HUM - ENVIRONMENT4_SHT_ABS_MIN_HUM ) * 
                                          raw_data / ENVIRONMENT4_SHT_DATA_RESOLUTION;
    if ( *hum > ENVIRONMENT4_SHT_MAX_RH )
    {
        *hum = ENVIRONMENT4_SHT_MAX_RH;
    }
    if ( *hum < ENVIRONMENT4_SHT_MIN_RH )
    {
        *hum = ENVIRONMENT4_SHT_MIN_RH;
    }
    return ENVIRONMENT4_OK;
}

static uint8_t environment4_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = ENVIRONMENT4_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ ENVIRONMENT4_POLYNOM );
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
