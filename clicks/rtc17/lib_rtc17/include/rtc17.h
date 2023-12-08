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
 * @file rtc17.h
 * @brief This file contains API for RTC 17 Click Driver.
 */

#ifndef RTC17_H
#define RTC17_H

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
#include "drv_i2c_master.h"

/*!
 * @addtogroup rtc17 RTC 17 Click Driver
 * @brief API for configuring and manipulating RTC 17 Click driver.
 * @{
 */

/**
 * @defgroup rtc17_reg RTC 17 Registers List
 * @brief List of registers of RTC 17 Click driver.
 */

/**
 * @addtogroup rtc17_reg
 * @{
 */

/**
 * @brief RTC 17 Register Map.
 * @details Specified Register Map of RTC 17 Click driver.
 */
#define RTC17_REG_SECOND_COUNTER            0x00
#define RTC17_REG_MINUTE_COUNTER            0x01
#define RTC17_REG_HOUR_COUNTER              0x02
#define RTC17_REG_DAY_OF_WEEK_COUNTER       0x03
#define RTC17_REG_DAY_COUNTER               0x04
#define RTC17_REG_MONTH_COUNTER             0x05
#define RTC17_REG_YEAR_COUNTER              0x06
#define RTC17_REG_OSC_ADJ                   0x07
#define RTC17_REG_ALARM_W_MINUTE            0x08
#define RTC17_REG_ALARM_W_HOUR              0x09
#define RTC17_REG_ALARM_W_DAY_OF_WEEK       0x0A
#define RTC17_REG_ALARM_D_MINUTE            0x0B
#define RTC17_REG_ALARM_D_HOUR              0x0C
#define RTC17_REG_CONTROL1                  0x0E
#define RTC17_REG_CONTROL2                  0x0F

/*! @} */ // rtc17_reg

/**
 * @defgroup rtc17_set RTC 17 Registers Settings
 * @brief Settings for registers of RTC 17 Click driver.
 */

/**
 * @addtogroup rtc17_set
 * @{
 */

/**
 * @brief RTC 17 Control 1 register settings.
 * @details Specified Control 1 register settings of RTC 17 Click driver.
 */
#define RTC17_CONTROL1_ALARM_W_DISABLE      0x00
#define RTC17_CONTROL1_ALARM_W_ENABLE       0x80
#define RTC17_CONTROL1_ALARM_D_DISABLE      0x00
#define RTC17_CONTROL1_ALARM_D_ENABLE       0x40
#define RTC17_CONTROL1_12HOUR_TIME          0x00
#define RTC17_CONTROL1_24HOUR_TIME          0x20
#define RTC17_CONTROL1_CLOCK1_ENABLE        0x00
#define RTC17_CONTROL1_CLOCK1_DISABLE       0x10
#define RTC17_CONTROL1_TEST_NORMAL          0x00
#define RTC17_CONTROL1_TEST_TEST            0x08
#define RTC17_CONTROL1_CT_OFF               0x00
#define RTC17_CONTROL1_CT_FIXED_L           0x01
#define RTC17_CONTROL1_CT_PULSE_2HZ         0x02
#define RTC17_CONTROL1_CT_PULSE_1HZ         0x03
#define RTC17_CONTROL1_CT_EVERY_SECOND      0x04
#define RTC17_CONTROL1_CT_EVERY_MINUTE      0x05
#define RTC17_CONTROL1_CT_EVERY_HOUR        0x06
#define RTC17_CONTROL1_CT_EVERY_MONTH       0x07

/**
 * @brief RTC 17 Control 2 register settings.
 * @details Specified Control 2 register settings of RTC 17 Click driver.
 */
