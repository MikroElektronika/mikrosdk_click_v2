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

#include "rtc7.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t rtc7_make_data_dec ( rtc7_t *ctx, uint8_t val, uint8_t val_mask );

static uint8_t rtc7_make_data_bin ( rtc7_t *ctx, uint8_t val, uint8_t val_mask );

static uint8_t rtc7_clear_data ( uint8_t val, uint8_t val_mask );

static void time_epoch_to_date ( long e, rtc7_time_t *ts );

static void get_dst ( uint8_t year, rtc7_time_t *start, rtc7_time_t *end );

static long time_date_to_epoch ( rtc7_time_t *ts );

static long rtc7_get_gmt_unix_time ( rtc7_t *ctx );

static long rtc7_get_local_unix_time ( rtc7_t *ctx );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc7_cfg_setup ( rtc7_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->itb   = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->ita = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x69;
}

RTC7_RETVAL rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC7_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->itb, cfg->itb );
    digital_in_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->ita, cfg->ita );
    
    return RTC7_OK;

}

void rtc7_generic_write ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc7_generic_read ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t rtc7_write_reg ( rtc7_t *ctx, uint8_t register_address, uint8_t transfer_data )
{
    if ( register_address > 0x74 )
    {
        return 1;
    }
    
    rtc7_generic_write( ctx, register_address, &transfer_data, 1 );   

    return 0;
}

uint8_t rtc7_read_reg ( rtc7_t *ctx, uint8_t register_address, uint8_t n_bytes, uint8_t *data_out )
{
    if ( register_address > 0x74 )
    {
        return 1;
    }

    rtc7_generic_read( ctx, register_address, data_out, n_bytes );
    
    return 0;
}

uint8_t rtc7_init_time ( rtc7_t *ctx, int8_t time_zone, uint8_t time_mode )
{
    uint8_t status;

    if ( ( time_zone > 14 ) || ( time_zone < -12 ) )
    {
        return 1;
    }
    if ( ( time_mode != RTC7_24HR_FORMAT ) && ( time_mode != RTC7_12HR_FORMAT ) )
    {
        return 2;
    }

    ctx->current_time_zone = time_zone;
    ctx->rtc7_am_pm |= time_mode >> 5;

    status = RTC7_WRITE_ALLOW | RTC7_READ_ALLOW;
    rtc7_write_reg( ctx, RTC7_CONFIG2_REG, status );
    status = time_mode;
    rtc7_write_reg( ctx, RTC7_HOURS_ADDR, status );
    status = RTC7_TIMER_RELOADS_VALUE | RTC7_TIMER_FREQ_16HZ | RTC7_TIMER_DIS;
    rtc7_write_reg( ctx, RTC7_TIMER_CONFIG_REG, status );
    status = RTC7_DISABLE_OSC | RTC7_NOT_RESET_DIGITAL_BLOCK;
    rtc7_write_reg( ctx, RTC7_CONFIG1_REG, status );
    status = RTC7_SLEEP_MODE_DIS;
    rtc7_write_reg( ctx, RTC7_SLEEP_CONFIG_REG, status );

    return 0;
}

void rtc7_enable_dst ( rtc7_t *ctx )
{
    ctx->dst_enabled = 1;
}

void rtc7_disable_dst ( rtc7_t *ctx )
{
    ctx->dst_enabled = 0;
}

uint8_t rtc7_set_osc ( rtc7_t *ctx, uint8_t enable_osc, uint8_t clk_in, uint8_t clk_out )
{
    uint8_t status;

    if ( ( enable_osc != RTC7_ENABLE_OSC ) && ( enable_osc != RTC7_DISABLE_OSC ) )
    {
        return 1;
    }
    if ( ( clk_in != RTC7_INPUT_FREQ_1HZ ) && ( clk_in != RTC7_INPUT_FREQ_50HZ ) && ( clk_in != RTC7_INPUT_FREQ_60HZ ) && ( clk_in != RTC7_INPUT_FREQ_32768HZ ) )
    {
        return 2;
    }
    if ( ( clk_out != RTC7_OUTPUT_FREQ_1HZ ) && ( clk_out != RTC7_OUTPUT_FREQ_4098HZ ) && ( clk_out != RTC7_OUTPUT_FREQ_8192HZ ) && ( clk_out != RTC7_OUTPUT_FREQ_32768HZ ) )
    {
        return 3;
    }
        
    rtc7_read_reg( ctx, RTC7_CONFIG1_REG, 1, &status );
    status &= 0xC1;
    status |= enable_osc;
    status |= clk_in;
    status |= clk_out;
    rtc7_write_reg( ctx, RTC7_CONFIG1_REG, status );
    
    return 0;
}

