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
 * @file pulse.h
 * @brief This file contains API for PULSE Click Driver.
 */

#ifndef PULSE_H
#define PULSE_H

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
 * @addtogroup pulse PULSE Click Driver
 * @brief API for configuring and manipulating PULSE Click driver.
 * @{
 */

 /**
 * @defgroup pulse_set PULSE Settings
 * @brief Settings of PULSE Click driver.
 */

/**
 * @addtogroup pulse_set
 * @{
 */

/**
 * @brief PULSE pin selection setting.
 * @details Specified setting for pin selection of PULSE Click driver.
 */
#define PULSE_PIN_OUT                   0
#define PULSE_PIN_INT                   1

/*! @} */ // pulse_set
 
/**
 * @defgroup pulse_map PULSE MikroBUS Map
 * @brief MikroBUS pin mapping of PULSE Click driver.
 */

/**
 * @addtogroup pulse_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of PULSE Click to the selected MikroBUS.
 */
#define PULSE_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.out = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // pulse_map
/*! @} */ // pulse

/**
 * @brief PULSE Click context object.
 * @details Context object definition of PULSE Click driver.
 */
typedef struct
{
    digital_in_t out;           /**< OUT pulse output pin (active high). */
    digital_in_t int_pin;       /**< INT pulse output pin (active high). */

} pulse_t;

/**
 * @brief PULSE Click configuration object.
 * @details Configuration object definition of PULSE Click driver.
 */
typedef struct
{
    pin_name_t out;             /**< OUT pulse output pin descriptor. */
    pin_name_t int_pin;         /**< INT pulse output pin descriptor. */

} pulse_cfg_t;

/**
 * @brief PULSE Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    PULSE_OK = 0,
    PULSE_ERROR = -1

} pulse_return_value_t;

/*!
 * @addtogroup pulse PULSE Click Driver
 * @brief API for configuring and manipulating PULSE Click driver.
 * @{
 */

/**
 * @brief PULSE configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #pulse_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void pulse_cfg_setup ( pulse_cfg_t *cfg );

/**
 * @brief PULSE initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #pulse_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #pulse_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pulse_init ( pulse_t *ctx, pulse_cfg_t *cfg );

/**
 * @brief PULSE read pin function.
 * @details This function reads the logic state of the selected pulse output pin.
 * @param[in] ctx : Click context object.
 * See #pulse_t object definition for detailed explanation.
 * @param[in] pin : Pin selection, PULSE_PIN_OUT or PULSE_PIN_INT.
 * @param[out] state : Logic state of the selected pin.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t pulse_read_pin ( pulse_t *ctx, uint8_t pin, uint8_t *state );

#ifdef __cplusplus
}
#endif
#endif // PULSE_H

/*! @} */ // pulse

// ------------------------------------------------------------------------ END
