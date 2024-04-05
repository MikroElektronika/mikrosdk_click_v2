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
 * \brief This file contains API for RTC2 Click driver.
 *
 * \addtogroup rtc2 RTC2 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC2_H
#define RTC2_H

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
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
#define RTC2_MAP_MIKROBUS( cfg, mikrobus ) \
  cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
  cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
  cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC2_RETVAL  uint8_t

#define RTC2_OK           0x00
#define RTC2_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup register_address  Register address
 * \{
 */
#define RTC2_I2C_ADDRESS                                           0x68
#define RTC2_REG_TIME_SEC                                          0x00
#define RTC2_REG_TIME_MIN                                          0x01
#define RTC2_REG_TIME_HOUR                                         0x02
#define RTC2_REG_TIME_DAY_OF_THE_WEEK                              0x03
#define RTC2_REG_TIME_DATE_DAY                                     0x04
#define RTC2_REG_TIME_DATE_MONTH                                   0x05
#define RTC2_REG_TIME_DATE_YEAR                                    0x06
#define RTC2_REG_CONTROL                                           0x07
/** \} */

/**
 * \defgroup configuration_bits Configuration bits
 * \{
 */
#define RTC2_ENABLE_COUNTING                                       0x7F
#define RTC2_DISABLE_COUNTING                                      0x80
#define RTC2_CONFIG_RATE_LOW                                       0x00
#define RTC2_CONFIG_RATE_HIGH                                      0x80
#define RTC2_CONFIG_RATE_SELECT_1_HZ                               0x10
#define RTC2_CONFIG_RATE_SELECT_4_096_kHZ                          0x11
#define RTC2_CONFIG_RATE_SELECT_8_192_kHZ                          0x12
#define RTC2_CONFIG_RATE_SELECT_32_768_kHZ                         0x13
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

    // Input pins 

    digital_in_t int_pin;
    
    // Modules 

    i2c_master_t i2c;

    // ctx variable 

    uint8_t slave_address;

} rtc2_t;

/**
 * @brief Data structure definition.
 */
typedef struct
{
    uint8_t day_of_the_week;
    uint8_t date_day;
    uint8_t date_month;
    uint16_t date_year;
} rtc2_data_t;

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

} rtc2_cfg_t;

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
void rtc2_cfg_setup ( rtc2_cfg_t *cfg );

