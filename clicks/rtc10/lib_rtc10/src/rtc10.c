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

#include "rtc10.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc10_cfg_setup ( rtc10_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->an   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RTC10_I2C_SLAVE_ADDRESS;
}

RTC10_RETVAL rtc10_init ( rtc10_t *ctx, rtc10_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC10_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    // Input pins

    digital_in_init( &ctx->an, cfg->an );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC10_OK;

}

void rtc10_generic_write ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc10_generic_read ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void rtc10_hw_reset ( rtc10_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    
    digital_out_high( &ctx->rst );
    Delay_100ms( );
}

uint8_t rtc10_check_interrupt ( rtc10_t *ctx )  
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t rtc10_read_byte ( rtc10_t *ctx, uint8_t reg_address )
{
    uint8_t r_buffer[ 1 ];

    rtc10_generic_read( ctx, reg_address, r_buffer, 1 );

    return r_buffer[ 0 ];
}

void rtc10_write_byte ( rtc10_t *ctx, uint8_t reg_address, uint8_t write_data )
{
    uint8_t w_buffer[ 2 ];

    rtc10_generic_write( ctx, reg_address, &write_data, 1 );

} 

uint8_t rtc10_get_time_seconds ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCSEC );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc10_set_time_seconds ( rtc10_t *ctx, uint8_t seconds )
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

    rtc10_write_byte( ctx, RTC10_RTCSEC, temp );
}  

uint8_t rtc10_get_time_minutes ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCMIN );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
} 

void rtc10_set_time_minutes ( rtc10_t *ctx, uint8_t minutes )
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

    rtc10_write_byte( ctx, RTC10_RTCMIN, temp );
} 

uint8_t rtc10_get_century_flag ( rtc10_t *ctx )
{
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCMIN );

    temp >=7;
    temp &= 0x01;

    return temp;
}

void rtc10_set_century_flag ( rtc10_t *ctx )
{
    uint8_t temp;
    
    temp = rtc10_read_byte( ctx, RTC10_RTCMIN );

    temp |= 0x80;

   temp= rtc10_read_byte( ctx, RTC10_RTCMIN  );
}

uint8_t rtc10_get_time_hours ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCHOUR );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc10_set_time_hours( rtc10_t *ctx, uint8_t hours )
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

    rtc10_write_byte( ctx, RTC10_RTCHOUR, temp );
}

uint8_t rtc10_get_day_of_the_week ( rtc10_t *ctx )
{
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCWKDAY );

    return temp;
}

void rtc10_set_day_of_the_week ( rtc10_t *ctx, uint8_t w_day )
{
    w_day %= 8;

    if ( w_day == 0 )
    {
        w_day = 1;
    }
    rtc10_write_byte( ctx, RTC10_RTCWKDAY, w_day );
}

uint8_t rtc10_get_date_day ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCDATE );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
} 

void rtc10_set_date_day ( rtc10_t *ctx, uint8_t date_day )
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

    rtc10_write_byte( ctx, RTC10_RTCDATE, temp );
}  

uint8_t rtc10_get_date_month ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCMTH );

    ones = temp & 0x0F;

    tens = ( temp & 0x10 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc10_set_date_month( rtc10_t *ctx, uint8_t date_month )
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

    rtc10_write_byte( ctx, RTC10_RTCMTH, temp );
}

uint8_t rtc10_get_date_year ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_RTCYEAR );

    ones = temp & 0x0F;

    tens = ( temp & 0xF0 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc10_set_date_year ( rtc10_t *ctx, uint16_t date_year )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    uint8_t temp_month;

    ones = 0x00;
    tens = 0x00;

    date_year %= 100;

    ones = ( ( uint8_t ) date_year ) % 10;

    tens = ( ( uint8_t ) date_year / 10 ) << 4;

    temp = tens | ones;

    rtc10_write_byte( ctx, RTC10_RTCYEAR, temp );
}

