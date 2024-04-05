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
 * @file thermo28.h
 * @brief This file contains API for Thermo 28 Click Driver.
 */

#ifndef THERMO28_H
#define THERMO28_H

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

#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup thermo28 Thermo 28 Click Driver
 * @brief API for configuring and manipulating Thermo 28 Click driver.
 * @{
 */

/**
 * @defgroup thermo28_reg Thermo 28 Registers List
 * @brief List of registers of Thermo 28 Click driver.
 */

/**
 * @addtogroup thermo28_reg
 * @{
 */

/**
 * @brief Thermo 28 description register.
 * @details Specified register for description of Thermo 28 Click driver.
 */
#define THERMO28_REG_TVAL                  0x00
#define THERMO28_REG_CONFIG                0x01
#define THERMO28_REG_TLOW                  0x02
#define THERMO28_REG_THIGH                 0x03

/*! @} */ // thermo28_reg

/**
 * @defgroup thermo28_set Thermo 28 Registers Settings
 * @brief Settings for registers of Thermo 28 Click driver.
 */

/**
 * @addtogroup thermo28_set
 * @{
 */

/**
 * @brief Thermo 28 description setting.
 * @details Specified setting for description of Thermo 28 Click driver.
 */
#define THERMO28_CFG_DEFAULT_CONFIG        0x40A0
#define THERMO28_CFG_SINGLE_SHOT           0x8000
#define THERMO28_CONV_RATE_BIT_MASK        0x00C0
#define THERMO28_STATE_BIT_MASK            0x0100
#define THERMO28_CONSEC_FAULTS_BIT_MASK    0x3000
#define THERMO28_ALERT_BIT_MASK            0x0200
#define THERMO28_SINGLE_SHOT_BIT_MASK      0x8000

/**
 * @brief Thermo 28 device address setting.
 * @details Specified setting for device slave address selection of
 * Thermo 28 Click driver.
 */
#define THERMO28_DEVICE_ADDRESS_VSS        0x48
#define THERMO28_DEVICE_ADDRESS_VDD        0x49
#define THERMO28_DEVICE_ADDRESS_SDA        0x4A
#define THERMO28_DEVICE_ADDRESS_SCL        0x4B

/*! @} */ // thermo28_set

/**
 * @defgroup thermo28_map Thermo 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Thermo 28 Click driver.
 */

/**
 * @addtogroup thermo28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Thermo 28 Click to the selected MikroBUS.
 */
#define THERMO28_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // thermo28_map
/*! @} */ // thermo28

/**
 * @brief Thermo 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    THERMO28_OK     = 0,
    THERMO28_ERROR = -1

} thermo28_return_value_t;

/**
 * @brief Thermo 28 Click conversion rate value data.
 * @details Predefined enum values for driver conversion rate values.
 */
typedef enum
{
    THERMO28_CONV_RATE025 = 0x0000,
    THERMO28_CONV_RATE1   = 0x0040,
    THERMO28_CONV_RATE4   = 0x0080,
    THERMO28_CONV_RATE8   = 0x00C0

} thermo28_conv_rate_t;

/**
 * @brief Thermo 28 Click sleep mode value data.
 * @details Predefined enum values for driver sleep mode values.
 */
typedef enum
{
    THERMO28_STATE_SLEEP  = 0x0100,
    THERMO28_STATE_ACTIVE = 0x0000

} thermo28_device_mode_t;

/**
 * @brief Thermo 28 Click interrupt mode value data.
 * @details Predefined enum values for driver interrupt mode values.
 */
typedef enum
{
    THERMO28_ALERT_INTERRUPT  = 0x0200,
    THERMO28_ALERT_COMPARATOR = 0x0000

} thermo28_alert_mode_t;


/**
 * @brief Thermo 28 Click polarity of the alert output value data.
 * @details Predefined enum values for driver polarity of the alert output values.
 */
typedef enum
{
    THERMO28_ALERT_ACTIVE_LOW  = 0x0000,
    THERMO28_ALERT_ACTIVE_HIGH = 0x0400

} thermo28_alert_polarity_t;

/**
 * @brief Thermo 28 Click consecutive faults value data.
 * @details Predefined enum values for driver consecutive faults values.
 */
typedef enum
{
    THERMO28_CONSEC_FAULTS1 = 0x0000,
    THERMO28_CONSEC_FAULTS2 = 0x1000,
    THERMO28_CONSEC_FAULTS3 = 0x2000,
    THERMO28_CONSEC_FAULTS4 = 0x3000

} thermo28_consec_faults_t;

/**
 * @brief Thermo 28 Click measurement mode value data.
 * @details Predefined enum values for driver measurement mode values.
 */
typedef enum
{
    THERMO28_SINGLE_SHOT_NO_CONVERSION    = 0x0000,
    THERMO28_SINGLE_SHOT_START_CONVERSION = 0x8000

} thermo28_single_shot_t;

/**
 * @brief Thermo 28 Click context object.
 * @details Context object definition of Thermo 28 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;    /**< Alert pin - indicates alarm condition. */

    // Modules
    i2c_master_t i2c;        /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;   /**< Device slave address (used for I2C driver). */

} thermo28_t;

