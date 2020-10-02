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
 * \brief This file contains API for RTC 9 Click driver.
 *
 * \addtogroup rtc9 RTC 9 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC9_H
#define RTC9_H

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
#define RTC9_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC9_RETVAL  uint8_t

#define RTC9_OK           0x00
#define RTC9_INIT_ERROR   0xFF
/** \} */
 
/**
 * \defgroup slave_addr  Slave Addr
 * \{
 */
#define RTC9_SLAVE_ADDRESS             0x68
/** \} */
 
/**
 * \defgroup registers  Registers
 * \{
 */
#define RTC9_REG_PART_SECONDS          0x00
#define RTC9_REG_SECONDS               0x01
#define RTC9_REG_MINUTES               0x02
#define RTC9_REG_CENTURY_HOURS         0x03
#define RTC9_REG_DAY                   0x04
#define RTC9_REG_DATE                  0x05
#define RTC9_REG_MONTH                 0x06
#define RTC9_REG_YEAR                  0x07
#define RTC9_REG_DIGITAL_CALIBRATION   0x08
#define RTC9_REG_WATCHDOG              0x09
#define RTC9_REG_ALARM1_MONTH          0x0A
#define RTC9_REG_ALARM1_DATE           0x0B
#define RTC9_REG_ALARM1_HOUR           0x0C
#define RTC9_REG_ALARM1_MINUTES        0x0D
#define RTC9_REG_ALARM1_SECONDS        0x0E
#define RTC9_REG_FLAGS                 0x0F
#define RTC9_REG_TIMER_VALUE           0x10
#define RTC9_REG_TIMER_CONTROL         0x11
#define RTC9_REG_ANALOG_CALIBRATION    0x12
#define RTC9_REG_SQW                   0x13
#define RTC9_REG_ALARM2_MONTH          0x14
#define RTC9_REG_ALARM2_DATE           0x15
#define RTC9_REG_ALARM2_HOUR           0x16
#define RTC9_REG_ALARM2_MINUTES        0x17
#define RTC9_REG_ALARM2_SECONDS        0x18
/** \} */
 
/**
 * \defgroup flag_registers  Flag Registers
 * \{
 */
#define RTC9_FLAG_WATCHDOG_ENABLE          0x80
#define RTC9_FLAG_WATCHDOG_DISABLE         0x00
#define RTC9_FLAG_ALARM_1_ENABLE           0x40
#define RTC9_FLAG_ALARM_1_DISABLE          0x00
#define RTC9_FLAG_ALARM_2_ENABLE           0x20
#define RTC9_FLAG_ALARM_2_DISABLE          0x00
#define RTC9_FLAG_BATTERY_LOW_ENABLE       0x10
#define RTC9_FLAG_BATTERY_LOW_DISABLE      0x00
#define RTC9_FLAG_TIMER_ENABLE             0x08
#define RTC9_FLAG_TIMER_DISABLE            0x00
#define RTC9_FLAG_OSCILATOR_FAIL_ENABLE    0x04
#define RTC9_FLAG_OSCILATOR_FAIL_DISABLE   0x00
/** \} */
 
/**
 * \defgroup time_control  Time Control
 * \{
 */
#define RTC9_TIMER_CONTROL_ENABLE                       0x80
#define RTC9_TIMER_CONTROL_DISABLE                      0x00
#define RTC9_TIMER_CONTROL_NORMAL_INT                   0x00
#define RTC9_TIMER_CONTROL_FREE_RUNNING_INT             0x40
#define RTC9_TIMER_CONTROL_INT_OUT_ASSERT               0x20
#define RTC9_TIMER_CONTROL_INT_OUT_DE_ASSERT            0x00
#define RTC9_TIMER_CONTROL_TIMER_SOURCE_FREQ_244p1_US   0x00
#define RTC9_TIMER_CONTROL_TIMER_SOURCE_FREQ_15p6_MS    0x01
#define RTC9_TIMER_CONTROL_TIMER_SOURCE_FREQ_1_S        0x02
#define RTC9_TIMER_CONTROL_TIMER_SOURCE_FREQ_60_S       0x03
/** \} */
 
/**
 * \defgroup analog_calibration  Analog Calibration
 * \{
 */
#define RTC9_ANALOG_CALIBRATION_OSCILATOR_FREQ_NORMAL   0x00
#define RTC9_ANALOG_CALIBRATION_OSCILATOR_FREQ_SLOW     0x27
#define RTC9_ANALOG_CALIBRATION_OSCILATOR_FREQ_FAST     0xC8
/** \} */
 
/**
 * \defgroup digital_calibration  Digital Calibration
 * \{
 */
