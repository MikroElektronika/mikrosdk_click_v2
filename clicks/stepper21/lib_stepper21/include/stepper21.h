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
 * @file stepper21.h
 * @brief This file contains API for Stepper 21 Click Driver.
 */

#ifndef STEPPER21_H
#define STEPPER21_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup stepper21 Stepper 21 Click Driver
 * @brief API for configuring and manipulating Stepper 21 Click driver.
 * @{
 */

/**
 * @defgroup stepper21_reg Stepper 21 Registers List
 * @brief List of registers of Stepper 21 Click driver.
 */

/**
 * @addtogroup stepper21_reg
 * @{
 */

/**
 * @brief Stepper 21 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 21 Click driver.
 */
#define STEPPER21_REG_INPUT                     0x00
#define STEPPER21_REG_OUTPUT                    0x01
#define STEPPER21_REG_POLARITY                  0x02
#define STEPPER21_REG_CONFIG                    0x03

/*! @} */ // stepper21_reg

/**
 * @defgroup stepper21_set Stepper 21 Registers Settings
 * @brief Settings for registers of Stepper 21 Click driver.
 */

/**
 * @addtogroup stepper21_set
 * @{
 */

/**
 * @brief Stepper 21 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 21 Click driver.
 */
#define STEPPER21_PIN_SLEEP                     0x01
#define STEPPER21_PIN_FAULT                     0x02
#define STEPPER21_PIN_DECAY                     0x04
#define STEPPER21_PIN_ENABLE                    0x08
#define STEPPER21_PIN_HOME                      0x10
#define STEPPER21_PIN_MODE0                     0x20
#define STEPPER21_PIN_MODE1                     0x40
#define STEPPER21_PIN_MODE2                     0x80

/**
 * @brief Stepper 21 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 21 Click driver.
 */
#define STEPPER21_DEFAULT_CONFIG                0x16

/**
 * @brief Stepper 21 direction setting.
 * @details Specified setting for direction of Stepper 21 Click driver.
 */
#define STEPPER21_DIR_CCW                       0
#define STEPPER21_DIR_CW                        1

/**
 * @brief Stepper 21 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 21 Click driver.
 */
#define STEPPER21_PIN_STATE_LOW                 0
#define STEPPER21_PIN_STATE_HIGH                1
#define STEPPER21_PIN_STATE_OPEN                2

/**
 * @brief Stepper 21 step resolution setting.
 * @details Specified setting for step resolution of Stepper 21 Click driver.
 */
#define STEPPER21_MODE_FULL_STEP                0x00
#define STEPPER21_MODE_HALF_STEP                0x01
#define STEPPER21_MODE_QUARTER_STEP             0x02
#define STEPPER21_MODE_1_OVER_8                 0x03
#define STEPPER21_MODE_1_OVER_16                0x04
#define STEPPER21_MODE_1_OVER_32                0x05
#define STEPPER21_MODE_MASK                     0x07

/**
 * @brief Stepper 21 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER21_SPEED_VERY_SLOW               0
#define STEPPER21_SPEED_SLOW                    1
#define STEPPER21_SPEED_MEDIUM                  2
#define STEPPER21_SPEED_FAST                    3
#define STEPPER21_SPEED_VERY_FAST               4 

/**
 * @brief Stepper 21 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 21 Click driver.
 */
#define STEPPER21_DEVICE_ADDRESS_A1A0_00        0x70
#define STEPPER21_DEVICE_ADDRESS_A1A0_01        0x71
#define STEPPER21_DEVICE_ADDRESS_A1A0_10        0x72
#define STEPPER21_DEVICE_ADDRESS_A1A0_11        0x73

/*! @} */ // stepper21_set

/**
 * @defgroup stepper21_map Stepper 21 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 21 Click driver.
 */

/**
 * @addtogroup stepper21_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 21 Click to the selected MikroBUS.
 */
#define STEPPER21_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper21_map
/*! @} */ // stepper21

/**
 * @brief Stepper 21 Click context object.
 * @details Context object definition of Stepper 21 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;              /**< Direction control pin. */
    digital_out_t rst;              /**< Electric angle reset and PCA9538A reset pin. */
    digital_out_t step;             /**< Step signal pin. */

    // Input pins
    digital_in_t int_pin;           /**< PCA9538A interrupt pin. */

    // Modules
    i2c_master_t i2c;               /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;          /**< Device slave address (used for I2C driver). */

} stepper21_t;

