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
 * @file thermo26.c
 * @brief Thermo 26 Click Driver.
 */

#include "thermo26.h"

/**
 * @brief Thermo 26 crc constants.
 * @details Specified constants for crc of Thermo 26 Click driver.
 */
#define THERMO26_POLYNOM                0x31
#define THERMO26_INIT_VALUE             0xFF

/** 
 * @brief Thermo 26 Dallas/Maxim calculation for CRC8 function.
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
static uint8_t thermo26_calculate_crc ( uint8_t *crc_source );

void thermo26_cfg_setup ( thermo26_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->rst = HAL_PIN_NC;
    cfg->alt = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO26_DEVICE_ADDRESS_0;
}

err_t thermo26_init ( thermo26_t *ctx, thermo26_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alt, cfg->alt );

    return I2C_MASTER_SUCCESS;
}

err_t thermo26_write_command ( thermo26_t *ctx, uint16_t cmd )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = ( uint8_t ) ( ( cmd >> 8 ) & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( cmd & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t thermo26_read_command ( thermo26_t *ctx, uint16_t cmd, uint16_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    err_t error_flag = thermo26_write_command ( ctx, cmd );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( ( THERMO26_OK == error_flag ) && ( data_buf[ 2 ] == thermo26_calculate_crc ( data_buf ) ) )
    {
        *data_out = ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ];
        return THERMO26_OK;
    }
    return THERMO26_ERROR;
}

void thermo26_reset_device ( thermo26_t *ctx )
{
    digital_out_low ( &ctx->rst );
    Delay_1ms ( );
    digital_out_high ( &ctx->rst );
    Delay_100ms ( );
}

void thermo26_set_rst_pin ( thermo26_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->rst, state );
}

uint8_t thermo26_get_alert_pin ( thermo26_t *ctx )
{
    return digital_in_read ( &ctx->alt );
}

err_t thermo26_read_temperature ( thermo26_t *ctx, float *temperature )
{
    uint16_t raw_temp;
    if ( THERMO26_OK == thermo26_read_command ( ctx, THERMO26_CMD_FETCH_DATA, &raw_temp ) )
    {
        *temperature = THERMO26_ABS_MIN_TEMP + 
                       ( THERMO26_ABS_MAX_TEMP - THERMO26_ABS_MIN_TEMP ) * raw_temp / THERMO26_DATA_RESOLUTION;
        return THERMO26_OK;
    }
    return THERMO26_ERROR;
}

err_t thermo26_read_serial_num ( thermo26_t *ctx, uint32_t *serial_num )
{
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = thermo26_write_command ( ctx, THERMO26_CMD_GET_SERIAL_NUM );
    Delay_1ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( THERMO26_OK == error_flag ) && 
         ( data_buf[ 2 ] == thermo26_calculate_crc ( &data_buf[ 0 ] ) ) &&
         ( data_buf[ 5 ] == thermo26_calculate_crc ( &data_buf[ 3 ] ) ) )
    {
        *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) |
                      ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
        return THERMO26_OK;
    }
    return THERMO26_ERROR;
}

err_t thermo26_start_measurement ( thermo26_t *ctx, uint16_t cmd )
{
    err_t error_flag = thermo26_write_command ( ctx, cmd );
    Delay_10ms ( );
    Delay_10ms ( );
    return error_flag;
}

err_t thermo26_stop_measurement ( thermo26_t *ctx )
{
    err_t error_flag = thermo26_write_command ( ctx, THERMO26_CMD_BREAK );
    Delay_1ms ( );
    return error_flag;
}

static uint8_t thermo26_calculate_crc ( uint8_t *crc_source )
{
    uint8_t crc = THERMO26_INIT_VALUE;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= crc_source[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ THERMO26_POLYNOM );
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
