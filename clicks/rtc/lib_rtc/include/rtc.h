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
 * \brief This file contains API for RTC Click driver.
 *
 * \addtogroup rtc RTC Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC_H
#define RTC_H

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

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
#define RTC_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT ); 
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC_OK                                          0
#define RTC_ERROR                                      -1
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define RTC_I2C_ADDRESS_0                               0x50
#define RTC_I2C_ADDRESS_1                               0x51
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define RTC_REG_CONTROL                                 0x00
#define RTC_REG_TIME_HUN_SEC                            0x01
#define RTC_REG_TIME_SEC                                0x02
#define RTC_REG_TIME_MIN                                0x03
#define RTC_REG_TIME_HOUR                               0x04
#define RTC_REG_TIME_DATE_DAY_AND_YEAR                  0x05
#define RTC_REG_TIME_DAY_OF_THE_WEEK_AND_MONTH          0x06
#define RTC_REG_TIMER                                   0x07
#define RTC_REG_TIME_ALARM_CONTROL                      0x08
#define RTC_REG_TIME_ALARM_HUN_SEC                      0x09
#define RTC_REG_TIME_ALARM_SEC                          0x0A
#define RTC_REG_TIME_ALARM_MIN                          0x0B
#define RTC_REG_TIME_ALARM_HOUR                         0x0C
#define RTC_REG_TIME_ALARM_DATE_DAY_AND_YEAR            0x0D
#define RTC_REG_TIME_ALARM_DAY_OF_THE_WEEK_AND_MONTH    0x0E
#define RTC_REG_TIME_ALARM_TIMER                        0x0F
/** \} */

/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

/**
 * @brief Date data structure.
 */
typedef struct
{
    uint8_t day_of_the_week;
    uint8_t date_day;
    uint8_t date_month;
    uint16_t date_year;

} rtc_date_t;

/**
 * @brief Time data structure.
 */
typedef struct
{
    uint8_t time_hours;
    uint8_t time_minutes;
    uint8_t time_seconds;
    int8_t time_hun_sec;

} rtc_time_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    // time and date data
    rtc_date_t date;
    rtc_time_t time;

} rtc_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t int_pin;

    // static variable 
    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc_cfg_t;



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
 * @details This function initializes click configuration structure to init state.
 * @note All used pins will be set to unconnected state.
 */
