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
 * @file rtc14.c
 * @brief RTC 14 Click Driver.
 */

#include "rtc14.h"

#define BIT_MASK_LSN               0x0F
#define BIT_MASK_BIT_0             0x01
#define BIT_MASK_TIME_REV_BIT      0x7F
#define BIT_MASK_ALARMS_ENABLE     0x04
#define MAX_MIN_SEC                  59
#define MAX_HOUR                     23
#define MAX_DAY                      31
#define BIT_MASK_ALARM_ENABLE      0x80
#define BIT_MASK_HOURS_FORMAT_12   0x1F
#define BIT_MASK_HOURS_FORMAT_24   0x3F

/**
 * @brief Decimal to RTC.
 * @details Decimal to RTC converter function.
 */
static uint8_t dev_dec_to_rtc ( uint8_t dec );

/**
 * @brief RTC to decimal.
 * @details RTC to decimal converter function.
 */
static uint8_t dev_rtc_to_dec ( uint8_t bcd );

/**
 * @brief RTC configuration and trigger delay function.
 * @details RTC configuration and trigger delay of the 10 milliseconds. 
 */
static void dev_cfg_trg_delay ( void );

void rtc14_cfg_setup ( rtc14_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;

    cfg->fo   = HAL_PIN_NC;
    cfg->ein = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = RTC14_SET_DEV_ADDR;
}

err_t rtc14_init ( rtc14_t *ctx, rtc14_cfg_t *cfg ) 
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

    digital_out_init( &ctx->ein, cfg->ein );

    digital_in_init( &ctx->fo, cfg->fo );
    digital_in_init( &ctx->int_pin, cfg->int_pin );

    return I2C_MASTER_SUCCESS;
}

err_t rtc14_default_cfg ( rtc14_t *ctx ) 
{
    digital_out_low( &ctx->ein );
    dev_cfg_trg_delay( );

    rtc14_soft_reset( ctx );
    dev_cfg_trg_delay( );
    
    rtc14_enable_rtc( ctx );
    dev_cfg_trg_delay( );
    
    return RTC14_OK;
}

err_t rtc14_generic_write ( rtc14_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len ) 
{
    uint8_t data_buf[ 257 ] = { 0 };

    data_buf[ 0 ] = reg;

    for ( uint8_t cnt = 1; cnt <= tx_len; cnt++ )
    {
        data_buf[ cnt ] = tx_buf[ cnt - 1 ];
    }

    return i2c_master_write( &ctx->i2c, data_buf, tx_len + 1 );
}

err_t rtc14_generic_read ( rtc14_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len ) 
{
    return i2c_master_write_then_read( &ctx->i2c, &reg, 1, rx_buf, rx_len );
}

err_t rtc14_write_sram ( rtc14_t *ctx, uint16_t sram_data_in ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };

    tx_buf[ 0 ] = ( uint8_t ) ( sram_data_in >> 8 );
    tx_buf[ 1 ] = ( uint8_t )   sram_data_in;

    return rtc14_generic_write( ctx, RTC14_REG_USR1, tx_buf, 2 );
}

err_t rtc14_read_sram ( rtc14_t *ctx, uint16_t *sram_data_out ) 
{
    uint8_t rx_buf [ 2 ];
    
    err_t err_flag = rtc14_generic_read( ctx, RTC14_REG_USR1,  rx_buf, 2 );
    
    *sram_data_out = rx_buf [ 0 ];
    *sram_data_out <<= 8;
    *sram_data_out |= rx_buf[ 1 ];
    
    return err_flag;
}

uint8_t rtc14_get_interrupt ( rtc14_t *ctx ) 
{
    return digital_in_read( &ctx->int_pin );
}

uint8_t rtc14_get_fout ( rtc14_t *ctx ) 
{
    return digital_in_read( &ctx->fo );
}

