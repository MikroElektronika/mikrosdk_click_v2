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
 * @file stepper23.h
 * @brief This file contains API for Stepper 23 Click Driver.
 */

#ifndef STEPPER23_H
#define STEPPER23_H

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
 * @addtogroup stepper23 Stepper 23 Click Driver
 * @brief API for configuring and manipulating Stepper 23 Click driver.
 * @{
 */

/**
 * @defgroup stepper23_reg Stepper 23 Registers List
 * @brief List of registers of Stepper 23 Click driver.
 */

/**
 * @addtogroup stepper23_reg
 * @{
 */

/**
 * @brief Stepper 23 PCA9555A registers.
 * @details Specified PCA9555A registers of Stepper 23 Click driver.
 */
#define STEPPER23_REG_INPUT_0                   0x00
#define STEPPER23_REG_INPUT_1                   0x01
#define STEPPER23_REG_OUTPUT_0                  0x02
#define STEPPER23_REG_OUTPUT_1                  0x03
#define STEPPER23_REG_POLARITY_0                0x04
#define STEPPER23_REG_POLARITY_1                0x05
#define STEPPER23_REG_CONFIG_0                  0x06
#define STEPPER23_REG_CONFIG_1                  0x07

/*! @} */ // stepper23_reg

/**
 * @defgroup stepper23_set Stepper 23 Registers Settings
 * @brief Settings for registers of Stepper 23 Click driver.
 */

/**
 * @addtogroup stepper23_set
 * @{
 */

/**
 * @brief Stepper 23 PCA9555A pin mask.
 * @details Specified PCA9555A pin mask of Stepper 23 Click driver.
 */
#define STEPPER23_P0_DMODE0_PIN                 0x01
#define STEPPER23_P0_DMODE1_PIN                 0x02
#define STEPPER23_P0_DMODE2_PIN                 0x04
#define STEPPER23_P0_DECAY1_PIN                 0x08
#define STEPPER23_P0_DECAY2_PIN                 0x10
#define STEPPER23_P0_TRQ0_PIN                   0x20
#define STEPPER23_P0_TRQ1_PIN                   0x40
#define STEPPER23_P0_SLEEP_X_PIN                0x80
#define STEPPER23_P1_LO1_PIN                    0x01
#define STEPPER23_P1_LO2_PIN                    0x02
#define STEPPER23_P1_MO_PIN                     0x04
#define STEPPER23_P1_RST_PIN                    0x08

/**
 * @brief Stepper 23 PCA9555A pin direction config.
 * @details Specified PCA9555A pin direction config of Stepper 23 Click driver.
 */
#define STEPPER23_P0_DEFAULT_CONFIG             0x00
#define STEPPER23_P1_DEFAULT_CONFIG             0xF7

/**
 * @brief Stepper 23 direction setting.
 * @details Specified setting for direction of Stepper 23 Click driver.
 */
#define STEPPER23_DIR_CW                        1
#define STEPPER23_DIR_CCW                       0

/**
 * @brief Stepper 23 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 23 Click driver.
 */
#define STEPPER23_PIN_LOW_LEVEL                 0
#define STEPPER23_PIN_HIGH_LEVEL                1

/**
 * @brief Stepper 23 step resolution setting.
 * @details Specified setting for step resolution of Stepper 23 Click driver.
 */
#define STEPPER23_MODE_FULL_STEP                0x00
#define STEPPER23_MODE_1_OVER_8                 0x01
#define STEPPER23_MODE_HALF_STEP_TYPE_B         0x02
#define STEPPER23_MODE_1_OVER_32                0x03
#define STEPPER23_MODE_HALF_STEP_TYPE_A         0x04
#define STEPPER23_MODE_1_OVER_16                0x05
#define STEPPER23_MODE_QUARTER_STEP             0x06
#define STEPPER23_MODE_MASK                     0x07

/**
 * @brief Stepper 23 torque setting.
 * @details Specified setting for torque of Stepper 23 Click driver.
 */
#define STEPPER23_TORQUE_100_PCT                0x00
#define STEPPER23_TORQUE_75_PCT                 0x01
#define STEPPER23_TORQUE_50_PCT                 0x02
#define STEPPER23_TORQUE_25_PCT                 0x03
#define STEPPER23_TORQUE_MASK                   0x03

/**
 * @brief Stepper 23 decay setting.
 * @details Specified setting for decay of Stepper 23 Click driver.
 */
#define STEPPER23_DECAY_MIXED                   0x00
#define STEPPER23_DECAY_SLOW                    0x01
#define STEPPER23_DECAY_FAST                    0x02
#define STEPPER23_DECAY_ADMD                    0x03
#define STEPPER23_DECAY_MASK                    0x03

/**
 * @brief Stepper 23 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER23_SPEED_VERY_SLOW               0
#define STEPPER23_SPEED_SLOW                    1
#define STEPPER23_SPEED_MEDIUM                  2
#define STEPPER23_SPEED_FAST                    3
#define STEPPER23_SPEED_VERY_FAST               4 

/**
 * @brief Stepper 23 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 23 Click driver.
 */
#define STEPPER23_DEVICE_ADDRESS_A1A0_00        0x20
#define STEPPER23_DEVICE_ADDRESS_A1A0_01        0x21
#define STEPPER23_DEVICE_ADDRESS_A1A0_10        0x22
#define STEPPER23_DEVICE_ADDRESS_A1A0_11        0x23

/*! @} */ // stepper23_set

/**
 * @defgroup stepper23_map Stepper 23 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 23 Click driver.
 */

/**
 * @addtogroup stepper23_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 23 Click to the selected MikroBUS.
 */
#define STEPPER23_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper23_map
/*! @} */ // stepper23

/**
 * @brief Stepper 23 Click context object.
 * @details Context object definition of Stepper 23 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t en;           /**< Enable output pin. */
    digital_out_t clk;          /**< Clock signal input pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9555A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper23_t;

/**
 * @brief Stepper 23 Click configuration object.
 * @details Configuration object definition of Stepper 23 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t en;              /**< Enable output pin. */
    pin_name_t clk;             /**< Clock signal input pin. */
    pin_name_t int_pin;         /**< PCA9555A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper23_cfg_t;

/**
 * @brief Stepper 23 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER23_OK = 0,
    STEPPER23_ERROR = -1

} stepper23_return_value_t;

/*!
 * @addtogroup stepper23 Stepper 23 Click Driver
 * @brief API for configuring and manipulating Stepper 23 Click driver.
 * @{
 */

/**
 * @brief Stepper 23 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper23_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper23_cfg_setup ( stepper23_cfg_t *cfg );

/**
 * @brief Stepper 23 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper23_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_init ( stepper23_t *ctx, stepper23_cfg_t *cfg );

/**
 * @brief Stepper 23 default configuration function.
 * @details This function executes a default configuration of Stepper 23
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper23_default_cfg ( stepper23_t *ctx );

/**
 * @brief Stepper 23 write register function.
 * @details This function writes a desired data byte to the selected PCA9555A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_write_register ( stepper23_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 23 read register function.
 * @details This function reads data from the selected PCA9555A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_read_register ( stepper23_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 23 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_step_mode ( stepper23_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 23 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_set_step_mode ( stepper23_t *ctx, uint8_t mode );

/**
 * @brief Stepper 23 get torque function.
 * @details This function reads the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_torque ( stepper23_t *ctx, uint8_t *torque );

/**
 * @brief Stepper 23 set torque function.
 * @details This function sets the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_set_torque ( stepper23_t *ctx, uint8_t torque );

/**
 * @brief Stepper 23 get decay function.
 * @details This function reads the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_decay ( stepper23_t *ctx, uint8_t *decay );

/**
 * @brief Stepper 23 set decay function.
 * @details This function sets the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_set_decay ( stepper23_t *ctx, uint8_t decay );

/**
 * @brief Stepper 23 get sleep x pin function.
 * @details This function reads the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_sleep_x_pin ( stepper23_t *ctx, uint8_t *state );

/**
 * @brief Stepper 23 set sleep x pin function.
 * @details This function sets the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_set_sleep_x_pin ( stepper23_t *ctx, uint8_t state );

/**
 * @brief Stepper 23 get lo1 pin function.
 * @details This function reads the lo1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_lo1_pin ( stepper23_t *ctx, uint8_t *state );

/**
 * @brief Stepper 23 get lo2 pin function.
 * @details This function reads the lo2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_lo2_pin ( stepper23_t *ctx, uint8_t *state );

/**
 * @brief Stepper 23 get mo pin function.
 * @details This function reads the mo pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_mo_pin ( stepper23_t *ctx, uint8_t *state );

/**
 * @brief Stepper 23 get RST pin function.
 * @details This function reads the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_get_rst_pin ( stepper23_t *ctx, uint8_t *state );

/**
 * @brief Stepper 23 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_set_rst_pin ( stepper23_t *ctx, uint8_t state );

/**
 * @brief Stepper 23 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper23_reset_device ( stepper23_t *ctx );

/**
 * @brief Stepper 23 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
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
void stepper23_drive_motor ( stepper23_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 23 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper23_enable_device ( stepper23_t *ctx );

/**
 * @brief Stepper 23 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper23_disable_device ( stepper23_t *ctx );

/**
 * @brief Stepper 23 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper23_set_direction ( stepper23_t *ctx, uint8_t dir );

/**
 * @brief Stepper 23 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper23_switch_direction ( stepper23_t *ctx );

/**
 * @brief Stepper 23 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper23_get_int_pin ( stepper23_t *ctx );

/**
 * @brief Stepper 23 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper23_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper23_set_clk_pin ( stepper23_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER23_H

/*! @} */ // stepper23

// ------------------------------------------------------------------------ END
