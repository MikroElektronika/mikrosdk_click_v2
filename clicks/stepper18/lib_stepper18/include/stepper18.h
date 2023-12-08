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
 * @file stepper18.h
 * @brief This file contains API for Stepper 18 Click Driver.
 */

#ifndef STEPPER18_H
#define STEPPER18_H

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

/**
 * @defgroup stepper18_set Stepper 18 Registers Settings
 * @brief Settings for registers of Stepper 18 Click driver.
 */

/**
 * @addtogroup stepper18_set
 * @{
 */

/**
 * @brief Stepper 18 device step resolution.
 * @details Specified setting for referencing step resolution.
 */
#define STEPPER18_STEP_RES_FULL     1
#define STEPPER18_STEP_RES_HALF     2
#define STEPPER18_STEP_RES_QUARTER  4
#define STEPPER18_STEP_RES_1div8    8
#define STEPPER18_STEP_RES_1div16   16
#define STEPPER18_STEP_RES_1div32   32
#define STEPPER18_STEP_RES_1div64   64
#define STEPPER18_STEP_RES_1div128  128
#define STEPPER18_STEP_RES_1div256  256

/**
 * @brief Stepper 18 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER18_SPEED_VERY_SLOW   1
#define STEPPER18_SPEED_SLOW        2
#define STEPPER18_SPEED_MEDIUM      3
#define STEPPER18_SPEED_FAST        4 
#define STEPPER18_SPEED_VERY_FAST   5

/**
 * @brief Stepper 18 device address setting.
 * @details Specified setting for device slave address selection of
 * Stepper 18 Click driver.
 */
#define STEPPER18_SET_DEV_ADDR      0x60

/*! @} */ // stepper18_set

/**
 * @defgroup stepper18_map Stepper 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 18 Click driver.
 */

/**
 * @addtogroup stepper18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 18 Click to the selected MikroBUS.
 */
#define STEPPER18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.stp = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper18_map
/*! @} */ // stepper18

/**
 * @brief Stepper 18 Click context object.
 * @details Context object definition of Stepper 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t  en;      /**< Enable. */
    digital_out_t  dir;     /**< Direction. */
    digital_out_t  slp;     /**< Sleep. */
    digital_out_t  stp;     /**< Step. */

    // Input pins
    digital_in_t  flt;      /**< Fault. */

    // Modules
    i2c_master_t i2c;       /**< I2C driver object. */

    // I2C slave address
    uint8_t slave_address;  /**< Device slave address (used for I2C driver). */

    // Motor stepps
    uint16_t steps;
    float resolution;
    
    
} stepper18_t;

/**
 * @brief Stepper 18 Click configuration object.
 * @details Configuration object definition of Stepper 18 Click driver.
 */
typedef struct
{
    pin_name_t  scl;        /**< Clock pin descriptor for I2C driver. */
    pin_name_t  sda;        /**< Bidirectional data pin descriptor for I2C driver. */

    pin_name_t  en;         /**< Enable. */
    pin_name_t  dir;        /**< Direction. */
    pin_name_t  slp;        /**< Sleep. */
    pin_name_t  stp;        /**< Step. */
    pin_name_t  flt;        /**< Fault. */

    uint32_t  i2c_speed;    /**< I2C serial speed. */
    uint8_t   i2c_address;  /**< I2C slave address. */

} stepper18_cfg_t;

/**
 * @brief Stepper 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   STEPPER18_OK = 0,
   STEPPER18_ERROR = -1

} stepper18_return_value_t;

/*!
 * @addtogroup stepper18 Stepper 18 Click Driver
 * @brief API for configuring and manipulating Stepper 18 Click driver.
 * @{
 */

