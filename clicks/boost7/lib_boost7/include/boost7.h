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
 * @file boost7.h
 * @brief This file contains API for Boost 7 Click Driver.
 */

#ifndef BOOST7_H
#define BOOST7_H

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
 * @addtogroup boost7 Boost 7 Click Driver
 * @brief API for configuring and manipulating Boost 7 Click driver.
 * @{
 */

/**
 * @defgroup boost7_map Boost 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Boost 7 Click driver.
 */

/**
 * @addtogroup boost7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Boost 7 Click to the selected MikroBUS.
 */
#define BOOST7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.stb1 = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.stb2 = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // boost7_map
/*! @} */ // boost7

/**
 * @brief Boost 7 Click context object.
 * @details Context object definition of Boost 7 Click driver.
 */
typedef struct
{
    digital_out_t stb1;         /**< Standby pin for VOUT 1 (Active low). */
    digital_out_t stb2;         /**< Standby pin for VOUT 2 (Active low). */

} boost7_t;

/**
 * @brief Boost 7 Click configuration object.
 * @details Configuration object definition of Boost 7 Click driver.
 */
typedef struct
{
    pin_name_t stb1;            /**< Standby pin for VOUT 1 (Active low). */
    pin_name_t stb2;            /**< Standby pin for VOUT 2 (Active low). */

} boost7_cfg_t;

/**
 * @brief Boost 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BOOST7_OK = 0,
    BOOST7_ERROR = -1

} boost7_return_value_t;

/*!
 * @addtogroup boost7 Boost 7 Click Driver
 * @brief API for configuring and manipulating Boost 7 Click driver.
 * @{
 */

/**
 * @brief Boost 7 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #boost7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void boost7_cfg_setup ( boost7_cfg_t *cfg );

/**
 * @brief Boost 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #boost7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #boost7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t boost7_init ( boost7_t *ctx, boost7_cfg_t *cfg );

/**
 * @brief Boost 7 enable out1 function.
 * @details This function enables the OUT1 (V-) by setting the STB1 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #boost7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost7_enable_out1 ( boost7_t *ctx );

/**
 * @brief Boost 7 disable out1 function.
 * @details This function disables the OUT1 (V-) by setting the STB1 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #boost7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost7_disable_out1 ( boost7_t *ctx );

/**
 * @brief Boost 7 enable out2 function.
 * @details This function enables the OUT2 (V+) by setting the STB2 pin to high logic state.
 * @param[in] ctx : Click context object.
 * See #boost7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost7_enable_out2 ( boost7_t *ctx );

/**
 * @brief Boost 7 disable out2 function.
 * @details This function disables the OUT2 (V+) by setting the STB2 pin to low logic state.
 * @param[in] ctx : Click context object.
 * See #boost7_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void boost7_disable_out2 ( boost7_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BOOST7_H

/*! @} */ // boost7

// ------------------------------------------------------------------------ END
