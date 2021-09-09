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
 * @file charger16.h
 * @brief This file contains API for Charger 16 Click Driver.
 */

#ifndef CHARGER16_H
#define CHARGER16_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup charger16 Charger 16 Click Driver
 * @brief API for configuring and manipulating Charger 16 Click driver.
 * @{
 */

/**
 * @defgroup charger16_map Charger 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Charger 16 Click driver.
 */

/**
 * @addtogroup charger16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Charger 16 Click to the selected MikroBUS.
 */
#define CHARGER16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.pwm = MIKROBUS( mikrobus, MIKROBUS_PWM )

/*! @} */ // charger16_map
/*! @} */ // charger16

/**
 * @brief Charger 16 Click context object.
 * @details Context object definition of Charger 16 Click driver.
 */
typedef struct
{
    digital_out_t  en;      /**< Enable pin. */
    digital_out_t  pwm;     /**< Programming the charge current pin. */

} charger16_t;

/**
 * @brief Charger 16 Click configuration object.
 * @details Configuration object definition of Charger 16 Click driver.
 */
typedef struct
{
    pin_name_t  en;     /**< Enable pin. */
    pin_name_t  pwm;    /**< Programming the charge current pin. */

} charger16_cfg_t;

/**
 * @brief Charger 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   CHARGER16_OK = 0,
   CHARGER16_ERROR = -1

} charger16_return_value_t;

/*!
 * @addtogroup charger16 Charger 16 Click Driver
 * @brief API for configuring and manipulating Charger 16 Click driver.
 * @{
 */

/**
 * @brief Charger 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #charger16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void charger16_cfg_setup ( charger16_cfg_t *cfg );

/**
 * @brief Charger 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #charger16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #charger16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger16_init ( charger16_t *ctx, charger16_cfg_t *cfg );

/**
 * @brief Charger 16 default configuration function.
 * @details This function executes a default configuration of Charger 16
 * click board.
 * @param[in] ctx : Click context object.
 * See #charger16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t charger16_default_cfg ( charger16_t *ctx );

/**
 * @brief Charger 16 enable charging function.
 * @details This function enable charging of the LT1571 Constant-Current/Constant-Voltage Battery Chargers 
 * with Preset Voltage and Termination Flag on the Charger 16 click board™.
 * @param[in] ctx : Click context object.
 * See #charger16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger16_enable_charging ( charger16_t *ctx );

/**
 * @brief Charger 16 disable charging function.
 * @details This function disable charging of the LT1571 Constant-Current/Constant-Voltage Battery Chargers 
 * with Preset Voltage and Termination Flag on the Charger 16 click board™.
 * @param[in] ctx : Click context object.
 * See #charger16_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t charger16_disable_charging ( charger16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // CHARGER16_H

/*! @} */ // charger16

// ------------------------------------------------------------------------ END
