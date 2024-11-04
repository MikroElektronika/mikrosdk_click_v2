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
 * @file brushless24.h
 * @brief This file contains API for Brushless 24 Click Driver.
 */

#ifndef BRUSHLESS24_H
#define BRUSHLESS24_H

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
 * @addtogroup brushless24 Brushless 24 Click Driver
 * @brief API for configuring and manipulating Brushless 24 Click driver.
 * @{
 */

/**
 * @defgroup brushless24_cfg Brushless 24 PWM Settings
 * @brief Settings for configuration of Brushless 24 Click driver.
 */

/**
 * @addtogroup brushless24_cfg
 * @{
 */

/**
 * @brief Brushless 24 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 24 Click driver.
 */
#define BRUSHLESS24_DEF_FREQ      25000

/*! @} */ // brushless24_cfg

/**
 * @defgroup brushless24_map Brushless 24 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 24 Click driver.
 */

/**
 * @addtogroup brushless24_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 24 Click to the selected MikroBUS.
 */
#define BRUSHLESS24_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless24_map
/*! @} */ // brushless24

/**
 * @brief Brushless 24 Click context object.
 * @details Context object definition of Brushless 24 Click driver.
 */
typedef struct
{
    // Input pins
    digital_in_t int_pin;                       /**< Frequency generator output. */

    // Modules
    pwm_t pwm;                                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                          /**< PWM frequency value. */

} brushless24_t;

/**
 * @brief Brushless 24 Click configuration object.
 * @details Configuration object definition of Brushless 24 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                             /**< PWM pin. */

    // Additional gpio pins
    pin_name_t int_pin;                         /**< Frequency generator output. */

    // Static variable
    uint32_t dev_pwm_freq;                      /**< PWM frequency value. */

} brushless24_cfg_t;

/**
 * @brief Brushless 24 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS24_OK = 0,
    BRUSHLESS24_ERROR = -1

} brushless24_return_value_t;

/*!
 * @addtogroup brushless24 Brushless 24 Click Driver
 * @brief API for configuring and manipulating Brushless 24 Click driver.
 * @{
 */

/**
 * @brief Brushless 24 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless24_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless24_cfg_setup ( brushless24_cfg_t *cfg );

/**
 * @brief Brushless 24 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless24_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless24_init ( brushless24_t *ctx, brushless24_cfg_t *cfg );

/**
 * @brief Brushless 24 default configuration function.
 * @details This function executes a default configuration of Brushless 24
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless24_default_cfg ( brushless24_t *ctx );

/**
 * @brief Brushless 24 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless24_set_duty_cycle ( brushless24_t *ctx, float duty_cycle );

/**
 * @brief Brushless 24 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless24_pwm_stop ( brushless24_t *ctx );

/**
 * @brief Brushless 24 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless24_pwm_start ( brushless24_t *ctx );

/**
 * @brief Brushless 24 get INT pin state.
 * @details This function reads state of the INT pin.
 * @param[in] ctx : Click context object.
 * See #brushless24_t object definition for detailed explanation.
 * @return State of the INT pin.
 * @note None.
 */
uint8_t brushless24_get_int_state ( brushless24_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS24_H

/*! @} */ // brushless24

// ------------------------------------------------------------------------ END
