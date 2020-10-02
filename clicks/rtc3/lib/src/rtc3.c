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

#include "rtc3.h"

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc3_cfg_setup ( rtc3_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RTC3_I2C_ADDRESS;
}

RTC3_RETVAL rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC3_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC3_OK;

}

void rtc3_generic_write ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc3_generic_read ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void rtc3_enable_disable_counting ( rtc3_t *ctx, uint8_t en_dis )
{
    uint8_t temp_w;

    rtc3_generic_read( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );

    if ( en_dis == 1 )
    {
        temp_w |= 0x7F;

        rtc3_generic_write( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );
    }
    else if ( en_dis == 0 )
    {
        temp_w |= 0x80;

        rtc3_generic_write( ctx, RTC3_REG_TIME_SEC, &temp_w, 1 );
    }
}

uint8_t rtc3_get_time_value ( rtc3_t *ctx, uint8_t time_part )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    rtc3_generic_read( ctx, time_part, &temp, 1 );

    ones = temp & 0x0F;

    if ( time_part == RTC3_REG_TIME_HOUR )
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

void rtc3_set_time_value ( rtc3_t *ctx, uint8_t time_part, uint8_t time_addr )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t temp;

    ones = 0x00;
    tens = 0x00;

    if ( time_addr == RTC3_REG_TIME_HOUR )
    {
        time_part %= 24;
    }
    else
    {
        time_part %= 60;
    }

    ones = time_part % 10;

    tens = ( uint8_t )( time_part / 10 ) << 4;

    temp = tens | ones;

    rtc3_generic_write( ctx, time_addr, &temp, 1 );
}

uint8_t rtc3_get_date_day ( rtc3_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;

    rtc3_generic_read( ctx, RTC3_REG_TIME_DATE_DAY, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0x30 ) >> 4;

    result = ( 10 * tens ) + ones;

    return result;
}

void rtc3_set_date_day ( rtc3_t *ctx, uint8_t date_day )
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

    temp |= ( tens | ones );

    rtc3_generic_write( ctx, RTC3_REG_TIME_DATE_DAY, &temp, 1 );
}

uint8_t rtc3_get_date_month ( rtc3_t *ctx )
{
    uint8_t ones;
    uint8_t tens;
    uint8_t result;
    uint8_t temp;
    
    ones = 0x00;
    tens = 0x00;

    rtc3_generic_read( ctx, RTC3_REG_TIME_DATE_MONTH, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0x10 ) >> 4;

    result = ( 10 * tens ) + ones;
    
    return result;
}

void rtc3_set_date_month ( rtc3_t *ctx, uint8_t date_month )
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

    rtc3_generic_write( ctx, RTC3_REG_TIME_DATE_MONTH, &temp, 1 );
}

uint8_t rtc3_get_date_year ( rtc3_t *ctx )
{
    uint8_t result;
    uint8_t temp;
    uint8_t ones;
    uint8_t tens;

    ones = 0x00;
    tens = 0x00;

    rtc3_generic_read( ctx, RTC3_REG_TIME_DATE_YEAR, &temp, 1 );

    ones = temp & 0x0F;

    tens = ( temp & 0xF0 ) >> 4;

    result = ( 10 * tens ) + ones + 6;

    return result;
}

void rtc3_set_date_year ( rtc3_t *ctx, uint16_t date_year )
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
    
    temp_buff[ 0 ] = date_year;
    temp_buff[ 1 ] = date_year >> 8;
    
    rtc3_generic_write( ctx, RTC3_REG_TIME_DATE_YEAR, temp_buff, 2 );
}

uint8_t rtc3_get_day_of_the_week ( rtc3_t *ctx )
{
    uint8_t temp;

    rtc3_generic_read( ctx, RTC3_REG_TIME_DAY_OF_THE_WEEK, &temp, 1 );
    
    temp &= 0xE0;
    temp >>= 5;

    return temp;
}

void rtc3_set_day_of_the_week ( rtc3_t *ctx, uint8_t w_day )
{
     w_day %= 8;

    if ( w_day == 0 )
    {
        w_day = 1;
    }

    rtc3_generic_write( ctx, RTC3_REG_TIME_DAY_OF_THE_WEEK, &w_day, 1 );
}

