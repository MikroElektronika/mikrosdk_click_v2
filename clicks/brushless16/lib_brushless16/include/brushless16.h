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
 * @file brushless16.h
 * @brief This file contains API for Brushless 16 Click Driver.
 */

#ifndef BRUSHLESS16_H
#define BRUSHLESS16_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/**
 * @defgroup brushless16_map Brushless 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Brushless 16 Click driver.
 */

/**
 * @addtogroup brushless16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Brushless 16 Click to the selected MikroBUS.
 */
#define BRUSHLESS16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.fg = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.rd = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // brushless16_map
/*! @} */ // brushless16

/**
 * @brief Brushless 16 Click context object.
 * @details Context object definition of Brushless 16 Click driver.
 */
typedef struct
{
    digital_out_t  en;  /**< Enable. */

    digital_in_t  fg;   /**< FG. */
    digital_in_t  rd;   /**< Motor lock. */

} brushless16_t;

/**
 * @brief Brushless 16 Click configuration object.
 * @details Configuration object definition of Brushless 16 Click driver.
 */
typedef struct
{
    pin_name_t  en;     /**< Enable. */
    pin_name_t  fg;     /**< FG. */
    pin_name_t  rd;     /**< Motor lock. */

} brushless16_cfg_t;

/**
 * @brief Brushless 16 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
   BRUSHLESS16_OK = 0,
   BRUSHLESS16_ERROR = -1

} brushless16_return_value_t;

/*!
 * @addtogroup brushless16 Brushless 16 Click Driver
 * @brief API for configuring and manipulating Brushless 16 Click driver.
 * @{
 */

/**
 * @brief Brushless 16 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #brushless16_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void brushless16_cfg_setup ( brushless16_cfg_t *cfg );

/**
 * @brief Brushless 16 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #brushless16_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #brushless16_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t brushless16_init ( brushless16_t *ctx, brushless16_cfg_t *cfg );

/**
 * @brief Set en pin state
 * @details This function sets the target pin on the high level of
 * Brushless 16 click board.
 * @param[in] ctx : Click context object.
 * See #brushless16_t object definition for detailed explanation.
 * @param[in] state : Pin state.
 * @return Nothing.
 */
void brushless16_set_en ( brushless16_t *ctx, uint8_t state );

/**
 * @brief Get rd pin state.
 * @details Read logic state of RD pin
 * @param[in] ctx : Click context object.
 * See #brushless16_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 */
uint8_t brushless16_get_rd ( brushless16_t *ctx );


/**
 * @brief Get fg pin state.
 * @details Read logic state of FG pin.
 * @param[in] ctx : Click context object.
 * See #brushless16_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 */
uint8_t brushless16_get_fg ( brushless16_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // BRUSHLESS16_H

/*! @} */ // brushless16

// ------------------------------------------------------------------------ END
