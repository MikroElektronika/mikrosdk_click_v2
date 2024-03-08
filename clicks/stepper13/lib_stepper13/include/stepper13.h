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
 * @file stepper13.h
 * @brief This file contains API for Stepper 13 Click Driver.
 */

#ifndef STEPPER13_H
#define STEPPER13_H

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
 * @addtogroup stepper13 Stepper 13 Click Driver
 * @brief API for configuring and manipulating Stepper 13 Click driver.
 * @{
 */

/**
 * @defgroup stepper13_reg Stepper 13 Registers List
 * @brief List of registers of Stepper 13 Click driver.
 */

/**
 * @addtogroup stepper13_reg
 * @{
 */

/**
 * @brief Stepper 13 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 13 Click driver.
 */
#define STEPPER13_PCA9538A_REG_INPUT            0x00
#define STEPPER13_PCA9538A_REG_OUTPUT           0x01
#define STEPPER13_PCA9538A_REG_POLARITY         0x02
#define STEPPER13_PCA9538A_REG_CONFIG           0x03

/*! @} */ // stepper13_reg

/**
 * @defgroup stepper13_set Stepper 13 Registers Settings
 * @brief Settings for registers of Stepper 13 Click driver.
 */

/**
 * @addtogroup stepper13_set
 * @{
 */


/**
 * @brief Stepper 13 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 13 Click driver.
 */
#define STEPPER13_PIN_MS1                       0x01
#define STEPPER13_PIN_MS2                       0x02
#define STEPPER13_PIN_MS_MASK                   0x03
#define STEPPER13_PIN_FAULT                     0x04
#define STEPPER13_PIN_DIR                       0x08
#define STEPPER13_PIN_SLEEP                     0x10
#define STEPPER13_PIN_ENABLE                    0x20

/**
 * @brief Stepper 13 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 13 Click driver.
 */
#define STEPPER13_PCA9538A_DEFAULT_CONFIG       0xC4

/**
 * @brief Stepper 13 direction setting.
 * @details Specified setting for direction of Stepper 13 Click driver.
 */
#define STEPPER13_DIR_CW                        0
#define STEPPER13_DIR_CCW                       1

/**
 * @brief Stepper 13 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 13 Click driver.
 */
#define STEPPER13_PIN_STATE_LOW                 0
#define STEPPER13_PIN_STATE_HIGH                1

/**
 * @brief Stepper 13 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER13_SPEED_VERY_SLOW               0
#define STEPPER13_SPEED_SLOW                    1
#define STEPPER13_SPEED_MEDIUM                  2
#define STEPPER13_SPEED_FAST                    3
#define STEPPER13_SPEED_VERY_FAST               4

/**
 * @brief Stepper 13 step resolution setting.
 * @details Specified setting for step resolution of Stepper 13 Click driver.
 */
#define STEPPER13_MODE_FULL_STEP                0
#define STEPPER13_MODE_HALF_STEP                1
#define STEPPER13_MODE_QUARTER_STEP             2
#define STEPPER13_MODE_1_OVER_8                 3

/**
 * @brief Stepper 13 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 13 Click driver.
 */
#define STEPPER13_DEVICE_ADDRESS_A1A0_00        0x70
#define STEPPER13_DEVICE_ADDRESS_A1A0_01        0x71
#define STEPPER13_DEVICE_ADDRESS_A1A0_10        0x72
#define STEPPER13_DEVICE_ADDRESS_A1A0_11        0x73

/*! @} */ // stepper13_set

/**
 * @defgroup stepper13_map Stepper 13 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 13 Click driver.
 */

/**
 * @addtogroup stepper13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 13 Click to the selected MikroBUS.
 */
#define STEPPER13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper13_map
/*! @} */ // stepper13

/**
 * @brief Stepper 13 Click context object.
 * @details Context object definition of Stepper 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;          /**< PCA9538A reset pin. */
    digital_out_t step;         /**< Step signal pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper13_t;

/**
 * @brief Stepper 13 Click configuration object.
 * @details Configuration object definition of Stepper 13 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t rst;             /**< PCA9538A reset pin. */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t int_pin;         /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper13_cfg_t;

/**
 * @brief Stepper 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER13_OK = 0,
    STEPPER13_ERROR = -1

} stepper13_return_value_t;

/*!
 * @addtogroup stepper13 Stepper 13 Click Driver
 * @brief API for configuring and manipulating Stepper 13 Click driver.
 * @{
 */

/**
 * @brief Stepper 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper13_cfg_setup ( stepper13_cfg_t *cfg );

/**
 * @brief Stepper 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_init ( stepper13_t *ctx, stepper13_cfg_t *cfg );

/**
 * @brief Stepper 13 default configuration function.
 * @details This function executes a default configuration of Stepper 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper13_default_cfg ( stepper13_t *ctx );

/**
 * @brief Stepper 13 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_pca_write_reg ( stepper13_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 13 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_pca_read_reg ( stepper13_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 13 get fault pin function.
 * @details This function reads the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_get_fault_pin ( stepper13_t *ctx, uint8_t *state );

/**
 * @brief Stepper 13 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_enable_device ( stepper13_t *ctx );

/**
 * @brief Stepper 13 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_disable_device ( stepper13_t *ctx );

/**
 * @brief Stepper 13 enable sleep function.
 * @details This function enables the sleep mode by setting the SLEEP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_enable_sleep ( stepper13_t *ctx );

/**
 * @brief Stepper 13 disable sleep function.
 * @details This function disables the sleep mode by setting the SLEEP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_disable_sleep ( stepper13_t *ctx );

/**
 * @brief Stepper 13 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_set_direction ( stepper13_t *ctx, uint8_t dir );

/**
 * @brief Stepper 13 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_switch_direction ( stepper13_t *ctx );

/**
 * @brief Stepper 13 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper13_set_rst_pin ( stepper13_t *ctx, uint8_t state );

/**
 * @brief Stepper 13 reset device function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper13_reset_pca ( stepper13_t *ctx );

/**
 * @brief Stepper 13 get INT pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper13_get_int_pin ( stepper13_t *ctx );

/**
 * @brief Stepper 13 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper13_set_step_pin ( stepper13_t *ctx, uint8_t state );

/**
 * @brief Stepper 13 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution:
 *                    @li @c 0 - Full step,
 *                    @li @c 1 - 1/2 step,
 *                    @li @c 2 - 1/4 step,
 *                    @li @c 3 - 1/8 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_get_step_mode ( stepper13_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 13 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution:
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - 1/2 step,
 *                   @li @c 2 - 1/4 step,
 *                   @li @c 3 - 1/8 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_set_step_mode ( stepper13_t *ctx, uint8_t mode );

/**
 * @brief Stepper 13 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper13_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper13_drive_motor ( stepper13_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER13_H

/*! @} */ // stepper13

// ------------------------------------------------------------------------ END
