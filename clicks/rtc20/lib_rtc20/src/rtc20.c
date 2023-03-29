/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file rtc20.c
 * @brief RTC 20 Click Driver.
 */

#include "rtc20.h"
#include "conversions.h"

/**
 * @brief RTC limit values data.
 * @details Definition of RTC limit values data.
 */
#define MAX_HSEC                     99
#define MAX_MINU_SEC                 59
#define MAX_HOUR                     23
#define MAX_DAY                      31
#define MAX_MONTH                    12
#define ZERO_VALUE                    0

void rtc20_cfg_setup ( rtc20_cfg_t *cfg ) 
{
    // Communication gpio pins
    cfg->scl = HAL_PIN_NC;
    cfg->sda = HAL_PIN_NC;

    // Additional gpio pins
    cfg->ir2 = HAL_PIN_NC;
    cfg->wdi = HAL_PIN_NC;
    cfg->ext = HAL_PIN_NC;
    cfg->ir1 = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC20_DEVICE_ADDRESS;
}

err_t rtc20_init ( rtc20_t *ctx, rtc20_cfg_t *cfg ) 
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

    digital_out_init( &ctx->wdi, cfg->wdi );
    digital_out_init( &ctx->ext, cfg->ext );

    digital_in_init( &ctx->ir2, cfg->ir2 );
    digital_in_init( &ctx->ir1, cfg->ir1 );

    digital_out_high( &ctx->wdi );
    digital_out_high( &ctx->ext );

    return I2C_MASTER_SUCCESS;
}

err_t rtc20_generic_write ( rtc20_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len ) 
{
    uint8_t data_buf[ 256 ] = { 0 };
    data_buf[ 0 ] = reg;
    for ( uint8_t cnt = 0; cnt < len; cnt++ )
    {
        data_buf[ cnt + 1 ] = data_in[ cnt ];
    }
    return i2c_master_write( &ctx->i2c, data_buf, len + 1 );
}

err_t rtc20_generic_read ( rtc20_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, data_out, len );
}

void rtc20_wdi_pin_state ( rtc20_t *ctx, uint8_t pin_state ) 
{
    digital_out_write( &ctx->wdi, pin_state );
}

void rtc20_ext_pin_state ( rtc20_t *ctx, uint8_t pin_state ) 
{
    digital_out_write( &ctx->ext, pin_state );
}

err_t rtc20_set_time ( rtc20_t *ctx, rtc20_time_t rtc_time )
{
    err_t err_flag;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( rtc_time.hundredths > MAX_HSEC ) || 
        ( rtc_time.second > MAX_MINU_SEC ) || 
        ( rtc_time.minute > MAX_MINU_SEC ) || 
        ( rtc_time.hour > MAX_HOUR ) ) 
    {
        err_flag = RTC20_ERROR;
    }
    else
    {
        data_buf[ 0 ] = dec_to_bcd( rtc_time.hundredths );
        data_buf[ 1 ] = dec_to_bcd( rtc_time.second );
        data_buf[ 2 ] = dec_to_bcd( rtc_time.minute );
        data_buf[ 3 ] = dec_to_bcd( rtc_time.hour );    
        err_flag = rtc20_generic_write( ctx, RTC20_REG_HUNDREDTHS, data_buf, 4 );
    }
    return err_flag;
}

err_t rtc20_get_time ( rtc20_t *ctx, rtc20_time_t *rtc_time )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = rtc20_generic_read( ctx, RTC20_REG_HUNDREDTHS, data_buf, 4 );
    rtc_time->hundredths = bcd_to_dec( data_buf[ 0 ] );
    rtc_time->second = bcd_to_dec( data_buf[ 1 ] );
    rtc_time->minute = bcd_to_dec( data_buf[ 2 ] );
    rtc_time->hour = bcd_to_dec( data_buf[ 3 ] );
    return err_flag;
}

