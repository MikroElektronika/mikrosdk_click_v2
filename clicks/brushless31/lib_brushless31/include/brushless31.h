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
 * @file brushless31.h
 * @brief This file contains API for Brushless 31 Click Driver.
 */

#ifndef BRUSHLESS31_H
#define BRUSHLESS31_H

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
 * @addtogroup brushless31 Brushless 31 Click Driver
 * @brief API for configuring and manipulating Brushless 31 Click driver.
 * @{
 */

/**
 * @defgroup brushless31_cfg Brushless 31 PWM Settings
 * @brief Settings for configuration of Brushless 31 Click driver.
 */

/**
 * @addtogroup brushless31_cfg
 * @{
 */

/**
 * @brief Brushless 31 direction settings.
 * @details Specified setting for direction of Brushless 31 Click driver.
 */
#define BRUSHLESS31_DIR_CW          0
#define BRUSHLESS31_DIR_CCW         1

/**
 * @brief Brushless 31 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 31 Click driver.
 */
#define BRUSHLESS31_DEF_FREQ        20000

/*! @} */ // brushless31_cfg

/**
 * @defgroup brushless31_map Brushless 31 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 31 Click driver.
 */

/**
 * @addtogroup brushless31_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 31 Click to the selected MikroBUS.
 */
#define BRUSHLESS31_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.start = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.brake = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.hp = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // brushless31_map
/*! @} */ // brushless31

/**
 * @brief Brushless 31 Click context object.
 * @details Context object definition of Brushless 31 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t dir;      /**< Direction control pin (CW-LOW, CCW-HIGH). */
    digital_out_t start;    /**< Start pin (active high). */
    digital_out_t brake;    /**< Brake pin (active low). */

    // Input pins
    digital_in_t hp;        /**< Hall pulse monitor pin. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} brushless31_t;

/**
 * @brief Brushless 31 Click configuration object.
 * @details Configuration object definition of Brushless 31 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */

    // Additional gpio pins
    pin_name_t dir;         /**< Direction control pin (CW-LOW, CCW-HIGH). */
    pin_name_t start;       /**< Start pin (active high). */
    pin_name_t brake;       /**< Brake pin (active low). */
    pin_name_t hp;          /**< Hall pulse monitor pin. */

    // Static variable
    uint32_t dev_pwm_freq;  /**< PWM frequency value. */

} brushless31_cfg_t;

/**
 * @brief Brushless 31 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS31_OK = 0,
    BRUSHLESS31_ERROR = -1

} brushless31_return_value_t;

/*!
 * @addtogroup brushless31 Brushless 31 Click Driver
 * @brief API for configuring and manipulating Brushless 31 Click driver.
 * @{
 */

/**
 * @brief Brushless 31 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless31_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless31_cfg_setup ( brushless31_cfg_t *cfg );

/**
 * @brief Brushless 31 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless31_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless31_init ( brushless31_t *ctx, brushless31_cfg_t *cfg );

/**
 * @brief Brushless 31 default configuration function.
 * @details This function executes a default configuration of Brushless 31
 * click board.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t brushless31_default_cfg ( brushless31_t *ctx );

/**
 * @brief Brushless 31 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless31_set_duty_cycle ( brushless31_t *ctx, float duty_cycle );

/**
 * @brief Brushless 31 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless31_pwm_stop ( brushless31_t *ctx );

/**
 * @brief Brushless 31 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless31_pwm_start ( brushless31_t *ctx );

/**
 * @brief Brushless 31 set direction function.
 * @details This function sets the direction of motor rotation by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - CW,
 *                  @li @c 1 - CCW.
 * @return None.
 * @note None.
 */
void brushless31_set_direction ( brushless31_t *ctx, uint8_t dir );

/**
 * @brief Brushless 31 switch direction function.
 * @details This function switches the direction of motor rotation by toggling the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless31_switch_direction ( brushless31_t *ctx );

/**
 * @brief Brushless 31 pull brake function.
 * @details This function pulls brake by setting the BRAKE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless31_pull_brake ( brushless31_t *ctx );

/**
 * @brief Brushless 31 release brake function.
 * @details This function releases brake by setting the BRAKE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless31_release_brake ( brushless31_t *ctx );

/**
 * @brief Brushless 31 start function.
 * @details This function starts motor by setting the START pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless31_start ( brushless31_t *ctx );

/**
 * @brief Brushless 31 stop function.
 * @details This function stops motor by setting the START pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void brushless31_stop ( brushless31_t *ctx );

/**
 * @brief Brushless 31 get hp pin function.
 * @details This function returns the hall pulse monitor pin logic state.
 * @param[in] ctx : Click context object.
 * See #brushless31_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t brushless31_get_hp_pin ( brushless31_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS31_H

/*! @} */ // brushless31

// ------------------------------------------------------------------------ END
