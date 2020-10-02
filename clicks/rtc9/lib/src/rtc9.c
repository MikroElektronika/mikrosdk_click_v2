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

#include "rtc9.h"

// ------------------------------------------------------------- PRIVATE MACROS 

// Leap year
#define NO_LEAP_YEAR 0
#define LEAP_YEAR 1
#define DUMMY 0

// ------------------------------------------------------------------ VARIABLES

static char MONTH_LIST[ 13 ][ 20 ] =
{
    "January", 
    "February", 
    "March", 
    "April", 
    "May", 
    "June", 
    "July", 
    "August", 
    "September", 
    "October", 
    "November", 
    "December"
};

static char WEEK_LIST[ 8 ][ 20 ] =
{
    "Sunday",
    "Monday", 
    "Tuesday", 
    "Wednesday", 
    "Thursday", 
    "Friday", 
    "Saturday"
};

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t drv_bcd_to_dec ( uint8_t bcd );
static uint8_t drv_dec_to_bcd ( uint8_t dec );
static uint8_t drv_get_number_of_days ( uint8_t month );
static uint8_t drv_check_leap_year ( uint8_t year );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc9_cfg_setup ( rtc9_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->rst = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = RTC9_SLAVE_ADDRESS;
}

RTC9_RETVAL rtc9_init ( rtc9_t *ctx, rtc9_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC9_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->rst, cfg->rst );

    digital_out_low( &ctx->rst );

    return RTC9_OK;
}

