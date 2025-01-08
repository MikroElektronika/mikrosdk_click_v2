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
 * @file brushless18.h
 * @brief This file contains API for Brushless 18 Click Driver.
 */

#ifndef BRUSHLESS18_H
#define BRUSHLESS18_H

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
 * @addtogroup brushless18 Brushless 18 Click Driver
 * @brief API for configuring and manipulating Brushless 18 Click driver.
 * @{
 */

/**
 * @defgroup brushless18_cfg Brushless 18 PWM Settings
 * @brief Settings for configuration of Brushless 18 Click driver.
 */

/**
 * @addtogroup brushless18_cfg
 * @{
 */

/**
 * @brief Brushless 18 default PWM frequency.
 * @details Specified setting for default PWM frequency of Brushless 18 Click driver.
 */
#define BRUSHLESS18_DEF_FREQ            400

/**
 * @brief Brushless 18 duty cycle settings.
 * @details Specified setting for duty cycle of Brushless 18 Click driver.
 */
#define BRUSHLESS18_DC_ZERO             0.0
#define BRUSHLESS18_DC_1MS              ( BRUSHLESS18_DEF_FREQ / 1000.0 )
#define BRUSHLESS18_DC_MIN_THROTTLE     ( BRUSHLESS18_DC_1MS * 1.064 )
#define BRUSHLESS18_DC_IDLE             ( BRUSHLESS18_DC_1MS * 1.464 )
#define BRUSHLESS18_DC_MAX_THROTTLE     ( BRUSHLESS18_DC_1MS * 1.864 )
#define BRUSHLESS18_DC_1_PCT            ( ( BRUSHLESS18_DC_MAX_THROTTLE - BRUSHLESS18_DC_IDLE ) / 100.0 )

/**
 * @brief Brushless 18 speed and direction settings.
 * @details Specified setting for speed and direction of Brushless 18 Click driver.
 */
#define BRUSHLESS18_SPEED_MIN           0
#define BRUSHLESS18_SPEED_MAX           100
#define BRUSHLESS18_DIRECTION_CW        0
#define BRUSHLESS18_DIRECTION_CCW       1

/*! @} */ // brushless18_cfg

/**
 * @defgroup brushless18_map Brushless 18 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 18 Click driver.
 */

/**
 * @addtogroup brushless18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 18 Click to the selected MikroBUS.
 */
#define BRUSHLESS18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // brushless18_map
/*! @} */ // brushless18

/**
 * @brief Brushless 18 Click context object.
 * @details Context object definition of Brushless 18 Click driver.
 */
typedef struct
{
    // Modules
    pwm_t pwm;                          /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;                  /**< PWM frequency value. */

} brushless18_t;

/**
 * @brief Brushless 18 Click configuration object.
 * @details Configuration object definition of Brushless 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                     /**< PWM pin. */

    // Static variable
    uint32_t dev_pwm_freq;              /**< PWM frequency value. */

} brushless18_cfg_t;

/**
 * @brief Brushless 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BRUSHLESS18_OK = 0,
    BRUSHLESS18_ERROR = -1

} brushless18_return_value_t;

/*!
 * @addtogroup brushless18 Brushless 18 Click Driver
 * @brief API for configuring and manipulating Brushless 18 Click driver.
 * @{
 */

/**
 * @brief Brushless 18 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless18_cfg_setup ( brushless18_cfg_t *cfg );

/**
 * @brief Brushless 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless18_init ( brushless18_t *ctx, brushless18_cfg_t *cfg );

/**
 * @brief Brushless 18 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless18_set_duty_cycle ( brushless18_t *ctx, float duty_cycle );

/**
 * @brief Brushless 18 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless18_pwm_stop ( brushless18_t *ctx );

/**
 * @brief Brushless 18 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless18_pwm_start ( brushless18_t *ctx );

/**
 * @brief Brushless 18 throttle calib module.
 * @details This function performs the ESC throttle calibration.
 * @param[in] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note The calibration process takes about 10 seconds.
 */
err_t brushless18_throttle_calib ( brushless18_t *ctx );

/**
 * @brief Brushless 18 drive motor module.
 * @details This function drives the motor at the selected speed and direction.
 * @param[in] ctx : Click context object.
 * See #brushless18_t object definition for detailed explanation.
 * @param[in] direction : @li @c 0 - Clockwise,
 *                        @li @c 1 - Counter-Clockwise.
 * @param[in] speed : Speed percents [0-100].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless18_drive_motor ( brushless18_t *ctx, uint8_t direction, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS18_H

/*! @} */ // brushless18

// ------------------------------------------------------------------------ END