/**
 * @brief Stepper 21 Click configuration object.
 * @details Configuration object definition of Stepper 21 Click driver.
 */
typedef struct
{
    pin_name_t scl;                 /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                 /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t dir;                 /**< Direction control pin. */
    pin_name_t rst;                 /**< Electric angle reset and PCA9538A reset pin. */
    pin_name_t step;                /**< Step signal pin. */
    pin_name_t int_pin;             /**< PCA9538A interrupt pin. */

    uint32_t   i2c_speed;           /**< I2C serial speed. */
    uint8_t    i2c_address;         /**< I2C slave address. */

} stepper21_cfg_t;

/**
 * @brief Stepper 21 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER21_OK = 0,
    STEPPER21_ERROR = -1

} stepper21_return_value_t;

/*!
 * @addtogroup stepper21 Stepper 21 Click Driver
 * @brief API for configuring and manipulating Stepper 21 Click driver.
 * @{
 */

/**
 * @brief Stepper 21 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper21_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper21_cfg_setup ( stepper21_cfg_t *cfg );

/**
 * @brief Stepper 21 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper21_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_init ( stepper21_t *ctx, stepper21_cfg_t *cfg );

/**
 * @brief Stepper 21 default configuration function.
 * @details This function executes a default configuration of Stepper 21
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper21_default_cfg ( stepper21_t *ctx );

/**
 * @brief Stepper 21 write register function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_write_register ( stepper21_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 21 read register function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_read_register ( stepper21_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 21 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_step_mode ( stepper21_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 21 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_set_step_mode ( stepper21_t *ctx, uint8_t mode );

/**
 * @brief Stepper 21 get sleep pin function.
 * @details This function reads the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_sleep_pin ( stepper21_t *ctx, uint8_t *state );

/**
 * @brief Stepper 21 set sleep pin function.
 * @details This function sets the sleep pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_set_sleep_pin ( stepper21_t *ctx, uint8_t state );

/**
 * @brief Stepper 21 get fault pin function.
 * @details This function reads the fault pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_fault_pin ( stepper21_t *ctx, uint8_t *state );

/**
 * @brief Stepper 21 get decay pin function.
 * @details This function reads the decay pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state,
 *                     @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_decay_pin ( stepper21_t *ctx, uint8_t *state );

/**
 * @brief Stepper 21 set decay pin function.
 * @details This function sets the decay pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state,
 *                    @li @c 2 - Open state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_set_decay_pin ( stepper21_t *ctx, uint8_t state );

/**
 * @brief Stepper 21 get enable pin function.
 * @details This function reads the enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_enable_pin ( stepper21_t *ctx, uint8_t *state );

/**
 * @brief Stepper 21 set enable pin function.
 * @details This function sets the enable pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_set_enable_pin ( stepper21_t *ctx, uint8_t state );

/**
 * @brief Stepper 21 get home pin function.
 * @details This function reads the home pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_get_home_pin ( stepper21_t *ctx, uint8_t *state );

/**
 * @brief Stepper 21 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return None.
 * @note None.
 */
void stepper21_drive_motor ( stepper21_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 21 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_enable_device ( stepper21_t *ctx );

/**
 * @brief Stepper 21 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper21_disable_device ( stepper21_t *ctx );

/**
 * @brief Stepper 21 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper21_set_direction ( stepper21_t *ctx, uint8_t dir );

/**
 * @brief Stepper 21 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper21_switch_direction ( stepper21_t *ctx );

/**
 * @brief Stepper 21 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper21_set_rst_pin ( stepper21_t *ctx, uint8_t state );

/**
 * @brief Stepper 21 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper21_reset_device ( stepper21_t *ctx );

/**
 * @brief Stepper 21 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper21_get_int_pin ( stepper21_t *ctx );

/**
 * @brief Stepper 21 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper21_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper21_set_step_pin ( stepper21_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER21_H

/*! @} */ // stepper21

// ------------------------------------------------------------------------ END
