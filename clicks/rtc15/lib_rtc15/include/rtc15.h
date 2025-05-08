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
 * @file rtc15.h
 * @brief This file contains API for RTC 15 Click Driver.
 */

#ifndef RTC15_H
#define RTC15_H

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
 * @addtogroup rtc15 RTC 15 Click Driver
 * @brief API for configuring and manipulating RTC 15 Click driver.
 * @{
 */

/**
 * @defgroup rtc15_reg RTC 15 Registers List
 * @brief List of registers of RTC 15 Click driver.
 */

/**
 * @addtogroup rtc15_reg
 * @{
 */

/**
 * @brief RTC 15 register list.
 * @details Specified register list of RTC 15 Click driver.
 */
#define RTC15_REG_CONTROL1                  0x00
#define RTC15_REG_CONTROL2                  0x01
#define RTC15_REG_OFFSET                    0x02
#define RTC15_REG_RAM                       0x03
#define RTC15_REG_SECONDS                   0x04
#define RTC15_REG_MINUTES                   0x05
#define RTC15_REG_HOURS                     0x06
#define RTC15_REG_DATE                      0x07
#define RTC15_REG_WEEKDAY                   0x08
#define RTC15_REG_MONTH                     0x09
#define RTC15_REG_YEAR                      0x0A
#define RTC15_REG_SECONDS_ALARM             0x0B
#define RTC15_REG_MINUTES_ALARM             0x0C
#define RTC15_REG_HOURS_ALARM               0x0D
#define RTC15_REG_DATE_ALARM                0x0E
#define RTC15_REG_WEEKDAY_ALARM             0x0F
#define RTC15_REG_TIMER_VALUE               0x10
#define RTC15_REG_TIMER_MODE                0x11

/*! @} */ // rtc15_reg

/**
 * @defgroup rtc15_set RTC 15 Registers Settings
 * @brief Settings for registers of RTC 15 Click driver.
 */

/**
 * @addtogroup rtc15_set
 * @{
 */

/**
 * @brief RTC 15 CONTROL1 register settings.
 * @details Specified settings for CONTROL1 register of RTC 15 Click driver.
 */
#define RTC15_CONTROL1_TEST_NORMAL          0x00
#define RTC15_CONTROL1_TEST_EXTCLK          0x80
#define RTC15_CONTROL1_TEST_MASK            0x80
#define RTC15_CONTROL1_SR_NORMAL            0x00
#define RTC15_CONTROL1_SR_RESET             0x58
#define RTC15_CONTROL1_SR_MASK              0x58
#define RTC15_CONTROL1_STOP_NO_STOP         0x00
#define RTC15_CONTROL1_STOP_RTC_STOP        0x20
#define RTC15_CONTROL1_STOP_MASK            0x20
#define RTC15_CONTROL1_CIE_DIS              0x00
#define RTC15_CONTROL1_CIE_EN               0x04
#define RTC15_CONTROL1_CIE_MASK             0x04
#define RTC15_CONTROL1_12_24_24             0x00
#define RTC15_CONTROL1_12_24_12             0x02
#define RTC15_CONTROL1_12_24_MASK           0x02

/**
 * @brief RTC 15 CONTROL2 register settings.
 * @details Specified settings for CONTROL2 register of RTC 15 Click driver.
 */
#define RTC15_CONTROL2_AIE_DIS              0x00
#define RTC15_CONTROL2_AIE_EN               0x80
#define RTC15_CONTROL2_AIE_MASK             0x80
#define RTC15_CONTROL2_AF_DIS               0x00
#define RTC15_CONTROL2_AF_EN                0x40
#define RTC15_CONTROL2_AF_MASK              0x40
#define RTC15_CONTROL2_MI_DIS               0x00
#define RTC15_CONTROL2_MI_EN                0x20
#define RTC15_CONTROL2_MI_MASK              0x20
#define RTC15_CONTROL2_HMI_DIS              0x00
#define RTC15_CONTROL2_HMI_EN               0x10
#define RTC15_CONTROL2_HMI_MASK             0x10
#define RTC15_CONTROL2_TF_DIS               0x00
#define RTC15_CONTROL2_TF_EN                0x08
#define RTC15_CONTROL2_TF_MASK              0x08
#define RTC15_CONTROL2_FD_32_768KHZ         0x00
#define RTC15_CONTROL2_FD_16_384KHZ         0x01
#define RTC15_CONTROL2_FD_8_192KHZ          0x02
#define RTC15_CONTROL2_FD_4_096KHZ          0x03
#define RTC15_CONTROL2_FD_2_048KHZ          0x04
#define RTC15_CONTROL2_FD_1_024KHZ          0x05
#define RTC15_CONTROL2_FD_1HZ               0x06
#define RTC15_CONTROL2_FD_LOW               0x07
#define RTC15_CONTROL2_FD_MASK              0x07

/**
 * @brief RTC 15 OFFSET register settings.
 * @details Specified settings for OFFSET register of RTC 15 Click driver.
 */
#define RTC15_OFFSET_MODE_NORMAL            0x00
#define RTC15_OFFSET_MODE_FAST              0x80
#define RTC15_OFFSET_MODE_MASK              0x80
#define RTC15_OFFSET_OFFSET_MASK            0x7F

/**
 * @brief RTC 15 TIMER_VALUE register settings.
 * @details Specified settings for TIMER_VALUE register of RTC 15 Click driver.
 */
#define RTC15_TIMER_VALUE_DEFAULT           0x01

/**
 * @brief RTC 15 TIMER_MODE register settings.
 * @details Specified settings for TIMER_MODE register of RTC 15 Click driver.
 */
#define RTC15_TIMER_MODE_TD_4_096KHZ        0x00
#define RTC15_TIMER_MODE_TD_64HZ            0x08
#define RTC15_TIMER_MODE_TD_1HZ             0x10
#define RTC15_TIMER_MODE_TD_1_OVER_64HZ     0x18
#define RTC15_TIMER_MODE_TD_MASK            0x18
#define RTC15_TIMER_MODE_TE_DIS             0x00
#define RTC15_TIMER_MODE_TE_EN              0x04
#define RTC15_TIMER_MODE_TE_MASK            0x04
#define RTC15_TIMER_MODE_TIE_DIS            0x00
#define RTC15_TIMER_MODE_TIE_EN             0x02
#define RTC15_TIMER_MODE_TIE_MASK           0x02
#define RTC15_TIMER_MODE_TI_TP_INTERVAL     0x00
#define RTC15_TIMER_MODE_TI_TP_PULSE        0x01
#define RTC15_TIMER_MODE_TI_TP_MASK         0x01

/**
 * @brief RTC 15 day of week values.
 * @details Specified day of week values of RTC 15 Click driver.
 */
#define RTC15_MONDAY                        0x00
#define RTC15_TUESDAY                       0x01
#define RTC15_WEDNESDAY                     0x02
#define RTC15_THURSDAY                      0x03
#define RTC15_FRIDAY                        0x04
#define RTC15_SATURDAY                      0x05
#define RTC15_SUNDAY                        0x06

/**
 * @brief RTC 15 dummy RAM data for communication check.
 * @details Specified dummy RAM data for communication check of RTC 15 Click driver.
 */
#define RTC15_DUMMY_RAM                     0xA5

/**
 * @brief RTC 15 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 15 Click driver.
 */
#define RTC15_DEVICE_ADDRESS                0x51

/*! @} */ // rtc15_set

/**
 * @defgroup rtc15_map RTC 15 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 15 Click driver.
 */

/**
 * @addtogroup rtc15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 15 Click to the selected MikroBUS.
 */
#define RTC15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cle = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc15_map
/*! @} */ // rtc15

/**
 * @brief RTC 15 Click context object.
 * @details Context object definition of RTC 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable pin (active high). */
    digital_out_t cle;          /**< Clock output enable pin (active high). */

    // Input pins
    digital_in_t int_pin;       /**< Interrupt pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc15_t;

/**
 * @brief RTC 15 Click configuration object.
 * @details Configuration object definition of RTC 15 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable pin (active high). */
    pin_name_t cle;             /**< Clock output enable pin (active high). */
    pin_name_t int_pin;         /**< Interrupt pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc15_cfg_t;

/**
 * @brief RTC 15 Click time object.
 * @details Time object definition of RTC 15 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc15_time_t;

/**
 * @brief RTC 15 Click date object.
 * @details Date object definition of RTC 15 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc15_date_t;

/**
 * @brief RTC 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC15_OK = 0,
    RTC15_ERROR = -1

} rtc15_return_value_t;

/*!
 * @addtogroup rtc15 RTC 15 Click Driver
 * @brief API for configuring and manipulating RTC 15 Click driver.
 * @{
 */

/**
 * @brief RTC 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc15_cfg_setup ( rtc15_cfg_t *cfg );

/**
 * @brief RTC 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc15_init ( rtc15_t *ctx, rtc15_cfg_t *cfg );

/**
 * @brief RTC 15 default configuration function.
 * @details This function executes a default configuration of RTC 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc15_default_cfg ( rtc15_t *ctx );

/**
 * @brief RTC 15 write multiple registers function.
 * @details This function writes a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc15_write_regs ( rtc15_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 15 read multiple registers function.
 * @details This function reads a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc15_read_regs ( rtc15_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 15 write single register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc15_write_reg ( rtc15_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 15 read single register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory to store the read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc15_read_reg ( rtc15_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 15 enable device function.
 * @details This function sets the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @note None.
 */
void rtc15_enable_device ( rtc15_t *ctx );

/**
 * @brief RTC 15 disable device function.
 * @details This function sets the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @note None.
 */
void rtc15_disable_device ( rtc15_t *ctx );

/**
 * @brief RTC 15 enable clock output function.
 * @details This function sets the CLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @note None.
 */
void rtc15_enable_clkout ( rtc15_t *ctx );

/**
 * @brief RTC 15 disable clock output function.
 * @details This function sets the CLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @note None.
 */
void rtc15_disable_clkout ( rtc15_t *ctx );

/**
 * @brief RTC 15 get interrupt pin function.
 * @details This function returns the logic state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc15_get_int_pin ( rtc15_t *ctx );

/**
 * @brief RTC 15 check communication function.
 * @details This function performs a write-read test on the RAM register to verify communication.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @return @li @c  0 - Success (communication established),
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc15_check_communication ( rtc15_t *ctx );

/**
 * @brief RTC 15 set time function.
 * @details This function sets the current time (hours, minutes, seconds) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] time : Pointer to the time structure.
 * See #rtc15_time_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Time values must be provided in decimal format.
 */
err_t rtc15_set_time ( rtc15_t *ctx, rtc15_time_t *time );

/**
 * @brief RTC 15 read time function.
 * @details This function reads the current time (hours, minutes, seconds) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[out] time : Pointer to the time structure to store the read values.
 * See #rtc15_time_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Time values are returned in decimal format.
 */
err_t rtc15_read_time ( rtc15_t *ctx, rtc15_time_t *time );

/**
 * @brief RTC 15 set date function.
 * @details This function sets the current date (day, day of week, month, year) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[in] date : Pointer to the date structure.
 * See #rtc15_date_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Date values must be provided in decimal format.
 */
err_t rtc15_set_date ( rtc15_t *ctx, rtc15_date_t *date );

/**
 * @brief RTC 15 read date function.
 * @details This function reads the current date (day, day of week, month, year) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc15_t object definition for detailed explanation.
 * @param[out] date : Pointer to the date structure to store the read values.
 * See #rtc15_date_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Date values are returned in decimal format.
 */
err_t rtc15_read_date ( rtc15_t *ctx, rtc15_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC15_H

/*! @} */ // rtc15

// ------------------------------------------------------------------------ END