uint8_t rtc7_set_timer ( rtc7_t *ctx, uint8_t enable_timer, uint8_t timer_freq )
{
    uint8_t timer_data;

    if ( ( enable_timer != RTC7_TIMER_DIS ) && ( enable_timer != RTC7_TIMER_EN ) )
    {
        return 1;
    }
    if ( timer_freq > RTC7_TIMER_FREQ_16HZ )
    {
        return 2;
    }
        
    rtc7_read_reg( ctx, RTC7_TIMER_CONFIG_REG, 1, &timer_data );
    timer_data &= 0x0C;
    timer_data |= enable_timer;
    timer_data |= timer_freq;
    rtc7_write_reg( ctx, RTC7_TIMER_CONFIG_REG, timer_data );
    
    return 0;
}

void rtc7_reset ( rtc7_t *ctx )
{
    uint8_t status;
    
    rtc7_read_reg( ctx, RTC7_CONFIG1_REG, 1, &status );
    status &= 0xFE;
    rtc7_write_reg( ctx, RTC7_CONFIG1_REG, status );
    Delay_1sec( );
    status |= RTC7_NOT_RESET_DIGITAL_BLOCK;
    rtc7_write_reg( ctx, RTC7_CONFIG1_REG, status );
    Delay_100ms( );
}

void rtc7_get_gmt_time ( rtc7_t *ctx, rtc7_time_t *gmt_time )
{
    uint8_t buffer_data[ RTC7_TIMEDATE_BYTES ];
    
    if ( ctx->cycle_check == 0 )
    {
        ctx->current_zone = 0;
        rtc7_set_gmt_time( ctx, ctx->time_set_tmp );
        ctx->cycle_check = 1;
    }
    
    rtc7_read_reg( ctx, RTC7_SECONDS_ADDR, RTC7_TIMEDATE_BYTES, buffer_data );
    ctx->rtc7_am_pm |= ( buffer_data[ RTC7_HOURS_BYTE ] & 0x20 ) >> 5;
    ctx->rtc7_month_mode = ( buffer_data[ RTC7_MONTH_BYTE ] & 0x40 ) >> 6;
    ctx->rtc7_century = ( buffer_data[ RTC7_MONTH_BYTE ] & 0x80 ) >> 7;
    
    gmt_time->seconds = rtc7_make_data_dec( ctx, buffer_data[ RTC7_SECONDS_BYTE ], RTC7_SECONDS_MASK );
    gmt_time->minutes = rtc7_make_data_dec( ctx, buffer_data[ RTC7_MINUTES_BYTE ], RTC7_MINUTES_MASK );
    ctx->hours_check = 1;
    gmt_time->hours = rtc7_make_data_dec( ctx, buffer_data[ RTC7_HOURS_BYTE ], RTC7_HOURS_MASK );
    ctx->hours_check = 0;
    gmt_time->weekdays = rtc7_make_data_dec( ctx, buffer_data[ RTC7_DAY_BYTE ], RTC7_DAY_MASK );
    gmt_time->monthday = rtc7_make_data_dec( ctx, buffer_data[ RTC7_DATE_BYTE ], RTC7_DATE_MASK );
    gmt_time->month = rtc7_make_data_dec( ctx, buffer_data[ RTC7_MONTH_BYTE ], RTC7_MONTH_MASK );
    gmt_time->year = rtc7_make_data_dec( ctx, buffer_data[ RTC7_YEAR_BYTE ], RTC7_YEAR_MASK );
    
    if ( ctx->rtc7_am_pm & 0x02 )
    {
        if ( ( buffer_data[ RTC7_HOURS_BYTE ] == 0 ) && ( ( ctx->val_pom & 0x20 ) != 0 ) )
        {
            rtc7_write_reg( ctx, RTC7_HOURS_ADDR, RTC7_12HR_FORMAT | RTC7_INDICATES_AM );
            ctx->rtc7_am_pm &= 0xFE;
        }
    }
    rtc7_read_reg( ctx, RTC7_HOURS_ADDR, 1, &ctx->val_pom );
}

