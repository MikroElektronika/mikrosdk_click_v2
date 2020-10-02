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
 * \brief This file contains API for RTC 3 Click driver.
 *
 * \addtogroup rtc3 RTC 3 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC3_H
#define RTC3_H

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
#define RTC3_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup slave_addr Slave Address
 * \{
 */
#define RTC3_I2C_ADDRESS                                            0x68
/** \} */

/**
 * \defgroup reg_addr Register Address
 * \{
 */
#define RTC3_REG_TIME_SEC                                           0x00
#define RTC3_REG_TIME_MIN                                           0x01
#define RTC3_REG_TIME_HOUR                                          0x02
#define RTC3_REG_TIME_DAY_OF_THE_WEEK                               0x03
#define RTC3_REG_TIME_DATE_DAY                                      0x04
#define RTC3_REG_TIME_DATE_MONTH                                    0x05
#define RTC3_REG_TIME_DATE_YEAR                                     0x06
#define RTC3_REG_CONFIG1                                            0x07
#define RTC3_REG_TRICKLE_CHARGE2                                    0x08
#define RTC3_REG_CONFIG2                                            0x09
#define RTC3_REG_SF_KEY1                                            0x20
#define RTC3_REG_SF_KEY2                                            0x21
#define RTC3_REG_SFR                                                0x22
/** \} */

/**
 * \defgroup reg_bits Configuration Bits
 * \{
 */
#define RTC3_ENABLE_COUNTING                                        0x7F
#define RTC3_DISABLE_COUNTING                                       0x80
#define RTC3_CONFIG1_INITIAL                                        0x80
#define RTC3_TCH2_OPEN                                              0x00
#define RTC3_TCH2_CLOSED                                            0x20
#define RTC3_TCFE_OPEN                                              0x00
#define RTC3_TCFE_CLOSED                                            0x20
#define RTC3_FTF_NORMAL_512_HZ                                      0x00
#define RTC3_FTF_1_HZ                                               0x01
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC3_RETVAL  uint8_t

#define RTC3_OK           0x00
#define RTC3_INIT_ERROR   0xFF
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

} date_data_t;

/**
 * @brief Time data structure.
 */
