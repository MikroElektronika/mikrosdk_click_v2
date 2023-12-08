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
 * @file leddriver13.h
 * @brief This file contains API for LED Driver 13 Click Driver.
 */

#ifndef LEDDRIVER13_H
#define LEDDRIVER13_H

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
 * @addtogroup leddriver13 LED Driver 13 Click Driver
 * @brief API for configuring and manipulating LED Driver 13 Click driver.
 * @{
 */

/**
 * @defgroup leddriver13_set LED Driver 13 PWM Settings
 * @brief Settings for configuration of LED Driver 13 Click driver.
 */

/**
 * @addtogroup leddriver13_cfg
 * @{
 */

/**
 * @brief LED Driver 13 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of LED Driver 13 Click driver.
 */
#define LEDDRIVER13_DEF_FREQ         5000

#define LEDDRIVER13_FAULT_OCCURS        0
#define LEDDRIVER13_CONDITION_OK        1

/*! @} */ // leddriver13_cfg

/**
 * @defgroup leddriver13_map LED Driver 13 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 13 Click driver.
 */

/**
 * @addtogroup leddriver13_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 13 Click to the selected MikroBUS.
 */
#define LEDDRIVER13_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS );   \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // leddriver13_map
/*! @} */ // leddriver13

/**
 * @brief LED Driver 13 Click driver selector.
 * @details Selects target driver interface of LED Driver 13 Click driver.
 */

/**
 * @brief LED Driver 13 Click context object.
 * @details Context object definition of LED Driver 13 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;       /**< Description. */

    // Input pins
    digital_in_t flt;       /**< Description. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} leddriver13_t;

/**
 * @brief LED Driver 13 Click configuration object.
 * @details Configuration object definition of LED Driver 13 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t en;              /**< Description. */
    pin_name_t flt;             /**< Description. */

    // Static variable
    uint32_t dev_pwm_freq;     /**< PWM frequency value. */

} leddriver13_cfg_t;

/**
 * @brief LED Driver 13 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER13_OK = 0,
    LEDDRIVER13_ERROR = -1,

} leddriver13_return_value_t;

/*!
 * @addtogroup leddriver13 LED Driver 13 Click Driver
 * @brief API for configuring and manipulating LED Driver 13 Click driver.
 * @{
 */

/**
 * @brief LED Driver 13 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver13_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver13_cfg_setup ( leddriver13_cfg_t *cfg );

/**
 * @brief LED Driver 13 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver13_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver13_init ( leddriver13_t *ctx, leddriver13_cfg_t *cfg );

/**
 * @brief LED Driver 13 default configuration function.
 * @details This function executes a default configuration of LED Driver 13
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver13_default_cfg ( leddriver13_t *ctx );

/**
 * @brief LED Driver 13 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver13_set_duty_cycle ( leddriver13_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 13 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver13_pwm_stop ( leddriver13_t *ctx );

/**
 * @brief LED Driver 13 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver13_pwm_start ( leddriver13_t *ctx );

/**
 * @brief LED Driver 13 set enable function.
 * @details This function enable 
 * the A80604 High Power LED Driver with Pre-Emptive Boost
 * for Ultra-High Dimming Ratio and Low Output Ripple
 * on the LED Driver 13 board™.
 * @param[out] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *
 * @note None.
 */
err_t leddriver13_set_enable ( leddriver13_t *ctx );

/**
 * @brief LED Driver 13 set disable function.
 * @details This function disable
 * the A80604 High Power LED Driver with Pre-Emptive Boost
 * for Ultra-High Dimming Ratio and Low Output Ripple
 * on the LED Driver 13 board™.
 * @param[out] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *
 * @note None.
 */
err_t leddriver13_set_disable ( leddriver13_t *ctx );

/**
 * @brief LED Driver 13 get fault function.
 * @details This function get fault state 
 * of the A80604 High Power LED Driver with Pre-Emptive Boost
 * for Ultra-High Dimming Ratio and Low Output Ripple
 * on the LED Driver 13 board™.
 * @param[out] ctx : Click context object.
 * See #leddriver13_t object definition for detailed explanation.
 * @return @li @c 0 ( LEDDRIVER13_FAULT_OCCURS ) - Fault occurs,
 *         @li @c 1 ( LEDDRIVER13_CONDITION_OK ) - Condition OK, No Fault.
 *
 * @note None.
 */
uint8_t leddriver13_get_fault ( leddriver13_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER13_H

/*! @} */ // leddriver13

// ------------------------------------------------------------------------ END