void rtc7_get_local_time ( rtc7_t *ctx, rtc7_time_t *local_time )
{
    rtc7_time_t start_dst;
    rtc7_time_t end_dst;
    long temp_time_unix;
    
    if ( ctx->cycle_check == 0 )
    {
        ctx->current_zone = 1;
        rtc7_set_gmt_time( ctx, ctx -> time_set_tmp );
        ctx->cycle_check = 1;
    }
    
    temp_time_unix = rtc7_get_gmt_unix_time( ctx  );

    temp_time_unix += ( ctx->current_time_zone * 60 * 60 );

    time_epoch_to_date( temp_time_unix, local_time );

    if ( ctx->dst_enabled )
    {
        get_dst( local_time->year, &start_dst, &end_dst );

        if ( ( local_time->month > start_dst.month ) && ( local_time->month < end_dst.month ) )
        {
            temp_time_unix = time_date_to_epoch( local_time );
            temp_time_unix += 60 * 60 * 1000;
        }
        else if ( ( ( local_time->month == end_dst.month ) && ( local_time->monthday < end_dst.monthday ) ) ||
                  ( ( local_time->month == end_dst.month ) && ( local_time->hours < 2 ) ) )
        {
            temp_time_unix = time_date_to_epoch( local_time );
            temp_time_unix += 60 * 60 * 1000;
        }
        else if ( ( ( local_time->month == start_dst.month ) && ( local_time->monthday > start_dst.monthday ) ) ||
                  ( ( local_time->month == start_dst.month ) && ( local_time->monthday == start_dst.monthday ) && ( local_time->hours >= 2 ) ) )
        {
            temp_time_unix = time_date_to_epoch( local_time );
            temp_time_unix += 60 * 60 * 1000;
        }
        else
            temp_time_unix -= 60 * 60 * 1000;
    }

    time_epoch_to_date( temp_time_unix, local_time );
    
    if ( ctx->rtc7_am_pm & 0x02 )
    {
        if ( ( local_time->hours == 0 ) && ( ctx->val_pom1 == 23 ) )
        {
            rtc7_write_reg( ctx, RTC7_HOURS_ADDR, RTC7_12HR_FORMAT | RTC7_INDICATES_AM );
            ctx->rtc7_am_pm &= 0xFE;
        }
        else if ( local_time->hours >= 12 )
        {
            ctx->val_pom1 = local_time->hours;
            local_time->hours -= 12;
            ctx->rtc7_am_pm |= 0x01;
        }
        else
        {
            ctx->val_pom1 = local_time->hours;
            ctx->rtc7_am_pm &= 0xFE;
        }
    }
}

