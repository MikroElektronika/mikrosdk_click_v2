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
 * \brief This file contains API for RTC 8 Click driver.
 *
 * \addtogroup rtc8 RTC 8 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC8_H
#define RTC8_H

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
#define RTC8_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.evi = MIKROBUS( mikrobus, MIKROBUS_CS ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC8_OK                                 0
#define RTC8_ERROR                             -1
/** \} */

/**
 * \defgroup time_read Time read registers
 * \{
 */
#define RTC8_REG_SECONDS                        0x00
#define RTC8_REG_MINUTES                        0x01
#define RTC8_REG_HOURS                          0x02
#define RTC8_REG_WEEKDAY                        0x03
#define RTC8_REG_DATE                           0x04
#define RTC8_REG_MONTH                          0x05
#define RTC8_REG_YEAR                           0x06
#define RTC8_REG_MINUTES_ALARM                  0x07
#define RTC8_REG_HOURS_ALARM                    0x08
#define RTC8_REG_WEEKDAY_ALARM                  0x09
#define RTC8_REG_TIMER_VALUE_0                  0x0A
#define RTC8_REG_TIMER_VALUE_1                  0x0B
#define RTC8_REG_TIMER_STATUS_0                 0x0C
#define RTC8_REG_TIMER_STATUS_1                 0x0D
#define RTC8_REG_STATUS                         0x0E
#define RTC8_REG_CONTROL1                       0x0F
#define RTC8_REG_CONTROL2                       0x10
#define RTC8_REG_GP_BITS                        0x11
#define RTC8_REG_CLOCK_INT_MASK                 0x12
#define RTC8_REG_EVENT_CONTROL                  0x13
#define RTC8_REG_COUNT_TS                       0x14
#define RTC8_REG_SECONDS_TS                     0x15
#define RTC8_REG_MINUTES_TS                     0x16
#define RTC8_REG_HOURS_TS                       0x17
#define RTC8_REG_DATE_TS                        0x18
#define RTC8_REG_MONTH_TS                       0x19
#define RTC8_REG_YEAR_TS                        0x1A
#define RTC8_REG_UNIX0                          0x1B
#define RTC8_REG_UNIX1                          0x1C
#define RTC8_REG_UNIX2                          0x1D
#define RTC8_REG_UNIX3                          0x1E
#define RTC8_REG_USER_RAM_1                     0x1F
#define RTC8_REG_USER_RAM_2                     0x20
#define RTC8_REG_PASSWORD_0                     0x21
#define RTC8_REG_PASSWORD_1                     0x22
#define RTC8_REG_PASSWORD_2                     0x23
#define RTC8_REG_PASSWORD_3                     0x24
#define RTC8_REG_EEPROM_ADDRESS                 0x25
#define RTC8_REG_EEPROM_DATA                    0x26
#define RTC8_REG_EEPROM_COM                     0x27
#define RTC8_REG_ID                             0x28
#define RTC8_REG_EEPROM_BACKUP                  0x37
/** \} */

/**
 * \defgroup status Status registers
 * \{
 */
#define RTC8_STATUS_EEPROM_BUSY                 0x80
#define RTC8_STATUS_CLOCK_INT_FLAG              0x40
#define RTC8_STATUS_BACKUP_SWITCH_FLAG          0x20
#define RTC8_STATUS_UPDATE_FLAG                 0x10
#define RTC8_STATUS_TIMER_FLAG                  0x08
#define RTC8_STATUS_ALARM_FLAG                  0x04
#define RTC8_STATUS_EVENT_FLAG                  0x02
#define RTC8_STATUS_POR_FLAG                    0x01
#define RTC8_STATUS_REG_CLEAR                   0x00
/** \} */

/**
 * \defgroup ctrl1 Ctrl 1 registers
 * \{
 */
#define RTC8_CTRL1_TRPT_SINGLE_MODE             0x00
#define RTC8_CTRL1_TRPT_REPEAT_MODE             0x80
#define RTC8_CTRL1_WADA_WEEKDAY_ALARM           0x00
#define RTC8_CTRL1_WADA_DATE_ALARM              0x20
#define RTC8_CTRL1_USEL_SECOND_UPDATE           0x00
#define RTC8_CTRL1_USEL_MINUTE_UPDATE           0x10
#define RTC8_CTRL1_EERD_REFRESH_ACTIVE          0x00
#define RTC8_CTRL1_EERD_REFRESH_NO_ACTIVE       0x08
#define RTC8_CTRL1_TE_TIMER_STOPS               0x00
#define RTC8_CTRL1_TE_TIMER_STARTS              0x04
#define RTC8_CTRL1_TD_TIMER_CLK_4096Hz          0x00
#define RTC8_CTRL1_TD_TIMER_CLK_64Hz            0x01
#define RTC8_CTRL1_TD_TIMER_CLK_1Hz             0x02
#define RTC8_CTRL1_TD_TIMER_CLK_1_60Hz          0x03
/** \} */

