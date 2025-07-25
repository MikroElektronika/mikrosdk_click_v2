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
 * @file powerstep.h
 * @brief This file contains API for Power Step Click Driver.
 */

#ifndef POWERSTEP_H
#define POWERSTEP_H

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
 * @addtogroup powerstep Power Step Click Driver
 * @brief API for configuring and manipulating Power Step Click driver.
 * @{
 */

/**
 * @defgroup powerstep_set Power Step Settings
 * @brief Settings of Power Step Click driver.
 */

/**
 * @addtogroup powerstep_set
 * @{
 */

/**
 * @brief Power Step direction setting.
 * @details Specified setting for direction of Power Step Click driver.
 */
#define POWERSTEP_DIR_CW                        0
#define POWERSTEP_DIR_CCW                       1

/**
 * @brief Power Step pin logic level setting.
 * @details Specified setting for pin logic level of Power Step Click driver.
 */
#define POWERSTEP_PIN_LOW_LEVEL                 0
#define POWERSTEP_PIN_HIGH_LEVEL                1

/**
 * @brief Power Step device speed settings.
 * @details Specified setting for rotation speed.
 */
#define POWERSTEP_SPEED_VERY_SLOW               0
#define POWERSTEP_SPEED_SLOW                    1
#define POWERSTEP_SPEED_MEDIUM                  2
#define POWERSTEP_SPEED_FAST                    3
#define POWERSTEP_SPEED_VERY_FAST               4

/*! @} */ // powerstep_set

/**
 * @defgroup powerstep_map Power Step MikroBUS Map
 * @brief MikroBUS pin mapping of Power Step Click driver.
 */

/**
 * @addtogroup powerstep_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power Step Click to the selected MikroBUS.
 */
#define POWERSTEP_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // powerstep_map
/*! @} */ // powerstep

/**
 * @brief Power Step Click context object.
 * @details Context object definition of Power Step Click driver.
 */
typedef struct
{
    digital_out_t dir;          /**< Direction control pin (0-CW, 1-CCW). */
    digital_out_t rst;          /**< Reset pin (active low). */
    digital_out_t en;           /**< Enable output pin (active low). */
    digital_out_t step;         /**< Step clock pin. */

} powerstep_t;

/**
 * @brief Power Step Click configuration object.
 * @details Configuration object definition of Power Step Click driver.
 */
typedef struct
{
    pin_name_t dir;             /**< Direction control pin (0-CW, 1-CCW). */
    pin_name_t rst;             /**< Reset pin (active low). */
    pin_name_t en;              /**< Enable output pin (active low). */
    pin_name_t step;            /**< Step clock pin. */

} powerstep_cfg_t;

/**
 * @brief Power Step Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERSTEP_OK = 0,
    POWERSTEP_ERROR = -1

} powerstep_return_value_t;

/*!
 * @addtogroup powerstep Power Step Click Driver
 * @brief API for configuring and manipulating Power Step Click driver.
 * @{
 */

/**
 * @brief Power Step configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powerstep_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powerstep_cfg_setup ( powerstep_cfg_t *cfg );

/**
 * @brief Power Step initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powerstep_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powerstep_init ( powerstep_t *ctx, powerstep_cfg_t *cfg );

/**
 * @brief Power Step enable device function.
 * @details This function enables the device output by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powerstep_enable_device ( powerstep_t *ctx );

/**
 * @brief Power Step disable device function.
 * @details This function disables the device output by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powerstep_disable_device ( powerstep_t *ctx );

/**
 * @brief Power Step set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void powerstep_set_direction ( powerstep_t *ctx, uint8_t dir );

/**
 * @brief Power Step switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powerstep_switch_direction ( powerstep_t *ctx );

/**
 * @brief Power Step set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void powerstep_set_rst_pin ( powerstep_t *ctx, uint8_t state );

/**
 * @brief Power Step reset device function.
 * @details This function resets the device by setting the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void powerstep_reset_device ( powerstep_t *ctx );

/**
 * @brief Power Step set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void powerstep_set_step_pin ( powerstep_t *ctx, uint8_t state );

/**
 * @brief Power Step driver motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #powerstep_t object definition for detailed explanation.
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
void powerstep_drive_motor ( powerstep_t *ctx, uint32_t steps, uint8_t speed );

#ifdef __cplusplus
}
#endif
#endif // POWERSTEP_H

/*! @} */ // powerstep

// ------------------------------------------------------------------------ END
