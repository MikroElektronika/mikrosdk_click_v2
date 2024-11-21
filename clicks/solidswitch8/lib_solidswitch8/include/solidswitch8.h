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
 * @file solidswitch8.h
 * @brief This file contains API for SolidSwitch 8 Click Driver.
 */

#ifndef SOLIDSWITCH8_H
#define SOLIDSWITCH8_H

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
 * @addtogroup solidswitch8 SolidSwitch 8 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 8 Click driver.
 * @{
 */

/**
 * @defgroup solidswitch8_set SolidSwitch 8 Registers Settings
 * @brief Settings for registers of SolidSwitch 8 Click driver.
 */

/**
 * @addtogroup solidswitch8_set
 * @{
 */

/**
 * @brief SolidSwitch 8 description setting.
 * @details Specified setting for description of SolidSwitch 8 Click driver.
 */
#define SOLIDSWITCH8_PIN_STATE_LOW                  0x00
#define SOLIDSWITCH8_PIN_STATE_HIGH                 0x01

/*! @} */ // solidswitch8_set

/**
 * @defgroup solidswitch8_map SolidSwitch 8 MikroBUS Map
 * @brief MikroBUS pin mapping of SolidSwitch 8 Click driver.
 */

/**
 * @addtogroup solidswitch8_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of SolidSwitch 8 Click to the selected MikroBUS.
 */
#define SOLIDSWITCH8_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.err = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.in = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sts = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // solidswitch8_map
/*! @} */ // solidswitch8

/**
 * @brief SolidSwitch 8 Click context object.
 * @details Context object definition of SolidSwitch 8 Click driver.
 */
typedef struct
{
    digital_out_t err;      /**< Error LED pin. */
    digital_out_t in;       /**< Input pin. */

    digital_in_t sts;       /**< Status pin. */

} solidswitch8_t;

/**
 * @brief SolidSwitch 8 Click configuration object.
 * @details Configuration object definition of SolidSwitch 8 Click driver.
 */
typedef struct
{
    pin_name_t err;         /**< Error LED pin. */
    pin_name_t in;          /**< Input pin. */
    pin_name_t sts;         /**< Status pin. */

} solidswitch8_cfg_t;

/**
 * @brief SolidSwitch 8 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SOLIDSWITCH8_OK = 0,
    SOLIDSWITCH8_ERROR = -1

} solidswitch8_return_value_t;

/*!
 * @addtogroup solidswitch8 SolidSwitch 8 Click Driver
 * @brief API for configuring and manipulating SolidSwitch 8 Click driver.
 * @{
 */

/**
 * @brief SolidSwitch 8 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #solidswitch8_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void solidswitch8_cfg_setup ( solidswitch8_cfg_t *cfg );

/**
 * @brief SolidSwitch 8 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #solidswitch8_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #solidswitch8_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t solidswitch8_init ( solidswitch8_t *ctx, solidswitch8_cfg_t *cfg );

/**
 * @brief SolidSwitch 8 default configuration function.
 * @details This function executes a default configuration of SolidSwitch 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch8_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void solidswitch8_default_cfg ( solidswitch8_t *ctx );

/**
 * @brief SolidSwitch 8 err pin setting function.
 * @details This function sets the err pin state to the selected level of
 * SolidSwitch 8 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch8_t object definition for detailed explanation.
 * @param[in] pin_state : State of the selected pin.
 * @return Nothing.
 * @note None.
 */
void solidswitch8_set_err_pin ( solidswitch8_t *ctx, uint8_t pin_state );

/**
 * @brief SolidSwitch 8 in pin setting function.
 * @details This function sets the in pin state to the selected level of
 * SolidSwitch 8 Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch8_t object definition for detailed explanation.
 * @param[in] pin_state : State of the selected pin.
 * @return Nothing.
 * @note None.
 */
void solidswitch8_set_in_pin ( solidswitch8_t *ctx, uint8_t pin_state );

/**
 * @brief SolidSwitch 8 sts pin reading function.
 * @details This function reads the state of the status pin of SolidSwitch 8
 * Click board.
 * @param[in] ctx : Click context object.
 * See #solidswitch8_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t solidswitch8_get_sts_pin ( solidswitch8_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // SOLIDSWITCH8_H

/*! @} */ // solidswitch8

// ------------------------------------------------------------------------ END
