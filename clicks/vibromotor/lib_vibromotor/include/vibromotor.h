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
 * @file vibromotor.h
 * @brief This file contains API for Vibro Motor Click Driver.
 */

#ifndef VIBROMOTOR_H
#define VIBROMOTOR_H

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
 * @addtogroup vibromotor Vibro Motor Click Driver
 * @brief API for configuring and manipulating Vibro Motor Click driver.
 * @{
 */

/**
 * @defgroup vibromotor_set Vibro Motor PWM Settings
 * @brief Settings for configuration of Vibro Motor Click driver.
 */

/**
 * @addtogroup vibromotor_cfg
 * @{
 */

/**
 * @brief Vibro Motor default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Vibro Motor Click driver.
 */
#define VIBROMOTOR_DEF_FREQ     5000

/*! @} */ // vibromotor_cfg

/**
 * @defgroup vibromotor_map Vibro Motor MikroBUS Map
 * @brief MikroBUS pin mapping of Vibro Motor Click driver.
 */

/**
 * @addtogroup vibromotor_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vibro Motor Click to the selected MikroBUS.
 */
#define VIBROMOTOR_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // vibromotor_map
/*! @} */ // vibromotor

/**
 * @brief Vibro Motor Click driver selector.
 * @details Selects target driver interface of Vibro Motor Click driver.
 */

/**
 * @brief Vibro Motor Click context object.
 * @details Context object definition of Vibro Motor Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                              /**< PWM frequency value. */

} vibromotor_t;

/**
 * @brief Vibro Motor Click configuration object.
 * @details Configuration object definition of Vibro Motor Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                                 /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;                          /**< PWM frequency value. */

} vibromotor_cfg_t;

/**
 * @brief Vibro Motor Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VIBROMOTOR_OK = 0,
   VIBROMOTOR_ERROR = -1

} vibromotor_return_value_t;

/*!
 * @addtogroup vibromotor Vibro Motor Click Driver
 * @brief API for configuring and manipulating Vibro Motor Click driver.
 * @{
 */

/**
 * @brief Vibro Motor configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vibromotor_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vibromotor_cfg_setup ( vibromotor_cfg_t *cfg );

/**
 * @brief Vibro Motor initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vibromotor_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vibromotor_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor_init ( vibromotor_t *ctx, vibromotor_cfg_t *cfg );

/**
 * @brief Vibro Motor sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #vibromotor_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor_set_duty_cycle ( vibromotor_t *ctx, float duty_cycle );

/**
 * @brief Vibro Motor stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor_pwm_stop ( vibromotor_t *ctx );

/**
 * @brief Vibro Motor start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor_pwm_start ( vibromotor_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VIBROMOTOR_H

/*! @} */ // vibromotor

// ------------------------------------------------------------------------ END
