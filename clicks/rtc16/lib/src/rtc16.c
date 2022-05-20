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
 * @file rtc16.c
 * @brief RTC 16 Click Driver.
 */

#include "rtc16.h"
#include "conversions.h"

void rtc16_cfg_setup ( rtc16_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC16_DEVICE_ADDRESS;
}

err_t rtc16_init ( rtc16_t *ctx, rtc16_cfg_t *cfg ) 
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

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc16_default_cfg ( rtc16_t *ctx ) 
{
    err_t error_flag = RTC16_OK;
    
    error_flag |= rtc16_write_register ( ctx, RTC16_REG_CONTROL1, RTC16_CONTROL1_ALARM_A_DISABLE |  
                                                                  RTC16_CONTROL1_ALARM_B_DISABLE | 
                                                                  RTC16_CONTROL1_CT_EVERY_SECOND );
    
    error_flag |= rtc16_write_register ( ctx, RTC16_REG_CONTROL2, RTC16_CONTROL2_24HOUR_TIME |  
                                                                  RTC16_CONTROL2_CLOCK_ENABLE );

    return error_flag;
}

err_t rtc16_write_register ( rtc16_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > RTC16_REG_CONTROL2 )
    {
        return RTC16_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg << 4;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t rtc16_write_multiple_registers ( rtc16_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    if ( ( reg > RTC16_REG_CONTROL2 ) || ( tx_len > 16 ) )
    {
        return RTC16_ERROR;
    }
    uint8_t data_buf[ 17 ] = { 0 };
    data_buf[ 0 ] = reg << 4;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t rtc16_read_register ( rtc16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > RTC16_REG_CONTROL2 )
    {
        return RTC16_ERROR;
    }
    reg = reg << 4;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t rtc16_read_register_fast ( rtc16_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > RTC16_REG_CONTROL2 )
    {
        return RTC16_ERROR;
    }
    reg = ( reg << 4 ) | RTC16_FAST_READ_BIT;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t rtc16_read_multiple_registers ( rtc16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    if ( ( reg > RTC16_REG_CONTROL2 ) || ( rx_len > 16 ) )
    {
        return RTC16_ERROR;
    }
    reg = reg << 4;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t rtc16_read_multiple_registers_fast ( rtc16_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    if ( ( reg > RTC16_REG_CONTROL2 ) || ( rx_len > 16 ) )
    {
        return RTC16_ERROR;
    }
    reg = ( reg << 4 ) | RTC16_FAST_READ_BIT;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t rtc16_get_int_pin ( rtc16_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc16_clear_interrupts ( rtc16_t *ctx )
{
    uint8_t reg_data;
    if ( RTC16_ERROR == rtc16_read_register ( ctx, RTC16_REG_CONTROL2, &reg_data ) )
    {
        return RTC16_ERROR;
    }
    reg_data &= ~RTC16_CONTROL2_CLEAR_INTERRUPT;
    reg_data &= ~RTC16_CONTROL2_CLEAR_ALARM_A;
    reg_data &= ~RTC16_CONTROL2_CLEAR_ALARM_B;
    return rtc16_write_register( ctx, RTC16_REG_CONTROL2, reg_data );
}

err_t rtc16_set_time ( rtc16_t *ctx, rtc16_time_t *time )
{
    uint8_t reg_data[ 3 ];
    reg_data[ 0 ] = dec_to_bcd ( time->second );
    reg_data[ 1 ] = dec_to_bcd ( time->minute );
    reg_data[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC16_ERROR == rtc16_write_multiple_registers ( ctx, RTC16_REG_SECOND_COUNTER, reg_data, 3 ) )
    {
        return RTC16_ERROR;
    }
    return RTC16_OK;
}

err_t rtc16_read_time ( rtc16_t *ctx, rtc16_time_t *time )
{
    uint8_t reg_data[ 3 ];
    if ( RTC16_ERROR == rtc16_read_multiple_registers ( ctx, RTC16_REG_SECOND_COUNTER, reg_data, 3 ) )
    {
        return RTC16_ERROR;
    }
    time->second = bcd_to_dec ( reg_data[ 0 ] );
    time->minute = bcd_to_dec ( reg_data[ 1 ] );
    time->hour = bcd_to_dec ( reg_data[ 2 ] );
    return RTC16_OK;
}

err_t rtc16_set_date ( rtc16_t *ctx, rtc16_date_t *date )
{
    uint8_t reg_data[ 4 ];
    reg_data[ 0 ] = dec_to_bcd ( date->day_of_week );
    reg_data[ 1 ] = dec_to_bcd ( date->day );
    reg_data[ 2 ] = dec_to_bcd ( date->month );
    reg_data[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC16_ERROR == rtc16_write_multiple_registers ( ctx, RTC16_REG_DAY_OF_WEEK_COUNTER, reg_data, 4 ) )
    {
        return RTC16_ERROR;
    }
    return RTC16_OK;
}

err_t rtc16_read_date ( rtc16_t *ctx, rtc16_date_t *date )
{
    uint8_t reg_data[ 4 ];
    if ( RTC16_ERROR == rtc16_read_multiple_registers ( ctx, RTC16_REG_DAY_OF_WEEK_COUNTER, reg_data, 4 ) )
    {
        return RTC16_ERROR;
    }
    date->day_of_week = reg_data[ 0 ];
    date->day = bcd_to_dec ( reg_data[ 1 ] );
    date->month = bcd_to_dec ( reg_data[ 2 ] );
    date->year = bcd_to_dec ( reg_data[ 3 ] );
    return RTC16_OK;
}

// ------------------------------------------------------------------------- END
