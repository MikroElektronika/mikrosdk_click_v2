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
 * @file stepper14.h
 * @brief This file contains API for Stepper 14 Click Driver.
 */

#ifndef STEPPER14_H
#define STEPPER14_H

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
 * @addtogroup stepper14 Stepper 14 Click Driver
 * @brief API for configuring and manipulating Stepper 14 Click driver.
 * @{
 */

/**
 * @defgroup stepper14_reg Stepper 14 Registers List
 * @brief List of registers of Stepper 14 Click driver.
 */

/**
 * @addtogroup stepper14_reg
 * @{
 */

/**
 * @brief Stepper 14 PCA9538A registers.
 * @details Specified PCA9538A registers of Stepper 14 Click driver.
 */
#define STEPPER14_PCA9538A_REG_INPUT            0x00
#define STEPPER14_PCA9538A_REG_OUTPUT           0x01
#define STEPPER14_PCA9538A_REG_POLARITY         0x02
#define STEPPER14_PCA9538A_REG_CONFIG           0x03

/*! @} */ // stepper14_reg

/**
 * @defgroup stepper14_set Stepper 14 Registers Settings
 * @brief Settings for registers of Stepper 14 Click driver.
 */

/**
 * @addtogroup stepper14_set
 * @{
 */

/**
 * @brief Stepper 14 PCA9538A pin mask.
 * @details Specified PCA9538A pin mask of Stepper 14 Click driver.
 */
#define STEPPER14_PIN_IN1                       0x01
#define STEPPER14_PIN_IN2                       0x02
#define STEPPER14_PIN_MODE                      0x04
#define STEPPER14_PIN_IN3                       0x08
#define STEPPER14_PIN_IN4                       0x10
#define STEPPER14_PIN_TRQ                       0x20

/**
 * @brief Stepper 14 PCA9538A pin direction config.
 * @details Specified PCA9538A pin direction config of Stepper 14 Click driver.
 */
#define STEPPER14_PCA9538A_DEFAULT_CONFIG       0xC0

/**
 * @brief Stepper 14 direction setting.
 * @details Specified setting for direction of Stepper 14 Click driver.
 */
#define STEPPER14_DIR_CW                        0
#define STEPPER14_DIR_CCW                       1

/**
 * @brief Stepper 14 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 14 Click driver.
 */
#define STEPPER14_PIN_STATE_LOW                 0
#define STEPPER14_PIN_STATE_HIGH                1

/**
 * @brief Stepper 14 pin interface setting.
 * @details Specified setting for pin interface of Stepper 14 Click driver.
 */
#define STEPPER14_INTERFACE_4_PIN               0
#define STEPPER14_INTERFACE_2_PIN               1

/**
 * @brief Stepper 14 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER14_SPEED_VERY_SLOW               0
#define STEPPER14_SPEED_SLOW                    1
#define STEPPER14_SPEED_MEDIUM                  2
#define STEPPER14_SPEED_FAST                    3
#define STEPPER14_SPEED_VERY_FAST               4

/**
 * @brief Stepper 14 step resolution setting.
 * @details Specified setting for step resolution of Stepper 14 Click driver.
 */
#define STEPPER14_MODE_FULL_STEP                0
#define STEPPER14_MODE_HALF_STEP                1

/**
 * @brief Stepper 14 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 14 Click driver.
 */
#define STEPPER14_DEVICE_ADDRESS_A1A0_00        0x70
#define STEPPER14_DEVICE_ADDRESS_A1A0_01        0x71
#define STEPPER14_DEVICE_ADDRESS_A1A0_10        0x72
#define STEPPER14_DEVICE_ADDRESS_A1A0_11        0x73

/*! @} */ // stepper14_set

/**
 * @defgroup stepper14_map Stepper 14 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 14 Click driver.
 */

/**
 * @addtogroup stepper14_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 14 Click to the selected MikroBUS.
 */
#define STEPPER14_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper14_map
/*! @} */ // stepper14

/**
 * @brief Stepper 14 Click context object.
 * @details Context object definition of Stepper 14 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;           /**< Enable driver pin. */
    digital_out_t rst;          /**< PCA9538A reset pin. */

    // Input pins
    digital_in_t flt;           /**< Fault pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */

    uint8_t pin_mode;           /**< Pin interface mode setting (0 - 4-pin, 1 - 2-pin). */
    uint8_t step_mode;          /**< Step mode setting (0 - full step, 1 - half step). */
    uint8_t direction;          /**< Direction setting (0 - cw, 1 - ccw). */

} stepper14_t;

