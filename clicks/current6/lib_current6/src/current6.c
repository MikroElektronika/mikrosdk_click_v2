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
 * @file current6.c
 * @brief Current 6 Click Driver.
 */

#include "current6.h"

/** 
 * @brief PEC calculation function.
 * @details This function calculates PEC (CRC8) with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x07 (x8 + x2 + x +1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final XOR 0x00
 * @param[in] data_buf : Array of bytes to calculate PEC from (with slave address write/read bytes).
 * @param[in] len : Number of bytes to calculate PEC from.
 * @return Calculated PEC byte.
 * @note None.
 */
static uint8_t current6_calculate_pec ( uint8_t *data_buf, uint8_t len );

void current6_cfg_setup ( current6_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alr  = HAL_PIN_NC;
    cfg->en   = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = CURRENT6_SET_DEV_ADDR;
}

err_t current6_init ( current6_t *ctx, current6_cfg_t *cfg ) 
{
    i2c_master_config_t i2c_cfg;
    
    digital_out_init( &ctx->en, cfg->en );
    current6_disable_device ( ctx );
    Delay_100ms ( );
    current6_enable_device ( ctx );
    Delay_100ms ( );

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
    
    digital_in_init( &ctx->alr, cfg->alr );

    return I2C_MASTER_SUCCESS;
}

err_t current6_default_cfg ( current6_t *ctx ) 
{
    err_t error_flag = CURRENT6_OK;
    ctx->pec_enable = CURRENT6_PEC_ENABLE; // default at POR
    uint16_t read_word = 0;
    uint16_t write_word = CURRENT6_FIFO_CFG_FLUSH;
    error_flag |= current6_write_word ( ctx, CURRENT6_REG_FIFO_CONFIGURATION, write_word );
    Delay_100ms ( );
    write_word = CURRENT6_OPMODE_ACTIVE_MODE_1_SPS | 
                 CURRENT6_PEC_ENABLE | 
                 CURRENT6_INPUT_RANGE_50mV | 
                 CURRENT6_ADC_SAMPLE_RATE_0p5_KSPS | 
                 CURRENT6_DIGITAL_FILTER_AVG_128_SAMPLES;
    error_flag |= current6_write_word ( ctx, CURRENT6_REG_CONFIGURATION, write_word );
    error_flag |= current6_read_word ( ctx, CURRENT6_REG_CONFIGURATION, &read_word );
    if ( write_word != read_word )
    {
        return CURRENT6_ERROR;
    }
    Delay_100ms ( );
    write_word = CURRENT6_FIFO_CFG_STORE_ALL | 
                 CURRENT6_FIFO_CFG_DATA_OVERFLOW_DEFAULT | 
                 CURRENT6_FIFO_CFG_ROLL_OVER;
    error_flag |= current6_write_word ( ctx, CURRENT6_REG_FIFO_CONFIGURATION, write_word );
    error_flag |= current6_read_word ( ctx, CURRENT6_REG_FIFO_CONFIGURATION, &read_word );
    if ( write_word != read_word )
    {
        return CURRENT6_ERROR;
    }
    return error_flag;
}

err_t current6_write_byte ( current6_t *ctx, uint8_t reg, uint8_t data_in ) 
{
    if ( ( ( reg < CURRENT6_REG_THRESHOLD_OVER_CURRENT ) || 
           ( reg > CURRENT6_REG_WAKE_UP_CURRENT ) ) && 
         ( CURRENT6_REG_INT_EN != reg ) )
    {
        return CURRENT6_ERROR;
    }
    if ( CURRENT6_PEC_ENABLE == ctx->pec_enable )
    {
        uint8_t data_buf[ 4 ] = { 0 };
        data_buf[ 0 ] = ctx->slave_address << 1;
        data_buf[ 1 ] = reg;
        data_buf[ 2 ] = data_in;
        data_buf[ 3 ] = current6_calculate_pec( data_buf, 3 );
        return i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 3 );
    }
    else
    {
        uint8_t data_buf[ 2 ] = { 0 };
        data_buf[ 0 ] = reg;
        data_buf[ 1 ] = data_in;
        return i2c_master_write( &ctx->i2c, data_buf, 2 );
    }
}

