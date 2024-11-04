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
 * @file stepper17.h
 * @brief This file contains API for Stepper 17 Click Driver.
 */

#ifndef STEPPER17_H
#define STEPPER17_H

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
 * @addtogroup stepper17 Stepper 17 Click Driver
 * @brief API for configuring and manipulating Stepper 17 Click driver.
 * @{
 */

/**
 * @defgroup stepper17_reg Stepper 17 Registers List
 * @brief List of registers of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_reg
 * @{
 */

/**
 * @brief Stepper 17 PCA9555A registers.
 * @details Specified PCA9555A registers of Stepper 17 Click driver.
 */
#define STEPPER17_REG_INPUT_0                   0x00
#define STEPPER17_REG_INPUT_1                   0x01
#define STEPPER17_REG_OUTPUT_0                  0x02
#define STEPPER17_REG_OUTPUT_1                  0x03
#define STEPPER17_REG_POLARITY_0                0x04
#define STEPPER17_REG_POLARITY_1                0x05
#define STEPPER17_REG_CONFIG_0                  0x06
#define STEPPER17_REG_CONFIG_1                  0x07

/*! @} */ // stepper17_reg

/**
 * @defgroup stepper17_set Stepper 17 Registers Settings
 * @brief Settings for registers of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_set
 * @{
 */

/**
 * @brief Stepper 17 PCA9555A pin mask.
 * @details Specified PCA9555A pin mask of Stepper 17 Click driver.
 */
#define STEPPER17_P0_DMODE0_PIN                 0x01
#define STEPPER17_P0_DMODE1_PIN                 0x02
#define STEPPER17_P0_DMODE2_PIN                 0x04
#define STEPPER17_P0_DECAY1_PIN                 0x08
#define STEPPER17_P0_DECAY2_PIN                 0x10
#define STEPPER17_P0_TRQ0_PIN                   0x20
#define STEPPER17_P0_TRQ1_PIN                   0x40
#define STEPPER17_P0_SLEEP_X_PIN                0x80
#define STEPPER17_P1_LO1_PIN                    0x01
#define STEPPER17_P1_LO2_PIN                    0x02
#define STEPPER17_P1_MO_PIN                     0x04

/**
 * @brief Stepper 17 PCA9555A pin direction config.
 * @details Specified PCA9555A pin direction config of Stepper 17 Click driver.
 */
#define STEPPER17_P0_DEFAULT_CONFIG             0x00
#define STEPPER17_P1_DEFAULT_CONFIG             0xFF

/**
 * @brief Stepper 17 direction setting.
 * @details Specified setting for direction of Stepper 17 Click driver.
 */
#define STEPPER17_DIR_CW                        1
#define STEPPER17_DIR_CCW                       0

/**
 * @brief Stepper 17 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 17 Click driver.
 */
#define STEPPER17_PIN_LOW_LEVEL                 0
#define STEPPER17_PIN_HIGH_LEVEL                1

/**
 * @brief Stepper 17 step resolution setting.
 * @details Specified setting for step resolution of Stepper 17 Click driver.
 */
#define STEPPER17_MODE_FULL_STEP                0x00
#define STEPPER17_MODE_1_OVER_8                 0x01
#define STEPPER17_MODE_HALF_STEP_TYPE_B         0x02
#define STEPPER17_MODE_1_OVER_32                0x03
#define STEPPER17_MODE_HALF_STEP_TYPE_A         0x04
#define STEPPER17_MODE_1_OVER_16                0x05
#define STEPPER17_MODE_QUARTER_STEP             0x06
#define STEPPER17_MODE_MASK                     0x07

/**
 * @brief Stepper 17 torque setting.
 * @details Specified setting for torque of Stepper 17 Click driver.
 */
#define STEPPER17_TORQUE_100_PCT                0x00
#define STEPPER17_TORQUE_75_PCT                 0x01
#define STEPPER17_TORQUE_50_PCT                 0x02
#define STEPPER17_TORQUE_25_PCT                 0x03
#define STEPPER17_TORQUE_MASK                   0x03

/**
 * @brief Stepper 17 decay setting.
 * @details Specified setting for decay of Stepper 17 Click driver.
 */
#define STEPPER17_DECAY_MIXED                   0x00
#define STEPPER17_DECAY_SLOW                    0x01
#define STEPPER17_DECAY_FAST                    0x02
#define STEPPER17_DECAY_ADMD                    0x03
#define STEPPER17_DECAY_MASK                    0x03

/**
 * @brief Stepper 17 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER17_SPEED_VERY_SLOW               0
#define STEPPER17_SPEED_SLOW                    1
#define STEPPER17_SPEED_MEDIUM                  2
#define STEPPER17_SPEED_FAST                    3
#define STEPPER17_SPEED_VERY_FAST               4 

/**
 * @brief Stepper 17 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 17 Click driver.
 */
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_000     0x20
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_001     0x21
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_010     0x22
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_011     0x23
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_100     0x24
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_101     0x25
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_110     0x26
#define STEPPER17_DEVICE_ADDRESS_A2A1A0_111     0x27

/*! @} */ // stepper17_set

/**
 * @defgroup stepper17_map Stepper 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 17 Click driver.
 */

/**
 * @addtogroup stepper17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 17 Click to the selected MikroBUS.
 */
#define STEPPER17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper17_map
/*! @} */ // stepper17

/**
 * @brief Stepper 17 Click context object.
 * @details Context object definition of Stepper 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable output pin. */
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t rst;          /**< Electric angle reset pin. */
    digital_out_t clk;          /**< Clock signal input pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9555A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper17_t;

/**
 * @brief Stepper 17 Click configuration object.
 * @details Configuration object definition of Stepper 17 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable output pin. */
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t rst;             /**< Electric angle reset pin. */
    pin_name_t clk;             /**< Clock signal input pin. */
    pin_name_t int_pin;         /**< PCA9555A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper17_cfg_t;

/**
 * @brief Stepper 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER17_OK = 0,
    STEPPER17_ERROR = -1

} stepper17_return_value_t;

/*!
 * @addtogroup stepper17 Stepper 17 Click Driver
 * @brief API for configuring and manipulating Stepper 17 Click driver.
 * @{
 */

/**
 * @brief Stepper 17 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper17_cfg_setup ( stepper17_cfg_t *cfg );

/**
 * @brief Stepper 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_init ( stepper17_t *ctx, stepper17_cfg_t *cfg );

/**
 * @brief Stepper 17 default configuration function.
 * @details This function executes a default configuration of Stepper 17
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper17_default_cfg ( stepper17_t *ctx );

/**
 * @brief Stepper 17 write register function.
 * @details This function writes a desired data byte to the selected PCA9555A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_write_register ( stepper17_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 17 read register function.
 * @details This function reads data from the selected PCA9555A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_read_register ( stepper17_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 17 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_step_mode ( stepper17_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 17 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_set_step_mode ( stepper17_t *ctx, uint8_t mode );

/**
 * @brief Stepper 17 get torque function.
 * @details This function reads the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_torque ( stepper17_t *ctx, uint8_t *torque );

/**
 * @brief Stepper 17 set torque function.
 * @details This function sets the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_set_torque ( stepper17_t *ctx, uint8_t torque );

/**
 * @brief Stepper 17 get decay function.
 * @details This function reads the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_decay ( stepper17_t *ctx, uint8_t *decay );

/**
 * @brief Stepper 17 set decay function.
 * @details This function sets the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_set_decay ( stepper17_t *ctx, uint8_t decay );

/**
 * @brief Stepper 17 get sleep x pin function.
 * @details This function reads the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_sleep_x_pin ( stepper17_t *ctx, uint8_t *state );

/**
 * @brief Stepper 17 set sleep x pin function.
 * @details This function sets the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_set_sleep_x_pin ( stepper17_t *ctx, uint8_t state );

/**
 * @brief Stepper 17 get lo1 pin function.
 * @details This function reads the lo1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_lo1_pin ( stepper17_t *ctx, uint8_t *state );

/**
 * @brief Stepper 17 get lo2 pin function.
 * @details This function reads the lo2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_lo2_pin ( stepper17_t *ctx, uint8_t *state );

/**
 * @brief Stepper 17 get mo pin function.
 * @details This function reads the mo pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper17_get_mo_pin ( stepper17_t *ctx, uint8_t *state );

/**
 * @brief Stepper 17 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
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
void stepper17_drive_motor ( stepper17_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 17 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper17_enable_device ( stepper17_t *ctx );

/**
 * @brief Stepper 17 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper17_disable_device ( stepper17_t *ctx );

/**
 * @brief Stepper 17 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper17_set_direction ( stepper17_t *ctx, uint8_t dir );

/**
 * @brief Stepper 17 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper17_switch_direction ( stepper17_t *ctx );

/**
 * @brief Stepper 17 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper17_reset_device ( stepper17_t *ctx );

/**
 * @brief Stepper 17 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper17_get_int_pin ( stepper17_t *ctx );

/**
 * @brief Stepper 17 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper17_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper17_set_clk_pin ( stepper17_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER17_H

/*! @} */ // stepper17

// ------------------------------------------------------------------------ END
