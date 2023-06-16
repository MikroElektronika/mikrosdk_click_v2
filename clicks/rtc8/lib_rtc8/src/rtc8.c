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
#include "conversions.h"

// ---------------------------------------------- PRIVATE FUNCTION DECLARATIONS 

static err_t rtc8_check_parameters ( uint8_t reg, uint8_t data_in );

// ------------------------------------------------ PUBLIC FUNCTION DEFINITIONS

void rtc8_cfg_setup ( rtc8_cfg_t *cfg )
{
    // Communication gpio pins 
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;
    
    // Additional gpio pins
    cfg->evi = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed = I2C_MASTER_SPEED_STANDARD; 
    cfg->i2c_address = 0x52;
}

err_t rtc8_init ( rtc8_t *ctx, rtc8_cfg_t *cfg )
{
    i2c_master_config_t i2c_cfg;

    i2c_master_configure_default( &i2c_cfg );
    i2c_cfg.speed  = cfg->i2c_speed;
    i2c_cfg.scl    = cfg->scl;
    i2c_cfg.sda    = cfg->sda;

    ctx->slave_address = cfg->i2c_address;

    if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) )
    {
        return RTC8_ERROR;
    }

    i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address );
    i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed );

    // Output pins 
    digital_out_init( &ctx->evi, cfg->evi );

    // Input pins
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return RTC8_OK;
}

err_t rtc8_default_cfg ( rtc8_t *ctx )
{
    err_t error_flag = RTC8_OK;
    uint8_t tmp = 0;

    // Click default configuration
    Delay_100ms( );

    // Status register
    rtc8_set_evi_pin( ctx, 1 );
    tmp = RTC8_STATUS_REG_CLEAR;

    error_flag |= rtc8_generic_write( ctx, RTC8_REG_STATUS, &tmp, 1 );

    // CTRL 1 register
    tmp = RTC8_CTRL1_TRPT_SINGLE_MODE | RTC8_CTRL1_WADA_WEEKDAY_ALARM |
          RTC8_CTRL1_USEL_SECOND_UPDATE | RTC8_CTRL1_EERD_REFRESH_ACTIVE |
          RTC8_CTRL1_TE_TIMER_STOPS | RTC8_CTRL1_TD_TIMER_CLK_4096Hz;

    error_flag |= rtc8_generic_write( ctx, RTC8_REG_CONTROL1, &tmp, 1 );

    // CTRL 2 register
    tmp = RTC8_CTRL2_TIME_STAMP_ENABLE | RTC8_CTRL2_INT_CLOCK_DISABLE |
          RTC8_CTRL2_TIME_UPDATE_NO_INTERRUPT | RTC8_CTRL2_TIMER_NO_INTERRUPT |
          RTC8_CTRL2_ALARM_INTERRUPT | RTC8_CTRL2_EVENT_NO_INTERRUPT |
          RTC8_CTRL2_HOUR_MODE_24;

    error_flag |= rtc8_generic_write( ctx, RTC8_REG_CONTROL2, &tmp, 1 );

    // EEPROM BACKUP
    tmp = 0x0C;
    error_flag |= rtc8_generic_write( ctx, RTC8_REG_EEPROM_BACKUP, &tmp, 1 );

    error_flag |= rtc8_reset_alarm_flag( ctx );
    return error_flag;
}

err_t rtc8_generic_write ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    uint8_t tx_buf[ 256 ] = { 0 };
    tx_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        tx_buf[ cnt + 1 ] = data_buf[ cnt ]; 
    }
    return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
}

err_t rtc8_generic_read ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len )
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_buf, len );
}

err_t rtc8_write_data ( rtc8_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_data = 0;

    if ( RTC8_ERROR == rtc8_check_parameters ( reg, data_in ) )
    {
        return RTC8_ERROR;
    }

    tx_data = dec_to_bcd ( data_in );

    return rtc8_generic_write( ctx, reg,  &tx_data, 1 );
}

err_t rtc8_read_data ( rtc8_t *ctx, uint8_t reg, uint8_t *data_out )
{
    uint8_t bcd_data = 0;

    err_t error_flag = rtc8_generic_read( ctx, reg, &bcd_data, 1);
    *data_out = bcd_to_dec( bcd_data );

    return error_flag;
}

err_t rtc8_get_uinx_time ( rtc8_t *ctx, uint32_t *unix_time )
{
    uint32_t time_stamp = 0;
    uint8_t rx_data[ 4 ];

    err_t error_flag = rtc8_generic_read( ctx, RTC8_REG_UNIX0, rx_data, 4 );

    time_stamp = rx_data[ 3 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 2 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 1 ];
    time_stamp <<= 8;
    time_stamp |= rx_data[ 0 ];
    
    *unix_time = time_stamp;

    return error_flag;
}

err_t rtc8_set_unix_time ( rtc8_t *ctx, uint32_t unix_time )
{
    err_t error_flag = RTC8_OK;
    uint8_t tmp = 0;

    tmp = ( uint8_t ) ( unix_time & 0xFF );
    error_flag |= rtc8_generic_write( ctx, RTC8_REG_UNIX0, &tmp, 1 );

    tmp = ( uint8_t ) ( ( unix_time >> 8 ) & 0xFF );
    error_flag |= rtc8_generic_write( ctx, RTC8_REG_UNIX1, &tmp, 1 );

    tmp = ( uint8_t ) ( ( unix_time >> 16 ) & 0xFF );
    error_flag |= rtc8_generic_write( ctx, RTC8_REG_UNIX2, &tmp, 1 );

    tmp = ( uint8_t ) ( ( unix_time >> 24 ) & 0xFF );
    error_flag |= rtc8_generic_write( ctx, RTC8_REG_UNIX3, &tmp, 1 );
    
    return error_flag;
}

