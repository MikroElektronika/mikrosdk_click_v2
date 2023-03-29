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
 * @file rtc21.c
 * @brief RTC 21 Click Driver.
 */

#include "rtc21.h"
#include "conversions.h"

void rtc21_cfg_setup ( rtc21_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ft  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC21_DEVICE_ADDRESS;
}

err_t rtc21_init ( rtc21_t *ctx, rtc21_cfg_t *cfg ) 
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

    digital_in_init( &ctx->ft, cfg->ft );

    return I2C_MASTER_SUCCESS;
}

err_t rtc21_generic_write ( rtc21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    if ( ( reg + len ) > ( RTC21_REG_RAM_TOP + 1 ) )
    {
        return RTC21_ERROR;
    }
    uint8_t data_buf[ RTC21_REG_RAM_TOP + 1 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc21_generic_read ( rtc21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( ( reg + len ) > ( RTC21_REG_RAM_TOP + 1 ) )
    {
        return RTC21_ERROR;
    }
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc21_write_register ( rtc21_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc21_generic_write ( ctx, reg, &data_in, 1 );
}

err_t rtc21_read_register ( rtc21_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc21_generic_read ( ctx, reg, data_out, 1 );
}

uint8_t rtc21_get_ft_pin ( rtc21_t *ctx )
{
    return digital_in_read ( &ctx->ft );
}

err_t rtc21_set_time ( rtc21_t *ctx, rtc21_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second );
    data_buf[ 1 ] = dec_to_bcd ( time->minute );
    data_buf[ 2 ] = dec_to_bcd ( time->hour );
    if ( RTC21_ERROR == rtc21_generic_write ( ctx, RTC21_REG_SECOND, data_buf, 3 ) )
    {
        return RTC21_ERROR;
    }
    return RTC21_OK;
}

err_t rtc21_read_time ( rtc21_t *ctx, rtc21_time_t *time )
{
    uint8_t data_buf[ 3 ] = { 0 };
    if ( RTC21_ERROR == rtc21_generic_read ( ctx, RTC21_REG_SECOND, data_buf, 3 ) )
    {
        return RTC21_ERROR;
    }
    time->second = bcd_to_dec ( data_buf[ 0 ] );
    time->minute = bcd_to_dec ( data_buf[ 1 ] );
    time->hour = bcd_to_dec ( data_buf[ 2 ] );
    return RTC21_OK;
}

err_t rtc21_set_date ( rtc21_t *ctx, rtc21_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day_of_week );
    data_buf[ 1 ] = dec_to_bcd ( date->day );
    data_buf[ 2 ] = dec_to_bcd ( date->month );
    data_buf[ 3 ] = dec_to_bcd ( date->year );
    if ( RTC21_ERROR == rtc21_generic_write ( ctx, RTC21_REG_DAY_OF_WEEK, data_buf, 4 ) )
    {
        return RTC21_ERROR;
    }
    return RTC21_OK;
}

err_t rtc21_read_date ( rtc21_t *ctx, rtc21_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC21_ERROR == rtc21_generic_read ( ctx, RTC21_REG_DAY_OF_WEEK, data_buf, 4 ) )
    {
        return RTC21_ERROR;
    }
    date->day_of_week = data_buf[ 0 ];
    date->day = bcd_to_dec ( data_buf[ 1 ] );
    date->month = bcd_to_dec ( data_buf[ 2 ] );
    date->year = bcd_to_dec ( data_buf[ 3 ] );
    return RTC21_OK;
}

// ------------------------------------------------------------------------- END
