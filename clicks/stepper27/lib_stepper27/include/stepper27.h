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
 * @file stepper27.h
 * @brief This file contains API for Stepper 27 Click Driver.
 */

#ifndef STEPPER27_H
#define STEPPER27_H

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
 * @addtogroup stepper27 Stepper 27 Click Driver
 * @brief API for configuring and manipulating Stepper 27 Click driver.
 * @{
 */

/**
 * @defgroup stepper27_set Stepper 27 Settings
 * @brief Settings of Stepper 27 Click driver.
 */

/**
 * @addtogroup stepper27_set
 * @{
 */

/**
 * @brief Stepper 27 direction setting.
 * @details Specified setting for direction of Stepper 27 Click driver.
 */
#define STEPPER27_DIR_CW                        1
#define STEPPER27_DIR_CCW                       0

/**
 * @brief Stepper 27 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 27 Click driver.
 */
#define STEPPER27_PIN_LOW_LEVEL                 0
#define STEPPER27_PIN_HIGH_LEVEL                1

/**
 * @brief Stepper 27 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER27_SPEED_VERY_SLOW               0
#define STEPPER27_SPEED_SLOW                    1
#define STEPPER27_SPEED_MEDIUM                  2
#define STEPPER27_SPEED_FAST                    3
#define STEPPER27_SPEED_VERY_FAST               4

/*! @} */ // stepper27_set

/**
 * @defgroup stepper27_map Stepper 27 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 27 Click driver.
 */

/**
 * @addtogroup stepper27_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 27 Click to the selected MikroBUS.
 */
#define STEPPER27_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.sleep = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper27_map
/*! @} */ // stepper27

/**
 * @brief Stepper 27 Click context object.
 * @details Context object definition of Stepper 27 Click driver.
 */
typedef struct
{
    digital_out_t dir;          /**< Direction pin (0-CCW, 1-CW). */
    digital_out_t sleep;        /**< Sleep pin (active low). */
    digital_out_t en;           /**< Enable output pin (active high). */
    digital_out_t step;         /**< Step signal pin. */

    digital_in_t fault;         /**< Fault indicator pin (active low). */

} stepper27_t;

/**
 * @brief Stepper 27 Click configuration object.
 * @details Configuration object definition of Stepper 27 Click driver.
 */
typedef struct
{
    pin_name_t dir;             /**< Direction pin (0-CCW, 1-CW). */
    pin_name_t sleep;           /**< Sleep pin (active low). */
    pin_name_t en;              /**< Enable output pin (active high). */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t fault;           /**< Fault indicator pin (active low). */

} stepper27_cfg_t;

/**
 * @brief Stepper 27 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER27_OK = 0,
    STEPPER27_ERROR = -1

} stepper27_return_value_t;

/*!
 * @addtogroup stepper27 Stepper 27 Click Driver
 * @brief API for configuring and manipulating Stepper 27 Click driver.
 * @{
 */

/**
 * @brief Stepper 27 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper27_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper27_cfg_setup ( stepper27_cfg_t *cfg );

/**
 * @brief Stepper 27 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper27_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper27_init ( stepper27_t *ctx, stepper27_cfg_t *cfg );

/**
 * @brief Stepper 27 enable device function.
 * @details This function enables the device output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper27_enable_device ( stepper27_t *ctx );

/**
 * @brief Stepper 27 disable device function.
 * @details This function disables the device output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper27_disable_device ( stepper27_t *ctx );

/**
 * @brief Stepper 27 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper27_set_direction ( stepper27_t *ctx, uint8_t dir );

/**
 * @brief Stepper 27 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper27_switch_direction ( stepper27_t *ctx );

/**
 * @brief Stepper 27 set sleep pin function.
 * @details This function sets the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper27_set_sleep_pin ( stepper27_t *ctx, uint8_t state );

/**
 * @brief Stepper 27 reset device function.
 * @details This function resets the device by toggling the SLEEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper27_reset_device ( stepper27_t *ctx );

/**
 * @brief Stepper 27 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper27_set_step_pin ( stepper27_t *ctx, uint8_t state );

/**
 * @brief Stepper 27 get fault pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper27_get_fault_pin ( stepper27_t *ctx );

/**
 * @brief Stepper 27 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper27_t object definition for detailed explanation.
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
void stepper27_drive_motor ( stepper27_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER27_H

/*! @} */ // stepper27

// ------------------------------------------------------------------------ END