uint8_t rtc7_set_gmt_time( rtc7_t *ctx, rtc7_time_t *time )
{
    uint8_t buffer_data[ RTC7_TIMEDATE_BYTES ];

    if ( time->seconds > 59 || time->minutes > 59 || time->hours > 24 || time->weekdays > 7 || time->weekdays < 1 ||
         time->monthday > 31 || time->monthday < 1 || time->month > 12 || time->month < 1 || time->year > 99 )
    {
        return 1;
    }
    
    buffer_data[ RTC7_SECONDS_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_SECONDS_BYTE ], RTC7_SECONDS_MASK );
    buffer_data[ RTC7_SECONDS_BYTE ] |= rtc7_make_data_bin( ctx, time->seconds, RTC7_SECONDS_MASK );
    buffer_data[ RTC7_MINUTES_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_MINUTES_BYTE ], RTC7_MINUTES_MASK );
    buffer_data[ RTC7_MINUTES_BYTE ] |= rtc7_make_data_bin( ctx, time->minutes, RTC7_MINUTES_MASK );
    ctx->hours_check = 1;
    buffer_data[ RTC7_HOURS_BYTE ] = rtc7_make_data_bin( ctx, time->hours, RTC7_HOURS_MASK );
    ctx->hours_check = 0;
    buffer_data[ RTC7_DAY_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_DAY_BYTE ], RTC7_DAY_MASK );
    buffer_data[ RTC7_DAY_BYTE ] |= rtc7_make_data_bin( ctx, time->weekdays, RTC7_DAY_MASK );
    buffer_data[ RTC7_DATE_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_DATE_BYTE ], RTC7_DATE_MASK );
    buffer_data[ RTC7_DATE_BYTE ] |= rtc7_make_data_bin( ctx, time->monthday, RTC7_DATE_MASK );
    buffer_data[ RTC7_MONTH_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_MONTH_BYTE ], RTC7_MONTH_MASK );
    buffer_data[ RTC7_MONTH_BYTE ] |= rtc7_make_data_bin( ctx, time->month, RTC7_MONTH_MASK );
    buffer_data[ RTC7_YEAR_BYTE ] = rtc7_clear_data( buffer_data[ RTC7_YEAR_BYTE ], RTC7_YEAR_MASK );
    buffer_data[ RTC7_YEAR_BYTE ] |= rtc7_make_data_bin( ctx, time->year, RTC7_YEAR_MASK );
    
    rtc7_write_reg( ctx, RTC7_SECONDS_ADDR, buffer_data[ RTC7_SECONDS_BYTE ] );
    rtc7_write_reg( ctx, RTC7_MINUTES_ADDR, buffer_data[ RTC7_MINUTES_BYTE ] );
    rtc7_write_reg( ctx, RTC7_HOURS_ADDR, buffer_data[ RTC7_HOURS_BYTE ] );
    rtc7_write_reg( ctx, RTC7_DAY_ADDR, buffer_data[ RTC7_DAY_BYTE ] );
    rtc7_write_reg( ctx, RTC7_DATE_ADDR, buffer_data[ RTC7_DATE_BYTE ] );
    rtc7_write_reg( ctx, RTC7_MONTH_ADDR, buffer_data[ RTC7_MONTH_BYTE ] );
    rtc7_write_reg( ctx, RTC7_YEAR_ADDR, buffer_data[ RTC7_YEAR_BYTE ] );
    
    ctx->time_set_tmp = time;

    return 0;
}

