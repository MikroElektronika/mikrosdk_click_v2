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
 * @file tilt3.h
 * @brief This file contains API for Tilt 3 Click Driver.
 */

#ifndef TILT3_H
#define TILT3_H

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
 * @addtogroup tilt3 Tilt 3 Click Driver
 * @brief API for configuring and manipulating Tilt 3 Click driver.
 * @{
 */

/**
 * @defgroup tilt3_set Tilt 3 Settings
 * @brief Settings of Tilt 3 Click driver.
 */

/**
 * @addtogroup tilt3_set
 * @{
 */

/**
 * @brief Tilt 3 tilt switch states.
 * @details Specified tilt switch states of Tilt 3 Click driver.
 */
#define TILT3_SWITCH_OFF       0
#define TILT3_SWITCH_ON        1


/*! @} */ // tilt3_set

/**
 * @defgroup tilt3_map Tilt 3 MikroBUS Map
 * @brief MikroBUS pin mapping of Tilt 3 Click driver.
 */

/**
 * @addtogroup tilt3_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Tilt 3 Click to the selected MikroBUS.
 */
#define TILT3_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.en = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // tilt3_map
/*! @} */ // tilt3

/**
 * @brief Tilt 3 Click context object.
 * @details Context object definition of Tilt 3 Click driver.
 */
typedef struct
{
    digital_out_t  en;          /**< Enable pin. */
    digital_in_t   int_pin;     /**< Interrupt pin. */

} tilt3_t;

/**
 * @brief Tilt 3 Click configuration object.
 * @details Configuration object definition of Tilt 3 Click driver.
 */
typedef struct
{
    pin_name_t  en;             /**< Enable pin. */
    pin_name_t  int_pin;        /**< Interrupt pin. */

} tilt3_cfg_t;

/**
 * @brief Tilt 3 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    TILT3_OK = 0,
    TILT3_ERROR = -1

} tilt3_return_value_t;

/*!
 * @addtogroup tilt3 Tilt 3 Click Driver
 * @brief API for configuring and manipulating Tilt 3 Click driver.
 * @{
 */

/**
 * @brief Tilt 3 configuration object setup function.
 * @details This function initializes click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #tilt3_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void tilt3_cfg_setup ( tilt3_cfg_t *cfg );

/**
 * @brief Tilt 3 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this click board.
 * @param[out] ctx : Click context object.
 * See #tilt3_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #tilt3_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t tilt3_init ( tilt3_t *ctx, tilt3_cfg_t *cfg );

/**
 * @brief Tilt 3 enable switch function.
 * @details This function enables the tilt switch by setting the EN pin to the high logic state.
 * @param[in] ctx : Click context object.
 * See #tilt3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void tilt3_enable_switch ( tilt3_t *ctx );

/**
 * @brief Tilt 3 disable switch function.
 * @details This function disables the tilt switch by setting the EN pin to the low logic state.
 * @param[in] ctx : Click context object.
 * See #tilt3_t object definition for detailed explanation.
 * @return Nothing.
 * @note None.
 */
void tilt3_disable_switch ( tilt3_t *ctx );

/**
 * @brief Tilt 3 get switch state function.
 * @details This function returns the INT pin logic state which indicates the tilt switch state. 
 * @param[in] ctx : Click context object.
 * See #tilt3_t object definition for detailed explanation.
 * @return @li @c 0 - Switch OFF,
 *         @li @c 1 - Switch ON.
 * @note None.
 */
uint8_t tilt3_get_switch_state ( tilt3_t *ctx );

#ifdef __cplusplus
}
#endif
#endif // TILT3_H

/*! @} */ // tilt3

// ------------------------------------------------------------------------ END
