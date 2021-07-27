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
 * @file haptic2.h
 * @brief This file contains API for HAPTIC 2 Click Driver.
 */

#ifndef HAPTIC2_H
#define HAPTIC2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup haptic2 HAPTIC 2 Click Driver
 * @brief API for configuring and manipulating HAPTIC 2 Click driver.
 * @{
 */

/**
 * @defgroup haptic2_set HAPTIC 2 PWM Settings
 * @brief Settings for configuration of HAPTIC 2 Click driver.
 */

/**
 * @addtogroup haptic2_cfg
 * @{
 */

/**
 * @brief HAPTIC 2 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of HAPTIC 2 Click driver.
 */
#define HAPTIC2_DEF_FREQ    8000

/*! @} */ // haptic2_cfg

/**
 * @defgroup haptic2_map HAPTIC 2 MikroBUS Map
 * @brief MikroBUS pin mapping of HAPTIC 2 Click driver.
 */

/**
 * @addtogroup haptic2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of HAPTIC 2 Click to the selected MikroBUS.
 */
#define HAPTIC2_MAP_MIKROBUS( cfg, mikrobus )      \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // haptic2_map
/*! @} */ // haptic2

/**
 * @brief HAPTIC 2 Click driver selector.
 * @details Selects target driver interface of HAPTIC 2 Click driver.
 */

/**
 * @brief HAPTIC 2 Click context object.
 * @details Context object definition of HAPTIC 2 Click driver.
 */
typedef struct
{
    // Modules

    pwm_t pwm;                /**< PWM driver object. */

    // ctx variable

    uint32_t pwm_freq;        /**< PWM frequency value. */

} haptic2_t;

/**
 * @brief HAPTIC 2 Click configuration object.
 * @details Configuration object definition of HAPTIC 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins

    pin_name_t pwm;           /**< PWM pin. */

    // Static variable

    uint32_t dev_pwm_freq;    /**< PWM frequency value. */

} haptic2_cfg_t;

/*!
 * @addtogroup haptic2 HAPTIC 2 Click Driver
 * @brief API for configuring and manipulating HAPTIC 2 Click driver.
 * @{
 */

/**
 * @brief HAPTIC 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #haptic2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void haptic2_cfg_setup ( haptic2_cfg_t *cfg );

/**
 * @brief HAPTIC 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #haptic2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #haptic2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic2_init ( haptic2_t *ctx, haptic2_cfg_t *cfg );

/**
 * @brief HAPTIC 2 default configuration function.
 * @details This function executes a default configuration of HAPTIC 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #haptic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t haptic2_default_cfg ( haptic2_t *ctx );

/**
 * @brief HAPTIC 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #haptic2_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic2_set_duty_cycle ( haptic2_t *ctx, float duty_ratio );

/**
 * @brief HAPTIC 2 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #haptic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic2_pwm_stop ( haptic2_t *ctx );

/**
 * @brief HAPTIC 2 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #haptic2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t haptic2_pwm_start ( haptic2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HAPTIC2_H

/*! @} */ // haptic2

// ------------------------------------------------------------------------ END