#define RTC17_CONTROL2_VDSL_2p1V            0x00
#define RTC17_CONTROL2_VDSL_1p6V            0x80
#define RTC17_CONTROL2_VDET_ABOVE           0x00
#define RTC17_CONTROL2_VDET_BELOW           0x40
#define RTC17_CONTROL2_SCRATCH_BIT          0x20
#define RTC17_CONTROL2_XSTP_NORMAL          0x00
#define RTC17_CONTROL2_XSTP_HALT            0x10
#define RTC17_CONTROL2_CLOCK2_ENABLE        0x00
#define RTC17_CONTROL2_CLOCK2_DISABLE       0x08
#define RTC17_CONTROL2_CLEAR_INTERRUPT      0x04
#define RTC17_CONTROL2_CLEAR_ALARM_W        0x02
#define RTC17_CONTROL2_CLEAR_ALARM_D        0x01

/**
 * @brief RTC 17 day of week values.
 * @details Specified day of week values of RTC 17 Click driver.
 */
#define RTC17_MONDAY                        0x00
#define RTC17_TUESDAY                       0x01
#define RTC17_WEDNESDAY                     0x02
#define RTC17_THURSDAY                      0x03
#define RTC17_FRIDAY                        0x04
#define RTC17_SATURDAY                      0x05
#define RTC17_SUNDAY                        0x06

/**
 * @brief RTC 17 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 17 Click driver.
 */
#define RTC17_SET_DEVICE_ADDRESS            0x32

/*! @} */ // rtc17_set

/**
 * @defgroup rtc17_map RTC 17 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 17 Click driver.
 */

/**
 * @addtogroup rtc17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 17 Click to the selected MikroBUS.
 */
#define RTC17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc17_map
/*! @} */ // rtc17

/**
 * @brief RTC 17 Click context object.
 * @details Context object definition of RTC 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc17_t;

/**
 * @brief RTC 17 Click configuration object.
 * @details Configuration object definition of RTC 17 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} rtc17_cfg_t;

/**
 * @brief RTC 17 Click time object.
 * @details Time object definition of RTC 17 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc17_time_t;

/**
 * @brief RTC 17 Click date object.
 * @details Date object definition of RTC 17 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc17_date_t;

/**
 * @brief RTC 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC17_OK = 0,
    RTC17_ERROR = -1

} rtc17_return_value_t;

/*!
 * @addtogroup rtc17 RTC 17 Click Driver
 * @brief API for configuring and manipulating RTC 17 Click driver.
 * @{
 */

/**
 * @brief RTC 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc17_cfg_setup ( rtc17_cfg_t *cfg );

/**
 * @brief RTC 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_init ( rtc17_t *ctx, rtc17_cfg_t *cfg );

/**
 * @brief RTC 17 default configuration function.
 * @details This function executes a default configuration of RTC 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc17_default_cfg ( rtc17_t *ctx );

/**
 * @brief RTC 17 write register function.
 * @details This function writes a desired data byte to the selected register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_write_register ( rtc17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 17 write multiple registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written [up to 16 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_write_multiple_registers ( rtc17_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief RTC 17 read register function.
 * @details This function reads a data byte from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] reg : register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_read_register ( rtc17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 17 read multiple registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read [up to 16 bytes].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_read_multiple_registers ( rtc17_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief RTC 17 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc17_get_int_pin ( rtc17_t *ctx );

/**
 * @brief RTC 17 clear interrupts function.
 * @details This function clears the interrupt and alarm flag bits in Control 2 register.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_clear_interrupts ( rtc17_t *ctx );

/**
 * @brief RTC 17 set time function.
 * @details This function sets the starting time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second, minute and hour values in Decimal format.
 * See #rtc17_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_set_time ( rtc17_t *ctx, rtc17_time_t *time );

/**
 * @brief RTC 17 read time function.
 * @details This function reads the current time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc17_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_read_time ( rtc17_t *ctx, rtc17_time_t *time );

/**
 * @brief RTC 17 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc17_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_set_date ( rtc17_t *ctx, rtc17_date_t *date );

/**
 * @brief RTC 17 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc17_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc17_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc17_read_date ( rtc17_t *ctx, rtc17_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC17_H

/*! @} */ // rtc17

// ------------------------------------------------------------------------ END
