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
 * @file proximity14.h
 * @brief This file contains API for Proximity 14 Click Driver.
 */

#ifndef PROXIMITY14_H
#define PROXIMITY14_H

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
 * @addtogroup proximity14 Proximity 14 Click Driver
 * @brief API for configuring and manipulating Proximity 14 Click driver.
 * @{
 */

/**
 * @defgroup proximity14_reg Proximity 14 Registers List
 * @brief List of registers of Proximity 14 Click driver.
 */

/**
 * @addtogroup proximity14_reg
 * @{
 */

/**
 * @brief Proximity 14 description register.
 * @details Specified register for description of Proximity 14 Click driver.
 */
#define PROXIMITY14_REG_CFG1            0x00
#define PROXIMITY14_REG_CFG2            0x03
#define PROXIMITY14_REG_CFG3            0x04
#define PROXIMITY14_REG_CFG4            0x08
#define PROXIMITY14_REG_THRESHOLD_LOW   0x05
#define PROXIMITY14_REG_THRESHOLD_HIGH  0x06
#define PROXIMITY14_REG_CANCELLATION    0x07
#define PROXIMITY14_REG_DATA            0xF8
#define PROXIMITY14_REG_INT_FLAG        0xF9
#define PROXIMITY14_REG_ID              0xFA
#define PROXIMITY14_REG_AC_DATA         0xFB

/*! @} */ // proximity14_reg

/**
 * @defgroup proximity14_set Proximity 14 Registers Settings
 * @brief Settings for registers of Proximity 14 Click driver.
 */

/**
 * @addtogroup proximity14_set
 * @{
 */

/**
 * @brief Proximity 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Proximity 14 Click driver.
 */
#define PROXIMITY14_SET_DEV_ADDR  0x60

/*! @} */ // proximity14_set

/**
 * @defgroup proximity14_map Proximity 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Proximity 14 Click driver.
 */

/**
 * @addtogroup proximity14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Proximity 14 Click to the selected MikroBUS.
 */
#define PROXIMITY14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // proximity14_map
/*! @} */ // proximity14

/**
 * @brief Proximity 14 Click context object.
 * @details Context object definition of Proximity 14 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;  /**< Description. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} proximity14_t;

/**
 * @brief Proximity 14 Click configuration object.
 * @details Configuration object definition of Proximity 14 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;    /**< Description. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} proximity14_cfg_t;

/**
 * @brief Proximity 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   PROXIMITY14_OK = 0,
   PROXIMITY14_ERROR = -1

} proximity14_return_value_t;

/*!
 * @addtogroup proximity14 Proximity 14 Click Driver
 * @brief API for configuring and manipulating Proximity 14 Click driver.
 * @{
 */

/**
 * @brief Proximity 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #proximity14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void proximity14_cfg_setup ( proximity14_cfg_t *cfg );

/**
 * @brief Proximity 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #proximity14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #proximity14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t proximity14_init ( proximity14_t *ctx, proximity14_cfg_t *cfg );

/**
 * @brief Proximity 14 default configuration function.
 * @details This function executes a default configuration of Proximity 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #proximity14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t proximity14_default_cfg ( proximity14_t *ctx );

/**
 * @brief Writing function.
 * @details This function writes a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t proximity14_generic_write ( proximity14_t *ctx, uint8_t reg, uint16_t tx_data );

/**
 * @brief Reading function.
 * @details This function reads a data to the selected register.
 * @param[in] ctx : Click context object.
 * See #proximity14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t proximity14_generic_read ( proximity14_t *ctx, uint8_t reg, uint16_t *rx_data );

/**
 * @brief Get INT pin state.
 * @details This function reads logic state of interrupt pin.
 * @param[in] ctx : Click context object.
 * See #proximity14_t object definition for detailed explanation.
 * @return Logic state pin
 */
uint8_t proximity14_get_int ( proximity14_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // PROXIMITY14_H

/*! @} */ // proximity14

// ------------------------------------------------------------------------ END
