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
 * @file stepper2.h
 * @brief This file contains API for Stepper 2 Click Driver.
 */

#ifndef STEPPER2_H
#define STEPPER2_H

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

/*!
 * @addtogroup stepper2 Stepper 2 Click Driver
 * @brief API for configuring and manipulating Stepper 2 Click driver.
 * @{
 */

/**
 * @defgroup stepper2_set Stepper 2 Settings
 * @brief Settings of Stepper 2 Click driver.
 */

/**
 * @addtogroup stepper2_set
 * @{
 */

/**
 * @brief Stepper 2 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 2 Click driver.
 */
#define STEPPER2_PIN_STATE_LOW                  0
#define STEPPER2_PIN_STATE_HIGH                 1

/**
 * @brief Stepper 2 direction setting.
 * @details Specified setting for direction of Stepper 2 Click driver.
 */
#define STEPPER2_DIR_CCW                        0
#define STEPPER2_DIR_CW                         1

/**
 * @brief Stepper 2 step resolution setting.
 * @details Specified setting for step resolution of Stepper 2 Click driver.
 */
#define STEPPER2_MODE_FULL_STEP                 0
#define STEPPER2_MODE_HALF_STEP                 1
#define STEPPER2_MODE_QUARTER_STEP              2
#define STEPPER2_MODE_1_OVER_8_STEP             3

/**
 * @brief Stepper 2 microstep setting.
 * @details Specified setting for microsteps of Stepper 2 Click driver.
 */
#define STEPPER2_MICROSTEP_NUM_PER_STEP         32

/**
 * @brief Stepper 2 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER2_SPEED_VERY_SLOW                0
#define STEPPER2_SPEED_SLOW                     1
#define STEPPER2_SPEED_MEDIUM                   2
#define STEPPER2_SPEED_FAST                     3
#define STEPPER2_SPEED_VERY_FAST                4 

/*! @} */ // stepper2_set

/**
 * @defgroup stepper2_map Stepper 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 2 Click driver.
 */

/**
 * @addtogroup stepper2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 2 Click to the selected MikroBUS.
 */
#define STEPPER2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.slp = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper2_map
/*! @} */ // stepper2

/**
 * @brief Stepper 2 Click context object.
 * @details Context object definition of Stepper 2 Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Enable pin (active low). */
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t slp;          /**< Sleep pin (active low). */
    digital_out_t step;         /**< Step signal pin. */
    digital_out_t dir;          /**< Direction control pin. */

} stepper2_t;

/**
 * @brief Stepper 2 Click configuration object.
 * @details Configuration object definition of Stepper 2 Click driver.
 */
typedef struct
{
    pin_name_t en;              /**< Enable pin (active low). */
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t slp;             /**< Sleep pin (active low). */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t dir;             /**< Direction control pin. */

} stepper2_cfg_t;

/**
 * @brief Stepper 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER2_OK = 0,
    STEPPER2_ERROR = -1

} stepper2_return_value_t;

/*!
 * @addtogroup stepper2 Stepper 2 Click Driver
 * @brief API for configuring and manipulating Stepper 2 Click driver.
 * @{
 */

/**
 * @brief Stepper 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper2_cfg_setup ( stepper2_cfg_t *cfg );

/**
 * @brief Stepper 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper2_init ( stepper2_t *ctx, stepper2_cfg_t *cfg );

/**
 * @brief Stepper 2 default configuration function.
 * @details This function executes a default configuration of Stepper 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void stepper2_default_cfg ( stepper2_t *ctx ) ;

/**
 * @brief Stepper 2 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast,
 * @return None.
 * @note None.
 */
void stepper2_drive_motor ( stepper2_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 2 enable reset function.
 * @details This function enables the reset by setting the RESET pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_enable_reset ( stepper2_t *ctx );

/**
 * @brief Stepper 2 disable reset function.
 * @details This function disables the reset by setting the RESET pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_disable_reset ( stepper2_t *ctx );

/**
 * @brief Stepper 2 enable sleep function.
 * @details This function enables the sleep by setting the SLEEP pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_enable_sleep ( stepper2_t *ctx );

/**
 * @brief Stepper 2 disable sleep function.
 * @details This function disables the sleep by setting the SLEEP pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_disable_sleep ( stepper2_t *ctx );

/**
 * @brief Stepper 2 enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_enable_device ( stepper2_t *ctx );

/**
 * @brief Stepper 2 disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_disable_device ( stepper2_t *ctx );

/**
 * @brief Stepper 2 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper2_set_direction ( stepper2_t *ctx, uint8_t dir );

/**
 * @brief Stepper 2 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper2_switch_direction ( stepper2_t *ctx );

/**
 * @brief Stepper 2 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper2_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper2_set_step_pin ( stepper2_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER2_H

/*! @} */ // stepper2

// ------------------------------------------------------------------------ END
