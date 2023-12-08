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
 * @file buttong.h
 * @brief This file contains API for Button G Click Driver.
 */


#ifndef BUTTONG_H
#define BUTTONG_H

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
 * @addtogroup buttong Button G Click Driver
 * @brief API for configuring and manipulating Button G Click driver.
 * @{
 */

/**
 * @defgroup buttong_set Button G PWM Settings
 * @brief Settings for configuration of Button G Click driver.
 */

/**
 * @addtogroup buttong_cfg
 * @{
 */

/**
 * @brief Button G default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Button G Click driver.
 */
#define BUTTONG_DEF_FREQ     500

/*! @} */ // buttong_cfg

/**
 * @defgroup buttong_map Button G MikroBUS Map
 * @brief MikroBUS pin mapping of Button G Click driver.
 */

/**
 * @addtogroup buttong_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Button G Click to the selected MikroBUS.
 */
#define BUTTONG_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // buttong_map
/*! @} */ // buttong

/**
 * @brief Button G Click driver selector.
 * @details Selects target driver interface of Button G Click driver.
 */

/**
 * @brief Button G Click context object.
 * @details Context object definition of Button G Click driver.
 */
typedef struct
{
    digital_in_t int_pin;       /**< Interrupt pin. */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} buttong_t;

/**
 * @brief Button G Click configuration object.
 * @details Configuration object definition of Button G Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< PWM pin. */

    pin_name_t int_pin;      /**< Interrupt pin. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} buttong_cfg_t;

/**
 * @brief Button G Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BUTTONG_OK = 0,
   BUTTONG_ERROR = -1

} buttong_return_value_t;

/*!
 * @addtogroup buttong Button G Click Driver
 * @brief API for configuring and manipulating Button G Click driver.
 * @{
 */

/**
 * @brief Button G configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #buttong_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void buttong_cfg_setup ( buttong_cfg_t *cfg );

/**
 * @brief Button G initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #buttong_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #buttong_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttong_init ( buttong_t *ctx, buttong_cfg_t *cfg );

/**
 * @brief Button G sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #buttong_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttong_set_duty_cycle ( buttong_t *ctx, float duty_cycle );

/**
 * @brief Button G stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttong_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttong_pwm_stop ( buttong_t *ctx );

/**
 * @brief Button G start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #buttong_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t buttong_pwm_start ( buttong_t *ctx );

/**
 * @brief Button G get button state function.
 * @details This function reads the digital signal from the INT pin which tells us whether 
 * the button has been pressed or not.
 * @param[out] ctx : Click context object.
 * See #buttong_t object definition for detailed explanation.
 * @return Function returns pin logical state (1 or 0).
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t buttong_get_button_state ( buttong_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BUTTONG_H

/*! @} */ // buttong

// ------------------------------------------------------------------------ END