err_t current6_read_byte ( current6_t *ctx, uint8_t reg, uint8_t *data_out ) 
{
    if ( ( ( reg < CURRENT6_REG_THRESHOLD_OVER_CURRENT ) || 
           ( reg > CURRENT6_REG_WAKE_UP_CURRENT ) ) && 
         ( CURRENT6_REG_INT_EN != reg ) )
    {
        return CURRENT6_ERROR;
    }
    if ( CURRENT6_PEC_ENABLE == ctx->pec_enable )
    {
        uint8_t data_buf[ 5 ] = { 0 };
        data_buf[ 0 ] = ctx->slave_address << 1;
        data_buf[ 1 ] = reg;
        data_buf[ 2 ] = ( ctx->slave_address << 1 ) | 1;
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, &data_buf[ 3 ], 2 );
        if ( data_buf[ 4 ] == current6_calculate_pec( data_buf, 4 ) )
        {
            *data_out = data_buf[ 3 ];
            return error_flag;
        }
        return CURRENT6_ERROR;
    }
    else
    {
        return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
    }
}

err_t current6_write_word ( current6_t *ctx, uint8_t reg, uint16_t data_in ) 
{
    if ( ( CURRENT6_REG_CONFIGURATION != reg ) && 
         ( CURRENT6_REG_STATUS != reg ) &&
         ( CURRENT6_REG_FIFO_CONFIGURATION != reg ) )
    {
        return CURRENT6_ERROR;
    }
    uint8_t data_buf[ 5 ] = { 0 };
    if ( CURRENT6_PEC_ENABLE == ctx->pec_enable )
    {
        data_buf[ 0 ] = ctx->slave_address << 1;
        data_buf[ 1 ] = reg;
        data_buf[ 2 ] = ( uint8_t ) ( data_in & 0xFF );
        data_buf[ 3 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        data_buf[ 4 ] = current6_calculate_pec( data_buf, 4 );
        return i2c_master_write( &ctx->i2c, &data_buf[ 1 ], 4 );
    }
    else
    {
        data_buf[ 0 ] = reg;
        data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
        data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
        return i2c_master_write( &ctx->i2c, data_buf, 3 );
    }
}

err_t current6_read_word ( current6_t *ctx, uint8_t reg, uint16_t *data_out ) 
{
    if ( ( CURRENT6_REG_CONFIGURATION != reg ) && 
         ( CURRENT6_REG_STATUS != reg ) &&
         ( ( reg < CURRENT6_REG_MAX_PEAK_CURRENT ) ||
           ( reg > CURRENT6_REG_VOLTAGE_MEASUREMENT ) ) )
    {
        return CURRENT6_ERROR;
    }
    uint8_t data_buf[ 6 ] = { 0 };
    if ( CURRENT6_PEC_ENABLE == ctx->pec_enable )
    {
        data_buf[ 0 ] = ctx->slave_address << 1;
        data_buf[ 1 ] = reg;
        data_buf[ 2 ] = ( ctx->slave_address << 1 ) | 1;
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, &data_buf[ 3 ], 3 );
        
        uint8_t pec = current6_calculate_pec( data_buf, 5 );
        if ( data_buf[ 5 ] == pec )
        {
            *data_out = ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
            return error_flag;
        }
        return CURRENT6_ERROR;
    }
    else
    {
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 2 );
        *data_out = ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return error_flag;
    }
}

err_t current6_read_32 ( current6_t *ctx, uint32_t *data_out )
{
    uint8_t reg = CURRENT6_REG_CURRENT_VOLTAGE_MEASUREMENT;
    if ( CURRENT6_PEC_ENABLE == ctx->pec_enable )
    {
        uint8_t data_buf[ 8 ] = { 0 };
        data_buf[ 0 ] = ctx->slave_address << 1;
        data_buf[ 1 ] = reg;
        data_buf[ 2 ] = ( ctx->slave_address << 1 ) | 1;
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, &data_buf[ 3 ], 5 );
        if ( data_buf[ 7 ] == current6_calculate_pec( data_buf, 7 ) )
        {
            *data_out = ( ( uint32_t ) data_buf[ 6 ] << 24 ) | ( ( uint32_t ) data_buf[ 5 ] << 16 ) | 
                        ( ( uint16_t ) data_buf[ 4 ] << 8 ) | data_buf[ 3 ];
            return error_flag;
        }
        return CURRENT6_ERROR;
    }
    else
    {
        uint8_t data_buf[ 4 ] = { 0 };
        err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, 4 );
        *data_out = ( ( uint32_t ) data_buf[ 3 ] << 24 ) | ( ( uint32_t ) data_buf[ 2 ] << 16 ) | 
                    ( ( uint16_t ) data_buf[ 1 ] << 8 ) | data_buf[ 0 ];
        return error_flag;
    }
}

