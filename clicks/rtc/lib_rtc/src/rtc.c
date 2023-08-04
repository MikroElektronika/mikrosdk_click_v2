/*
 * MikroSDK - MikroE Software Development Kit
 * Copyright© 2020 MikroElektronika d.o.o.
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, 
 * publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE 
 * OR OTHER DEALINGS IN THE SOFTWARE. 
 */

/*!
 * \file
 *
 */

#include "rtc.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc_cfg_setup ( rtc_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RTC_I2C_ADDRESS_0;
}

err_t rtc_init ( rtc_t *ctx, rtc_cfg_t *cfg )
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

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC_OK;
}

err_t rtc_generic_write ( rtc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc_generic_read ( rtc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void rtc_enable_disable_counting ( rtc_t *ctx, uint8_t en_dis )
{
    uint8_t temp_w;

    temp_w = 0x00;

    if ( en_dis == 1 )
    {
        rtc_generic_write( ctx, RTC_REG_CONTROL, &temp_w, 1 );
    }
    else if ( en_dis == 0 )
    {
        temp_w = 0x80;

        rtc_generic_write( ctx, RTC_REG_CONTROL, &temp_w, 1 );
    }

}

void rtc_read_time ( rtc_t *ctx )
{
    uint8_t temp;
    
    rtc_generic_read( ctx, RTC_REG_CONTROL, &temp, 1 );
    
    temp &= 0xF7;
    
    rtc_generic_write( ctx, RTC_REG_CONTROL, &temp, 1 );
}

void rtc_read_date ( rtc_t *ctx )
{
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_CONTROL, &temp, 1 );

    temp |= 0x08;

    rtc_generic_write( ctx, RTC_REG_CONTROL, &temp, 1 );
}

uint8_t rtc_get_time_value ( rtc_t *ctx, uint8_t time_part )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    rtc_generic_read( ctx, time_part, &temp, 1 );

    ones = temp & 0x0F;

    if ( time_part == RTC_REG_TIME_HOUR )
    {
        tens = ( temp & 0x30 ) >> 4;
    }
    else
    {
        tens = ( temp & 0x70 ) >> 4;
    }

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc_set_time_value ( rtc_t *ctx, uint8_t time_part, uint8_t time_addr )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    if ( time_addr == RTC_REG_TIME_HOUR )
    {
        time_part %= 24;
    }
    else
    {
        time_part %= 60;
    }

    ones = time_part % 10;

    tens = ( time_part / 10 ) << 4;

    temp = tens | ones;

    rtc_generic_write( ctx, time_addr, &temp, 1 );
}

uint8_t rtc_get_date_day ( rtc_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc_set_date_day ( rtc_t *ctx, uint8_t date_day )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    date_day %= 32;

    if ( date_day == 0 )
    {
        date_day = 1;
    }

    ones = date_day % 10;

    tens = ( date_day / 10 ) << 4;
    
    rtc_generic_read( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );

    temp |= ( tens | ones );

    rtc_generic_write( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );
}

uint8_t rtc_get_date_year ( rtc_t *ctx )
{
    uint8_t result;
    uint8_t temp;
    uint8_t ones;
    uint8_t tens;

    ones = 0x00;
    tens = 0x00;

    rtc_generic_read( ctx, RTC_REG_TIMER, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0xF0 ) >> 4;

    result = ( 10 * tens ) + ones;

    if ( result % 4 == 0 )
    {
        temp |= 0xC0;
        rtc_generic_write( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );
    }

    return result;
}

void rtc_set_date_year ( rtc_t *ctx, uint16_t date_year )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    uint8_t temp_buff[ 2 ];

    ones = 0x00;
    tens = 0x00;

    date_year %= 100;

    ones = date_year % 10;

    tens = ( date_year / 10 ) << 4;

    temp = tens | ones;
    
    if ( date_year % 4 )
    {
        temp |= 0xC0;
        rtc_generic_write( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );
    }
    
    temp_buff[ 0 ] = date_year;
    temp_buff[ 1 ] = date_year >> 8;
    
    rtc_generic_write( ctx, RTC_REG_TIMER, temp_buff, 2 );
}

