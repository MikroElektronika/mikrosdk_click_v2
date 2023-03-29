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

#include "rtc6.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint16_t format_to_bin ( uint16_t value );

static uint16_t foramt_to_bcd ( uint16_t value );

static void time_epoch_to_date ( int32_t e, rtc6_time_t *time_seg );

static uint32_t time_date_to_epoch( rtc6_time_t *time_seg );

static void trigger_switch ( uint8_t trigger, uint8_t *temp );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc6_cfg_setup ( rtc6_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x6F;

    cfg->time_zone_cfg = -1;
}

RTC6_RETVAL rtc6_init ( rtc6_t *ctx, rtc6_cfg_t *cfg )
{
     i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed    = cfg->i2c_speed;
    i2c_cfg.scl      = cfg->scl;
    i2c_cfg.sda      = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC6_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC6_OK;

}

void rtc6_default_cfg ( rtc6_t *ctx, int8_t time_zone, rtc6_time_t *utc_time, rtc6_time_t *alarm_time )
{
    rtc6_init_fun( ctx, time_zone );
    rtc6_set_gmt_time( ctx, utc_time );
    rtc6_set_alarm( ctx, RTC6_ALARM_0, RTC6_REG_ALARM0_SECOND, alarm_time );
}

void rtc6_generic_write ( rtc6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc6_generic_read ( rtc6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t rtc6_init_fun ( rtc6_t *ctx, int8_t time_zone )
{
    uint8_t status;

    if ( ( time_zone > 14 ) || ( time_zone < -12 ) )
    {
        return SET_ERROR;
    }
    
    ctx->time_zone = time_zone;

    ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;

    rtc6_generic_read( ctx, RTC6_REG_SECONDS, &status, 1 );

    status |= 0x07;

    rtc6_generic_write( ctx, RTC6_REG_SECONDS, &status, 1 );


    if ( ( status != 0 ) & 0x80 )
    {
        status |= 0x07;

        rtc6_generic_write( ctx, RTC6_REG_SECONDS, &status, 1 );
    }

    return DEVICE_OK;
}

void rtc6_enable_swo ( rtc6_t *ctx, uint8_t swo )
{
    uint8_t temp;
    
    rtc6_generic_read( ctx, RTC6_REG_CONTROL, &temp, 1 );

    temp |= 0x40;

    switch ( swo )
    {
        case RTC6_SWO_1HZ:
        {
            temp &= 0xF8;
            break;
        }
        case RTC6_SWO_4_096KHZ:
        {
            temp &= 0xF8;
            temp |= 0x01;
            break;
        }
        case RTC6_SWO_8_192KHZ:
        {
            temp &= 0xF8;
            temp |= 0x02;
            break;
        }
        case RTC6_SWO_32_768KHZ:
        {
            temp &= 0xF8;
            temp |= 0x03;
            break;
        }
        default:
        {
            break;
        }
    }

    rtc6_generic_write( ctx, RTC6_REG_CONTROL, &temp, 1 );
}

void rtc6_disable_swo ( rtc6_t *ctx )
{
    uint8_t temp;

    rtc6_generic_read( ctx, RTC6_REG_CONTROL, &temp, 1 );

    temp &= 0xBF;

    rtc6_generic_write( ctx, RTC6_REG_CONTROL,  &temp, 1 );
}

void rtc6_battery_enable ( rtc6_t *ctx )
{
    uint8_t temp = 0;

    rtc6_generic_read( ctx, RTC6_REG_DAY, &temp, 1 );

    temp |= ( 1 << 3 );

    rtc6_generic_write( ctx, RTC6_REG_DAY, &temp, 1 );
}

void rtc6_get_gmt_time ( rtc6_t *ctx, rtc6_time_t *gmt_time )
{
    uint8_t buffer[ 7 ];
    
    rtc6_generic_read( ctx, RTC6_REG_SECONDS, &buffer, 7 );

    gmt_time->seconds  = format_to_bin( buffer[ RTC6_SECONDS_BYTE ] & 0x7F );
    gmt_time->minutes  = format_to_bin( buffer[ RTC6_MINUTES_BYTE ] & 0x7F );
    gmt_time->hours    = format_to_bin( buffer[ RTC6_HOUR_BYTE ]    & 0x3F );
    gmt_time->weekdays = format_to_bin( buffer[ RTC6_DAY_BYTE ]     & 0x07 );
    gmt_time->monthday = format_to_bin( buffer[ RTC6_DATE_BYTE ]    & 0x3F );
    gmt_time->month    = format_to_bin( buffer[ RTC6_MONTH_BYTE ]   & 0x1F );
    gmt_time->year     = format_to_bin( buffer[ RTC6_YEAR_BYTE ]    & 0xFF );
}

void rtc6_set_gmt_time ( rtc6_t *ctx, rtc6_time_t *set_time )
{
    uint8_t buffer[ 7 ] = { 0 };

    rtc6_generic_read( ctx, RTC6_REG_SECONDS, buffer, 7 );

    buffer[ RTC6_SECONDS_BYTE ] =  buffer[ RTC6_SECONDS_BYTE ] & 0x80 | 0x80;
    buffer[ RTC6_SECONDS_BYTE ] |= foramt_to_bcd( set_time->seconds );

    buffer[ RTC6_MINUTES_BYTE ] = buffer[ RTC6_MINUTES_BYTE ] & 0x80;
    buffer[ RTC6_MINUTES_BYTE ] |= foramt_to_bcd( set_time->minutes );
            
    buffer[ RTC6_HOUR_BYTE ] = buffer[ RTC6_HOUR_BYTE ] & 0xC0;
    buffer[ RTC6_HOUR_BYTE ] |= foramt_to_bcd( set_time->hours );
            
    buffer[ RTC6_DAY_BYTE ] = buffer[ RTC6_DAY_BYTE ] & 0xF8;
    buffer[ RTC6_DAY_BYTE ] |= foramt_to_bcd( set_time->weekdays );
            
    buffer[ RTC6_DATE_BYTE ] = buffer[ RTC6_DATE_BYTE ] & 0xC0;
    buffer[ RTC6_DATE_BYTE ] |= foramt_to_bcd( set_time->monthday );
            
    buffer[ RTC6_MONTH_BYTE ] = buffer[ RTC6_MONTH_BYTE ] & 0xE0;
    buffer[ RTC6_MONTH_BYTE ] |= foramt_to_bcd( set_time->month );
            
    buffer[ RTC6_YEAR_BYTE ] =  buffer[ RTC6_YEAR_BYTE ] & 0x00;
    buffer[ RTC6_YEAR_BYTE ] |= foramt_to_bcd( set_time->year );

    rtc6_generic_write( ctx, RTC6_REG_SECONDS, buffer, 7 );
}

void rtc6_get_local_time ( rtc6_t *ctx, rtc6_time_t *local_time )
{
    uint32_t temp_time_unix;
    rtc6_time_t *ltime;
    
    ltime = local_time;
    
    temp_time_unix = rtc6_get_gmt_unix_time( ctx );
    temp_time_unix += ( uint32_t )( ctx->time_zone * 3600 );
    time_epoch_to_date ( temp_time_unix, ltime );
}

uint32_t rtc6_get_gmt_unix_time ( rtc6_t *ctx )
{
    rtc6_time_t time;
    uint32_t temp;
    
    rtc6_get_gmt_time( ctx, &time );
    temp = time_date_to_epoch( &time );

    return temp;
}

uint32_t rtc6_get_local_unix_time( rtc6_t *ctx )
{
    uint32_t temp;
    rtc6_time_t time;
    
    rtc6_get_local_time( ctx, &time );
    temp = time_date_to_epoch( &time );
    
    return temp;
}

uint8_t rtc6_is_leap_year ( rtc6_t *ctx )
{
    volatile uint8_t temp;
    
    rtc6_generic_read( ctx, RTC6_REG_MONTH, &temp, 1 );
    temp = temp & 0x20;
    
    if ( temp == 0 )
    {
        return DEVICE_ERROR;
    }

    return DEVICE_OK;
}

uint8_t rtc6_is_power_failure ( rtc6_t *ctx )
{
    uint8_t temp;

    rtc6_generic_read( ctx, RTC6_REG_DAY, &temp, 1 );
    
    temp &= 0x10;
    
    if ( temp == 0 )
    {
        return DEVICE_ERROR;
    }

    return DEVICE_OK;
}

void rtc6_get_last_power_failure ( rtc6_t *ctx, rtc6_time_t *last_time )
{
    uint8_t buffer[ 4 ];

    rtc6_generic_read( ctx, RTC6_REG_POWER_DOWN_MINUTE, buffer, 4 );
    
    last_time->minutes  = format_to_bin( buffer[ 0 ] & 0x7F );
    last_time->hours    = format_to_bin( buffer[ 1 ] & 0x3F );
    last_time->monthday = format_to_bin( buffer[ 2 ] & 0x07 );
    last_time->weekdays = format_to_bin( buffer[ 3 ] & 0xE0 );
    last_time->month    = format_to_bin( buffer[ 3 ] & 0x1F );
}

// --------------------------- Alarm

void rtc6_set_alarm ( rtc6_t *ctx, uint8_t alarm, uint8_t trigger, rtc6_time_t *time )
{
    uint8_t buffer[ 6 ];
    uint8_t temp;

    switch ( alarm )
    {
        case RTC6_ALARM_0:
        {
            rtc6_generic_read( ctx, RTC6_REG_ALARM0_SECOND, buffer, 6 );
            buffer[ RTC6_SECONDS_BYTE ] =  buffer[ RTC6_SECONDS_BYTE ] & 0x80;
            buffer[ RTC6_SECONDS_BYTE ] |= foramt_to_bcd( time->seconds );
                
            buffer[ RTC6_MINUTES_BYTE ] =  buffer[ RTC6_MINUTES_BYTE ] & 0x80;
            buffer[ RTC6_MINUTES_BYTE ] |= foramt_to_bcd( time->minutes );

            buffer[ RTC6_HOUR_BYTE ] =  buffer[ RTC6_HOUR_BYTE ] & 0xC0;
            buffer[ RTC6_HOUR_BYTE ] |= foramt_to_bcd( time->hours );

            buffer[ RTC6_DAY_BYTE ] =  buffer[ RTC6_DAY_BYTE ] & 0xF8;
            buffer[ RTC6_DAY_BYTE ] |= foramt_to_bcd( time->weekdays );
                
            buffer[ RTC6_DATE_BYTE ] =  buffer[ RTC6_DATE_BYTE ] & 0xC0;
            buffer[ RTC6_DATE_BYTE ] |= foramt_to_bcd( time->monthday );
                
            buffer[ RTC6_MONTH_BYTE ] = buffer[ RTC6_MONTH_BYTE ] & 0xE0;
            buffer[ RTC6_MONTH_BYTE ] |= foramt_to_bcd( time->month );
            
            rtc6_generic_write( ctx, RTC6_REG_ALARM0_SECOND, buffer, 6 );
            rtc6_generic_read( ctx, RTC6_REG_ALARM0_DAY, &temp, 1 );
            
            trigger_switch( trigger, &temp );

            temp |= 0x80;
            rtc6_generic_write( ctx, RTC6_REG_ALARM0_DAY, &temp, 1 );
            
            rtc6_generic_read( ctx, RTC6_REG_DAY, &temp, 1 );
            temp |= 0x08;
            rtc6_generic_write( ctx, RTC6_REG_DAY, &temp, 1 );

            rtc6_generic_read( ctx, RTC6_REG_CONTROL, &temp, 1 );
            temp &= 0x3F;
            temp |= 0x10;
            rtc6_generic_write( ctx, RTC6_REG_CONTROL, &temp, 1 );

            break;
        }
        case RTC6_ALARM_1:
        {
            rtc6_generic_read( ctx, RTC6_REG_ALARM1_SECOND, buffer, 6 );
            
            buffer[ RTC6_SECONDS_BYTE ] = buffer[ RTC6_SECONDS_BYTE ] & 0x80;
            buffer[ RTC6_SECONDS_BYTE ] |= foramt_to_bcd( time->seconds );
                  
            buffer[ RTC6_MINUTES_BYTE ] = buffer[ RTC6_MINUTES_BYTE ] & 0x80;
            buffer[ RTC6_MINUTES_BYTE ] |= foramt_to_bcd( time->minutes );
                 
            buffer[ RTC6_HOUR_BYTE ] = buffer[ RTC6_HOUR_BYTE ] & 0xC0;
            buffer[ RTC6_HOUR_BYTE ] |= foramt_to_bcd( time->hours );
                 
            buffer[ RTC6_DAY_BYTE ] = buffer[ RTC6_DAY_BYTE ] & 0xF8;
            buffer[ RTC6_DAY_BYTE ] |= foramt_to_bcd( time->weekdays );
                 
            buffer[ RTC6_DATE_BYTE ] = buffer[ RTC6_DATE_BYTE ] & 0xC0;
            buffer[ RTC6_DATE_BYTE ] |= foramt_to_bcd( time->monthday );
                 
            buffer[ RTC6_MONTH_BYTE ] = buffer[ RTC6_MONTH_BYTE ] & 0xE0;
            buffer[ RTC6_MONTH_BYTE ] |= foramt_to_bcd( time->month );
            
            rtc6_generic_write( ctx, RTC6_REG_ALARM1_SECOND, buffer, 6 );
            rtc6_generic_read( ctx, RTC6_REG_ALARM1_DAY, &temp, 1 );
            
            trigger_switch( trigger, &temp );

            temp |= 0x80;
            rtc6_generic_write( ctx, RTC6_REG_ALARM1_DAY, &temp, 1 );

            rtc6_generic_read( ctx, RTC6_REG_DAY, &temp, 1 );
            temp |= 0x08;
            rtc6_generic_write( ctx, RTC6_REG_DAY, &temp, 1 );

            rtc6_generic_read( ctx, RTC6_REG_CONTROL, &temp, 1 );
            temp &= 0xBF;
            temp |= 0x20;
            rtc6_generic_write( ctx, RTC6_REG_CONTROL, &temp, 1 );

            break;
        }
    }
}

void rtc6_disable_alarm ( rtc6_t *ctx, uint8_t alarm )
{
    uint8_t temp;

    rtc6_generic_read( ctx, RTC6_REG_CONTROL, &temp, 1 );

    switch ( alarm )
    {
        case RTC6_ALARM_0:
        {
            temp &= 0x2F;
            rtc6_generic_write( ctx, RTC6_REG_CONTROL, &temp, 1 );

            break;
        }
        case RTC6_ALARM_1:
        {
            temp &= 0x2F;
            rtc6_generic_write( ctx, RTC6_REG_CONTROL, &temp, 1 );

            break;
        }
    }
}

void rtc6_read_alarm ( rtc6_t *ctx, uint8_t alarm, rtc6_time_t *get_alarm )
{
    uint8_t buffer[ 6 ];
    
    if ( alarm == RTC6_ALARM_0 )
    {
        rtc6_generic_read( ctx, 0x0A, buffer, 6 );
    }
    else
    {
        rtc6_generic_read( ctx, 0x11, buffer, 6 );
    }

    get_alarm->seconds  = format_to_bin( buffer[ RTC6_SECONDS_BYTE ] & 0x7F );
    get_alarm->minutes  = format_to_bin( buffer[ RTC6_MINUTES_BYTE ] & 0x7F );
    get_alarm->hours    = format_to_bin( buffer[ RTC6_HOUR_BYTE ]    & 0x3F );
    get_alarm->weekdays = format_to_bin( buffer[ RTC6_DAY_BYTE ]     & 0x07 );
    get_alarm->monthday = format_to_bin( buffer[ RTC6_DATE_BYTE ]    & 0x3F );
    get_alarm->month    = format_to_bin( buffer[ RTC6_MONTH_BYTE ]   & 0x1F );
}

void rtc6_repeat_alarm ( rtc6_t *ctx, uint8_t alarm, uint32_t sec )
{
    volatile uint32_t unix_time;
    volatile rtc6_time_t new_time;
    
    unix_time = rtc6_get_gmt_unix_time( ctx );
    unix_time += sec;
    time_epoch_to_date( unix_time, &new_time );
    rtc6_set_alarm( ctx, alarm, RTC6_REG_ALARM0_SECOND , &new_time );
}

uint8_t rtc6_is_active_alarm( rtc6_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}
// --------------------------- SRAM

void rtc6_write_sram ( rtc6_t *ctx, uint8_t addr, uint8_t data_in )
{
    if ( ( addr + RTC6_RAM_START ) < RTC6_RAM_END )
    {
        ctx->slave_address = RTC6_SRAM_SLAVE_ADDR;

        rtc6_generic_write( ctx, ( RTC6_RAM_START + addr ), &data_in, 1 );

        ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
    }
}

uint8_t rtc6_read_sram ( rtc6_t *ctx, uint8_t addr )
{
    uint8_t temp = 0;
    
    if ( ( addr + RTC6_RAM_START ) < RTC6_RAM_END )
    {
        ctx->slave_address = RTC6_SRAM_SLAVE_ADDR;

        rtc6_generic_read( ctx, ( RTC6_RAM_START + addr ), &temp, 1 );

        ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
    }

    return temp;
}


void rtc6_write_eeprom_protect_on ( rtc6_t *ctx )
{
    uint8_t temp;
    
    ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;

    rtc6_generic_read( ctx, 0xff, &temp, 1 );

    temp |= ( 1 << 3 ) | ( 1 << 2 );

    rtc6_generic_write( ctx, 0xff, &temp, 1 );

    ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
}

void rtc6_write_eeprom_protect_off ( rtc6_t *ctx )
{
    uint8_t temp;
    
    ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;

    rtc6_generic_read( ctx, 0xff, &temp, 1 );

    temp &= ~( 1 << 3 ) | ( 1 << 2 );

    rtc6_generic_write( ctx, 0xff, &temp, 1 );
    
    ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
}

uint8_t rtc6_eeprom_is_locked ( rtc6_t *ctx )
{
    uint8_t temp;
    
    ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;

    rtc6_generic_read( ctx, 0xff, &temp, 1 );

    ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
    
    if ( ( temp & 0x0C ) != 0 )
    {
        return 0;
    }

    return 1;
}

void rtc6_write_eeprom ( rtc6_t *ctx, uint8_t addr, uint8_t *data_in, uint8_t data_size )
{
    uint8_t i;
    uint8_t count;
    uint8_t rem;
    uint8_t temp;
            
    if ( ( addr >= RTC6_EEPROM_START ) && ( addr + data_size ) < RTC6_EEPROM_END )
    {

        ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;
                
        if ( data_size <= RTC6_EEPROM_PAGE_SIZE )
        {
            rtc6_generic_write( ctx, addr, data_in, data_size );
        }
        else 
        {
            count = data_size / RTC6_EEPROM_PAGE_SIZE;
            rem = data_size % RTC6_EEPROM_PAGE_SIZE;
                    
            for ( i = 0; i < count; i++ )
            {
                temp = *data_in + ( i * 8 );
                rtc6_generic_write( ctx, ( addr + ( i * 8 ) ), &temp , RTC6_EEPROM_PAGE_SIZE );
            }

            if( rem != 0 )
            {
                temp = *data_in + ( i * 8 );
                rtc6_generic_write ( ctx, ( addr + ( count * 8 ) ), &temp, rem );
            }
        }

        ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;

    }
}


void rtc6_read_eeprom ( rtc6_t *ctx, uint8_t addr, uint8_t *data_out, uint8_t data_size )
{
    if ( ( data_size < RTC6_EEPROM_SIZE ) && ( ( addr + data_size ) < RTC6_EEPROM_END ) && ( addr >= RTC6_EEPROM_START ) )
    {
        ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;

        rtc6_generic_read( ctx, addr, data_out, data_size );

        ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
    }
}

void rtc6_read_unique_id ( rtc6_t *ctx, uint8_t *unique_id )
{
    ctx->slave_address = RTC6_EEPROM_SLAVE_ADDR;

    rtc6_generic_read( ctx, 0xF0, unique_id, 8 );

    ctx->slave_address = RTC6_DEVICE_SLAVE_ADDR;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static uint16_t format_to_bin ( uint16_t value )
{
    uint16_t calc;
    
    calc = value & 0x0F;
    calc = calc + ( value / 16 ) * 10;
    
    return calc;
}

static uint16_t foramt_to_bcd ( uint16_t value )
{
    uint16_t calc;
    
    calc = ( value / 10 ) * 16;
    calc = calc + ( value % 10 );
    
    return calc;
}

static void time_epoch_to_date ( int32_t e, rtc6_time_t *time_seg )
{
    uint32_t epoch = e;
    uint16_t current_day;
    uint8_t cnt_month;

    time_seg->year = (uint8_t)( epoch / 31557600 ) - 30;
    time_seg->month = (uint8_t)( ( epoch / 2629743 ) - ( ( time_seg->year + 30 ) * 12 ) ) + 1;
    current_day = ( epoch / 86400 ) - ( ( time_seg->year + 30 ) * 365 ) - ( ( time_seg->year + 30 ) / 4 );
    
    for ( cnt_month = 0; cnt_month < ( time_seg->month - 1 ); cnt_month++ )
    {
        if ( ( cnt_month == RTC6_MONTH_JANUARY ) || ( cnt_month == RTC6_MONTH_MARCH ) ||
             ( cnt_month == RTC6_MONTH_MAY ) || ( cnt_month == RTC6_MONTH_JULY ) || 
             ( cnt_month == RTC6_MONTH_AUGUST ) || ( cnt_month == RTC6_MONTH_OCTOBER ) || ( cnt_month == RTC6_MONTH_DECEMBER ) )
        {
            current_day -= 31;
        }
        else if ( ( cnt_month == RTC6_MONTH_APRIL ) || ( cnt_month == RTC6_MONTH_JUNE ) || ( cnt_month == RTC6_MONTH_SEPTEMBER ) || 
                  ( cnt_month == RTC6_MONTH_NOVEMBER ) )
        {
            current_day -= 30;
        }
        else
        {
            if ( ( time_seg->year + 2000 ) % 4 == 0 )
            {
                current_day -= 29;
            }
            else
            {
                current_day -= 28;
            }
        }
    }
    time_seg->monthday = ( uint8_t )current_day + 1;
    time_seg->seconds = ( uint8_t )( epoch % 60 );
    epoch /= 60;
    time_seg->minutes = ( uint8_t )( epoch % 60 );
    epoch /= 60;
    time_seg->hours = ( uint8_t )( epoch % 24 );

}

static uint32_t time_date_to_epoch ( rtc6_time_t *time_seg )
{
    uint32_t utime;
    uint8_t current_year;
    uint8_t current_month;
    uint8_t cnt_month;

    current_year = time_seg->year + 30;
    utime = current_year * ( uint32_t )TIME_SEC_IN_YEAR_365;
    utime += ( current_year / 4 ) * ( uint32_t )TIME_SEC_IN_DAY;
    
    current_month = time_seg->month - 1;
    for ( cnt_month = 0; cnt_month < current_month; cnt_month++ )
    {
        if ( ( cnt_month == RTC6_MONTH_JANUARY ) || ( cnt_month == RTC6_MONTH_MARCH ) || ( cnt_month == RTC6_MONTH_MAY ) || 
             ( cnt_month == RTC6_MONTH_JULY ) || ( cnt_month == RTC6_MONTH_AUGUST ) || ( cnt_month == RTC6_MONTH_OCTOBER ) || 
             ( cnt_month == RTC6_MONTH_DECEMBER ) )
        {
            utime += ( uint32_t )2678400;
        }
        else if ( ( cnt_month == RTC6_MONTH_APRIL ) || ( cnt_month == RTC6_MONTH_JUNE ) || ( cnt_month == RTC6_MONTH_SEPTEMBER ) || 
                  ( cnt_month == RTC6_MONTH_NOVEMBER ) )
        {
            utime += ( uint32_t )2592000;
        }
        else
        {
            if ( ( current_year + 1970 ) % 4 == 0 )
            {
                utime += ( uint32_t )2505600;
            }
            else
            {
                utime += ( uint32_t )2419200;
            }
        }
    }
    
    utime += ( time_seg->monthday - 1 ) *( uint32_t )TIME_SEC_IN_DAY;
    utime += ( uint32_t )( time_seg->hours ) * TIME_SEC_IN_HOUR;
    utime += ( uint32_t )( time_seg->minutes ) * TIME_SEC_IN_MIN;
    utime += ( uint32_t )time_seg->seconds;
    
    return utime;
}

static void trigger_switch ( uint8_t trigger, uint8_t *temp )
{
    switch ( trigger )
            {
                case RTC6_REG_ALARM0_SECOND:
                {
                    *temp &= 0x87;
                    break;
                }
                case RTC6_REG_ALARM0_MINUTE:
                {
                    *temp &= 0x87;
                    *temp |= 0x10;
                    break;
                }
                case RTC6_REG_ALARM0_HOUR:
                {
                    *temp &= 0x87;
                    *temp |= 0x20;
                    break;
                }
                case RTC6_REG_ALARM0_DAY:
                {
                    *temp &= 0x87;
                    *temp |= 0x30;
                    break;
                }
                case RTC6_REG_ALARM0_DATE:
                {
                    *temp &= 0x87;
                    *temp |= 0x40;
                    break;
                }
                case RTC6_REG_ALARM0_MONTH:
                {
                    *temp &= 0x87;
                    *temp |= 0x78;
                }
                default:
                {
                    break;
                }
            }
}
// ------------------------------------------------------------------------- END