void rtc9_generic_write ( rtc9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc9_generic_read ( rtc9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
     i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

void rtc9_wakeup ( rtc9_t *ctx )
{
    uint8_t reg;
    uint8_t data_c;

    reg = 0x0C;
    data_c = 0x3F;
    rtc9_generic_write( ctx, reg, &data_c, 1 );
}

void rtc9_software_reset( rtc9_t *ctx ) 
{
    uint8_t tx_buf[ 5 ];

    tx_buf[ 0 ] = DUMMY;
    tx_buf[ 1 ] = DUMMY;
    tx_buf[ 2 ] = DUMMY;
    tx_buf[ 3 ] = DUMMY;
    tx_buf[ 4 ] = DUMMY;

    rtc9_generic_write( ctx, 0x00, tx_buf, 5 );
}

void rtc9_hardware_reset ( rtc9_t *ctx )
{
    digital_out_low( &ctx->rst );
    Delay_100ms( );
    digital_out_high( &ctx->rst );
    Delay_100ms( );
    Delay_100ms( );
    Delay_100ms( );
    digital_out_low( &ctx->rst );
    Delay_100ms( );
}

void rtc9_set_time( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec )
{
    uint8_t sec_data;
    uint8_t min_data;
    uint8_t hour_data;
    
    if ( sec >= 59 ) 
    {
        sec_data = drv_dec_to_bcd( 59 );
    }
    else 
    {
        sec_data = drv_dec_to_bcd( sec );
    }
    if ( min >= 59 ) 
    {
        min_data = drv_dec_to_bcd( 59 );
    }
    else 
    {
        min_data = drv_dec_to_bcd( min );
    }
    if ( hour >= 23 ) 
    {
        hour_data = drv_dec_to_bcd( 23 );
    }
    else 
    {
        hour_data = drv_dec_to_bcd( hour );
    }
    rtc9_generic_write( ctx, RTC9_REG_SECONDS, &sec_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_MINUTES, &min_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_CENTURY_HOURS, &hour_data, 1 );
}

void rtc9_set_date ( rtc9_t *ctx, rtc9_set_data_t *set_data )
{
    uint8_t year_data;
    uint8_t month_data;
    uint8_t week_data;
    uint8_t day_data;
    uint8_t tmp;
    
    uint8_t max_num_day;
    uint8_t leap_year;
    
    // Y-E-A-R
    if ( set_data->year >= 99 )
    { 
        year_data = drv_dec_to_bcd( 99 );
        set_data->year = 99;
    }
    else year_data = drv_dec_to_bcd( set_data->year );

    // M-O-N-T-H
    if ( set_data->month >= 12 )
    {
        month_data = drv_dec_to_bcd( 12 );
        set_data->month = 12;
    }
    else if ( set_data->month <= 1 )
    {
        month_data = drv_dec_to_bcd( 1 );
        set_data->month = 1;
    }
    else
    {
        month_data = drv_dec_to_bcd( set_data->month );
    }
    
    // D-A-Y  O-F  W-E-E-K
    if ( set_data->day_of_week >= 7 )
    { 
        week_data = drv_dec_to_bcd( 7 );
    }
    else 
    { 
        week_data = drv_dec_to_bcd( set_data->day_of_week );
    }
    
    // D-A-Y
    max_num_day = drv_get_number_of_days( set_data->month );
    leap_year = drv_check_leap_year( set_data->year );
    if ( leap_year != 0 )
    {
       max_num_day++;
    }
    
    if ( set_data->day >= max_num_day )
    {
        day_data = drv_dec_to_bcd( max_num_day );
    }
    else
    {
        day_data = drv_dec_to_bcd( set_data->day );
    }

    tmp = month_data & 0x1F;
    rtc9_generic_write( ctx, RTC9_REG_YEAR, &year_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_MONTH, &tmp, 1 );
    rtc9_generic_write( ctx, RTC9_REG_DAY, &week_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_DATE, &day_data, 1 );
}


void rtc9_get_time( rtc9_t *ctx, rtc9_get_time_t *get_time )
{
    uint8_t part_sec_data;
    uint8_t sec_data;
    uint8_t min_data;
    uint8_t hour_data;

    rtc9_generic_read( ctx, RTC9_REG_PART_SECONDS, &part_sec_data, 1 );
    get_time->part_sec = ( part_sec_data & 0x0F );
    get_time->part_sec += ( ( ( part_sec_data >> 4 ) & 0x0F ) * 10 );

    rtc9_generic_read( ctx, RTC9_REG_SECONDS, &sec_data, 1 );
    get_time->sec = drv_bcd_to_dec( sec_data & 0x7F );
    
    rtc9_generic_read( ctx, RTC9_REG_MINUTES, &min_data, 1 );
    get_time->min = drv_bcd_to_dec( min_data & 0x7F );

    rtc9_generic_read( ctx, RTC9_REG_CENTURY_HOURS, &hour_data, 1 );
    get_time->hour = drv_bcd_to_dec( hour_data & 0x3F );
}

void rtc9_get_date( rtc9_t *ctx, rtc9_get_date_t *get_data )
{
    uint8_t year_data;
    uint8_t month_data;
    uint8_t week_data;
    uint8_t day_data;

    rtc9_generic_read( ctx, RTC9_REG_DAY, &week_data, 1 );
    get_data->day_of_week = drv_bcd_to_dec( week_data & 0x07 );

    rtc9_generic_read( ctx, RTC9_REG_DATE, &day_data, 1 );
    get_data->day = drv_bcd_to_dec( day_data & 0x3F );
    
    rtc9_generic_read( ctx, RTC9_REG_MONTH, &month_data, 1 );
    get_data->month = drv_bcd_to_dec( month_data & 0x1F );

    rtc9_generic_read( ctx, RTC9_REG_YEAR, &year_data, 1 );
    get_data->year = drv_bcd_to_dec( year_data );
}

char *rtc9_current_month( uint8_t month )
{
    return MONTH_LIST[ month - 1 ];
}

char *rtc9_current_day_of_week( uint8_t day_of_week )
{
    return WEEK_LIST[ day_of_week - 1 ];
}

void rtc9_set_alarm_time( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec )
{
    uint8_t sec_data;
    uint8_t min_data;
    uint8_t hour_data;

    if ( sec >= 59 ) 
    {
       sec_data = drv_dec_to_bcd( 59 );
    }
    else 
    {
        sec_data = drv_dec_to_bcd( sec );
    }

    if ( min >= 59 )
    {
        min_data = drv_dec_to_bcd( 59 );
    }
    else 
    {
        min_data = drv_dec_to_bcd( min );
    }

    if ( hour >= 23 ) 
    {
        hour_data = drv_dec_to_bcd( 23 );
    }
    else 
    {
        hour_data = drv_dec_to_bcd( hour );
    } 

    rtc9_generic_write( ctx, RTC9_REG_ALARM1_SECONDS, &sec_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_ALARM1_MINUTES, &min_data, 1 );
    rtc9_generic_write( ctx, RTC9_REG_ALARM1_HOUR, &hour_data, 1 );
}

void rtc9_set_alarm_date ( rtc9_t *ctx, uint8_t day, uint8_t month, uint8_t year )
{
    uint8_t month_data;
    uint8_t day_data;
    uint8_t tmp;

    uint8_t max_num_day;
    uint8_t leap_year;

    // M-O-N-T-H
    if ( month >= 12 )
    {
        month_data = drv_dec_to_bcd( 12 );
        month = 12;
    }
    else if ( month <= 1 )
    {
        month_data = drv_dec_to_bcd( 1 );
        month = 1;
    }
    else
    {
        month_data = drv_dec_to_bcd( month );
    }
    
    // D-A-Y
    max_num_day = drv_get_number_of_days( month );
    leap_year = drv_check_leap_year( year );
    
    if ( leap_year != 0 )
    {
       max_num_day++;
    }

    if ( day >= max_num_day )
    {
        day_data = drv_dec_to_bcd( max_num_day );
    }
    else
    {
        day_data = drv_dec_to_bcd( day );
    }

    tmp = month_data & 0x1F;
    rtc9_generic_write( ctx, RTC9_REG_ALARM1_MONTH, &tmp, 1 );
    rtc9_generic_write( ctx, RTC9_REG_ALARM1_DATE, &day_data, 1 );
}

void rtc9_read_flag_status ( rtc9_t *ctx, uint8_t *read_data )
{
    rtc9_generic_read( ctx, RTC9_REG_FLAGS, read_data, 1 );
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint8_t drv_bcd_to_dec ( uint8_t bcd )
{
    return ( bcd & 0x0F ) + ( ( bcd >> 4 ) * 10 );
}

static uint8_t drv_dec_to_bcd ( uint8_t dec )
{
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t drv_get_number_of_days ( uint8_t month )
{
    uint8_t num_day;
    
    
    switch ( month )
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        {
            num_day = 31;
            break;
        }
        
        case 4:
        case 6:
        case 9:
        case 11:
        {
            num_day = 30;
            break;
        }
        
        case 2:
        {
            num_day = 28;
            break;
        }
    }
    return num_day;
}

static uint8_t drv_check_leap_year ( uint8_t year )
{
    uint16_t full_year;
    
    full_year = 2000 + year;
    
    if ( ( full_year % 400 ) == 0 )
    {
        return LEAP_YEAR;
    }
    else if ( ( full_year % 100 != 0 ) && ( full_year % 4 == 0 ) )
    {
        return LEAP_YEAR;
    }
    else
    {
        return NO_LEAP_YEAR;
    }
}

// ------------------------------------------------------------------------- END

