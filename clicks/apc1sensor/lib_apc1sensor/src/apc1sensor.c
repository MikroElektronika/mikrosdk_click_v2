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
 * @file apc1sensor.c
 * @brief APC1 Sensor Demo Driver.
 */

#include "apc1sensor.h"

/**
 * @brief APC1 Sensor send command function.
 * @details This function sends a desired command by using I2C serial interface.
 * @param[in] ctx : Demo context object.
 * See #apc1sensor_t object definition for detailed explanation.
 * @param[in] cmd : Command byte (0xE4 - set mode, 0xE9 - get info).
 * @param[in] mode : Mode word (0x00 - idle, 0x01 - measurement, 0x0F - reset).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t apc1sensor_send_command ( apc1sensor_t *ctx, uint8_t cmd, uint16_t mode );

/**
 * @brief APC1 Sensor calculate checksum function.
 * @details This function calculates the checksum word from the input buffer.
 * @param[in] data_in : Data buffer to calculate the checksum from.
 * @param[in] len : Number of data bytes in buffer.
 * @return Calculated checksum word.
 * @note None.
 */
static uint16_t apc1sensor_calculate_checksum ( uint8_t *data_in, uint8_t len );

void apc1sensor_cfg_setup ( apc1sensor_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->set = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = APC1SENSOR_DEVICE_ADDRESS;
}

err_t apc1sensor_init ( apc1sensor_t *ctx, apc1sensor_cfg_t *cfg ) 
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
    digital_out_init( &ctx->set, cfg->set );

    return APC1SENSOR_OK;
}

err_t apc1sensor_default_cfg ( apc1sensor_t *ctx )
{
    err_t error_flag = APC1SENSOR_OK;
    apc1sensor_set_opmode ( ctx, APC1SENSOR_OPMODE_NORMAL );
    error_flag |= apc1sensor_sw_reset ( ctx );
    error_flag |= apc1sensor_start_measurement ( ctx );
    return error_flag;
}

err_t apc1sensor_set_idle_mode ( apc1sensor_t *ctx )
{
    uint16_t checksum = 0;
    uint8_t reg = APC1SENSOR_ADDRESS_RESPONSE;
    uint8_t data_buf[ 8 ] = { 0 };
    if ( APC1SENSOR_ERROR == apc1sensor_send_command ( ctx, APC1SENSOR_CMD_SET_MODE, APC1SENSOR_MODE_IDLE ) )
    {
        return APC1SENSOR_ERROR;
    }
    Delay_100ms ( );
    Delay_100ms ( );
    if ( APC1SENSOR_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 8 ) )
    {
        return APC1SENSOR_ERROR;
    }
    checksum = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
    if ( ( APC1SENSOR_HEADER_0 != data_buf[ 0 ] ) || 
         ( APC1SENSOR_HEADER_1 != data_buf[ 1 ] ) ||
         ( checksum != apc1sensor_calculate_checksum ( data_buf, 6 ) ) )
    {
        return APC1SENSOR_ERROR;
    }
    return APC1SENSOR_OK;
}

err_t apc1sensor_start_measurement ( apc1sensor_t *ctx )
{
    err_t error_flag = apc1sensor_send_command ( ctx, APC1SENSOR_CMD_SET_MODE, APC1SENSOR_MODE_MEASUREMENT );
    Delay_100ms ( );
    Delay_100ms ( );
    return error_flag;
}

err_t apc1sensor_sw_reset ( apc1sensor_t *ctx )
{
    err_t error_flag = apc1sensor_send_command ( ctx, APC1SENSOR_CMD_SET_MODE, APC1SENSOR_MODE_RESET );
    Delay_1sec ( );
    return error_flag;
}

