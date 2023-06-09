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
 * @file powermux.h
 * @brief This file contains API for Power MUX Click Driver.
 */

#ifndef POWERMUX_H
#define POWERMUX_H

#ifdef __cplusplus
extern "C"{
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"

/*!
 * @addtogroup powermux Power MUX Click Driver
 * @brief API for configuring and manipulating Power MUX Click driver.
 * @{
 */

/**
 * @defgroup powermux_set Power MUX Registers Settings
 * @brief Settings for registers of Power MUX Click driver.
 */

/**
 * @addtogroup powermux_set
 * @{
 */

/**
 * @brief Power MUX description setting.
 * @details Specified setting for description of Power MUX Click driver.
 */
#define POWERMUX_INPUT_CHANNEL_1_ON             0
#define POWERMUX_INPUT_CHANNEL_2_ON             1
#define POWERMUX_INPUT_CHANNEL_OFF              2
#define POWERMUX_INPUT_CHANNEL_AUTO             3

/*! @} */ // powermux_set

/**
 * @defgroup powermux_map Power MUX MikroBUS Map
 * @brief MikroBUS pin mapping of Power MUX Click driver.
 */

/**
 * @addtogroup powermux_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Power MUX Click to the selected MikroBUS.
 */
#define POWERMUX_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.d0 = MIKROBUS( mikrobus, MIKROBUS_RST ); \
    cfg.d1 = MIKROBUS( mikrobus, MIKROBUS_PWM ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // powermux_map
/*! @} */ // powermux

/**
 * @brief Power MUX Click context object.
 * @details Context object definition of Power MUX Click driver.
 */
typedef struct
{
    digital_out_t d0;       /**< Control pin 0. */
    digital_out_t d1;       /**< Control pin 1. */

    digital_in_t  int_pin;  /**< Switch status pin. */

} powermux_t;

/**
 * @brief Power MUX Click configuration object.
 * @details Configuration object definition of Power MUX Click driver.
 */
typedef struct
{
    pin_name_t d0;          /**< Control pin 0. */
    pin_name_t d1;          /**< Control pin 1. */
    pin_name_t int_pin;     /**< Switch status pin. */

} powermux_cfg_t;

/**
 * @brief Power MUX Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    POWERMUX_OK = 0,
    POWERMUX_ERROR = -1

} powermux_return_value_t;

/*!
 * @addtogroup powermux Power MUX Click Driver
 * @brief API for configuring and manipulating Power MUX Click driver.
 * @{
 */

/**
 * @brief Power MUX configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #powermux_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void powermux_cfg_setup ( powermux_cfg_t *cfg );

/**
 * @brief Power MUX initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #powermux_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #powermux_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg );

/**
 * @brief Power MUX default configuration function.
 * @details This function executes a default configuration of Power MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #powermux_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
void powermux_default_cfg ( powermux_t *ctx );

/**
 * @brief Power MUX pin reading function.
 * @details This function reads the state of the INT pin of Power MUX
 * click board.
 * @param[in] ctx : Click context object.
 * See #powermux_t object definition for detailed explanation.
 * @return @li @c 0 - Low pin state,
 *         @li @c 1 - High pin state.
 */
uint8_t powermux_int_pin_read ( powermux_t *ctx );

/**
 * @brief Power MUX mode set function.
 * @details This function sets operating mode of Power MUX click board.
 * @param[in] ctx : Click context object.
 * See #powermux_t object definition for detailed explanation.
 * @param[in] mode : Operating mode.
 * @return Nothing.
 */
void powermux_set_mode ( powermux_t *ctx, uint8_t mode );

#ifdef __cplusplus
}
#endif
#endif // POWERMUX_H

/*! @} */ // powermux

// ------------------------------------------------------------------------ END