#define RTC9_DIGITAL_CALIBRATION_POSITIVE               0x20
#define RTC9_DIGITAL_CALIBRATION_NEGATIVE               0x00
#define RTC9_DIGITAL_CALIBRATION_FREQ_TEST_ENABLED      0x40
#define RTC9_DIGITAL_CALIBRATION_FREQ_TEST_DISABLED     0x00
#define RTC9_DIGITAL_CALIBRATION_VALUE_0                0x00
#define RTC9_DIGITAL_CALIBRATION_VALUE_1                0x01
#define RTC9_DIGITAL_CALIBRATION_VALUE_2                0x02
#define RTC9_DIGITAL_CALIBRATION_VALUE_3                0x03
#define RTC9_DIGITAL_CALIBRATION_VALUE_4                0x04
#define RTC9_DIGITAL_CALIBRATION_VALUE_5                0x05
#define RTC9_DIGITAL_CALIBRATION_VALUE_6                0x06
#define RTC9_DIGITAL_CALIBRATION_VALUE_7                0x07
#define RTC9_DIGITAL_CALIBRATION_VALUE_8                0x08
#define RTC9_DIGITAL_CALIBRATION_VALUE_9                0x09
#define RTC9_DIGITAL_CALIBRATION_VALUE_10               0x0A
#define RTC9_DIGITAL_CALIBRATION_VALUE_11               0x0B
#define RTC9_DIGITAL_CALIBRATION_VALUE_12               0x0C
#define RTC9_DIGITAL_CALIBRATION_VALUE_13               0x0D
#define RTC9_DIGITAL_CALIBRATION_VALUE_14               0x0E
#define RTC9_DIGITAL_CALIBRATION_VALUE_15               0x0F
#define RTC9_DIGITAL_CALIBRATION_VALUE_16               0x10
#define RTC9_DIGITAL_CALIBRATION_VALUE_17               0x11
#define RTC9_DIGITAL_CALIBRATION_VALUE_18               0x12
#define RTC9_DIGITAL_CALIBRATION_VALUE_19               0x13
#define RTC9_DIGITAL_CALIBRATION_VALUE_20               0x14
#define RTC9_DIGITAL_CALIBRATION_VALUE_21               0x15
#define RTC9_DIGITAL_CALIBRATION_VALUE_22               0x16
#define RTC9_DIGITAL_CALIBRATION_VALUE_23               0x17
#define RTC9_DIGITAL_CALIBRATION_VALUE_24               0x18
#define RTC9_DIGITAL_CALIBRATION_VALUE_25               0x19
#define RTC9_DIGITAL_CALIBRATION_VALUE_26               0x1A
#define RTC9_DIGITAL_CALIBRATION_VALUE_27               0x1B
#define RTC9_DIGITAL_CALIBRATION_VALUE_28               0x1C
#define RTC9_DIGITAL_CALIBRATION_VALUE_29               0x1D
#define RTC9_DIGITAL_CALIBRATION_VALUE_30               0x1E
#define RTC9_DIGITAL_CALIBRATION_VALUE_31               0x1F
/** \} */
 
/**
 * \defgroup watchdog  Watchdog
 * \{
 */
#define RTC9_WATCHDOG_OSCILATOR_FAIL_ENABLED            0x80
#define RTC9_WATCHDOG_OSCILATOR_FAIL_DISABLED           0x00
#define RTC9_WATCHDOG_RESOLUTION_1_DIV_16_SEC           0x00
#define RTC9_WATCHDOG_RESOLUTION_1_DIV_4_SEC            0x01
#define RTC9_WATCHDOG_RESOLUTION_1_SEC                  0x02
#define RTC9_WATCHDOG_RESOLUTION_4_SEC                  0x03
/** \} */
 
/**
 * \defgroup months  Months
 * \{
 */
#define RTC9_MONTH_JANUARY                              0x01
#define RTC9_MONTH_FEBRUARY                             0x02
#define RTC9_MONTH_MARCH                                0x03
#define RTC9_MONTH_APRIL                                0x04
#define RTC9_MONTH_MAY                                  0x05
#define RTC9_MONTH_JUNE                                 0x06
#define RTC9_MONTH_JULY                                 0x07
#define RTC9_MONTH_AUGUST                               0x08
#define RTC9_MONTH_SEPTEMBER                            0x09
#define RTC9_MONTH_OCTOBER                              0x0A
#define RTC9_MONTH_NOVEMBER                             0x0B
#define RTC9_MONTH_DECEMBER                             0x0C
/** \} */
 
/**
 * \defgroup day_of_week  Day of week
 * \{
 */
