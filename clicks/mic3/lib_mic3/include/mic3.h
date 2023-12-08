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
 * @file mic3.h
 * @brief This file contains API for MIC 3 Click Driver.
 */

#ifndef MIC3_H
#define MIC3_H

#ifdef __cplusplus
extern "C"{
#endif

#include "mikrosdk_version.h"

#ifdef __GNUC__
#if mikroSDK_GET_VERSION < 20800ul
#include "rcu_delays.h"
#else
#include "delays.h"
#endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup mic3 MIC 3 Click Driver
 * @brief API for configuring and manipulating MIC 3 Click driver.
 * @{
 */

/**
 * @defgroup mic3_set MIC 3 Registers Settings
 * @brief Settings for registers of MIC 3 Click driver.
 */

/**
 * @addtogroup mic3_set
 * @{
 */

/**
 * @brief MIC 3 description setting.
 * @details Specified setting for description of MIC 3 Click driver.
 */
#define MIC3_PIN_STATE_HIGH                 0x01
#define MIC3_PIN_STATE_LOW                  0x00

/*! @} */ // mic3_set

/**
 * @defgroup mic3_map MIC 3 MikroBUS Map
 * @brief MikroBUS pin mapping of MIC 3 Click driver.
 */

/**
 * @addtogroup mic3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of MIC 3 Click to the selected MikroBUS.
 */
#define MIC3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.shd = MIKROBUS( mikrobus, MIKROBUS_CS )

/*! @} */ // mic3_map
/*! @} */ // mic3

/**
 * @brief MIC 3 Click context object.
 * @details Context object definition of MIC 3 Click driver.
 */
typedef struct
{
    digital_out_t  shd;         /**< Shutdown. */
    
} mic3_t;

/**
 * @brief MIC 3 Click configuration object.
 * @details Configuration object definition of MIC 3 Click driver.
 */
typedef struct
{
    pin_name_t  shd;            /**< Shutdown. */


} mic3_cfg_t;

/**
 * @brief MIC 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   MIC3_OK = 0,
   MIC3_ERROR = -1

} mic3_return_value_t;

/*!
 * @addtogroup mic3 MIC 3 Click Driver
 * @brief API for configuring and manipulating MIC 3 Click driver.
 * @{
 */

/**
 * @brief MIC 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #mic3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void mic3_cfg_setup ( mic3_cfg_t *cfg );

/**
 * @brief MIC 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #mic3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #mic3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 */
err_t mic3_init ( mic3_t *ctx, mic3_cfg_t *cfg );

/**
 * @brief MIC 3 default configuration function.
 * @details This function executes a default configuration of MIC 3
 * click board.
 * @param[in] ctx : Click context object.
 * See #mic3_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t mic3_default_cfg ( mic3_t *ctx );

/**
 * @brief MIC 3 SHD pin setting function.
 * @details This function sets the target pin on the high level of
 * MIC 3 click board.
 * @param[in] ctx : Click context object.
 * See #mic3_t object definition for detailed explanation.
 * @param[in] state : State of the SHD pin.
 * @return Nothing.
 */
void mic3_shd_pin_set ( mic3_t *ctx, uint8_t state ); 

#ifdef __cplusplus
}
#endif
#endif // MIC3_H

/*! @} */ // mic3

// ------------------------------------------------------------------------ END