/**
 * \defgroup ctrl2 Ctrl 2 registers
 * \{
 */
#define RTC8_CTRL2_TIME_STAMP_DISABLE           0x00
#define RTC8_CTRL2_TIME_STAMP_ENABLE            0x80
#define RTC8_CTRL2_INT_CLOCK_DISABLE            0x00
#define RTC8_CTRL2_INT_CLOCK_ENABLE             0x40
#define RTC8_CTRL2_TIME_UPDATE_INTERRUPT        0x20
#define RTC8_CTRL2_TIME_UPDATE_NO_INTERRUPT     0x00
#define RTC8_CTRL2_TIMER_INTERRUPT              0x10
#define RTC8_CTRL2_TIMER_NO_INTERRUPT           0x00
#define RTC8_CTRL2_ALARM_INTERRUPT              0x08
#define RTC8_CTRL2_ALARM_NO_INTERRUPT           0x00
#define RTC8_CTRL2_EVENT_INTERRUPT              0x04
#define RTC8_CTRL2_EVENT_NO_INTERRUPT           0x00
#define RTC8_CTRL2_HOUR_MODE_12                 0x02
#define RTC8_CTRL2_HOUR_MODE_24                 0x00
#define RTC8_CTRL2_RESET_ACTIVE                 0x01
#define RTC8_CTRL2_NO_RESET                     0x00
/** \} */

/**
 * \defgroup clock_int_mask Clock Interrupt Mask
 * \{
 */
#define RTC8_CLKIM_EVENT_INT_ENABLE             0x08
#define RTC8_CLKIM_EVENT_INT_DISABLE            0x00
#define RTC8_CLKIM_ALARM_INT_ENABLE             0x04
#define RTC8_CLKIM_ALARM_INT_DISABLE            0x00
#define RTC8_CLKIM_TIMER_INT_ENABLE             0x02
#define RTC8_CLKIM_TIMER_INT_DISABLE            0x00
#define RTC8_CLKIM_TIME_UPDATE_INT_ENABLE       0x01
#define RTC8_CLKIM_TIME_UPDATE_INT_DISABLE      0x00
/** \} */

/**
 * \defgroup event_ctrl Event Control
 * \{
 */
#define RTC8_EC_EVENT_LOW_LEVEL                 0x00
#define RTC8_EC_EVENT_HIGH_LEVEL                0x40
#define RTC8_EC_EVENT_PERIOD_256Hz              0x10
#define RTC8_EC_EVENT_PERIOD_64Hz               0x20
#define RTC8_EC_EVENT_PERIOD_8Hz                0x30
#define RTC8_EC_EVENT_NO_FILTERING              0x00
#define RTC8_EC_TIME_STAMP_RESET_ENABLE         0x04
#define RTC8_EC_TIME_STAMP_RESET_DISABLE        0x00
#define RTC8_EC_TSOW_EVF_CLEARED                0x00
#define RTC8_EC_TSOW_EVF_NO_CLEARED             0x02
#define RTC8_EC_TSS_TSE_ON_EVI                  0x00
#define RTC8_EC_TSS_TSE_ON_VBACKUP              0x01
/** \} */

/**
 * \defgroup eeprom_cmd EEPROM command
 * \{
 */
#define RTC8_EECMD_WRITE_ALL_EEPROM_REG         0x11
#define RTC8_EECMD_READ_ALL_EEPROM_REG          0x12
#define RTC8_EECMD_WRITE_ONE_EEPROM_REG         0x21
#define RTC8_EECMD_READ_ONE_EEPROM_REG          0x22
/** \} */

/**
 * \defgroup active_alarm Active alarm
 * \{
 */
#define RTC8_ALARM_IS_ACTIVE                    0x01
#define RTC8_ALARM_NO_ACTIVE                    0x00
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
    digital_out_t evi;

    // Input pins 
    digital_in_t int_pin;
    
    // Modules 
    i2c_master_t i2c;

    // ctx variable 
    uint8_t slave_address;

} rtc8_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 
    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 
    pin_name_t evi;
    pin_name_t int_pin;

    // static variable 
    uint32_t i2c_speed;
    uint8_t i2c_address;

} rtc8_cfg_t;

/**
 * @brief Time structure definition.
 */
typedef struct
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

} rtc8_time_t;

/**
 * @brief Date structure definition.
 */
