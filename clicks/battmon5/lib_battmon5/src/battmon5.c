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
 * @file battmon5.c
 * @brief BATT-MON 5 Click Driver.
 */

#include "battmon5.h"

/** 
 * @brief CRC8-ATM calculation function.
 * @details This function calculates CRC8-ATM with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x +1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input True
 * @li @c  Reflect output False
 * @li @c  Final NO XOR
 * @param[in] data_buf : Array of bytes to calculate CRC8-ATM from.
 * @param[in] len : Number of bytes to calculate CRC8-ATM from.
 * @return Calculated CRC8-ATM byte.
 * @note None.
 */
static uint8_t battmon5_calculate_crc ( uint8_t *data_buf, uint8_t len );

void battmon5_cfg_setup ( battmon5_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alarm = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = BATTMON5_DEVICE_ADDRESS;
}

err_t battmon5_init ( battmon5_t *ctx, battmon5_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alarm, cfg->alarm );

    return I2C_MASTER_SUCCESS;
}

err_t battmon5_default_cfg ( battmon5_t *ctx ) 
{
    err_t error_flag = BATTMON5_OK;
    error_flag |= battmon5_write_reg ( ctx, BATTMON5_REG_APA, BATTMON5_APA_2000MAH );
    error_flag |= battmon5_write_reg ( ctx, BATTMON5_REG_CHANGE_PARAM, BATTMON5_CHANGE_PARAM_3_7_V );
    error_flag |= battmon5_write_reg ( ctx, BATTMON5_REG_IC_POWER_MODE, BATTMON5_IC_POWER_MODE_NORMAL );
    Delay_100ms ( );
    error_flag |= battmon5_write_reg ( ctx, BATTMON5_REG_BATT_STATUS, BATTMON5_BATT_STATUS_CLEAR );
    return error_flag;
}

err_t battmon5_write_reg ( battmon5_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    uint8_t data_buf[ 5 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    data_buf[ 4 ] = battmon5_calculate_crc ( data_buf, 4 );
    return i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 4 );
}

err_t battmon5_read_reg ( battmon5_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    err_t error_flag = BATTMON5_OK;
    uint8_t data_buf[ 6 ] = { 0 };
    data_buf[ 0 ] = ( ctx->slave_address << 1 );
    data_buf[ 1 ] = reg;
    data_buf[ 2 ] = ( ctx->slave_address << 1 ) | 1;
    error_flag |= i2c_master_write_then_read( &ctx->i2c, &reg, 1, &data_buf[ 3 ], 3 );
    if ( ( BATTMON5_OK == error_flag ) && 
         ( data_buf[ 5 ] != battmon5_calculate_crc ( data_buf, 5 ) ) )
    {
        error_flag |= BATTMON5_ERROR;
    }
    if ( BATTMON5_OK == error_flag )
    {
        *data_out = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
    }
    return error_flag;
}

uint8_t battmon5_get_alarm_pin ( battmon5_t *ctx )
{
    return digital_in_read ( &ctx->alarm );
}

static uint8_t battmon5_calculate_crc ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0;
    uint8_t byte_cnt = 0;
    uint8_t bit_cnt = 0;
    for ( byte_cnt = 0; byte_cnt < len; byte_cnt++ ) 
    {
        crc ^= data_buf[ byte_cnt ];
        for ( bit_cnt = 0; bit_cnt < 8; bit_cnt++ ) 
        {
            if ( crc & 0x80 ) 
            {
                crc = ( crc << 1 ) ^ 0x07;
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
