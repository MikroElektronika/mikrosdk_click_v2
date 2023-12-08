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
 * @file rtc4.h
 * @brief This file contains API for RTC 4 Click Driver.
 */

#ifndef RTC4_H
#define RTC4_H

#ifdef __cplusplus
extern "C"{
#endif

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
#include "drv_one_wire.h"

/*!
 * @addtogroup rtc4 RTC 4 Click Driver
 * @brief API for configuring and manipulating RTC 4 Click driver.
 * @{
 */

/**
 * @defgroup rtc4_cmd RTC 4 Commands List
 * @brief List of commands of RTC 4 Click driver.
 */

/**
 * @addtogroup rtc4_cmd
 * @{
 */

/**
 * @brief RTC 4 commands list.
 * @details Specified commands list of RTC 4 Click driver.
 */
#define RTC4_CMD_READ_CLOCK             0x66
#define RTC4_CMD_WRITE_CLOCK            0x99

/*! @} */ // rtc4_cmd

/**
 * @defgroup rtc4_time RTC 4 time values list. 
 * @brief List of time values.
 */

/**
 * @addtogroup rtc4_time
 * @{
 */

/**
 * @brief Time values list. 
 * @details Specified time values list.
 */
#define RTC4_SEC_PER_MINUTE             60
#define RTC4_SEC_PER_HOUR               3600
#define RTC4_SEC_PER_DAY                86400 
#define RTC4_START_YEAR                 1970
#define RTC4_DAYS_PER_LEAP_YEAR         366      
#define RTC4_DAYS_PER_YEAR              365 
#define RTC4_DAYS_IN_FEB                29 

/*! @} */ // rtc4_time

/**
 * @defgroup rtc4_set RTC 4 Settings
 * @brief Settings of RTC 4 Click driver.
 */

/**
 * @addtogroup rtc4_set
 * @{
 */

/**
 * @brief RTC 4 device control byte.
 * @details Specified family code value of RTC 4 Click driver.
 */
#define RTC4_DCB_INT_ENABLE             0x80
#define RTC4_DCB_OSC_ENABLE             0x0C
#define RTC4_DCB_INTERVAL_1S            0x00
#define RTC4_DCB_INTERVAL_4S            0x10
#define RTC4_DCB_INTERVAL_32S           0x20
#define RTC4_DCB_INTERVAL_64S           0x30
#define RTC4_DCB_INTERVAL_2048S         0x40
#define RTC4_DCB_INTERVAL_4096S         0x50
#define RTC4_DCB_INTERVAL_65536S        0x60  
#define RTC4_DCB_INTERVAL_131072S       0x70

/**
 * @brief RTC 4 device control byte.
 * @details Specified device control byte of RTC 4 Click driver.
 */
#define RTC4_FAMILY_CODE                0x27

/*! @} */ // rtc4_set

/**
 * @defgroup rtc4_map RTC 4 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 4 Click driver.
 */

/**
 * @addtogroup rtc4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 4 Click to the selected MikroBUS.
 */
#define RTC4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.gp0 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.gp1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc4_map

/*! @} */ // rtc4

/**
 * @brief RTC 4 Click time object.
 * @details Time object definition of RTC 4 Click driver.
 */
typedef struct 
{
    uint32_t hours; 
    uint32_t min;
    uint32_t sec; 
    
} rtc4_time_t;

/**
 * @brief RTC 4 Click date object.
 * @details Date object definition of RTC 4 Click driver.
 */
typedef struct 
{
    uint32_t year;
    uint32_t month;
    uint32_t day;

} rtc4_date_t;

/**
 * @brief RTC 4 Click gpio selector.
 * @details Selects gpio pin of RTC 4 Click driver.
 */
typedef enum
{
    RTC4_GPIO_0,                        /**< GPIO 0 pin. */
    RTC4_GPIO_1                         /**< GPIO 1 pin. */

} rtc4_gpio_sel_t;

/**
 * @brief RTC 4 Click context object.
 * @details Context object definition of RTC 4 Click driver.
 */
typedef struct
{
    //Input pins
    digital_in_t int_pin;               /**< Interrupt pin. */

    //Modules
    one_wire_t ow;                      /**< One Wire driver object. */

    one_wire_rom_address_t rom_addr;    /**< ROM address of device. */
    uint8_t address;                    /**< Device address selection. */

} rtc4_t;

/**
 * @brief RTC 4 Click configuration object.
 * @details Configuration object definition of RTC 4 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t gp0;                     /**< GPIO 0 pin. */
    pin_name_t gp1;                     /**< GPIO 1 pin. */

    // Additional gpio pins
    pin_name_t int_pin;                 /**< Interrupt pin. */

    rtc4_gpio_sel_t gpio_sel;           /**< GPIO selection. */

} rtc4_cfg_t;

