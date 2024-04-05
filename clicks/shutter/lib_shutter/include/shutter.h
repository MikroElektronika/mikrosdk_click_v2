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
 * @file shutter.h
 * @brief This file contains API for Shutter Click Driver.
 */

#ifndef SHUTTER_H
#define SHUTTER_H

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
 * @addtogroup shutter Shutter Click Driver
 * @brief API for configuring and manipulating Shutter Click driver.
 * @{
 */

/**
 * @defgroup shutter_set Shutter Settings
 * @brief Settings of Shutter Click driver.
 */

/**
 * @addtogroup shutter_set
 * @{
 */

/**
 * @brief Shutter state setting.
 * @details Specified setting for state of Shutter Click driver.
 */
#define SHUTTER_STATE_OFF           0
#define SHUTTER_STATE_ON            1

/*! @} */ // shutter_set

/**
 * @defgroup shutter_map Shutter MikroBUS Map
 * @brief MikroBUS pin mapping of Shutter Click driver.
 */

/**
 * @addtogroup shutter_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Shutter Click to the selected MikroBUS.
 */
#define SHUTTER_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.af = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.sht = MIKROBUS( mikrobus, MIKROBUS_AN );

/*! @} */ // shutter_map
/*! @} */ // shutter

/**
 * @brief Shutter Click context object.
 * @details Context object definition of Shutter Click driver.
 */
typedef struct
{
    digital_out_t af;           /**< Auto focus pin. */
    digital_out_t sht;          /**< Shutter pin. */

} shutter_t;

/**
 * @brief Shutter Click configuration object.
 * @details Configuration object definition of Shutter Click driver.
 */
typedef struct
{
    pin_name_t af;              /**< Auto focus pin. */
    pin_name_t sht;             /**< Shutter pin. */

} shutter_cfg_t;

/**
 * @brief Shutter Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    SHUTTER_OK = 0,
    SHUTTER_ERROR = -1

} shutter_return_value_t;

/*!
 * @addtogroup shutter Shutter Click Driver
 * @brief API for configuring and manipulating Shutter Click driver.
 * @{
 */

/**
 * @brief Shutter configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #shutter_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void shutter_cfg_setup ( shutter_cfg_t *cfg );

/**
 * @brief Shutter initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #shutter_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #shutter_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t shutter_init ( shutter_t *ctx, shutter_cfg_t *cfg );

/**
 * @brief Shutter set auto focus function.
 * @details This function sets the auto focus ON/OFF by setting the AF pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #shutter_t object definition for detailed explanation.
 * @param[in] state : Auto focus state: 0 - OFF, 1 - ON.
 * @return None.
 * @note None.
 */
void shutter_set_auto_focus ( shutter_t *ctx, uint8_t state );

/**
 * @brief Shutter set shutter function.
 * @details This function sets the shutter ON/OFF by setting the SHT pin to desired logic state.
 * @param[in] ctx : Click context object.
 * See #shutter_t object definition for detailed explanation.
 * @param[in] state : Shutter state: 0 - OFF, 1 - ON.
 * @return None.
 * @note None.
 */
void shutter_set_shutter ( shutter_t *ctx, uint8_t state );

/**
 * @brief Shutter take picture function.
 * @details This function sets AF and SHT pins to desired states for taking pictures with or
 * without auto focus function.
 * @param[in] ctx : Click context object.
 * See #shutter_t object definition for detailed explanation.
 * @param[in] auto_focus : Auto focus state: @li @c 0 - OFF - disables auto focus then triggers shutter,
 *                                           @li @c 1 - ON - enables auto focus then triggers shutter.
 * @return None.
 * @note None.
 */
void shutter_take_picture ( shutter_t *ctx, uint8_t auto_focus );

#ifdef __cplusplus
}
#endif
#endif // SHUTTER_H

/*! @} */ // shutter

// ------------------------------------------------------------------------ END