err_t rtc8_set_time ( rtc8_t *ctx, rtc8_time_t *time_s )
{
   err_t error_flag = RTC8_OK;

   error_flag |= rtc8_write_data( ctx, RTC8_REG_HOURS, time_s->hours );
   error_flag |= rtc8_write_data( ctx, RTC8_REG_MINUTES, time_s->minutes );
   error_flag |= rtc8_write_data( ctx, RTC8_REG_SECONDS, time_s->seconds );

   return error_flag;
}

err_t rtc8_set_date ( rtc8_t *ctx, rtc8_date_t *date_s )
{
    err_t error_flag = RTC8_OK;

    error_flag |= rtc8_write_data( ctx, RTC8_REG_WEEKDAY, date_s->weekdays );
    error_flag = rtc8_write_data( ctx, RTC8_REG_DATE, date_s->day );
    error_flag |= rtc8_write_data( ctx, RTC8_REG_MONTH, date_s->month );
    error_flag |= rtc8_write_data( ctx, RTC8_REG_YEAR, date_s->year );

    return error_flag;
}

err_t rtc8_set_alarm ( rtc8_t *ctx, rtc8_alarm_t *alarm_s )
{
    err_t error_flag = RTC8_OK;

    error_flag |= rtc8_write_data( ctx, RTC8_REG_WEEKDAY_ALARM, alarm_s->weekdays );
    error_flag |= rtc8_write_data( ctx, RTC8_REG_HOURS_ALARM, alarm_s->hours );
    error_flag |= rtc8_write_data( ctx, RTC8_REG_MINUTES_ALARM, alarm_s->minutes );

    return error_flag;
}

uint8_t rtc8_get_int_pin ( rtc8_t *ctx )
{
    return digital_in_read( &ctx->int_pin );
}

void rtc8_set_evi_pin ( rtc8_t *ctx, uint8_t state )
{
    digital_out_write( &ctx->evi, state );
}

err_t rtx8_get_time_and_date ( rtc8_t *ctx, rtc8_time_t *time_s, rtc8_date_t *date_s )
{
    err_t error_flag = RTC8_OK;
    // Time
    error_flag |= rtc8_read_data( ctx, RTC8_REG_SECONDS, &time_s->seconds );
    error_flag |= rtc8_read_data( ctx, RTC8_REG_MINUTES, &time_s->minutes );
    error_flag |= rtc8_read_data( ctx, RTC8_REG_HOURS, &time_s->hours );
    // Date
    error_flag |= rtc8_read_data( ctx, RTC8_REG_WEEKDAY, &date_s->weekdays );
    error_flag |= rtc8_read_data( ctx, RTC8_REG_DATE, &date_s->day );
    error_flag |= rtc8_read_data( ctx, RTC8_REG_MONTH, &date_s->month );
    error_flag |= rtc8_read_data( ctx, RTC8_REG_YEAR, &date_s->year );
    return error_flag;
}

err_t rtc8_reset_alarm_flag ( rtc8_t *ctx )
{
    uint8_t tmp = RTC8_STATUS_REG_CLEAR;
    return rtc8_generic_write( ctx, RTC8_REG_STATUS, &tmp, 1 );
}

err_t rtc8_get_status ( rtc8_t *ctx, uint8_t *status )
{
    return rtc8_read_data( ctx, RTC8_REG_STATUS, status );
}

err_t rtc8_get_alarm_flag ( rtc8_t *ctx, uint8_t *alarm_flag )
{
    uint8_t status = 0;

    err_t error_flag = rtc8_get_status( ctx, &status );
    if ( ( status & RTC8_STATUS_ALARM_FLAG ) / 4 )
    {
        *alarm_flag = RTC8_ALARM_IS_ACTIVE;
    }
    else
    {
        *alarm_flag = RTC8_ALARM_NO_ACTIVE;
    }
    return error_flag;
}

// ----------------------------------------------- PRIVATE FUNCTION DEFINITIONS

static err_t rtc8_check_parameters ( uint8_t reg, uint8_t data_in )
{
    err_t error_flag = RTC8_OK;
    switch ( reg )
    {
        case RTC8_REG_SECONDS:
        case RTC8_REG_MINUTES:
        case RTC8_REG_MINUTES_ALARM:
        {
            if ( data_in > 59 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        case RTC8_REG_HOURS:
        case RTC8_REG_HOURS_ALARM:
        {
            if ( data_in > 23 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        case RTC8_REG_WEEKDAY:
        case RTC8_REG_WEEKDAY_ALARM:
        {
            if ( data_in > 6 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        case RTC8_REG_DATE:
        {
            if ( data_in > 31 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        case RTC8_REG_MONTH:
        {
            if ( data_in > 12 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        case RTC8_REG_YEAR:
        {
            if ( data_in > 99 )
            {
                error_flag = RTC8_ERROR;
            }
            break;
        }
        default:
        {
            error_flag = RTC8_ERROR;
            break;
        }
    }
    return error_flag;
}
// ------------------------------------------------------------------------- END

