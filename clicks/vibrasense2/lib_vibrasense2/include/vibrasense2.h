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
 * @file vibrasense2.h
 * @brief This file contains API for Vibra Sense 2 Click Driver.
 */

#ifndef VIBRASENSE2_H
#define VIBRASENSE2_H

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
 * @addtogroup vibrasense2 Vibra Sense 2 Click Driver
 * @brief API for configuring and manipulating Vibra Sense 2 Click driver.
 * @{
 */

/**
 * @defgroup vibrasense2_set Vibra Sense 2 Registers Settings
 * @brief Settings for registers of Vibra Sense 2 Click driver.
 */

/**
 * @addtogroup vibrasense2_set
 * @{
 */

/**
 * @brief Vibra Sense 2 description setting.
 * @details Specified setting for description of Vibra Sense 2 Click driver.
 */

/**
 * @brief Vibra Sense 2 resolution setting.
 * @details Specified setting for resolution of Vibra Sense 2 Click driver.
 */
#define VIBRASENSE2_RESOLUTION           4096
#define VIBRASENSE2_12_BIT_DATA          0x0FFF

/**
 * @brief Vibra Sense 2 Vibration levels.
 * @details Vibration levels of Vibra Sense 2 Click driver.
 */
#define VIBRASENSE2_VIBRA_LVL_ERROR     -1
#define VIBRASENSE2_VIBRA_LVL_0          0
#define VIBRASENSE2_VIBRA_LVL_1          1
#define VIBRASENSE2_VIBRA_LVL_2          2
#define VIBRASENSE2_VIBRA_LVL_3          3
#define VIBRASENSE2_VIBRA_LVL_4          4
#define VIBRASENSE2_VIBRA_LVL_5          5
#define VIBRASENSE2_VIBRA_LVL_6          6

/**
 * @brief Vibra Sense 2 device address setting.
 * @details Specified setting for device slave address selection of
 * Vibra Sense 2 Click driver.
 */
#define VIBRASENSE2_SET_DEV_ADDR  0x4D

/*! @} */ // vibrasense2_set

/**
 * @defgroup vibrasense2_map Vibra Sense 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Vibra Sense 2 Click driver.
 */

/**
 * @addtogroup vibrasense2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vibra Sense 2 Click to the selected MikroBUS.
 */
#define VIBRASENSE2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA )
/*! @} */ // vibrasense2_map
/*! @} */ // vibrasense2

/**
 * @brief Vibra Sense 2 Click context object.
 * @details Context object definition of Vibra Sense 2 Click driver.
 */
typedef struct
{
    // Modules
    i2c_master_t i2c;                                /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;                           /**< Device slave address (used for I2C driver). */

} vibrasense2_t;

/**
 * @brief Vibra Sense 2 Click configuration object.
 * @details Configuration object definition of Vibra Sense 2 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    uint32_t  i2c_speed;                                /**< I2C serial speed. */
    uint8_t   i2c_address;                              /**< I2C slave address. */

} vibrasense2_cfg_t;

/**
 * @brief Vibra Sense 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VIBRASENSE2_OK = 0,
   VIBRASENSE2_ERROR = -1

} vibrasense2_return_value_t;

/*!
 * @addtogroup vibrasense2 Vibra Sense 2 Click Driver
 * @brief API for configuring and manipulating Vibra Sense 2 Click driver.
 * @{
 */

/**
 * @brief Vibra Sense 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vibrasense2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vibrasense2_cfg_setup ( vibrasense2_cfg_t *cfg );

/**
 * @brief Vibra Sense 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vibrasense2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibrasense2_init ( vibrasense2_t *ctx, vibrasense2_cfg_t *cfg );

/**
 * @brief Vibra Sense 2 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibrasense2_generic_write ( vibrasense2_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Vibra Sense 2 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_buf : Output read data.
 * @param[in] rx_len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t vibrasense2_generic_read ( vibrasense2_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );

/**
 * @brief Read data function.
 * @details Function is used to read raw data from MCP3221.
 * @param[in] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @returns Result 16-bit value that represents ADC value from output register
**/
uint16_t vibrasense2_read_data ( vibrasense2_t *ctx );

/**
 * @brief Read voltage function.
 * @details Function is used to calculate piezo voltage in millivolts.
 * @param[in] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @param[in] v_ref : 16-bit value representing power supply voltage.
 * @returns Result 16-bit value that represents voltage in millivolts.
**/
uint16_t vibrasense2_read_voltage ( vibrasense2_t *ctx, uint16_t v_ref );

/**
 * @brief Get Vibration Level function.
 * @details Function is used to get vibration level.
 * @param[in] ctx : Click context object.
 * See #vibrasense2_t object definition for detailed explanation.
 * @returns 8-bit value representing vibration level or error occurence.
 *
 * @note Vibration levels available: "No vibrations", "Marginal", "Slight",
 * "Enhanced", "Moderate", "High", and "Severe" vibrations detected.
**/
int8_t vibrasense2_vibration_level ( vibrasense2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VIBRASENSE2_H

/*! @} */ // vibrasense2

// ------------------------------------------------------------------------ END
