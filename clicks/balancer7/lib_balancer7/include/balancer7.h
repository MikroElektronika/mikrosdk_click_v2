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
 * @file balancer7.h
 * @brief This file contains API for Balancer 7 Click Driver.
 */

#ifndef BALANCER7_H
#define BALANCER7_H

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
 * @addtogroup balancer7 Balancer 7 Click Driver
 * @brief API for configuring and manipulating Balancer 7 Click driver.
 * @{
 */

/**
 * @defgroup balancer7_set Balancer 7 Settings
 * @brief Settings of Balancer 7 Click driver.
 */

/**
 * @addtogroup balancer7_set
 * @{
 */

/**
 * @brief Balancer 7 device mode setting.
 * @details Specified setting for device mode of Balancer 7 Click driver.
 */
#define BALANCER7_MODE_BUCK             0
#define BALANCER7_MODE_BOOST            1

/*! @} */ // balancer7_set

/**
 * @defgroup balancer7_map Balancer 7 MikroBUS Map
 * @brief MikroBUS pin mapping of Balancer 7 Click driver.
 */

/**
 * @addtogroup balancer7_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Balancer 7 Click to the selected MikroBUS.
 */
#define BALANCER7_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.mb_en = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.mb_md = MIKROBUS( mikrobus, MIKROBUS_PWM );

/*! @} */ // balancer7_map
/*! @} */ // balancer7

/**
 * @brief Balancer 7 Click context object.
 * @details Context object definition of Balancer 7 Click driver.
 */
typedef struct
{
    digital_out_t mb_en;            /**< Enable pin(Active high). */
    digital_out_t mb_md;            /**< Mode pin(high - boost, low - buck). */

} balancer7_t;

/**
 * @brief Balancer 7 Click configuration object.
 * @details Configuration object definition of Balancer 7 Click driver.
 */
typedef struct
{
    pin_name_t mb_en;               /**< Enable pin descriptor. */
    pin_name_t mb_md;               /**< Mode pin descriptor. */

} balancer7_cfg_t;

/**
 * @brief Balancer 7 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    BALANCER7_OK = 0,
    BALANCER7_ERROR = -1

} balancer7_return_value_t;

/*!
 * @addtogroup balancer7 Balancer 7 Click Driver
 * @brief API for configuring and manipulating Balancer 7 Click driver.
 * @{
 */

/**
 * @brief Balancer 7 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #balancer7_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void balancer7_cfg_setup ( balancer7_cfg_t *cfg );

/**
 * @brief Balancer 7 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #balancer7_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #balancer7_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t balancer7_init ( balancer7_t *ctx, balancer7_cfg_t *cfg );

/**
 * @brief Balancer 7 enable device function.
 * @details This function enables the device by setting the MB_EN pin to the high logic level.
 * @param[in] ctx : Click context object.
 * See #balancer7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void balancer7_enable_device ( balancer7_t *ctx );

/**
 * @brief Balancer 7 disable device function.
 * @details This function disables the device by setting the MB_EN pin to the low logic level.
 * @param[in] ctx : Click context object.
 * See #balancer7_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void balancer7_disable_device ( balancer7_t *ctx );

/**
 * @brief Balancer 7 set mode function.
 * @details This function selects the balancing mode by setting the MB_MD pin logic level.
 * @param[in] ctx : Click context object.
 * See #balancer7_t object definition for detailed explanation.
 * @param[in] mode : @li @c 0 - Buck-balance mode (charge from the upper cell to the lower cell),
 *                   @li @c 1 - Boost-balance mode (charge from the lower cell to the upper cell).
 * @return Nothing.
 * @note None.
 */
void balancer7_set_mode ( balancer7_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // BALANCER7_H

/*! @} */ // balancer7

// ------------------------------------------------------------------------ END
