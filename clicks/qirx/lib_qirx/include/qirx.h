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
 * @file qirx.h
 * @brief This file contains API for Qi RX Click Driver.
 */

#ifndef QIRX_H
#define QIRX_H

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
 * @addtogroup qirx Qi RX Click Driver
 * @brief API for configuring and manipulating Qi RX Click driver.
 * @{
 */

/**
 * @defgroup qirx_set Qi RX Registers Settings
 * @brief Settings for registers of Qi RX Click driver.
 */

/**
 * @addtogroup qirx_set
 * @{
 */

/**
 * @brief Qi RX description setting.
 * @details Specified setting for description of Qi RX Click driver.
 */
#define QIRX_RESOLUTION      4096
#define QIRX_12_BIT_DATA     0x0FFF
/**
 * @brief Qi RX device address setting.
 * @details Specified setting for device slave address selection of
 * Qi RX Click driver.
 */
#define QIRX_SET_DEV_ADDR  0x4D

/*! @} */ // qirx_set

/**
 * @defgroup qirx_map Qi RX MikroBUS Map
 * @brief MikroBUS pin mapping of Qi RX Click driver.
 */

/**
 * @addtogroup qirx_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Qi RX Click to the selected MikroBUS.
 */
#define QIRX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )

/*! @} */ // qirx_map
/*! @} */ // qirx

/**
 * @brief Qi RX Click context object.
 * @details Context object definition of Qi RX Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} qirx_t;

/**
 * @brief Qi RX Click configuration object.
 * @details Configuration object definition of Qi RX Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} qirx_cfg_t;

/**
 * @brief Qi RX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    QIRX_OK = 0,
    QIRX_ERROR = -1

} qirx_return_value_t;

/*!
 * @addtogroup qirx Qi RX Click Driver
 * @brief API for configuring and manipulating Qi RX Click driver.
 * @{
 */

/**
 * @brief Qi RX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #qirx_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void qirx_cfg_setup ( qirx_cfg_t *cfg );

/**
 * @brief Qi RX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #qirx_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #qirx_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t qirx_init ( qirx_t *ctx, qirx_cfg_t *cfg );

/**
 * @brief Read data function. 
 * @details Function is used to read raw data from MCP3221.
 * @param[in] ctx : Click context object.
 * See #qirx_t object definition for detailed explanation.
 * @returns Result 16-bit value that represents ADC value from output register.
**/
uint16_t qirx_read_data ( qirx_t *ctx );

/**
 * @brief Read voltage function.
 * @details Function is used to calculate voltage of the connected battery.
 * @param[in] ctx : Click context object.
 * See #qirx_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 12-bit value that represents voltage in millivolts.
**/
uint16_t qirx_read_voltage ( qirx_t *ctx, uint16_t v_ref );

#ifdef __cplusplus
}
#endif
#endif // QIRX_H

/*! @} */ // qirx

// ------------------------------------------------------------------------ END
