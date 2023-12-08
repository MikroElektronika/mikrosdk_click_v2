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
 * @file brushless17.h
 * @brief This file contains API for Brushless 17 Click Driver.
 */

#ifndef BRUSHLESS17_H
#define BRUSHLESS17_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup brushless17 Brushless 17 Click Driver
 * @brief API for configuring and manipulating Brushless 17 Click driver.
 * @{
 */

/**
 * @defgroup brushless17_set Brushless 17 PWM Settings
 * @brief Settings for configuration of Brushless 17 Click driver.
 */

/**
 * @addtogroup brushless17_cfg
 * @{
 */

/**
 * @brief Brushless 17 direction setting.
 * @details Specified setting for direction of Brushless 17 Click driver.
 */
#define BRUSHLESS17_DIR_CCW             0
#define BRUSHLESS17_DIR_CW              1

/**
 * @brief Brushless 17 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 17 Click driver.
 */
#define BRUSHLESS17_DEF_FREQ            5000

/*! @} */ // brushless17_cfg

/**
 * @defgroup brushless17_map Brushless 17 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 17 Click driver.
 */

/**
 * @addtogroup brushless17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 17 Click to the selected MikroBUS.
 */
#define BRUSHLESS17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.brk = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.diag = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless17_map
/*! @} */ // brushless17

/**
 * @brief Brushless 17 Click driver selector.
 * @details Selects target driver interface of Brushless 17 Click driver.
 */

/**
 * @brief Brushless 17 Click context object.
 * @details Context object definition of Brushless 17 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t brk;          /**< Brake pin (Active Low). */
    digital_out_t dir;          /**< Direction pin (CW-HIGH, CCW-LOW). */
    digital_out_t en;           /**< Chip enable pin (Active High). */

    // Input pins
    digital_in_t diag;          /**< Diagnostic pin (Active Low). */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} brushless17_t;

/**
 * @brief Brushless 17 Click configuration object.
 * @details Configuration object definition of Brushless 17 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t brk;             /**< Brake pin (Active Low). */
    pin_name_t dir;             /**< Direction pin (CW-HIGH, CCW-LOW). */
    pin_name_t en;              /**< Chip enable pin (Active High). */
    pin_name_t diag;            /**< Diagnostic pin (Active Low). */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} brushless17_cfg_t;

/**
 * @brief Brushless 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS17_OK = 0,
    BRUSHLESS17_ERROR = -1

} brushless17_return_value_t;

/*!
 * @addtogroup brushless17 Brushless 17 Click Driver
 * @brief API for configuring and manipulating Brushless 17 Click driver.
 * @{
 */

/**
 * @brief Brushless 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless17_cfg_setup ( brushless17_cfg_t *cfg );

/**
 * @brief Brushless 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless17_init ( brushless17_t *ctx, brushless17_cfg_t *cfg );

/**
 * @brief Brushless 17 default configuration function.
 * @details This function executes a default configuration of Brushless 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless17_default_cfg ( brushless17_t *ctx );

/**
 * @brief Brushless 17 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless17_set_duty_cycle ( brushless17_t *ctx, float duty_cycle );

/**
 * @brief Brushless 17 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless17_pwm_stop ( brushless17_t *ctx );

/**
 * @brief Brushless 17 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless17_pwm_start ( brushless17_t *ctx );

/**
 * @brief Brushless 17 enable chip function.
 * @details This function enables the chip by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless17_enable_chip ( brushless17_t *ctx );

/**
 * @brief Brushless 17 disable chip function.
 * @details This function disables the chip by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless17_disable_chip ( brushless17_t *ctx );

/**
 * @brief Brushless 17 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @param[in] dir @li @c 0 - Counter Clockwise,
 *                @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void brushless17_set_direction ( brushless17_t *ctx, uint8_t dir );

/**
 * @brief Brushless 17 switch direction function.
 * @details This function switches the direction by toggling the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless17_switch_direction ( brushless17_t *ctx );

/**
 * @brief Brushless 17 pull brake function.
 * @details This function pulls brake by setting the BRK pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless17_pull_brake ( brushless17_t *ctx );

/**
 * @brief Brushless 17 release brake function.
 * @details This function releases brake by setting the BRK pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless17_release_brake ( brushless17_t *ctx );

/**
 * @brief Brushless 17 get diagnostic pin function.
 * @details This function returns the DIAG pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless17_t object definition for detailed explanation.
 * @return @li @c 0 - An overcurrent or overtemperature event has occured,
 *         @li @c 1 - Normal operation.
 * @note None.
 */
uint8_t brushless17_get_diagnostic_pin ( brushless17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS17_H

/*! @} */ // brushless17

// ------------------------------------------------------------------------ END
