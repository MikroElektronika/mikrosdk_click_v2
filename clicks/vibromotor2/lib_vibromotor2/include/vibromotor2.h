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
 * @file vibromotor2.h
 * @brief This file contains API for Vibro Motor 2 Click Driver.
 */

#ifndef VIBROMOTOR2_H
#define VIBROMOTOR2_H

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
#include "drv_pwm.h"

/*!
 * @addtogroup vibromotor2 Vibro Motor 2 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 2 Click driver.
 * @{
 */

/**
 * @defgroup vibromotor2_set Vibro Motor 2 PWM Settings
 * @brief Settings for configuration of Vibro Motor 2 Click driver.
 */

/**
 * @addtogroup vibromotor2_cfg
 * @{
 */

/**
 * @brief Vibro Motor 2 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Vibro Motor 2 Click driver.
 */
#define VIBROMOTOR2_DEF_FREQ     5000

/*! @} */ // vibromotor2_cfg

/**
 * @defgroup vibromotor2_map Vibro Motor 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Vibro Motor 2 Click driver.
 */

/**
 * @addtogroup vibromotor2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Vibro Motor 2 Click to the selected MikroBUS.
 */
#define VIBROMOTOR2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // vibromotor2_map
/*! @} */ // vibromotor2

/**
 * @brief Vibro Motor 2 Click driver selector.
 * @details Selects target driver interface of Vibro Motor 2 Click driver.
 */

/**
 * @brief Vibro Motor 2 Click context object.
 * @details Context object definition of Vibro Motor 2 Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                              /**< PWM frequency value. */

} vibromotor2_t;

/**
 * @brief Vibro Motor 2 Click configuration object.
 * @details Configuration object definition of Vibro Motor 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                                 /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;                          /**< PWM frequency value. */

} vibromotor2_cfg_t;

/**
 * @brief Vibro Motor 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   VIBROMOTOR2_OK = 0,
   VIBROMOTOR2_ERROR = -1

} vibromotor2_return_value_t;

/*!
 * @addtogroup vibromotor2 Vibro Motor 2 Click Driver
 * @brief API for configuring and manipulating Vibro Motor 2 Click driver.
 * @{
 */

/**
 * @brief Vibro Motor 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vibromotor2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vibromotor2_cfg_setup ( vibromotor2_cfg_t *cfg );

/**
 * @brief Vibro Motor 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #vibromotor2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vibromotor2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor2_init ( vibromotor2_t *ctx, vibromotor2_cfg_t *cfg );

/**
 * @brief Vibro Motor 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #vibromotor2_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor2_set_duty_cycle ( vibromotor2_t *ctx, float duty_cycle );

/**
 * @brief Vibro Motor 2 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor2_pwm_stop ( vibromotor2_t *ctx );

/**
 * @brief Vibro Motor 2 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #vibromotor2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vibromotor2_pwm_start ( vibromotor2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VIBROMOTOR2_H

/*! @} */ // vibromotor2

// ------------------------------------------------------------------------ END
