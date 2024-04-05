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
 * @file stspin220.h
 * @brief This file contains API for STSPIN220 Click Driver.
 */

#ifndef STSPIN220_H
#define STSPIN220_H

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
 * @addtogroup stspin220 STSPIN220 Click Driver
 * @brief API for configuring and manipulating STSPIN220 Click driver.
 * @{
 */

/**
 * @defgroup stspin220_set STSPIN220 Settings
 * @brief Settings of STSPIN220 Click driver.
 */

/**
 * @addtogroup stspin220_set
 * @{
 */

/**
 * @brief STSPIN220 direction setting.
 * @details Specified setting for direction of STSPIN220 Click driver.
 */
#define STSPIN220_DIR_CW                        0
#define STSPIN220_DIR_CCW                       1

/**
 * @brief STSPIN220 pin logic level setting.
 * @details Specified setting for pin logic level of STSPIN220 Click driver.
 */
#define STSPIN220_PIN_LOW_LEVEL                 0
#define STSPIN220_PIN_HIGH_LEVEL                1

/**
 * @brief STSPIN220 device speed settings.
 * @details Specified setting for rotation speed.
 */
#define STSPIN220_SPEED_VERY_SLOW               0
#define STSPIN220_SPEED_SLOW                    1
#define STSPIN220_SPEED_MEDIUM                  2
#define STSPIN220_SPEED_FAST                    3
#define STSPIN220_SPEED_VERY_FAST               4 

/*! @} */ // stspin220_set

/**
 * @defgroup stspin220_map STSPIN220 MikroBUS Map
 * @brief MikroBUS pin mapping of STSPIN220 Click driver.
 */

/**
 * @addtogroup stspin220_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of STSPIN220 Click to the selected MikroBUS.
 */
#define STSPIN220_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.dir = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.rst = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.step = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.fault = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // stspin220_map
/*! @} */ // stspin220

/**
 * @brief STSPIN220 Click context object.
 * @details Context object definition of STSPIN220 Click driver.
 */
typedef struct
{
    digital_out_t dir;      /**< Direction control pin. */
    digital_out_t rst;      /**< Electric angle reset pin. */
    digital_out_t en;       /**< Enable output pin. */
    digital_out_t step;     /**< Step signal pin. */

    digital_in_t fault;     /**< Fault pin indication. */

} stspin220_t;

/**
 * @brief STSPIN220 Click configuration object.
 * @details Configuration object definition of STSPIN220 Click driver.
 */
typedef struct
{
    pin_name_t dir;         /**< Direction control pin. */
    pin_name_t rst;         /**< Electric angle reset pin. */
    pin_name_t en;          /**< Enable output pin. */
    pin_name_t step;        /**< Step signal pin. */
    pin_name_t fault;       /**< Fault pin indication. */

} stspin220_cfg_t;

/**
 * @brief STSPIN220 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    STSPIN220_OK = 0,
    STSPIN220_ERROR = -1

} stspin220_return_value_t;

/*!
 * @addtogroup stspin220 STSPIN220 Click Driver
 * @brief API for configuring and manipulating STSPIN220 Click driver.
 * @{
 */

/**
 * @brief STSPIN220 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #stspin220_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void stspin220_cfg_setup ( stspin220_cfg_t *cfg );

/**
 * @brief STSPIN220 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #stspin220_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t stspin220_init ( stspin220_t *ctx, stspin220_cfg_t *cfg );

/**
 * @brief STSPIN220 default configuration function.
 * @details This function executes a default configuration of STSPIN220
 * click board.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return None.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void stspin220_default_cfg ( stspin220_t *ctx );

/**
 * @brief STSPIN220 drive motor function.
 * @details This function drives the motor for the specific number of steps at the selected speed.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
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
void stspin220_drive_motor ( stspin220_t *ctx, uint32_t steps, uint8_t speed );

/**
 * @brief STSPIN220 enable device function.
 * @details This function enables the device by setting the EN pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stspin220_enable_device ( stspin220_t *ctx );

/**
 * @brief STSPIN220 disable device function.
 * @details This function disables the device by setting the EN pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stspin220_disable_device ( stspin220_t *ctx );

/**
 * @brief STSPIN220 set direction function.
 * @details This function sets the motor direction by setting the DIR pin logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @param[in] dir : @li @c 0 - Clockwise,
 *                  @li @c 1 - Counter-Clockwise.
 * @return None.
 * @note None.
 */
void stspin220_set_direction ( stspin220_t *ctx, uint8_t dir );

/**
 * @brief STSPIN220 switch direction function.
 * @details This function switches the motor direction by toggling the DIR pin.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stspin220_switch_direction ( stspin220_t *ctx );

/**
 * @brief STSPIN220 reset device function.
 * @details This function resets the device by toggling the RST pin.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void stspin220_reset_device ( stspin220_t *ctx );

/**
 * @brief STSPIN220 set rst pin function.
 * @details This function sets the RST pin logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stspin220_set_rst_pin ( stspin220_t *ctx, uint8_t state );

/**
 * @brief STSPIN220 get fault pin function.
 * @details This function returns the FAULT pin logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t stspin220_get_fault_pin ( stspin220_t *ctx );

/**
 * @brief STSPIN220 set step pin function.
 * @details This function sets the STEP pin logic state.
 * @param[in] ctx : Click context object.
 * See #stspin220_t object definition for detailed explanation.
 * @param[in] state : @li @c 0 - Low logic state,
 *                    @li @c 1 - High logic state.
 * @return None.
 * @note None.
 */
void stspin220_set_step_pin ( stspin220_t *ctx, uint8_t state );

#ifdef __cplusplus
}
#endif
#endif // STSPIN220_H

/*! @} */ // stspin220

// ------------------------------------------------------------------------ END
