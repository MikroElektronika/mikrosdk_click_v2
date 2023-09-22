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
 * @file waterdetect2.h
 * @brief This file contains API for Water Detect 2 Click Driver.
 */

#ifndef WATERDETECT2_H
#define WATERDETECT2_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup waterdetect2 Water Detect 2 Click Driver
 * @brief API for configuring and manipulating Water Detect 2 Click driver.
 * @{
 */

/**
 * @addtogroup waterdetect2_get
 * @{
 */

/**
 * @defgroup waterdetect2_get Water Detect 2 status of the fluid detection.
 * @brief Status of the fluid detection of Water Detect 2 Click driver.
 */
#define WATERDETECT2_FLUID_DETECTED    0

/*! @} */ // waterdetect2_get

/**
 * @defgroup waterdetect2_map Water Detect 2 MikroBUS Map
 * @brief MikroBUS pin mapping of Water Detect 2 Click driver.
 */

/**
 * @addtogroup waterdetect2_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Water Detect 2 Click to the selected MikroBUS.
 */
#define WATERDETECT2_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.on = MIKROBUS( mikrobus, MIKROBUS_PWM );   \
    cfg.det = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // waterdetect2_map
/*! @} */ // waterdetect2

/**
 * @brief Water Detect 2 Click context object.
 * @details Context object definition of Water Detect 2 Click driver.
 */
typedef struct
{
    digital_out_t on;    /**< Power on pin. */
    digital_in_t det;    /**< Fluid detection pin. */

} waterdetect2_t;

/**
 * @brief Water Detect 2 Click configuration object.
 * @details Configuration object definition of Water Detect 2 Click driver.
 */
typedef struct
{
    pin_name_t on;     /**< Power on pin. */
    pin_name_t det;    /**< Fluid detection pin. */

} waterdetect2_cfg_t;

/**
 * @brief Water Detect 2 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    WATERDETECT2_OK = 0,
    WATERDETECT2_ERROR = -1

} waterdetect2_return_value_t;

/*!
 * @addtogroup waterdetect2 Water Detect 2 Click Driver
 * @brief API for configuring and manipulating Water Detect 2 Click driver.
 * @{
 */

/**
 * @brief Water Detect 2 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #waterdetect2_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void waterdetect2_cfg_setup ( waterdetect2_cfg_t *cfg );

/**
 * @brief Water Detect 2 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #waterdetect2_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #waterdetect2_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t waterdetect2_init ( waterdetect2_t *ctx, waterdetect2_cfg_t *cfg );

/**
 * @brief Water Detect 2 default configuration function.
 * @details This function executes a default configuration of Water Detect 2
 * click board.
 * @param[in] ctx : Click context object.
 * See #waterdetect2_t object definition for detailed explanation.
 * @return Nothing.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void waterdetect2_default_cfg ( waterdetect2_t *ctx );

/**
 * @brief Water Detect 2 enable function.
 * @details This function sets the ON (PWM) pin on the high level 
 * to enable water detection of the Water Detect 2 click board™.
 * @param[in] ctx : Click context object.
 * See #waterdetect2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void waterdetect2_enable ( waterdetect2_t *ctx );

/**
 * @brief Water Detect 2 disable function.
 * @details This function clears the ON (PWM) pin on the low level 
 * to disable water detection of the Water Detect 2 click board™.
 * @param[in] ctx : Click context object.
 * See #waterdetect2_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void waterdetect2_disable ( waterdetect2_t *ctx );

/**
 * @brief Water Detect 2 get fluid status function.
 * @details This function reads the fluid presence status
 * of the Water Detect 2 click board™.
 * @param[in] ctx : Click context object.
 * See #waterdetect2_t object definition for detailed explanation.
 * @return @li @c 0 - Fluid is present,
 *         @li @c 1 - No fluid present.
 * @note None.
 */
uint8_t waterdetect2_get_fluid_status ( waterdetect2_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // WATERDETECT2_H

/*! @} */ // waterdetect2

// ------------------------------------------------------------------------ END
