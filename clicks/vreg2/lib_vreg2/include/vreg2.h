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
 * @file vreg2.h
 * @brief This file contains API for VREG 2 Click Driver.
 */

#ifndef VREG2_H
#define VREG2_H

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
 * @addtogroup vreg2 VREG 2 Click Driver
 * @brief API for configuring and manipulating VREG 2 Click driver.
 * @{
 */

/**
 * @defgroup vreg2_cfg VREG 2 PWM Settings
 * @brief Settings for configuration of VREG 2 Click driver.
 */

/**
 * @addtogroup vreg2_cfg
 * @{
 */

/**
 * @brief VREG 2 default PWM frequency.
 * @details Specified setting for default PWM frequency of VREG 2 Click driver.
 */
#define VREG2_DEF_FREQ      5000

/*! @} */ // vreg2_cfg

/**
 * @defgroup vreg2_map VREG 2 MikroBUS Map
 * @brief MikroBUS pin mapping of VREG 2 Click driver.
 */

/**
 * @addtogroup vreg2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of VREG 2 Click to the selected MikroBUS.
 */
#define VREG2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // vreg2_map
/*! @} */ // vreg2

/**
 * @brief VREG 2 Click context object.
 * @details Context object definition of VREG 2 Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                                  /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                          /**< PWM frequency value. */

} vreg2_t;

/**
 * @brief VREG 2 Click configuration object.
 * @details Configuration object definition of VREG 2 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                             /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;                      /**< PWM frequency value. */

} vreg2_cfg_t;

/**
 * @brief VREG 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    VREG2_OK = 0,
    VREG2_ERROR = -1

} vreg2_return_value_t;

/*!
 * @addtogroup vreg2 VREG 2 Click Driver
 * @brief API for configuring and manipulating VREG 2 Click driver.
 * @{
 */

/**
 * @brief VREG 2 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #vreg2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void vreg2_cfg_setup ( vreg2_cfg_t *cfg );

/**
 * @brief VREG 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #vreg2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #vreg2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vreg2_init ( vreg2_t *ctx, vreg2_cfg_t *cfg );

/**
 * @brief VREG 2 default configuration function.
 * @details This function executes a default configuration of VREG 2
 * Click board.
 * @param[in] ctx : Click context object.
 * See #vreg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t vreg2_default_cfg ( vreg2_t *ctx );

/**
 * @brief VREG 2 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #vreg2_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vreg2_set_duty_cycle ( vreg2_t *ctx, float duty_cycle );

/**
 * @brief VREG 2 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #vreg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vreg2_pwm_stop ( vreg2_t *ctx );

/**
 * @brief VREG 2 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #vreg2_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t vreg2_pwm_start ( vreg2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // VREG2_H

/*! @} */ // vreg2

// ------------------------------------------------------------------------ END
