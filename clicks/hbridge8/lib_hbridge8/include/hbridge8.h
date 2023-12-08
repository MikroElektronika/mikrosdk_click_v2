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
 * @file hbridge8.h
 * @brief This file contains API for H-Bridge 8 Click Driver.
 */

#ifndef HBRIDGE8_H
#define HBRIDGE8_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup hbridge8 H-Bridge 8 Click Driver
 * @brief API for configuring and manipulating H-Bridge 8 Click driver.
 * @{
 */


/**
 * @addtogroup mode
 * @{
 */

/**
 * @brief H-Bridge 8 Current polarity setting.
 * @details Specified setting for Current polarity setting of H-Bridge 8 Click driver.
 */
#define HBRIDGE8_MODE_REVERSE      0
#define HBRIDGE8_MODE_FORWARD      1

/*! @} */ // mode

/**
 * @defgroup hbridge8_set H-Bridge 8 PWM Settings
 * @brief Settings for configuration of H-Bridge 8 Click driver.
 */

/**
 * @addtogroup hbridge8_cfg
 * @{
 */

/**
 * @brief H-Bridge 8 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of H-Bridge 8 Click driver.
 */
#define HBRIDGE8_DEF_FREQ     225000

/*! @} */ // hbridge8_cfg

/**
 * @defgroup hbridge8_map H-Bridge 8 MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge 8 Click driver.
 */

/**
 * @addtogroup hbridge8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge 8 Click to the selected MikroBUS.
 */
#define HBRIDGE8_MAP_MIKROBUS( cfg, mikrobus )    \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_RST );  \
    cfg.mod = MIKROBUS( mikrobus, MIKROBUS_CS );  \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // hbridge8_map
/*! @} */ // hbridge8

/**
 * @brief H-Bridge 8 Click driver selector.
 * @details Selects target driver interface of H-Bridge 8 Click driver.
 */

/**
 * @brief H-Bridge 8 Click context object.
 * @details Context object definition of H-Bridge 8 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t en;     /**< IC enable pin. */
    digital_out_t mod;    /**< Current polarity mode pin. */

    // Input pins
    digital_in_t flt;     /**< Fault indication pin. */

    // Modules
    pwm_t pwm;            /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;    /**< PWM frequency value. */

} hbridge8_t;

/**
 * @brief H-Bridge 8 Click configuration object.
 * @details Configuration object definition of H-Bridge 8 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;           /**< PWM pin. */

    // Additional gpio pins
    pin_name_t en;           /**< IC enable pin. */
    pin_name_t mod;          /**< Current polarity mode pin. */
    pin_name_t flt;          /**< Fault indication pin. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} hbridge8_cfg_t;

/**
 * @brief H-Bridge 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   HBRIDGE8_OK = 0,
   HBRIDGE8_ERROR = -1

} hbridge8_return_value_t;

/*!
 * @addtogroup hbridge8 H-Bridge 8 Click Driver
 * @brief API for configuring and manipulating H-Bridge 8 Click driver.
 * @{
 */

/**
 * @brief H-Bridge 8 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge8_cfg_setup ( hbridge8_cfg_t *cfg );

/**
 * @brief H-Bridge 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_init ( hbridge8_t *ctx, hbridge8_cfg_t *cfg );

/**
 * @brief H-Bridge 8 default configuration function.
 * @details This function executes a default configuration of H-Bridge 8
 * click board.
 * @param[in] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t hbridge8_default_cfg ( hbridge8_t *ctx );

/**
 * @brief H-Bridge 8 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_set_duty_cycle ( hbridge8_t *ctx, float duty_cycle );

/**
 * @brief H-Bridge 8 stop PWM module.
 * @details This function stops the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_pwm_stop ( hbridge8_t *ctx );

/**
 * @brief H-Bridge 8 start PWM module.
 * @details This function starts the PWM moudle output.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_pwm_start ( hbridge8_t *ctx );

/**
 * @brief H-Bridge 8 set operating mode function.
 * @details This function sets the desired operating mode 
 * of the H-Bridge 8 click board™.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 *            @li @c 0 ( HBRIDGE8_MODE_REVERSE ) - Drive the motor reverse,
 *            @li @c 1 ( HBRIDGE8_MODE_FORWARD ) - Drive the motor forward.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_set_mode ( hbridge8_t *ctx, uint8_t mode );

/**
 * @brief H-Bridge 8 set IC enable function.
 * @details This function sets the IC enable 
 * of the H-Bridge 8 click board™.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_enable ( hbridge8_t *ctx );

/**
 * @brief H-Bridge 8 set IC disable function.
 * @details This function sets the IC disable 
 * of the H-Bridge 8 click board™.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge8_disable ( hbridge8_t *ctx );

/**
 * @brief H-Bridge 8 get fault indication function.
 * @details This function get fault indication
 * of the H-Bridge 8 click board™.
 * @param[out] ctx : Click context object.
 * See #hbridge8_t object definition for detailed explanation.
 * @return @li @c 0 - Fault conditions,
 *         @li @c 1 - Normal conditions.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint8_t hbridge8_get_fault_indication ( hbridge8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE8_H

/*! @} */ // hbridge8

// ------------------------------------------------------------------------ END