err_t rtc14_enable_rtc ( rtc14_t *ctx ) 
{
    uint8_t tx_buf;
    tx_buf = RTC14_SET_ENABLE_WRTC;

    return rtc14_generic_write( ctx, RTC14_REG_SR, &tx_buf, 1 );
}

err_t rtc14_soft_reset ( rtc14_t *ctx ) 
{
    uint8_t tx_buf;
    tx_buf = RTC14_SET_SOFT_RESET;

    return rtc14_generic_write( ctx, RTC14_REG_SR, &tx_buf, 1 );
}

err_t rtc14_get_time ( rtc14_t *ctx, rtc14_time_t *rtc_time ) 
{
    uint8_t rx_data;

    err_t error_flag = rtc14_generic_read( ctx, RTC14_REG_SC, &rx_data, 1 );
    rtc_time->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MN, &rx_data, 1 );
    rtc_time->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_HR, &rx_data, 1 );
    if ( rx_data & RTC14_SET_HOURS_FORMAT_24 )
    {
        rx_data &= BIT_MASK_HOURS_FORMAT_24;    
    }
    else
    {
        rtc_time->am_pm = rx_data & RTC14_SET_HOURS_FORMAT_12_PM;
        rx_data &= BIT_MASK_HOURS_FORMAT_12;    
    }
    
    rtc_time->hours = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc14_set_time ( rtc14_t *ctx, rtc14_time_t rtc_time ) 
{
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    if ( ( rtc_time.sec > MAX_MIN_SEC ) || 
         ( rtc_time.min > MAX_MIN_SEC ) || 
         ( rtc_time.hours > MAX_HOUR ) ) {
        error_flag = RTC14_ERROR;
    } else {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.sec ); 
        error_flag = rtc14_generic_write( ctx, RTC14_REG_SC, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.min ); 
        error_flag |= rtc14_generic_write( ctx, RTC14_REG_MN, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_time.hours ); 
        tx_buf[ 0 ] |= rtc_time.hours_format;
        if ( rtc_time.hours_format == RTC14_SET_HOURS_FORMAT_12 )
        {
            tx_buf[ 0 ] &= ~RTC14_SET_HOURS_FORMAT_12_PM;
            tx_buf[ 0 ] |= rtc_time.am_pm;   
        }
        error_flag |= rtc14_generic_write( ctx, RTC14_REG_HR, tx_buf, 1 );
    }
    
    return error_flag;
}

err_t rtc14_get_date ( rtc14_t *ctx, rtc14_date_t *rtc_date ) 
{
    uint8_t rx_data;

    err_t error_flag = rtc14_generic_read( ctx, RTC14_REG_DT, &rx_data, 1 );
    rtc_date->day = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MO, &rx_data, 1 );
    rtc_date->month = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_YR, &rx_data, 1 );
    rtc_date->year = dev_rtc_to_dec( rx_data );
    
    error_flag = rtc14_generic_read( ctx, RTC14_REG_DW, &rx_data, 1 );
    rtc_date->day_of_week = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc14_set_date ( rtc14_t *ctx, rtc14_date_t rtc_date ) 
{
    uint8_t num_day;
    err_t error_flag;
    uint8_t tx_buf[ 1 ];
    
    error_flag = RTC14_ERROR;
    
    switch ( rtc_date.month ) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
        {
            num_day = 31;
            break;
        }
        case 4: case 6: case 9: case 11: 
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
    
    if ( ( rtc_date.year % 4 == 0 ) && ( num_day == 28 ) ) 
    {
        num_day = 29; 
    }
    
    if ( ( rtc_date.day < 1 )       || 
         ( num_day < rtc_date.day ) || 
         ( rtc_date.month < 1 )     || 
         ( rtc_date.month > 12 ) ) 
    {
        error_flag = RTC14_OK;    
    } 
    else 
    {
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.day ); 
        rtc14_generic_write( ctx, RTC14_REG_DT, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.month );
        rtc14_generic_write( ctx, RTC14_REG_MO, tx_buf, 1 );
    
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.year );
        rtc14_generic_write( ctx, RTC14_REG_YR, tx_buf, 1 );
        
        tx_buf[ 0 ] = dev_dec_to_rtc( rtc_date.day_of_week ); 
        rtc14_generic_write( ctx, RTC14_REG_DW, tx_buf, 1 );
    }
    
    return error_flag; 
}