err_t apc1sensor_read_info ( apc1sensor_t *ctx, apc1sensor_info_t *info )
{
    uint16_t checksum = 0;
    uint8_t reg = APC1SENSOR_ADDRESS_RESPONSE;
    uint8_t data_buf[ 23 ] = { 0 };
    if ( APC1SENSOR_ERROR == apc1sensor_send_command ( ctx, APC1SENSOR_CMD_GET_INFO, APC1SENSOR_MODE_IDLE ) )
    {
        return APC1SENSOR_ERROR;
    }
    Delay_100ms ( );
    Delay_100ms ( );
    if ( APC1SENSOR_ERROR == i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 23 ) )
    {
        return APC1SENSOR_ERROR;
    }
    checksum = ( ( uint16_t ) data_buf[ 21 ] << 8 ) | data_buf[ 22 ];
    if ( ( APC1SENSOR_HEADER_0 != data_buf[ 0 ] ) || 
         ( APC1SENSOR_HEADER_1 != data_buf[ 1 ] ) ||
         ( checksum != apc1sensor_calculate_checksum ( data_buf, 21 ) ) )
    {
        return APC1SENSOR_ERROR;
    }
    memcpy ( info->module_name, &data_buf[ 4 ], 6 );
    info->module_name[ 6 ] = 0;
    memcpy ( info->serial_num, &data_buf[ 10 ], 8 );
    memcpy ( info->fw_version, &data_buf[ 19 ], 2 );
    return APC1SENSOR_OK;
}

err_t apc1sensor_read_measurement ( apc1sensor_t *ctx, apc1sensor_measurement_t *measurement )
{
    uint16_t checksum = 0;
    uint8_t data_buf[ 64 ] = { 0 };
    if ( APC1SENSOR_ERROR == i2c_master_read( &ctx->i2c, data_buf, 64 ) )
    {
        return APC1SENSOR_ERROR;
    }
    checksum = ( ( uint16_t ) data_buf[ 62 ] << 8 ) | data_buf[ 63 ];
    if ( ( APC1SENSOR_HEADER_0 != data_buf[ 0 ] ) || 
         ( APC1SENSOR_HEADER_1 != data_buf[ 1 ] ) ||
         ( checksum != apc1sensor_calculate_checksum ( data_buf, 62 ) ) )
    {
        return APC1SENSOR_ERROR;
    }
    measurement->pm1_0 = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 5 ];
    measurement->pm2_5 = ( ( uint16_t ) data_buf[ 6 ] << 8 ) | data_buf[ 7 ];
    measurement->pm10 = ( ( uint16_t ) data_buf[ 8 ] << 8 ) | data_buf[ 9 ];
    measurement->pm1_0_air = ( ( uint16_t ) data_buf[ 10 ] << 8 ) | data_buf[ 11 ];
    measurement->pm2_5_air = ( ( uint16_t ) data_buf[ 12 ] << 8 ) | data_buf[ 13 ];
    measurement->pm10_air = ( ( uint16_t ) data_buf[ 14 ] << 8 ) | data_buf[ 15 ];
    measurement->part_over_0_3um = ( ( uint16_t ) data_buf[ 16 ] << 8 ) | data_buf[ 17 ];
    measurement->part_over_0_5um = ( ( uint16_t ) data_buf[ 18 ] << 8 ) | data_buf[ 19 ];
    measurement->part_over_1_0um = ( ( uint16_t ) data_buf[ 20 ] << 8 ) | data_buf[ 21 ];
    measurement->part_over_2_5um = ( ( uint16_t ) data_buf[ 22 ] << 8 ) | data_buf[ 23 ];
    measurement->part_over_5_0um = ( ( uint16_t ) data_buf[ 24 ] << 8 ) | data_buf[ 25 ];
    measurement->part_over_10um = ( ( uint16_t ) data_buf[ 26 ] << 8 ) | data_buf[ 27 ];
    measurement->tvoc = ( ( uint16_t ) data_buf[ 28 ] << 8 ) | data_buf[ 29 ];
    measurement->eco2 = ( ( uint16_t ) data_buf[ 30 ] << 8 ) | data_buf[ 31 ];
    measurement->t_comp = ( ( ( uint16_t ) data_buf[ 34 ] << 8 ) | data_buf[ 35 ] ) * 0.1f;
    measurement->rh_comp = ( ( ( uint16_t ) data_buf[ 36 ] << 8 ) | data_buf[ 37 ] ) * 0.1f;
    measurement->t_raw = ( ( ( uint16_t ) data_buf[ 38 ] << 8 ) | data_buf[ 39 ] ) * 0.1f;
    measurement->rh_raw = ( ( ( uint16_t ) data_buf[ 40 ] << 8 ) | data_buf[ 41 ] ) * 0.1f;
    measurement->rs0 = ( ( uint32_t ) data_buf[ 42 ] << 24 ) | ( ( uint32_t ) data_buf[ 43 ] << 16 ) | 
                       ( ( uint16_t ) data_buf[ 44 ] << 8 ) | data_buf[ 45 ];
    measurement->rs1 = ( ( uint32_t ) data_buf[ 46 ] << 24 ) | ( ( uint32_t ) data_buf[ 47 ] << 16 ) | 
                       ( ( uint16_t ) data_buf[ 48 ] << 8 ) | data_buf[ 49 ];
    measurement->rs2 = ( ( uint32_t ) data_buf[ 50 ] << 24 ) | ( ( uint32_t ) data_buf[ 51 ] << 16 ) | 
                       ( ( uint16_t ) data_buf[ 52 ] << 8 ) | data_buf[ 53 ];
    measurement->rs3 = ( ( uint32_t ) data_buf[ 54 ] << 24 ) | ( ( uint32_t ) data_buf[ 55 ] << 16 ) | 
                       ( ( uint16_t ) data_buf[ 56 ] << 8 ) | data_buf[ 57 ];
    measurement->aqi = data_buf[ 58 ];
    measurement->version = data_buf[ 60 ];
    measurement->error_code = data_buf[ 61 ];
    return APC1SENSOR_OK;
}