void rtc3_set_time ( rtc3_t *ctx )
{
    rtc3_set_time_value( ctx, ctx->time.time_hours, RTC3_REG_TIME_HOUR );
    rtc3_set_time_value( ctx, ctx->time.time_minutes, RTC3_REG_TIME_MIN );
    rtc3_set_time_value( ctx, ctx->time.time_seconds, RTC3_REG_TIME_SEC );
}

void rtc3_get_time ( rtc3_t *ctx )
{
    ctx->time.time_hours = rtc3_get_time_value( ctx, RTC3_REG_TIME_HOUR );
    ctx->time.time_minutes = rtc3_get_time_value( ctx, RTC3_REG_TIME_MIN );
    ctx->time.time_seconds = rtc3_get_time_value( ctx, RTC3_REG_TIME_SEC );
}      

void rtc3_set_date ( rtc3_t *ctx )
{
    rtc3_set_day_of_the_week( ctx, ctx->date.day_of_the_week );
    rtc3_set_date_day( ctx, ctx->date.date_day );
    rtc3_set_date_month( ctx, ctx->date.date_month );
    rtc3_set_date_year( ctx, ctx->date.date_year );
}

void rtc3_get_date ( rtc3_t *ctx )
{
    ctx->date.day_of_the_week = rtc3_get_day_of_the_week( ctx );
    ctx->date.date_day = rtc3_get_date_day( ctx );
    ctx->date.date_month = rtc3_get_date_month( ctx );
    ctx->date.date_year = rtc3_get_date_year( ctx );
}

// Set calibration function

void rtc3_set_calibration ( rtc3_t *ctx, uint8_t cal_sign, uint8_t cal_number )
{
    uint8_t temp;
    
    temp = RTC3_CONFIG1_INITIAL;
    
    temp |= cal_sign << 5;
    temp |= cal_number;
    
    rtc3_generic_write( ctx, RTC3_REG_CONFIG1, &temp, 1 );
}

// Set trickle charge control function

void rtc3_set_trickle_charge ( rtc3_t *ctx, uint8_t tch2 )
{
    uint8_t temp;

    rtc3_generic_read( ctx, RTC3_REG_TRICKLE_CHARGE2, &temp, 1 );

    if ( tch2 == 0 )
    {
        temp |= RTC3_TCH2_OPEN;
    }

    if ( tch2 == 1 )
    {
        temp |= RTC3_TCH2_CLOSED;
    }

    rtc3_generic_write( ctx, RTC3_REG_TRICKLE_CHARGE2, &temp, 1 );
}

// Set trickle charge bypass control function

void rtc3_set_trickle_charge_bypass ( rtc3_t *ctx, uint8_t tcfe )
{
    uint8_t temp;

    rtc3_generic_read( ctx, RTC3_REG_CONFIG2, &temp, 1 );

    if ( tcfe == 0 )
    {
        temp |= RTC3_TCFE_OPEN;
    }

    if ( tcfe == 1 )
    {
        temp |= RTC3_TCFE_CLOSED;
    }

    rtc3_generic_write( ctx, RTC3_REG_CONFIG2, &temp, 1 );
}

// Set special function key byte 1 function

void rtc3_set_special_function_key1 ( rtc3_t *ctx, uint8_t sfkey1 )
{
    rtc3_generic_write( ctx, RTC3_REG_SF_KEY1, &sfkey1, 1 );
}

// Set special function key byte 2 function

void rtc3_set_special_function_key2 ( rtc3_t *ctx, uint8_t sfkey2 )
{
    rtc3_generic_write( ctx, RTC3_REG_SF_KEY2, &sfkey2, 1 );
}

// Set frequency calibration control function

void rtc3_set_frequency_calibration( rtc3_t *ctx, uint8_t ftf )
{
    uint8_t w_temp;

    if ( ftf == 0 )
    {
        w_temp = RTC3_FTF_NORMAL_512_HZ;
        rtc3_generic_write( ctx, RTC3_REG_SFR, &w_temp, 1 );
    }

    if ( ftf == 1 )
    {
        w_temp = RTC3_FTF_1_HZ;
        rtc3_generic_write( ctx, RTC3_REG_SFR, &w_temp, 1 );
    }
}

// Get state of interrupt pin function

uint8_t rtc3_get_interrupt( rtc3_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

// ------------------------------------------------------------------------- END

