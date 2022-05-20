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
 * @file rtc17.c
 * @brief RTC 17 Click Driver.
 */

#include "rtc17.h"
#include "conversions.h"

void rtc17_cfg_setup ( rtc17_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC17_SET_DEVICE_ADDRESS;
}

err_t rtc17_init ( rtc17_t *ctx, rtc17_cfg_t *cfg ) 
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

err_t rtc17_default_cfg ( rtc17_t *ctx ) 
{
    err_t error_flag = RTC17_OK;
    
    error_flag |= rtc17_write_register ( ctx, RTC17_REG_CONTROL1, RTC17_CONTROL1_ALARM_W_DISABLE |  
                                                                  RTC17_CONTROL1_ALARM_D_DISABLE | 
                                                                  RTC17_CONTROL1_24HOUR_TIME |  
                                                                  RTC17_CONTROL1_CLOCK1_ENABLE | 
                                                                  RTC17_CONTROL1_CT_EVERY_SECOND );

    return error_flag;
}

err_t rtc17_write_register ( rtc17_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > RTC17_REG_CONTROL2 )
    {
        return RTC17_ERROR;
    }
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] = reg << 4;
    data_buf[ 1 ] = data_in;
    return i2c_master_write( &ctx->i2c, data_buf, 2 );
}

err_t rtc17_write_multiple_registers ( rtc17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len )
{
    if ( ( reg > RTC17_REG_CONTROL2 ) || ( tx_len > 17 ) )
    {
        return RTC17_ERROR;
    }
    uint8_t data_buf[ 17 ] = { 0 };
    data_buf[ 0 ] = reg << 4;
    for ( uint8_t cnt = 0; cnt < tx_len; cnt++ )
    {
        data_buf[ cnt + 1 ] = tx_buf[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t rtc17_read_register ( rtc17_t *ctx, uint8_t reg, uint8_t *data_out )
{
    if ( reg > RTC17_REG_CONTROL2 )
    {
        return RTC17_ERROR;
    }
    reg = reg << 4;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, 1 );
}

err_t rtc17_read_multiple_registers ( rtc17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len )
{
    if ( ( reg > RTC17_REG_CONTROL2 ) || ( rx_len > 17 ) )
    {
        return RTC17_ERROR;
    }
    reg = reg << 4;
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

uint8_t rtc17_get_int_pin ( rtc17_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc17_clear_interrupts ( rtc17_t *ctx )
{
    uint8_t reg_data;
    if ( RTC17_ERROR == rtc17_read_register ( ctx, RTC17_REG_CONTROL2, &reg_data ) )
    {
        return RTC17_ERROR;
    }
    reg_data &= ~RTC17_CONTROL2_CLEAR_INTERRUPT;
    reg_data &= ~RTC17_CONTROL2_CLEAR_ALARM_W;
    reg_data &= ~RTC17_CONTROL2_CLEAR_ALARM_D;
    return rtc17_write_register( ctx, RTC17_REG_CONTROL2, reg_data );
}

err_t rtc17_set_time ( rtc17_t *ctx, rtc17_time_t *time )
{
    uint8_t reg_data[ 3 ];
    reg_data[ 0 ] = dec_to_bcd ( time->second );
    reg_data[ 1 ] = dec_to_bcd ( time->minute );
    reg_data[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC17_ERROR == rtc17_write_multiple_registers ( ctx, RTC17_REG_SECOND_COUNTER, reg_data, 3 ) )
    {
        return RTC17_ERROR;
    }
    return RTC17_OK;
}

err_t rtc17_read_time ( rtc17_t *ctx, rtc17_time_t *time )
{
    uint8_t reg_data[ 3 ];
    if ( RTC17_ERROR == rtc17_read_multiple_registers ( ctx, RTC17_REG_SECOND_COUNTER, reg_data, 3 ) )
    {
        return RTC17_ERROR;
    }
    time->second = bcd_to_dec ( reg_data[ 0 ] );
    time->minute = bcd_to_dec ( reg_data[ 1 ] );
    time->hour = bcd_to_dec ( reg_data[ 2 ] );
    return RTC17_OK;
}

err_t rtc17_set_date ( rtc17_t *ctx, rtc17_date_t *date )
{
    uint8_t reg_data[ 4 ];
    reg_data[ 0 ] = dec_to_bcd ( date->day_of_week );
    reg_data[ 1 ] = dec_to_bcd ( date->day );
    reg_data[ 2 ] = dec_to_bcd ( date->month );
    reg_data[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC17_ERROR == rtc17_write_multiple_registers ( ctx, RTC17_REG_DAY_OF_WEEK_COUNTER, reg_data, 4 ) )
    {
        return RTC17_ERROR;
    }
    return RTC17_OK;
}

err_t rtc17_read_date ( rtc17_t *ctx, rtc17_date_t *date )
{
    uint8_t reg_data[ 4 ];
    if ( RTC17_ERROR == rtc17_read_multiple_registers ( ctx, RTC17_REG_DAY_OF_WEEK_COUNTER, reg_data, 4 ) )
    {
        return RTC17_ERROR;
    }
    date->day_of_week = reg_data[ 0 ];
    date->day = bcd_to_dec ( reg_data[ 1 ] );
    date->month = bcd_to_dec ( reg_data[ 2 ] );
    date->year = bcd_to_dec ( reg_data[ 3 ] );
    return RTC17_OK;
}

// ------------------------------------------------------------------------- END
