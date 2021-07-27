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
 * @file buttonplay.h
 * @brief This file contains API for Button Play Click Driver.
 */

#ifndef BUTTONPLAY_H
#define BUTTONPLAY_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup buttonplay Button Play Click Driver
 * @brief API for configuring and manipulating Button Play Click driver.
 * @{
 */

/**
 * @defgroup buttonplay_set Button Play PWM Settings
 * @brief Settings for configuration of Button Play Click driver.
 */

/**
 * @addtogroup buttonplay_cfg
 * @{
 */

/**
 * @brief ButtonPlay default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Button Play Click driver.
 */
#define BUTTONPLAY_DEF_FREQ     500

/*! @} */ // buttonplay_cfg

/**
 * @defgroup buttonplay_map Button Play MikroBUS Map
 * @brief MikroBUS pin mapping of Button Play Click driver.
 */

/**
 * @addtogroup buttonplay_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button Play Click to the selected MikroBUS.
 */
#define BUTTONPLAY_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buttonplay_map
/*! @} */ // buttonplay

/**
 * @brief Button Play Click driver selector.
 * @details Selects target driver interface of Button Play Click driver.
 */

/**
 * @brief Button Play Click context object.
 * @details Context object definition of Button Play Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} buttonplay_t;

/**
 * @brief Button Play Click configuration object.
 * @details Configuration object definition of Button Play Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< PWM pin. */

    pin_name_t int_pin;      /**< Interrupt pin. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} buttonplay_cfg_t;

/**
 * @brief Button Play Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUTTONPLAY_OK = 0,
   BUTTONPLAY_ERROR = -1

} buttonplay_return_value_t;

/*!
 * @addtogroup buttonplay Button Play Click Driver
 * @brief API for configuring and manipulating Button Play Click driver.
 * @{
 */

/**
 * @brief Button Play configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buttonplay_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buttonplay_cfg_setup ( buttonplay_cfg_t *cfg );

/**
 * @brief Button Play initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buttonplay_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buttonplay_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonplay_init ( buttonplay_t *ctx, buttonplay_cfg_t *cfg );

/**
 * @brief Button Play sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buttonplay_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonplay_set_duty_cycle ( buttonplay_t *ctx, float duty_cycle );

/**
 * @brief Button Play stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonplay_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonplay_pwm_stop ( buttonplay_t *ctx );

/**
 * @brief Button Play start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttonplay_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttonplay_pwm_start ( buttonplay_t *ctx );

/**
 * @brief Button Play get button state function.
 * @details This function reads the digital signal from the INT pin which tells us whether 
 * the button has been pressed or not.
 * @param[out] ctx : Click context object.
 * See #buttonplay_t object definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t buttonplay_get_button_state ( buttonplay_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTONPLAY_H

/*! @} */ // buttonplay

// ------------------------------------------------------------------------ END