uint8_t current6_get_alert_pin ( current6_t *ctx )
{
    return digital_in_read ( &ctx->alr );
}

err_t current6_read_data ( current6_t *ctx, float *voltage, float *current )
{
    uint32_t raw_data = 0;
    if ( CURRENT6_OK == current6_read_32 ( ctx, &raw_data ) )
    {
        if ( raw_data & CURRENT6_FIFO_DATA_VALID_32 )
        {
            uint16_t config = 0;
            if ( CURRENT6_OK == current6_read_word ( ctx, CURRENT6_REG_CONFIGURATION, &config ) )
            {
                uint16_t raw_voltage = ( uint16_t ) ( ( raw_data >> 16 ) & CURRENT6_FIFO_DATA_RESOLUTION );
                int16_t raw_current = ( int16_t ) ( raw_data & CURRENT6_FIFO_DATA_RESOLUTION ) | 
                                                  ( raw_data & CURRENT6_FIFO_DATA_SIGN_BIT );
                raw_current = ( raw_current ^ CURRENT6_FIFO_DATA_SIGN_BIT ) - CURRENT6_FIFO_DATA_SIGN_BIT;
                
                *voltage = raw_voltage * CURRENT6_VOLTAGE_CALCULATION_COEFFICIENT;
                *current = raw_current * CURRENT6_CURRENT_CALCULATION_COEFFICIENT;
                if ( config & CURRENT6_INPUT_RANGE_10mV )
                {
                    *current /= 5;
                }
                return CURRENT6_OK;
            }
                
        }
    }
    return CURRENT6_ERROR;
}

err_t current6_get_status ( current6_t *ctx, uint16_t *status )
{
    if ( CURRENT6_OK == current6_read_word ( ctx, CURRENT6_REG_STATUS, status ) )
    {
        // clear status flags
        if ( CURRENT6_OK == current6_write_word ( ctx, CURRENT6_REG_STATUS, *status ) ) 
        {
            return CURRENT6_OK;
        }
    }
    return CURRENT6_ERROR;
}

err_t current6_enable_pec ( current6_t *ctx )
{
    uint16_t rx_data = 0;
    err_t error_flag = current6_read_word ( ctx, CURRENT6_REG_CONFIGURATION, &rx_data );
    rx_data |= CURRENT6_PEC_ENABLE;
    error_flag |= current6_write_word ( ctx, CURRENT6_REG_CONFIGURATION, rx_data );
    if ( CURRENT6_OK == error_flag )
    {
        ctx->pec_enable = CURRENT6_PEC_ENABLE;
    }
    return error_flag;
}

err_t current6_disable_pec ( current6_t *ctx )
{
    uint16_t rx_data = 0;
    err_t error_flag = current6_read_word ( ctx, CURRENT6_REG_CONFIGURATION, &rx_data );
    rx_data &= ~CURRENT6_PEC_ENABLE;
    error_flag |= current6_write_word ( ctx, CURRENT6_REG_CONFIGURATION, rx_data );
    if ( CURRENT6_OK == error_flag )
    {
        ctx->pec_enable = CURRENT6_PEC_DISABLE;
    }
    return error_flag;
}

void current6_enable_device ( current6_t *ctx )
{
    digital_out_high ( &ctx->en );
}

void current6_disable_device ( current6_t *ctx )
{
    digital_out_low ( &ctx->en );
}

static uint8_t current6_calculate_pec ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    uint8_t cnt_len = 0;
    uint8_t cnt_bit = 0;
    for ( cnt_len = 0; cnt_len < len; cnt_len++ ) 
    {
        crc ^= data_buf[ cnt_len ];
        for ( cnt_bit = 0; cnt_bit < 8; cnt_bit++ ) 
        {
            if ( crc & 0x80 )
            {    
                crc = ( uint8_t )( ( crc << 1 ) ^ 0x07 );
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
