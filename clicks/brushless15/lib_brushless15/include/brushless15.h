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
 * @file brushless15.h
 * @brief This file contains API for Brushless 15 Click Driver.
 */

#ifndef BRUSHLESS15_H
#define BRUSHLESS15_H

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
 * @addtogroup brushless15 Brushless 15 Click Driver
 * @brief API for configuring and manipulating Brushless 15 Click driver.
 * @{
 */

/**
 * @defgroup brushless15_set Brushless 15 PWM Settings
 * @brief Settings for configuration of Brushless 15 Click driver.
 */

/**
 * @addtogroup brushless15_cfg
 * @{
 */

/**
 * @brief Brushless 15 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Brushless 15 Click driver.
 */
#define BRUSHLESS15_DEF_FREQ            1000

/**
 * @brief Brushless 15 direction macros.
 * @details Specified macros for direction settings of Brushless 15 Click driver.
 */
#define BRUSHLESS15_DIR_CW              0
#define BRUSHLESS15_DIR_CCW             1

/*! @} */ // brushless15_cfg

/**
 * @defgroup brushless15_map Brushless 15 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 15 Click driver.
 */

/**
 * @addtogroup brushless15_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 15 Click to the selected MikroBUS.
 */
#define BRUSHLESS15_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless15_map
/*! @} */ // brushless15

/**
 * @brief Brushless 15 Click driver selector.
 * @details Selects target driver interface of Brushless 15 Click driver.
 */

/**
 * @brief Brushless 15 Click context object.
 * @details Context object definition of Brushless 15 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;      /**< Direction control pin. */
    digital_out_t en;       /**< Active-low enable pin. */

    // Input pins
    digital_in_t int_pin;   /**< Rotation signal interrupt pin. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} brushless15_t;

/**
 * @brief Brushless 15 Click configuration object.
 * @details Configuration object definition of Brushless 15 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */

    // Additional gpio pins
    pin_name_t dir;         /**< Direction control pin. */
    pin_name_t en;          /**< Active-low enable pin. */
    pin_name_t int_pin;     /**< Rotation signal interrupt pin. */

    // Static variable
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */

} brushless15_cfg_t;

/**
 * @brief Brushless 15 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS15_OK = 0,
    BRUSHLESS15_ERROR = -1

} brushless15_return_value_t;

/*!
 * @addtogroup brushless15 Brushless 15 Click Driver
 * @brief API for configuring and manipulating Brushless 15 Click driver.
 * @{
 */

/**
 * @brief Brushless 15 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless15_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless15_cfg_setup ( brushless15_cfg_t *cfg );

/**
 * @brief Brushless 15 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless15_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless15_init ( brushless15_t *ctx, brushless15_cfg_t *cfg );

/**
 * @brief Brushless 15 default configuration function.
 * @details This function executes a default configuration of Brushless 15
 * Click board.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless15_default_cfg ( brushless15_t *ctx );

/**
 * @brief Brushless 15 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless15_set_duty_cycle ( brushless15_t *ctx, float duty_cycle );

/**
 * @brief Brushless 15 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless15_pwm_stop ( brushless15_t *ctx );

/**
 * @brief Brushless 15 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless15_pwm_start ( brushless15_t *ctx );

/**
 * @brief Brushless 15 enable device function.
 * @details This function enables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless15_enable_device ( brushless15_t *ctx );

/**
 * @brief Brushless 15 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless15_disable_device ( brushless15_t *ctx );

/**
 * @brief Brushless 15 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless15_get_int_pin ( brushless15_t *ctx );

/**
 * @brief Brushless 15 set direction function.
 * @details This function sets the motor direction.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @param[in] direction : @li @c  0 - Clockwise,
 *                        @li @c  1 - Counter Clockwise.
 * @return None.
 * @note None.
 */
void brushless15_set_direction ( brushless15_t *ctx, uint8_t direction );

/**
 * @brief Brushless 15 switch direction function.
 * @details This function switches the direction by toggling the DIR pin state.
 * @param[in] ctx : Click context object.
 * See #brushless15_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless15_switch_direction ( brushless15_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS15_H

/*! @} */ // brushless15

// ------------------------------------------------------------------------ END
