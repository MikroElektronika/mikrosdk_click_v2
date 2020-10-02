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
 * \brief This file contains API for RTC5 Click driver.
 *
 * \addtogroup rtc5 RTC5 Click Driver
 * @{
 */
// ----------------------------------------------------------------------------

#ifndef RTC5_H
#define RTC5_H

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_spi_master.h"


// -------------------------------------------------------------- PUBLIC MACROS 
/**
 * \defgroup macros Macros
 * \{
 */

/**
 * \defgroup map_mikrobus MikroBUS
 * \{
 */

#define RTC5_MAP_MIKROBUS( cfg, mikrobus )          \
   cfg.miso  = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
   cfg.mosi  = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
   cfg.sck   = MIKROBUS( mikrobus, MIKROBUS_SCK );  \
   cfg.cs    = MIKROBUS( mikrobus, MIKROBUS_CS );   \
   cfg.mfp = MIKROBUS( mikrobus, MIKROBUS_INT );
/** \} */

/**
 * \defgroup error_code Error Code
 * \{
 */
#define RTC5_RETVAL  uint8_t

#define RTC5_OK           0x00
#define RTC5_INIT_ERROR   0xFF
/** \} */

/**
 * \defgroup reg Register address
 * \{
 */
#define RTC5_REG_TIME_HUN_OF_SEC                                0x00
#define RTC5_REG_TIME_SEC                                       0x01
#define RTC5_REG_TIME_MIN                                       0x02
#define RTC5_REG_TIME_HOUR                                      0x03
#define RTC5_REG_TIME_DAY_OF_THE_WEEK                           0x04
#define RTC5_REG_TIME_DATE_DAY                                  0x05
#define RTC5_REG_TIME_DATE_MONTH                                0x06
#define RTC5_REG_TIME_DATE_YEAR                                 0x07
#define RTC5_REG_CONFIG                                         0x08
#define RTC5_REG_CALIBRATION                                    0x09
#define RTC5_REG_ALARM_0_SEC                                    0x0C
#define RTC5_REG_ALARM_0_MIN                                    0x0D
#define RTC5_REG_ALARM_0_HOUR                                   0x0E
#define RTC5_REG_ALARM_0_DATE_DATE                              0x0F
#define RTC5_REG_ALARM_0_DATE_DAY                               0x10
#define RTC5_REG_ALARM_0_MONTH                                  0x11
#define RTC5_REG_ALARM_1_HUN_OF_SEC                             0x12
#define RTC5_REG_ALARM_1_SEC                                    0x13
#define RTC5_REG_ALARM_1_MIN                                    0x14
#define RTC5_REG_ALARM_1_HOUR                                   0x15
#define RTC5_REG_ALARM_1_DATE_DATE                              0x16
#define RTC5_REG_ALARM_1_DATE_DAY                               0x17
/** \} */

/**
 * \defgroup alarm_val Alarm value
 * \{
 */
#define RTC5_ALARM_0_VALUE                                      0x00
#define RTC5_ALARM_1_VALUE                                      0x01
/** \} */

/**
 * \defgroup spi_cmd SPI read/write command
 * \{
 */
#define RTC5_SPI_WRITE                                          0x12
#define RTC5_SPI_READ                                           0x13
/** \} */

/**
 * \defgroup en_osc Enable oscilator
 * \{
 */
#define RTC5_OSC_DISABLE                                        0x00
#define RTC5_OSC_ENABLE                                         0x01
/** \} */

/**
 * \defgroup set_count Set counting status
 * \{
 */
#define RTC5_COUNTING_DISABLE                                   0x7F
#define RTC5_COUNTING_ENABLE                                    0x80
/** \} */

/**
 * \defgroup clr_cmd Clear register command
 * \{
 */
#define RTC5_CLR_CMD                                           0x54
/** \} */

/**
 * \defgroup w_day day of the week
 * \{
 */
#define RTC5_DAY_OF_THE_WEEK_MONDAY                             1
#define RTC5_DAY_OF_THE_WEEK_TUESDAY                            2
#define RTC5_DAY_OF_THE_WEEK_WEDNESDAY                          3
#define RTC5_DAY_OF_THE_WEEK_THURSDAY                           4
#define RTC5_DAY_OF_THE_WEEK_FRIDAY                             5
#define RTC5_DAY_OF_THE_WEEK_SATURDAY                           6
#define RTC5_DAY_OF_THE_WEEK_SUNDAY                             7
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
    digital_out_t cs;

    // Input pins 

    digital_in_t mfp;
    
    // Modules 

    spi_master_t spi;
    pin_name_t chip_select;

} rtc5_t;

/**
 * @brief Click configuration structure definition.
 */