uint8_t rtc_check_leap_year ( rtc_t *ctx )
{
    uint8_t temp;
    
    temp = 0x00;
    
    rtc_generic_read( ctx, RTC_REG_TIME_DATE_DAY_AND_YEAR, &temp, 1 );
    
    temp >>= 6;

    if ( temp == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t rtc_get_day_of_the_week ( rtc_t *ctx )
{
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH, &temp, 1 );
    
    temp &= 0xE0;
    temp >>= 5;

    return temp;
}

void rtc_set_day_of_the_week ( rtc_t *ctx, uint8_t w_day )
{
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH, &temp, 1 );
    
    w_day %= 7;
    w_day <<= 5;
    
    temp |= w_day;

    rtc_generic_write( ctx, RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH, &w_day, 1 );
}

uint8_t rtc_get_date_month ( rtc_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;
    
    ones = 0x00;
    tens = 0x00;

    rtc_generic_read( ctx, RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0x10 ) >> 4;

    result = ( 10 * tens ) + ones;
    
    return result;
}

void rtc_set_date_month ( rtc_t *ctx, uint8_t date_month )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    date_month %= 13;

    if ( date_month == 0 )
    {
        date_month = 1;
    }

    ones = date_month % 10;

    tens = ( date_month / 10 ) << 4;

    temp = tens | ones;

    rtc_generic_write( ctx, RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH, &temp, 1 );
}

void rtc_set_time ( rtc_t *ctx )
{
    rtc_set_time_value( ctx, ctx->time.time_hours, RTC_REG_TIME_HOUR );
    rtc_set_time_value( ctx, ctx->time.time_minutes, RTC_REG_TIME_MIN );
    rtc_set_time_value( ctx, ctx->time.time_seconds, RTC_REG_TIME_SEC );
    rtc_set_time_value( ctx, ctx->time.time_hun_sec, RTC_REG_TIME_HUN_SEC );
    
    rtc_enable_disable_counting( ctx, 1 );
}

void rtc_get_time ( rtc_t *ctx )
{
    ctx->time.time_hours = rtc_get_time_value( ctx, RTC_REG_TIME_HOUR );
    ctx->time.time_minutes = rtc_get_time_value( ctx, RTC_REG_TIME_MIN );
    ctx->time.time_seconds = rtc_get_time_value( ctx, RTC_REG_TIME_SEC );
    ctx->time.time_hun_sec = rtc_get_time_value( ctx, RTC_REG_TIME_HUN_SEC );
}                 

void rtc_set_date ( rtc_t *ctx )
{
    rtc_set_day_of_the_week( ctx, ctx->date.day_of_the_week );
    rtc_set_date_day( ctx, ctx->date.date_day );
    rtc_set_date_month( ctx, ctx->date.date_month );
    rtc_set_date_year( ctx, ctx->date.date_year );
    
    rtc_enable_disable_counting( ctx, 1 );
}

void rtc_get_date ( rtc_t *ctx )
{
    ctx->date.day_of_the_week = rtc_get_day_of_the_week( ctx );
    ctx->date.date_day = rtc_get_date_day( ctx );
    ctx->date.date_month = rtc_get_date_month( ctx );
    ctx->date.date_year = rtc_get_date_year( ctx );
}

void rtc_enable_disable_alarm ( rtc_t *ctx, uint8_t en_dis )
{
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_CONTROL, &temp, 1 );
    if ( en_dis == 1 )
    {
        temp |= 0x04;
    }
    else
    {
        temp &= 0xFB;
    }
    
    rtc_generic_write( ctx, RTC_REG_CONTROL, &temp, 1 );
}

void rtc_set_alarm_value ( rtc_t *ctx, uint8_t al_time_val, uint8_t al_time_type )
{
    uint8_t temp;
    uint8_t ones;
    uint8_t tens;

    rtc_generic_read( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );

    switch ( al_time_type )
    {
        case RTC_REG_TIME_ALARM_HUN_SEC:
        {   
            al_time_val %= 100;
            temp |= 0x01;
            break;
        }
        case RTC_REG_TIME_ALARM_SEC:
        {
            al_time_val %= 60;
            temp |= 0x02;
            break;
        }
        case RTC_REG_TIME_ALARM_MIN:
        {
            al_time_val %= 60;
            temp |= 0x03;
            break;
        }
        case RTC_REG_TIME_ALARM_HOUR:
        {
            al_time_val %= 24;
            temp |= 0x04;
            break;
        }
        default:
        {
            break;
        }
    }

    rtc_generic_write( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );

    temp = 0x00;
    ones = 0x00;
    tens = 0x00;

    ones = al_time_val % 10;

    tens = ( al_time_val / 10 ) << 4;

    temp = tens | ones;

    rtc_generic_write( ctx, al_time_type, &temp, 1 );
}

