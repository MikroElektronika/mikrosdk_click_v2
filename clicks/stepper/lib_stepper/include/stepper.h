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
 * @file stepper.h
 * @brief This file contains API for Stepper Click Driver.
 */

#ifndef STEPPER_H
#define STEPPER_H

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
 * @addtogroup stepper Stepper Click Driver
 * @brief API for configuring and manipulating Stepper Click driver.
 * @{
 */

/**
 * @defgroup stepper_set Stepper Settings
 * @brief Settings of Stepper Click driver.
 */

/**
 * @addtogroup stepper_set
 * @{
 */

/**
 * @brief Stepper pin logic state setting.
 * @details Specified setting for pin logic state of Stepper Click driver.
 */
#define STEPPER_PIN_STATE_LOW                   0
#define STEPPER_PIN_STATE_HIGH                  1

/**
 * @brief Stepper direction setting.
 * @details Specified setting for direction of Stepper Click driver.
 */
#define STEPPER_DIR_CW                          0
#define STEPPER_DIR_CCW                         1

/**
 * @brief Stepper step resolution setting.
 * @details Specified setting for step resolution of Stepper Click driver.
 */
#define STEPPER_MODE_FULL_STEP                  0
#define STEPPER_MODE_HALF_STEP                  1
#define STEPPER_MODE_QUARTER_STEP               2
#define STEPPER_MODE_1_OVER_8_STEP              3

/**
 * @brief Stepper microstep setting.
 * @details Specified setting for microsteps of Stepper Click driver.
 */
#define STEPPER_MICROSTEP_NUM_PER_STEP          32

/**
 * @brief Stepper device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER_SPEED_VERY_SLOW                 0
#define STEPPER_SPEED_SLOW                      1
#define STEPPER_SPEED_MEDIUM                    2
#define STEPPER_SPEED_FAST                      3
#define STEPPER_SPEED_VERY_FAST                 4 

/*! @} */ // stepper_set

/**
 * @defgroup stepper_map Stepper MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper Click driver.
 */

/**
 * @addtogroup stepper_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper Click to the selected MikroBUS.
 */
#define STEPPER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.ms1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.ms2 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper_map
/*! @} */ // stepper

/**
 * @brief Stepper Click context object.
 * @details Context object definition of Stepper Click driver.
 */
typedef struct
{
    digital_out_t ms1;          /**< Step mode selection 1 pin. */
    digital_out_t ms2;          /**< Step mode selection 2 pin. */
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t step;         /**< Step signal pin. */
    digital_out_t en;           /**< Enable output pin. */

} stepper_t;

/**
 * @brief Stepper Click configuration object.
 * @details Configuration object definition of Stepper Click driver.
 */
typedef struct
{
    pin_name_t ms1;             /**< Step mode selection 1 pin. */
    pin_name_t ms2;             /**< Step mode selection 2 pin. */
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t en;              /**< Enable output pin. */

} stepper_cfg_t;

/**
 * @brief Stepper Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER_OK = 0,
    STEPPER_ERROR = -1

} stepper_return_value_t;

/*!
 * @addtogroup stepper Stepper Click Driver
 * @brief API for configuring and manipulating Stepper Click driver.
 * @{
 */

/**
 * @brief Stepper configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper_cfg_setup ( stepper_cfg_t *cfg );

/**
 * @brief Stepper initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper_init ( stepper_t *ctx, stepper_cfg_t *cfg );

/**
 * @brief Stepper default configuration function.
 * @details This function executes a default configuration of Stepper
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void stepper_default_cfg ( stepper_t *ctx ) ;

/**
 * @brief Stepper set step mode function.
 * @details This function sets the step mode resolution settings.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @param[in] mode : Step mode resolution.
 * @return None.
 * @note None.
 */
void stepper_set_step_mode ( stepper_t *ctx, uint8_t mode );

/**
 * @brief Stepper driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
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
void stepper_drive_motor ( stepper_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper enable device function.
 * @details This function enables the device by setting the ENABLE pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper_enable_device ( stepper_t *ctx );

/**
 * @brief Stepper disable device function.
 * @details This function disables the device by setting the ENABLE pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper_disable_device ( stepper_t *ctx );

/**
 * @brief Stepper set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper_set_direction ( stepper_t *ctx, uint8_t dir );

/**
 * @brief Stepper switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper_switch_direction ( stepper_t *ctx );

/**
 * @brief Stepper set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper_set_step_pin ( stepper_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER_H

/*! @} */ // stepper

// ------------------------------------------------------------------------ END
