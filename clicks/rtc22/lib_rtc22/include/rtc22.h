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
 * @file rtc22.h
 * @brief This file contains API for RTC 22 Click Driver.
 */

#ifndef RTC22_H
#define RTC22_H

#ifdef __cplusplus
extern "C"{
#endif

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

/*!
 * @addtogroup rtc22 RTC 22 Click Driver
 * @brief API for configuring and manipulating RTC 22 Click driver.
 * @{
 */

/**
 * @defgroup rtc22_reg RTC 22 Registers List
 * @brief List of registers of RTC 22 Click driver.
 */

/**
 * @addtogroup rtc22_reg
 * @{
 */

/**
 * @brief RTC 22 register list.
 * @details Specified register list of RTC 22 Click driver.
 */
#define RTC22_REG_HUNDREDTHS                        0x00
#define RTC22_REG_SECONDS                           0x01
#define RTC22_REG_MINUTES                           0x02
#define RTC22_REG_HOURS                             0x03
#define RTC22_REG_DATE                              0x04
#define RTC22_REG_MONTHS                            0x05
#define RTC22_REG_YEARS                             0x06
#define RTC22_REG_WEEKDAYS                          0x07
#define RTC22_REG_HUNDREDTHS_ALARM                  0x08
#define RTC22_REG_SECONDS_ALARM                     0x09
#define RTC22_REG_MINUTES_ALARM                     0x0A
#define RTC22_REG_HOURS_ALARM                       0x0B
#define RTC22_REG_DATE_ALARM                        0x0C
#define RTC22_REG_MONTHS_ALARM                      0x0D
#define RTC22_REG_WEEKDAYS_ALARM                    0x0E
#define RTC22_REG_STATUS                            0x0F
#define RTC22_REG_CONTROL1                          0x10
#define RTC22_REG_CONTROL2                          0x11
#define RTC22_REG_INT_MASK                          0x12
#define RTC22_REG_SQW                               0x13
#define RTC22_REG_CAL_XT                            0x14
#define RTC22_REG_CAL_RC_HI                         0x15
#define RTC22_REG_CAL_RC_LOW                        0x16
#define RTC22_REG_SLEEP_CONTROL                     0x17
#define RTC22_REG_TIMER_CONTROL                     0x18
#define RTC22_REG_TIMER                             0x19
#define RTC22_REG_TIMER_INITIAL                     0x1A
#define RTC22_REG_WDT                               0x1B
#define RTC22_REG_OSC_CONTROL                       0x1C
#define RTC22_REG_OSC_STATUS                        0x1D
#define RTC22_REG_CONFIGURATION_KEY                 0x1F
#define RTC22_REG_TRICKLE                           0x20
#define RTC22_REG_BREF_CONTROL                      0x21
#define RTC22_REG_AFCTRL                            0x26
#define RTC22_REG_BATMODE_IO                        0x27
#define RTC22_REG_ID0                               0x28
#define RTC22_REG_ID1                               0x29
#define RTC22_REG_ID2                               0x2A
#define RTC22_REG_ID3                               0x2B
#define RTC22_REG_ID4                               0x2C
#define RTC22_REG_ID5                               0x2D
#define RTC22_REG_ID6                               0x2E
#define RTC22_REG_ASTAT                             0x2F
#define RTC22_REG_OCTRL                             0x30
#define RTC22_REG_EXTENSION_ADDRESS                 0x3F
#define RTC22_REG_RAM                               0x40

/*! @} */ // rtc22_reg

/**
 * @defgroup rtc22_set RTC 22 Registers Settings
 * @brief Settings for registers of RTC 22 Click driver.
 */

/**
 * @addtogroup rtc22_set
 * @{
 */

/**
 * @brief RTC 22 day of week values.
 * @details Specified day of week values of RTC 22 Click driver.
 */
#define RTC22_MONDAY                                0x00
#define RTC22_TUESDAY                               0x01
#define RTC22_WEDNESDAY                             0x02
#define RTC22_THURSDAY                              0x03
#define RTC22_FRIDAY                                0x04
#define RTC22_SATURDAY                              0x05
#define RTC22_SUNDAY                                0x06

/**
 * @brief RTC 22 device ID value.
 * @details Specified device ID value of RTC 22 Click driver.
 */
#define RTC22_DEVICE_ID                             0x18

/**
 * @brief RTC 22 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 22 Click driver.
 */
#define RTC22_DEVICE_ADDRESS                        0x69

/*! @} */ // rtc22_set

/**
 * @defgroup rtc22_map RTC 22 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 22 Click driver.
 */

/**
 * @addtogroup rtc22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 22 Click to the selected MikroBUS.
 */
#define RTC22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.tirq = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.psw = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.wdi = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc22_map
/*! @} */ // rtc22

/**
 * @brief RTC 22 Click context object.
 * @details Context object definition of RTC 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t wdi;          /**< Watchdog reset pin. */

    // Input pins
    digital_in_t tirq;          /**< Timer interrupt pin. */
    digital_in_t psw;           /**< INT 2 or power switch pin. */
    digital_in_t int_pin;       /**< INT 1 or function pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc22_t;

/**
 * @brief RTC 22 Click configuration object.
 * @details Configuration object definition of RTC 22 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t tirq;            /**< Timer interrupt pin. */
    pin_name_t wdi;             /**< Watchdog reset pin. */
    pin_name_t psw;             /**< INT 2 or power switch pin. */
    pin_name_t int_pin;         /**< INT 1 or function pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc22_cfg_t;

/**
 * @brief RTC 22 Click time object.
 * @details Time object definition of RTC 22 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second_100th;
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc22_time_t;

/**
 * @brief RTC 22 Click date object.
 * @details Date object definition of RTC 22 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc22_date_t;

/**
 * @brief RTC 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC22_OK = 0,
    RTC22_ERROR = -1

} rtc22_return_value_t;

/*!
 * @addtogroup rtc22 RTC 22 Click Driver
 * @brief API for configuring and manipulating RTC 22 Click driver.
 * @{
 */

/**
 * @brief RTC 22 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc22_cfg_setup ( rtc22_cfg_t *cfg );

/**
 * @brief RTC 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_init ( rtc22_t *ctx, rtc22_cfg_t *cfg );

/**
 * @brief RTC 22 write regs function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_write_regs ( rtc22_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 22 read regs function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_read_regs ( rtc22_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 22 write reg function.
 * @details This function writes a data byte to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_write_reg ( rtc22_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 22 read reg function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_read_reg ( rtc22_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 22 set WDI pin function.
 * @details This function sets the watchdog reset (WDI) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] state : Pin logic state.
 * @return None.
 * @note None.
 */
void rtc22_set_wdi_pin ( rtc22_t *ctx, uint8_t state );

/**
 * @brief RTC 22 get PSW pin function.
 * @details This function returns the power switch (PSW) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc22_get_psw_pin ( rtc22_t *ctx );

/**
 * @brief RTC 22 get TIRQ pin function.
 * @details This function returns the timer interrupt (TIRQ) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc22_get_tirq_pin ( rtc22_t *ctx );

/**
 * @brief RTC 22 get INT pin function.
 * @details This function returns the interrupt (INT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc22_get_int_pin ( rtc22_t *ctx );

/**
 * @brief RTC 22 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_check_communication ( rtc22_t *ctx );

/**
 * @brief RTC 22 set time function.
 * @details This function sets the starting time values - second 100th, second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second 100th, second, minute and hour values in Decimal format.
 * See #rtc22_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_set_time ( rtc22_t *ctx, rtc22_time_t *time );

/**
 * @brief RTC 22 read time function.
 * @details This function reads the current time values - second 100th, second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc22_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_read_time ( rtc22_t *ctx, rtc22_time_t *time );

/**
 * @brief RTC 22 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc22_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_set_date ( rtc22_t *ctx, rtc22_date_t *date );

/**
 * @brief RTC 22 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc22_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc22_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc22_read_date ( rtc22_t *ctx, rtc22_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC22_H

/*! @} */ // rtc22

// ------------------------------------------------------------------------ END
