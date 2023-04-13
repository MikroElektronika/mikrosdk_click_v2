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
 * @file captouch6.h
 * @brief This file contains API for Cap Touch 6 Click Driver.
 */

#ifndef CAPTOUCH6_H
#define CAPTOUCH6_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup captouch6 Cap Touch 6 Click Driver
 * @brief API for configuring and manipulating Cap Touch 6 Click driver.
 * @{
 */

/**
 * @defgroup captouch6_map Cap Touch 6 MikroBUS Map
 * @brief MikroBUS pin mapping of Cap Touch 6 Click driver.
 */

/**
 * @addtogroup captouch6_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Cap Touch 6 Click to the selected MikroBUS.
 */
#define CAPTOUCH6_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.tout = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.pout = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // captouch6_map
/*! @} */ // captouch6

/**
 * @brief Cap Touch 6 Click context object.
 * @details Context object definition of Cap Touch 6 Click driver.
 */
typedef struct
{
    digital_in_t tout;          /**< Touch event pin. */
    digital_in_t pout;          /**< Proximity event pin. */

} captouch6_t;

/**
 * @brief Cap Touch 6 Click configuration object.
 * @details Configuration object definition of Cap Touch 6 Click driver.
 */
typedef struct
{
    pin_name_t tout;            /**< Touch event pin. */
    pin_name_t pout;            /**< Proximity event pin. */

} captouch6_cfg_t;

/**
 * @brief Cap Touch 6 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    CAPTOUCH6_OK = 0,
    CAPTOUCH6_ERROR = -1

} captouch6_return_value_t;

/*!
 * @addtogroup captouch6 Cap Touch 6 Click Driver
 * @brief API for configuring and manipulating Cap Touch 6 Click driver.
 * @{
 */

/**
 * @brief Cap Touch 6 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #captouch6_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void captouch6_cfg_setup ( captouch6_cfg_t *cfg );

/**
 * @brief Cap Touch 6 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #captouch6_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #captouch6_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t captouch6_init ( captouch6_t *ctx, captouch6_cfg_t *cfg );

/**
 * @brief Cap Touch 6 get tout pin function.
 * @details This function returns the TOUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #captouch6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t captouch6_get_tout_pin ( captouch6_t *ctx );

/**
 * @brief Cap Touch 6 get pout pin function.
 * @details This function returns the POUT pin logic state.
 * @param[in] ctx : Click context object.
 * See #captouch6_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 * @note None.
 */
uint8_t captouch6_get_pout_pin ( captouch6_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CAPTOUCH6_H

/*! @} */ // captouch6

// ------------------------------------------------------------------------ END
