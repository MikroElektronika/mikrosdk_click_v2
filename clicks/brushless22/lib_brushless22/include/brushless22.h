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
 * @file brushless22.h
 * @brief This file contains API for Brushless 22 Click Driver.
 */

#ifndef BRUSHLESS22_H
#define BRUSHLESS22_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup brushless22 Brushless 22 Click Driver
 * @brief API for configuring and manipulating Brushless 22 Click driver.
 * @{
 */

/**
 * @defgroup brushless22_set Brushless 22 Settings
 * @brief Settings for configuration of Brushless 22 Click driver.
 */

/**
 * @addtogroup brushless22_cfg
 * @{
 */

/**
 * @brief Brushless 22 digipot settings.
 * @details Specified digipot settings of Brushless 22 Click driver.
 */
#define BRUSHLESS22_DIGIPOT_MAX_VALUE       100000ul
#define BRUSHLESS22_DIGIPOT_RESOLUTION      257
#define BRUSHLESS22_ROUND_TO_NEAREST_INT    0.5
#define BRUSHLESS22_SLEW_RATE_RES_MAX       47000
#define BRUSHLESS22_SLEW_RATE_RES_DEFAULT   10000
#define BRUSHLESS22_SLEW_RATE_RES_MIN       4700
#define BRUSHLESS22_RPROG_3900              3900
#define BRUSHLESS22_RPROG_24000             24000
#define BRUSHLESS22_RPROG_ADDRESS           0x10

/**
 * @brief Brushless 22 device address setting.
 * @details Specified setting for device slave address selection of
 * Brushless 22 Click driver.
 */
#define BRUSHLESS22_ADDR_A2A1A0_000         0x28
#define BRUSHLESS22_ADDR_A2A1A0_001         0x29
#define BRUSHLESS22_ADDR_A2A1A0_010         0x2A
#define BRUSHLESS22_ADDR_A2A1A0_011         0x2B
#define BRUSHLESS22_ADDR_A2A1A0_100         0x2C
#define BRUSHLESS22_ADDR_A2A1A0_101         0x2D
#define BRUSHLESS22_ADDR_A2A1A0_110         0x2E
#define BRUSHLESS22_ADDR_A2A1A0_111         0x2F

/**
 * @brief Brushless 22 direction setting.
 * @details Specified setting for direction of Brushless 22 Click driver.
 */
#define BRUSHLESS22_DIR_FORWARD             0
#define BRUSHLESS22_DIR_REVERSE             1

/**
 * @brief Brushless 22 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 22 Click driver.
 */
#define BRUSHLESS22_DEF_FREQ                50000

/*! @} */ // brushless22_cfg

/**
 * @defgroup brushless22_map Brushless 22 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 22 Click driver.
 */

/**
 * @addtogroup brushless22_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 22 Click to the selected MikroBUS.
 */
#define BRUSHLESS22_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rt = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.ss = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fg = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless22_map
/*! @} */ // brushless22

/**
 * @brief Brushless 22 Click driver selector.
 * @details Selects target driver interface of Brushless 22 Click driver.
 */

/**
 * @brief Brushless 22 Click context object.
 * @details Context object definition of Brushless 22 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;          /**< Motor rotation direction pin (Forward-LOW, Reverse-HIGH). */
    digital_out_t ss;           /**< Strong start pin. */
    digital_out_t rt;           /**< Regulation target pin. */

    // Input pins
    digital_in_t fg;            /**< Motor speed indication pin. */

    // Modules
    i2c_master_t i2c;           /**< I2C driver object. */
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint8_t slave_address;      /**< Device slave address (used for I2C driver). */
    uint32_t pwm_freq;          /**< PWM frequency value. */

} brushless22_t;

/**
 * @brief Brushless 22 Click configuration object.
 * @details Configuration object definition of Brushless 22 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t scl;             /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;             /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t dir;             /**< Motor rotation direction pin (Forward-LOW, Reverse-HIGH). */
    pin_name_t ss;              /**< Strong start pin (Active High). */
    pin_name_t fg;              /**< Motor speed indication pin. */
    pin_name_t rt;              /**< Regulation target pin. */

    // Static variable
    uint32_t i2c_speed;         /**< I2C serial speed. */
    uint8_t  i2c_address;       /**< I2C slave address. */
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} brushless22_cfg_t;

/**
 * @brief Brushless 22 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS22_OK = 0,
    BRUSHLESS22_ERROR = -1

} brushless22_return_value_t;

/*!
 * @addtogroup brushless22 Brushless 22 Click Driver
 * @brief API for configuring and manipulating Brushless 22 Click driver.
 * @{
 */

/**
 * @brief Brushless 22 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless22_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless22_cfg_setup ( brushless22_cfg_t *cfg );

/**
 * @brief Brushless 22 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless22_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_init ( brushless22_t *ctx, brushless22_cfg_t *cfg );

/**
 * @brief Brushless 22 default configuration function.
 * @details This function executes a default configuration of Brushless 22
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless22_default_cfg ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set slew rate resistance function.
 * @details This function sets the slew rate resistance by configuring the onboard digital potentiometer.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance in Ohms (valid values from 4700 to 47000).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_set_slew_rate_resistance ( brushless22_t *ctx, uint16_t res_ohm );

/**
 * @brief Brushless 22 set rprog function.
 * @details This function sets the Rprog resistance by configuring the onboard digital potentiometer.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @param[in] res_ohm : Resistance in Ohms (valid values are 3900 and 24000 only).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_set_rprog ( brushless22_t *ctx, uint16_t res_ohm );

/**
 * @brief Brushless 22 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_set_duty_cycle ( brushless22_t *ctx, float duty_cycle );

/**
 * @brief Brushless 22 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_pwm_stop ( brushless22_t *ctx );

/**
 * @brief Brushless 22 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless22_pwm_start ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set strong start function.
 * @details This function sets the motor strong start by setting the SS pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless22_set_strong_start ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set soft start function.
 * @details This function sets the motor soft start by setting the SS pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless22_set_soft_start ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @param[in] dir @li @c 0 - Forward,
 *                @li @c 1 - Reverse.
 * @return None.
 * @note None.
 */
void brushless22_set_direction ( brushless22_t *ctx, uint8_t dir );

/**
 * @brief Brushless 22 switch direction function.
 * @details This function switches the direction by toggling the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless22_switch_direction ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set normal regulation function.
 * @details This function sets the normal regulation by setting the RT pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless22_set_normal_regulation ( brushless22_t *ctx );

/**
 * @brief Brushless 22 set low load regulation function.
 * @details This function sets the low load regulation by setting the RT pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless22_set_low_load_regulation ( brushless22_t *ctx );

/**
 * @brief Brushless 22 get fd pin function.
 * @details This function returns the FD pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless22_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless22_get_fg_pin ( brushless22_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS22_H

/*! @} */ // brushless22

// ------------------------------------------------------------------------ END
