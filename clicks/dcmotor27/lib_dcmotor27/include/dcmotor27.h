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
 * @file dcmotor27.h
 * @brief This file contains API for DC Motor 27 Click Driver.
 */

#ifndef DCMOTOR27_H
#define DCMOTOR27_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_pwm.h"

/*!
 * @addtogroup dcmotor27 DC Motor 27 Click Driver
 * @brief API for configuring and manipulating DC Motor 27 Click driver.
 * @{
 */

/**
 * @defgroup dcmotor27_cfg DC Motor 27 PWM Settings
 * @brief Settings for configuration of DC Motor 27 Click driver.
 */

/**
 * @addtogroup dcmotor27_cfg
 * @{
 */

/**
 * @brief DC Motor 27 default PWM frequency.
 * @details Specified setting for default PWM frequency of DC Motor 27 Click driver.
 */
#define DCMOTOR27_DEF_FREQ          5000

/**
 * @brief DC Motor 27 pin mode settings.
 * @details Specified setting for pin state of DC Motor 27 Click driver.
 */
#define DCMOTOR27_SET_PIN_HIGH      0x01
#define DCMOTOR27_SET_PIN_LOW       0x00

/**
 * @brief DC Motor 27 coast mode settings.
 * @details Specified setting for coast state of DC Motor 27 Click driver.
 */
#define DCMOTOR27_SET_COAST_ON      0x01
#define DCMOTOR27_SET_COAST_OFF     0x00

/*! @} */ // dcmotor27_cfg

/**
 * @defgroup dcmotor27_map DC Motor 27 MikroBUS Map
 * @brief MikroBUS pin mapping of DC Motor 27 Click driver.
 */

/**
 * @addtogroup dcmotor27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of DC Motor 27 Click to the selected MikroBUS.
 */
#define DCMOTOR27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.ip = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.cs = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.flt = MIKROBUS( mikrobus, MIKROBUS_INT );

/*! @} */ // dcmotor27_map
/*! @} */ // dcmotor27

/**
 * @brief DC Motor 27 Click context object.
 * @details Context object definition of DC Motor 27 Click driver.
 */
typedef struct
{
    // Output pins
    digital_out_t rst;              /**< Reset pin. */
    digital_out_t cs;               /**< Drive off pin. */

    // Input pins
    digital_in_t ip;                /**< Driver load current analog feedback. */
    digital_in_t flt;               /**< Fault indication pin. */

    // Modules
    pwm_t pwm;                      /**< PWM driver object. */

    // ctx variable
    uint32_t pwm_freq;              /**< PWM frequency value. */

} dcmotor27_t;

/**
 * @brief DC Motor 27 Click configuration object.
 * @details Configuration object definition of DC Motor 27 Click driver.
 */
typedef struct
{
    // Communication gpio pins
    pin_name_t pwm;                 /**< PWM pin. */

    // Additional gpio pins
    pin_name_t ip;                  /**< Driver load current analog feedback. */
    pin_name_t rst;                 /**< Reset pin. */
    pin_name_t cs;                  /**< Drive off pin. */
    pin_name_t flt;                 /**< Fault indication pin. */

    // Static variable
    uint32_t dev_pwm_freq;          /**< PWM frequency value. */

} dcmotor27_cfg_t;

/**
 * @brief DC Motor 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    DCMOTOR27_OK = 0,
    DCMOTOR27_ERROR = -1

} dcmotor27_return_value_t;

/*!
 * @addtogroup dcmotor27 DC Motor 27 Click Driver
 * @brief API for configuring and manipulating DC Motor 27 Click driver.
 * @{
 */

/**
 * @brief DC Motor 27 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #dcmotor27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void dcmotor27_cfg_setup ( dcmotor27_cfg_t *cfg );

/**
 * @brief DC Motor 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #dcmotor27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor27_init ( dcmotor27_t *ctx, dcmotor27_cfg_t *cfg );

/**
 * @brief DC Motor 27 default configuration function.
 * @details This function executes a default configuration of DC Motor 27
 * click board.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t dcmotor27_default_cfg ( dcmotor27_t *ctx );

/**
 * @brief DC Motor 27 sets PWM duty cycle.
 * @details This function sets the PWM duty cycle in percentages ( Range[ 0..1 ] ).
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @param[in] duty_cycle : PWM duty cycle.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor27_set_duty_cycle ( dcmotor27_t *ctx, float duty_cycle );

/**
 * @brief DC Motor 27 stop PWM module.
 * @details This function stops the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor27_pwm_stop ( dcmotor27_t *ctx );

/**
 * @brief DC Motor 27 start PWM module.
 * @details This function starts the PWM module output.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t dcmotor27_pwm_start ( dcmotor27_t *ctx );

/**
 * @brief DC Motor 27 get flt pin state.
 * @details This function reads flt pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @return Flt pin state.
 * @note None.
 */
uint8_t dcmotor27_get_flt_pin ( dcmotor27_t *ctx );

/**
 * @brief DC Motor 27 get ip pin state.
 * @details This function reads ip pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @return Flt pin state.
 * @note None.
 */
uint8_t dcmotor27_get_ip_pin ( dcmotor27_t *ctx );

/**
 * @brief DC Motor 27 set RST pin state.
 * @details This function is used to set RST pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @param[in] pin_state : State of the pin.
 * @return Nothing.
 * @note None
 */
void dcmotor27_set_rst_pin ( dcmotor27_t *ctx, uint8_t pin_state );

/**
 * @brief DC Motor 27 set CS pin state.
 * @details This function is used to set CS pin state.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @param[in] pin_state : State of the pin.
 * @return Nothing.
 * @note None
 */
void dcmotor27_set_cs_pin ( dcmotor27_t *ctx, uint8_t pin_state );

/**
 * @brief DC Motor 27 set coast mode funtion.
 * @details This function is used to set motor to coast mode.
 * @param[in] ctx : Click context object.
 * See #dcmotor27_t object definition for detailed explanation.
 * @param[in] coast_state : Coast state.
 * @return Nothing.
 * @note None.
 */
void dcmotor27_set_coast ( dcmotor27_t *ctx, uint8_t coast_state );

#ifdef __cplusplus
}
#endif
#endif // DCMOTOR27_H

/*! @} */ // dcmotor27

// ------------------------------------------------------------------------ END