void rtc_cfg_setup ( rtc_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t rtc_init ( rtc_t *ctx, rtc_cfg_t *cfg );

/**
 * @brief RTC I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc_generic_write ( rtc_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc_generic_read ( rtc_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Enable/Disable counting function
 *
 * @param ctx          Click object.
 * @param en_dis       Enable/Disable flag.
 * 
 * @details Function that enables or disables counting on RTC Click.
 */
void rtc_enable_disable_counting ( rtc_t *ctx, uint8_t en_dis );

/**
 * @brief Set control register to read time function
 *
 * @param ctx          Click object.
 * 
 * @details Function sets control register to read time by clearing read location bit
 * of PCF8583 chip on RTC Click.
 */
void rtc_read_time ( rtc_t *ctx );

/**
 * @brief Set control register to read date function
 *
 * @param ctx          Click object.
 * 
 * @details Function sets control register to read time by setting read location bit
 * of PCF8583 chip on RTC Click.
 */
void rtc_read_date ( rtc_t *ctx );

/**
 * @brief Get time value function
 *
 * @param ctx          Click object.
 * @param time_part    Time part register address.
 * 
 * @return Part of the current time in hours [ 0 h - 23 h ], minutes [ 0 min - 59 min ],
 * seconds [ 0 sec - 59 sec ], or hunreths of a second [ 0 ms - 99 ms ].
 *
 * @details Function gets hundredths of a second, seconds, minutes or hours data from
 * the target register address of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_time_value ( rtc_t *ctx, uint8_t time_part );

/**
 * @brief Set time values function
 *
 * @param ctx             Click object.
 * @param time_part       Part of time format ( hours, minutes, seconds or hundreths of a second ).
 * @param time_addr       Register address of the corresponding part of the time format.
 * 
 * @details Function sets seconds data to the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc_set_time_value ( rtc_t *ctx, uint8_t time_part, uint8_t time_addr );

/**
 * @brief Get day function
 *
 * @param ctx             Click object.
 * 
 * @return Date day [ 1 - 31 ]
 *
 * @details Function gets day data from the target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_date_day ( rtc_t *ctx );

/**
 * @brief Set day function
 *
 * @param ctx             Click object.
 * @param date_day        Date day data [ 1 - 31 ]
 *
 * @details Function sets day data from the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc_set_date_day ( rtc_t *ctx, uint8_t date_day );

/**
 * @brief Get year function
 *
 * @param ctx             Click object.
 * 
 * @return Year [ 00 - 99 ]
 *
 * @details Function gets year data from the target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_date_year ( rtc_t *ctx );

/**
 * @brief Set year function
 *
 * @param ctx               Click object.
 * @param date_year         Date year data [ 00 - 99 ]
 *
 * @details Function sets year data from the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc_set_date_year ( rtc_t *ctx, uint16_t date_year );

/**
 * @brief Check if it's a leap year function
 *
 * @param ctx               Click object.
 * 
 * @return result
 *      <pre>
 *        - 0 : Is't Leap Year - February has 28 days.
 *        - 1 : Is Leap Year   - February has 29 days.
 *      </pre>
 *
 * @details Function check if it's a leap year by read from the target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc_check_leap_year ( rtc_t *ctx );

/**
 * @brief Get day of the week function
 *
 * @param ctx               Click object.
 * 
 * @return Day of the week [ 1 - 7 ]
 *
 * @details Function gets day of the week data from tne target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_day_of_the_week ( rtc_t *ctx );

/**
 * @brief Set day of the week function
 *
 * @param ctx                 Click object.
 * @param w_day               Day of the week data [ 1 - 7 ]
 *                            <pre>
 *                              - 1 : Monday;
 *                              - 2 : Tuesday;
 *                              - 3 : Wednesday;
 *                              - 4 : Thursday;
 *                              - 5 : Friday;
 *                              - 6 : Saturday;
 *                              - 7 : Sunday;
 *                            </pre>
 * 
 * @details Function sets day of the week data to the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc_set_day_of_the_week ( rtc_t *ctx, uint8_t w_day );

/**
 * @brief Get month function
 *
 * @param ctx                 Click object.
 * 
 * @return Month [ 1 - 12 ]
 *
 * @details Function gets month data from the target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_date_month ( rtc_t *ctx );

/**
 * @brief Set month function
 *
 * @param ctx                 Click object.
 * @param date_month          Date month data [ 1 - 12 ]
 *
 * @details Function sets month data from the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc_set_date_month ( rtc_t *ctx, uint8_t date_month );

/**
 * @brief Set time hours, minutes, seconds and hundredth of a seconds function
 *
 * @param ctx                 Click object.
 *
 * @details Function sets time: hours, minutes and seconds data to
 * the target register address of PCF8583 chip on RTC Click.
 */
void rtc_set_time ( rtc_t *ctx );

/**
 * @brief Get time hours, minutes, seconds and hundredth of a seconds function
 *
 * @param ctx                 Click object.
 *
 * @details Function gets time: hours, minutes and seconds data from
 * the target register address of PCF8583 chip on RTC Click.
 */
void rtc_get_time ( rtc_t *ctx );

/**
 * @brief Set date hours, minutes and seconds function
 *
 * @param ctx                 Click object.
 *
 * @details Function sets date: day of the week, day, month and year data to
 * the target register address of PCF8583 chip on RTC Click.
 */
void rtc_set_date ( rtc_t *ctx );

/**
 * @brief Get time hours, minutes and seconds function
 *
 * @param ctx                 Click object.
 *
 * @details Function gets date: day of the week, day, month and year data from
 * the target register address of PCF8583 chip on RTC Click.
 */
void rtc_get_date ( rtc_t *ctx );

/**
 * @brief Enable/Disable alarm function
 *
 * @param ctx                 Click object.
 * @param en_dis              Enable/Disable switch flag.
 * 
 * @details Function enable alarm by set alarm control bit register
 * to the target register address of PCF8583 chip on RTC Click.
 */
void rtc_enable_disable_alarm ( rtc_t *ctx, uint8_t en_dis );

/**
 * @brief Set alarm time value
 *
 * @param ctx                 Click object.
 * @param al_time_val         Alarm time part value ( hours, minutes, seconds, hundreths of a second )
 * @param al_time_type        Alarm time register address.
 *
 * @details Function set alarm time - hundredth of a seconds, seconds, minutes or hours by writing time part
 * value to the target register address of PCF8583 chip on RTC Click.
 */
void rtc_set_alarm_value ( rtc_t *ctx, uint8_t al_time_val, uint8_t al_time_type );

/**
 * @brief Get alarm time value function
 *
 * @param ctx                 Click object.
 * @param alarm_addr          Address of the corresponding alarm time register
 * 
 * @return alarm time in hours [ 0 h - 23 h ], minutes [ 0 min - 59 min ],
 * seconds [ 0 sec - 59 sec ], or hunreths of a second [ 0 ms - 99 ms ].
 *
 * @details Function getx alarm time value ( hundredth of a second, seconds, minutes or hours ) 
 * by reading time value from the target register address of PCF8583 chip on RTC Click.
 */
uint8_t rtc_get_alarm_value ( rtc_t *ctx, uint8_t alarm_addr );

/**
 * @brief Set alarm time - minutes function
 *
 * @param ctx                 Click object.
 *
 * @details Function set alarm time - minutes by write minutes value
 * to the target register address of PCF8583 chip on RTC Click.
 */
void rtc_set_time_alarm ( rtc_t *ctx );

/**
 * @brief Get the alarm time hours, minutes, seconds and hundredth of a seconds function
 *
 * @param ctx                 Click object.
 *
 * @details Function gets the alarm time: hours, minutes and seconds data from
 * the target register address of PCF8583 chip on RTC Click.
 */
void rtc_get_time_alarm ( rtc_t *ctx );

/**
 * @brief Enable alarm interrupt function
 *
 * @param ctx                 Click object.
 * @param flag                Enable/Disable switch flag.
 * 
 * @details Function enables/disables alarm interrupt by setting alarm interrupt bit register
 * to the target register address of PCF8583 chip on RTC Click.
 */
void rtc_enable_disable_interrupt( rtc_t *ctx, uint8_t flag );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx                 Click object.
 * @return state of INT pin
 *            <pre>
 *            - 0: not active;
 *            - 1: active
 *            </pre>
 *
 * @details Function get state of interrupt ( INT ) pin.
 */
uint8_t rtc_get_interrupt( rtc_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RTC_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