void rtc10_set_time ( rtc10_t *ctx, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds )
{
    rtc10_set_time_hours( ctx, time_hours );
    rtc10_set_time_minutes( ctx, time_minutes );
    rtc10_set_time_seconds( ctx, time_seconds );
}

void rtc10_get_time ( rtc10_t *ctx, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds )
{
    *time_hours = rtc10_get_time_hours( ctx );
    *time_minutes = rtc10_get_time_minutes( ctx );
    *time_seconds = rtc10_get_time_seconds( ctx );
}

void rtc10_set_date( rtc10_t *ctx, uint8_t day_of_the_week, uint8_t date_day, uint8_t date_month, uint16_t date_year )
{
    rtc10_set_day_of_the_week( ctx, day_of_the_week );
    rtc10_set_date_day( ctx, date_day );
    rtc10_set_date_month( ctx, date_month );
    rtc10_set_date_year( ctx, date_year );
}

void rtc10_get_date( rtc10_t *ctx, uint8_t *day_of_the_week, uint8_t *date_day, uint8_t *date_month, uint8_t *date_year )
{
    *day_of_the_week = rtc10_get_day_of_the_week( ctx );
    *date_day = rtc10_get_date_day( ctx );
    *date_month = rtc10_get_date_month( ctx );
    *date_year = rtc10_get_date_year( ctx );
}

// -------------------------------------------------------------- ALARM 1 & 2  

// Get seconds function  

uint8_t rtc10_get_alarm_time_seconds ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_ALM1SEC );

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

// Set seconds function  

void rtc10_set_alarm_time_seconds ( rtc10_t *ctx, uint8_t seconds )
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

    rtc10_write_byte( ctx, RTC10_ALM1SEC, temp );
}

// Get minutes function  

uint8_t rtc10_get_alarm_time_minutes ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;
    uint8_t alm_flag;
    
    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );

    if ( ( alm_flag & 0x01 ) == 1 )
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM1MIN );
    }
    else
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM2MIN );
    }

    ones = temp & 0x0F;

    tens = ( temp & 0x70 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

// Set minutes function  

void rtc10_set_alarm_time_minutes( rtc10_t *ctx, uint8_t minutes )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    uint8_t alm_flag;

    ones = 0x00;
    tens = 0x00;

    minutes %= 60;

    ones = minutes % 10;

    tens = ( minutes / 10 ) << 4;

    temp = tens | ones;
    
    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );
    
    if ( ( alm_flag & 0x01 ) == 1 )
    {
        rtc10_write_byte( ctx,RTC10_ALM1MIN, temp );
    }
    else
    {
        rtc10_write_byte( ctx, RTC10_ALM2MIN, temp );
    }
}

// Get hours function  

uint8_t rtc10_get_alarm_time_hours ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;
    uint8_t alm_flag;

    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );

    if ( ( alm_flag & 0x01 ) == 1 )
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM1HOUR );
    }
    else
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM2HOUR );
    }

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

// Set hours function  

void rtc10_set_alarm_time_hours ( rtc10_t *ctx, uint8_t hours )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    uint8_t alm_flag;

    ones = 0x00;
    tens = 0x00;

    hours %= 24;

    ones = hours % 10;

    tens = ( hours / 10 ) << 4;

    temp = tens | ones;

    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );

    if ( ( alm_flag & 0x01 ) == 1 )
    {
        rtc10_write_byte( ctx, RTC10_ALM1HOUR, temp );
    }
    else
    {
        rtc10_write_byte( ctx, RTC10_ALM2HOUR, temp );
    }
}

// Get day function  

uint8_t rtc10_get_alarm_date_day ( rtc10_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;
    uint8_t alm_flag;

    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );

    if ( ( alm_flag & 0x01 ) == 1 )
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM1DATE );
    }
    else
    {
        temp = rtc10_read_byte( ctx, RTC10_ALM2DATE );
    }

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

// Set day function  