/**
 * @brief RTC 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC4_OK = 0,
    RTC4_ERROR = -1

} rtc4_return_value_t;

/*!
 * @addtogroup rtc4 RTC 4 Click Driver
 * @brief API for configuring and manipulating RTC 4 Click driver.
 * @{
 */

/**
 * @brief RTC 4 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc4_cfg_setup ( rtc4_cfg_t *cfg );

/**
 * @brief RTC 4 driver interface setup function.
 * @details This function sets a communication GPIO pin which will be used
 * further in the click driver.
 * @param[out] cfg : Click configuration structure.
 * See #rtc4_cfg_t object definition for detailed explanation.
 * @param[in] gpio_sel : GPIO pin selection.
 * See #rtc4_gpio_sel_t object definition for detailed explanation.
 * @return Nothing.
 * @note This gpio selection should be call before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void rtc4_gpio_selection ( rtc4_cfg_t *cfg, rtc4_gpio_sel_t gpio_sel );

/**
 * @brief RTC 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc4_cfg_t object definition for detailed explanation.
 * @return Nothing. 
 * @note None.
 */
err_t rtc4_init ( rtc4_t *ctx, rtc4_cfg_t *cfg );

/**
 * @brief RTC 4 check communication function.
 * @details This function checks the communication by reading the ROM address 
 * as well as verifying family code and Maxim CRC 8.  
 * @param[in] ctx : Click context object.
 * See #rtc4_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc4_check_communication ( rtc4_t *ctx );

/**
 * @brief RTC 4 get interrupt function.
 * @details This function checks the interrupt state of the DS2417 Real time clock/calendar.
 * @param[in] ctx : Click context object.
 * See #rtc4_t object definition for detailed explanation.
 * @return @li @c 0 - INT pin state low,
 *         @li @c 1 - INT pin state high.
 * @note None.
 */
uint8_t rtc4_get_interrupt ( rtc4_t *ctx ); 

/**
 * @brief RTC 4 set unix and interrupt interval function.
 * @details This function sets both unix time and interrupt interval.
 * @param[in] ctx : Click context object.
 * See #rtc4_t object definition for detailed explanation.
 * @param[in] unix_time : Unix time we want to set. 
 * @param[in] int_interval : Interrupt interval we want to set. 
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc4_set_unix_and_int ( rtc4_t *ctx, uint32_t unix_time, uint8_t int_interval ); 

/**
 * @brief RTC 4 get unix time function.
 * @details This function gets unix time of the DS2417 Real time clock/calender.
 * @param[in] ctx : Click context object.
 * See #rtc4_t object definition for detailed explanation.
 * @param[out] unix_time : Pointing to the address where to store unix time.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc4_get_unix_time ( rtc4_t *ctx, uint32_t *unix_time ); 

/**
 * @brief RTC 4 unix to date time function. 
 * @details This function converts unix time to the human-readable format. 
 * @param[in] unix_time : Unix time we want to convert.
 * @param[out] time : Pointing to the address where to store time.
 * See #rtc4_time_t object definition for detailed explanation.
 * @param[out] date : Pointing to the address where to store date. 
 * See #rtc4_date_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void rtc4_unix_to_date_time ( uint32_t unix_time, rtc4_time_t *time, rtc4_date_t *date ); 

/**
 * @brief RTC 4 date time to unix function.
 * @details This function converts date time to the unix time.
 * @param[in] date : Pointing to the address from where to get date.
 * See #rtc4_date_t object definition for detailed explanation.
 * @param[in] time : Pointing to the address from where to get time.
 * See #rtc4_time_t object definition for detailed explanation.
 * @param[out] unix_time : Pointing to the address where to store unix time. 
 * @return Nothing.
 * @note None.
 */
void rtc4_date_time_to_unix ( rtc4_date_t *date, rtc4_time_t *time, uint32_t *unix_time );

/**
 * @brief RTC 4 set date time function.
 * @details This function sets date and time structure along with interrupt interval.
 * @param[in] ctx : Click context object.
 * @param[in] date : Pointing to the address from where to set date.
 * See #rtc4_date_t object definition for detailed explanation.
 * @param[in] time : Pointing to the address from where to set date.
 * See #rtc4_time_t object definition for detailed explanation.
 * @param[in] int_interval : Interrupt interval.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc4_set_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time, uint8_t int_interval );

/**
 * @brief RTC 4 get date time function.
 * @details This function gets RTC4 time and date structure. 
 * @param[in] ctx : Click context object.
 * @param[out] date : Pointing to the address where to store date. 
 * See #rtc4_date_t object definition for detailed explanation.
 * @param[out] time : Pointing to the address where to store time. 
 * See #rtc4_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc4_get_date_time ( rtc4_t *ctx, rtc4_date_t *date, rtc4_time_t *time );

#ifdef __cplusplus
}
#endif
#endif // RTC4_H

/*! @} */ // rtc4

// ------------------------------------------------------------------------ END