typedef struct
{
    // Communication gpio pins 

    pin_name_t miso;
    pin_name_t mosi;
    pin_name_t sck;
    pin_name_t cs;

    // Additional gpio pins 

    pin_name_t mfp;

    // static variable 

    uint32_t spi_speed;
    spi_master_mode_t   spi_mode;
    spi_master_chip_select_polarity_t cs_polarity;

} rtc5_cfg_t;

/**
 * @brief Time and date structure definition.
 */
typedef struct
{
    // Time 

    uint8_t hun_of_sec;
    uint8_t sec;
    uint8_t min;
    uint8_t hours;

    // Date

    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t w_day;

} rtc5_timedate_t;

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
void rtc5_cfg_setup ( rtc5_cfg_t *cfg );

/**
 * @brief Initialization function.
 * @param rtc5 Click object.
 * @param cfg Click configuration structure.
 * 
 * @description This function initializes all necessary pins and peripherals used for this click.
 */
RTC5_RETVAL rtc5_init ( rtc5_t *ctx, rtc5_cfg_t *cfg );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx  Click object.
 *
 * @description This function executes default configuration for RTC5 click.
 *  * @note
 * Set time and date:
 * -------------------
 * <pre>
 *     Time : 00:00:00
 * </pre>
 * <pre>
 *     Date : 01.01.2000.
 * </pre>
 * <pre>
 *     Day of the week : Saturday
 * </pre>
 */
void rtc5_default_cfg ( rtc5_t *ctx );

/**
 * @brief Generic transfer function.
 *
 * @param ctx          Click object.
 * @param wr_buf       Write data buffer
 * @param wr_len       Number of byte in write data buffer
 * @param rd_buf       Read data buffer
 * @param rd_len       Number of byte in read data buffer
 *
 * @description Generic SPI transfer, for sending and receiving packages
 */
void rtc5_generic_transfer 
( 
    rtc5_t *ctx, 
    uint8_t *wr_buf, 
    uint16_t wr_len, 
    uint8_t *rd_buf, 
    uint16_t rd_len 
);

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx      Click object.
 * @param reg      Register address.
 * @param tx_data  Data to be written.
 *
 * @description This function executes write the 8-bit of data to the
 * target 8-bit register address of MCP79510 chip on RTC 5 Click.
 */
