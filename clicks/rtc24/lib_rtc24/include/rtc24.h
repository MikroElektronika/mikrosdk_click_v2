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
 * @file rtc24.h
 * @brief This file contains API for RTC 24 Click Driver.
 */

#ifndef RTC24_H
#define RTC24_H

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
 * @addtogroup rtc24 RTC 24 Click Driver
 * @brief API for configuring and manipulating RTC 24 Click driver.
 * @{
 */

/**
 * @defgroup rtc24_reg RTC 24 Registers List
 * @brief List of registers of RTC 24 Click driver.
 */

/**
 * @addtogroup rtc24_reg
 * @{
 */

/**
 * @brief RTC 24 register list.
 * @details Specified register list of RTC 24 Click driver.
 */
#define RTC24_REG_SECONDS               0x00
#define RTC24_REG_MINUTES               0x01
#define RTC24_REG_HOURS                 0x02
#define RTC24_REG_DAY                   0x03
#define RTC24_REG_DATE                  0x04
#define RTC24_REG_MONTH                 0x05
#define RTC24_REG_YEAR                  0x06
#define RTC24_REG_CONTROL               0x07
#define RTC24_REG_RAM_START             0x08
#define RTC24_REG_RAM_END               0x3F

/*! @} */ // rtc24_reg

/**
 * @defgroup rtc24_set RTC 24 Registers Settings
 * @brief Settings for registers of RTC 24 Click driver.
 */

/**
 * @addtogroup rtc24_set
 * @{
 */

/**
 * @brief RTC 24 CONTROL register setting.
 * @details Specified setting for CONTROL register of RTC 24 Click driver.
 */
#define RTC24_CONTROL_OUT_LOW           0x00
#define RTC24_CONTROL_OUT_HIGH          0x80
#define RTC24_CONTROL_OUT_MASK          0x80
#define RTC24_CONTROL_SQWE_DIS          0x00
#define RTC24_CONTROL_SQWE_EN           0x10
#define RTC24_CONTROL_SQWE_MASK         0x10
#define RTC24_CONTROL_RS_1HZ            0x00
#define RTC24_CONTROL_RS_4_096KHZ       0x01
#define RTC24_CONTROL_RS_8_192KHZ       0x02
#define RTC24_CONTROL_RS_32_768KHZ      0x03
#define RTC24_CONTROL_RS_MASK           0x03

/**
 * @brief RTC 24 day of week values.
 * @details Specified day of week values of RTC 24 Click driver.
 */
#define RTC24_MONDAY                    0x00
#define RTC24_TUESDAY                   0x01
#define RTC24_WEDNESDAY                 0x02
#define RTC24_THURSDAY                  0x03
#define RTC24_FRIDAY                    0x04
#define RTC24_SATURDAY                  0x05
#define RTC24_SUNDAY                    0x06

/**
 * @brief RTC 24 dummy RAM data for communication check.
 * @details Specified dummy RAM data for communication check of RTC 24 Click driver.
 */
#define RTC24_DUMMY_RAM                 0xA5

/**
 * @brief RTC 24 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 24 Click driver.
 */
#define RTC24_DEVICE_ADDRESS            0x68

/*! @} */ // rtc24_set

/**
 * @defgroup rtc24_map RTC 24 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 24 Click driver.
 */

/**
 * @addtogroup rtc24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 24 Click to the selected MikroBUS.
 */
#define RTC24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.sqw = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc24_map
/*! @} */ // rtc24

/**
 * @brief RTC 24 Click context object.
 * @details Context object definition of RTC 24 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t sqw;           /**< Square wave pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc24_t;

/**
 * @brief RTC 24 Click configuration object.
 * @details Configuration object definition of RTC 24 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t sqw;             /**< Square wave pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc24_cfg_t;

/**
 * @brief RTC 24 Click time object.
 * @details Time object definition of RTC 24 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc24_time_t;

/**
 * @brief RTC 24 Click date object.
 * @details Date object definition of RTC 24 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc24_date_t;

/**
 * @brief RTC 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC24_OK = 0,
    RTC24_ERROR = -1

} rtc24_return_value_t;

/*!
 * @addtogroup rtc24 RTC 24 Click Driver
 * @brief API for configuring and manipulating RTC 24 Click driver.
 * @{
 */

/**
 * @brief RTC 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc24_cfg_setup ( rtc24_cfg_t *cfg );

/**
 * @brief RTC 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc24_init ( rtc24_t *ctx, rtc24_cfg_t *cfg );

/**
 * @brief RTC 24 default configuration function.
 * @details This function executes a default configuration of RTC 24
 * Click board.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t rtc24_default_cfg ( rtc24_t *ctx );

/**
 * @brief RTC 24 write multiple registers function.
 * @details This function writes a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Pointer to the data to be written.
 * @param[in] len : Number of bytes to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc24_write_regs ( rtc24_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 24 read multiple registers function.
 * @details This function reads a sequence of bytes starting from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Pointer to the buffer to store read data.
 * @param[in] len : Number of bytes to read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc24_read_regs ( rtc24_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 24 write single register function.
 * @details This function writes a single byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data byte to write.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc24_write_reg ( rtc24_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 24 read single register function.
 * @details This function reads a single byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Pointer to the memory to store the read byte.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc24_read_reg ( rtc24_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 24 get square wave pin function.
 * @details This function returns the logic state of the SQW pin.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc24_get_sqw_pin ( rtc24_t *ctx );

/**
 * @brief RTC 24 check communication function.
 * @details This function performs a write-read test on the RAM register to verify communication.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @return @li @c  0 - Success (communication established),
 *         @li @c -1 - Error.
 * @note None.
 */
err_t rtc24_check_communication ( rtc24_t *ctx );

/**
 * @brief RTC 24 set time function.
 * @details This function sets the current time (hours, minutes, seconds) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] time : Pointer to the time structure.
 * See #rtc24_time_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Time values must be provided in decimal format.
 */
err_t rtc24_set_time ( rtc24_t *ctx, rtc24_time_t *time );

/**
 * @brief RTC 24 read time function.
 * @details This function reads the current time (hours, minutes, seconds) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[out] time : Pointer to the time structure to store the read values.
 * See #rtc24_time_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Time values are returned in decimal format.
 */
err_t rtc24_read_time ( rtc24_t *ctx, rtc24_time_t *time );

/**
 * @brief RTC 24 set date function.
 * @details This function sets the current date (day, day of week, month, year) in the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[in] date : Pointer to the date structure.
 * See #rtc24_date_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Date values must be provided in decimal format.
 */
err_t rtc24_set_date ( rtc24_t *ctx, rtc24_date_t *date );

/**
 * @brief RTC 24 read date function.
 * @details This function reads the current date (day, day of week, month, year) from the RTC.
 * @param[in] ctx : Click context object.
 * See #rtc24_t object definition for detailed explanation.
 * @param[out] date : Pointer to the date structure to store the read values.
 * See #rtc24_date_t object definition for structure fields.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * @note Date values are returned in decimal format.
 */
err_t rtc24_read_date ( rtc24_t *ctx, rtc24_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC24_H

/*! @} */ // rtc24

// ------------------------------------------------------------------------ END
