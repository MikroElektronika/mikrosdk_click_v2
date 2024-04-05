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
 * @file hbridge.h
 * @brief This file contains API for H-Bridge Click Driver.
 */

#ifndef HBRIDGE_H
#define HBRIDGE_H

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

/*!
 * @addtogroup hbridge H-Bridge Click Driver
 * @brief API for configuring and manipulating H-Bridge Click driver.
 * @{
 */

/**
 * @defgroup hbridge_set H-Bridge Registers Settings
 * @brief Settings for registers of H-Bridge Click driver.
 */

/**
 * @addtogroup hbridge_set
 * @{
 */

/**
 * @brief H-Bridge direction setting.
 * @details Specified setting for direction of H-Bridge Click driver.
 */
#define HBRIDGE_DIR_CW                      0
#define HBRIDGE_DIR_CCW                     1

/**
 * @brief H-Bridge pin logic level setting.
 * @details Specified setting for pin logic level of H-Bridge Click driver.
 */
#define HBRIDGE_PIN_LOW_LEVEL               0
#define HBRIDGE_PIN_HIGH_LEVEL              1

/**
 * @brief H-Bridge step resolution setting.
 * @details Specified setting for step resolution of H-Bridge Click driver.
 */
#define HBRIDGE_MODE_FULL_STEP              0
#define HBRIDGE_MODE_HALF_STEP              1

/**
 * @brief H-Bridge device speed settings.
 * @details Specified setting for rotation speed.
 */
#define HBRIDGE_SPEED_VERY_SLOW             0
#define HBRIDGE_SPEED_SLOW                  1
#define HBRIDGE_SPEED_MEDIUM                2
#define HBRIDGE_SPEED_FAST                  3
#define HBRIDGE_SPEED_VERY_FAST             4 

/*! @} */ // hbridge_set

/**
 * @defgroup hbridge_map H-Bridge MikroBUS Map
 * @brief MikroBUS pin mapping of H-Bridge Click driver.
 */

/**
 * @addtogroup hbridge_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of H-Bridge Click to the selected MikroBUS.
 */
#define HBRIDGE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.in2a = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.in2b = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in1b = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.in1a = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // hbridge_map
/*! @} */ // hbridge

/**
 * @brief H-Bridge Click context object.
 * @details Context object definition of H-Bridge Click driver.
 */
typedef struct
{
    digital_out_t in2a;         /**< IN2A pin. */
    digital_out_t in2b;         /**< IN2B pin. */
    digital_out_t in1b;         /**< IN1B pin. */
    digital_out_t in1a;         /**< IN1A pin. */

    uint8_t step_mode;          /**< Step mode setting (0-full step, 1-half step). */
    uint8_t direction;          /**< Direction setting (0-cw, 1-ccw). */

} hbridge_t;

/**
 * @brief H-Bridge Click configuration object.
 * @details Configuration object definition of H-Bridge Click driver.
 */
typedef struct
{
    pin_name_t in2a;            /**< IN2A pin. */
    pin_name_t in2b;            /**< IN2B pin. */
    pin_name_t in1b;            /**< IN1B pin. */
    pin_name_t in1a;            /**< IN1A pin. */

} hbridge_cfg_t;

/**
 * @brief H-Bridge Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    HBRIDGE_OK = 0,
    HBRIDGE_ERROR = -1

} hbridge_return_value_t;

/*!
 * @addtogroup hbridge H-Bridge Click Driver
 * @brief API for configuring and manipulating H-Bridge Click driver.
 * @{
 */

/**
 * @brief H-Bridge configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #hbridge_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void hbridge_cfg_setup ( hbridge_cfg_t *cfg );

/**
 * @brief H-Bridge initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #hbridge_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t hbridge_init ( hbridge_t *ctx, hbridge_cfg_t *cfg );

/**
 * @brief H-Bridge set in1a pin function.
 * @details This function sets the IN1A pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void hbridge_set_in1a_pin ( hbridge_t *ctx, uint8_t state );

/**
 * @brief H-Bridge set in2a pin function.
 * @details This function sets the IN2A pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void hbridge_set_in2a_pin ( hbridge_t *ctx, uint8_t state );

/**
 * @brief H-Bridge set in1b pin function.
 * @details This function sets the IN1B pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void hbridge_set_in1b_pin ( hbridge_t *ctx, uint8_t state );

/**
 * @brief H-Bridge set in2b pin function.
 * @details This function sets the IN2B pin logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void hbridge_set_in2b_pin ( hbridge_t *ctx, uint8_t state );

/**
 * @brief H-Bridge set step mode function.
 * @details This function sets the step mode resolution settings in @b ctx->step_mode.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step.
 * @return None.
 * @note None.
 */
void hbridge_set_step_mode ( hbridge_t *ctx, uint8_t mode );

/**
 * @brief H-Bridge set direction function.
 * @details This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void hbridge_set_direction ( hbridge_t *ctx, uint8_t dir );

/**
 * @brief H-Bridge switch direction function.
 * @details This function switches the motor direction in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge_switch_direction ( hbridge_t *ctx );

/**
 * @brief H-Bridge enable device function.
 * @details This function enables the device by setting all pins to low logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge_enable_device ( hbridge_t *ctx );

/**
 * @brief H-Bridge disable device function.
 * @details This function disables the device by setting all pins to high logic state.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void hbridge_disable_device ( hbridge_t *ctx );

/**
 * @brief H-Bridge driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #hbridge_t object definition for detailed explanation.
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
void hbridge_drive_motor ( hbridge_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // HBRIDGE_H

/*! @} */ // hbridge

// ------------------------------------------------------------------------ END