err_t rtc20_set_date ( rtc20_t *ctx, rtc20_date_t rtc_date )
{
    err_t err_flag = RTC20_ERROR; 
    uint8_t max_num_day = 0;
    uint8_t data_buf[ 4 ] = { 0 };
    
    switch ( rtc_date.month ) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
        {
            max_num_day = 31;
            break;
        }
        case 4: case 6: case 9: case 11: 
        {
            max_num_day = 30;
            break;
        }
        case 2: 
        {
            max_num_day = 28;
            break;
        }
    }
    
    if ( rtc_date.year % 4 == 0 ) 
    {
        max_num_day = 29; 
    }
    
    if ( ( rtc_date.day < 1 ) || (  rtc_date.day > max_num_day ) ) 
    {
        err_flag = RTC20_ERROR;    
    } 
    else
    {
        data_buf[ 0 ] = dec_to_bcd( rtc_date.day );
        data_buf[ 1 ] = dec_to_bcd( rtc_date.month );
        data_buf[ 2 ] = dec_to_bcd( rtc_date.year );
        data_buf[ 3 ] = dec_to_bcd( rtc_date.day_of_week );
        err_flag = rtc20_generic_write( ctx, RTC20_REG_DATE, data_buf, 4 );
    }
    
    return err_flag; 
}

err_t rtc20_get_date ( rtc20_t *ctx, rtc20_date_t *rtc_date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = rtc20_generic_read( ctx, RTC20_REG_DATE, data_buf, 4 );
    rtc_date->day = bcd_to_dec( data_buf[ 0 ] );
    rtc_date->month = bcd_to_dec( data_buf[ 1 ] );
    rtc_date->year = bcd_to_dec( data_buf[ 2 ] );
    rtc_date->day_of_week = data_buf[ 3 ];
    return err_flag;
}

err_t rtc20_set_alarm ( rtc20_t *ctx, rtc20_time_t rtc_alarm_time, rtc20_date_t rtc_alarm_date ) 
{
    err_t err_flag = RTC20_OK;
    uint8_t data_buf[ 4 ] = { 0 };
    if ( ( rtc_alarm_time.hundredths > MAX_HSEC ) || ( rtc_alarm_time.hundredths > ZERO_VALUE ) ||
        ( rtc_alarm_time.second > MAX_MINU_SEC ) || ( rtc_alarm_time.second > ZERO_VALUE ) ||
        ( rtc_alarm_time.minute > MAX_MINU_SEC ) || ( rtc_alarm_time.minute > ZERO_VALUE ) ||
        ( rtc_alarm_time.hour > MAX_HOUR ) || ( rtc_alarm_time.hour > ZERO_VALUE ) ||
        ( rtc_alarm_date.day > MAX_DAY ) || ( rtc_alarm_date.month > MAX_MONTH ) || 
        ( rtc_alarm_date.day_of_week > RTC20_DW_SATURDAY ) ) 
    {
        err_flag = RTC20_ERROR;
    }
    else 
    {
        data_buf[ 0 ] = dec_to_bcd( rtc_alarm_time.hundredths );
        data_buf[ 1 ] = dec_to_bcd( rtc_alarm_time.second );
        data_buf[ 2 ] = dec_to_bcd( rtc_alarm_time.minute );
        data_buf[ 3 ] = dec_to_bcd( rtc_alarm_time.hour );    
        err_flag = rtc20_generic_write( ctx, RTC20_REG_HUNDREDTHS, data_buf, 4 );
        
        data_buf[ 0 ] = dec_to_bcd( rtc_alarm_date.day );
        data_buf[ 1 ] = dec_to_bcd( rtc_alarm_date.month );
        data_buf[ 2 ] = dec_to_bcd( rtc_alarm_date.year );
        data_buf[ 3 ] = rtc_alarm_date.day_of_week;
        err_flag |= rtc20_generic_write( ctx, RTC20_REG_DATE, data_buf, 4 );
    }
    return err_flag;
}

