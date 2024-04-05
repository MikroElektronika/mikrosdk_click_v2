/****************************************************************************
** Copyright (C) 2021 MikroElektronika d.o.o.
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
 * @file driver2.h
 * @brief This file contains API for Driver 2 Click Driver.
 */

#ifndef DRIVER2_H
#define DRIVER2_H

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
 * @addtogroup driver2 Driver 2 Click Driver
 * @brief API for configuring and manipulating Driver 2 Click driver.
 * @{
 */

/**
 * @defgroup driver2_set Driver 2 PWM Settings
 * @brief Settings for configuration of Driver 2 Click driver.
 */

/**
 * @addtogroup driver2_cfg
 * @{
 */

/**
 * @brief Driver 2 pin state.
 * @details Specified setting for pin state of Driver 2 Click driver.
 */
#define DRIVER2_PIN_ENABLE         0x01
#define DRIVER2_PIN_DISABLE        0x00

/**
 * @brief Driver 2 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of Driver 2 Click driver.
 */
#define DRIVER2_DEF_FREQ           5000

/*! @} */ // driver2_cfg

/**
 * @defgroup driver2_map Driver 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Driver 2 Click driver.
 */

/**
 * @addtogroup driver2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Driver 2 Click to the selected MikroBUS.
 */
#define DRIVER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sd = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fb = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // driver2_map
/*! @} */ // driver2

/**
 * @brief Driver 2 Click driver selector.
 * @details Selects target driver interface of Driver 2 Click driver.
 */

/**
 * @brief Driver 2 Click context object.
 * @details Context object definition of Driver 2 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sd;       /**< Shutdown. */

    // Input pins
    digital_in_t fb;        /**< Feedback. */

    // Modules
    pwm_t pwm;                                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                              /**< PWM frequency value. */

} driver2_t;

/**
 * @brief Driver 2 Click configuration object.
 * @details Configuration object definition of Driver 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                                 /**< PWM pin. */

    // Additional gpio pins
    pin_name_t sd;      /**< Shutdown. */
    pin_name_t fb;      /**< Feedback. */

    // Static variable
    uint32_t dev_pwm_freq;                          /**< PWM frequency value. */

} driver2_cfg_t;

/**
 * @brief Driver 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DRIVER2_OK = 0,
   DRIVER2_ERROR = -1

} driver2_return_value_t;

/*!
 * @addtogroup driver2 Driver 2 Click Driver
 * @brief API for configuring and manipulating Driver 2 Click driver.
 * @{
 */

/**
 * @brief Driver 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #driver2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void driver2_cfg_setup ( driver2_cfg_t *cfg );

/**
 * @brief Driver 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #driver2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t driver2_init ( driver2_t *ctx, driver2_cfg_t *cfg );

/**
 * @brief Driver 2 default configuration function.
 * @details This function executes a default configuration of Driver 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t driver2_default_cfg ( driver2_t *ctx );

/**
 * @brief Driver 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t driver2_set_duty_cycle ( driver2_t *ctx, float duty_cycle );

/**
 * @brief Driver 2 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t driver2_pwm_stop ( driver2_t *ctx );

/**
 * @brief Driver 2 start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t driver2_pwm_start ( driver2_t *ctx );

/**
 * @brief Set SD pin.
 * @details This function sets state of the SD pin.
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @param[in] state : State of pin.
 * @return Nothing.
 */
void driver2_set_sd_pin ( driver2_t *ctx, uint8_t state );

/**
 * @brief Set PWM pin.
 * @details This function sets state of the PWM pin.
 * @param[out] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @param[in] state : State of pin.
 * @return Nothing.
 */
void driver2_set_pwm_pin ( driver2_t *ctx, uint8_t state );

/**
 * @brief Get FB pin
 * @details This function is reading state of the FB pin.
 * @param[in] ctx : Click context object.
 * See #driver2_t object definition for detailed explanation.
 * @return State of pin
 */
uint8_t driver2_get_fb_pin ( driver2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // DRIVER2_H

/*! @} */ // driver2

// ------------------------------------------------------------------------ END