err_t rtc14_get_alarm ( rtc14_t *ctx, rtc14_alarm_t *rtc_alarm ) 
{
    uint8_t rx_data;
    
    err_t error_flag = rtc14_generic_read( ctx, RTC14_REG_SCA, &rx_data, 1 );
    rtc_alarm->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MNA, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_HRA, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->hours = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_DTA, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->day = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MOA, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->month = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_DWA, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_alarm->day_of_week = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

err_t rtc14_set_alarm ( rtc14_t *ctx, rtc14_alarm_t rtc_alarm ) 
{
    uint8_t tx_buf[ 1 ];
    err_t error_flag;
    
    error_flag = RTC14_OK;
    
    if ( ( rtc_alarm.min > MAX_MIN_SEC ) || 
         ( rtc_alarm.hours > MAX_HOUR )  ||
         ( rtc_alarm.day > MAX_DAY ) ) 
    {
        error_flag = RTC14_ERROR;
    } 
    else 
    {
        if ( rtc_alarm.sec > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.sec );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_SCA, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.min > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.min );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_MNA, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.hours > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.hours );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_HRA, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.day > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.day );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_DTA, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.month > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.month );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_MOA, tx_buf, 1 );    
        }
        
        if ( rtc_alarm.day_of_week > 0 )
        {
            tx_buf[ 0 ] = dev_dec_to_rtc( rtc_alarm.day_of_week );
            tx_buf[ 0 ] |= BIT_MASK_ALARM_ENABLE;
            error_flag |= rtc14_generic_write( ctx, RTC14_REG_DWA, tx_buf, 1 );    
        }
        
        error_flag |= rtc14_generic_read( ctx, RTC14_REG_INT, tx_buf, 1 );
        tx_buf[ 0 ] |= RTC14_SET_ALARM_ENABLE;
        tx_buf[ 0 ] |= RTC14_SET_INT_ENABLE;
        error_flag |= rtc14_generic_write( ctx, RTC14_REG_INT, tx_buf, 1 );  
    }
    
    return error_flag;
}

void rtc14_trigger_time_stamp ( rtc14_t *ctx ) 
{
    digital_out_high( &ctx->ein );
    dev_cfg_trg_delay( );
    digital_out_low( &ctx->ein );
    dev_cfg_trg_delay( );
}

err_t rtc14_get_time_stamp ( rtc14_t *ctx, rtc14_time_stamp_t *rtc_time_stamp ) 
{
    uint8_t rx_data;
    
    err_t error_flag = rtc14_generic_read( ctx, RTC14_REG_SCT, &rx_data, 1 );
    rtc_time_stamp->sec = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MNT, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_time_stamp->min = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_HRT, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_time_stamp->hours = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_DTT, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_time_stamp->day = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_MOT, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_time_stamp->month = dev_rtc_to_dec( rx_data );
    
    error_flag |= rtc14_generic_read( ctx, RTC14_REG_YRT, &rx_data, 1 );
    rx_data &= BIT_MASK_TIME_REV_BIT;
    rtc_time_stamp->year = dev_rtc_to_dec( rx_data );
    
    return error_flag;
}

static uint8_t dev_dec_to_rtc ( uint8_t dec ) 
{
    return ( ( dec / 10 ) << 4 ) + ( dec % 10 );
}

static uint8_t dev_rtc_to_dec ( uint8_t bcd ) 
{
    return ( bcd & BIT_MASK_LSN ) + ( ( bcd >> 4 ) * 10 );
}

static void dev_cfg_trg_delay ( void )
{
    Delay_10ms( );
}

// ------------------------------------------------------------------------- END
