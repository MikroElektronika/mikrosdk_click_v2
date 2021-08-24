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
 * @file stepper11.h
 * @brief This file contains API for Stepper 11 Click Driver.
 */

#ifndef STEPPER11_H
#define STEPPER11_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"

/*!
 * @addtogroup stepper11 Stepper 11 Click Driver
 * @brief API for configuring and manipulating Stepper 11 Click driver.
 * @{
 */

/**
 * @defgroup stepper11_reg Stepper 11 Registers List
 * @brief List of registers of Stepper 11 Click driver.
 */

/**
 * @addtogroup stepper11_reg
 * @{
 */

/**
 * @brief Stepper 11 description register.
 * @details Specified register for description of Stepper 11 Click driver.
 */
#define STEPPER11_REG_INPUT_PORT        0x00
#define STEPPER11_REG_OUTPUT_PORT       0x01
#define STEPPER11_REG_POLARITY          0x02
#define STEPPER11_REG_CONFIGURATION     0x03

/*! @} */ // stepper11_reg

/**
 * @defgroup stepper11_set Stepper 11 Registers Settings
 * @brief Settings for registers of Stepper 11 Click driver.
 */

/**
 * @addtogroup stepper11_set
 * @{
 */

/**
 * @brief Stepper 11 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER11_SPEED_SLOW            1
#define STEPPER11_SPEED_MEDIUM          2
#define STEPPER11_SPEED_FAST            3 

/**
 * @brief Stepper 11 device resolution settings.
 * @details Specified setting for step resolution.
 */
#define STEPPER11_RESOLUTION_FULL       0x4
#define STEPPER11_RESOLUTION_HALF_A     0x2
#define STEPPER11_RESOLUTION_HALF_B     0x1
#define STEPPER11_RESOLUTION_QUARTER    0x6
#define STEPPER11_RESOLUTION_1div8      0x5
#define STEPPER11_RESOLUTION_1div16     0x3
#define STEPPER11_RESOLUTION_1div32     0x7

/**
 * @brief Stepper 11 device torque settings.
 * @details Specified setting for torque.
 */
#define STEPPER11_TORQUE_100            0x0
#define STEPPER11_TORQUE_70             0x1
#define STEPPER11_TORQUE_50             0x2
#define STEPPER11_TORQUE_30             0x3

/**
 * @brief Stepper 11 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 11 Click driver.
 */
#define STEPPER11_SET_DEV_ADDR          0x70

/*! @} */ // stepper11_set

/**
 * @defgroup stepper11_map Stepper 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 11 Click driver.
 */

/**
 * @addtogroup stepper11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 11 Click to the selected MikroBUS.
 */
#define STEPPER11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.clk = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper11_map
/*! @} */ // stepper11

/**
 * @brief Stepper 11 Click context object.
 * @details Context object definition of Stepper 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;      /**< Enable. */
    digital_out_t  dir;     /**< Direction. */
    digital_out_t  rst;     /**< Reset. */
    digital_out_t  clk;     /**< Clock. */

    // Input pins
    digital_in_t  int_pin;  /**< Interrupt. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */
    // ctx variable
    uint16_t steps;             /**< Motor steps. */
    float resolution;           /**< Motor resolution. */
    uint8_t step_resolution;    /**< Step resolution. */

} stepper11_t;

/**
 * @brief Stepper 11 Click configuration object.
 * @details Configuration object definition of Stepper 11 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Enable. */
    pin_name_t  dir;        /**< Direction. */
    pin_name_t  rst;        /**< Reset. */
    pin_name_t  clk;        /**< Clock. */
    pin_name_t  int_pin;    /**< Interrupt. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} stepper11_cfg_t;

/**
 * @brief Stepper 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   STEPPER11_OK = 0,
   STEPPER11_ERROR = -1

} stepper11_return_value_t;

/*!
 * @addtogroup stepper11 Stepper 11 Click Driver
 * @brief API for configuring and manipulating Stepper 11 Click driver.
 * @{
 */