/**
 * @brief Stepper 14 Click configuration object.
 * @details Configuration object definition of Stepper 14 Click driver.
 */
typedef struct
{
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t en;              /**< Enable driver pin. */
    pin_name_t rst;             /**< PCA9538A reset pin. */
    pin_name_t flt;             /**< Fault pin. */

    uint32_t   i2c_speed;       /**< I2C serial speed. */
    uint8_t    i2c_address;     /**< I2C slave address. */

} stepper14_cfg_t;

/**
 * @brief Stepper 14 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER14_OK = 0,
    STEPPER14_ERROR = -1

} stepper14_return_value_t;

/*!
 * @addtogroup stepper14 Stepper 14 Click Driver
 * @brief API for configuring and manipulating Stepper 14 Click driver.
 * @{
 */

/**
 * @brief Stepper 14 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper14_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper14_cfg_setup ( stepper14_cfg_t *cfg );

/**
 * @brief Stepper 14 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper14_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_init ( stepper14_t *ctx, stepper14_cfg_t *cfg );

/**
 * @brief Stepper 14 default configuration function.
 * @details This function executes a default configuration of Stepper 14
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper14_default_cfg ( stepper14_t *ctx );

/**
 * @brief Stepper 14 pca write reg function.
 * @details This function writes a desired data byte to the selected PCA9538A register 
 * by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_pca_write_reg ( stepper14_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief Stepper 14 pca read reg function.
 * @details This function reads data from the selected PCA9538A register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_pca_read_reg ( stepper14_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief Stepper 14 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper14_set_rst_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 reset device function.
 * @details This function resets the PCA9538A device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper14_reset_pca ( stepper14_t *ctx );

/**
 * @brief Stepper 14 get FAULT pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper14_get_fault_pin ( stepper14_t *ctx );

/**
 * @brief Stepper 14 enable device function.
 * @details This function enables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper14_enable_device ( stepper14_t *ctx );

/**
 * @brief Stepper 14 disable device function.
 * @details This function disables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper14_disable_device ( stepper14_t *ctx );

/**
 * @brief Stepper 14 set IN1 pin function.
 * @details This function sets the IN1 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_in1_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set IN2 pin function.
 * @details This function sets the IN2 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_in2_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set IN3 pin function.
 * @details This function sets the IN3 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_in3_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set IN4 pin function.
 * @details This function sets the IN4 pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_in4_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set MODE pin function.
 * @details This function sets the MODE pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_mode_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set TRQ pin function.
 * @details This function sets the TRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_trq_pin ( stepper14_t *ctx, uint8_t state );

/**
 * @brief Stepper 14 set interface mode function.
 * @details This function sets the interface mode settings in @b ctx->pin_mode.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] mode : Interface mode settings.
 *                   @li @c 0 - 4-pin interface,
 *                   @li @c 1 - 2-pin interface.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_set_interface_mode ( stepper14_t *ctx, uint8_t mode );

/**
 * @brief Stepper 14 set step mode function.
 * @details This function sets the step mode resolution settings in @b ctx->step_mode.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step.
 * @return None.
 * @note None.
 */
void stepper14_set_step_mode ( stepper14_t *ctx, uint8_t mode );

/**
 * @brief Stepper 14 set direction function.
 * @details This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper14_set_direction ( stepper14_t *ctx, uint8_t dir );

/**
 * @brief Stepper 14 switch direction function.
 * @details This function switches the motor direction in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper14_switch_direction ( stepper14_t *ctx );

/**
 * @brief Stepper 14 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper14_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper14_drive_motor ( stepper14_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER14_H

/*! @} */ // stepper14

// ------------------------------------------------------------------------ END