/**
 * @brief Thermo 28 Click configuration object.
 * @details Configuration object definition of Thermo 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t int_pin;         /**< Alert pin - indicates alarm condition. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} thermo28_cfg_t;

/**
 * @brief Thermo 28 Click configuration object.
 * @details Configuration object definition of Thermo 28 Click driver.
 */
typedef struct
{
    thermo28_conv_rate_t conv_rate;
    thermo28_device_mode_t device_mode;
    thermo28_alert_mode_t alert_mode;
    thermo28_alert_polarity_t alert_polarity;
    thermo28_consec_faults_t consecutive_faults;
    thermo28_single_shot_t single_shot;

} thermo28_config_t;

/*!
 * @addtogroup thermo28 Thermo 28 Click Driver
 * @brief API for configuring and manipulating Thermo 28 Click driver.
 * @{
 */

/**
 * @brief Thermo 28 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #thermo28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void thermo28_cfg_setup ( thermo28_cfg_t *cfg );

/**
 * @brief Thermo 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #thermo28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_init ( thermo28_t *ctx, thermo28_cfg_t *cfg );

/**
 * @brief Thermo 28 default configuration function.
 * @details This function executes a default configuration of Thermo 28
 * click board.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t thermo28_default_cfg ( thermo28_t *ctx );

/**
 * @brief Thermo 28 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_generic_write ( thermo28_t *ctx, uint8_t reg, uint8_t *data_in, uint8_t len );

/**
 * @brief Thermo 28 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_generic_read ( thermo28_t *ctx, uint8_t reg, uint8_t *data_out, uint8_t len );

/**
 * @brief Thermo 28 get temperature function.
 * @details This function reads the temperature raw data measurements and converts them to degrees Celsius.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[out] temperature : Temperature measurements in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_get_temperature ( thermo28_t *ctx, float *temperature );

/**
 * @brief Thermo 28 set alert limits function.
 * @details This function sets temperature alert limits values.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[in] alert_min : Minimum temperature alert limit in degrees Celsius.
 * @param[in] alert_max : Maximum temperature alert limit in degrees Celsius.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_set_alert_limits ( thermo28_t *ctx, float alert_min, float alert_max );

/**
 * @brief Thermo 28 set configuration function.
 * @details This function executes a configuration of the AS6221 Digital Temperature Sensor
 * on the Thermo 28 click board™.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @param[in] config : Device configuration object object.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_set_config ( thermo28_t *ctx, thermo28_config_t config );

/**
 * @brief Thermo 28 set continuous conversion function.
 * @details This function executes a configuration of the continuous conversion
 * on the Thermo 28 click board™.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_set_continuous_conversion ( thermo28_t *ctx );

/**
 * @brief Thermo 28 set device working mode function.
 * @details This function executes a configuration of the device's working mode
 * on the Thermo 28 click board™.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_set_sleep_mode ( thermo28_t *ctx );

/**
 * @brief Thermo 28 set trigger single-shot function.
 * @details This function executes a trigger single-shot mode
 * on the Thermo 28 click board™.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t thermo28_set_trigger_single_shot ( thermo28_t *ctx );

/**
 * @brief Thermo 28 set alert status function.
 * @details This function gets alert status by reading the states of the INT pin
 * of the Thermo 28 click board™.
 * @param[in] ctx : Click context object.
 * See #thermo28_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t thermo28_get_int_pin ( thermo28_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // THERMO28_H

/*! @} */ // thermo28

// ------------------------------------------------------------------------ END
