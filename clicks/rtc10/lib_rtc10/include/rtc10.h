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
 * \brief This file contains API for Rtc 10 Click driver.
 *
 * \addtogroup rtc10 Rtc 10 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC10_H
#define RTC10_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */
#define RTC10_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC10_RETVAL  uint8_t

#define RTC10_OK           0x00
#define RTC10_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup slave_address  Slave Address
 * \{
 */
#define RTC10_I2C_SLAVE_ADDRESS                                  0x68
/** \} */

/**
 * \defgroup register_address   Register Address
 * \{
 */
#define RTC10_RTCSEC                                             0x00
#define RTC10_RTCMIN                                             0x01
#define RTC10_RTCHOUR                                            0x02
#define RTC10_RTCWKDAY                                           0x03
#define RTC10_RTCDATE                                            0x04
#define RTC10_RTCMTH                                             0x05
#define RTC10_RTCYEAR                                            0x06
#define RTC10_ALM1SEC                                            0x07
#define RTC10_ALM1MIN                                            0x08
#define RTC10_ALM1HOUR                                           0x09
#define RTC10_ALM1DATE                                           0x0A
#define RTC10_ALM2MIN                                            0x0B
#define RTC10_ALM2HOUR                                           0x0C
#define RTC10_ALM2DATE                                           0x0D
#define RTC10_CONTROL                                            0x0E
#define RTC10_STATUS                                             0x0F
#define RTC10_AGING                                              0x10
#define RTC10_TEMPERATURE_MSB                                    0x11
#define RTC10_TEMPERATURE_LSB                                    0x12
/** \} */

/**
 * \defgroup disable_enable  Disable Enable
 * \{
 */
#define RTC10_DISABLE_ALARMS                                     0x00
#define RTC10_ENABLE_ALARM_1                                     0x01
#define RTC10_ENABLE_ALARM_2                                     0x02
#define RTC10_ENABLE_INTERRUPT                                   0x04
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;

    // Input pins 

    digital_in_t an;
    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} rtc10_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t an;
    pin_name_t rst;
    pin_name_t int_pin;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} rtc10_cfg_t;

/** \} */ // End types group
// ----------------------------------------------- PUBLIC FUNCTION DECLARATIONS

