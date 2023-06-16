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
#include "conversions.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static void time_epoch_to_date ( int32_t epoch_time, rtc7_time_t *ts );

static int32_t time_date_to_epoch ( rtc7_time_t *ts );

static err_t rtc7_get_gmt_unix_time ( rtc7_t *ctx, int32_t *unix_time );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc7_cfg_setup ( rtc7_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->itb = HAL_PIN_NC;
    cfg->rst = HAL_PIN_NC;
    cfg->ita = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x69;
}

err_t rtc7_init ( rtc7_t *ctx, rtc7_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return RTC7_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins
    digital_in_init( &ctx->itb, cfg->itb );
    digital_in_init( &ctx->rst, cfg->rst );
    digital_in_init( &ctx->ita, cfg->ita );
    
    return RTC7_OK;
}

err_t rtc7_generic_write ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );  
}

err_t rtc7_generic_read ( rtc7_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

err_t rtc7_write_reg ( rtc7_t *ctx, uint8_t reg, uint8_t data_in )
{
    if ( reg > 0x74 )
    {
        return RTC7_ERROR;
    }
    return rtc7_generic_write( ctx, reg, &data_in, 1 );
}

err_t rtc7_read_reg ( rtc7_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len )
{
    if ( reg > 0x74 )
    {
        return RTC7_ERROR;
    }
    return rtc7_generic_read( ctx, reg, data_out, len );
}

err_t rtc7_init_time ( rtc7_t *ctx, int8_t time_zone )
{
    if ( ( time_zone > 14 ) || ( time_zone < -12 ) )
    {
        return RTC7_ERROR;
    }

    ctx->current_time_zone = time_zone;

    err_t error_flag = rtc7_write_reg( ctx, RTC7_CONFIG2_REG, RTC7_WRITE_ALLOW | RTC7_READ_ALLOW );
    error_flag |= rtc7_write_reg( ctx, RTC7_TIMER_CONFIG_REG, 
                                  RTC7_TIMER_RELOADS_VALUE | RTC7_TIMER_FREQ_16HZ | RTC7_TIMER_EN );
    error_flag |= rtc7_write_reg( ctx, RTC7_CONFIG1_REG, RTC7_DISABLE_OSC | RTC7_NOT_RESET_DIGITAL_BLOCK );
    error_flag |= rtc7_write_reg( ctx, RTC7_SLEEP_CONFIG_REG, RTC7_SLEEP_MODE_DIS );
    error_flag |= rtc7_write_reg( ctx, RTC7_INT_EN_REG, RTC7_TIMER_INTERR_EN );

    return error_flag;
}

err_t rtc7_set_osc ( rtc7_t *ctx, uint8_t enable_osc, uint8_t clk_in, uint8_t clk_out )
{
    uint8_t config1 = 0;

    if ( ( RTC7_ENABLE_OSC != enable_osc ) && ( RTC7_DISABLE_OSC != enable_osc ) )
    {
        return RTC7_ERROR;
    }
    if ( ( RTC7_INPUT_FREQ_1HZ != clk_in ) && ( RTC7_INPUT_FREQ_50HZ != clk_in ) && 
         ( RTC7_INPUT_FREQ_60HZ != clk_in ) && ( RTC7_INPUT_FREQ_32768HZ != clk_in ) )
    {
        return RTC7_ERROR;
    }
    if ( ( RTC7_OUTPUT_FREQ_1HZ != clk_out ) && ( RTC7_OUTPUT_FREQ_4098HZ != clk_out ) && 
         ( RTC7_OUTPUT_FREQ_8192HZ != clk_out ) && ( RTC7_OUTPUT_FREQ_32768HZ != clk_out ) )
    {
        return RTC7_ERROR;
    }
        
    err_t error_flag = rtc7_read_reg( ctx, RTC7_CONFIG1_REG, &config1, 1 );
    config1 &= 0xC1;
    config1 |= enable_osc;
    config1 |= clk_in;
    config1 |= clk_out;
    error_flag |= rtc7_write_reg( ctx, RTC7_CONFIG1_REG, config1 );
    
    return error_flag;
}

err_t rtc7_set_timer ( rtc7_t *ctx, uint8_t enable_timer, uint8_t timer_freq )
{
    uint8_t timer_data = 0;

    if ( ( RTC7_TIMER_DIS != enable_timer ) && ( RTC7_TIMER_EN != enable_timer ) )
    {
        return RTC7_ERROR;
    }
    if ( timer_freq > RTC7_TIMER_FREQ_16HZ )
    {
        return RTC7_ERROR;
    }
        
    err_t error_flag = rtc7_read_reg( ctx, RTC7_TIMER_CONFIG_REG, &timer_data, 1 );
    timer_data &= 0x0C;
    timer_data |= enable_timer;
    timer_data |= timer_freq;
    error_flag |= rtc7_write_reg( ctx, RTC7_TIMER_CONFIG_REG, timer_data );
    
    return error_flag;
}

err_t rtc7_reset ( rtc7_t *ctx )
{
    uint8_t config1 = 0;
    err_t error_flag = rtc7_read_reg( ctx, RTC7_CONFIG1_REG, &config1, 1 );
    config1 &= 0xFE;
    error_flag |= rtc7_write_reg( ctx, RTC7_CONFIG1_REG, config1 );
    Delay_1sec( );
    config1 |= RTC7_NOT_RESET_DIGITAL_BLOCK;
    error_flag |= rtc7_write_reg( ctx, RTC7_CONFIG1_REG, config1 );
    Delay_100ms( );
    return error_flag;
}

err_t rtc7_get_gmt_time ( rtc7_t *ctx, rtc7_time_t *gmt_time )
{
    uint8_t buffer_data[ RTC7_TIMEDATE_BYTES ] = { 0 };
    err_t error_flag = RTC7_OK;
    
    error_flag |= rtc7_read_reg( ctx, RTC7_SECONDS_ADDR, buffer_data, RTC7_TIMEDATE_BYTES );
    ctx->rtc7_century = ( buffer_data[ RTC7_MONTH_BYTE ] & 0x80 ) >> 7;
    
    gmt_time->seconds = bcd_to_dec ( buffer_data[ RTC7_SECONDS_BYTE ] );
    gmt_time->minutes = bcd_to_dec ( buffer_data[ RTC7_MINUTES_BYTE ] );
    gmt_time->hours = bcd_to_dec ( buffer_data[ RTC7_HOURS_BYTE ] );
    gmt_time->weekdays = bcd_to_dec ( buffer_data[ RTC7_DAY_BYTE ] );
    gmt_time->monthday = bcd_to_dec ( buffer_data[ RTC7_DATE_BYTE ] );
    gmt_time->month = bcd_to_dec ( buffer_data[ RTC7_MONTH_BYTE ] );
    gmt_time->year = bcd_to_dec ( buffer_data[ RTC7_YEAR_BYTE ] );
    
    return error_flag;
}

err_t rtc7_get_local_time ( rtc7_t *ctx, rtc7_time_t *local_time )
{
    int32_t temp_time_unix = 0;
    
    err_t error_flag = rtc7_get_gmt_unix_time( ctx, &temp_time_unix );
    
    temp_time_unix += ( ctx->current_time_zone * 60 * 60 );

    time_epoch_to_date( temp_time_unix, local_time );
    
    return error_flag;
}

err_t rtc7_set_gmt_time( rtc7_t *ctx, rtc7_time_t *time )
{
    err_t error_flag = RTC7_OK;
    uint8_t buffer_data[ RTC7_TIMEDATE_BYTES ] = { 0 };

    if ( time->seconds > 59 || time->minutes > 59 || time->hours > 24 || time->weekdays > 7 || 
         time->weekdays < 1 || time->monthday > 31 || time->monthday < 1 || time->month > 12 || 
         time->month < 1 || time->year > 99 )
    {
        return RTC7_ERROR;
    }
    
    buffer_data[ RTC7_SECONDS_BYTE ] = dec_to_bcd ( time->seconds );
    buffer_data[ RTC7_MINUTES_BYTE ] = dec_to_bcd ( time->minutes );
    buffer_data[ RTC7_HOURS_BYTE ] = dec_to_bcd ( time->hours );
    buffer_data[ RTC7_DAY_BYTE ] = dec_to_bcd ( time->weekdays );
    buffer_data[ RTC7_DATE_BYTE ] = dec_to_bcd ( time->monthday );
    buffer_data[ RTC7_MONTH_BYTE ] = dec_to_bcd ( time->month );
    buffer_data[ RTC7_YEAR_BYTE ] = dec_to_bcd ( time->year );
    
    error_flag |= rtc7_write_reg( ctx, RTC7_SECONDS_ADDR, buffer_data[ RTC7_SECONDS_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_MINUTES_ADDR, buffer_data[ RTC7_MINUTES_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_HOURS_ADDR, buffer_data[ RTC7_HOURS_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_DAY_ADDR, buffer_data[ RTC7_DAY_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_DATE_ADDR, buffer_data[ RTC7_DATE_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_MONTH_ADDR, buffer_data[ RTC7_MONTH_BYTE ] );
    error_flag |= rtc7_write_reg( ctx, RTC7_YEAR_ADDR, buffer_data[ RTC7_YEAR_BYTE ] );
    
    return error_flag;
}

uint8_t rtc7_check_interrupt ( rtc7_t *ctx )
{
    return digital_in_read( &ctx->ita );
}

uint8_t rtc7_check_psw ( rtc7_t *ctx )
{
    return digital_in_read( &ctx->rst );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static void time_epoch_to_date ( int32_t epoch_time, rtc7_time_t *ts )
{
    int32_t julian_day = 0;
    int32_t val_j = 0;
    int32_t val_k = 0;
    int32_t val_l = 0;
    int32_t val_n = 0;
    int32_t val_nn = 0;
    int32_t val_i = 0;

    julian_day = epoch_time;
    julian_day /= RTC7_TIME_SEC_IN_24_HOURS;
    julian_day += RTC7_JULIAN_DAY_1970;

    if ( epoch_time < 0 )
    {
        julian_day--;
    }

    ts->weekdays = julian_day % 7;

    val_l = julian_day + 68569ul;
    val_n = 4 * val_l;
    val_n /= 146097ul;
    val_nn = 146097ul * val_n;
    val_nn += 3;
    val_nn /= 4;
    val_l -= val_nn;
    val_i = 4000 * ( val_l + 1 );
    val_i /= 1461001ul;
    val_nn = 1461 * val_i;
    val_nn /= 4;
    val_nn -= 31;
    val_l -= val_nn;
    val_j = 80 * val_l;
    val_j /= 2447;
    val_k = val_l - ( 2447 * val_j ) / 80;
    val_l = val_j / 11;
    val_j = val_j + 2 - 12 * val_l;
    val_i = ( 100 * ( val_n - 49 ) + val_i + val_l ) - 2000;

    ts->year = val_i;
    ts->month = val_j;
    ts->monthday = val_k;

    if ( epoch_time < 0 )
    {
        epoch_time *= -1;
        epoch_time %= RTC7_TIME_SEC_IN_24_HOURS;
        epoch_time = RTC7_TIME_SEC_IN_24_HOURS - epoch_time;
    }

    val_l = epoch_time % RTC7_TIME_SEC_IN_24_HOURS;
    val_k = val_l / RTC7_TIME_SEC_IN_HOUR;
    ts->hours = val_k;

    val_k = val_l;
    val_k -= ( uint32_t ) ts->hours * RTC7_TIME_SEC_IN_HOUR;
    val_k /= RTC7_TIME_SEC_IN_MIN;
    ts->minutes = val_k;

    val_k = val_l % RTC7_TIME_SEC_IN_MIN;
    ts->seconds = val_k;
    ts->weekdays++;
}

static int32_t time_date_to_epoch ( rtc7_time_t *ts )
{
    uint32_t val_ji = 0;
    uint32_t julian_day = 0;
    uint32_t sec = 0;
    int32_t epoch_time = 0;

    val_ji = ts->year + 2000 + 4800;
    val_ji *= 12;
    val_ji += ts->month - 3;

    julian_day = ( 2 * ( val_ji % 12 ) + 7 + 365 * val_ji ) / 12;
    julian_day += ts->monthday + ( val_ji / 48 ) - 32083;
    if ( julian_day > 2299171ul )
    {
        julian_day += val_ji / 4800 - val_ji / 1200 + 38;
    }
    ts->weekdays = ( julian_day % 7 );

    sec = ts->hours;
    sec *= RTC7_TIME_SEC_IN_HOUR;
    sec += ts->minutes * RTC7_TIME_SEC_IN_MIN;
    sec += ts->seconds;

    epoch_time = ( julian_day - RTC7_JULIAN_DAY_1970 );
    epoch_time *= RTC7_TIME_SEC_IN_24_HOURS;
    epoch_time += sec;
    
    return epoch_time;
}

static err_t rtc7_get_gmt_unix_time ( rtc7_t *ctx, int32_t *unix_time )
{
    rtc7_time_t temp_time;
    err_t error_flag = rtc7_get_gmt_time( ctx, &temp_time );
    *unix_time = time_date_to_epoch( &temp_time );
    return error_flag;
}

// ------------------------------------------------------------------------- END

