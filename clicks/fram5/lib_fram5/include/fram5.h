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
 * @file fram5.h
 * @brief This file contains API for FRAM 5 Click Driver.
 */

#ifndef FRAM5_H
#define FRAM5_H

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
 * @addtogroup fram5 FRAM 5 Click Driver
 * @brief API for configuring and manipulating FRAM 5 Click driver.
 * @{
 */

/**
 * @defgroup fram5_set FRAM 5 Registers Settings
 * @brief Settings for registers of FRAM 5 Click driver.
 */

/**
 * @addtogroup fram5_set
 * @{
 */

/**
 * @brief FRAM 5 memory address range.
 * @details Specified memory address range of FRAM 5 Click driver.
 */
#define FRAM5_MIN_ADDRESS                       0x00000
#define FRAM5_MAX_ADDRESS                       0x1FFFF

/**
 * @brief FRAM 5 slave ID.
 * @details Specified slave ID of FRAM 5 Click driver.
 */
#define FRAM5_SLAVE_ID                          0x7C

/**
 * @brief FRAM 5 device ID.
 * @details Specified device ID of FRAM 5 Click driver.
 */
#define FRAM5_MANUFACTURER_ID_DENSITY           0x44

/**
 * @brief FRAM 5 device address setting.
 * @details Specified setting for device slave address selection of
 * FRAM 5 Click driver.
 */
#define FRAM5_DEVICE_ADDRESS_A2A1_00            0x50
#define FRAM5_DEVICE_ADDRESS_A2A1_01            0x52
#define FRAM5_DEVICE_ADDRESS_A2A1_10            0x54
#define FRAM5_DEVICE_ADDRESS_A2A1_11            0x56

/*! @} */ // fram5_set

/**
 * @defgroup fram5_map FRAM 5 MikroBUS Map
 * @brief MikroBUS pin mapping of FRAM 5 Click driver.
 */

/**
 * @addtogroup fram5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of FRAM 5 Click to the selected MikroBUS.
 */
#define FRAM5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.wp = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // fram5_map
/*! @} */ // fram5

/**
 * @brief FRAM 5 Click context object.
 * @details Context object definition of FRAM 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  wp;          /**< Write-protect pin (Active-high). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} fram5_t;

/**
 * @brief FRAM 5 Click configuration object.
 * @details Configuration object definition of FRAM 5 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  wp;             /**< Write-protect pin (Active-high). */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} fram5_cfg_t;

/**
 * @brief FRAM 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    FRAM5_OK = 0,
    FRAM5_ERROR = -1

} fram5_return_value_t;

/*!
 * @addtogroup fram5 FRAM 5 Click Driver
 * @brief API for configuring and manipulating FRAM 5 Click driver.
 * @{
 */

/**
 * @brief FRAM 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #fram5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void fram5_cfg_setup ( fram5_cfg_t *cfg );

/**
 * @brief FRAM 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #fram5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram5_init ( fram5_t *ctx, fram5_cfg_t *cfg );

/**
 * @brief FRAM 5 memory write function.
 * @details This function writes a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFF].
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram5_memory_write ( fram5_t *ctx, uint32_t address, uint8_t *data_in, uint8_t len );

/**
 * @brief FRAM 5 memory read function.
 * @details This function reads a desired number of data bytes starting from the
 * selected memory address.
 * @param[in] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @param[in] address : Starting memory address [0x00000-0x1FFFF].
 * @param[out] data_out : Read data output.
 * @param[in] len : Number of data bytes.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram5_memory_read ( fram5_t *ctx, uint32_t address, uint8_t *data_out, uint8_t len );

/**
 * @brief FRAM 5 check communication function.
 * @details This function checks the communication by reading and verifying the device ID.
 * @param[in] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t fram5_check_communication ( fram5_t *ctx );

/**
 * @brief FRAM 5 write protect function.
 * @details This function write protects the entire memory by setting the WP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void fram5_write_protect ( fram5_t *ctx );

/**
 * @brief FRAM 5 write enable function.
 * @details This function disables memory write-protect by setting the WP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #fram5_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void fram5_write_enable ( fram5_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // FRAM5_H

/*! @} */ // fram5

// ------------------------------------------------------------------------ END
