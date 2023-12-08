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
 * @file currentlimit5.h
 * @brief This file contains API for Current Limit 5 Click Driver.
 */

#ifndef CURRENTLIMIT5_H
#define CURRENTLIMIT5_H

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
 * @addtogroup currentlimit5 Current Limit 5 Click Driver
 * @brief API for configuring and manipulating Current Limit 5 Click driver.
 * @{
 */

/**
 * @defgroup currentlimit5_set Current Limit 5 Settings
 * @brief Settings of Current Limit 5 Click driver.
 */

/**
 * @addtogroup currentlimit5_set
 * @{
 */

/**
 * @brief Current Limit 5 calculation values.
 * @details Specified calculation values of Current Limit 5 Click driver.
 */
#define CURRENTLIMIT5_DIGIPOT_MAX_VALUE     5000
#define CURRENTLIMIT5_DIGIPOT_OFFSET        80
#define CURRENTLIMIT5_DIGIPOT_RESOLUTION    257
#define CURRENTLIMIT5_ROUND_TO_NEAREST_INT  0.5

/**
 * @brief Current Limit 5 device address setting.
 * @details Specified setting for device slave address selection of
 * Current Limit 5 Click driver.
 */
#define CURRENTLIMIT5_SET_DEV_ADDR          0x2F

/*! @} */ // currentlimit5_set

/**
 * @defgroup currentlimit5_map Current Limit 5 MikroBUS Map
 * @brief MikroBUS pin mapping of Current Limit 5 Click driver.
 */

/**
 * @addtogroup currentlimit5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Current Limit 5 Click to the selected MikroBUS.
 */
#define CURRENTLIMIT5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // currentlimit5_map
/*! @} */ // currentlimit5

/**
 * @brief Current Limit 5 Click context object.
 * @details Context object definition of Current Limit 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;          /**< Enable pin (Active High). */

    // Input pins
    digital_in_t  fault;        /**< Fault status pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} currentlimit5_t;

/**
 * @brief Current Limit 5 Click configuration object.
 * @details Configuration object definition of Current Limit 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;             /**< Enable pin. */
    pin_name_t  fault;          /**< Fault status pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} currentlimit5_cfg_t;

/**
 * @brief Current Limit 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CURRENTLIMIT5_OK = 0,
    CURRENTLIMIT5_ERROR = -1

} currentlimit5_return_value_t;

/**
 * @brief Current Limit 5 Click Ilimit values.
 * @details Predefined enum values for Ilimit.
 */
typedef enum
{
    CURRENTLIMIT5_ILIMIT_100mA = 0,
    CURRENTLIMIT5_ILIMIT_200mA,
    CURRENTLIMIT5_ILIMIT_300mA,
    CURRENTLIMIT5_ILIMIT_400mA,
    CURRENTLIMIT5_ILIMIT_500mA,
    CURRENTLIMIT5_ILIMIT_600mA,
    CURRENTLIMIT5_ILIMIT_700mA,
    CURRENTLIMIT5_ILIMIT_800mA,
    CURRENTLIMIT5_ILIMIT_900mA,
    CURRENTLIMIT5_ILIMIT_1000mA,
    CURRENTLIMIT5_ILIMIT_1100mA,

} currentlimit5_ilimit_t;

/*!
 * @addtogroup currentlimit5 Current Limit 5 Click Driver
 * @brief API for configuring and manipulating Current Limit 5 Click driver.
 * @{
 */

/**
 * @brief Current Limit 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #currentlimit5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void currentlimit5_cfg_setup ( currentlimit5_cfg_t *cfg );

/**
 * @brief Current Limit 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #currentlimit5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit5_init ( currentlimit5_t *ctx, currentlimit5_cfg_t *cfg );

/**
 * @brief Current Limit 5 default configuration function.
 * @details This function executes a default configuration of Current Limit 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t currentlimit5_default_cfg ( currentlimit5_t *ctx );

/**
 * @brief Current Limit 5 set ilimit function.
 * @details This function sets the current limit value by configuring the onboard digital potentiometer.
 * @param[in] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @param[in] ilimit : Ilimit value.
 * See #currentlimit5_ilimit_t enum definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t currentlimit5_set_ilimit ( currentlimit5_t *ctx, currentlimit5_ilimit_t ilimit );

/**
 * @brief Current Limit 5 get fault pin function.
 * @details This function returns the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @return @li @c  0 - Current limiting or thermal shutdown operation,
 *         @li @c  1 - Normal operation.
 * @note None.
 */
uint8_t currentlimit5_get_fault_pin ( currentlimit5_t *ctx );

/**
 * @brief Current Limit 5 enable limit function.
 * @details This function enables the current limiting switch.
 * @param[in] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void currentlimit5_enable_limit ( currentlimit5_t *ctx );

/**
 * @brief Current Limit 5 disable limit function.
 * @details This function disables the current limiting switch.
 * @param[in] ctx : Click context object.
 * See #currentlimit5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void currentlimit5_disable_limit ( currentlimit5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CURRENTLIMIT5_H

/*! @} */ // currentlimit5

// ------------------------------------------------------------------------ END
