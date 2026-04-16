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
 * @file thermo10.h
 * @brief This file contains API for Thermo 10 Click Driver.
 */

#ifndef THERMO10_H
#define THERMO10_H

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
 * @addtogroup thermo10 Thermo 10 Click Driver
 * @brief API for configuring and manipulating Thermo 10 Click driver.
 * @{
 */

/**
 * @defgroup thermo10_reg Thermo 10 Registers List
 * @brief List of registers of Thermo 10 Click driver.
 */

/**
 * @addtogroup thermo10_reg
 * @{
 */

/**
 * @brief Thermo 10 register list.
 * @details Specified register list of Thermo 10 Click driver.
 */
#define THERMO10_REG_TEMP                           0x00
#define THERMO10_REG_CONF                           0x01
#define THERMO10_REG_TLOW                           0x02
#define THERMO10_REG_THIGH                          0x03

/*! @} */ // thermo10_reg

/**
 * @defgroup thermo10_set Thermo 10 Registers Settings
 * @brief Settings for registers of Thermo 10 Click driver.
 */

/**
 * @addtogroup thermo10_set
 * @{
 */

/**
 * @brief Thermo 10 CONF register setting.
 * @details Specified setting for CONF register of Thermo 10 Click driver.
 */
#define THERMO10_CONF_ONE_SHOT                      0x80
#define THERMO10_CONF_CONV_TIME_27_5_MS             0x00
#define THERMO10_CONF_CONV_TIME_55_MS               0x20
#define THERMO10_CONF_CONV_TIME_110_MS              0x40
#define THERMO10_CONF_CONV_TIME_220_MS              0x60
#define THERMO10_CONF_CONV_TIME_MASK                0x60
#define THERMO10_CONF_FAULT_QUEUE_1                 0x00
#define THERMO10_CONF_FAULT_QUEUE_2                 0x08
#define THERMO10_CONF_FAULT_QUEUE_4                 0x10
#define THERMO10_CONF_FAULT_QUEUE_6                 0x18
#define THERMO10_CONF_FAULT_QUEUE_MASK              0x18
#define THERMO10_CONF_POL_ACTIVE_LOW                0x00
#define THERMO10_CONF_POL_ACTIVE_HIGH               0x04
#define THERMO10_CONF_POL_MASK                      0x04
#define THERMO10_CONF_THERMOSTAT_MODE_COMP          0x00
#define THERMO10_CONF_THERMOSTAT_MODE_INT           0x02
#define THERMO10_CONF_THERMOSTAT_MODE_MASK          0x02
#define THERMO10_CONF_SHUTDOWN_MODE_CONTINUOUS      0x00
#define THERMO10_CONF_SHUTDOWN_MODE_SHUTDOWN        0x01
#define THERMO10_CONF_SHUTDOWN_MODE_MASK            0x01

/**
 * @brief Thermo 10 data resolution setting.
 * @details Specified setting for data resolution of Thermo 10 Click driver.
 */
#define THERMO10_DATA_RESOLUTION                    0.0625

/**
 * @brief Thermo 10 temperature alert limit setting.
 * @details Specified setting for temperature alert limit of Thermo 10 Click driver.
 */
#define THERMO10_TEMP_LIMIT_LOW                     35.0
#define THERMO10_TEMP_LIMIT_HIGH                    40.0

/**
 * @brief Thermo 10 measurement mode setting.
 * @details Specified setting for measurement mode of Thermo 10 Click driver.
 */
#define THERMO10_MEASUREMENT_MODE_ONE_SHOT          0
#define THERMO10_MEASUREMENT_MODE_CONT_27_5_MS      1
#define THERMO10_MEASUREMENT_MODE_CONT_55_MS        2
#define THERMO10_MEASUREMENT_MODE_CONT_110_MS       3
#define THERMO10_MEASUREMENT_MODE_CONT_220_MS       4

/**
 * @brief Thermo 10 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 10 Click driver.
 */
#define THERMO10_DEVICE_ADDRESS_A2A1A0_000          0x48
#define THERMO10_DEVICE_ADDRESS_A2A1A0_001          0x49
#define THERMO10_DEVICE_ADDRESS_A2A1A0_010          0x4A
#define THERMO10_DEVICE_ADDRESS_A2A1A0_011          0x4B
#define THERMO10_DEVICE_ADDRESS_A2A1A0_100          0x4C
#define THERMO10_DEVICE_ADDRESS_A2A1A0_101          0x4D
#define THERMO10_DEVICE_ADDRESS_A2A1A0_110          0x4E
#define THERMO10_DEVICE_ADDRESS_A2A1A0_111          0x4F

/*! @} */ // thermo10_set

/**
 * @defgroup thermo10_map Thermo 10 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 10 Click driver.
 */

/**
 * @addtogroup thermo10_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 10 Click to the selected MikroBUS.
 */
#define THERMO10_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.alert = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo10_map
/*! @} */ // thermo10

/**
 * @brief Thermo 10 Click context object.
 * @details Context object definition of Thermo 10 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable device pin (active high). */

    // Input pins
    digital_in_t alert;         /**< Alert pin (active low). */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} thermo10_t;

/**
 * @brief Thermo 10 Click configuration object.
 * @details Configuration object definition of Thermo 10 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable device pin (active high). */
    pin_name_t alert;           /**< Alert pin (active low). */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo10_cfg_t;