void rtc5_generic_write ( rtc5_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Click Default Configuration function.
 *
 * @param ctx      Click object.
 * @param reg      Register address.
 * 
 * @return  
 * Read data.
 *
 * @description This function executes read the 8-bit of data from the
 * target 8-bit register address of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_generic_read ( rtc5_t *ctx, uint8_t reg );

/**
 * @brief Enable counting function.
 *
 * @param ctx      Click object.
 * @param en_osc   Enable oscilator.
 *
 * @description This function executes enable or disable counting on RTC 5 Click.
 */
void rtc5_set_counting ( rtc5_t *ctx, uint8_t en_osc );

/**
 * @brief Clear RTCC and SRAM memory function.
 *
 * @param ctx      Click object.
 *
 * @description This function executes clear RTCC and SRAM memory
 * of MCP79510 chip on RTC 5 Click.
 */
void rtc5_clear ( rtc5_t *ctx );

/**
 * @brief Set hundred of seconds function.
 *
 * @param ctx      Click object.
 * @param hun_sec  Time: hundred of seconds [ 0 hs : 99 hs ].
 *
 * @description This function sets hundred of seconds value 
 * to the target register address
 * ( 0x00 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_time_hun_of_sec ( rtc5_t *ctx, uint8_t hun_sec );

/**
 * @brief Get hundred of seconds function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Time : hundred of second [ 0 hs : 59 hs ]
 *
 * @description This function gets hundred of second data 
 * from the target register address
 * ( 0x00 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_time_hun_of_sec ( rtc5_t *ctx );

/**
 * @brief Set seconds function.
 *
 * @param ctx      Click object.
 * @param seconds  Time seconds [ 0 sec : 59 sec ]
 *
 * @description This function sets seconds value 
 * to the target register address
 * ( 0x01 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_time_sec ( rtc5_t *ctx, uint8_t seconds );

/**
 * @brief Get seconds function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Time : seconds [ 0 sec : 59 sec ]
 *
 * @description This function gets seconds data 
 * from the target register address
 * ( 0x01 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_time_sec ( rtc5_t *ctx );

/**
 * @brief Set minutes function.
 *
 * @param ctx      Click object.
 * @param minutes  Time minutes [ 0 min : 59 min ]
 *
 * @description This function sets minutes value 
 * to the target register address
 * ( 0x02 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_time_min ( rtc5_t *ctx, uint8_t minutes );

/**
 * @brief Get minutes function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Time : minutes [ 0 sec : 59 sec ]
 *
 * @description This function gets minutes data 
 * from the target register address
 * ( 0x02 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_time_min ( rtc5_t *ctx );

/**
 * @brief Set hours function.
 *
 * @param ctx      Click object.
 * @param hours    Time hours [ 0 h : 23 h ]
 *
 * @description This function sets hours value 
 * to the target register address
 * ( 0x03 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_time_hours ( rtc5_t *ctx, uint8_t hours );

/**
 * @brief Get hours function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Time : hours [ 0 sec : 59 sec ]
 *
 * @description This function gets hours data 
 * from the target register address
 * ( 0x03 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_time_hours ( rtc5_t *ctx );

/**
 * @brief Set day of the week function.
 *
 * @param ctx      Click object.
 * @param wDay     
 * Day of the week data [ 1 : 7 ]
 * - 1 : Monday;
 * - 2 : Tuesday;
 * - 3 : Wednesday;
 * - 4 : Thursday;
 * - 5 : Friday;
 * - 6 : Saturday;
 * - 7 : Sunday;
 *
 * @description This function sets day of the week data
 * to the target register address
 * ( 0x04 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_day_of_the_week ( rtc5_t *ctx, uint8_t w_day );

/**
 * @brief Get day of the week function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Day of the week [ 1 : 7 ]
 *
 * @description This function gets day of the week data 
 * from the target register address
 * ( 0x04 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_day_of_the_week ( rtc5_t *ctx );

/**
 * @brief Set day function.
 *
 * @param ctx         Click object.
 * @param date_day    Date day data [ 1 : 31 ]
 *
 * @description This function sets day data 
 * from the target register address
 * ( 0x05 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_date_day ( rtc5_t *ctx, uint8_t date_day );

/**
 * @brief Get day function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Day [ 1 : 31 ]
 *
 * @description This function gets day data 
 * from the target register address
 * ( 0x05 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_date_day ( rtc5_t *ctx );

/**
 * @brief Set month function.
 *
 * @param ctx           Click object.
 * @param date_month    Date month data [ 1 : 31 ]
 *
 * @description This function sets month data 
 * from the target register address
 * ( 0x06 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_date_month ( rtc5_t *ctx, uint8_t date_month );

/**
 * @brief Get month function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Month [ 1 : 12 ]
 *
 * @description This function gets month data 
 * from the target register address
 * ( 0x06 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_date_month ( rtc5_t *ctx );

/**
 * @brief Get leap year function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * - 0 : not leap year
 * - 1 : leap year
 *
 * @description This function gets leap year data 
 * from the target register address
 * ( 0x06 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_leap_year ( rtc5_t *ctx );

/**
 * @brief Set year function.
 *
 * @param ctx           Click object.
 * @param date_year     Date year data [ 00 : 99 ]
 *
 * @description This function sets year data
 * from the target register address
 * ( 0x07 ) of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_date_year ( rtc5_t *ctx, uint16_t date_year );

/**
 * @brief Get year function.
 *
 * @param ctx      Click object.
 *
 * @return 
 * Year [ 00 : 99 ]
 *
 * @description This function gets year data 
 * from the target register address
 * ( 0x07 ) of MCP79510 chip on RTC 5 Click.
 */
uint8_t rtc5_get_date_year ( rtc5_t *ctx );

/**
 * @brief Set time hours, minutes and seconds function
 *
 * @param ctx           Click object.
 * @param time_hours    Time hours [ 0 h : 23 h ]
 * @param time_min      Time minutes [ 0 min : 59 min ]
 * @param time_sec      Time seconds [ 0 sec : 59 sec ]
 *
 * This function sets time: hours, minutes and seconds data to
 * the target register address ( 0x01, 0x02 & 0x03 )
 * of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_time ( rtc5_t *ctx, uint8_t time_hours, uint8_t time_min, uint8_t time_sec );

/**
 * @brief Set date hours, minutes and seconds function
 *
 * @param ctx           Click object.
 * @param date_day      Date day data [ 1 : 31 ]
 * @param date_month    Date month data [ 1 : 12 ]
 * @param date_year     Date year data [ 0 : 99 ]
 *
 * This function sets date: day, month and year data to
 * the target register address ( 0x04, 0x05, 0x06 & 0x07 )
 * of MCP79510 chip on RTC 5 Click.
 */
void rtc5_set_date ( rtc5_t *ctx, uint8_t date_day, uint8_t date_month, uint16_t date_year );

/**
 * @brief Get time and date function.
 *
 * @param ctx              Click object.
 * @param timedate_data    pointer to the memory location where time and date data be stored.
 *
 * This function gets time ( hours, minutes and seconds ) 
 * and date ( day, month and year )
 * of MCP79510 chip on RTC 5 Click.
 */
void rtc5_get_time_and_date ( rtc5_t *ctx, rtc5_timedate_t *timedate_data );



#ifdef __cplusplus
}
#endif
#endif  // _RTC5_H_

/** \} */ // End public_function group
/// \}    // End click Driver group  
/*! @} */
// ------------------------------------------------------------------------- END