typedef struct
{
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t weekdays;

} rtc8_date_t;

/**
 * @brief Alarm structure definition.
 */
typedef struct
{
    uint8_t weekdays;
    uint8_t hours;
    uint8_t minutes;

} rtc8_alarm_t;

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
void rtc8_cfg_setup ( rtc8_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function initializes all necessary pins and peripherals used for this click.
 */
err_t rtc8_init ( rtc8_t *ctx, rtc8_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function executes default configuration for RTC 8 click.
 */
err_t rtc8_default_cfg ( rtc8_t *ctx );

/**
 * @brief Generic write function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Data buf to be written.
 * @param len          Number of the bytes in data buf.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function writes data to the desired register.
 */
err_t rtc8_generic_write ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read function.
 *
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param data_buf     Output data buf
 * @param len          Number of the bytes to be read
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @details This function reads data from the desired register.
 */
err_t rtc8_generic_read ( rtc8_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Write data ( Convert and send data in BCD format )
 *
 * @param ctx          Click object.
 * @param reg          Register Address
 * @param data_in      Data in decimal format
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use this function when you need to write the data in the register in decimal format.
 */
err_t rtc8_write_data ( rtc8_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Read one byte data from register in DEC format
 *
 * @param ctx           Click object.
 * @param reg           Register Address
 * @param data_out      Data output in decimal format
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Use this function when you need to read the register with converting data from BCD format to DEC format.
 */
err_t rtc8_read_data ( rtc8_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Get current UNIX time
 *
 * @param ctx           Click object.
 * @param unix_time     UNIX time.
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtc8_get_uinx_time ( rtc8_t *ctx, uint32_t *unix_time );

/**
 * @brief Set UNIX time
 *
 * @param ctx           Click object.
 * @param unix_time     4 byte unix time
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtc8_set_unix_time ( rtc8_t *ctx, uint32_t unix_time );

/**
 * @brief Set new time - 24 hour format
 *
 * @param ctx           Click object.
 * @param time_s        Time Structure ( New Hours (0 - 23), New minutes (0 - 59), New secconds (0 - 59) )
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If no new time is set - RTC continues to count where it stopped.
 */
err_t rtc8_set_time ( rtc8_t *ctx, rtc8_time_t *time_s );

/**
 * @brief Set new date
 *
 * @param ctx           Click object.
 * @param date_s        Date Structure ( New Hours (0 - 31), New minutes (1 - 12), New secconds (0 - 99) 
 *                                       2000 year ... 2099 year)
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note If no new date is set - RTC continues to count where it stopped.
 */
err_t rtc8_set_date ( rtc8_t *ctx, rtc8_date_t *date_s );

/**
 * @brief Set Alarm
 *
 * @param ctx           Click object.
 * @param alarm_s       Alarm Structure ( weekdays, hours, minutes )
 *
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note Set the time at which the alarm active
 */
err_t rtc8_set_alarm ( rtc8_t *ctx, rtc8_alarm_t *alarm_s );

/**
 * @brief Get interrupt state
 *
 * @param ctx           Click object.
 *
 * @return Interrupt pin state
 */
uint8_t rtc8_get_int_pin ( rtc8_t *ctx );

/**
 * @brief Set EVI(External Event Input) pin
 *
 * @param ctx           Click object.
 * @param state         - EVI state
 */
void rtc8_set_evi_pin ( rtc8_t *ctx, uint8_t state );

/**
 * @brief Get RTC data ( Time and Data )
 *
 * @param ctx           Click object.
 * @param time_s        Time Structure ( New Hours (0 - 23), New minutes (0 - 59), New secconds (0 - 59) )
 * @param date_s        Date Structure ( New Hours (0 - 31), New minutes (1 - 12), New secconds (0 - 99)
 *                                       2000 year ... 2099 year)
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtx8_get_time_and_date ( rtc8_t *ctx, rtc8_time_t *time_s, rtc8_date_t *date_s );

/**
 * @brief Reset alarm
 *
 * @param ctx          Click object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtc8_reset_alarm_flag ( rtc8_t *ctx );

/**
 * @brief Get status
 *
 * @param ctx           Click object.
 * @param status        Status register data
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtc8_get_status ( rtc8_t *ctx, uint8_t *status );

/**
 * @brief Get Alarm flag
 *
 * @param ctx           Click object.
 * @param alarm_flag    Alarm flage ( ALARM IS ACTIVE or ALARM ISN'T ACTIVE)
 * 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
err_t rtc8_get_alarm_flag ( rtc8_t *ctx, uint8_t *alarm_flag );

#ifdef __cplusplus
}
#endif
#endif  // _RTC8_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