void rtc10_set_alarm_date_day ( rtc10_t *ctx, uint8_t date_day )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;
    uint8_t alm_flag;

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

    alm_flag = rtc10_read_byte( ctx, RTC10_CONTROL );

    if ( ( alm_flag & 0x01 ) == 1 )
    {
        rtc10_write_byte( ctx, RTC10_ALM1DATE, temp );
    }
    else
    {
        rtc10_write_byte( ctx, RTC10_ALM2DATE, temp );
    }
}

// Set Alarm 1 time: days, hours, minutes and seconds function  

void rtc10_set_first_alarm ( rtc10_t *ctx, uint8_t time_days, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds )
{
    uint8_t temp;
    
    temp = rtc10_read_byte( ctx, RTC10_CONTROL );
    
    temp |= RTC10_ENABLE_ALARM_1;
    temp |= RTC10_ENABLE_INTERRUPT;
    
    rtc10_set_alarm_date_day( ctx, time_days );
    rtc10_set_alarm_time_hours( ctx, time_hours );
    rtc10_set_alarm_time_minutes( ctx, time_minutes );
    rtc10_set_alarm_time_seconds( ctx, time_seconds );
}

// Get Alarm 1 time: days, hours, minutes and seconds function  

void rtc10_get_first_alarm ( rtc10_t *ctx, uint8_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds )
{
    *time_days = rtc10_get_alarm_date_day( ctx );
    *time_hours = rtc10_get_alarm_time_hours( ctx );
    *time_minutes = rtc10_get_alarm_time_minutes( ctx );
    *time_seconds = rtc10_get_alarm_time_seconds( ctx );

}

// Set Alarm 2 time: days, hours, and minutes function 

void rtc10_set_second_alarm( rtc10_t *ctx, uint8_t time_days, uint8_t time_hours, uint8_t time_minutes )
{
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_CONTROL );
    Delay_10us( );

    temp |= RTC10_ENABLE_ALARM_2;
    temp |= RTC10_ENABLE_INTERRUPT;

    rtc10_set_alarm_date_day( ctx, time_days );
    rtc10_set_alarm_time_hours( ctx, time_hours );
    rtc10_set_alarm_time_minutes( ctx, time_minutes );
}

// Get Alarm 2 time: days, hours, and minutes function  

void rtc10_get_second_alarm ( rtc10_t *ctx, uint8_t *time_days, uint8_t *time_hours, uint8_t *time_minutes )
{
    *time_days = rtc10_get_alarm_date_day( ctx );
    *time_hours = rtc10_get_alarm_time_hours( ctx );
    *time_minutes = rtc10_get_alarm_time_minutes( ctx );
}

// ------------------------------------------------------------ CONFIGURATION  

// Enable counting function  

void rtc10_enable_counting ( rtc10_t *ctx )
{
    uint8_t temp;

    temp = rtc10_read_byte( ctx, RTC10_CONTROL );

    temp &= 0x7F;

    temp =  rtc10_read_byte( ctx, RTC10_CONTROL  );
}

// Set configuration function 

void rtc10_set_config( rtc10_t *ctx, uint8_t config_data )
{
    rtc10_write_byte( ctx, RTC10_CONTROL, config_data );
}

// Get configuration status function  

uint8_t rtc10_get_status ( rtc10_t *ctx )
{
    uint8_t config_status;

    config_status = rtc10_read_byte( ctx, RTC10_STATUS );

    return config_status;
}

// -------------------------------------------------------------- TEMPERATURE  

// Get temperature function  

float rtc10_get_temperature ( rtc10_t *ctx )
{
    float temperature;
    int8_t msb;
    uint8_t lsb;

    msb = rtc10_read_byte( ctx, RTC10_TEMPERATURE_MSB );
    lsb = rtc10_read_byte( ctx, RTC10_TEMPERATURE_LSB );
    
    lsb >>= 6;
    
    if ( msb & 0x80 )
    {
        ~msb;
        ~lsb;
    }
    
    temperature = ( float ) msb;
    temperature += ( ( float ) lsb ) * 0.25;

    return temperature;
}

// ------------------------------------------------------------------------- END

