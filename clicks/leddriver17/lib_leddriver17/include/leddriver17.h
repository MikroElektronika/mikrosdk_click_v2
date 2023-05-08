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
 * @file leddriver17.h
 * @brief This file contains API for LED Driver 17 Click Driver.
 */

#ifndef LEDDRIVER17_H
#define LEDDRIVER17_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup leddriver17 LED Driver 17 Click Driver
 * @brief API for configuring and manipulating LED Driver 17 Click driver.
 * @{
 */

/**
 * @defgroup leddriver17_cfg LED Driver 17 PWM Settings
 * @brief Settings for configuration of LED Driver 17 Click driver.
 */

/**
 * @addtogroup leddriver17_cfg
 * @{
 */

/**
 * @brief LED Driver 17 default PWM frequency.
 * @details Specified setting for default PWM frequency of LED Driver 17 Click driver.
 */
#define LEDDRIVER17_DEF_FREQ        20000

/*! @} */ // leddriver17_cfg

/**
 * @defgroup leddriver17_map LED Driver 17 MikroBUS Map
 * @brief MikroBUS pin mapping of LED Driver 17 Click driver.
 */

/**
 * @addtogroup leddriver17_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of LED Driver 17 Click to the selected MikroBUS.
 */
#define LEDDRIVER17_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // leddriver17_map
/*! @} */ // leddriver17

/**
 * @brief LED Driver 17 Click context object.
 * @details Context object definition of LED Driver 17 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t flt;           /**< Fault indication pin (Active low). */

    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} leddriver17_t;

/**
 * @brief LED Driver 17 Click configuration object.
 * @details Configuration object definition of LED Driver 17 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t flt;             /**< Fault indication pin (Active low). */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} leddriver17_cfg_t;

/**
 * @brief LED Driver 17 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    LEDDRIVER17_OK = 0,
    LEDDRIVER17_ERROR = -1

} leddriver17_return_value_t;

/*!
 * @addtogroup leddriver17 LED Driver 17 Click Driver
 * @brief API for configuring and manipulating LED Driver 17 Click driver.
 * @{
 */

/**
 * @brief LED Driver 17 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #leddriver17_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void leddriver17_cfg_setup ( leddriver17_cfg_t *cfg );

/**
 * @brief LED Driver 17 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #leddriver17_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver17_init ( leddriver17_t *ctx, leddriver17_cfg_t *cfg );

/**
 * @brief LED Driver 17 default configuration function.
 * @details This function executes a default configuration of LED Driver 17
 * click board.
 * @param[in] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t leddriver17_default_cfg ( leddriver17_t *ctx );

/**
 * @brief LED Driver 17 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver17_set_duty_cycle ( leddriver17_t *ctx, float duty_cycle );

/**
 * @brief LED Driver 17 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver17_pwm_stop ( leddriver17_t *ctx );

/**
 * @brief LED Driver 17 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t leddriver17_pwm_start ( leddriver17_t *ctx );

/**
 * @brief LED Driver 17 get fault pin function.
 * @details This function returns the fault (FLT) pin logic state.
 * @param[in] ctx : Click context object.
 * See #leddriver17_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t leddriver17_get_fault_pin ( leddriver17_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // LEDDRIVER17_H

/*! @} */ // leddriver17

// ------------------------------------------------------------------------ END