#define RTC9_DAY_SUNDAY                                 0x01
#define RTC9_DAY_MONDAY                                 0x02
#define RTC9_DAY_TUESDAY                                0x03
#define RTC9_DAY_WEDNESDAY                              0x04
#define RTC9_DAY_THURSDAY                               0x05
#define RTC9_DAY_FRIDAY                                 0x06
#define RTC9_DAY_SATURDAY                               0x07
/** \} */
 
/** \} */ // End group macro 
// --------------------------------------------------------------- PUBLIC TYPES
/**
 * \defgroup type Types
 * \{
 */

typedef struct
{
    uint8_t day;
    uint8_t day_of_week; 
    uint8_t month; 
    uint8_t year;

} rtc9_set_data_t;

typedef struct 
{
    uint8_t hour; 
    uint8_t min;
    uint8_t sec; 
    uint8_t part_sec;

} rtc9_get_time_t;

typedef struct 
{
    uint8_t day;
    uint8_t day_of_week; 
    uint8_t month; 
    uint8_t year;

} rtc9_get_date_t;

/**
 * @brief Click ctx object definition.
 */
typedef struct
{
    // Output pins 

    digital_out_t rst;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

    rtc9_set_data_t set_data;
    rtc9_get_time_t get_time;
    rtc9_get_date_t get_date;

} rtc9_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t scl;
    pin_name_t sda;
    
    // Additional gpio pins 

    pin_name_t rst;

    // static variable 

    uint32_t i2c_speed;
    uint8_t i2c_address;

} rtc9_cfg_t;

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
void rtc9_cfg_setup ( rtc9_cfg_t *cfg );

/**
 * @brief Initialization function.
 * 
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC9_RETVAL rtc9_init ( rtc9_t *ctx, rtc9_cfg_t *cfg );

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
void rtc9_generic_write ( rtc9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void rtc9_generic_read ( rtc9_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Wake-up process
 *
 * @param rtc9 Click object.
 * 
 * @note This function must be called at the start of the program
 */
void rtc9_wakeup ( rtc9_t *ctx );

/**
 * @brief Software reset
 * 
 * @param rtc9 Click object.
 * 
 */
void rtc9_software_reset( rtc9_t *ctx ) ;

/**
 * @brief Hardware reset
 * 
 * @param rtc9 Click object.
 * 
 */
void rtc9_hardware_reset ( rtc9_t *ctx );

/**
 * @brief Set new time - 24 hour format
 *
 * @param rtc9 Click object.
 * @param hour        New Hours (0 - 23)
 * @param min         New minutes (0 - 59)
 * @param sec         New secconds (0 - 59)
 */
void rtc9_set_time( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec );

/**
 * @brief Set new date
 *
 * @param rtc9 Click object.
 * @param set_data Struct object.
 *
 */
void rtc9_set_date ( rtc9_t *ctx, rtc9_set_data_t *set_data );

/**
 * @brief Get new time - 24 hour format
 *
 * @param rtc9       Click object.
 * @param get_time   Struct object.
 * 
 */
void rtc9_get_time( rtc9_t *ctx, rtc9_get_time_t *get_time );

/**
 * @brief Get new date
 *
 * @param rtc9      Click object.
 * @param get_data  Struct object.
 * 
 */
void rtc9_get_date( rtc9_t *ctx, rtc9_get_date_t *get_data );

/**
 * @brief Month in the String format
 *
 * @param month         Current month
 * 
 * @return pointer to string... ( 1 = January... )
 */
char *rtc9_current_month( uint8_t month );

/**
 * @brief Day of Week in the String format
 *
 * @param day_of_week    Current dey of week
 * 
 * @return pointer to string... ( 1 = Sunday... )
 */
char *rtc9_current_day_of_week( uint8_t day_of_week );

/**
 * @brief Set new ALARM 1 time - 24 hour format
 *
 * @param rtc9        Click object.
 * @param hour        New Hours (0 - 23)
 * @param min         New minutes (0 - 59)
 * @param sec         New secconds (0 - 59)
 */
void rtc9_set_alarm_time( rtc9_t *ctx, uint8_t hour, uint8_t min, uint8_t sec );

/**
 * @brief Set new ALARM 1 date
 *
 * @param rtc9          Click object.
 * @param day           New Day (1 - 31/30/28/29)
 * @param month         New month (1 - 12)
 * @param year          New year (0 - 99) 2000 year ... 2099 year
 */
void rtc9_set_alarm_date ( rtc9_t *ctx, uint8_t day, uint8_t month, uint8_t year );

/**
 * @brief Reads FLAGS regiter
 *
 * @param rtc9        Click object.
 * @param read_data   Data to be read.
 * 
 */
void rtc9_read_flag_status ( rtc9_t *ctx, uint8_t *read_data );

#ifdef __cplusplus
}
#endif
#endif  // _RTC9_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
