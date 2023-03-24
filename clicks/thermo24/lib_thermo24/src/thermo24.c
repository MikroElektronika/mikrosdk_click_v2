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
 * @file thermo24.c
 * @brief Thermo 24 Click Driver.
 */

#include "thermo24.h"

/**
 * @brief Thermo 24 crc constants.
 * @details Specified constants for crc of Thermo 24 Click driver.
 */
#define THERMO24_POLYNOM                    0x31
#define THERMO24_INIT_VALUE                 0xFF

/** 
 * @brief Thermo 24 Dallas/Maxim calculation for CRC8 function.
 * @details This function calculates CRC8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 +1)
 * @li @c  Initialization 0xFF
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @li @c  Example CRC(0xBEEF) = 0x92
 * @param[in] crc_source : Word to calculate crc from.
 * @return Calculated CRC8 output.
 * @note None.
 */
static uint8_t thermo24_calculate_crc ( uint16_t crc_source );

void thermo24_cfg_setup ( thermo24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = THERMO24_SET_DEVICE_ADDRESS;
}

err_t thermo24_init ( thermo24_t *ctx, thermo24_cfg_t *cfg ) 
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

err_t thermo24_soft_reset ( thermo24_t *ctx )
{
    uint8_t command = THERMO24_CMD_SOFT_RESET;
    err_t error_flag = i2c_master_write( &ctx->i2c, &command, 1 );
    Delay_1sec ( );
    return error_flag;
}

err_t thermo24_read_serial ( thermo24_t *ctx, uint32_t *serial_num )
{
    uint8_t command = THERMO24_CMD_READ_SERIAL;
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = i2c_master_write( &ctx->i2c, &command, 1 );
    Delay_1ms ( );
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 6 );
    if ( ( THERMO24_OK == error_flag ) &&
         ( data_buf[ 2 ] == thermo24_calculate_crc ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) ) &&
         ( data_buf[ 5 ] == thermo24_calculate_crc ( ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ] ) ) )
    {
        *serial_num = ( ( uint32_t ) data_buf[ 0 ] << 24 ) | ( ( uint32_t ) data_buf[ 1 ] << 16 ) | 
                      ( ( uint16_t ) data_buf[ 3 ] << 8 ) | data_buf[ 4 ];
        return THERMO24_OK;
    }
    return THERMO24_ERROR;
}

err_t thermo24_read_temperature ( thermo24_t *ctx, uint8_t precision, float *temperature )
{
    uint8_t command = 0;
    uint8_t data_buf[ 6 ] = { 0 };
    err_t error_flag = THERMO24_OK;
    switch ( precision )
    {
        case THERMO24_MEASURE_PRECISION_LOW:
        {
            command = THERMO24_CMD_MEASURE_LOWEST_PRECISION;
            error_flag |= i2c_master_write( &ctx->i2c, &command, 1 );
            Delay_1ms ( );
            Delay_1ms ( );
            break;
        }
        case THERMO24_MEASURE_PRECISION_MEDIUM:
        {
            command = THERMO24_CMD_MEASURE_MEDIUM_PRECISION;
            error_flag |= i2c_master_write( &ctx->i2c, &command, 1 );
            Delay_5ms ( );
            break;
        }
        case THERMO24_MEASURE_PRECISION_HIGH:
        {
            command = THERMO24_CMD_MEASURE_HIGH_PRECISION;
            error_flag |= i2c_master_write( &ctx->i2c, &command, 1 );
            Delay_10ms ( );
            break;
        }
        default:
        {
            return THERMO24_ERROR;
        }
    }
    error_flag |= i2c_master_read( &ctx->i2c, data_buf, 3 );
    if ( ( THERMO24_OK == error_flag ) &&
         ( data_buf[ 2 ] == thermo24_calculate_crc ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) ) )
    {
        *temperature = THERMO24_TEMP_MULTIPLIER_CELSIUS * 
                       ( ( float ) ( ( ( uint16_t ) data_buf[ 0 ] << 8 ) | data_buf[ 1 ] ) / THERMO24_TEMP_RESOLUTION ) - 
                       THERMO24_TEMP_OFFSET;
        return THERMO24_OK;
    }
    return THERMO24_ERROR;
}

static uint8_t thermo24_calculate_crc ( uint16_t crc_source )
{
    uint8_t crc = THERMO24_INIT_VALUE;
    uint8_t src_buf[ 2 ] = { 0 };
    src_buf[ 0 ] = crc_source >> 8;
    src_buf[ 1 ] = crc_source;
    for ( uint8_t byte_cnt = 0; byte_cnt < 2; byte_cnt++ ) 
    {
        crc ^= src_buf[ byte_cnt ];
        for ( uint8_t bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( ( crc & 0x80 ) != 0 )
            {
                crc = ( uint8_t ) ( ( crc << 1 ) ^ THERMO24_POLYNOM );
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
