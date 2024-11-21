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
 * @file current14.c
 * @brief Current 14 Click Driver.
 */

#include "current14.h"

void current14_cfg_setup ( current14_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->alert = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_FULL;
    cfg->i2c_address = CURRENT14_DEVICE_ADDRESS_0;
}

err_t current14_init ( current14_t *ctx, current14_cfg_t *cfg ) 
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

    digital_in_init( &ctx->alert, cfg->alert );

    return I2C_MASTER_SUCCESS;
}

err_t current14_default_cfg ( current14_t *ctx ) 
{
    err_t error_flag = CURRENT14_OK;
    // Enable device
    error_flag |= current14_write_reg_byte ( ctx, CURRENT14_REG_CNTL1, CURRENT14_CNTL1_PC1_ACTIVE );
    Delay_1sec ( );
    // Unlock device config
    error_flag |= current14_write_reg_word ( ctx, CURRENT14_REG_CNTL4_LSB, CURRENT14_CNTL4_RELEASE );
    // Enable alert/drdy pin output
    error_flag |= current14_write_reg_byte ( ctx, CURRENT14_REG_CNTL2, CURRENT14_CNTL2_ALERT_EN );
    // Set output data rate
    error_flag |= current14_set_odr ( ctx, CURRENT14_ODR_200_HZ );
    // Start continuous measurement
    error_flag |= current14_write_reg_byte ( ctx, CURRENT14_REG_CNTL3, CURRENT14_CNTL3_FORCE );
    return error_flag;
}

err_t current14_write_reg_byte ( current14_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t current14_write_reg_word ( current14_t *ctx, uint8_t reg, uint16_t data_in )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = reg;
    data_buf[ 1 ] = ( uint8_t ) ( data_in & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( data_in >> 8 ) & 0xFF );
    return i2c_master_write( &ctx->i2c, data_buf, 3 );
}

err_t current14_read_reg_byte ( current14_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

uint8_t current14_get_alert_pin ( current14_t *ctx )
{
    return digital_in_read ( &ctx->alert );
}

err_t current14_set_odr ( current14_t *ctx, uint8_t odr )
{
    if ( odr > CURRENT14_ODR_1_KHZ )
    {
        return CURRENT14_ERROR;
    }
    uint8_t reg_data = 0;
    err_t error_flag = current14_read_reg_byte ( ctx, CURRENT14_REG_CNTL1, &reg_data );
    if ( CURRENT14_OK == error_flag )
    {
        reg_data &= ( ~CURRENT14_CNTL1_ODR_MASK );
        reg_data |= ( odr << 3 );
        error_flag |= current14_write_reg_byte ( ctx, CURRENT14_REG_CNTL1, reg_data );
        if ( CURRENT14_ODR_20_HZ == odr )
        {
            ctx->odr = 20;
        }
        else if ( CURRENT14_ODR_100_HZ == odr )
        {
            ctx->odr = 100;
        }
        else if ( CURRENT14_ODR_200_HZ == odr )
        {
            ctx->odr = 200;
        }
        else if ( CURRENT14_ODR_1_KHZ == odr )
        {
            ctx->odr = 1000;
        }
    }
    return error_flag;
}

err_t current14_read_data ( current14_t *ctx, int16_t *data_out )
{
    uint8_t data_buf[ 3 ] = { 0 };
    uint8_t reg_addr = CURRENT14_REG_STA1;
    err_t error_flag = i2c_master_write_then_read( &ctx->i2c, &reg_addr, 1, data_buf, 3 );
    if ( ( CURRENT14_OK == error_flag ) && ( NULL != data_out ) )
    {
        *data_out = ( ( int16_t ) data_buf[ 2 ] << 8 ) | data_buf[ 1 ];
    }
    return error_flag;
}

err_t current14_calib_offset ( current14_t *ctx )
{
    int16_t raw_data = 0;
    int32_t raw_data_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < ctx->odr )
    {
        if ( current14_get_alert_pin ( ctx ) )
        {
            if ( CURRENT14_OK == current14_read_data ( ctx, &raw_data ) )
            {
                raw_data_sum += raw_data;
                cnt++;
            }
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > CURRENT14_TIMEOUT_MS )
        {
            return CURRENT14_ERROR;
        }
    }
    raw_data = ( int16_t ) ( raw_data_sum / ctx->odr );
    ctx->zero_curr_offset = raw_data;
    return CURRENT14_OK;
}

err_t current14_calib_resolution ( current14_t *ctx, float calib_current )
{
    int16_t raw_data = 0;
    int32_t raw_data_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < ctx->odr )
    {
        if ( current14_get_alert_pin ( ctx ) )
        {
            if ( CURRENT14_OK == current14_read_data ( ctx, &raw_data ) )
            {
                raw_data_sum += raw_data;
                cnt++;
            }
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > CURRENT14_TIMEOUT_MS )
        {
            return CURRENT14_ERROR;
        }
    }
    raw_data = ( int16_t ) ( raw_data_sum / ctx->odr );
    ctx->data_resolution = calib_current / ( raw_data - ctx->zero_curr_offset );
    return CURRENT14_OK;
}

err_t current14_get_current ( current14_t *ctx, float *current )
{
    int16_t raw_data = 0;
    int32_t raw_data_sum = 0;
    uint16_t cnt = 0;
    uint16_t timeout_cnt = 0;
    while ( cnt < ctx->odr )
    {
        if ( current14_get_alert_pin ( ctx ) )
        {
            if ( CURRENT14_OK == current14_read_data ( ctx, &raw_data ) )
            {
                raw_data_sum += raw_data;
                cnt++;
            }
        }
        Delay_1ms ( );
        if ( ++timeout_cnt > CURRENT14_TIMEOUT_MS )
        {
            return CURRENT14_ERROR;
        }
    }
    raw_data = ( int16_t ) ( raw_data_sum / ctx->odr );
    *current = ( raw_data - ctx->zero_curr_offset ) * ctx->data_resolution;
    return CURRENT14_OK;
}

// ------------------------------------------------------------------------- END
