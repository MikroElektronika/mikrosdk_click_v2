/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file thermo32.h
 * @brief This file contains API for Thermo 32 Click Driver.
 */

#ifndef THERMO32_H
#define THERMO32_H

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
 * @addtogroup thermo32 Thermo 32 Click Driver
 * @brief API for configuring and manipulating Thermo 32 Click driver.
 * @{
 */

/**
 * @defgroup thermo32_reg Thermo 32 Registers List
 * @brief List of registers of Thermo 32 Click driver.
 */

/**
 * @addtogroup thermo32_reg
 * @{
 */

/**
 * @brief Thermo 32 register list.
 * @details Specified register list of Thermo 32 Click driver.
 */
#define THERMO32_REG_TEMPERATURE                    0x00
#define THERMO32_REG_CONFIGURATION                  0x01
#define THERMO32_REG_TLOW                           0x02
#define THERMO32_REG_THIGH                          0x03

/*! @} */ // thermo32_reg

/**
 * @defgroup thermo32_set Thermo 32 Registers Settings
 * @brief Settings for registers of Thermo 32 Click driver.
 */

/**
 * @addtogroup thermo32_set
 * @{
 */

/**
 * @brief Thermo 32 CONFIGURATION register setting.
 * @details Specified setting for CONFIGURATION register of Thermo 32 Click driver.
 */
#define THERMO32_CONFIGURATION_CONV_RATE_0_25_HZ    0x0000
#define THERMO32_CONFIGURATION_CONV_RATE_1_HZ       0x2000
#define THERMO32_CONFIGURATION_CONV_RATE_4_HZ       0x4000
#define THERMO32_CONFIGURATION_CONV_RATE_16_HZ      0x6000
#define THERMO32_CONFIGURATION_CONV_RATE_MASK       0x6000
#define THERMO32_CONFIGURATION_THIGH_FLAG           0x1000
#define THERMO32_CONFIGURATION_TLOW_FLAG            0x0800
#define THERMO32_CONFIGURATION_THERMOSTAT_COMP      0x0000
#define THERMO32_CONFIGURATION_THERMOSTAT_INT       0x0400
#define THERMO32_CONFIGURATION_THERMOSTAT_MASK      0x0400
#define THERMO32_CONFIGURATION_MODE_SHUTDOWN        0x0000
#define THERMO32_CONFIGURATION_MODE_ONE_SHOT        0x0100
#define THERMO32_CONFIGURATION_MODE_CONTINUOUS      0x0200
#define THERMO32_CONFIGURATION_MODE_MASK            0x0300
#define THERMO32_CONFIGURATION_POLARITY_LOW         0x0000
#define THERMO32_CONFIGURATION_POLARITY_HIGH        0x0080
#define THERMO32_CONFIGURATION_POLARITY_MASK        0x0080
#define THERMO32_CONFIGURATION_HYS_0C               0x0000
#define THERMO32_CONFIGURATION_HYS_1C               0x0010
#define THERMO32_CONFIGURATION_HYS_2C               0x0020
#define THERMO32_CONFIGURATION_HYS_3C               0x0030
#define THERMO32_CONFIGURATION_HYS_MASK             0x0030

/**
 * @brief Thermo 32 temperature calculation setting.
 * @details Specified setting for temperature calculation of Thermo 32 Click driver.
 */
#define THERMO32_TEMP_RESOLUTION                    0.0625f

/**
 * @brief Thermo 32 temperature alert limit setting.
 * @details Specified setting for temperature alert limit of Thermo 32 Click driver.
 */
#define THERMO32_TEMP_LIMIT_LOW                     20.0
#define THERMO32_TEMP_LIMIT_HIGH                    35.0

/**
 * @brief Thermo 32 measurement mode setting.
 * @details Specified setting for measurement mode of Thermo 32 Click driver.
 */
#define THERMO32_MEASUREMENT_MODE_ONE_SHOT          0
#define THERMO32_MEASUREMENT_MODE_CONT_0_25_HZ      1
#define THERMO32_MEASUREMENT_MODE_CONT_1_HZ         2
#define THERMO32_MEASUREMENT_MODE_CONT_4_HZ         3
#define THERMO32_MEASUREMENT_MODE_CONT_16_HZ        4

/**
 * @brief Thermo 32 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 32 Click driver.
 */
#define THERMO32_DEVICE_ADDRESS_GND                 0x48
#define THERMO32_DEVICE_ADDRESS_VCC                 0x49
#define THERMO32_DEVICE_ADDRESS_SDA                 0x4A

/*! @} */ // thermo32_set

/**
 * @defgroup thermo32_map Thermo 32 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 32 Click driver.
 */

/**
 * @addtogroup thermo32_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 32 Click to the selected MikroBUS.
 */
#define THERMO32_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo32_map
/*! @} */ // thermo32

/**
 * @brief Thermo 32 Click context object.
 * @details Context object definition of Thermo 32 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t alert;         /**< Alert pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo32_t;

/**
 * @brief Thermo 32 Click configuration object.
 * @details Configuration object definition of Thermo 32 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t alert;           /**< Alert pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo32_cfg_t;

/**
 * @brief Thermo 32 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO32_OK = 0,
    THERMO32_ERROR = -1

} thermo32_return_value_t;

/*!
 * @addtogroup thermo32 Thermo 32 Click Driver
 * @brief API for configuring and manipulating Thermo 32 Click driver.
 * @{
 */

/**
 * @brief Thermo 32 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo32_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo32_cfg_setup ( thermo32_cfg_t *cfg );

/**
 * @brief Thermo 32 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo32_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_init ( thermo32_t *ctx, thermo32_cfg_t *cfg );

/**
 * @brief Thermo 32 default configuration function.
 * @details This function executes a default configuration of Thermo 32
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo32_default_cfg ( thermo32_t *ctx );

/**
 * @brief Thermo 32 set configuration function.
 * @details This function writes the configuration register with the provided configuration byte.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] config : Configuration byte to be written to @ref THERMO32_REG_CONFIGURATION.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_set_config ( thermo32_t *ctx, uint16_t config );

/**
 * @brief Thermo 32 get configuration function.
 * @details This function reads the configuration register into the provided buffer.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] config : Output configuration byte read from @ref THERMO32_REG_CONFIGURATION.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_config ( thermo32_t *ctx, uint16_t *config );

/**
 * @brief Thermo 32 get raw temperature function.
 * @details This function reads the raw temperature value from the temperature register.
 * The value is returned as a signed 12-bit right-aligned sample.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp_raw : Output raw temperature (12-bit signed, right-aligned).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_temp_raw ( thermo32_t *ctx, int16_t *temp_raw );

/**
 * @brief Thermo 32 get temperature function.
 * @details This function reads the temperature and converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp : Output temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_temp ( thermo32_t *ctx, float *temp );

/**
 * @brief Thermo 32 set high limit (raw) function.
 * @details This function writes the raw high temperature limit to the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] temp_high_raw : Raw high temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_set_high_limit_raw ( thermo32_t *ctx, int16_t temp_high_raw );

/**
 * @brief Thermo 32 set low limit (raw) function.
 * @details This function writes the raw low temperature limit to the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] temp_low_raw : Raw low temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_set_low_limit_raw ( thermo32_t *ctx, int16_t temp_low_raw );

/**
 * @brief Thermo 32 set high limit function.
 * @details This function converts the high temperature limit from degrees Celsius to raw format
 * and writes it to the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] temp_high : High temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_set_high_limit ( thermo32_t *ctx, float temp_high );

/**
 * @brief Thermo 32 set low limit function.
 * @details This function converts the low temperature limit from degrees Celsius to raw format
 * and writes it to the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] temp_low : Low temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_set_low_limit ( thermo32_t *ctx, float temp_low );

/**
 * @brief Thermo 32 get high limit (raw) function.
 * @details This function reads the raw high temperature limit from the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp_high_raw : Output raw high temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_high_limit_raw ( thermo32_t *ctx, int16_t *temp_high_raw );

/**
 * @brief Thermo 32 get low limit (raw) function.
 * @details This function reads the raw low temperature limit from the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp_low_raw : Output raw low temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_low_limit_raw ( thermo32_t *ctx, int16_t *temp_low_raw );

/**
 * @brief Thermo 32 get high limit function.
 * @details This function reads the high temperature limit and converts it to degrees Celsius
 * using the device resolution @ref THERMO32_TEMP_RESOLUTION.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp_high : Output high temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_high_limit ( thermo32_t *ctx, float *temp_high );

/**
 * @brief Thermo 32 get low limit function.
 * @details This function reads the low temperature limit and converts it to degrees Celsius
 * using the device resolution @ref THERMO32_TEMP_RESOLUTION.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[out] temp_low : Output low temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_get_low_limit ( thermo32_t *ctx, float *temp_low );

/**
 * @brief Thermo 32 get alert pin function.
 * @details This function reads the digital state of the ALERT pin.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @return @li @c  0 - ALERT pin logic low,
 *         @li @c  1 - ALERT pin logic high.
 * @note None.
 */
uint8_t thermo32_get_alert_pin ( thermo32_t *ctx );

/**
 * @brief Thermo 32 clear alert function.
 * @details This function clears the alert interrupt by reading the configuration register.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_clear_alert ( thermo32_t *ctx );

/**
 * @brief Thermo 32 start measurement function.
 * @details This function starts a temperature measurement according to the selected
 * measurement @p mode. One-shot mode performs a single conversion from shutdown state,
 * while continuous modes configure the conversion time and run periodic measurements.
 * @param[in] ctx : Click context object.
 * See #thermo32_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode (one-shot or continuous conversion time).
 * Use predefined THERMO32_MEASUREMENT_MODE_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo32_start_measurement ( thermo32_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // THERMO32_H

/*! @} */ // thermo32

// ------------------------------------------------------------------------ END
