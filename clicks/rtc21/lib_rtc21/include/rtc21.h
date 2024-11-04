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
 * @file rtc21.h
 * @brief This file contains API for RTC 21 Click Driver.
 */

#ifndef RTC21_H
#define RTC21_H

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
 * @addtogroup rtc21 RTC 21 Click Driver
 * @brief API for configuring and manipulating RTC 21 Click driver.
 * @{
 */

/**
 * @defgroup rtc21_reg RTC 21 Registers List
 * @brief List of registers of RTC 21 Click driver.
 */

/**
 * @addtogroup rtc21_reg
 * @{
 */

/**
 * @brief RTC 21 RTC register list.
 * @details Specified RTC register list for description of RTC 21 Click driver.
 */
#define RTC21_REG_SECOND                    0x00
#define RTC21_REG_MINUTE                    0x01
#define RTC21_REG_HOUR                      0x02
#define RTC21_REG_DAY_OF_WEEK               0x03
#define RTC21_REG_DATE                      0x04
#define RTC21_REG_MONTH                     0x05
#define RTC21_REG_YEAR                      0x06
#define RTC21_REG_CONTROL                   0x07
#define RTC21_REG_RAM_BOTTOM                0x08
#define RTC21_REG_RAM_TOP                   0x3F

/*! @} */ // rtc21_reg

/**
 * @defgroup rtc21_set RTC 21 Registers Settings
 * @brief Settings for registers of RTC 21 Click driver.
 */

/**
 * @addtogroup rtc21_set
 * @{
 */

/**
 * @brief RTC 21 day of week values.
 * @details Specified day of week values of RTC 21 Click driver.
 */
#define RTC21_MONDAY                        0x01
#define RTC21_TUESDAY                       0x02
#define RTC21_WEDNESDAY                     0x03
#define RTC21_THURSDAY                      0x04
#define RTC21_FRIDAY                        0x05
#define RTC21_SATURDAY                      0x06
#define RTC21_SUNDAY                        0x07

/**
 * @brief RTC 21 device address setting.
 * @details Specified setting for device slave address selection of
 * RTC 21 Click driver.
 */
#define RTC21_DEVICE_ADDRESS                0x68

/*! @} */ // rtc21_set

/**
 * @defgroup rtc21_map RTC 21 MikroBUS Map
 * @brief MikroBUS pin mapping of RTC 21 Click driver.
 */

/**
 * @addtogroup rtc21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of RTC 21 Click to the selected MikroBUS.
 */
#define RTC21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ft  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // rtc21_map
/*! @} */ // rtc21

/**
 * @brief RTC 21 Click context object.
 * @details Context object definition of RTC 21 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t ft;            /**< FT/OUT pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} rtc21_t;

/**
 * @brief RTC 21 Click configuration object.
 * @details Configuration object definition of RTC 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t ft;              /**< FT/OUT pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} rtc21_cfg_t;

/**
 * @brief RTC 21 Click time object.
 * @details Time object definition of RTC 21 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;

} rtc21_time_t;

/**
 * @brief RTC 21 Click date object.
 * @details Date object definition of RTC 21 Click driver.
 * @note Values are converted to decimal format.
 */
typedef struct
{
    uint8_t day_of_week;
    uint8_t day;
    uint8_t month;
    uint8_t year;

} rtc21_date_t;

/**
 * @brief RTC 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    RTC21_OK = 0,
    RTC21_ERROR = -1

} rtc21_return_value_t;

/*!
 * @addtogroup rtc21 RTC 21 Click Driver
 * @brief API for configuring and manipulating RTC 21 Click driver.
 * @{
 */

/**
 * @brief RTC 21 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #rtc21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void rtc21_cfg_setup ( rtc21_cfg_t *cfg );

/**
 * @brief RTC 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #rtc21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_init ( rtc21_t *ctx, rtc21_cfg_t *cfg );

/**
 * @brief RTC 21 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_generic_write ( rtc21_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief RTC 21 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_generic_read ( rtc21_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief RTC 21 write register function.
 * @details This function writes data to the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_write_register ( rtc21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief RTC 21 read register function.
 * @details This function reads data from the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_read_register ( rtc21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief RTC 21 get ft pin function.
 * @details This function returns the FT/OUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t rtc21_get_ft_pin ( rtc21_t *ctx );

/**
 * @brief RTC 21 set time function.
 * @details This function sets the starting time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] time : Time object structure that carries second, minute and hour values in Decimal format.
 * See #rtc21_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_set_time ( rtc21_t *ctx, rtc21_time_t *time );

/**
 * @brief RTC 21 read time function.
 * @details This function reads the current time values - second, minute and hour.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[out] time : Time object structure.
 * See #rtc21_time_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_read_time ( rtc21_t *ctx, rtc21_time_t *time );

/**
 * @brief RTC 21 set date function.
 * @details This function sets the starting date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[in] date : Date object structure that carries day of week, day, month and year values in Decimal format.
 * See #rtc21_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_set_date ( rtc21_t *ctx, rtc21_date_t *date );

/**
 * @brief RTC 21 read date function.
 * @details This function reads the current date values - day of week, day, month and year.
 * @param[in] ctx : Click context object.
 * See #rtc21_t object definition for detailed explanation.
 * @param[out] date : Date object structure.
 * See #rtc21_date_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t rtc21_read_date ( rtc21_t *ctx, rtc21_date_t *date );

#ifdef __cplusplus
}
#endif
#endif // RTC21_H

/*! @} */ // rtc21

// ------------------------------------------------------------------------ END
