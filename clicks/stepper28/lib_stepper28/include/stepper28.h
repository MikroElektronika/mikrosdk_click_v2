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
 * @file stepper28.h
 * @brief This file contains API for Stepper 28 Click Driver.
 */

#ifndef STEPPER28_H
#define STEPPER28_H

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
 * @addtogroup stepper28 Stepper 28 Click Driver
 * @brief API for configuring and manipulating Stepper 28 Click driver.
 * @{
 */

/**
 * @defgroup stepper28_reg Stepper 28 Registers List
 * @brief List of registers of Stepper 28 Click driver.
 */

/**
 * @addtogroup stepper28_reg
 * @{
 */

/**
 * @brief Stepper 28 PCA9555A registers.
 * @details Specified PCA9555A registers of Stepper 28 Click driver.
 */
#define STEPPER28_REG_INPUT_0                   0x00
#define STEPPER28_REG_INPUT_1                   0x01
#define STEPPER28_REG_OUTPUT_0                  0x02
#define STEPPER28_REG_OUTPUT_1                  0x03
#define STEPPER28_REG_POLARITY_0                0x04
#define STEPPER28_REG_POLARITY_1                0x05
#define STEPPER28_REG_CONFIG_0                  0x06
#define STEPPER28_REG_CONFIG_1                  0x07

/*! @} */ // stepper28_reg

/**
 * @defgroup stepper28_set Stepper 28 Registers Settings
 * @brief Settings for registers of Stepper 28 Click driver.
 */

/**
 * @addtogroup stepper28_set
 * @{
 */

/**
 * @brief Stepper 28 PCA9555A pin mask.
 * @details Specified PCA9555A pin mask of Stepper 28 Click driver.
 */
#define STEPPER28_P0_DMODE0_PIN                 0x01
#define STEPPER28_P0_DMODE1_PIN                 0x02
#define STEPPER28_P0_DMODE2_PIN                 0x04
#define STEPPER28_P0_DECAY1_PIN                 0x08
#define STEPPER28_P0_DECAY2_PIN                 0x10
#define STEPPER28_P0_TRQ0_PIN                   0x20
#define STEPPER28_P0_TRQ1_PIN                   0x40
#define STEPPER28_P0_SLEEP_X_PIN                0x80
#define STEPPER28_P1_LO1_PIN                    0x01
#define STEPPER28_P1_LO2_PIN                    0x02
#define STEPPER28_P1_MO_PIN                     0x04
#define STEPPER28_P1_RST_PIN                    0x08

/**
 * @brief Stepper 28 PCA9555A pin direction config.
 * @details Specified PCA9555A pin direction config of Stepper 28 Click driver.
 */
#define STEPPER28_P0_DEFAULT_CONFIG             0x00
#define STEPPER28_P1_DEFAULT_CONFIG             0xF7

/**
 * @brief Stepper 28 direction setting.
 * @details Specified setting for direction of Stepper 28 Click driver.
 */
#define STEPPER28_DIR_CW                        1
#define STEPPER28_DIR_CCW                       0

/**
 * @brief Stepper 28 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 28 Click driver.
 */
#define STEPPER28_PIN_LOW_LEVEL                 0
#define STEPPER28_PIN_HIGH_LEVEL                1

/**
 * @brief Stepper 28 step resolution setting.
 * @details Specified setting for step resolution of Stepper 28 Click driver.
 */
#define STEPPER28_MODE_FULL_STEP                0x00
#define STEPPER28_MODE_1_OVER_8                 0x01
#define STEPPER28_MODE_HALF_STEP_TYPE_B         0x02
#define STEPPER28_MODE_1_OVER_32                0x03
#define STEPPER28_MODE_HALF_STEP_TYPE_A         0x04
#define STEPPER28_MODE_1_OVER_16                0x05
#define STEPPER28_MODE_QUARTER_STEP             0x06
#define STEPPER28_MODE_MASK                     0x07

/**
 * @brief Stepper 28 torque setting.
 * @details Specified setting for torque of Stepper 28 Click driver.
 */
#define STEPPER28_TORQUE_100_PCT                0x00
#define STEPPER28_TORQUE_75_PCT                 0x01
#define STEPPER28_TORQUE_50_PCT                 0x02
#define STEPPER28_TORQUE_25_PCT                 0x03
#define STEPPER28_TORQUE_MASK                   0x03

/**
 * @brief Stepper 28 decay setting.
 * @details Specified setting for decay of Stepper 28 Click driver.
 */
#define STEPPER28_DECAY_MIXED                   0x00
#define STEPPER28_DECAY_SLOW                    0x01
#define STEPPER28_DECAY_FAST                    0x02
#define STEPPER28_DECAY_ADMD                    0x03
#define STEPPER28_DECAY_MASK                    0x03

/**
 * @brief Stepper 28 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER28_SPEED_VERY_SLOW               0
#define STEPPER28_SPEED_SLOW                    1
#define STEPPER28_SPEED_MEDIUM                  2
#define STEPPER28_SPEED_FAST                    3
#define STEPPER28_SPEED_VERY_FAST               4 

/**
 * @brief Stepper 28 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 28 Click driver.
 */
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_000     0x20
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_001     0x21
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_010     0x22
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_011     0x23
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_100     0x24
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_101     0x25
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_110     0x26
#define STEPPER28_DEVICE_ADDRESS_A2A1A0_111     0x27

/*! @} */ // stepper28_set

/**
 * @defgroup stepper28_map Stepper 28 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 28 Click driver.
 */

/**
 * @addtogroup stepper28_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 28 Click to the selected MikroBUS.
 */
#define STEPPER28_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper28_map
/*! @} */ // stepper28

/**
 * @brief Stepper 28 Click context object.
 * @details Context object definition of Stepper 28 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable output pin (active high). */
    digital_out_t dir;          /**< Direction control pin (CW-high, CCW-low). */
    digital_out_t clk;          /**< Clock signal pin. */

    // Input pins
    digital_in_t int_pin;       /**< PCA9555A interrupt pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

} stepper28_t;

/**
 * @brief Stepper 28 Click configuration object.
 * @details Configuration object definition of Stepper 28 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable output pin (active high). */
    pin_name_t dir;             /**< Direction control pin (CW-high, CCW-low). */
    pin_name_t clk;             /**< Clock signal pin. */
    pin_name_t int_pin;         /**< PCA9555A interrupt pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper28_cfg_t;

/**
 * @brief Stepper 28 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER28_OK = 0,
    STEPPER28_ERROR = -1

} stepper28_return_value_t;

/*!
 * @addtogroup stepper28 Stepper 28 Click Driver
 * @brief API for configuring and manipulating Stepper 28 Click driver.
 * @{
 */

/**
 * @brief Stepper 28 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper28_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper28_cfg_setup ( stepper28_cfg_t *cfg );

/**
 * @brief Stepper 28 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper28_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_init ( stepper28_t *ctx, stepper28_cfg_t *cfg );

/**
 * @brief Stepper 28 default configuration function.
 * @details This function executes a default configuration of Stepper 28
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper28_default_cfg ( stepper28_t *ctx );

/**
 * @brief Stepper 28 write register function.
 * @details This function writes a desired data byte to the selected PCA9555A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_write_register ( stepper28_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 28 read register function.
 * @details This function reads data from the selected PCA9555A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_read_register ( stepper28_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 28 get step mode function.
 * @details This function reads the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_step_mode ( stepper28_t *ctx, uint8_t *mode );

/**
 * @brief Stepper 28 set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_set_step_mode ( stepper28_t *ctx, uint8_t mode );

/**
 * @brief Stepper 28 get torque function.
 * @details This function reads the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_torque ( stepper28_t *ctx, uint8_t *torque );

/**
 * @brief Stepper 28 set torque function.
 * @details This function sets the motor torque settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] torque : Torque settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_set_torque ( stepper28_t *ctx, uint8_t torque );

/**
 * @brief Stepper 28 get decay function.
 * @details This function reads the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_decay ( stepper28_t *ctx, uint8_t *decay );

/**
 * @brief Stepper 28 set decay function.
 * @details This function sets the motor decay settings.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] decay : Decay settings.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_set_decay ( stepper28_t *ctx, uint8_t decay );

/**
 * @brief Stepper 28 get sleep x pin function.
 * @details This function reads the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_sleep_x_pin ( stepper28_t *ctx, uint8_t *state );

/**
 * @brief Stepper 28 set sleep x pin function.
 * @details This function sets the sleep x pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_set_sleep_x_pin ( stepper28_t *ctx, uint8_t state );

/**
 * @brief Stepper 28 get lo1 pin function.
 * @details This function reads the lo1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_lo1_pin ( stepper28_t *ctx, uint8_t *state );

/**
 * @brief Stepper 28 get lo2 pin function.
 * @details This function reads the lo2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_lo2_pin ( stepper28_t *ctx, uint8_t *state );

/**
 * @brief Stepper 28 get mo pin function.
 * @details This function reads the mo pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_mo_pin ( stepper28_t *ctx, uint8_t *state );

/**
 * @brief Stepper 28 get RST pin function.
 * @details This function reads the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[out] state : @li @c 0 - Low logic state,
 *                     @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_get_rst_pin ( stepper28_t *ctx, uint8_t *state );

/**
 * @brief Stepper 28 set RST pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_set_rst_pin ( stepper28_t *ctx, uint8_t state );

/**
 * @brief Stepper 28 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper28_reset_device ( stepper28_t *ctx );

/**
 * @brief Stepper 28 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
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
void stepper28_drive_motor ( stepper28_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 28 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper28_enable_device ( stepper28_t *ctx );

/**
 * @brief Stepper 28 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper28_disable_device ( stepper28_t *ctx );

/**
 * @brief Stepper 28 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper28_set_direction ( stepper28_t *ctx, uint8_t dir );

/**
 * @brief Stepper 28 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper28_switch_direction ( stepper28_t *ctx );

/**
 * @brief Stepper 28 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper28_get_int_pin ( stepper28_t *ctx );

/**
 * @brief Stepper 28 set clk pin function.
 * @details This function sets the CLK pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper28_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper28_set_clk_pin ( stepper28_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER28_H

/*! @} */ // stepper28

// ------------------------------------------------------------------------ END
