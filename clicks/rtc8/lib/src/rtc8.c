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

#include "rtc8.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static uint8_t bcd_to_dec ( uint8_t bcdnum );
static uint8_t dec_to_bcd ( uint8_t decnum );
static uint8_t invalid_data ( uint8_t reg, uint8_t _data );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc8_cfg_setup ( rtc8_cfg_t *cfg )
{
    // Communication gpio pins 

    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins

    cfg->evi   = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x52;
}

RTC8_RETVAL rtc8_init ( rtc8_t *ctx, rtc8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( i2c_master_open( &ctx->i2c, &i2c_cfg ) == I2C_MASTER_ERROR )
    {
        return RTC8_INIT_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 

    digital_out_init( &ctx->evi, cfg->evi );

    // Input pins

    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC8_OK;
}

void rtc8_default_cfg ( rtc8_t *ctx )
{
    uint8_t tmp;

    // Click default configuration

    Delay_100ms();

    // Status register

    rtc8_set_external_event_input( ctx, 1 );
    tmp = RTC8_STATUS_REG_CLEAR;

    rtc8_generic_write( ctx, RTC8_REG_STATUS, &tmp, 1 );

    // CTRL 1 register

    tmp = RTC8_CTRL1_TRPT_SINGLE_MODE | RTC8_CTRL1_WADA_WEEKDAY_ALARM |
          RTC8_CTRL1_USEL_SECOND_UPDATE | RTC8_CTRL1_EERD_REFRESH_ACTIVE |
          RTC8_CTRL1_TE_TIMER_STOPS | RTC8_CTRL1_TD_TIMER_CLK_4096Hz;

    rtc8_generic_write( ctx, RTC8_REG_CONTROL1, &tmp, 1 );

    // CTRL 2 register

    tmp = RTC8_CTRL2_TIME_STAMP_ENABLE | RTC8_CTRL2_INT_CLOCK_DISABLE |
          RTC8_CTRL2_TIME_UPDATE_NO_INTERRUPT | RTC8_CTRL2_TIMER_NO_INTERRUPT |
          RTC8_CTRL2_ALARM_INTERRUPT | RTC8_CTRL2_EVENT_NO_INTERRUPT |
          RTC8_CTRL2_HOUR_MODE_24;

    rtc8_generic_write( ctx, RTC8_REG_CONTROL2, &tmp, 1 );

    // EPPROM BACKUP

    tmp = 0x0C;
    rtc8_generic_write( ctx, RTC8_REG_EEPROM_BACKUP, &tmp, 1 );

    rtc8_reset_alarm_flag( ctx );
}

void  rtc8_generic_write ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
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

void rtc8_generic_read ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

uint8_t rtc8_write_data_bcd_format ( rtc8_t *ctx, uint8_t reg, uint8_t _data )
{
    uint8_t tx_data;
    uint8_t error;

    error = invalid_data ( reg, _data );
    if ( error == 1 )
    {
        return 1;
    }

    tx_data = dec_to_bcd( _data );

    rtc8_generic_write( ctx, reg,  &tx_data, 1 );

    return 0;
}

uint8_t rtc8_read_data_bcd_format ( rtc8_t *ctx, uint8_t reg )
{
    uint8_t bcd_data;
    uint8_t data_out;

    rtc8_generic_read( ctx, reg, &bcd_data, 1);
    data_out = bcd_to_dec( bcd_data );

    return data_out;
}

uint32_t rtc8_get_uinx_time ( rtc8_t *ctx )
{
    uint32_t time_stamp = 0;
    uint8_t rx_data[ 4 ];

    rtc8_generic_read( ctx, RTC8_REG_UNIX0, rx_data, 4 );

    time_stamp = rx_data[ 3 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 2 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 1 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 0 ];

    return time_stamp;
}

void rtc8_set_unix_time ( rtc8_t *ctx, int32_t unix_time )
{
    uint8_t tmp;

    tmp = ( uint8_t )( unix_time & 0x000000ff );
    rtc8_generic_write( ctx, RTC8_REG_UNIX0, &tmp, 1 );

    tmp = ( uint8_t )( ( unix_time & 0x0000ff00 ) >> 8 );
    rtc8_generic_write( ctx, RTC8_REG_UNIX1, &tmp, 1 );

    tmp = ( uint8_t )( ( unix_time & 0x00ff0000 ) >> 16 );
    rtc8_generic_write( ctx, RTC8_REG_UNIX2, &tmp, 1 );

    tmp = ( uint8_t )( ( unix_time & 0xff000000 ) >> 24 );
    rtc8_generic_write( ctx, RTC8_REG_UNIX3, &tmp, 1 );
}


uint8_t rtc8_set_time ( rtc8_t *ctx, rtc8_time_t *time_s )
{
   uint8_t error = 0;

   error = rtc8_write_data_bcd_format( ctx, RTC8_REG_HOURS, time_s->hours );
   error <<= 1;
   error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_MINUTES, time_s->minutes );
   error <<= 1;
   error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_SECONDS, time_s->seconds );

   return error;
}

