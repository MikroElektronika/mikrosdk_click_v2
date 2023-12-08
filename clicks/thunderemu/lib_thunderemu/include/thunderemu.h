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
 * @file thunderemu.h
 * @brief This file contains API for Thunder EMU Click Driver.
 */

#ifndef THUNDEREMU_H
#define THUNDEREMU_H

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
 * @addtogroup thunderemu Thunder EMU Click Driver
 * @brief API for configuring and manipulating Thunder EMU Click driver.
 * @{
 */

/**
 * @defgroup thunderemu_set Thunder EMU Registers Settings
 * @brief Settings for registers of Thunder EMU Click driver.
 */

/**
 * @addtogroup thunderemu_set
 * @{
 */

/**
 * @brief Thunder EMU mode setting.
 * @details Specified setting for mode of Thunder EMU Click driver.
 */
#define THUNDEREMU_MODE_CLOSE                   0
#define THUNDEREMU_MODE_MID                     1
#define THUNDEREMU_MODE_FAR                     2

/**
 * @brief Thunder EMU dac mode setting.
 * @details Specified setting for dac mode of Thunder EMU Click driver.
 */
#define THUNDEREMU_DAC_MODE_FAST_NORMAL         0x00
#define THUNDEREMU_DAC_MODE_FAST_PDOWN_1K       0x10
#define THUNDEREMU_DAC_MODE_FAST_PDOWN_100K     0x20
#define THUNDEREMU_DAC_MODE_FAST_PDOWN_500K     0x30
#define THUNDEREMU_DAC_MODE_EEPROM_NORMAL       0x60
#define THUNDEREMU_DAC_MODE_EEPROM_PDOWN_1K     0x62
#define THUNDEREMU_DAC_MODE_EEPROM_PDOWN_100K   0x64
#define THUNDEREMU_DAC_MODE_EEPROM_PDOWN_500K   0x66

/**
 * @brief Thunder EMU DAC range setting.
 * @details Specified setting for DAC range of Thunder EMU Click driver.
 */
#define THUNDEREMU_DAC_OUT_MIN                  0x0000
#define THUNDEREMU_DAC_OUT_MAX                  0x0FFF

/**
 * @brief Thunder EMU device address setting.
 * @details Specified setting for device slave address selection of
 * Thunder EMU Click driver.
 */
#define THUNDEREMU_DEVICE_ADDRESS_0             0x60
#define THUNDEREMU_DEVICE_ADDRESS_1             0x61

/*! @} */ // thunderemu_set

/**
 * @defgroup thunderemu_map Thunder EMU MikroBUS Map
 * @brief MikroBUS pin mapping of Thunder EMU Click driver.
 */

/**
 * @addtogroup thunderemu_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thunder EMU Click to the selected MikroBUS.
 */
#define THUNDEREMU_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.close = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.led = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mid = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.far_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thunderemu_map
/*! @} */ // thunderemu

/**
 * @brief Thunder EMU Click context object.
 * @details Context object definition of Thunder EMU Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t led;          /**< Thunder LED pin. */

    // Input pins
    digital_in_t close;         /**< Close range thunder pin indicator. */
    digital_in_t mid;           /**< Mid range thunder pin indicator. */
    digital_in_t far_pin;       /**< Far range thunder pin indicator. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thunderemu_t;

/**
 * @brief Thunder EMU Click configuration object.
 * @details Configuration object definition of Thunder EMU Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t led;             /**< Thunder LED pin. */
    pin_name_t close;           /**< Close range thunder pin indicator. */
    pin_name_t mid;             /**< Mid range thunder pin indicator. */
    pin_name_t far_pin;         /**< Far range thunder pin indicator. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thunderemu_cfg_t;

/**
 * @brief Thunder EMU Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THUNDEREMU_OK = 0,
    THUNDEREMU_ERROR = -1

} thunderemu_return_value_t;

/*!
 * @addtogroup thunderemu Thunder EMU Click Driver
 * @brief API for configuring and manipulating Thunder EMU Click driver.
 * @{
 */

/**
 * @brief Thunder EMU configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thunderemu_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thunderemu_cfg_setup ( thunderemu_cfg_t *cfg );

/**
 * @brief Thunder EMU initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thunderemu_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thunderemu_init ( thunderemu_t *ctx, thunderemu_cfg_t *cfg );

/**
 * @brief Thunder EMU default configuration function.
 * @details This function executes a default configuration of Thunder EMU
 * click board.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thunderemu_default_cfg ( thunderemu_t *ctx );

/**
 * @brief Thunder EMU set dac output function.
 * @details This function sets the DAC output data and mode by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @param[in] mode : DAC operating mode, refer to THUNDEREMU_DAC_MODE_x macros definition for more details.
 * @param[in] dac_data : DAC 12-bit raw data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thunderemu_set_dac_output ( thunderemu_t *ctx, uint8_t mode, uint16_t dac_data );

/**
 * @brief Thunder EMU generate thunder function.
 * @details This function generates close, mid or far range thunder signal by setting the predefined
 * DAC output profile at the specific timing.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Close range thunder signal,
 *                   @li @c 1 - Mid range thunder signal,
 *                   @li @c 2 - Far range thunder signal.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note DAC profile is calibrated for ranges of up to 15cm between inductors.
 */
err_t thunderemu_generate_thunder ( thunderemu_t *ctx, uint8_t mode );

/**
 * @brief Thunder EMU led enable function.
 * @details This function enables the thunder LED indicator.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thunderemu_led_enable ( thunderemu_t *ctx );

/**
 * @brief Thunder EMU led disable function.
 * @details This function disables the thunder LED indicator.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void thunderemu_led_disable ( thunderemu_t *ctx );

/**
 * @brief Thunder EMU get close pin function.
 * @details This function returns the CLOSE pin logic state.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thunderemu_get_close_pin ( thunderemu_t *ctx );

/**
 * @brief Thunder EMU get mid pin function.
 * @details This function returns the MID pin logic state.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thunderemu_get_mid_pin ( thunderemu_t *ctx );

/**
 * @brief Thunder EMU get far pin function.
 * @details This function returns the FAR pin logic state.
 * @param[in] ctx : Click context object.
 * See #thunderemu_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t thunderemu_get_far_pin ( thunderemu_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THUNDEREMU_H

/*! @} */ // thunderemu

// ------------------------------------------------------------------------ END
