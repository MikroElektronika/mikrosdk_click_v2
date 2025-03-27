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
 * @file rtc22.c
 * @brief RTC 22 Click Driver.
 */

#include "rtc22.h"
#include "conversions.h"

void rtc22_cfg_setup ( rtc22_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->tirq = HAL_PIN_NC;
    cfg->wdi = HAL_PIN_NC;
    cfg->psw = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC22_DEVICE_ADDRESS;
}

err_t rtc22_init ( rtc22_t *ctx, rtc22_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wdi, cfg->wdi );

    digital_in_init( &ctx->tirq, cfg->tirq );
    digital_in_init( &ctx->psw, cfg->psw );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc22_write_regs ( rtc22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len )
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc22_read_regs ( rtc22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

err_t rtc22_write_reg ( rtc22_t *ctx, uint8_t reg, uint8_t data_in )
{
    return rtc22_write_regs( ctx, reg, &data_in, 1 );
}

err_t rtc22_read_reg ( rtc22_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return rtc22_read_regs( ctx, reg, data_out, 1 );
}

void rtc22_set_wdi_pin ( rtc22_t *ctx, uint8_t state )
{
    digital_out_write ( &ctx->wdi, state );
}

uint8_t rtc22_get_psw_pin ( rtc22_t *ctx )
{
    return digital_in_read ( &ctx->psw );
}

uint8_t rtc22_get_tirq_pin ( rtc22_t *ctx )
{
    return digital_in_read ( &ctx->tirq );
}

uint8_t rtc22_get_int_pin ( rtc22_t *ctx )
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc22_check_communication ( rtc22_t *ctx )
{
    uint8_t device_id = 0;
    if ( RTC22_OK == rtc22_read_reg ( ctx, RTC22_REG_ID0, &device_id ) )
    {
        if ( RTC22_DEVICE_ID == device_id )
        {
            return RTC22_OK;
        }
    }
    return RTC22_ERROR;
}

err_t rtc22_set_time ( rtc22_t *ctx, rtc22_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( time->second_100th );
    data_buf[ 1 ] = dec_to_bcd ( time->second );
    data_buf[ 2 ] = dec_to_bcd ( time->minute );
    data_buf[ 3 ] = dec_to_bcd ( time->hour );
    if ( RTC22_ERROR == rtc22_write_regs ( ctx, RTC22_REG_HUNDREDTHS, data_buf, 4 ) )
    {
        return RTC22_ERROR;
    }
    return RTC22_OK;
}

err_t rtc22_read_time ( rtc22_t *ctx, rtc22_time_t *time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC22_ERROR == rtc22_read_regs ( ctx, RTC22_REG_HUNDREDTHS, data_buf, 4 ) )
    {
        return RTC22_ERROR;
    }
    time->second_100th = bcd_to_dec ( data_buf[ 0 ] );
    time->second = bcd_to_dec ( data_buf[ 1 ] );
    time->minute = bcd_to_dec ( data_buf[ 2 ] );
    time->hour = bcd_to_dec ( data_buf[ 3 ] );
    return RTC22_OK;
}

err_t rtc22_set_date ( rtc22_t *ctx, rtc22_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    data_buf[ 0 ] = dec_to_bcd ( date->day );
    data_buf[ 1 ] = dec_to_bcd ( date->month );
    data_buf[ 2 ] = dec_to_bcd ( date->year );
    data_buf[ 3 ] = dec_to_bcd ( date->day_of_week );
    if ( RTC22_ERROR == rtc22_write_regs ( ctx, RTC22_REG_DATE, data_buf, 4 ) )
    {
        return RTC22_ERROR;
    }
    return RTC22_OK;
}

err_t rtc22_read_date ( rtc22_t *ctx, rtc22_date_t *date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    if ( RTC22_ERROR == rtc22_read_regs ( ctx, RTC22_REG_DATE, data_buf, 4 ) )
    {
        return RTC22_ERROR;
    }
    date->day = bcd_to_dec ( data_buf[ 0 ] );
    date->month = bcd_to_dec ( data_buf[ 1 ] );
    date->year = bcd_to_dec ( data_buf[ 2 ] );
    date->day_of_week = data_buf[ 3 ];
    return RTC22_OK;
}

// ------------------------------------------------------------------------- END
