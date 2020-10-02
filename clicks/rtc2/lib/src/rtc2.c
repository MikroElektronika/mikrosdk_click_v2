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

#include "rtc2.h"

void rtc2_cfg_setup ( rtc2_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x68;
}

RTC2_RETVAL rtc2_init ( rtc2_t *ctx, rtc2_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC2_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    

    return RTC2_OK;
}

void rtc2_generic_write ( rtc2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ];
    uint8_t cnt;
    
    tx_buf[ 0 ] = reg;
    
    for ( cnt = 1; cnt <= len; cnt++ )
    {
        tx_buf[ cnt ] = data_buf[ cnt - 1 ]; 
    }
    
    i2c_master_write( &ctx->i2c, tx_buf, len + 1 ); 
}

void rtc2_generic_read ( rtc2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t rtc2_read_byte ( rtc2_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];
    
    rtc2_generic_read( ctx, reg_address, r_buffer, 1 );
    
    return r_buffer[ 0 ];
}


void rtc2_write_byte ( rtc2_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 1 ];

    w_buffer[ 0 ] = write_data;

    rtc2_generic_write( ctx, reg_address, w_buffer, 1 );
}

void rtc2_enable_counting ( rtc2_t *ctx )
{
    uint8_t temp;
    
    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_SEC );
    
    temp &= 0x7F;
    
    rtc2_write_byte( ctx, RTC2_REG_TIME_SEC, temp );
}

void rtc2_disable_counting ( rtc2_t *ctx )
{
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_SEC );

    temp |= 0x80;

    rtc2_write_byte( ctx, RTC2_REG_TIME_SEC, temp );
}

uint8_t rtc2_get_time_seconds ( rtc2_t *ctx ) 
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_SEC );
    
    ones = temp & 0x0F;
    
    tens = ( temp & 0x70 ) >> 4;
    
    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_time_seconds ( rtc2_t *ctx, uint8_t seconds )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;
    
    seconds %= 60;

    ones = seconds % 10;

    tens = ( seconds / 10 ) << 4;

    temp = tens | ones;

    rtc2_write_byte( ctx, RTC2_REG_TIME_SEC, temp );
}

uint8_t rtc2_get_time_minutes ( rtc2_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_MIN );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_time_minutes ( rtc2_t *ctx, uint8_t minutes )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    
    ones = 0x00;
    tens = 0x00;

    minutes %= 60;

    ones = minutes % 10;

    tens = ( minutes / 10 ) << 4;

    temp = tens | ones;

    rtc2_write_byte( ctx, RTC2_REG_TIME_MIN, temp );
}

uint8_t rtc2_get_time_hours ( rtc2_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_HOUR );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_time_hours ( rtc2_t *ctx, uint8_t hours )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    hours %= 24;

    ones = hours % 10;

    tens = ( hours / 10 ) << 4;

    temp = tens | ones;

    rtc2_write_byte( ctx, RTC2_REG_TIME_HOUR, temp );
}

uint8_t rtc2_get_day_of_the_week ( rtc2_t *ctx )
{
    uint8_t temp;
    
    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_DAY_OF_THE_WEEK );

    return temp;
}

void rtc2_set_day_of_the_week ( rtc2_t *ctx, uint8_t w_day )
{
    w_day %= 8;
    
    if ( w_day == 0 )
    {
        w_day = 1;
    }
    rtc2_write_byte( ctx, RTC2_REG_TIME_DAY_OF_THE_WEEK, w_day );
}

uint8_t rtc2_get_date_day ( rtc2_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_DATE_DAY );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_date_day ( rtc2_t *ctx, uint8_t date_day )
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

    temp = tens | ones;

    rtc2_write_byte( ctx, RTC2_REG_TIME_DATE_DAY, temp );
}

uint8_t rtc2_get_date_month ( rtc2_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte( ctx, RTC2_REG_TIME_DATE_MONTH );

    ones = temp & 0x0F;

    tens = ( temp & 0x10 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_date_month ( rtc2_t *ctx, uint8_t date_month )
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

    rtc2_write_byte( ctx, RTC2_REG_TIME_DATE_MONTH, temp );
}

uint8_t rtc2_get_date_year ( rtc2_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc2_read_byte ( ctx, RTC2_REG_TIME_DATE_YEAR );

    ones = temp & 0x0F;

    tens = ( temp & 0xF0 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc2_set_date_year ( rtc2_t *ctx, uint16_t date_year )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;
    
    date_year %= 100;

    ones = date_year % 10;

    tens = ( date_year / 10 ) << 4;

    temp = tens | ones;

    rtc2_write_byte( ctx, RTC2_REG_TIME_DATE_YEAR, temp );
}

void rtc2_set_time ( rtc2_t *ctx, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds )
{
    rtc2_set_time_hours( ctx, time_hours );
    rtc2_set_time_minutes( ctx, time_minutes );
    rtc2_set_time_seconds( ctx, time_seconds );
}

void rtc2_get_time ( rtc2_t *ctx, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds )
{
    *time_hours = rtc2_get_time_hours( ctx );
    *time_minutes = rtc2_get_time_minutes( ctx );
    *time_seconds = rtc2_get_time_seconds( ctx );
}

void rtc2_set_date ( rtc2_t *ctx, rtc2_data_t *date )
{
    rtc2_set_day_of_the_week( ctx, date->day_of_the_week );
    rtc2_set_date_day( ctx, date->date_day );
    rtc2_set_date_month( ctx, date->date_month );
    rtc2_set_date_year( ctx, date->date_year );
}

void rtc2_get_date ( rtc2_t *ctx, rtc2_data_t *date )
{
    date->day_of_the_week = rtc2_get_day_of_the_week( ctx );
    date->date_day = rtc2_get_date_day( ctx );
    date->date_month = rtc2_get_date_month( ctx );
    date->date_year = rtc2_get_date_year( ctx );
}

void rtc2_set_frequency_sqwe ( rtc2_t *ctx, uint8_t rate_select )
{
    rtc2_write_byte( ctx, RTC2_REG_CONTROL, rate_select );
}

// ------------------------------------------------------------------------- END