/**
 * @brief Stepper 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper11_cfg_setup ( stepper11_cfg_t *cfg );

/**
 * @brief Stepper 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper11_init ( stepper11_t *ctx, stepper11_cfg_t *cfg );

/**
 * @brief Stepper 11 default configuration function.
 * @details This function executes a default configuration of Stepper 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper11_default_cfg ( stepper11_t *ctx );

/**
 * @brief Stepper 11 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] tx_data : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper11_generic_write ( stepper11_t *ctx, uint8_t reg, uint8_t tx_data );

/**
 * @brief Stepper 11 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] rx_data : Output read data.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper11_generic_read ( stepper11_t *ctx, uint8_t reg, uint8_t *rx_data );

/**
 * @brief Set direction.
 * @details This function sets a @b dir pin to change motor rotation direction.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] state : Logic state to set.
 * @return Nothing.
 */
void stepper11_set_direction ( stepper11_t *ctx, uint8_t state );

/**
 * @brief Set enable.
 * @details This function sets a @b en pin to change enable state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] state : Logic state to set.
 * @return Nothing.
 */
void stepper11_set_enable ( stepper11_t *ctx, uint8_t state );

/**
 * @brief Set restart.
 * @details This function sets a @b rst pin to change start state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] state : Logic state to set.
 * @return Nothing.
 */
void stepper11_set_reset ( stepper11_t *ctx, uint8_t state );

/**
 * @brief Set clock state.
 * @details This function sets a @b clk pin to change clock state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] state : Logic state to set.
 * @return Nothing.
 */
void stepper11_set_clock ( stepper11_t *ctx, uint8_t state );

/**
 * @brief Get interrupt.
 * @details This function gets a @b int pin state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper11_get_interrupt ( stepper11_t *ctx );

/**
 * @brief Get anomaly detection flag.
 * @details This function gets a @b diag pin state that signals
 * for anomaly detection flag.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper11_get_diag ( stepper11_t *ctx );

/**
 * @brief Get electrical angle monitoring signal.
 * @details This function gets a @b mo pin state that signals
 * electrical angle monitoring.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper11_get_mo ( stepper11_t *ctx );

/**
 * @brief Get stall detection flag.
 * @details This function gets a @b sd pin state that signals
 * for stall detection flag.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper11_get_sd ( stepper11_t *ctx );

/**
 * @brief Set step resolution.
 * @details This function sets step resolution for motor control.
 * @param[in,out] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] step_res : Step resolution:
 *                      @li @c  4 - Full step,
 *                      @li @c  2 - Half step A,
 *                      @li @c  1 - Half step B,
 *                      @li @c  6 - Quarter step,
 *                      @li @c  5 - 1/8 step,
 *                      @li @c  3 - 1/16 step,
 *                      @li @c  7 - 1/32 step.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper11_set_step_resolution ( stepper11_t *ctx, uint8_t step_res );

/**
 * @brief Set torque.
 * @details This function sets torque for motor control.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] torque : Torque:
 *                      @li @c  0 - 100%,
 *                      @li @c  1 - 70%,
 *                      @li @c  2 - 50%,
 *                      @li @c  3 - 30%.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t stepper11_set_torque ( stepper11_t *ctx, uint8_t torque );

/**
 * @brief Move motor in angle value.
 * @details This function moves motor for desired angle value.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] degree : Degrees to move.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Slow,
 *                  @li @c  2 - Normal,
 *                  @li @c  3 - Fast.
 * @return Nothing
 */
void stepper11_move_motor_angle ( stepper11_t *ctx, float degree, uint8_t speed );

/**
 * @brief Move motor in step value.
 * @details This function moves motor for desired step value.
 * @param[in] ctx : Click context object.
 * See #stepper11_t object definition for detailed explanation.
 * @param[in] steps : Steps to move.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Slow,
 *                  @li @c  2 - Normal,
 *                  @li @c  3 - Fast.
 * @return Nothing
 */
void stepper11_move_motor_step ( stepper11_t *ctx, uint16_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER11_H

/*! @} */ // stepper11

// ------------------------------------------------------------------------ END