uint8_t rtc8_set_date ( rtc8_t *ctx, rtc8_date_t *date_s )
{
    uint8_t error = 0;

    error = rtc8_write_data_bcd_format( ctx, RTC8_REG_DATE, date_s->day );
    error <<= 1;
    error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_MONTH, date_s->month );
    error <<= 1;
    error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_YEAR, date_s->year );

    return error;
}

uint8_t rtc8_set_alarm ( rtc8_t *ctx, rtc8_alarm_t *alarm_s )
{
    uint8_t error;

    error = rtc8_write_data_bcd_format( ctx, RTC8_REG_WEEKDAY_ALARM, alarm_s->weekdays );
    error <<= 1;
    error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_HOURS_ALARM, alarm_s->hours );
    error <<= 1;
    error |= rtc8_write_data_bcd_format( ctx, RTC8_REG_MINUTES_ALARM, alarm_s->minutes );

    return error;
}

uint8_t rtc8_get_interrupt_state ( rtc8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void rtc8_set_external_event_input ( rtc8_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->evi, state );
}

void rtx8_get_time_and_date ( rtc8_t *ctx, rtc8_time_t *time_s, rtc8_date_t *date_s )
{
    // Time

    time_s->seconds = rtc8_read_data_bcd_format( ctx, RTC8_REG_SECONDS );
    time_s->minutes = rtc8_read_data_bcd_format( ctx, RTC8_REG_MINUTES );
    time_s->hours = rtc8_read_data_bcd_format( ctx, RTC8_REG_HOURS );

    // Date

    date_s->weekdays = rtc8_read_data_bcd_format( ctx, RTC8_REG_WEEKDAY );
    date_s->day = rtc8_read_data_bcd_format( ctx, RTC8_REG_DATE );
    date_s->month = rtc8_read_data_bcd_format( ctx, RTC8_REG_MONTH );
    date_s->year = rtc8_read_data_bcd_format( ctx, RTC8_REG_YEAR );
}

void rtc8_reset_alarm_flag ( rtc8_t *ctx )
{
    uint8_t tmp;

    tmp = RTC8_STATUS_REG_CLEAR;

    rtc8_generic_write( ctx, RTC8_REG_STATUS, &tmp, 1 );
}

uint8_t rtc8_get_status ( rtc8_t *ctx )
{
    uint8_t status;

    status = rtc8_read_data_bcd_format( ctx, RTC8_REG_STATUS );

    return status;
}

uint8_t rtc8_get_alarm_flag ( rtc8_t *ctx )
{
    uint8_t status;

    status = rtc8_get_status( ctx );
    if ( ( ( status & RTC8_STATUS_ALARM_FLAG ) / 4 ) != 0 )
    {
       return RTC8_ALARM_IS_ACTIVE;
    }

    return RTC8_ALARM_NO_ACTIVE;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS


static uint8_t bcd_to_dec ( uint8_t bcd_num )
{
    uint8_t tmp = 0;

    tmp = ( bcd_num >> 4 ) * 10;
    tmp += ( bcd_num & 0x0F );

    return tmp;
}

static uint8_t dec_to_bcd ( uint8_t dec_num )
{
    uint8_t tmp = 0;

    if ( dec_num > 9 )
    {
        tmp = dec_num / 10;
        tmp <<= 4;
        tmp |= ( dec_num % 10 );
    }
    else
    {
        tmp = dec_num;
    }

    return tmp;
}

static uint8_t invalid_data ( uint8_t reg, uint8_t _data )
{
    uint8_t error = 0;

    switch( reg )
    {
        case 0: // Seconds
        {
            if ( _data > 59 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 1: // Minute
        {
            if ( _data > 59 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 2: // Hours
        {
            if ( _data > 23 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 3: // weekday
        {
            if ( _data > 6 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 4: // Date
        {
            if ( _data > 31 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 5: // Month
        {
            if ( _data > 12 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 6: // year
        {
            if ( _data > 99 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 7: // Alarm minute
        {
            if ( _data > 59 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 8: // Alarm hours
        {
            if ( _data > 23 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        case 9: // Alarm weekday
        {
            if ( _data > 6 )
            {
                error = 1;
            }
            else
            {
                error = 0;
            }
            break;
        }
        default:
        {
            error = 1;
            break;
        }
    }
    return error;
}
// ------------------------------------------------------------------------- END