uint8_t rtc7_check_interr ( rtc7_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->ita );

    if ( state )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8_t rtc7_check_psw ( rtc7_t *ctx )
{
    uint8_t state;

    state = digital_in_read( &ctx->rst );

    if ( state )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t rtc7_make_data_dec ( rtc7_t *ctx, uint8_t val, uint8_t val_mask )
{ 
    uint8_t tmp = val;
    
    tmp &= val_mask;
    tmp = ( tmp & 15 ) + ( ( tmp >> 4 ) * 10 );
    
    if ( ctx->hours_check )
    {
        if ( ( ctx->rtc7_am_pm & 0x02 ) == 0 )
        {
            if ( ctx->rtc7_am_pm & 0x01 )
                tmp += 20;
        }
    }

    return tmp;
}

static uint8_t rtc7_make_data_bin ( rtc7_t *ctx, uint8_t val, uint8_t val_mask )
{
    uint8_t tmp = val;
    
    if ( ctx->hours_check )
    {
        tmp = 0;
        if ( ( ctx->rtc7_am_pm ) && ( ctx->current_zone == 0 ) )
        {
            if (  val == 24)
            {
                val = 0;
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
            }
            else if ( val > 12 )
            {
                val -= 12;
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
                tmp |= 0x20;
            }
            else if ( val == 12 )
            {
                val = 0;
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
                tmp |= 0x20;
            }
            else
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
            tmp |= 0x40;
        }
        else
        {
            if ( val == 24 )
            {
                val = 0;
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
            }
            else if ( val >= 20 )
            {
                val -= 20;
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
                tmp |= 0x20;
            }
            else
                tmp = ( ( val / 10 ) << 4 ) + ( val % 10 );
        }
    }
    else
    {
        tmp = ( ( tmp / 10 ) << 4 ) + ( tmp % 10 );
        tmp &= val_mask;
    }

    return tmp;
}

static uint8_t rtc7_clear_data ( uint8_t val, uint8_t val_mask )
{
    uint8_t tmp = val;
    
    tmp &= ~val_mask;
    
    return tmp;
}

static void time_epoch_to_date ( long e, rtc7_time_t *ts )
{
    long julian_day;

    long j;
    long k;
    long l;
    long n;
    long nn;
    long i;

    julian_day = e;
    julian_day /= RTC7_TIME_SEC_IN_24_HOURS;
    julian_day += RTC7_JULIAN_DAY_1970;

    if ( e < 0 )
        julian_day--;

    ts->weekdays = julian_day % 7;

    l = julian_day + 68569;
    n = 4 * l;
    n /= 146097;
    nn = 146097 * n;
    nn += 3;
    nn /= 4;
    l -= nn;
    i = 4000 * ( l + 1 );
    i /= 1461001;
    nn = 1461 * i;
    nn /= 4;
    nn -= 31;
    l -= nn;
    j = 80 * l;
    j /= 2447;
    k = l - ( 2447 * j ) / 80;
    l = j / 11;
    j = j + 2 - 12 * l;
    i = ( 100 * ( n - 49 ) + i + l ) - 2000;

    ts->year = i;
    ts->month = j;
    ts->monthday = k;

    if ( e < 0 )
    {
        e *= -1;
        e %= RTC7_TIME_SEC_IN_24_HOURS;
        e = RTC7_TIME_SEC_IN_24_HOURS - e;
    }

    l = e % RTC7_TIME_SEC_IN_24_HOURS;
    k = l / RTC7_TIME_SEC_IN_HOUR;
    ts->hours = k;

    k = l;
    k -= ( uint32_t )ts->hours * RTC7_TIME_SEC_IN_HOUR;
    k /= RTC7_TIME_SEC_IN_MIN;
    ts->minutes = k;

    k = l % RTC7_TIME_SEC_IN_MIN;
    ts->seconds = k;
    ts->weekdays++;
}

static void get_dst ( uint8_t year, rtc7_time_t *start, rtc7_time_t *end )
{
    start->seconds = 0;
    start->minutes = 0;
    start->hours = 2;
    start->weekdays = 7;
    start->monthday = 14 - ( ( 1 + ( ( year * 5 ) / 4 ) ) % 7 );
    start->month = 3;
    start->year = year;

    end->seconds  = 0;
    end->minutes  = 0;
    end->hours  = 2;
    end->weekdays  = 7;
    end->monthday  = 7 - ( ( 1 + ( ( year * 5 ) / 4 ) ) % 7 );
    end->month  = 11;
    end->year  = year;
}

static long time_date_to_epoch ( rtc7_time_t *ts )
{
    uint32_t ji;
    uint32_t julian_day;
    uint32_t sec;
    long e;

    ji = ts->year + 2000 + 4800;
    ji *= 12;
    ji += ts->month - 3;

    julian_day = ( 2 * ( ji % 12 ) + 7 + 365 * ji ) / 12;
    julian_day += ts->monthday + ( ji / 48 ) - 32083;
    if ( julian_day > 2299171L )
    {
        julian_day += ji / 4800 - ji / 1200 + 38;
    }
    ts->weekdays = ( julian_day % 7 );

    sec = ts->hours;
    sec *= RTC7_TIME_SEC_IN_HOUR;
    sec += ts->minutes * RTC7_TIME_SEC_IN_MIN;
    sec += ts->seconds;

    e = ( julian_day - RTC7_JULIAN_DAY_1970 );
    e *= RTC7_TIME_SEC_IN_24_HOURS;
    e += sec;
    
    return e;
}

static long rtc7_get_gmt_unix_time ( rtc7_t *ctx )
{
    rtc7_time_t temp_time;
    
    long temp;
    
    rtc7_get_gmt_time(  ctx, &temp_time );

    temp = time_date_to_epoch( &temp_time );

    return temp;
}

static long rtc7_get_local_unix_time ( rtc7_t *ctx )
{
    long temp;
    rtc7_time_t temp_time;

    rtc7_get_local_time( ctx, &temp_time );
    temp = time_date_to_epoch( &temp_time );

    return temp;
}

// ------------------------------------------------------------------------- END

