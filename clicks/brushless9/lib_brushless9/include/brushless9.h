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
 * @file brushless9.h
 * @brief This file contains API for Brushless 9 Click Driver.
 */

#ifndef BRUSHLESS9_H
#define BRUSHLESS9_H

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
 * @addtogroup brushless9 Brushless 9 Click Driver
 * @brief API for configuring and manipulating Brushless 9 Click driver.
 * @{
 */

/**
 * @defgroup brushless9_set Brushless 9 PWM Settings
 * @brief Settings for configuration of Brushless 9 Click driver.
 */

/**
 * @addtogroup brushless9_cfg
 * @{
 */

/**
 * @brief Brushless 9 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 9 Click driver.
 */
#define BRUSHLESS9_DEF_FREQ     5000

/*! @} */ // brushless9_cfg

/**
 * @defgroup brushless9_map Brushless 9 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 9 Click driver.
 */

/**
 * @addtogroup brushless9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 9 Click to the selected MikroBUS.
 */
#define BRUSHLESS9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fg = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.brk = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless9_map
/*! @} */ // brushless9

/**
 * @brief Brushless 9 Click driver selector.
 * @details Selects target driver interface of Brushless 9 Click driver.
 */

/**
 * @brief Brushless 9 Click context object.
 * @details Context object definition of Brushless 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;      /**< Description. */
    digital_out_t brk;      /**< Description. */

    // Input pins
    digital_in_t fg;        /**< Description. */
    digital_in_t int_pin;   /**< Description. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} brushless9_t;

/**
 * @brief Brushless 9 Click configuration object.
 * @details Configuration object definition of Brushless 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */

    // Additional gpio pins
    pin_name_t fg;          /**< Description. */
    pin_name_t dir;         /**< Description. */
    pin_name_t brk;         /**< Description. */
    pin_name_t int_pin;     /**< Description. */

    // Static variable
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */

} brushless9_cfg_t;

/*!
 * @addtogroup brushless9 Brushless 9 Click Driver
 * @brief API for configuring and manipulating Brushless 9 Click driver.
 * @{
 */

/**
 * @brief Brushless 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless9_cfg_setup ( brushless9_cfg_t *cfg );

/**
 * @brief Brushless 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless9_init ( brushless9_t *ctx, brushless9_cfg_t *cfg );

/**
 * @brief Brushless 9 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless9_set_duty_cycle ( brushless9_t *ctx, float duty_cycle );

/**
 * @brief Brushless 9 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless9_pwm_stop ( brushless9_t *ctx );

/**
 * @brief Brushless 9 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t brushless9_pwm_start ( brushless9_t *ctx );

/**
 * @brief Brushless 9 @b dir pin setting.
 * @details This function sets @b dir pin output to
 * @b status setting.
 * @param[in] ctx Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void brushless9_set_dir ( brushless9_t *ctx, uint8_t state );

/**
 * @brief Brushless 9 @b brk pin setting.
 * @details This function sets @b brk pin output to
 * @b status setting.
 * @param[in] ctx Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @param[in] state Output value setting.
 *         @li @c  0 - digital out high,
 *         @li @c  1 - digital out low.
 */
void brushless9_set_brk ( brushless9_t *ctx, uint8_t state );

/**
 * @brief Brushless 9 @b fg state.
 * @details This function reads @b fg pin input state.
 * @param[in] ctx Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @return @li @c  0 - logical state low,
 *         @li @c  1 - logical state high.
 */
uint8_t brushless9_get_fg ( brushless9_t *ctx );

/**
 * @brief Brushless 9 @b int_pin state.
 * @details This function reads @b int_pin pin input state.
 * @param[in] ctx Click context object.
 * See #brushless9_t object definition for detailed explanation.
 * @return @li @c  0 - logical state low,
 *         @li @c  1 - logical state high.
 */
uint8_t brushless9_get_int_pin ( brushless9_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS9_H

/*! @} */ // brushless9

// ------------------------------------------------------------------------ END