void apc1sensor_set_opmode ( apc1sensor_t *ctx, uint8_t opmode )
{
    switch ( opmode )
    {
        case APC1SENSOR_OPMODE_RESET:
        {
            digital_out_low ( &ctx->rst );
            break;
        }
        case APC1SENSOR_OPMODE_DEEP_SLEEP:
        {
            digital_out_high ( &ctx->rst );
            digital_out_low ( &ctx->set );
            break;
        }
        case APC1SENSOR_OPMODE_NORMAL:
        default:
        {
            digital_out_high ( &ctx->rst );
            digital_out_high ( &ctx->set );
            break;
        }
    }
    Delay_1sec ( );
}

void apc1sensor_reset_device ( apc1sensor_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1sec ( );
    digital_out_high ( &ctx->rst );
    Delay_1sec ( );
}

static err_t apc1sensor_send_command ( apc1sensor_t *ctx, uint8_t cmd, uint16_t mode )
{
    uint8_t data_buf[ 8 ] = { 0 };
    uint16_t checksum = 0;
    if ( ( ( APC1SENSOR_CMD_SET_MODE != cmd ) && 
           ( APC1SENSOR_CMD_GET_INFO != cmd ) ) || 
         ( ( APC1SENSOR_MODE_IDLE != mode ) && 
           ( APC1SENSOR_MODE_MEASUREMENT != mode ) && 
           ( APC1SENSOR_MODE_RESET != mode ) ) )
    {
        return APC1SENSOR_ERROR;
    }
    data_buf[ 0 ] = APC1SENSOR_ADDRESS_CMD;
    data_buf[ 1 ] = APC1SENSOR_HEADER_0;
    data_buf[ 2 ] = APC1SENSOR_HEADER_1;
    data_buf[ 3 ] = cmd;
    data_buf[ 4 ] = ( uint8_t ) ( ( mode >> 8 ) & 0xFF );
    data_buf[ 5 ] = ( uint8_t ) ( mode & 0xFF );
    checksum = apc1sensor_calculate_checksum ( &data_buf[ 1 ], 5 );
    data_buf[ 6 ] = ( uint8_t ) ( ( checksum >> 8 ) & 0xFF );
    data_buf[ 7 ] = ( uint8_t ) ( checksum & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 8 );
}

static uint16_t apc1sensor_calculate_checksum ( uint8_t *data_in, uint8_t len )
{
    uint16_t checksum = 0;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        checksum += data_in[ cnt ];
    }
    return checksum;
}

// ------------------------------------------------------------------------- END
