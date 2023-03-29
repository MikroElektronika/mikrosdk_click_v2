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
 * @file rtc4.c
 * @brief RTC 4 Click Driver.
 */

#include "rtc4.h"

/** 
 * @brief Calculation for Maxim CRC 8 function.
 * @details This function calculates Maxim CRC 8 with parameteres: 
 * @li @c  Width 8 bit
 * @li @c  Polynomial 0x31 (x8 + x5 + x4 + 1 )
 * @li @c  Initialization 0x00
 * @li @c  Reflect input False
 * @li @c  Reflect output False
 * @li @c  Final No xor
 * @param[in] data_buf : Array of bytes to calculate crc from.
 * @param[in] len : Number of bytes to calculate crc from.
 * @return Calculated Maxim CRC.
 * @note None.
 */
static uint8_t rtc4_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len );

void rtc4_cfg_setup ( rtc4_cfg_t *cfg ) 
{
    cfg->gp0 = HAL_PIN_NC;
    cfg->gp1 = HAL_PIN_NC;
    cfg->int_pin = HAL_PIN_NC;
    
    cfg->gpio_sel = RTC4_GPIO_0;
}

void rtc4_gpio_selection ( rtc4_cfg_t *cfg, rtc4_gpio_sel_t gpio_sel ) 
{
    cfg->gpio_sel = gpio_sel;
}

err_t rtc4_init ( rtc4_t *ctx, rtc4_cfg_t *cfg ) 
{
    one_wire_configure_default( &ctx->ow );

    ctx->ow.data_pin = ( cfg->gpio_sel == RTC4_GPIO_0 ) ? cfg->gp0 : cfg->gp1;

    if ( ONE_WIRE_ERROR == one_wire_open( &ctx->ow ) )
    {
        return ONE_WIRE_ERROR;
    }

    digital_in_init( &ctx->int_pin, cfg->int_pin );
    
    return ONE_WIRE_SUCCESS;
}

err_t rtc4_check_communication ( rtc4_t *ctx )
{
    if ( ONE_WIRE_ERROR == one_wire_read_rom ( &ctx->ow, &ctx->rom_addr ) )
    {
        return RTC4_ERROR;
    }
    if ( RTC4_FAMILY_CODE != ctx->rom_addr.address[ 0 ] )
    {
        return RTC4_ERROR;
    }
    if ( ctx->rom_addr.address[ 7 ] != rtc4_calculate_crc8_maxim( &ctx->rom_addr.address[ 0 ], 7 ) )
    {
        return  RTC4_ERROR; 
    }
    return RTC4_OK;
}

uint8_t rtc4_get_interrupt ( rtc4_t *ctx ) 
{
    return digital_in_read ( &ctx->int_pin );
}

err_t rtc4_set_unix_and_int ( rtc4_t *ctx, uint32_t unix_time, uint8_t int_interval )
{
    err_t error_flag = RTC4_OK; 
    
    uint8_t data_buf[ 4 ]; 
    uint8_t control = RTC4_DCB_INT_ENABLE | RTC4_DCB_OSC_ENABLE | int_interval;
    uint8_t command = RTC4_CMD_WRITE_CLOCK; 
    
    data_buf[ 0 ] = ( uint8_t ) ( unix_time & 0xFF );
    data_buf[ 1 ] = ( uint8_t ) ( ( unix_time >> 8 ) & 0xFF );
    data_buf[ 2 ] = ( uint8_t ) ( ( unix_time >> 16 ) & 0xFF );
    data_buf[ 3 ] = ( uint8_t ) ( ( unix_time >> 24 ) & 0xFF );

    error_flag |= one_wire_skip_rom( &ctx->ow ); 
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 ); 
    error_flag |= one_wire_write_byte( &ctx->ow, &control, 1 ); 
    error_flag |= one_wire_write_byte( &ctx->ow, &data_buf[ 0 ], 4 );
    
    return error_flag; 
}

err_t rtc4_get_unix_time ( rtc4_t *ctx, uint32_t *unix_time )
{
    err_t error_flag = RTC4_OK;
    
    uint8_t data_buf[ 4 ];
    uint8_t control;
    uint8_t command = RTC4_CMD_READ_CLOCK;
 
    error_flag |= one_wire_match_rom( &ctx->ow, &ctx->rom_addr );
    error_flag |= one_wire_write_byte( &ctx->ow, &command, 1 );

    error_flag |= one_wire_read_byte( &ctx->ow, &control, 1 );
    error_flag |= one_wire_read_byte( &ctx->ow, &data_buf[ 0 ], 4 );
    
    *unix_time = data_buf[ 3 ];
    *unix_time <<= 8;
    *unix_time |= data_buf[ 2 ];
    *unix_time <<= 8;
    *unix_time |= data_buf[ 1 ];
    *unix_time <<= 8;
    *unix_time |= data_buf[ 0 ];

    return error_flag;
}