/**
 * @brief Thermo 10 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO10_OK = 0,
    THERMO10_ERROR = -1

} thermo10_return_value_t;

/*!
 * @addtogroup thermo10 Thermo 10 Click Driver
 * @brief API for configuring and manipulating Thermo 10 Click driver.
 * @{
 */

/**
 * @brief Thermo 10 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo10_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo10_cfg_setup ( thermo10_cfg_t *cfg );

/**
 * @brief Thermo 10 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo10_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_init ( thermo10_t *ctx, thermo10_cfg_t *cfg );

/**
 * @brief Thermo 10 default configuration function.
 * @details This function executes a default configuration of Thermo 10
 * Click board.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo10_default_cfg ( thermo10_t *ctx );

/**
 * @brief Thermo 10 set configuration function.
 * @details This function writes the configuration register with the provided configuration byte.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] config : Configuration byte to be written to @ref THERMO10_REG_CONF.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_set_config ( thermo10_t *ctx, uint8_t config );

/**
 * @brief Thermo 10 get configuration function.
 * @details This function reads the configuration register into the provided buffer.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] config : Output configuration byte read from @ref THERMO10_REG_CONF.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_config ( thermo10_t *ctx, uint8_t *config );

/**
 * @brief Thermo 10 get raw temperature function.
 * @details This function reads the raw temperature value from the temperature register.
 * The value is returned as a signed 12-bit right-aligned sample.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp_raw : Output raw temperature (12-bit signed, right-aligned).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_temp_raw ( thermo10_t *ctx, int16_t *temp_raw );

/**
 * @brief Thermo 10 get temperature function.
 * @details This function reads the temperature and converts it to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp : Output temperature in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_temp ( thermo10_t *ctx, float *temp );

/**
 * @brief Thermo 10 set high limit (raw) function.
 * @details This function writes the raw high temperature limit to the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] temp_high_raw : Raw high temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_set_high_limit_raw ( thermo10_t *ctx, int16_t temp_high_raw );

/**
 * @brief Thermo 10 set low limit (raw) function.
 * @details This function writes the raw low temperature limit to the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] temp_low_raw : Raw low temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_set_low_limit_raw ( thermo10_t *ctx, int16_t temp_low_raw );

/**
 * @brief Thermo 10 set high limit function.
 * @details This function converts the high temperature limit from degrees Celsius to raw format
 * and writes it to the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] temp_high : High temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_set_high_limit ( thermo10_t *ctx, float temp_high );

/**
 * @brief Thermo 10 set low limit function.
 * @details This function converts the low temperature limit from degrees Celsius to raw format
 * and writes it to the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] temp_low : Low temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_set_low_limit ( thermo10_t *ctx, float temp_low );

/**
 * @brief Thermo 10 get high limit (raw) function.
 * @details This function reads the raw high temperature limit from the high limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp_high_raw : Output raw high temperature threshold (12-bit.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_high_limit_raw ( thermo10_t *ctx, int16_t *temp_high_raw );

/**
 * @brief Thermo 10 get low limit (raw) function.
 * @details This function reads the raw low temperature limit from the low limit register.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp_low_raw : Output raw low temperature threshold (12-bit).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_low_limit_raw ( thermo10_t *ctx, int16_t *temp_low_raw );

/**
 * @brief Thermo 10 get high limit function.
 * @details This function reads the high temperature limit and converts it to degrees Celsius
 * using the device resolution @ref THERMO10_DATA_RESOLUTION.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp_high : Output high temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_high_limit ( thermo10_t *ctx, float *temp_high );

/**
 * @brief Thermo 10 get low limit function.
 * @details This function reads the low temperature limit and converts it to degrees Celsius
 * using the device resolution @ref THERMO10_DATA_RESOLUTION.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[out] temp_low : Output low temperature threshold in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_get_low_limit ( thermo10_t *ctx, float *temp_low );

/**
 * @brief Thermo 10 enable device function.
 * @details This function enables the device by setting the EN pin to logic high state
 * and waits 100 ms for the device to stabilize.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @return None.
 * @note Wait time allows the device to power up and become ready for operation.
 */
void thermo10_enable_device ( thermo10_t *ctx );

/**
 * @brief Thermo 10 disable device function.
 * @details This function disables the device by setting the EN pin to logic low state
 * and waits 100 ms for the device to fully power down.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @return None.
 * @note Wait time ensures complete shutdown of the device.
 */
void thermo10_disable_device ( thermo10_t *ctx );

/**
 * @brief Thermo 10 get alert pin function.
 * @details This function reads the digital state of the ALERT pin.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @return @li @c  0 - ALERT pin logic low,
 *         @li @c  1 - ALERT pin logic high.
 * @note None.
 */
uint8_t thermo10_get_alert_pin ( thermo10_t *ctx );

/**
 * @brief Thermo 10 start measurement function.
 * @details This function starts a temperature measurement according to the selected
 * measurement @p mode. One-shot mode performs a single conversion from shutdown state,
 * while continuous modes configure the conversion time and run periodic measurements.
 * @param[in] ctx : Click context object.
 * See #thermo10_t object definition for detailed explanation.
 * @param[in] mode : Measurement mode (one-shot or continuous conversion time).
 * Use predefined THERMO10_MEASUREMENT_MODE_ macros.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo10_start_measurement ( thermo10_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // THERMO10_H

/*! @} */ // thermo10

// ------------------------------------------------------------------------ END
