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
 * @file rtc24.c
 * @brief RTC 24 Click Driver.
 */

#include "rtc24.h"
#include "conversions.h"

void rtc24_cfg_setup ( rtc24_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->sqw = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC24_DEVICE_ADDRESS;
}

err_t rtc24_init ( rtc24_t *ctx, rtc24_cfg_t *cfg ) 
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

    digital_in_init( &ctx->sqw, cfg->sqw );

    return I2C_MASTER_SUCCESS;
}

err_t rtc24_default_cfg ( rtc24_t *ctx ) 
{
    err_t error_flag = RTC24_OK;
    if ( RTC24_ERROR == rtc24_check_communication ( ctx ) )
    {
        return RTC24_ERROR;
    }

    error_flag |= rtc24_write_reg ( ctx, RTC24_REG_CONTROL, RTC24_CONTROL_OUT_LOW | 
                                                            RTC24_CONTROL_SQWE_EN | 
                                                            RTC24_CONTROL_RS_1HZ );
    return error_flag;
}

err_t rtc24_write_regs ( rtc24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ RTC24_REG_RAM_END + 2 ] = { 0 };
    if ( ( ( reg + len ) > ( RTC24_REG_RAM_END + 1 ) ) || ( NULL == data_in ) )
    {
        return RTC24_ERROR;
    }
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc24_read_regs ( rtc24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( ( reg + len ) > ( RTC24_REG_RAM_END + 1 ) ) || ( NULL == data_out ) )
    {
        return RTC24_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc24_write_reg ( rtc24_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc24_write_regs( ctx, reg, &data_in, 1 );
}

err_t rtc24_read_reg ( rtc24_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc24_read_regs( ctx, reg, data_out, 1 );
}

uint8_t rtc24_get_sqw_pin ( rtc24_t *ctx )
{
    return digital_in_read ( &ctx->sqw );
}

err_t rtc24_check_communication ( rtc24_t *ctx )
{
    uint8_t dummy_ram = 0;
    if ( RTC24_OK == rtc24_write_reg ( ctx, RTC24_REG_RAM_START, RTC24_DUMMY_RAM ) )
    {
        if ( RTC24_OK == rtc24_read_reg ( ctx, RTC24_REG_RAM_START, &dummy_ram ) )
        {
            if ( RTC24_DUMMY_RAM == dummy_ram )
            {
                return RTC24_OK;
            }
        }
    }
    return RTC24_ERROR;
}

err_t rtc24_set_time ( rtc24_t *ctx, rtc24_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second );
    data_buf[ 1 ] = dec_to_bcd ( time->minute );
    data_buf[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC24_ERROR == rtc24_write_regs ( ctx, RTC24_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC24_ERROR;
    }
    return RTC24_OK;
}

err_t rtc24_read_time ( rtc24_t *ctx, rtc24_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( RTC24_ERROR == rtc24_read_regs ( ctx, RTC24_REG_SECONDS, data_buf, 3 ) )
    {
        return RTC24_ERROR;
    }
    time->second = bcd_to_dec ( data_buf[ 0 ] );
    time->minute = bcd_to_dec ( data_buf[ 1 ] );
    time->hour = bcd_to_dec ( data_buf[ 2 ] );
    return RTC24_OK;
}

err_t rtc24_set_date ( rtc24_t *ctx, rtc24_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 1 ] = dec_to_bcd ( date->day );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC24_ERROR == rtc24_write_regs ( ctx, RTC24_REG_DAY, data_buf, 4 ) )
    {
        return RTC24_ERROR;
    }
    return RTC24_OK;
}

err_t rtc24_read_date ( rtc24_t *ctx, rtc24_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC24_ERROR == rtc24_read_regs ( ctx, RTC24_REG_DAY, data_buf, 4 ) )
    {
        return RTC24_ERROR;
    }
    date->day_of_week = data_buf[ 0 ];
    date->day = bcd_to_dec ( data_buf[ 1 ] );
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC24_OK;
}

// ------------------------------------------------------------------------- END