typedef struct
{

  uint8_t time_hours;
  uint8_t time_minutes;
  uint8_t time_seconds;
  int8_t time_hun_sec;

} time_data_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;
    
    // time and date data

    date_data_t date;
    time_data_t time;

} rtc3_t;

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

    uint32_t i2c_speed;
    uint8_t i2c_address;

} rtc3_cfg_t;

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
void rtc3_cfg_setup ( rtc3_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC3_RETVAL rtc3_init ( rtc3_t *ctx, rtc3_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for Rtc 3 click.
 */
void rtc3_default_cfg ( rtc3_t *ctx );

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
void rtc3_generic_write ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @description This function reads data from the desired register.
 */
void rtc3_generic_read ( rtc3_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Enable/Disable counting function
 *
 * @param ctx          Click object.
 * 
 * @description Function enables or disables counting on RTC 3 Click.
 */
void rtc3_enable_disable_counting ( rtc3_t *ctx, uint8_t en_dis );

/**
 * @brief Get time value function
 *
 * @param ctx          Click object.
 * @param time_part    Time part register address.
 * 
 * @retval Part of the current time in hours [ 0 h - 23 h ], minutes [ 0 min - 59 min ],
 * or seconds [ 0 sec - 59 sec ].
 *
 * @description Function gets hundredths of a second, seconds, minutes or hours data from
 * the target register address of PCF8583 chip on RTC 3 Click.
 */
uint8_t rtc3_get_time_value ( rtc3_t *ctx, uint8_t time_part );

/**
 * @brief Set time values function
 *
 * @param ctx             Click object.
 * @param time_part       Part of time format ( hours, minutes or seconds ).
 * @param time_addr       Register address of the corresponding part of the time format.
 * 
 * @description Function sets seconds data to the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_time_value ( rtc3_t *ctx, uint8_t time_part, uint8_t time_addr );

/**
 * @brief Get day function
 *
 * @param ctx             Click object.
 * 
 * @retval Date day [ 1 - 31 ]
 *
 * @description Function gets day data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
uint8_t rtc3_get_date_day ( rtc3_t *ctx );

/**
 * @brief Set day function
 *
 * @param ctx             Click object.
 * @param date_day        Date day data [ 1 - 31 ]
 *
 * @description Function sets day data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_date_day ( rtc3_t *ctx, uint8_t date_day );

/**
 * @brief Get month function
 *
 * @param ctx                 Click object.
 * 
 * @retval Month [ 1 - 12 ]
 *
 * @description Function gets month data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
uint8_t rtc3_get_date_month ( rtc3_t *ctx );

/**
 * @brief Set month function
 *
 * @param ctx                 Click object.
 * @param date_month          Date month data [ 1 - 12 ]
 *
 * @description Function sets month data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_date_month ( rtc3_t *ctx, uint8_t date_month );

/**
 * @brief Get year function
 *
 * @param ctx             Click object.
 * 
 * @retval Year [ 00 - 99 ]
 *
 * @description Function gets year data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
uint8_t rtc3_get_date_year ( rtc3_t *ctx );

/**
 * @brief Set year function
 *
 * @param ctx               Click object.
 * @param date_year         Date year data [ 00 - 99 ]
 *
 * @description Function sets year data from the target register address
 * of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_date_year ( rtc3_t *ctx, uint16_t date_year );

/**
 * @brief Get day of the week function
 *
 * @param ctx               Click object.
 * 
 * @retval Day of the week [ 1 - 7 ]
 *
 * @description Function gets day of the week data from tne target register address
 * of PCF8583 chip on RTC Click.
 */
uint8_t rtc3_get_day_of_the_week ( rtc3_t *ctx );

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
 * @description Function sets day of the week data to the target register address
 * of PCF8583 chip on RTC Click.
 */
void rtc3_set_day_of_the_week ( rtc3_t *ctx, uint8_t w_day );

/**
 * @brief Set time hours, minutes, seconds and hundredth of a seconds function
 *
 * @param ctx                 Click object.
 *
 * @description Function sets time: hours, minutes and seconds data to
 * the target register address of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_time ( rtc3_t *ctx );

/**
 * @brief Get time hours, minutes, seconds and hundredth of a seconds function
 *
 * @param ctx                 Click object.
 *
 * @description Function gets time: hours, minutes and seconds data from
 * the target register address of PCF8583 chip on RTC 3 Click.
 */
void rtc3_get_time ( rtc3_t *ctx );

/**
 * @brief Set date hours, minutes and seconds function
 *
 * @param ctx                 Click object.
 *
 * @description Function sets date: day of the week, day, month and year data to
 * the target register address of PCF8583 chip on RTC 3 Click.
 */
void rtc3_set_date ( rtc3_t *ctx );

/**
 * @brief Get time hours, minutes and seconds function
 *
 * @param ctx                 Click object.
 *
 * @description Function gets date: day of the week, day, month and year data from
 * the target register address of PCF8583 chip on RTC 3 Click.
 */
void rtc3_get_date ( rtc3_t *ctx );

/**
 * @brief Set calibration function
 *
 * @param ctx                         Click object.
 * @param calSign                     Calibration sign:
 * 
 *                              <pre>
 *                                - 0: POSITIV;
 *                                - 1: NEGATIV;
 *                              </pre>
 * @param calNumber                   Calibration number:
 *                              <pre>
 *                                - positiv: number/491520 ppm
 *                                - negativ: number/245760 ppm
 *                              </pre>
 * @description Function set calibration by write CAL_CFG1 register of BQ32000 chip.
 */
void rtc3_set_calibration ( rtc3_t *ctx, uint8_t cal_sign, uint8_t cal_mumber );

/**
 * @brief Set trickle charge control function
 *
 * @param ctx                         Click object.
 * @param tch2                        trickle charge control
 *                             <pre>
 *                              - 0: Open;
 *                              - 1: Closed;
 *                             </pre>                       
 * 
 * @description Function set the TCH2 bit determines if 
 * the internal trickle charge switch is closed or open.
 * All the trickle charge switches must be closed
 * in order for trickle charging to occur.
 */
void rtc3_set_trickle_charge ( rtc3_t *ctx, uint8_t tch2 );

/**
 * @brief Set trickle charge bypass control function
 *
 * @param ctx                         Click object.
 * @param tcfe                        trickle charge control
 *                           <pre>
 *                             - 0: Open;
 *                             - 1: Closed;
 *                           </pre>
 * 
 * @description Function set the trickle charge FET bypass. 
 * The TCFE bit is used to enable the trickle charge FET. 
 * When TCFE is 0, the FET is off.
 */
void rtc3_set_trickle_charge_bypass ( rtc3_t *ctx, uint8_t tcfe );

/**
 * @brief Set special function key byte 1 function
 *
 * @param ctx                         Click object.
 * @param sfkey1                      special function key byte 1
 *
 * @description Function set special function access key byte 1. 
 * Reads as 0x00, and key is 0x5E.
 * The SF KEY 1 registers are used to enable access to the main special function register (SFR). 
 * Access to SFR is granted only after the special function keys are written sequentially to SF KEY 1. 
 * Each write to the SFR must be preceded by writing the SF keys to the SF key registers, 
 * in order, SF KEY 1 then SF KEY 2.
 */
void rtc3_set_special_function_key1 ( rtc3_t *ctx, uint8_t sfkey1 );

/**
 * @brief Set special function key byte 2 function
 *
 * @param ctx                         Click object.
 * @param sfkey2                      special function key byte 2
 *
 * @description Function set special function access key byte 2.
 * Reads as 0x00, and key is 0x5E.
 * The SF KEY 2 registers are used to enable access to the main special function register (SFR).
 * Access to SFR is granted only after the special function keys are written sequentially to SF KEY 2.
 * Each write to the SFR must be preceded by writing the SF keys to the SF key registers,
 * in order, SF KEY 1 then SF KEY 2.
 */
void rtc3_set_special_function_key2 ( rtc3_t *ctx, uint8_t sfkey2 );

/**
 * @brief Set frequency calibration control function
 *
 * @param ctx                         Click object.
 * @param ftf                         frequency of the calibration output
 *                   <pre>
 *                    - 0: Normal 512 Hz calibration;
 *                    - 1: 1 Hz calibration;
 *                   </pre>
 *
 * @description Function set force calibration control.
 * FTF allows the frequency of the calibration output to be changed from 512 Hz to 1 Hz. 
 * By default, FTF is cleared, and the RTC outputs a 512-Hz calibration signal. 
 * Setting FTF forces the calibration signal to 1 Hz, 
 * and the calibration tracks the internal ppm adjustment. 
 *
 * @note: The default 512-Hz calibration signal does not include
 * the effect of the ppm adjustment.
 */
void rtc3_set_frequency_calibration( rtc3_t *ctx, uint8_t ftf );

/**
 * @brief Get state of interrupt pin function
 *
 * @param ctx                 Click object.
 * @retval state of INT pin
 *            <pre>
 *            - 0: not active;
 *            - 1: active
 *            </pre>
 *
 * @description Function get state of interrupt ( INT ) pin.
 */
uint8_t rtc3_get_interrupt( rtc3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif  // _RTC3_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