/**
 * @brief Stepper 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper18_cfg_setup ( stepper18_cfg_t *cfg );

/**
 * @brief Stepper 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper18_init ( stepper18_t *ctx, stepper18_cfg_t *cfg );

/**
 * @brief Stepper 18 default configuration function.
 * @details This function executes a default configuration of Stepper 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t stepper18_default_cfg ( stepper18_t *ctx );

/**
 * @brief Writing function.
 * @details This function writes a desired number of data bytes by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] tx_buf : Data to be written.
 * @param[in] tx_len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper18_generic_write ( stepper18_t *ctx, uint8_t *tx_buf, uint8_t tx_len );

/**
 * @brief Set voltage reference.
 * @details This function sets a desired reference voltage of device.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] voltage : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper18_set_out_voltage ( stepper18_t *ctx, uint16_t voltage );

/**
 * @brief Set direction.
 * @details This function sets a @b dir pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper18_set_dir ( stepper18_t *ctx, uint8_t value );

/**
 * @brief Set sleep.
 * @details This function sets a @b slp pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper18_set_slp ( stepper18_t *ctx, uint8_t value );

/**
 * @brief Set enable.
 * @details This function sets a @b en pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper18_set_en ( stepper18_t *ctx, uint8_t value );

/**
 * @brief Set step state.
 * @details This function sets a @b stp pin to high/low state.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] value : Logic state to set.
 * @return Nothing.
 */
void stepper18_set_stp ( stepper18_t *ctx, uint8_t value );

/**
 * @brief Get fault.
 * @details This function gets a @b flt pin.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Logic state of pin.
 */
uint8_t stepper18_get_flt ( stepper18_t *ctx );

/**
 * @brief Move motor in angle value.
 * @details This function moves motor for desired angle value.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] degree : Degrees to move.
 * @param[in] step_res : Step resolution refrence:
 *                  @li @c  1 - Full step,
 *                  @li @c  2 - Half step,
 *                  @li @c  4 - Quarter step,
 *                  @li @c  8 - 1/8 step,
 *                  @li @c  16 - 1/16 step,
 *                  @li @c  32 - 1/32 step,
 *                  @li @c  64 - 1/64 step,
 *                  @li @c  128 - 1/128 step,
 *                  @li @c  256 - 1/256 step.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Very Slow,
 *                  @li @c  2 - Slow,
 *                  @li @c  3 - Normal,
 *                  @li @c  4 - Fast,
 *                  @li @c  5 - Very Fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Step resolution depends on postion on M0, M1 switches.
 */
void stepper18_move_motor_angle ( stepper18_t *ctx, float degree, uint8_t step_res, uint8_t speed );

/**
 * @brief Move motor in step value.
 * @details This function moves motor for desired step value.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @param[in] steps : Steps to move.
 * @param[in] step_res : Step resolution refrence:
 *                  @li @c  1 - Full step,
 *                  @li @c  2 - Half step,
 *                  @li @c  4 - Quarter step,
 *                  @li @c  8 - 1/8 step,
 *                  @li @c  16 - 1/16 step,
 *                  @li @c  32 - 1/32 step,
 *                  @li @c  64 - 1/64 step,
 *                  @li @c  128 - 1/128 step,
 *                  @li @c  256 - 1/256 step.
 * @param[in] speed : Predefined speed macros:
 *                  @li @c  1 - Very Slow,
 *                  @li @c  2 - Slow,
 *                  @li @c  3 - Normal,
 *                  @li @c  4 - Fast,
 *                  @li @c  5 - Very Fast.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Step resolution depends on postion on M0, M1 switches.
 */
void stepper18_move_motor_step ( stepper18_t *ctx, uint16_t steps, uint8_t step_res, uint8_t speed );

/**
 * @brief Calculate step-degree resolution.
 * @details This function calculates resolution of selected motor steps.
 * @param[in] ctx : Click context object.
 * See #stepper18_t object definition for detailed explanation.
 * @return Nothing.
 * @note It calculates steps set from context object and sets resolution of it's member.
 */
void stepper18_calculate_resolution ( stepper18_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // STEPPER18_H

/*! @} */ // stepper18

// ------------------------------------------------------------------------ END
