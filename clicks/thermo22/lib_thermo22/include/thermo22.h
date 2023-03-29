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
 * @file thermo22.h
 * @brief This file contains API for Thermo 22 Click Driver.
 */

#ifndef THERMO22_H
#define THERMO22_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup thermo22 Thermo 22 Click Driver
 * @brief API for configuring and manipulating Thermo 22 Click driver.
 * @{
 */

/**
 * @defgroup thermo22_reg Thermo 22 Registers List
 * @brief List of registers of Thermo 22 Click driver.
 */

/**
 * @addtogroup thermo22_reg
 * @{
 */

/**
 * @brief Thermo 22 register list.
 * @details Specified register list of Thermo 22 Click driver.
 */
#define THERMO22_REG_TEMPERATURE            0x00
#define THERMO22_REG_CONFIGURATION          0x01
#define THERMO22_REG_TEMPERATURE_LOW        0x02
#define THERMO22_REG_TEMPERATURE_HIGH       0x03
#define THERMO22_REG_ONE_SHOT               0x04

/*! @} */ // thermo22_reg

/**
 * @defgroup thermo22_set Thermo 22 Registers Settings
 * @brief Settings for registers of Thermo 22 Click driver.
 */

/**
 * @addtogroup thermo22_set
 * @{
 */

/**
 * @brief Thermo 22 Configuration register setting.
 * @details Specified setting for Configuration register of Thermo 22 Click driver.
 */
#define THERMO22_CONFIG_ONESHOT_DIS         0x00
#define THERMO22_CONFIG_ONESHOT_EN          0x20
#define THERMO22_CONFIG_FAULT_QUEUE_1       0x00
#define THERMO22_CONFIG_FAULT_QUEUE_2       0x08
#define THERMO22_CONFIG_FAULT_QUEUE_4       0x10
#define THERMO22_CONFIG_FAULT_QUEUE_6       0x18
#define THERMO22_CONFIG_ALERT_ACTIVE_LOW    0x00
#define THERMO22_CONFIG_ALERT_ACTIVE_HIGH   0x04
#define THERMO22_CONFIG_ALERT_COMPARATOR    0x00
#define THERMO22_CONFIG_ALERT_INTERRUPT     0x02
#define THERMO22_CONFIG_SHUTDOWN_DIS        0x00
#define THERMO22_CONFIG_SHUTDOWN_EN         0x01

/**
 * @brief Thermo 22 temperature resolution value.
 * @details Specified temperature resolution value of Thermo 22 Click driver.
 */
#define THERMO22_TEMPERATURE_RESOLUTION     0.0625
#define THERMO22_TEMPERATURE_MAX            128.0
#define THERMO22_TEMPERATURE_MIN            -128.0
#define THERMO22_TEMPERATURE_ALERT_LIMIT    35.0

/**
 * @brief Thermo 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 22 Click driver.
 */
#define THERMO22_DEV_ADDR_A2A1A0_000        0x48
#define THERMO22_DEV_ADDR_A2A1A0_001        0x49
#define THERMO22_DEV_ADDR_A2A1A0_010        0x4A
#define THERMO22_DEV_ADDR_A2A1A0_011        0x4B
#define THERMO22_DEV_ADDR_A2A1A0_100        0x4C
#define THERMO22_DEV_ADDR_A2A1A0_101        0x4D
#define THERMO22_DEV_ADDR_A2A1A0_110        0x4E
#define THERMO22_DEV_ADDR_A2A1A0_111        0x4F

/*! @} */ // thermo22_set

/**
 * @defgroup thermo22_map Thermo 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 22 Click driver.
 */

/**
 * @addtogroup thermo22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 22 Click to the selected MikroBUS.
 */
#define THERMO22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo22_map
/*! @} */ // thermo22

/**
 * @brief Thermo 22 Click context object.
 * @details Context object definition of Thermo 22 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t  int_pin;      /**< Overtemperature alert interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo22_t;

/**
 * @brief Thermo 22 Click configuration object.
 * @details Configuration object definition of Thermo 22 Click driver.
 */
typedef struct
{
    pin_name_t  scl;            /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;            /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  int_pin;        /**< Overtemperature alert interrupt pin. */

    uint32_t  i2c_speed;        /**< I2C serial speed. */
    uint8_t   i2c_address;      /**< I2C slave address. */

} thermo22_cfg_t;

/**
 * @brief Thermo 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO22_OK = 0,
    THERMO22_ERROR = -1

} thermo22_return_value_t;

/*!
 * @addtogroup thermo22 Thermo 22 Click Driver
 * @brief API for configuring and manipulating Thermo 22 Click driver.
 * @{
 */

/**
 * @brief Thermo 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo22_cfg_setup ( thermo22_cfg_t *cfg );

/**
 * @brief Thermo 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_init ( thermo22_t *ctx, thermo22_cfg_t *cfg );

/**
 * @brief Thermo 22 default configuration function.
 * @details This function executes a default configuration of Thermo 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo22_default_cfg ( thermo22_t *ctx );

/**
 * @brief Thermo 22 write config function.
 * @details This function writes a config byte to the desired config register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[in] config : Config byte to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_write_config ( thermo22_t *ctx, uint8_t config );

/**
 * @brief Thermo 22 read config function.
 * @details This function reads a config byte from the desired config register
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[out] config : Config byte read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_read_config ( thermo22_t *ctx, uint8_t *config );

/**
 * @brief Thermo 22 read temperature function.
 * @details This function reads the temperature data in Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[out] temperature : Temperature in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_read_temperature ( thermo22_t *ctx, float *temperature );

/**
 * @brief Thermo 22 set temperature low limit function.
 * @details This function sets the temperature low limit at which the overtemperature alert flag
 * is being cleared.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[out] low_limit : Temperature low limit in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_set_temperature_low_limit ( thermo22_t *ctx, float low_limit );

/**
 * @brief Thermo 22 set temperature high limit function.
 * @details This function sets the temperature high limit at which the overtemperature alert flag
 * is being set.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @param[out] high_limit : Temperature high limit in Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo22_set_temperature_high_limit ( thermo22_t *ctx, float high_limit );

/**
 * @brief Thermo 22 get int pin function.
 * @details This function returns the INT pin logic state which indicates the overtemperature alert.
 * @param[in] ctx : Click context object.
 * See #thermo22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thermo22_get_int_pin ( thermo22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO22_H

/*! @} */ // thermo22

// ------------------------------------------------------------------------ END