void rtc_set_time_alarm ( rtc_t *ctx )
{
    rtc_set_alarm_value( ctx, ctx->time.time_hours, RTC_REG_TIME_ALARM_HOUR );
    rtc_set_alarm_value( ctx, ctx->time.time_minutes, RTC_REG_TIME_ALARM_MIN );
    rtc_set_alarm_value( ctx, ctx->time.time_seconds, RTC_REG_TIME_ALARM_SEC );
    rtc_set_alarm_value( ctx, ctx->time.time_hun_sec, RTC_REG_TIME_ALARM_HUN_SEC );

    rtc_enable_disable_counting( ctx, 1 );
}

uint8_t rtc_get_alarm_value ( rtc_t *ctx, uint8_t alarm_addr )
{
    uint8_t temp;
    uint8_t ones;
    uint8_t tens;
    uint8_t result;

    temp = 0x00;
    ones = 0x00;
    tens = 0x00;

    rtc_generic_read( ctx, alarm_addr, &temp, 1 );

    switch ( alarm_addr )
    {
        case RTC_REG_TIME_ALARM_HUN_SEC:
        {   
            ones = temp & 0x0F;

            tens = ( temp & 0xF0 ) >> 4;

            break;
        }
        case RTC_REG_TIME_ALARM_SEC:
        {
            ones = temp & 0x0F;

            tens = ( temp & 0x70 ) >> 4;

            break;
        }
        case RTC_REG_TIME_ALARM_MIN:
        {
            ones = temp & 0x0F;

            tens = ( temp & 0x70 ) >> 4;

            break;
        }
        case RTC_REG_TIME_ALARM_HOUR:
        {
            ones = temp & 0x0F;

            tens = ( temp & 0x30 ) >> 4;

            break;
        }
        default:
        {
            break;
        }
    }

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc_get_time_alarm ( rtc_t *ctx )
{
    ctx->time.time_hours = rtc_get_alarm_value( ctx, RTC_REG_TIME_ALARM_HOUR );
    ctx->time.time_minutes = rtc_get_alarm_value( ctx, RTC_REG_TIME_ALARM_HOUR );
    ctx->time.time_seconds = rtc_get_alarm_value( ctx, RTC_REG_TIME_ALARM_SEC );
    ctx->time.time_hun_sec = rtc_get_alarm_value( ctx, RTC_REG_TIME_ALARM_HUN_SEC );
}

void rtc_set_alarm_days ( rtc_t *ctx, uint8_t days )
{
    uint8_t temp;
    uint8_t ones;
    uint8_t tens;

    rtc_generic_read( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );

    temp |= 0x05;

    rtc_generic_write( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );

    temp = 0x00;
    ones = 0x00;
    tens = 0x00;

    days %= 31;

    ones = days % 10;

    tens = ( days / 10 ) << 4;

    temp = tens | ones;

    rtc_generic_write( ctx, RTC_REG_TIME_ALARM_DATE_DAY_AND_YEAR, &temp, 1 );
}

void rtc_enable_disable_interrupt( rtc_t *ctx, uint8_t flag )
{
    uint8_t temp;

    rtc_generic_read( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );

    if ( flag == 1 )
    {
        temp |= 0x80;
    }
    else
    {
        temp &= 0x7F;
    }

    rtc_generic_write( ctx, RTC_REG_TIME_ALARM_CONTROL, &temp, 1 );
}

uint8_t rtc_get_interrupt( rtc_t *ctx )
{
    uint8_t inter;

    inter = digital_in_read( &ctx->int_pin );

    return inter;
}

// ------------------------------------------------------------------------- END

