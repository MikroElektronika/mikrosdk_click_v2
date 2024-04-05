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
 * @file brushless11.h
 * @brief This file contains API for Brushless 11 Click Driver.
 */

#ifndef BRUSHLESS11_H
#define BRUSHLESS11_H

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
 * @addtogroup brushless11 Brushless 11 Click Driver
 * @brief API for configuring and manipulating Brushless 11 Click driver.
 * @{
 */

/**
 * @defgroup brushless11_cfg Brushless 11 PWM Settings
 * @brief Settings for configuration of Brushless 11 Click driver.
 */

/**
 * @addtogroup brushless11_cfg
 * @{
 */

/**
 * @brief Brushless 11 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 11 Click driver.
 */
#define BRUSHLESS11_DEF_FREQ                5000

/**
 * @brief Brushless 11 pin states.
 * @details Specified setting for pin states of Brushless 11 Click driver.
 */
#define BRUSHLESS11_PIN_STATE_HIGH          0x01
#define BRUSHLESS11_PIN_STATE_LOW           0x00

/**
 * @brief Brushless 11 brake states.
 * @details Specified setting for brake states of Brushless 11 Click driver.
 */
#define BRUSHLESS11_BRAKE_ON                0x01
#define BRUSHLESS11_BRAKE_OFF               0x00

/*! @} */ // brushless11_cfg

/**
 * @defgroup brushless11_map Brushless 11 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 11 Click driver.
 */

/**
 * @addtogroup brushless11_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 11 Click to the selected MikroBUS.
 */
#define BRUSHLESS11_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fg1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.brk = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.fg2 = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless11_map
/*! @} */ // brushless11

/**
 * @brief Brushless 11 Click context object.
 * @details Context object definition of Brushless 11 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t brk;              /**< Motor brake pin. */

    // Input pins
    digital_in_t fg1;               /**< FG 1 speed control output pin. */
    digital_in_t fg2;               /**< FG 2 speed control output pin. */

    // Modules
    pwm_t pwm;                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;              /**< PWM frequency value. */

} brushless11_t;

/**
 * @brief Brushless 11 Click configuration object.
 * @details Configuration object definition of Brushless 11 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                 /**< PWM pin. */

    // Additional gpio pins
    pin_name_t fg1;                 /**< FG 1 speed control output pin. */
    pin_name_t brk;                 /**< Motor brake pin. */ 
    pin_name_t fg2;                 /**< FG 2 speed control output pin. */

    // Static variable
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} brushless11_cfg_t;

/**
 * @brief Brushless 11 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS11_OK = 0,
    BRUSHLESS11_ERROR = -1

} brushless11_return_value_t;

/*!
 * @addtogroup brushless11 Brushless 11 Click Driver
 * @brief API for configuring and manipulating Brushless 11 Click driver.
 * @{
 */

/**
 * @brief Brushless 11 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless11_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless11_cfg_setup ( brushless11_cfg_t *cfg );

/**
 * @brief Brushless 11 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless11_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless11_init ( brushless11_t *ctx, brushless11_cfg_t *cfg );

/**
 * @brief Brushless 11 default configuration function.
 * @details This function executes a default configuration of Brushless 11
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless11_default_cfg ( brushless11_t *ctx );

/**
 * @brief Brushless 11 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless11_set_duty_cycle ( brushless11_t *ctx, float duty_cycle );

/**
 * @brief Brushless 11 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless11_pwm_stop ( brushless11_t *ctx );

/**
 * @brief Brushless 11 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless11_pwm_start ( brushless11_t *ctx );

/**
 * @brief Brushless 11 set BRK pin state function.
 * @details This function is used to set state of the BRK pin.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @param[in] pin_state : State of the BRK pin.
 * @return Nothing.
 * @note None.
 */
void brushless11_set_brk_pin ( brushless11_t *ctx, uint8_t pin_state );

/**
 * @brief Brushless 11 get FG1 pin state function.
 * @details This function is used to get state of the FG1 pin.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t brushless11_get_fg1_pin ( brushless11_t *ctx );

/**
 * @brief Brushless 11 get FG2 pin state function.
 * @details This function is used to get state of the FG2 pin.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @return @li @c 0 - Pin state low,
 *         @li @c 1 - Pin state high.
 * @note None.
 */
uint8_t brushless11_get_fg2_pin ( brushless11_t *ctx );

/**
 * @brief Brushless 11 set motor brake state function.
 * @details This function is used to set state of the motor brake.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @param[in] brake_state : State of the motor brake.
 * @return Nothing.
 * @note None.
 */
void brushless11_set_brake ( brushless11_t *ctx, uint8_t brake_state );

/**
 * @brief Brushless 11 set motor speed.
 * @details This function is used to set motor speed.
 * @param[in] ctx : Click context object.
 * See #brushless11_t object definition for detailed explanation.
 * @param[in] speed : Motor speed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless11_set_speed ( brushless11_t *ctx, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS11_H

/*! @} */ // brushless11

// ------------------------------------------------------------------------ END
