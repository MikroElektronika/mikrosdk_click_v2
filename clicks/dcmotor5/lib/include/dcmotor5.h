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
 * @file dcmotor5.h
 * @brief This file contains API for DC Motor 5 Click Driver.
 */

#ifndef DCMOTOR5_H
#define DCMOTOR5_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup dcmotor5 DC Motor 5 Click Driver
 * @brief API for configuring and manipulating DC Motor 5 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor5_cfg DC Motor 5 PWM Settings
 * @brief Settings for configuration of DC Motor 5 Click driver.
 */

/**
 * @addtogroup dcmotor5_cfg
 * @{
 */

/**
 * @brief DC Motor 5 default PWM frequency.
 * @details Specified setting for default PWM frequency of DC Motor 5 Click driver.
 */
#define DCMOTOR5_DEF_FREQ     20000

/*! @} */ // dcmotor5_cfg

/**
 * @defgroup dcmotor5_map DC Motor 5 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 5 Click driver.
 */

/**
 * @addtogroup dcmotor5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 5 Click to the selected MikroBUS.
 */
#define DCMOTOR5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.snso = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in2 = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // dcmotor5_map
/*! @} */ // dcmotor5

/**
 * @brief DC Motor 5 Click context object.
 * @details Context object definition of DC Motor 5 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t sleep;            /**< Device sleep mode */
    digital_out_t in2;              /**< Input signal 2 */

    // Input pins
    digital_in_t snso;              /**< Sense comparator output */
    digital_in_t fault;             /**< Fault indication pin */

    // Modules
    pwm_t pwm;                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;              /**< PWM frequency value. */

} dcmotor5_t;

/**
 * @brief DC Motor 5 Click configuration object.
 * @details Configuration object definition of DC Motor 5 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;          /**< Input signal 1 */

    // Additional gpio pins
    pin_name_t snso;         /**< Sense comparator output. */
    pin_name_t sleep;        /**< Device sleep mode. */
    pin_name_t fault;        /**< Fault indication pin */
    pin_name_t in2;          /**< Input signal 2. */

    // Static variable
    uint32_t dev_pwm_freq;   /**< PWM frequency value. */

} dcmotor5_cfg_t;

/**
 * @brief DC Motor 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR5_OK = 0,
    DCMOTOR5_ERROR = -1

} dcmotor5_return_value_t;

/*!
 * @addtogroup dcmotor5 DC Motor 5 Click Driver
 * @brief API for configuring and manipulating DC Motor 5 Click driver.
 * @{
 */

/**
 * @brief DC Motor 5 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor5_cfg_setup ( dcmotor5_cfg_t *cfg );

/**
 * @brief DC Motor 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
err_t dcmotor5_init ( dcmotor5_t *ctx, dcmotor5_cfg_t *cfg );

/**
 * @brief DC Motor 5 default configuration function.
 * @details This function executes a default configuration of DC Motor 5
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void dcmotor5_default_cfg ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return Nothing.
 */
void dcmotor5_set_duty_cycle ( dcmotor5_t *ctx, float duty_cycle );

/**
 * @brief DC Motor 5 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor5_pwm_stop ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor5_pwm_start ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor5_enable ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 Disable the engine function.
 * @details Function disables the engine by clearing SLEEP ( RST ) pin on DC 
 * Motor 5 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor5_standby ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 Set the direction of rotation in the counter clockwise direction function.
 * @details Function sets the direction of rotation in the counter clockwise direction
 * by clearing IN1 ( PWM ) pin and seting IN2 ( INT ) pin on DC Motor 5 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing
 **/
void dcmotor5_counter_clockwise ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 Set the direction of rotation in the clockwise direction function.
 * @details Function sets the direction of rotation in the clockwise direction
 * by setting IN1 ( PWM ) pin and claering IN2 ( INT ) pin on DC Motor 5 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing
 **/
void dcmotor5_clockwise ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 brake the engine function.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing
 **/
void dcmotor5_short_brake ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 stop the engine function.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return Nothing
 **/
void dcmotor5_stop ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 get fault conditions state function.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return State of the FAULT pin
 **/
uint8_t dcmotor5_get_fault_conditions ( dcmotor5_t *ctx );

/**
 * @brief DC Motor 5 get sense comparator.
 * @details This function returns sense comparator state, 
 * state of AN pin on DC Motor 5 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor5_t object definition for detailed explanation.
 * @return State of the SNSO pin.
 */
uint8_t dcmotor5_get_sense_comparator ( dcmotor5_t *ctx );


#ifdef __cplusplus
}
#endif
#endif // DCMOTOR5_H

/*! @} */ // dcmotor5

// ------------------------------------------------------------------------ END
