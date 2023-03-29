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
 * @file buttonalarm.h
 * @brief This file contains API for Button Alarm Click Driver.
 */

#ifndef BUTTONALARM_H
#define BUTTONALARM_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup buttonalarm Button Alarm Click Driver
 * @brief API for configuring and manipulating Button Alarm Click driver.
 * @{
 */

/**
 * @defgroup buttonalarm_set Button Alarm PWM Settings
 * @brief Settings for configuration of Button Alarm Click driver.
 */

/**
 * @addtogroup buttonalarm_cfg
 * @{
 */

/**
 * @brief ButtonAlarm default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Button Alarm Click driver.
 */
#define BUTTONALARM_DEF_FREQ     500

/*! @} */ // buttonalarm_cfg

/**
 * @defgroup buttonalarm_map Button Alarm MikroBUS Map
 * @brief MikroBUS pin mapping of Button Alarm Click driver.
 */

/**
 * @addtogroup buttonalarm_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button Alarm Click to the selected MikroBUS.
 */
#define BUTTONALARM_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buttonalarm_map
/*! @} */ // buttonalarm

/**
 * @brief Button Alarm Click driver selector.
 * @details Selects target driver interface of Button Alarm Click driver.
 */

/**
 * @brief Button Alarm Click context object.
 * @details Context object definition of Button Alarm Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} buttonalarm_t;

/**
 * @brief Button Alarm Click configuration object.
 * @details Configuration object definition of Button Alarm Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< PWM pin. */

    pin_name_t int_pin;      /**< Interrupt pin. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} buttonalarm_cfg_t;

/**
 * @brief Button Alarm Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUTTONALARM_OK = 0,
   BUTTONALARM_ERROR = -1

} buttonalarm_return_value_t;

/*!
 * @addtogroup buttonalarm Button Alarm Click Driver
 * @brief API for configuring and manipulating Button Alarm Click driver.
 * @{
 */

/**
 * @brief Button Alarm configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buttonalarm_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buttonalarm_cfg_setup ( buttonalarm_cfg_t *cfg );

/**
 * @brief Button Alarm initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buttonalarm_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buttonalarm_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonalarm_init ( buttonalarm_t *ctx, buttonalarm_cfg_t *cfg );

/**
 * @brief Button Alarm sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buttonalarm_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonalarm_set_duty_cycle ( buttonalarm_t *ctx, float duty_cycle );

/**
 * @brief Button Alarm stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonalarm_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonalarm_pwm_stop ( buttonalarm_t *ctx );

/**
 * @brief Button Alarm start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonalarm_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonalarm_pwm_start ( buttonalarm_t *ctx );

/**
 * @brief Button Alarm get button state function.
 * @details This function reads the digital signal from the INT pin which tells us whether 
 * the button has been pressed or not.
 * @param[out] ctx : Click context object.
 * See #buttonalarm_t object definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t buttonalarm_get_button_state ( buttonalarm_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTONALARM_H

/*! @} */ // buttonalarm

// ------------------------------------------------------------------------ END

