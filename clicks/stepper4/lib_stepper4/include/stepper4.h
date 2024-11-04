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
 * @file stepper4.h
 * @brief This file contains API for Stepper 4 Click Driver.
 */

#ifndef STEPPER4_H
#define STEPPER4_H

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
 * @addtogroup stepper4 Stepper 4 Click Driver
 * @brief API for configuring and manipulating Stepper 4 Click driver.
 * @{
 */

/**
 * @defgroup stepper4_set Stepper 4 Settings
 * @brief Settings of Stepper 4 Click driver.
 */

/**
 * @addtogroup stepper4_set
 * @{
 */

/**
 * @brief Stepper 4 direction setting.
 * @details Specified setting for direction of Stepper 4 Click driver.
 */
#define STEPPER4_DIR_CW                         0
#define STEPPER4_DIR_CCW                        1

/**
 * @brief Stepper 4 pin logic level setting.
 * @details Specified setting for pin logic level of Stepper 4 Click driver.
 */
#define STEPPER4_PIN_LOW_LEVEL                  0
#define STEPPER4_PIN_HIGH_LEVEL                 1

/**
 * @brief Stepper 4 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER4_SPEED_VERY_SLOW                0
#define STEPPER4_SPEED_SLOW                     1
#define STEPPER4_SPEED_MEDIUM                   2
#define STEPPER4_SPEED_FAST                     3
#define STEPPER4_SPEED_VERY_FAST                4 

/*! @} */ // stepper4_set

/**
 * @defgroup stepper4_map Stepper 4 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 4 Click driver.
 */

/**
 * @addtogroup stepper4_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 4 Click to the selected MikroBUS.
 */
#define STEPPER4_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper4_map
/*! @} */ // stepper4

/**
 * @brief Stepper 4 Click context object.
 * @details Context object definition of Stepper 4 Click driver.
 */
typedef struct
{
    digital_out_t dir;          /**< Direction control pin. */
    digital_out_t rst;          /**< Electric angle reset pin. */
    digital_out_t en;           /**< Enable output pin. */
    digital_out_t step;         /**< Step signal pin. */

    digital_in_t int_pin;       /**< MO/LO input pin. */

} stepper4_t;

/**
 * @brief Stepper 4 Click configuration object.
 * @details Configuration object definition of Stepper 4 Click driver.
 */
typedef struct
{
    pin_name_t dir;             /**< Direction control pin. */
    pin_name_t rst;             /**< Electric angle reset pin. */
    pin_name_t en;              /**< Enable output pin. */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t int_pin;         /**< MO/LO input pin. */

} stepper4_cfg_t;

/**
 * @brief Stepper 4 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER4_OK = 0,
    STEPPER4_ERROR = -1

} stepper4_return_value_t;

/*!
 * @addtogroup stepper4 Stepper 4 Click Driver
 * @brief API for configuring and manipulating Stepper 4 Click driver.
 * @{
 */

/**
 * @brief Stepper 4 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper4_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper4_cfg_setup ( stepper4_cfg_t *cfg );

/**
 * @brief Stepper 4 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper4_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper4_init ( stepper4_t *ctx, stepper4_cfg_t *cfg );

/**
 * @brief Stepper 4 default configuration function.
 * @details This function executes a default configuration of Stepper 4
 * Click board.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void stepper4_default_cfg ( stepper4_t *ctx );

/**
 * @brief Stepper 4 drive motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
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
void stepper4_drive_motor ( stepper4_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief Stepper 4 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper4_enable_device ( stepper4_t *ctx );

/**
 * @brief Stepper 4 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper4_disable_device ( stepper4_t *ctx );

/**
 * @brief Stepper 4 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stepper4_set_direction ( stepper4_t *ctx, uint8_t dir );

/**
 * @brief Stepper 4 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper4_switch_direction ( stepper4_t *ctx );

/**
 * @brief Stepper 4 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper4_reset_device ( stepper4_t *ctx );

/**
 * @brief Stepper 4 get int pin function.
 * @details This function returns the INT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper4_get_int_pin ( stepper4_t *ctx );

/**
 * @brief Stepper 4 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper4_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper4_set_step_pin ( stepper4_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STEPPER4_H

/*! @} */ // stepper4

// ------------------------------------------------------------------------ END
