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
 * @file buttonpower.h
 * @brief This file contains API for Button Power Click Driver.
 */

#ifndef BUTTONPOWER_H
#define BUTTONPOWER_H

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
 * @addtogroup buttonpower Button Power Click Driver
 * @brief API for configuring and manipulating Button Power Click driver.
 * @{
 */

/**
 * @defgroup buttonpower_set Button Power PWM Settings
 * @brief Settings for configuration of Button Power Click driver.
 */

/**
 * @addtogroup buttonpower_cfg
 * @{
 */

/**
 * @brief ButtonPower default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Button Power Click driver.
 */
#define BUTTONPOWER_DEF_FREQ     500

/*! @} */ // buttonpower_cfg

/**
 * @defgroup buttonpower_map Button Power MikroBUS Map
 * @brief MikroBUS pin mapping of Button Power Click driver.
 */

/**
 * @addtogroup buttonpower_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button Power Click to the selected MikroBUS.
 */
#define BUTTONPOWER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buttonpower_map
/*! @} */ // buttonpower

/**
 * @brief Button Power Click driver selector.
 * @details Selects target driver interface of Button Power Click driver.
 */

/**
 * @brief Button Power Click context object.
 * @details Context object definition of Button Power Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} buttonpower_t;

/**
 * @brief Button Power Click configuration object.
 * @details Configuration object definition of Button Power Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< PWM pin. */

    pin_name_t int_pin;      /**< Interrupt pin. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} buttonpower_cfg_t;

/**
 * @brief Button Power Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUTTONPOWER_OK = 0,
   BUTTONPOWER_ERROR = -1

} buttonpower_return_value_t;

/*!
 * @addtogroup buttonpower Button Power Click Driver
 * @brief API for configuring and manipulating Button Power Click driver.
 * @{
 */

/**
 * @brief Button Power configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buttonpower_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buttonpower_cfg_setup ( buttonpower_cfg_t *cfg );

/**
 * @brief Button Power initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buttonpower_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buttonpower_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonpower_init ( buttonpower_t *ctx, buttonpower_cfg_t *cfg );

/**
 * @brief Button Power sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buttonpower_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonpower_set_duty_cycle ( buttonpower_t *ctx, float duty_cycle );

/**
 * @brief Button Power stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonpower_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonpower_pwm_stop ( buttonpower_t *ctx );

/**
 * @brief Button Power start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonpower_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonpower_pwm_start ( buttonpower_t *ctx );

/**
 * @brief Button Power get button state function.
 * @details This function reads the digital signal from the INT pin which tells us whether 
 * the button has been pressed or not.
 * @param[out] ctx : Click context object.
 * See #buttonpower_t object definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t buttonpower_get_button_state ( buttonpower_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTONPOWER_H

/*! @} */ // buttonpower

// ------------------------------------------------------------------------ END
