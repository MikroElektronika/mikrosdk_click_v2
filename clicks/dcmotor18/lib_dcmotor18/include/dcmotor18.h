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
 * @file dcmotor18.h
 * @brief This file contains API for DC Motor 18 Click Driver.
 */

#ifndef DCMOTOR18_H
#define DCMOTOR18_H

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
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor18 DC Motor 18 Click Driver
 * @brief API for configuring and manipulating DC Motor 18 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor18_set DC Motor 18 PWM Settings
 * @brief Settings for configuration of DC Motor 18 Click driver.
 */

/**
 * @addtogroup dcmotor18_cfg
 * @{
 */

/**
 * @brief DC Motor 18 default PWM frequency.
 * @details Specified setting for setting default PWM frequency of DC Motor 18 Click driver.
 */
#define DCMOTOR18_DEF_FREQ     5000

/*! @} */ // dcmotor18_cfg

/**
 * @defgroup dcmotor18_map DC Motor 18 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 18 Click driver.
 */

/**
 * @addtogroup dcmotor18_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 18 Click to the selected MikroBUS.
 */
#define DCMOTOR18_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pw2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // dcmotor18_map
/*! @} */ // dcmotor18

/**
 * @brief DC Motor 18 Click driver selector.
 * @details Selects target driver interface of DC Motor 18 Click driver.
 */

/**
 * @brief DC Motor 18 Click context object.
 * @details Context object definition of DC Motor 18 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t pw2;      /**< PWM 2. */
    digital_out_t en;       /**< Enable. */

    // Input pins
    digital_in_t int_pin;   /**< Interrupt. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */
    analog_in_t  adc;       /**< ADC module object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */
    uint8_t direction;      /**< Description. */

} dcmotor18_t;

/**
 * @brief DC Motor 18 Click configuration object.
 * @details Configuration object definition of DC Motor 18 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;     /**< PWM pin. */
    pin_name_t  an;     /**< Analog pin descriptor. */

    // Additional gpio pins
    pin_name_t pw2;     /**< PWM 2. */
    pin_name_t en;      /**< Enable. */
    pin_name_t int_pin; /**< Interrupt. */

    // Static variable
    uint32_t dev_pwm_freq;              /**< PWM frequency value. */
    analog_in_resolution_t  resolution; /**< ADC resolution. */
    float                   vref;       /**< ADC reference voltage. */

} dcmotor18_cfg_t;

/**
 * @brief DC Motor 18 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   DCMOTOR18_OK = 0,
   DCMOTOR18_ERROR = -1

} dcmotor18_return_value_t;

/*!
 * @addtogroup dcmotor18 DC Motor 18 Click Driver
 * @brief API for configuring and manipulating DC Motor 18 Click driver.
 * @{
 */

/**
 * @brief DC Motor 18 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor18_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor18_cfg_setup ( dcmotor18_cfg_t *cfg );

/**
 * @brief DC Motor 18 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor18_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_init ( dcmotor18_t *ctx, dcmotor18_cfg_t *cfg );

/**
 * @brief DC Motor 18 default configuration function.
 * @details This function executes a default configuration of DC Motor 18
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor18_default_cfg ( dcmotor18_t *ctx );

/**
 * @brief Sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[in] duty_ratio : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_set_duty_cycle ( dcmotor18_t *ctx, float duty_cycle );

/**
 * @brief DC Motor 18 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_pwm_stop ( dcmotor18_t *ctx );

/**
 * @brief DC Motor 18 start PWM module.
 * @details This function starts the PWM module output.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_pwm_start ( dcmotor18_t *ctx );

/**
 * @brief DC Motor 18 read AN pin value function.
 * @details This function reads results of AD conversion of the AN pin.
 * @param[in] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[out] data_out : Output ADC result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_read_an_pin_value ( dcmotor18_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 18 read AN pin voltage level function.
 * @details This function reads results of AD conversion of the AN pin and
 * converts them to proportional voltage level.
 * @param[in] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[out] data_out : Output voltage level of the analog pin [V].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note The conversion to voltage depends on the entered configuration of the
 * ADC (resolution, reference voltage).
 */
err_t dcmotor18_read_an_pin_voltage ( dcmotor18_t *ctx, float *data_out );

/**
 * @brief Read AN pin current.
 * @details This function reads voltage of AN pin and
 * calculates current.
 * @param[in] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[out] data_out : Output current of the analog pin [mA].
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_read_an_pin_current ( dcmotor18_t *ctx, float *data_out );

/**
 * @brief Set diretion of motor rotation.
 * @details This function sets the @b pw2 pin state.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[in] state : State of the pin.
 * @return Nothing.
 */
void dcmotor18_set_direction ( dcmotor18_t *ctx, uint8_t state );

/**
 * @brief Set enable pin state.
 * @details This function sets the @b en pin state.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[in] state : State of the pin.
 * @return Nothing.
 */
void dcmotor18_set_enable ( dcmotor18_t *ctx, uint8_t state );

/**
 * @brief Get interrupt pin state.
 * @details This function reads the @b int_pin pin state.
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @return Interrupt pin state.
 */
uint8_t dcmotor18_get_interrupt ( dcmotor18_t *ctx );

/**
 * @brief Set speed output percentage.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[out] ctx : Click context object.
 * See #dcmotor18_t object definition for detailed explanation.
 * @param[in] speed_percentage : PWM duty_ratio.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor18_set_speed_percentage ( dcmotor18_t *ctx, float speed_percentage );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR18_H

/*! @} */ // dcmotor18

// ------------------------------------------------------------------------ END