/**
 * \defgroup public_function Public function
 * \{
 */
 
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief Config Object Initialization function.
 *
 * @param cfg  Click configuration structure.
 *
 * @description This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rtc10_cfg_setup ( rtc10_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC10_RETVAL rtc10_init ( rtc10_t *ctx, rtc10_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Rtc10 click.
 */
void rtc10_default_cfg ( rtc10_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @description This function writes data to the desired register.
 */
void rtc10_generic_write ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void rtc10_generic_read ( rtc10_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Hardware reset function.
 *
 * @param ctx          Click object.
 *
 * @description This function hardware reset the DS3231M I2C realtime clock on RTC 10 Click
 * by cleared to '0' state of the RST pin,
 * wait the 100 ms, sets to '1' state of the RST pin
 * and wait another the 100 ms..
 */
void rtc10_hw_reset ( rtc10_t *ctx );

/**
 * @brief Check the state of interrupt function.
 *
 * @param ctx          Click object.
 *
 * @description Function check the state of interrupt ( INT ) pin of RTC 10 Click.
 */
uint8_t rtc10_check_interrupt ( rtc10_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx               Click object.
 * @param reg_address       8-bit register address.
 *
 * @description This Function write the 8-bit of data to the target 8-bit register address of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_read_byte ( rtc10_t *ctx, uint8_t reg_address );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg_address  8-bit register address.
 * @param write_data   8-bit data to write
 *
 * @description This function write the 8-bit of data to thetarget 8-bit register address of DS3231M I2C realtime clock on RTC 10 Click..
 */
void rtc10_write_byte ( rtc10_t *ctx, uint8_t reg_address, uint8_t write_data );

/**
 * @brief Get seconds function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets seconds data from the target ( _RTC10_RTCSEC ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_time_seconds ( rtc10_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param seconds      time seconds [ 0 sec : 59 sec ]
 *
 * @description This function sets seconds data to the target ( _RTC10_RTCSEC ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_time_seconds ( rtc10_t *ctx, uint8_t seconds );

/**
 * @brief Get seconds function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets seconds data from the target ( _RTC10_RTCMIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_time_minutes ( rtc10_t *ctx );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param minutes      Time minutes [ 0 min : 59 min ]
 *
 * @description This function sets minutes data to the target ( _RTC10_RTCMIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_time_minutes ( rtc10_t *ctx, uint8_t minutes );

/**
 * @brief Get century flag function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets century flag ( bit 7 ) from the target ( _RTC10_RTCMIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_century_flag ( rtc10_t *ctx );

/**
 * @brief Set century flag function.
 *
 * @param ctx          Click object.
 *
 * @description This function sets century flag ( bit 7 ) to the target ( _RTC10_RTCMIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_century_flag ( rtc10_t *ctx );

/**
 * @brief Get hours function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets hours data from the target ( _RTC10_RTCHOUR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_time_hours ( rtc10_t *ctx );

/**
 * @brief Set hours function.
 *
 * @param ctx          Click object.
 * @param hours        Time hours [ 0 h : 23 h ]
 *
 * @description This function sets hours data to the target ( _RTC10_RTCHOUR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_time_hours( rtc10_t *ctx, uint8_t hours );

/**
 * @brief Get day of the week function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets day of the week data from the target ( _RTC10_RTCWKDAY ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_day_of_the_week ( rtc10_t *ctx );

/**
 * @brief Set day of the week function.
 *
 * @param ctx          Click object.
 * @param w_day        Day of the week data [ 1 : 7 ]
 * - 1 : Monday;
 * - 2 : Tuesday;
 * - 3 : Wednesday;
 * - 4 : Thursday;
 * - 5 : Friday;
 * - 6 : Saturday;
 * - 7 : Sunday;
 *
 * @description This function sets day of the week data to the target ( _RTC10_RTCWKDAY ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_day_of_the_week ( rtc10_t *ctx, uint8_t w_day );

/**
 * @brief Get date function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets date data from the target ( _RTC10_RTCDATE ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_date_day ( rtc10_t *ctx );

/**
 * @brief Set date function.
 *
 * @param ctx          Click object.
 * @param date_day     Date day data [ 1 : 31 ]
 *
 * @description This function sets date data from the target ( _RTC10_RTCDATE ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_date_day ( rtc10_t *ctx, uint8_t date_day );

/**
 * @brief Get month function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets month data from the target ( _RTC10_RTCMTH ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_date_month ( rtc10_t *ctx );

/**
 * @brief Set month function.
 *
 * @param ctx          Click object.
 * @param date_month   Date month data [ 1 : 12 ]
 *
 * @description This function sets month data from the target ( _RTC10_RTCMTH ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_date_month( rtc10_t *ctx, uint8_t date_month );

/**
 * @brief Get year function.
 *
 * @param ctx          Click object.
 *
 * @description This function gets year data from the target ( _RTC10_RTCYEAR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_date_year ( rtc10_t *ctx );

/**
 * @brief Set month function.
 *
 * @param ctx          Click object.
 * @param date_year    Date year data [ xx00 : xx99 ]
 *
 * @description This function sets year data to the target ( _RTC10_RTCYEAR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_date_year ( rtc10_t *ctx, uint16_t date_year );

/**
 * @brief Set time: hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_minutes          Time minutes [ 0 min : 59 min ]
 * @param time_hours            Time hours [ 0 h : 23 h ]
 * @param time_seconds          Time seconds [ 0 sec : 59 sec ]
 *
 * @description This function sets time: hours, minutes and seconds data to the
 * targets ( _RTC10_RTCHOUR, _RTC10_RTCMIN and _RTC10_RTCHOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_time ( rtc10_t *ctx, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds );

/**
 * @brief Get time hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_minutes          pointer of time minutes [ 0 min : 59 min ]
 * @param time_hours            pointer of time hours [ 0 h : 23 h ]
 * @param time_seconds          pointer of time seconds [ 0 sec : 59 sec ]
 *
 * @description This function gets time: hours, minutes and seconds data from the
 * targets ( _RTC10_RTCHOUR, _RTC10_RTCMIN and _RTC10_RTCHOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_get_time ( rtc10_t *ctx, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

/**
 * @brief Set date hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param day_of_the_week       Date of the week data [ 1 : 7 ]
 * @param date_day              Date day data [ 1 : 31 ]
 * @param date_month            Date month data [ 1 : 12 ]
 * @param date_year             Date year data [ 0 : 99 ]
 *
 * @description This function sets date: day of the week, day, month and year data to the
 * targets ( _RTC10_RTCWKDAY, _RTC10_RTCDATE, _RTC10_RTCMTH and _RTC10_RTCYEAR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_date( rtc10_t *ctx, uint8_t day_of_the_week, uint8_t date_day, uint8_t date_month, uint16_t date_year );

/**
 * @brief Get time hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param day_of_the_week       pointer of date of the week data [ 1 : 7 ]
 * @param date_day              pointer of date day data [ 1 : 31 ]
 * @param date_month            pointer of date month data [ 1 : 12 ]
 * @param date_year             pointer of date year data [ 0 : 99 ]
 *
 * @description This function gets date: day of the week, day, month and year data from the
 * targets ( _RTC10_RTCWKDAY, _RTC10_RTCDATE, _RTC10_RTCMTH and _RTC10_RTCYEAR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_get_date( rtc10_t *ctx, uint8_t *day_of_the_week, uint8_t *date_day, uint8_t *date_month, uint8_t *date_year );

/**
 * @brief Get alarm time seconds function.
 *
 * @param ctx                   Click object.
 *
 * @description This function gets alarm time seconds data from the target ( _RTC10_ALM1SEC ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_alarm_time_seconds ( rtc10_t *ctx );

/**
 * @brief Set alarm time seconds function.
 *
 * @param ctx                   Click object. 
 * @param seconds               Alarm time seconds [ 0 sec : 59 sec ]
 *
 * @description This function gets alarm time seconds data to the target ( _RTC10_ALM1SEC ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_alarm_time_seconds ( rtc10_t *ctx, uint8_t seconds );

/**
 * @brief Get alarm time minutes function.
 *
 * @param ctx                   Click object. 
 *
 * @description This function sets alarm time minutes data from the target ( _RTC10_ALM1MIN or _RTC10_ALM2MIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_alarm_time_minutes ( rtc10_t *ctx );

/**
 * @brief Set alarm time seconds function.
 *
 * @param ctx                   Click object. 
 * @param minutes               Alarm time minutes [ 0 min : 59 min ]
 *
 * @description This function sets alarm time minutes data to the target ( _RTC10_ALM1MIN or _RTC10_ALM2MIN ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_alarm_time_minutes( rtc10_t *ctx, uint8_t minutes );

/**
 * @brief Get alarm time hours function.
 *
 * @param ctx                   Click object. 
 *
 * @description This function sets alarm time hours data from the target ( _RTC10_ALM1HOUR or _RTC10_ALM2HOUR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_alarm_time_hours ( rtc10_t *ctx );

/**
 * @brief Set alarm time seconds function.
 *
 * @param ctx                   Click object. 
 * @param hours                 hours [ 0 h : 23 h ]
 *
 * @description This function sets alarm time hours data from the target ( _RTC10_ALM1HOUR or _RTC10_ALM2HOUR ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_alarm_time_hours ( rtc10_t *ctx, uint8_t hours );

/**
 * @brief Get alarm days function.
 *
 * @param ctx                   Click object. 
 *
 * @description This function gets alarm days data from the target ( _RTC10_ALM1DATE or _RTC10_ALM2DATE ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_alarm_date_day ( rtc10_t *ctx );

/**
 * @brief Set alarm days function.
 *
 * @param ctx                   Click object. 
 * @param date_day              Date days data [ 1 : 31 ]
 *
 * @description This function sets alarm time minutes data from the target ( _RTC10_ALM1DATE or _RTC10_ALM2DATE ) register address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_alarm_date_day ( rtc10_t *ctx, uint8_t date_day );

/**
 * @brief Set Alarm 1 time: hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_days             Time days data [ 1 : 31 ]
 * @param time_hours            Time hours [ 0 h : 23 h ]
 * @param time_minutes          Time minutes [ 0 min : 59 min ]
 * @param time_seconds          Time seconds [ 0 sec : 59 sec ]
 *
 * @description This function sets Alarm 1 time: hours, minutes and seconds data to the
 * targets ( _RTC10_ALM1SEC, _RTC10_ALM1MIN and _RTC10_ALM1HOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_first_alarm ( rtc10_t *ctx, uint8_t time_days, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds );

/**
 * @brief Get Alarm 1 time hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_days             pointer of time days [ 1 : 31 ]
 * @param time_hours            pointer of time hours [ 0 h : 23 h ]
 * @param time_minutes          pointer of time minutes [ 0 min : 59 min ]
 * @param time_seconds          pointer of time seconds [ 0 sec : 59 sec ]
 *
 * @description This function gets Alarm 1 time: hours, minutes and seconds data from the
 * targets ( _RTC10_ALM1SEC, _RTC10_ALM1MIN and _RTC10_ALM1HOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_get_first_alarm ( rtc10_t *ctx, uint8_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

/**
 * @brief Set Alarm 2 time: hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_days             Time days [ 1 : 31 ]
 * @param time_hours            Time hours [ 0 h : 23 h ]
 * @param time_minutes          Time minutes [ 0 min : 59 min ]
 
 *
 * @description This function sets Alarm 2 time: hours, minutes and seconds data to the
 * targets ( _RTC10_ALM2SEC, _RTC10_ALM2MIN and _RTC10_ALM2HOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_second_alarm( rtc10_t *ctx, uint8_t time_days, uint8_t time_hours, uint8_t time_minutes );

/**
 * @brief Set Alarm 2 time: hours, minutes and seconds function.
 *
 * @param ctx                   Click object.
 * @param time_days             pointer of time days [ 1 : 31 ]
 * @param time_hours            pointer of time hours [ 0 h : 23 h ]
 * @param time_minutes          pointer of time minutes [ 0 min : 59 min ]
 
 *
 * @description This function gets Alarm 2 time: hours, minutes and seconds data from the
 * targets ( _RTC10_ALM2SEC, _RTC10_ALM2MIN and _RTC10_ALM2HOUR ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_get_second_alarm ( rtc10_t *ctx, uint8_t *time_days, uint8_t *time_hours, uint8_t *time_minutes );

/**
 * @brief Enable counting function.
 *
 * @param ctx                   Click object.
 *
 * @description This function enable counting on RTC 10 Click
 * by set bit 7 of the targets ( _RTC10_CONTROL ) registers address
 * of DS3231M I2C realtime clock.
 */
void rtc10_enable_counting ( rtc10_t *ctx );

/**
 * @brief Set configuration function.
 *
 * @param ctx                   Click object.
 * @param config_data           - bit [ 7 ]     : Enable oscillator. When set to logic 0, the oscillator is started.
 *                   When set to logic 1, the oscillator is stopped when the device switches to VBAT.
 *                   This bit is clear (logic 0) when power is first applied.
 *                   When the device is powered by VCC, the oscillator is always on regardless of the status of the EOSC bit.
 *                   When the oscillator is disabled, all register data is static
 * - bit [ 6 ]     : Battery-backed square-wave enable. 
 *                   When set to logic 1 with INTCN = 0 and VCC < VPF, this bit enables the 1Hz square wave.
 *                   When BBSQW is logic 0, INT/SQW goes high impedance when VCC falls below VPF.
 *                   This bit is disabled (logic 0) when power is first applied.
 * - bit [ 5 ]     : Convert temperature. 
 *                   Setting this bit to 1 forces the temperature sensor to convert the temperature into digital code
 *                   and execute the temperature compensate algorithm to update the oscillator�s accuracy.
 *                   The device cannot be forced to execute the temperature-compensate algorithm faster than once per second.
 *                   A user-initiated temperature conversion does not affect the internal update cycle.
 *                   The CONV bit remains at a 1 from the time it is written until the temperature conversion is completed, at which time both CONV and BSY go to 0.
 *                   The CONV bit should be used when monitoring the status of a user-initiated conversion. See Figure 7 for more details.
 * - bit [ 4 : 3 ] : Not applicable. 
 *                   These bits have no affect on the device and can be set to either 0 or 1.
 * - bit [ 2 ]     : Interrupt control.
 *                   This bit controls the INT/SQW output signal. 
 *                   When the INTCN bit is set to logic 0, a 1Hz square wave is output on INT/SQW. When the INTCN bit is set to logic 1,
 *                   a match between the timekeeping registers and either of the alarm registers activates the INT/SQW output (if the alarm is also enabled).
 *                   The corresponding alarm flag is always set regardless of the state of the INTCN bit.
 *                   The INTCN bit is set to a logic 1 when power is first applied.
 * - bit [ 1 ]     : Alarm 2 interrupt enable. 
 *                   When set to logic 1, this bit permits the alarm 2 flag (A2F) bit in the status register to assert INT/SQW (when INTCN = 1). 
 *                   When the A2IE bit is set to logic 0 or INTCN is set to logic 0, the A2F bit does not initiate an interrupt signal.
 *                   The A2IE bit is disabled (logic 0) when power is first applied.
 * - bit [ 0 ]     : Alarm 1 interrupt enable. 
 *                   When set to logic 1, this bit permits the alarm 1 flag (A1F) bit in the status register to assert INT/SQW (when INTCN = 1). 
 *                   When the A1IE bit is set to logic 0 or INTCN is set to logic 0, the A1F bit does not initiate an interrupt signal. 
 *                   The A1IE bit is disabled (logic 0) when power is first applied.
 *
 * @description This function sets configuration value to the
 * targets ( _RTC10_CONTROL ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
void rtc10_set_config( rtc10_t *ctx, uint8_t config_data );

/**
 * @brief Get configuration status function.
 *
 * @param ctx                   Click object.
 * @param config_data           * - bit [ 7 ]     : EOscillator stop flag. 
 *                   A logic 1 in this bit indicates that the oscillator either is stopped or was stopped
 *                   for some period and could be used to judge the validity of the timekeeping data.
 *                   This bit is set to logic 1 any time that the oscillator stops. This bit remains at logic 1 until written to logic 0.
 *                   The following are examples of conditions that can cause the OSF bit to be set:
 *                       - 1 : The first time power is applied;
 *                       - 2 : The voltages present on both VCC and VBAT are insufficient to support the oscillator;
 *                       - 3 : The EOSC bit is turned off in battery-backed mode;
 *                       - 4 : External influences on the oscillator (i.e., noise, leakage, etc.).
 * - bit [ 6 : 4 ] : Unused ( 0 ).
 *                   These bits have no meaning and are fixed at 0 when read.
 * - bit [ 3 ]     : Enabled 32.768kHz output.
 *                   This bit enables and disables the 32KHZ output. 
 *                   When set to a logic 0, the 32KHZ output is high impedance.
 *                   On initial power-up, this bit is set to a logic 1 and the 32KHZ output is enabled
 *                   and produces a 32.768kHz square wave if the oscillator is enabled.
 *                   These bits have no affect on the device and can be set to either 0 or 1.
 * - bit [ 2 ]     : Busy. 
 *                   This bit indicates the device is busy executing temperature conversion function. 
 *                   It goes to logic 1 when the conversion signal to the temperature sensor is asserted, 
 *                   and then it is cleared when the device has completed the temperature conversion.
 * - bit [ 1 ]     : Alarm 2 flag. 
 *                   A logic 1 in the alarm 2 flag bit indicates that the time matched the alarm 2 registers. 
 *                   If the A2IE bit is logic 1 and the INTCN bit is set to logic 1, INT/SQW is also asserted. 
 *                   A2F is cleared when written to logic 0. 
 *                   This bit can only be written to logic 0. 
 *                   Attempting to write to logic 1 leaves the value unchanged.
 * - bit [ 0 ]     : Alarm 1 flag. 
 *                   A logic 1 in the alarm 1 flag bit indicates that the time matched the alarm 1 registers. 
 *                   If the A1IE bit is logic 1 and the INTCN bit is set to logic 1, INT/SQW is also asserted. 
 *                   A1F is cleared when written to logic 0. 
 *                   This bit can only be written to logic 0. 
 *                   Attempting to write to logic 1 leaves the value unchanged. 
 *                   The A1IE bit is disabled (logic 0) when power is first applied.
 *
 * @description This function get configuration status value from the
 * target ( _RTC10_STATUS ) registers address
 * of DS3231M I2C realtime clock on RTC 10 Click.
 */
uint8_t rtc10_get_status ( rtc10_t *ctx );

/**
 * @brief Get temperature function.
 *
 * @param ctx                   Click object.
 *
 * @description This function get value of temperature [ �C ] from the
 * targets ( _RTC10_TEMPERATURE_MSB and _RTC10_TEMPERATURE_LSB ) registers address
 * of DS3231M I2C realtime clock.
 */
float rtc10_get_temperature ( rtc10_t *ctx );



#ifdef __cplusplus
}
#endif
#endif  // _RTC10_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
