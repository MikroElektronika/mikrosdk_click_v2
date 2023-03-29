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
 * @file dcmotor9.h
 * @brief This file contains API for DC Motor 9 Click Driver.
 */

#ifndef DCMOTOR9_H
#define DCMOTOR9_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"
#include "drv_analog_in.h"

/*!
 * @addtogroup dcmotor9 DC Motor 9 Click Driver
 * @brief API for configuring and manipulating DC Motor 9 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor9_cfg DC Motor 9 PWM Settings
 * @brief Settings for configuration of DC Motor 9 Click driver.
 */

/**
 * @addtogroup dcmotor9_cfg
 * @{
 */

/**
 * @brief DC Motor 9 default PWM frequency.
 * @details Specified setting for default PWM frequency of DC Motor 9 Click driver.
 */
#define DCMOTOR9_DEF_FREQ     20000
#define DCMOTOR9_DEF_VREF     3.3

/**
 * @brief DC Motor 9 PWM duty settings.
 * @details Specified setting for PWM duty cycle settings of DC Motor 9 Click driver.
 */
#define DCMOTOR9_PWM_DUTY_PERCENT_0   0.0
#define DCMOTOR9_PWM_DUTY_PERCENT_10  0.1
#define DCMOTOR9_PWM_DUTY_PERCENT_20  0.2
#define DCMOTOR9_PWM_DUTY_PERCENT_30  0.3
#define DCMOTOR9_PWM_DUTY_PERCENT_40  0.4
#define DCMOTOR9_PWM_DUTY_PERCENT_50  0.5
#define DCMOTOR9_PWM_DUTY_PERCENT_60  0.6
#define DCMOTOR9_PWM_DUTY_PERCENT_70  0.7
#define DCMOTOR9_PWM_DUTY_PERCENT_80  0.8
#define DCMOTOR9_PWM_DUTY_PERCENT_90  0.9
#define DCMOTOR9_PWM_DUTY_PERCENT_100 1.0

/*! @} */ // dcmotor9_cfg

/**
 * @defgroup dcmotor9_map DC Motor 9 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 9 Click driver.
 */

/**
 * @addtogroup dcmotor9_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 9 Click to the selected MikroBUS.
 */
#define DCMOTOR9_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.an = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.pw2 = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // dcmotor9_map
/*! @} */ // dcmotor9

/**
 * @brief DC Motor 9 Click context object.
 * @details Context object definition of DC Motor 9 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t shd;      /** Shutdown control pin. */
    digital_out_t pw2;      /** PWM control pin 2. */

    // Modules
    pwm_t pwm;              /**< PWM driver object. */
    
    analog_in_t  adc;       /**< ADC module object. */

    // ctx variable
    uint32_t pwm_freq;      /**< PWM frequency value. */

} dcmotor9_t;

/**
 * @brief DC Motor 9 Click configuration object.
 * @details Configuration object definition of DC Motor 9 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;         /**< PWM pin. */

    // Additional gpio pins
    pin_name_t an;         /** Analog state pin. */
    pin_name_t shd;        /** Shutdown control pin. */
    pin_name_t pw1;        /** PWM control pin 1. */
    pin_name_t pw2;        /** PWM control pin 2. */

    // Static variable
    uint32_t dev_pwm_freq;                 /**< PWM frequency value. */
    analog_in_resolution_t resolution;     /**< ADC resolution. */
    float vref;                            /**< ADC reference voltage. */
    
} dcmotor9_cfg_t;

/**
 * @brief DC Motor 9 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR9_OK = 0,
    DCMOTOR9_ERROR = -1

} dcmotor9_return_value_t;

/*!
 * @addtogroup dcmotor9 DC Motor 9 Click Driver
 * @brief API for configuring and manipulating DC Motor 9 Click driver.
 * @{
 */

/**
 * @brief DC Motor 9 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg );

/**
 * @brief DC Motor 9 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor9_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg );

/**
 * @brief DC Motor 9 default configuration function.
 * @details This function executes a default configuration of DC Motor 9
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor9_default_cfg ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #dcmotor9_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle );

/**
 * @brief DC Motor 9 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_pwm_stop ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_pwm_start ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Enable the engine function.
 * @details Function enables the engine by setting SHDN ( RST ) pin on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_enable ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Disable the engine function.
 * @details TFunction disables the engine by clearing SHDN ( RST ) pin on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_standby ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Set the counter clockwise direction of rotation function.
 * @details Function sets the counter clockwise direction of rotation
 * by clearing IN1 ( CS ) pin and seting IN2 ( PWM ) pin on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_counter_clockwise ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Set the clockwise direction of rotation function.
 * @details Function sets the clockwise direction of rotation
 * by setting IN1 ( CS ) pin and claering IN2 ( PWM ) pin on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_clockwise ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Brake the engine function.
 * @details Function brakes the engine by setting IN1 ( CS )
 * and IN2 ( PWM ) pins on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_short_brake ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 Stop the engine function.
 * @details Function stops the engine by clearing IN1 ( CS ) and IN2 ( PWM ) pins on DC Motor 9 Click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor9_cfg_t object definition for detailed explanation.
 * @return Nothing.
 */
void dcmotor9_stop ( dcmotor9_t *ctx );

/**
 * @brief DC Motor 9 AN Value Read function.
 * @details This function reads results of AD conversion on the AN pin.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : AN value.
 * See #dcmotor9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_read_an_value ( dcmotor9_t *ctx, uint16_t *data_out );

/**
 * @brief DC Motor 9 AN Voltage Read function.
 * @details This function reads results of AD conversion on the AN pin and calculates these results to voltage.
 * @param[in] ctx : Click context object.
 * @param[out] data_out : AN Voltage[V].
 * See #dcmotor9_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t dcmotor9_read_an_voltage ( dcmotor9_t *ctx, float *data_out );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR9_H

/*! @} */ // dcmotor9

// ------------------------------------------------------------------------ END