err_t rtc20_get_alarm ( rtc20_t *ctx, rtc20_time_t *rtc_alarm_time, rtc20_date_t *rtc_alarm_date )
{
    uint8_t data_buf[ 4 ] = { 0 };
    err_t err_flag = rtc20_generic_read( ctx, RTC20_REG_HUNDREDTHS, data_buf, 4 );
    rtc_alarm_time->hundredths = bcd_to_dec( data_buf[ 0 ] );
    rtc_alarm_time->second = bcd_to_dec( data_buf[ 1 ] );
    rtc_alarm_time->minute = bcd_to_dec( data_buf[ 2 ] );
    rtc_alarm_time->hour = bcd_to_dec( data_buf[ 3 ] );

    err_flag |= rtc20_generic_read( ctx, RTC20_REG_DATE, data_buf, 4 );
    rtc_alarm_date->day = bcd_to_dec( data_buf[ 0 ] );
    rtc_alarm_date->month = bcd_to_dec( data_buf[ 1 ] );
    rtc_alarm_date->year = bcd_to_dec( data_buf[ 2 ] );
    rtc_alarm_date->day_of_week = bcd_to_dec( data_buf[ 3 ] );
    return err_flag;
}

err_t rtc20_get_status ( rtc20_t *ctx, uint8_t *status )
{
    return rtc20_generic_read( ctx, RTC20_REG_STATUS, status, 1 );
}

err_t rtc20_set_ctrl_signals ( rtc20_t *ctx, rtc20_ctrl_signals_t ctrl_signals )
{
    uint8_t data_buf[ 2 ] = { 0 };
    data_buf[ 0 ] =  ( ctrl_signals.stop          & 0x01 ) << 7;
    data_buf[ 0 ] |= ( ctrl_signals.hours_op_mode & 0x01 ) << 6;
    data_buf[ 0 ] |= ( ctrl_signals.outb          & 0x01 ) << 5;
    data_buf[ 0 ] |= ( ctrl_signals.out           & 0x01 ) << 4;
    data_buf[ 0 ] |= ( ctrl_signals.arst          & 0x01 ) << 2;
    data_buf[ 0 ] |=   ctrl_signals.wrtc          & 0x01;
    data_buf[ 1 ] =  ( ctrl_signals.out2s         & 0x07 ) << 2;
    data_buf[ 1 ] |=   ctrl_signals.out1s         & 0x03;
    return rtc20_generic_write( ctx, RTC20_REG_CONTROL1, data_buf, 2 );
}

err_t rtc20_get_ctrl_signals ( rtc20_t *ctx, rtc20_ctrl_signals_t *ctrl_signals )
{
    uint8_t data_buf[ 2 ] = { 0 };
    err_t err_flag = rtc20_generic_read( ctx, RTC20_REG_CONTROL1, data_buf, 2 );
    ctrl_signals->stop          = ( data_buf[ 0 ] >> 7 ) & 0x01;
    ctrl_signals->hours_op_mode = ( data_buf[ 0 ] >> 6 ) & 0x01;
    ctrl_signals->outb          = ( data_buf[ 0 ] >> 5 ) & 0x01;
    ctrl_signals->out           = ( data_buf[ 0 ] >> 4 ) & 0x01; 
    ctrl_signals->arst          = ( data_buf[ 0 ] >> 2 ) & 0x01; 
    ctrl_signals->wrtc          =   data_buf[ 0 ]        & 0x01; 
    ctrl_signals->out2s         = ( data_buf[ 1 ] >> 2 ) & 0x07; 
    ctrl_signals->out1s         =   data_buf[ 1 ]        & 0x03; 
    return err_flag;
}

uint8_t rtc20_get_ir1_pin ( rtc20_t *ctx )
{
    return digital_in_read ( &ctx->ir1 );
}

uint8_t rtc20_get_ir2_pin ( rtc20_t *ctx )
{
    return digital_in_read ( &ctx->ir2 );
}

// ------------------------------------------------------------------------- END