void rtc4_unix_to_date_time ( uint32_t unix_time, rtc4_time_t *time, rtc4_date_t *date ) 
{
    uint32_t days_of_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    uint8_t flag = 0; 
    uint8_t flag1 = 0; 
    uint32_t curr_year = RTC4_START_YEAR;
    uint32_t days_till_now;
    uint32_t extra_days;
    uint32_t day; 
    uint32_t month = 0;
    
    days_till_now = unix_time / RTC4_SEC_PER_DAY;
    
    if ( date->year % 400 == 0 || ( date->year % 4 == 0 && date->year % 100 != 0 ) ) 
    {
        flag1 = 1; 
    }
    
    while ( ( days_till_now >= RTC4_DAYS_PER_YEAR && flag1 == 0 ) || ( days_till_now > RTC4_DAYS_PER_YEAR && flag1 == 1 ) ) 
    {
        if ( curr_year % 400 == 0 || ( curr_year % 4 == 0 && curr_year % 100 != 0 ) ) 
        {
            days_till_now -= RTC4_DAYS_PER_LEAP_YEAR; 
        }
        else  
        {
            days_till_now -= RTC4_DAYS_PER_YEAR ; 
        }
        curr_year += 1; 
    }
    
    extra_days = days_till_now + 1; 
    
    if ( curr_year % 400 == 0 || ( curr_year % 4 == 0 && curr_year % 100 != 0 ) ) 
    {
        flag = 1; 
        for ( ; ; ) 
        {
            if ( month == 1 ) 
            {
                if ( extra_days <= RTC4_DAYS_IN_FEB ) 
                {
                    break; 
                }
                month += 1; 
                extra_days -= RTC4_DAYS_IN_FEB; 
            }
            else  
            {
                if ( extra_days <= days_of_month [ month ] ) 
                {
                    break; 
                }
                extra_days -= days_of_month [ month ]; 
                month += 1; 
            } 
        }
    }
    else 
    {
        for ( ; ; ) 
        {
            if ( extra_days <= days_of_month [ month ] ) 
            {
                break; 
            }
            extra_days -= days_of_month [ month ];  
            month += 1; 
        }
    }
    
    if ( extra_days )  
    {
        month += 1;  
        day = extra_days; 
    }
    else if ( month == 2 && flag == 1 )
    {
        day = RTC4_DAYS_IN_FEB; 
    }
    else
    {
        day = days_of_month [ month - 1 ]; 
    }
    
    date->year = curr_year; 
    date->month = month; 
    date->day = day; 
    
    time->hours = ( unix_time % RTC4_SEC_PER_DAY ) / RTC4_SEC_PER_HOUR; 
    time->min = ( unix_time % RTC4_SEC_PER_HOUR ) / RTC4_SEC_PER_MINUTE;
    time->sec = unix_time % RTC4_SEC_PER_MINUTE;
}

void rtc4_date_time_to_unix ( rtc4_date_t *date, rtc4_time_t *time, uint32_t *unix_time )
{
    uint8_t days_of_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    uint8_t leap_year = 0;
    
    *unix_time = time->sec + RTC4_SEC_PER_MINUTE * time->min + RTC4_SEC_PER_HOUR * time->hours; 
 
    for ( uint16_t cnt = date->year - 1; cnt >= RTC4_START_YEAR; cnt--)
    {
        if ( cnt % 400 == 0 || ( cnt % 4 == 0 && cnt % 100 != 0 ) )
        {
            *unix_time += RTC4_DAYS_PER_LEAP_YEAR * RTC4_SEC_PER_DAY;
        }
        else
        {
            *unix_time += RTC4_DAYS_PER_YEAR * RTC4_SEC_PER_DAY;
        }
    }

    if ( date->year % 400 == 0 || ( date->year % 4 == 0 && date->year % 100 != 0 ) )
    {
        leap_year = 1;
    }
        
    for ( uint8_t cnt = 0; cnt < date->month - 1; cnt++ ) 
    {
        if ( leap_year && ( cnt == 1 ) ) 
        {
            *unix_time += RTC4_SEC_PER_DAY;
        }
        *unix_time += RTC4_SEC_PER_DAY * days_of_month [ cnt ];
    }
    
    *unix_time += RTC4_SEC_PER_DAY * ( date->day - 1 ); 
}

err_t rtc4_set_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time, uint8_t int_interval )
{
    uint32_t unix_time;
    rtc4_date_time_to_unix ( date, time, &unix_time ); 
    return rtc4_set_unix_and_int ( ctx, unix_time, int_interval ); 
}

err_t rtc4_get_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time )
{ 
    err_t error_flag = RTC4_OK; 
    uint32_t unix_time; 
    error_flag |= rtc4_get_unix_time ( ctx, &unix_time );
    rtc4_unix_to_date_time ( unix_time, time, date ); 
    return error_flag; 
}

static uint8_t rtc4_calculate_crc8_maxim ( uint8_t *data_buf, uint8_t len )
{
    uint8_t crc = 0x00;
    
    for ( uint8_t cnt_0 = 0; cnt_0 < len; cnt_0++ ) 
    {
        uint8_t in_byte = data_buf[ cnt_0 ];
        for ( uint8_t cnt_1 = 0; cnt_1 < 8; cnt_1++ ) 
        {
            uint8_t mix = ( crc ^ in_byte ) & 0x01;
            crc >>= 1;
            if ( 0 != mix ) 
            {
                crc ^= 0x8C;
            }
            in_byte >>= 1;
        }
    }
    return crc;
}

// ------------------------------------------------------------------------- END
