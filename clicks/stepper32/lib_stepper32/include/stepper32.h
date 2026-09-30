/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
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
 * @file stepper32.h
 * @brief This file contains API for Stepper 32 Click Driver.
 */

#ifndef STEPPER32_H
#define STEPPER32_H

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
 * @addtogroup stepper32 Stepper 32 Click Driver
 * @brief API for configuring and manipulating Stepper 32 Click driver.
 * @{
 */

/**
 * @defgroup stepper32_set Stepper 32 Settings
 * @brief Settings of Stepper 32 Click driver.
 */

/**
 * @addtogroup stepper32_set
 * @{
 */

/**
 * @brief Stepper 32 direction setting.
 * @details Specified setting for direction of Stepper 32 Click driver.
 */
#define STEPPER32_DIR_CW                            0
#define STEPPER32_DIR_CCW                           1

/**
 * @brief Stepper 32 pin logic state setting.
 * @details Specified setting for pin logic state of Stepper 32 Click driver.
 */
#define STEPPER32_PIN_STATE_LOW                     0
#define STEPPER32_PIN_STATE_HIGH                    1

/**
 * @brief Stepper 32 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STEPPER32_SPEED_VERY_SLOW                   0
#define STEPPER32_SPEED_SLOW                        1
#define STEPPER32_SPEED_MEDIUM                      2
#define STEPPER32_SPEED_FAST                        3
#define STEPPER32_SPEED_VERY_FAST                   4

/*! @} */ // stepper32_set

/**
 * @defgroup stepper32_map Stepper 32 MikroBUS Map
 * @brief MikroBUS pin mapping of Stepper 32 Click driver.
 */

/**
 * @addtogroup stepper32_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Stepper 32 Click to the selected MikroBUS.
 */
#define STEPPER32_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.home = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stepper32_map
/*! @} */ // stepper32

/**
 * @brief Stepper 32 Click context object.
 * @details Context object definition of Stepper 32 Click driver.
 */
typedef struct
{
    digital_out_t en;           /**< Enable output pin (active low). */
    digital_out_t rst;          /**< Reset device pin (active low). */
    digital_out_t dir;          /**< Direction control pin (CW-high, CCW-low). */
    digital_out_t step;         /**< Step signal pin. */

    digital_in_t home;          /**< Home position pin (active low). */

} stepper32_t;

/**
 * @brief Stepper 32 Click configuration object.
 * @details Configuration object definition of Stepper 32 Click driver.
 */
typedef struct
{
    pin_name_t en;              /**< Enable output pin (active high). */
    pin_name_t rst;             /**< Reset device pin (active low). */
    pin_name_t dir;             /**< Direction control pin (CW-high, CCW-low). */
    pin_name_t step;            /**< Step signal pin. */
    pin_name_t home;            /**< Home position pin (active low). */

} stepper32_cfg_t;

/**
 * @brief Stepper 32 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STEPPER32_OK = 0,
    STEPPER32_ERROR = -1

} stepper32_return_value_t;

/*!
 * @addtogroup stepper32 Stepper 32 Click Driver
 * @brief API for configuring and manipulating Stepper 32 Click driver.
 * @{
 */

/**
 * @brief Stepper 32 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stepper32_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stepper32_cfg_setup ( stepper32_cfg_t *cfg );

/**
 * @brief Stepper 32 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stepper32_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stepper32_init ( stepper32_t *ctx, stepper32_cfg_t *cfg );

/**
 * @brief Stepper 32 enable device function.
 * @details This function enables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper32_enable_device ( stepper32_t *ctx );

/**
 * @brief Stepper 32 disable device function.
 * @details This function disables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper32_disable_device ( stepper32_t *ctx );

/**
 * @brief Stepper 32 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper32_set_rst_pin ( stepper32_t *ctx, uint8_t state );

/**
 * @brief Stepper 32 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper32_reset_device ( stepper32_t *ctx );

/**
 * @brief Stepper 32 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Counter-Clockwise,
 *                  @li @c 1 - Clockwise.
 * @return None.
 * @note None.
 */
void stepper32_set_direction ( stepper32_t *ctx, uint8_t dir );

/**
 * @brief Stepper 32 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stepper32_switch_direction ( stepper32_t *ctx );

/**
 * @brief Stepper 32 get HOME pin function.
 * @details This function returns the HOME pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stepper32_get_home_pin ( stepper32_t *ctx );

/**
 * @brief Stepper 32 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stepper32_set_step_pin ( stepper32_t *ctx, uint8_t state );

/**
 * @brief Stepper 32 driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stepper32_t object definition for detailed explanation.
 * @param[in] steps : Number of steps to rotate motor.
 * @param[in] speed : Motor rotation speed:
 *                    @li @c 0 - Very slow,
 *                    @li @c 1 - Slow,
 *                    @li @c 2 - Medium,
 *                    @li @c 3 - Fast,
 *                    @li @c 4 - Very fast.
 * @return None.
 * @note None.
 */
void stepper32_drive_motor ( stepper32_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // STEPPER32_H

/*! @} */ // stepper32

// ------------------------------------------------------------------------ END
