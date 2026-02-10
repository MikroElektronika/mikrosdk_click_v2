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
 * @file boost12.h
 * @brief This file contains API for Boost 12 Click Driver.
 */

#ifndef BOOST12_H
#define BOOST12_H

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
 * @addtogroup boost12 Boost 12 Click Driver
 * @brief API for configuring and manipulating Boost 12 Click driver.
 * @{
 */

/**
 * @defgroup boost12_cfg Boost 12 PWM Settings
 * @brief Settings for configuration of Boost 12 Click driver.
 */

/**
 * @addtogroup boost12_cfg
 * @{
 */

/**
 * @brief Boost 12 default PWM frequency and duty cycle.
 * @details Specified setting for default PWM frequency and duty cycle of Boost 12 Click driver.
 */
#define BOOST12_DEF_PWM_FREQ        5000
#define BOOST12_DEF_PWM_DC          0.0

/*! @} */ // boost12_cfg

/**
 * @defgroup boost12_map Boost 12 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 12 Click driver.
 */

/**
 * @addtogroup boost12_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 12 Click to the selected MikroBUS.
 */
#define BOOST12_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // boost12_map
/*! @} */ // boost12

/**
 * @brief Boost 12 Click context object.
 * @details Context object definition of Boost 12 Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;          /**< PWM frequency value. */

} boost12_t;

/**
 * @brief Boost 12 Click configuration object.
 * @details Configuration object definition of Boost 12 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;             /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;      /**< PWM frequency value. */

} boost12_cfg_t;

/**
 * @brief Boost 12 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST12_OK = 0,
    BOOST12_ERROR = -1

} boost12_return_value_t;

/*!
 * @addtogroup boost12 Boost 12 Click Driver
 * @brief API for configuring and manipulating Boost 12 Click driver.
 * @{
 */

/**
 * @brief Boost 12 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost12_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost12_cfg_setup ( boost12_cfg_t *cfg );

/**
 * @brief Boost 12 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #boost12_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost12_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost12_init ( boost12_t *ctx, boost12_cfg_t *cfg );

/**
 * @brief Boost 12 default configuration function.
 * @details This function executes a default configuration of Boost 12
 * Click board.
 * @param[in] ctx : Click context object.
 * See #boost12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t boost12_default_cfg ( boost12_t *ctx );

/**
 * @brief Boost 12 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #boost12_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost12_set_duty_cycle ( boost12_t *ctx, float duty_cycle );

/**
 * @brief Boost 12 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #boost12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost12_pwm_stop ( boost12_t *ctx );

/**
 * @brief Boost 12 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #boost12_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost12_pwm_start ( boost12_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BOOST12_H

/*! @} */ // boost12

// ------------------------------------------------------------------------ END
