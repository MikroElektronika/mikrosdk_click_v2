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
 * @file thermo18.h
 * @brief This file contains API for Thermo 18 Click Driver.
 */

#ifndef THERMO18_H
#define THERMO18_H

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
 * @addtogroup thermo18 Thermo 18 Click Driver
 * @brief API for configuring and manipulating Thermo 18 Click driver.
 * @{
 */

/**
 * @defgroup thermo18_reg Thermo 18 Registers List
 * @brief List of registers of Thermo 18 Click driver.
 */

/**
 * @addtogroup thermo18_reg
 * @{
 */

/**
 * @brief Thermo 18 description register.
 * @details Specified register for description of Thermo 18 Click driver.
 */
#define THERMO18_REG_DEVICE_ID                  0x1
#define THERMO18_REG_T_H_LIMIT                  0x2
#define THERMO18_REG_T_L_LIMIT                  0x3
#define THERMO18_REG_CTRL                       0x4
#define THERMO18_REG_STATUS                     0x5
#define THERMO18_REG_DATA_T_L                   0x6
#define THERMO18_REG_DATA_T_H                   0x7
#define THERMO18_REG_SOFT_RESET                 0xC

/*! @} */ // thermo18_reg

/**
 * @defgroup thermo18_set Thermo 18 Registers Settings
 * @brief Settings for registers of Thermo 18 Click driver.
 */

/**
 * @addtogroup thermo18_set
 * @{
 */

/**
 * @brief Thermo 18 control settings.
 * @details Specified setting for control register of Thermo 18 Click driver.
 */
#define THERMO18_CONTROL_ONESHOT_ENABLED        0x01
#define THERMO18_CONTROL_CONTINOUS_ENABLED      0x04

/**
 * @brief Thermo 18 description status values.
 * @details Specified values for status of Thermo 18 Click driver.
 */
#define THERMO18_STATUS_DATA_READY              0x00
#define THERMO18_STATUS_DATA_BUSY               0x01
#define THERMO18_STATUS_OVERTEMPERATURE         0x02
#define THERMO18_STATUS_UNDERTEMPERATURE        0x04

/**
 * @brief Thermo 18 description setting.
 * @details Specified setting for description of Thermo 18 Click driver.
 */
#define THERMO18_DEVICE_ID                      0xA0

/**
 * @brief Thermo 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 18 Click driver.
 */
#define THERMO18_SET_DEV_ADDR                   0x3F

/*! @} */ // thermo18_set

/**
 * @defgroup thermo18_map Thermo 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 18 Click driver.
 */

/**
 * @addtogroup thermo18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 18 Click to the selected MikroBUS.
 */
#define THERMO18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo18_map
/*! @} */ // thermo18

/**
 * @brief Thermo 18 Click context object.
 * @details Context object definition of Thermo 18 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;  /**< Interrupt. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

} thermo18_t;

/**
 * @brief Thermo 18 Click configuration object.
 * @details Configuration object definition of Thermo 18 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} thermo18_cfg_t;

/**
 * @brief Thermo 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   THERMO18_OK = 0,
   THERMO18_ERROR = -1

} thermo18_return_value_t;

/*!
 * @addtogroup thermo18 Thermo 18 Click Driver
 * @brief API for configuring and manipulating Thermo 18 Click driver.
 * @{
 */

/**
 * @brief Thermo 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo18_cfg_setup ( thermo18_cfg_t *cfg );

/**
 * @brief Thermo 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_init ( thermo18_t *ctx, thermo18_cfg_t *cfg );

/**
 * @brief Thermo 18 default configuration function.
 * @details This function executes a default configuration of Thermo 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo18_default_cfg ( thermo18_t *ctx );

/**
 * @brief Thermo 18 I2C writing function.
 * @details This function writes a data byte to the selected register.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_generic_write ( thermo18_t *ctx, uint8_t reg, uint8_t tx_data ) ;

/**
 * @brief Thermo 18 I2C reading function.
 * @details This function reads a data byte from the selected register.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_generic_read ( thermo18_t *ctx, uint8_t reg, uint8_t *rx_data );

/**
 * @brief Reads and calculates temperature value.
 * @details Reads data registers and calculates temperature value
 * in degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @param[out] temperature : Output temperature data in degC.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_read_temperature ( thermo18_t *ctx, float *temperature );

/**
 * @brief Resets device.
 * @details Sends commands to reset device and clears it, when resets is done.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_reset ( thermo18_t *ctx );

/**
 * @brief Get interrput status.
 * @details Reads interrupt pin state.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @return Interrupt pin state
 */
uint8_t thermo18_get_interrupt ( thermo18_t *ctx );

/**
 * @brief Sets temperature threshold.
 * @details Calculates and sets undertemperature thresholds 
 * or overtemperature threshold.
 * @param[in] ctx : Click context object.
 * See #thermo18_t object definition for detailed explanation.
 * @param[in] threshold_reg : Can be @b THERMO18_REG_T_H_LIMIT 
 * or @b THERMO18_REG_T_L_LIMIT.
 * @param[in] threshold_limit : Temperature threshold to set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t thermo18_set_temperature_threshold ( thermo18_t *ctx, uint8_t threshold_reg, float threshold_limit );

#ifdef __cplusplus
}
#endif
#endif // THERMO18_H

/*! @} */ // thermo18

// ------------------------------------------------------------------------ END
