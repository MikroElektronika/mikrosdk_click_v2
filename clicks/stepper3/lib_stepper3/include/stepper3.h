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
 * @file stepper3.h
 * @brief This file contains API for Stepper 3 Click Driver.
 */

#ifndef STEPPER3_H
#define STEPPER3_H

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
 * @addtogroup stepper3 Stepper 3 Click Driver
 * @brief API for configuring and manipulating Stepper 3 Click driver.
 * @{
 */

/**
 * @defgroup stepper3_set Stepper 3 Registers Settings
 * @brief Settings for registers of Stepper 3 Click driver.
 */

/**
 * @addtogroup stepper3_set
 * @{
 */

/**
 * @brief Stepper 3 direction setting.
 * @details Specified setting for direction of Stepper 3 Click driver.
 */
#define STEPPER3_DIR_CW                     0
#define STEPPER3_DIR_CCW                    1

/**
 * @brief Stepper 3 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 3 Click driver.
 */
#define STEPPER3_PIN_LOW_LEVEL              0
#define STEPPER3_PIN_HIGH_LEVEL             1

/**
 * @brief Stepper 3 step resolution setting.
 * @details Specified setting for step resolution of Stepper 3 Click driver.
 */
#define STEPPER3_MODE_FULL_STEP             0
#define STEPPER3_MODE_HALF_STEP             1

/**
 * @brief Stepper 3 microstep setting.
 * @details Specified setting for microsteps of Stepper 3 Click driver.
 */
#define STEPPER3_MICROSTEP_NUM_PER_STEP     32

/**
 * @brief Stepper 3 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER3_SPEED_VERY_SLOW            0
#define STEPPER3_SPEED_SLOW                 1
#define STEPPER3_SPEED_MEDIUM               2
#define STEPPER3_SPEED_FAST                 3
#define STEPPER3_SPEED_VERY_FAST            4 

/*! @} */ // stepper3_set

/**
 * @defgroup stepper3_map Stepper 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 3 Click driver.
 */

/**
 * @addtogroup stepper3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 3 Click to the selected MikroBUS.
 */
#define STEPPER3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ina = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.inb = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.inc = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.ind = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // stepper3_map
/*! @} */ // stepper3

/**
 * @brief Stepper 3 Click context object.
 * @details Context object definition of Stepper 3 Click driver.
 */
typedef struct
{
    digital_out_t ina;      /**< INA pin. */
    digital_out_t inb;      /**< INB pin. */
    digital_out_t inc;      /**< INC pin. */
    digital_out_t ind;      /**< IND pin. */

    uint8_t step_mode;      /**< Step mode setting (0-full step, 1-half step). */
    uint8_t direction;      /**< Direction setting (0-cw, 1-ccw). */

} stepper3_t;

/**
 * @brief Stepper 3 Click configuration object.
 * @details Configuration object definition of Stepper 3 Click driver.
 */
typedef struct
{
    pin_name_t ina;         /**< INA pin. */
    pin_name_t inb;         /**< INB pin. */
    pin_name_t inc;         /**< INC pin. */
    pin_name_t ind;         /**< IND pin. */

} stepper3_cfg_t;

/**
 * @brief Stepper 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER3_OK = 0,
    STEPPER3_ERROR = -1

} stepper3_return_value_t;

/*!
 * @addtogroup stepper3 Stepper 3 Click Driver
 * @brief API for configuring and manipulating Stepper 3 Click driver.
 * @{
 */

/**
 * @brief Stepper 3 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper3_cfg_setup ( stepper3_cfg_t *cfg );

/**
 * @brief Stepper 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper3_init ( stepper3_t *ctx, stepper3_cfg_t *cfg );

/**
 * @brief Stepper 3 set ina pin function.
 * @details This function sets the INA pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper3_set_ina_pin ( stepper3_t *ctx, uint8_t state );

/**
 * @brief Stepper 3 set inb pin function.
 * @details This function sets the INB pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper3_set_inb_pin ( stepper3_t *ctx, uint8_t state );

/**
 * @brief Stepper 3 set inc pin function.
 * @details This function sets the INC pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper3_set_inc_pin ( stepper3_t *ctx, uint8_t state );

/**
 * @brief Stepper 3 set ind pin function.
 * @details This function sets the IND pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper3_set_ind_pin ( stepper3_t *ctx, uint8_t state );

/**
 * @brief Stepper 3 set step mode function.
 * @details This function sets the step mode resolution settings in @b ctx->step_mode.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 *                   @li @c 0 - Full step,
 *                   @li @c 1 - Half step.
 * @return None.
 * @note None.
 */
void stepper3_set_step_mode ( stepper3_t *ctx, uint8_t mode );

/**
 * @brief Stepper 3 set direction function.
 * @details This function sets the motor direction to clockwise or counter-clockwise in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper3_set_direction ( stepper3_t *ctx, uint8_t dir );

/**
 * @brief Stepper 3 switch direction function.
 * @details This function switches the motor direction in @b ctx->direction.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper3_switch_direction ( stepper3_t *ctx );

/**
 * @brief Stepper 3 enable device function.
 * @details This function enables the device by setting all pins to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper3_enable_device ( stepper3_t *ctx );

/**
 * @brief Stepper 3 disable device function.
 * @details This function disables the device by setting all pins to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper3_disable_device ( stepper3_t *ctx );

/**
 * @brief Stepper 3 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper3_t object definition for detailed explanation.
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
void stepper3_drive_motor ( stepper3_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER3_H

/*! @} */ // stepper3

// ------------------------------------------------------------------------ END