/**
 * @brief Initialization function.
 *
 * @param ctx Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC2_RETVAL rtc2_init ( rtc2_t *ctx, rtc2_cfg_t *cfg );

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
void rtc2_generic_write ( rtc2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

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
void rtc2_generic_read ( rtc2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

/**
 * @brief Generic read byte of data function.
 * 
 * @param ctx          Click object.
 * @param reg_address  Register address.
 *
 * @description Function read the 8-bit of data from the
 * target 8-bit register address of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_read_byte ( rtc2_t *ctx, uint8_t reg_address );

/**
 * @brief Generic write byte of data function.
 * 
 * @param ctx          Click object.
 * @param reg          Register address.
 * @param write_data   Byte of data to write.
 *
 * @description Function write the 8-bit of data to the
 * target 8-bit register address of DS1307 chip on RTC 2 Click.
 */
 void rtc2_write_byte ( rtc2_t *ctx, uint8_t reg_address, uint8_t write_data );

 /**
 * @brief Enable counting function.
 * 
 * @param ctx          Click object.
 * @description Function enable counting on RTC 2 Click.
 */
 void rtc2_enable_counting ( rtc2_t *ctx );

 /**
 * @brief Disable counting function.
 * 
 * @param ctx          Click object.
 *
 * @description Function disable counting on RTC 2 Click.
 */
 void rtc2_disable_counting ( rtc2_t *ctx );

 /**
 * @brief Get seconds function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets seconds data from the target register address
 * ( 0x00 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_time_seconds ( rtc2_t *ctx ) ;

 /**
 * @brief Set seconds function.
 * 
 * @param ctx          Click object.
 * @param seconds      Time seconds. 
 *
 * @description Function sets seconds data to the target register address
 * ( 0x00 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_time_seconds ( rtc2_t *ctx, uint8_t seconds );

 /**
 * @brief Get hours function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets hours data from the target register address
 * ( 0x02 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_time_minutes ( rtc2_t *ctx );

 /**
 * @brief Set minutes function.
 * 
 * @param ctx          Click object.
 * @param minutes      Time minutes.
 *
 * @description  Function sets minutes data to the target register address
 * ( 0x01 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_time_minutes ( rtc2_t *ctx, uint8_t minutes );

 /**
 * @brief Set hours function.
 * 
 * @param ctx          Click object.
 *
 * @description Function sets hours data to the target register address
 * ( 0x02 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_time_hours ( rtc2_t *ctx );

 /**
 * @brief Set hours function.
 * 
 * @param ctx          Click object.
 * @param hours        Time hours.
 *
 * @description  Function sets hours data to the target register address
 * ( 0x02 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_time_hours ( rtc2_t *ctx, uint8_t hours );

 /**
 * @brief Set day of the week function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets day of the week data from tne target register address
 * ( 0x03 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_day_of_the_week ( rtc2_t *ctx );

 /**
 * @brief Generic read function.
 * 
 * @param ctx          Click object.
 * @param w_day        Day of the week data.
 *
 * @description Function sets day of the week data to the target register address
 * ( 0x03 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_day_of_the_week ( rtc2_t *ctx, uint8_t w_day );

 /**
 * @brief Get day function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets day data from the target register address
 * ( 0x04 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_date_day ( rtc2_t *ctx );

 /**
 * @brief Set day function
 * 
 * @param ctx          Click object.
 * @param date_day     Date day data.
 *
 * @description Function sets day data from the target register address
 * ( 0x04 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_date_day ( rtc2_t *ctx, uint8_t date_day );

 /**
 * @brief Get month function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets month data from the target register address
 * ( 0x05 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_date_month ( rtc2_t *ctx );

 /**
 * @brief Set month function.
 * 
 * @param ctx          Click object.
 * @param date_month   Date month data.
 *
 * @description Function sets month data from the target register address
 * ( 0x05 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_date_month ( rtc2_t *ctx, uint8_t date_month );

/**
 * @brief Get year function.
 * 
 * @param ctx          Click object.
 *
 * @description Function gets year data from the target register address
 * ( 0x06 ) of DS1307 chip on RTC 2 Click.
 */
 uint8_t rtc2_get_date_year ( rtc2_t *ctx );

 /**
 * @brief Set year function.
 * 
 * @param ctx          Click object.
 * @param date_year    Date year data.
 *
 * @description Function sets year data from the target register address
 * ( 0x06 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_date_year ( rtc2_t *ctx, uint16_t date_year );

 /**
 * @brief Set time hours, minutes and seconds function.
 * 
 * @param ctx          Click object.
 * @param time_hours   Time hours.
 * @param time_minutes Time minutes.
 * @param time_seconds Time seconds.
 *
 * @description Function sets time: hours, minutes and seconds data to
 * the target register address ( 0x00, 0x01 & 0x02 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_time ( rtc2_t *ctx, uint8_t time_hours, uint8_t time_minutes, uint8_t time_seconds );

 /**
 * @brief Get time hours, minutes and seconds function.
 *
 * @param ctx          Click object.
 * @param time_hours   Pointer of time hours.
 * @param time_minutes Pointer of time minutes.
 * @param time_seconds Pointer of time seconds.
 *
 * @description Function gets time: hours, minutes and seconds data from
 * the target register address ( 0x00, 0x01 & 0x02 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_get_time ( rtc2_t *ctx, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

 /**
 * @brief Generic read function.
 * 
 * @param ctx                Click object.
 * @param date               Date parameters.
 *
 * @description Function sets date: day of the week, day, month and year data to
 * the target register address ( 0x03, 0x04, 0x05 & 0x06 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_date ( rtc2_t *ctx, rtc2_data_t *date );

 /**
 * @brief Generic read function.
 * 
 * @param ctx                Click object.
 * @param data               Data parameters.
 *
 * @description Function gets date: day of the week, day, month and year data from
 * the target register address ( 0x03, 0x04, 0x05 & 0x06 ) of DS1307 chip on RTC 2 Click.
 */
 void rtc2_get_date ( rtc2_t *ctx, rtc2_data_t *date );

 /**
 * @brief Set frequency of square-wave output function.
 * 
 * @param ctx          Click object.
 * @param rate_select  Rate selection of frequency of SQWE.
 *
 * @description Function set frequency of square-wave output of DS1307 chip on RTC 2 Click.
 */
 void rtc2_set_frequency_sqwe ( rtc2_t *ctx, uint8_t rate_select );


#ifdef __cplusplus
}
#endif
#endif  // _RTC2_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
